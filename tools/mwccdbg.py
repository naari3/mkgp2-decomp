#!/usr/bin/env python3
"""Register-allocation explainer built on cadmic/mwcc-debugger.

mwcc-debugger (https://github.com/cadmic/mwcc-debugger, not vendored: it has no
licence file) runs mwcceppc.exe under encounter's retrowin32 fork with a gdb
stub and dumps the compiler's internal state for ONE function: frontend AST,
backend PCode after every pass (virtual registers r32+/f32+), and the
register colouring order (regalloc-{gpr,fpr}-pass-N-assigned.txt).

This wrapper:
  1. takes the TU's exact production command line from `ninja -t commands`,
     swaps the compiler for the nearest one the debugger supports
     (GC/1.3..2.7 -> GC/2.6, GC/1.0..1.2.5n -> GC/1.1) and adds `-sym on`;
  2. runs the debugger (about 7 s per function);
  3. aligns the PCode with our object and the TARGET object instruction by
     instruction (the diff must be register-only) and reports, in colouring
     order, every virtual register whose machine register differs from the
     target, plus which earlier-coloured neighbour already holds the wanted
     register. The first row marked `<-- first` is where to start: the
     colouring is greedy, so everything after it can be a knock-on effect.

Setup (once per container, about 4 minutes):
    bash /mnt/project-files/setup/mwccdbg/install.sh
which builds retrowin32 and clones mwcc-debugger into build/mwccdbg/.

Usage:
    python3 tools/mwccdbg.py game/dtor_801F8214 fn_801F8404
    python3 tools/mwccdbg.py game/dtor_801F8214 fn_801F8404 --class fpr --all
Dumps land in build/mwccdbg/out/<fn>/ (the backend-*.txt files are the
readable PCode; backend-11-before-regalloc shows each virtual register's
defining instruction and source line).

Only one run at a time: the debugger uses the fixed gdb port 9001.
"""
from __future__ import annotations

import argparse
import os
import re
import shlex
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DBG_DIR = ROOT / "build" / "mwccdbg"
EXE = ".exe" if os.name == "nt" else ""
OBJDUMP = ROOT / "build" / "binutils" / f"powerpc-eabi-objdump{EXE}"
# Native mode (default on Windows): gdb runs mwcceppc.exe directly through
# tools/mwccdbg_native.py instead of retrowin32's gdb stub. Needs a 32-bit
# x86 gdb with Python (MSYS2: pacman -S mingw-w64-i686-gdb), path in
# MWCCDBG_GDB or on PATH. No fixed gdb port, so runs can go in parallel.
NATIVE = os.environ.get("MWCCDBG_NATIVE", "1" if os.name == "nt" else "0") == "1"
GDB = os.environ.get("MWCCDBG_GDB", "gdb")
VERSION = "GNLJ82"

TO_SUPPORTED = {
    **{v: "2.6" for v in ("1.3", "1.3.2", "1.3.2r", "2.0", "2.0p1", "2.5", "2.6", "2.7")},
    **{v: "1.1" for v in ("1.0", "1.1", "1.1p1", "1.2.5", "1.2.5e", "1.2.5n")},
}

REG = re.compile(r"\b([rf])(\d+)\b")
PC_LINE = re.compile(r"^\s+(\d*)\s+([a-z][\w.+-]*)\s*(.*)$")


def sh(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, **kw)


