#!/usr/bin/env python3
"""asmgrep.py: find how an assembly shape was written in C/C++ in the
functions that already match.

Every 100 % function's instructions are the target's, so its source is a
known-good way to produce them. This tool indexes the target assembly of
all matched functions (build/GNLJ82/asm/<unit>.s, restricted by
build/GNLJ82/report.json) and searches it with a small register-agnostic
pattern language. Use it on a near miss: take the target window that you
cannot reproduce, look for matched functions that contain the same shape,
and read how their source is written.

    python3 tools/asmgrep.py index
    python3 tools/asmgrep.py find -e 'fmadds $a, *, *, $a' -e '...' -e 'lfs $t, 0x30($m)' \\
        -e 'fadds $a, $t, $a' [--src] [--limit 20]
    python3 tools/asmgrep.py find -f pattern.txt
    python3 tools/asmgrep.py like game/kartmove/carobject fn_8019EB9C \\
        [--from 0x48 --to 0x78] [--loose] [--src]
    python3 tools/asmgrep.py similar game/kartmove/carobject fn_8019EB9C [--from/--to] [--src]
    python3 tools/asmgrep.py idioms [--md docs/reports/asm_idioms.md] [--json OUT]

Pattern language (one instruction per -e / per line of -f):
  mnemonic      a regular expression, matched in full (`fm(add|sub)s`, `l[bhw]z`)
  operands      comma separated; a memory operand `off(base)` is two operands
    $name       a register variable. Every $name binds one register; two
                different names never bind the same register.
    r5 / f4     a concrete register is a variable too (pasting the target's
                asm works across register numbering) unless --exact-regs.
                r1 (stack), r2 and r13 (small-data bases) always match literally.
    *           any one operand
    #           any immediate
    SYM         any symbol reference (lbl_xxx@sda21, foo@ha, a branch target);
                SYM:glob (SYM:lbl_806D*) matches by name
    other       literal (numbers compare by value: 0x30 == 48)
  ...  / ...N   gap: up to N (default --gap) arbitrary instructions
  #comment      ignored

Run after a build (`ninja` produces report.json and the split asm). The
index is cached in build/asmgrep/index.json; `index` rebuilds it, the other
commands build it when missing or older than report.json.
"""
from __future__ import annotations

import argparse
import fnmatch
import json
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BUILD = ROOT / "build" / "GNLJ82"
REPORT = BUILD / "report.json"
ASM = BUILD / "asm"
INDEX = ROOT / "build" / "asmgrep" / "index.json"
IDIOMS = Path(__file__).resolve().parent / "asm_idioms.json"

INS = re.compile(r"^/\*\s*([0-9A-F]{8})\s+[0-9A-F]+\s+(?:[0-9A-F]{2}\s?)+\*/\s+(\S+)\s*(.*)$")
FN_START = re.compile(r"^\.fn\s+([^,\s]+)")
FN_END = re.compile(r"^\.endfn\s+")
REG = re.compile(r"^([rf])(\d+)$")
MEM = re.compile(r"^(.*)\(([^()]+)\)$")
FIXED_REGS = {"r1", "r2", "r13"}


# --------------------------------------------------------------------------
# assembly parsing

def split_ops(s: str, comments=True) -> list[str]:
    if comments:
        s = s.split("#", 1)[0]
    s = s.strip()
    if not s:
        return []
    out = []
    for a in re.split(r",\s*", s):
        m = MEM.match(a)
        if m:
            out += [m.group(1) or "0", m.group(2)]
        else:
            out.append(a)
    return out


def parse_asm_file(path: Path) -> dict[str, list[list]]:
    """{fn: [[addr, mnemonic, [operands...]], ...]} for every .fn in a dtk .s file."""
    fns, cur, name = {}, None, None
    for line in path.read_text(errors="replace").splitlines():
        m = FN_START.match(line)
        if m:
            name, cur = m.group(1), []
            continue
        if cur is None:
            continue
        if FN_END.match(line):
            fns[name] = cur
            cur = None
            continue
        m = INS.match(line)
        if m:
            cur.append([int(m.group(1), 16), m.group(2), split_ops(m.group(3)), m.group(3).split("#", 1)[0].strip()])
    return fns


