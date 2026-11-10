#!/usr/bin/env python3
"""Provisional names for unnamed data symbols (`lbl_XXXXXXXX`).

    python3 tools/data_names.py plan [--section .data] [--limit N]   # print old -> new
    python3 tools/data_names.py census                              # docs/reports/data_names.md
    python3 tools/data_names.py apply [--section S] [--range LO-HI] [--limit N]
    python3 tools/data_names.py fixup [FILES]   # old lbl_ names in your work -> new names

Run `apply` right after a build of the same symbols.txt: the asm under
build/GNLJ82/asm must still carry the lbl_ names.  `apply` appends every
rename to tools/data_names_map.tsv; after rebasing work that still uses an
old name, `fixup` rewrites it.

Names come from who uses the object, read from the disassembly dtk writes
for every unit (build/GNLJ82/asm, so run a build first):

  vtable / RTTI   <Class>_vtable_<ADDR> / <Class>_RTTI_<ADDR>, the class a
                  TU already maps it to in tools/extab_user_renames.json
                  (not the mangled `__vt__...`: weak copies would clash)
  one function    <Function>_<kind>_<ADDR>      (kind: data, bss, rodata)
  one class       <Class>_<kind>_<ADDR>         (every user is Class::method)
  one unit        <Unit>_<kind>_<ADDR>          (unit name not fn_/anon_)
  pointed to by a named object only   <Object>_<kind>_<ADDR>

The address stays in the name, so names are unique and old notes can still
be followed.  Left alone: strings, compiler literal pools (targets of `@N`
renames), .sdata2/.sbss2 (float literals), objects used only by unnamed
`fn_` functions, and anything a file under an open unit-claim mentions
(build/open_claims.txt, one `game/Foo.c` per line).

`apply` renames the symbol in config/GNLJ82/symbols.txt and replaces the
whole word `lbl_XXXXXXXX` in every tracked text file except the append-only
board (docs/agents/).  Nothing in main.dol depends on a symbol name, so the
check is `ninja` -> main.dol OK with the same report totals.
"""
import argparse
import json
import os
import re
import subprocess
import sys
from collections import defaultdict, Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMS = os.path.join(ROOT, "config/GNLJ82/symbols.txt")
ASM = os.path.join(ROOT, "build/GNLJ82/asm")
RENAMES = os.path.join(ROOT, "tools/extab_user_renames.json")
MAP = os.path.join(ROOT, "tools/data_names_map.tsv")

SYM_RE = re.compile(r"^(\S+) = (\.\w+):0x([0-9A-Fa-f]+); // (.*)$")
LBL_RE = re.compile(r"\blbl_[0-9A-F]{8}\b")
KIND = {".data": "data", ".sdata": "data", ".bss": "bss", ".sbss": "bss",
        ".rodata": "rodata"}
STRING_DATA = {"string", "wstring", "string_table", "wstring_table", "sjis", "sjis_table"}
UNNAMED = re.compile(r"^(fn_|lbl_|anon_|auto_|@|func_|sub_|jumptable_|zz_|\.)")


def load_symbols():
    syms = {}
    order = []
    with open(SYMS) as f:
        for line in f:
            m = SYM_RE.match(line.rstrip("\n"))
            if not m:
                continue
            name, sect, addr, attrs = m.groups()
            syms[name] = {"sect": sect, "addr": int(addr, 16), "attrs": attrs}
            order.append(name)
    return syms, order


OWNER = {}   # object -> unit whose asm defines it