def compile_command(unit: str, out_obj: Path) -> tuple[list[str], str]:
    obj = f"build/{VERSION}/src/{unit}.o"
    r = sh(["ninja", "-t", "commands", obj], cwd=ROOT)
    line = [l for l in r.stdout.splitlines() if "mwcceppc.exe" in l]
    if not line:
        sys.exit(f"no mwcceppc command for {obj} (is the unit name right?)")
    toks = shlex.split(line[-1].split("&&")[0].replace("\\", "/"))
    i = next(k for k, t in enumerate(toks) if t.endswith("mwcceppc.exe"))
    toks = toks[i:]
    m = re.search(r"GC/([^/]+)/mwcceppc\.exe", toks[0])
    orig = m.group(1)
    sup = TO_SUPPORTED.get(orig)
    if sup is None:
        sys.exit(f"compiler GC/{orig} has no supported stand-in")
    toks[0] = toks[0].replace(f"GC/{orig}/", f"GC/{sup}/")
    o = toks.index("-o")
    toks[o + 1] = str(out_obj)
    toks[o:o] = ["-sym", "on"]
    return toks, f"GC/{orig} -> GC/{sup}"


def objdump_fn(obj: Path, fn: str) -> list[str]:
    r = sh([str(OBJDUMP), "-d", "--no-show-raw-insn", str(obj)])
    out, on = [], False
    for l in r.stdout.splitlines():
        if re.match(rf"^[0-9a-f]+ <{re.escape(fn)}>:", l):
            on = True
            continue
        if on:
            if not l.strip():
                break
            if "\t" in l:
                out.append(l.split("\t", 1)[1].strip())
    return out


def regs(text: str, objdump=False) -> list[str]:
    # objdump prints a literal 0 base as "(0)", PCode prints it as r0: drop both.
    if objdump:
        text = re.sub(r"\(0\)", "", text)
    rs = [a + b for a, b in REG.findall(text)]
    return rs


def parse_pcode(path: Path) -> list[tuple[str, str, str]]:
    """[(line, opcode, operands)] in order, branches included."""
    res = []
    for l in path.read_text().splitlines():
        m = PC_LINE.match(l)
        if m and not l.lstrip().startswith(("B", ":")):
            res.append((m.group(1), m.group(2), m.group(3)))
    return res


def pc_regs(op: str, operands: str) -> list[str]:
    rs = regs(operands)
    # memory forms "lfs f33,r0,0(lbl)": r0 as base means "no base" (absolute/sda)
    if re.search(r",r0,[^,]*\(", "," + operands) and "r0" in rs:
        rs.remove("r0")
    return rs


def parse_assigned(path: Path):
    """Colouring order: [(vreg, phys, neighbours)]."""
    out = []
    cur = None
    for l in path.read_text().splitlines():
        m = re.match(r"^([rf]\d+) -> ([rf]\d+)", l)
        if m:
            cur = [m.group(1), m.group(2), []]
            out.append(cur)
            continue
        m = re.match(r"^\s+neighbors: \d+ \((.*)\)", l)
        if m and cur is not None:
            cur[2] = m.group(1).split()
    return out