def load_report():
    if not REPORT.exists():
        sys.exit(f"{REPORT} missing: run ninja first")
    return json.loads(REPORT.read_text())


def unit_key(unit_name: str) -> str:
    # report unit names look like "main/game/foo"
    return unit_name.split("/", 1)[1] if "/" in unit_name else unit_name


_RENAMES = None


def compiled_names(fn: str) -> list[str]:
    """Names the compiler gives fn before tools/extab_user_renames.json renames it."""
    global _RENAMES
    if _RENAMES is None:
        _RENAMES = {}
        p = ROOT / "tools" / "extab_user_renames.json"
        if p.exists():
            for tu in json.loads(p.read_text()).values():
                if isinstance(tu, dict):
                    for k, v in tu.items():
                        _RENAMES.setdefault(v, set()).add(k)
    return sorted(_RENAMES.get(fn, ()))


def cw_demangle_names(m: str) -> list[str]:
    """Search names for a CodeWarrior mangled symbol: __ct__6StrPcbFi -> StrPcb(,
    __dt__7STLTreeFv -> ~STLTree(, Update__5clCabFv -> clCab::Update( / Update(."""
    mm = re.match(r"^(\w+?)__(\d+)(\w+)", m)
    if not mm:
        return []
    meth, n, rest = mm.group(1), int(mm.group(2)), mm.group(3)
    cls = rest[:n]
    if meth == "__ct":
        return [f"{cls}::{cls}", cls]
    if meth == "__dt":
        return [f"{cls}::~{cls}", "~" + cls]
    if meth.startswith("__"):
        return [f"{cls}::operator"]
    return [f"{cls}::{meth}", meth]


def _includes(path: Path, seen: set) -> list[Path]:
    out = []
    try:
        text = path.read_text(errors="replace")
    except OSError:
        return out
    for inc in re.findall(r'^\s*#\s*include\s+"([^"]+)"', text, re.M):
        for cand in (ROOT / inc, path.parent / inc):
            if cand.exists() and cand not in seen and cand.suffix in (".c", ".cpp", ".cp", ".h", ".inc"):
                seen.add(cand)
                out.append(cand)
                out += _includes(cand, seen)
                break
    return out


def find_def_line(src: Path, fn: dict):
    """Best-effort (file, line) of the function definition: the unit source and
    the files it #includes are searched for fn's name, its demangled name, and
    the compiler names it is renamed from."""
    names = [fn["name"]]
    dn = fn.get("demangled_name") or ""
    if dn:
        base = dn.split("(", 1)[0]
        names += [base, base.split("::")[-1]]
    for c in [fn["name"]] + compiled_names(fn["name"]):
        if c != fn["name"]:
            names.append(c)
        names += cw_demangle_names(c)
    files = [src] + _includes(src, {src})
    for nm in dict.fromkeys(n for n in names if n):
        pat = re.compile(r"(?<![\w:~.>])" + re.escape(nm) + r"\s*\(")
        short = "::" not in nm
        for path in files:
            try:
                lines = path.read_text(errors="replace").splitlines()
            except OSError:
                continue
            for i, l in enumerate(lines):
                if not pat.search(l):
                    continue
                st = l.strip()
                if st.endswith(";") or st.startswith(("//", "*", "/*", "return", "#")):
                    continue
                # a definition: the next non-blank text after the parameter list is '{'
                tail = " ".join(lines[i:i + 6])
                after = tail[tail.find(nm):]
                m = re.match(re.escape(nm) + r"\s*\([^;{]*\)[^;{]*\{", after)
                if not m:
                    continue
                if short and l[:1] in " \t" and not l.lstrip().startswith(("static", "inline", "extern", "void", "int")) \
                        and fn["name"] != nm and "::" not in l:
                    # indented short name: allow in-class definitions only
                    pass
                return str(path.relative_to(ROOT)), i + 1
    return None, None