def xref():
    """lbl -> {"fn": set(function names), "obj": set(object names), "unit": set(units)}"""
    refs = defaultdict(lambda: {"fn": set(), "obj": set(), "unit": set()})
    for dp, _, fns in os.walk(ASM):
        for fn in fns:
            if not fn.endswith(".s"):
                continue
            path = os.path.join(dp, fn)
            unit = os.path.splitext(os.path.relpath(path, ASM))[0]
            cur, curkind = None, None
            with open(path, encoding="latin-1") as f:
                for line in f:
                    if line.startswith(".fn "):
                        cur, curkind = line[4:].split(",")[0].strip().strip('"'), "fn"
                        continue
                    if line.startswith(".obj "):
                        cur, curkind = line[5:].split(",")[0].strip().strip('"'), "obj"
                        OWNER[cur] = unit
                        continue
                    if line.startswith((".endfn", ".endobj")):
                        cur = None
                        continue
                    if cur is None or "lbl_" not in line:
                        continue
                    for l in LBL_RE.findall(line):
                        if l == cur:
                            continue
                        refs[l][curkind].add(cur)
                        refs[l]["unit"].add(unit)
    return refs


def readable(fn):
    """C name or a short form of a mangled C++ name; None when unnamed."""
    if UNNAMED.match(fn):
        return None
    m = re.match(r"^(__ct|__dt|\w+?)__(\d+)(\w+)$", fn)
    if m and not fn.startswith("__") or (m and m.group(1) in ("__ct", "__dt")):
        meth, n, rest = m.group(1), int(m.group(2)), m.group(3)
        cls = rest[:n]
        if len(cls) == n and re.fullmatch(r"[A-Za-z_]\w*", cls):
            meth = {"__ct": "ct", "__dt": "dt"}.get(meth, meth)
            return f"{cls}_{meth}", cls
    if fn.startswith("__") or not re.fullmatch(r"[A-Za-z_]\w*", fn):
        return None
    return fn, None


def literal_targets():
    with open(RENAMES) as f:
        text = f.read()
    return set(re.findall(r'"@\d+"\s*:\s*"(lbl_[0-9A-F]{8})"', text))


def vtable_names():
    """lbl -> mangled __vt__/__RTTI__ name when every TU agrees."""
    with open(RENAMES) as f:
        text = f.read()
    seen = defaultdict(Counter)
    for k, v in re.findall(r'"((?:__vt__|__RTTI__)\w+)"\s*:\s*"(lbl_[0-9A-F]{8})"', text):
        seen[v][k] += 1
    out = {}
    for v, c in seen.items():
        if len(c) != 1:
            continue
        m = re.match(r"__(vt|RTTI)__(\d+)(\w+)$", c.most_common(1)[0][0])
        if not m or len(m.group(3)) != int(m.group(2)):
            continue
        # not the mangled name itself: a TU that emits its own weak copy of
        # the vtable would then define it twice
        kind = "vtable" if m.group(1) == "vt" else "RTTI"
        out[v] = f"{m.group(3)}_{kind}_{v[4:]}"
    return out


def claimed_words():
    p = os.path.join(ROOT, "build/open_claims.txt")
    words = set()
    if not os.path.exists(p):
        return words
    for x in open(p):
        x = x.strip()
        if not x:
            continue
        for ext in ("",):
            path = os.path.join(ROOT, "src", x + ext)
            if os.path.exists(path):
                words |= set(LBL_RE.findall(open(path, encoding="latin-1").read()))
    return words