def find(d: Path, prefix: str, last=False) -> Path | None:
    """Dump file by pass name; pass numbers differ per function (loop passes)."""
    c = sorted(d.glob(prefix + "*"))
    if not c:
        c = sorted(d.glob("backend-[0-9][0-9]-" + prefix + "*"))
    if not c:
        return None
    return c[-1] if last else c[0]


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("unit", help="unit path without extension, e.g. game/dtor_801F8214")
    ap.add_argument("fn", help="function symbol (mangled for C++)")
    ap.add_argument("--class", dest="rc", choices=["gpr", "fpr", "both"], default="both")
    ap.add_argument("--all", action="store_true", help="list every vreg, not only mismatches")
    ap.add_argument("--no-run", action="store_true", help="reuse existing dumps")
    ap.add_argument("--timeout", type=int, default=300)
    a = ap.parse_args()

    out = DBG_DIR / "out" / a.fn
    out.mkdir(parents=True, exist_ok=True)
    emu = DBG_DIR / "retrowin32"
    script = DBG_DIR / "mwcc-debugger" / "mwcc_debugger.py"
    if not a.no_run:
        if not script.exists() or (not NATIVE and not emu.exists()):
            sys.exit("install first: python3 tools/mwccdbg_install.py")
        cmd, note = compile_command(a.unit, out / "dbg.o")
        print(f"[mwccdbg] {note}{' (native gdb)' if NATIVE else ''}", file=sys.stderr)
        sh(["ninja", f"build/{VERSION}/src/{a.unit}.o"], cwd=ROOT)
        if not run_debugger(cmd, a.fn, out, a.timeout):
            sys.exit(f"debugger produced no regalloc dump; see {out}/run.log")

    rows, info = analyze_dumps(out, ROOT / f"build/{VERSION}/src/{a.unit}.o",
                               ROOT / f"build/{VERSION}/obj/{a.unit}.o", a.fn, a.rc)
    if rows is None:
        sys.exit(info)
    print(f"{a.fn}: {info['ours']} insns ours / {info['tgt']} target, {info['nstruct']} opcode diffs")
    for rc in (["gpr", "fpr"] if a.rc == "both" else [a.rc]):
        rr = [r for r in rows if r["class"] == rc]
        if not rr:
            continue
        print(f"\n== {rc.upper()} colouring order ({len(rr)} vregs; first = coloured first) ==")
        print(f"{'#':>3} {'vreg':>5} {'ours':>4} {'want':>4}  def (line, PCode)    blockers")
        first = True
        for r in rr:
            if not (a.all or r["bad"]):
                continue
            mark = "  <-- first" if r["bad"] and first else ""
            if r["bad"]:
                first = False
            print(f"{r['pos']:>3} {r['vreg']:>5} {r['ours']:>4} {r['want']:>4}  {r['where']:<40} {r['block']}{mark}")
        if first:
            print("   (no mismatching vregs in this class)")
    print(f"\ndumps: {out}")


def debugger_argv(cmd: list[str], fn: str, out: Path) -> list[str] | None:
    """argv that dumps fn's compiler state into out (native gdb or retrowin32)."""
    script = DBG_DIR / "mwcc-debugger" / "mwcc_debugger.py"
    if not script.exists():
        return None
    if NATIVE:
        setup = (f'py FUNCTION_NAME = "{fn}"; OUTPUT_DIR = "{Path(out).resolve().as_posix()}"; '
                 f'MWCCDBG_SCRIPT = "{script.resolve().as_posix()}"')
        exe = str((ROOT / cmd[0]).resolve()) if not os.path.isabs(cmd[0]) else cmd[0]
        return [GDB, "-batch", "-nx", "-ex", setup, "-x", str(ROOT / "tools" / "mwccdbg_native.py"),
                "--args", exe, *cmd[1:]]
    emu = DBG_DIR / f"retrowin32{EXE}"
    if not emu.exists():
        return None
    return [sys.executable, "-I", str(script), "-e", str(emu), "-a", shlex.join(cmd), fn, str(out)]


def run_debugger(cmd: list[str], fn: str, out: Path, timeout=300) -> bool:
    """Run mwcc-debugger with an explicit compiler command line; dumps into out."""
    argv = debugger_argv(cmd, fn, out)
    if not argv:
        return False
    out.mkdir(parents=True, exist_ok=True)
    for f in out.glob("*.txt"):
        f.unlink(missing_ok=True)
    r = sh(argv, cwd=ROOT, timeout=timeout)
    (out / "run.log").write_text(r.stdout + r.stderr)
    return find(out, "regalloc-") is not None


def analyze(cmd: list[str], fn: str, ours_obj, tgt_obj, out_dir, timeout=300, rc="both"):
    """Programmatic entry (tools/shapesweep.py): run the debugger on cmd and
    return the vreg rows (see analyze_dumps), or None."""
    out = Path(out_dir)
    if not run_debugger(cmd, fn, out, timeout):
        return None
    rows, _ = analyze_dumps(out, Path(ours_obj), Path(tgt_obj), fn, rc)
    return rows