def build_index(verbose=True):
    rep = load_report()
    out = []
    asm_cache: dict[str, dict] = {}
    n_units = 0
    for u in rep.get("units", []):
        key = unit_key(u["name"])
        src = (u.get("metadata") or {}).get("source_path")
        fns = [f for f in u.get("functions", []) if f.get("fuzzy_match_percent", 0) >= 100.0]
        if not fns:
            continue
        asm_path = ASM / (key + ".s")
        if not asm_path.exists():
            continue
        if key not in asm_cache:
            asm_cache[key] = parse_asm_file(asm_path)
        n_units += 1
        for f in fns:
            ins = asm_cache[key].get(f["name"])
            if not ins:
                continue
            dsrc, line = find_def_line(ROOT / src, f) if src else (None, None)
            out.append({
                "fn": f["name"], "demangled": f.get("demangled_name"), "unit": key,
                "src": dsrc or src, "line": line, "ins": ins,
            })
    INDEX.parent.mkdir(parents=True, exist_ok=True)
    INDEX.write_text(json.dumps({"report_mtime": REPORT.stat().st_mtime, "fns": out}))
    if verbose:
        print(f"indexed {len(out)} matched functions from {n_units} units -> {INDEX.relative_to(ROOT)}",
              file=sys.stderr)
    return out


def load_index():
    if INDEX.exists() and REPORT.exists():
        d = json.loads(INDEX.read_text())
        if d.get("report_mtime", 0) >= REPORT.stat().st_mtime:
            return d["fns"]
    return build_index()


# --------------------------------------------------------------------------
# pattern language

class Pat:
    """One compiled pattern: list of ('gap', n) | ('ins', mnemonic_re, [op, ...])."""

    def __init__(self, lines: list[str], gap=6, exact_regs=False):
        self.items = []
        self.src = []
        for raw in lines:
            l = raw.strip()
            if not l or l.startswith("#") or l.startswith("//"):
                continue
            self.src.append(l)
            m = re.fullmatch(r"\.\.\.(\d*)", l)
            if m:
                self.items.append(("gap", int(m.group(1)) if m.group(1) else gap))
                continue
            parts = l.split(None, 1)
            mn = re.compile(parts[0].replace(".", r"\.") if not any(c in parts[0] for c in "()|[]*+?") else parts[0])
            ops = split_ops(parts[1], comments=False) if len(parts) > 1 else None
            if ops is not None:
                ops = [self.op(o, exact_regs) for o in ops]
            self.items.append(("ins", mn, ops))

    @staticmethod
    def op(o: str, exact_regs: bool):
        o = o.strip()
        if o == "*":
            return ("any",)
        if o == "#":
            return ("imm",)
        if o.startswith("$"):
            return ("var", o)
        if o == "SYM" or o.startswith("SYM:"):
            return ("sym", o[4:] or "*")
        if REG.match(o):
            if o in FIXED_REGS or exact_regs:
                return ("lit", o)
            return ("var", "$" + o)
        return ("lit", o)


def num(s: str):
    try:
        return int(s, 0)
    except ValueError:
        return None


def is_sym(o: str) -> bool:
    return bool(re.match(r"^[A-Za-z_.$][\w.$@<>:-]*$", o)) and not REG.match(o) and o not in ("qr0",) \
        and not o.startswith(("cr", "qr"))


def match_op(p, o: str, env: dict, used: dict):
    k = p[0]
    if k == "any":
        return env, used
    if k == "imm":
        return (env, used) if num(o) is not None else None
    if k == "sym":
        if not is_sym(o):
            return None
        name = o.split("@", 1)[0]
        return (env, used) if fnmatch.fnmatch(name, p[1]) else None
    if k == "lit":
        if o == p[1]:
            return env, used
        a, b = num(o), num(p[1])
        return (env, used) if a is not None and a == b else None
    # var
    if not REG.match(o) or o in FIXED_REGS:
        return None
    v = p[1]
    if v in env:
        return (env, used) if env[v] == o else None
    if o in used:
        return None
    env = dict(env); used = dict(used)
    env[v] = o; used[o] = v
    return env, used


def match_ins(item, ins, env, used):
    _, mn, ops = item
    if not mn.fullmatch(ins[1]):
        return None
    if ops is None:
        return env, used
    if len(ops) != len(ins[2]):
        return None
    for p, o in zip(ops, ins[2]):
        r = match_op(p, o, env, used)
        if r is None:
            return None
        env, used = r
    return env, used