def plan(args):
    syms, _ = load_symbols()
    refs = xref()
    lits = literal_targets()
    vts = vtable_names()
    claimed = claimed_words()
    taken = set(syms)
    out = {}
    why = Counter()
    for name, s in syms.items():
        if not name.startswith("lbl_") or "type:object" not in s["attrs"]:
            continue
        if args.section and s["sect"] not in args.section:
            continue
        if args.range:
            lo, hi = args.range
            if not lo <= s["addr"] < hi:
                continue
        if name in claimed:
            why["claimed"] += 1
            continue
        if name in vts and vts[name] not in taken:
            out[name] = vts[name]
            taken.add(vts[name])
            why["vtable/RTTI"] += 1
            continue
        kind = KIND.get(s["sect"])
        if kind is None:
            why["section " + s["sect"]] += 1
            continue
        dm = re.search(r"data:(\w+)", s["attrs"])
        if dm and dm.group(1) in STRING_DATA:
            why["string"] += 1
            continue
        if name in lits:
            why["compiler literal"] += 1
            continue
        r = refs.get(name)
        if not r:
            why["no reference"] += 1
            continue
        base = None
        fns = [readable(f) for f in r["fn"]]
        if r["fn"] and all(fns):
            if len(fns) == 1:
                base, how = fns[0][0], "one function"
            else:
                cls = {c for _, c in fns}
                if len(cls) == 1 and None not in cls:
                    base, how = cls.pop(), "one class"
        if base is None and len(r["unit"]) == 1:
            u = os.path.basename(next(iter(r["unit"])))
            # a data-only unit (src/game/autodata) is named after an address: no name to give
            if not UNNAMED.match(u) and re.fullmatch(r"[A-Za-z_]\w*", u) \
                    and not u.startswith(("data_", "rodata_", "sdata_", "sdata2_", "bss_", "sbss_")):
                base, how = u, "one unit"
        if base is None and len(fns) > 1 and all(fns):
            # several named functions: their common name prefix (whole words)
            pre = os.path.commonprefix([f[0] for f in fns])
            pre = pre[:pre.rfind("_")] if "_" in pre and not pre.endswith("_") else pre.rstrip("_")
            if len(pre) >= 4 and re.fullmatch(r"[A-Za-z_]\w*", pre) and not UNNAMED.match(pre):
                base, how = pre, "common prefix of its functions"
        if base is None and name in OWNER:
            u = os.path.basename(OWNER[name])
            if not UNNAMED.match(u) and not u.startswith(("data_", "rodata_", "sdata_", "bss_", "sbss_"))\
                    and re.fullmatch(r"[A-Za-z_]\w*", u):
                base, how = u, "unit that defines it"
        if base is None and not r["fn"] and len(r["obj"]) == 1:
            o = next(iter(r["obj"]))
            o = re.sub(r"_(data|bss|rodata|vtable|RTTI)_[0-9A-F]{8}$", "", o)
            if not UNNAMED.match(o) and re.fullmatch(r"[A-Za-z_]\w*", o):
                base, how = o, "pointed to by a named object"
        if base is None:
            why["no single named user"] += 1
            continue
        new = f"{base}_{kind}_{name[4:]}"
        if new in taken:
            why["name taken"] += 1
            continue
        taken.add(new)
        out[name] = new
        why[how] += 1
    if args.limit:
        out = dict(sorted(out.items(), key=lambda kv: syms[kv[0]]["addr"])[:args.limit])
    return out, why


def tracked_files():
    out = subprocess.run(["git", "ls-files"], cwd=ROOT, capture_output=True, text=True,
                         check=True).stdout.split("\n")
    skip_ext = (".png", ".jpg", ".zip", ".iso", ".bin", ".o", ".a", ".dol", ".elf")
    return [f for f in out if f and not f.startswith("docs/agents/")
            and not f.endswith(skip_ext) and os.path.join(ROOT, f) not in (MAP, MANUAL)]


MANUAL = os.path.join(ROOT, "tools", "data_names_manual.tsv")


def manual(args):
    """Names a person chose by reading the users: tools/data_names_manual.tsv
    (old <tab> new <tab> why).  Lines whose old name is gone are done."""
    syms, _ = load_symbols()
    ren = {}
    for line in open(MANUAL):
        if line.startswith("#") or "\t" not in line:
            continue
        old, new = line.rstrip("\n").split("\t")[:2]
        if old in syms and new not in syms and re.fullmatch(r"[A-Za-z_]\w*", new):
            ren[old] = new
        elif old in syms:
            print(f"skip {old} -> {new}: name taken or not an identifier")
    return ren, Counter({"chosen by reading the users (data_names_manual.tsv)": len(ren)})