def analyze_dumps(out: Path, ours_obj: Path, tgt_obj: Path, fn: str, rc="both"):
    """Rows [{class, pos, vreg, ours, want, bad, where, block}] in colouring
    order, plus info; (None, message) on failure."""
    if not find(out, "before-regalloc") or not find(out, "after-regalloc"):
        return None, f"debugger produced no regalloc dump; see {out}/run.log"
    pre = parse_pcode(find(out, "before-regalloc"))
    post = parse_pcode(find(out, "after-regalloc"))
    final = parse_pcode(find(out, "after-scheduling", last=True))

    # 11 -> 12: same order; regalloc only deletes coalesced copies (mr/fmr whose
    # operands got the same register).
    pair = []
    j = 0
    for ins in pre:
        if j < len(post) and post[j][1] == ins[1] and len(pc_regs(*post[j][1:])) == len(pc_regs(*ins[1:])):
            pair.append((ins, post[j]))
            j += 1
    # 12 -> 15: greedy exact-text match (scheduling only reorders).
    used = [False] * len(final)
    idx12 = []
    for _, p in pair:
        key = (p[1], p[2])
        k = next((k for k, f in enumerate(final) if not used[k] and (f[1], f[2]) == key), None)
        if k is not None:
            used[k] = True
        idx12.append(k)

    # the debugger quits before the object is written, so our side comes from
    # the build tree (rebuilt above, so source edits are picked up).
    ours = objdump_fn(ours_obj, fn)
    tgt = objdump_fn(tgt_obj, fn)
    if not ours or not tgt:
        return None, "function not found in our or target object (build first)"
    if len(final) != len(ours):
        warn(f"[mwccdbg] warning: PCode has {len(final)} insns, our .o {len(ours)};"
              " GC stand-in may differ from the production compiler", file=sys.stderr)
    if len(ours) != len(tgt):
        warn(f"[mwccdbg] warning: ours {len(ours)} vs target {len(tgt)} insns;"
              " mapping is only meaningful for register-only diffs", file=sys.stderr)
    nstruct = sum(1 for o, t in zip(ours, tgt) if o.split()[0] != t.split()[0])

    # per vreg: phys reg (ours) and the set of target regs at the same operand slots
    want: dict[str, dict[str, int]] = {}
    where: dict[str, str] = {}
    for (pv, pp), k in zip(pair, idx12):
        if k is None or k >= len(ours) or k >= len(tgt):
            continue
        vr, pr = pc_regs(*pv[1:]), pc_regs(*pp[1:])
        orr, tr = regs(ours[k], True), regs(tgt[k], True)
        if len(orr) != len(tr) or orr != pr:
            continue
        for v, p, t in zip(vr, pr, tr):
            if int(v[1:]) < 32:
                continue
            want.setdefault(v, {}).setdefault(t, 0)
            want[v][t] += 1
            where.setdefault(v, f"{pv[0]:>4}  {pv[1]} {pv[2]}")

    rows = []
    for c in (["gpr", "fpr"] if rc == "both" else [rc]):
        f = find(out, f"regalloc-{c}-pass-1-assigned")
        if not f:
            continue
        order = parse_assigned(f)
        phys = {v: p for v, p, _ in order}
        pos = {v: i for i, (v, _, _) in enumerate(order)}
        for n, (v, p, nb) in enumerate(order):
            w = want.get(v)
            wv = max(w, key=w.get) if w else "?"
            bad = w is not None and wv != p
            block = ""
            if bad:
                hold = [x for x in nb if phys.get(x) == wv and pos[x] < n]
                block = ("taken by " + ",".join(hold)) if hold else f"{p} was lowest free here (target: {p} busy or coloured in another order)"
                if len(w) > 1:
                    block += f"  (target varies: {w})"
            rows.append({"class": c, "pos": n, "vreg": v, "ours": p, "want": wv, "bad": bad,
                         "where": where.get(v, ""), "block": block})
    return rows, {"ours": len(ours), "tgt": len(tgt), "nstruct": nstruct}


def warn(msg, **_):
    print(msg, file=sys.stderr)


if __name__ == "__main__":
    main()