def match_at(items, ins, i, k=0, env=None, used=None, hit=None):
    """Yield (end_index, env, matched_indices) for items[k:] starting at ins[i]."""
    env = env or {}; used = used or {}; hit = hit or []
    if k == len(items):
        yield i, env, hit
        return
    it = items[k]
    if it[0] == "gap":
        for j in range(i, min(len(ins), i + it[1]) + 1):
            yield from match_at(items, ins, j, k + 1, env, used, hit)
        return
    if i >= len(ins):
        return
    r = match_ins(it, ins[i], env, used)
    if r is not None:
        yield from match_at(items, ins, i + 1, k + 1, r[0], r[1], hit + [i])


def search(fns, pat: Pat, limit=None, exclude=()):
    items = pat.items
    while items and items[0][0] == "gap":
        items = items[1:]
    hits = []
    for f in fns:
        if f["fn"] in exclude:
            continue
        ins = f["ins"]
        for i in range(len(ins)):
            m = next(match_at(items, ins, i), None)
            if m:
                hits.append((f, i, m[0], m[2]))
                break
        if limit and len(hits) >= limit * 20:
            break
    hits.sort(key=lambda h: len(h[0]["ins"]))
    return hits[:limit] if limit else hits


# --------------------------------------------------------------------------
# output

def fmt_ins(ins):
    if len(ins) > 3:
        return f"{ins[1]} {ins[3]}".rstrip()
    return f"{ins[1]} {', '.join(ins[2])}"


# --------------------------------------------------------------------------
# n-gram similarity (fast "which matched functions look like this code")

def norm_window(win) -> tuple:
    """Register-renamed, immediate-free form of a short instruction window."""
    ren, out = {}, []
    for ins in win:
        ops = []
        for o in ins[2]:
            if REG.match(o) and o not in FIXED_REGS:
                ren.setdefault(o, f"{o[0]}{len([k for k in ren if k[0] == o[0]])}")
                ops.append(ren[o])
            elif num(o) is not None:
                ops.append("#")
            elif o.startswith(".L"):
                ops.append("L")
            elif is_sym(o):
                ops.append("S")
            else:
                ops.append(o)
        out.append(ins[1] + " " + ",".join(ops))
    return tuple(out)


def ngrams(ins, n=5) -> set:
    return {hash(norm_window(ins[i:i + n])) for i in range(max(0, len(ins) - n + 1))}


def cmd_similar(a, fns):
    asm = parse_asm_file(ASM / (a.unit + ".s"))
    if a.fn not in asm:
        sys.exit(f"{a.fn} not in {a.unit}.s")
    ins = asm[a.fn]
    base = ins[0][0]
    if a.frm or a.to:
        lo = int(a.frm, 0) if a.frm else 0
        hi = int(a.to, 0) if a.to else 1 << 32
        lo = lo if lo >= 0x80000000 else base + lo
        hi = hi if hi >= 0x80000000 else base + hi
        ins = [x for x in ins if lo <= x[0] < hi]
    for n in range(a.n, 2, -1):  # shorter windows when scheduling breaks the long ones
        q = ngrams(ins, n)
        if not q:
            continue
        scored = []
        for f in fns:
            if f["fn"] == a.fn:
                continue
            g = ngrams(f["ins"], n)
            inter = len(q & g)
            if inter:
                scored.append((inter / len(q), inter / max(1, len(g)), f))
        if scored:
            print(f"(window length {n})", file=sys.stderr)
            break
    else:
        sys.exit("no matched function shares a 3-instruction shape")
    scored.sort(key=lambda x: (-x[0], -x[1]))
    for cov, dens, f in scored[: a.limit]:
        loc = f"{f['src']}:{f['line']}" if f.get("line") else f.get("src")
        print(f"{100 * cov:5.1f}% of query  {100 * dens:5.1f}% of fn  {f['fn']:40s} {len(f['ins']):5d} insns  {loc}")
        if a.src:
            for l in func_source(f, a.max_lines):
                print("   | " + l)
            print()


def func_source(f, max_lines=40) -> list[str]:
    if not f.get("src") or not f.get("line"):
        return []
    try:
        lines = (ROOT / f["src"]).read_text(errors="replace").splitlines()
    except OSError:
        return []
    i = f["line"] - 1
    out, depth, seen = [], 0, False
    for l in lines[i:i + 400]:
        out.append(l)
        depth += l.count("{") - l.count("}")
        if "{" in l:
            seen = True
        if seen and depth <= 0:
            break
    if len(out) > max_lines:
        out = out[:max_lines] + [f"    ... ({len(out) - max_lines} more lines)"]
    return out