def apply(args):
    ren, why = manual(args) if getattr(args, "manual", False) else plan(args)
    if not ren:
        print("nothing to rename")
        return
    pat = re.compile(r"\blbl_[0-9A-F]{8}\b")
    nfiles = 0
    for f in tracked_files():
        p = os.path.join(ROOT, f)
        if not os.path.isfile(p):
            continue
        with open(p, "rb") as fh:
            data = fh.read()
        if b"lbl_" not in data:
            continue
        text = data.decode("latin-1")
        new = pat.sub(lambda m: ren.get(m.group(0), m.group(0)), text)
        if new != text:
            with open(p, "wb") as fh:
                fh.write(new.encode("latin-1"))
            nfiles += 1
    old = load_map()
    old.update(ren)
    with open(MAP, "w") as fh:
        fh.write("# old\tnew  (tools/data_names.py; `fixup` rewrites old names in your files)\n")
        for k in sorted(old):
            fh.write(f"{k}\t{old[k]}\n")
    print(f"renamed {len(ren)} symbols in {nfiles} files")
    for k, v in why.most_common():
        print(f"  {v:6} {k}")


def load_map():
    m = {}
    if os.path.exists(MAP):
        for line in open(MAP):
            if line.startswith("#") or "\t" not in line:
                continue
            a, b = line.rstrip("\n").split("\t")
            m[a] = b
    return m


def fixup(args):
    """Rewrite old lbl_ names (from tools/data_names_map.tsv) in the given
    files, or in every tracked file that differs from origin/main plus
    untracked sources: run it after rebasing work that still uses old names."""
    ren = load_map()
    files = args.files
    if not files:
        out = subprocess.run(["git", "diff", "--name-only", "origin/main"], cwd=ROOT,
                             capture_output=True, text=True).stdout.split()
        out += subprocess.run(["git", "ls-files", "--others", "--exclude-standard"], cwd=ROOT,
                              capture_output=True, text=True).stdout.split()
        files = out
    files = [f for f in files if not f.startswith("docs/agents/")
             and os.path.normpath(os.path.join(ROOT, f)) != MAP]
    pat = re.compile(r"\blbl_[0-9A-F]{8}\b")
    for f in files:
        p = os.path.join(ROOT, f)
        if not os.path.isfile(p):
            continue
        text = open(p, "rb").read().decode("latin-1")
        new, n = pat.subn(lambda m: ren.get(m.group(0), m.group(0)), text)
        if new != text:
            open(p, "wb").write(new.encode("latin-1"))
            print(f"{f}: updated")


def census(args):
    args.section = None
    args.range = None
    args.limit = 0
    ren, why = plan(args)
    syms, _ = load_symbols()
    total = sum(1 for n, s in syms.items() if "type:object" in s["attrs"])
    unnamed = sum(1 for n, s in syms.items() if "type:object" in s["attrs"] and n.startswith("lbl_"))
    lines = ["# Unnamed data symbols (tools/data_names.py census)", "",
             "Regenerate with `python3 tools/data_names.py census` after a build.", "",
             "| Item | Count |", "|---|---|",
             f"| data objects in symbols.txt | {total} |",
             f"| still `lbl_` | {unnamed} |",
             f"| `apply` would name now | {len(ren)} |", "",
             "| Outcome for each `lbl_` object | Count |", "|---|---|"]
    for k, v in why.most_common():
        lines.append(f"| {k} | {v} |")
    with open(os.path.join(ROOT, "docs/reports/data_names.md"), "w") as f:
        f.write("\n".join(lines) + "\n")
    print("\n".join(lines))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("fixup")
    p.add_argument("files", nargs="*")
    p.set_defaults(fn=fixup)
    for name, fn in (("plan", None), ("apply", apply), ("census", census)):
        p = sub.add_parser(name)
        p.add_argument("--section", action="append")
        p.add_argument("--range", type=lambda s: tuple(int(x, 16) for x in s.split("-")))
        p.add_argument("--limit", type=int, default=0)
        p.set_defaults(fn=fn)
        if name == "apply":
            p.add_argument("--manual", action="store_true",
                           help="apply tools/data_names_manual.tsv instead of the rules")
    args = ap.parse_args()
    if args.cmd == "plan":
        ren, why = plan(args)
        for k, v in ren.items():
            print(k, v)
        for k, v in why.most_common():
            print(f"# {v:6} {k}", file=sys.stderr)
        return
    args.fn(args)


if __name__ == "__main__":
    main()