def show(hits, src=False, ctx=2, max_lines=40, total=None):
    for f, s, e, idx in hits:
        loc = f"{f['src']}:{f['line']}" if f.get("line") else (f.get("src") or f["unit"])
        print(f"== {f['fn']}  ({len(f['ins'])} insns)  {loc}")
        ins = f["ins"]
        lo, hi = max(0, s - ctx), min(len(ins), e + ctx)
        mark = set(idx)
        for j in range(lo, hi):
            print(f"   {'>' if j in mark else ' '} {ins[j][0]:08X}  {fmt_ins(ins[j])}")
        if src:
            for l in func_source(f, max_lines):
                print("   | " + l)
        print()
    n = total if total is not None else len(hits)
    print(f"{n} matched function(s)", file=sys.stderr)


# --------------------------------------------------------------------------
# commands

def window_pattern(ins, loose=False, keep_syms=False) -> list[str]:
    out = []
    for a, mn, ops in ins:
        ps = []
        for o in ops:
            if REG.match(o):
                ps.append(o)
            elif num(o) is not None:
                ps.append("#" if loose else o)
            elif mn.startswith("b") and o.startswith(".L"):
                ps.append("*")
            elif is_sym(o):
                ps.append(("SYM:" + o.split("@")[0]) if keep_syms else "SYM")
            else:
                ps.append("*")
        out.append(f"{mn} {', '.join(ps)}" if ps else mn)
    return out


def cmd_like(a, fns):
    asm = parse_asm_file(ASM / (a.unit + ".s"))
    if a.fn not in asm:
        sys.exit(f"{a.fn} not in {a.unit}.s")
    ins = asm[a.fn]
    base = ins[0][0]
    lo = base + (int(a.frm, 0) if a.frm else 0)
    hi = base + int(a.to, 0) if a.to else ins[-1][0] + 4
    if lo >= 0x80000000 - 0 and a.frm and int(a.frm, 0) >= 0x80000000:
        lo = int(a.frm, 0)
    if a.to and int(a.to, 0) >= 0x80000000:
        hi = int(a.to, 0)
    win = [x for x in ins if lo <= x[0] < hi]
    lines = window_pattern(win, a.loose, a.keep_syms)
    print("pattern:\n  " + "\n  ".join(lines), file=sys.stderr)
    pat = Pat(lines, exact_regs=a.exact_regs)
    hits = search(fns, pat, a.limit, exclude={a.fn})
    if hits or not a.sub:
        show(hits, a.src, max_lines=a.max_lines)
        return
    # no full hit: best sub-windows of length --sub
    best = {}
    for s in range(0, max(1, len(lines) - a.sub + 1)):
        p = Pat(lines[s:s + a.sub], exact_regs=a.exact_regs)
        for h in search(fns, p, None, exclude={a.fn}):
            best.setdefault(h[0]["fn"], [h, 0])[1] += 1
    ranked = sorted(best.values(), key=lambda x: (-x[1], len(x[0][0]["ins"])))[: a.limit]
    print(f"no full-window match; {len(best)} function(s) share {a.sub}-instruction sub-windows "
          f"(ranked by number of shared windows)", file=sys.stderr)
    show([r[0] for r in ranked], a.src, max_lines=a.max_lines)


def run_idioms(fns, max_examples=3):
    spec = json.loads(IDIOMS.read_text())
    res = []
    for idm in spec["idioms"]:
        pat = Pat(idm["pattern"], gap=idm.get("gap", 6))
        hits = search(fns, pat)
        res.append((idm, hits))
    return res


def cmd_idioms(a, fns):
    res = run_idioms(fns)
    if a.json:
        Path(a.json).write_text(json.dumps([
            {"id": i["id"], "count": len(h),
             "examples": [{"fn": f["fn"], "src": f["src"], "line": f["line"], "insns": len(f["ins"])}
                          for f, *_ in h[:10]]} for i, h in res], indent=1))
    if not a.md:
        for i, h in res:
            ex = ", ".join(f["fn"] for f, *_ in h[:3])
            print(f"{len(h):5d}  {i['id']:28s} {ex}")
        return
    md = ["# Assembly idioms and the C/C++ that produced them",
          "",
          "Generated by `python3 tools/asmgrep.py idioms --md docs/reports/asm_idioms.md` from the "
          "target assembly of every 100 % function (patterns: `tools/asm_idioms.json`). "
          "Count = matched functions containing the idiom; the example is the smallest one, with its "
          "source. Use `tools/asmgrep.py find` / `like` for shapes that are not listed.",
          ""]
    md += ["| idiom | functions | C/C++ form | examples |", "|---|---|---|---|"]
    for i, h in res:
        ex = ", ".join(f"`{f['fn']}`" for f, *_ in h[:4])
        md.append(f"| [{i['id']}](#{i['id'].lower()}) | {len(h)} | {i['source']} | {ex} |")
    md.append("")
    for i, h in res:
        md += [f"## {i['id']}", "", i.get("note", i["source"]), "", "```", *i["pattern"], "```", ""]
        if i.get("refs"):
            md += ["Refs: " + ", ".join(i["refs"]), ""]
        for f, s, e, idx in h[: a.examples]:
            loc = f"{f['src']}:{f['line']}" if f.get("line") else f.get("src")
            md += [f"`{f['fn']}` ({len(f['ins'])} insns, {loc})", "", "```"]
            mark = set(idx)
            for j in range(max(0, s - 1), min(len(f["ins"]), e + 1)):
                md.append(f"{'>' if j in mark else ' '} {fmt_ins(f['ins'][j])}")
            md += ["```", ""]
            body = func_source(f, a.max_lines)
            if body:
                ext = "cpp" if f["src"].endswith((".cpp", ".cp")) else "c"
                md += [f"```{ext}", *body, "```", ""]
    Path(a.md).write_text("\n".join(md) + "\n")
    print(f"wrote {a.md}", file=sys.stderr)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("index")
    f = sub.add_parser("find")
    f.add_argument("-e", action="append", default=[], help="pattern line (repeatable)")
    f.add_argument("-f", help="pattern file")
    lk = sub.add_parser("like")
    lk.add_argument("unit"); lk.add_argument("fn")
    lk.add_argument("--from", dest="frm", help="window start: offset in fn or absolute address")
    lk.add_argument("--to", help="window end (exclusive)")
    lk.add_argument("--loose", action="store_true", help="immediates/offsets match anything")
    lk.add_argument("--keep-syms", action="store_true", help="symbols must match by name")
    lk.add_argument("--sub", type=int, default=6, help="when nothing matches the whole window, "
                    "rank functions by shared sub-windows of this length (0 = off)")
    sm = sub.add_parser("similar", help="matched functions sharing the most 5-instruction shapes")
    sm.add_argument("unit"); sm.add_argument("fn")
    sm.add_argument("--from", dest="frm"); sm.add_argument("--to")
    sm.add_argument("-n", type=int, default=5, help="window length")
    idm = sub.add_parser("idioms")
    idm.add_argument("--md"); idm.add_argument("--json")
    idm.add_argument("--examples", type=int, default=1)
    for p in (f, lk, idm, sm):
        p.add_argument("--max-lines", type=int, default=40)
    for p in (f, lk, sm):
        p.add_argument("--src", action="store_true", help="print the function's source")
        p.add_argument("--limit", type=int, default=15)
        p.add_argument("--gap", type=int, default=6)
        p.add_argument("--exact-regs", action="store_true")
    a = ap.parse_args()
    if a.cmd == "index":
        build_index()
        return
    fns = load_index()
    if a.cmd == "find":
        lines = list(a.e)
        if a.f:
            lines += Path(a.f).read_text().splitlines()
        if not lines:
            sys.exit("no pattern (-e/-f)")
        pat = Pat(lines, gap=a.gap, exact_regs=a.exact_regs)
        hits = search(fns, pat)
        show(hits[: a.limit], a.src, max_lines=a.max_lines, total=len(hits))
    elif a.cmd == "like":
        cmd_like(a, fns)
    elif a.cmd == "similar":
        cmd_similar(a, fns)
    elif a.cmd == "idioms":
        cmd_idioms(a, fns)


if __name__ == "__main__":
    main()
