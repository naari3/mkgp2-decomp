#!/usr/bin/env python3
# Probe driver for fp-scratch register NUMBERING direction (Phase 2a).
# For each (compiler, flags, prelude) combo: compile fpnum_min.c, disasm with
# dtk, and per fn classify the main lfs load block as
#   <offset-dir><reg-dir>  with a=ascending d=descending m=mixed ?=too-short
# TARGET signature (for the *_asc fns and c16_pipe): "ad" = offsets ascending,
# registers DESCENDING (later-first-use -> lower reg).
import re
import subprocess
import sys
import os

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
WT = os.path.join(ROOT, ".worktrees", "batch_research_fpnumbering_phase2a",
                  "tmp_probe")
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")
SRC = os.path.join(WT, "fpnum_min.c")

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]

# fns whose TARGET signature is "ad" (asc-def source forms)
ASC_FNS = ("c8_asc", "c4_asc", "c6_asc", "c2_asc", "c16_pipe")


def dirof(seq):
    if len(seq) < 2:
        return "?"
    if all(b > a for a, b in zip(seq, seq[1:])):
        return "a"
    if all(b < a for a, b in zip(seq, seq[1:])):
        return "d"
    return "m"


def classify(asm_text):
    out = {}
    for m in re.finditer(r"\.fn (\w+), global(.*?)\.endfn", asm_text, re.S):
        name, body = m.group(1), m.group(2)
        insns = []
        for line in body.splitlines():
            line = line.strip()
            im = re.match(r"^/\*.*?\*/\s+(\S+)\s*(.*)$", line)
            if im:
                insns.append((im.group(1), im.group(2)))
        # collect runs of consecutive lfs with parseable reg+offset
        runs = []
        cur = []
        for mn, args in insns:
            pm = re.match(r"f(\d+), (-?(?:0x[0-9a-fA-F]+|\d+))\(r\d+\)", args)
            if mn == "lfs" and pm:
                cur.append((int(pm.group(1)), int(pm.group(2), 0)))
            else:
                if len(cur) >= 2:
                    runs.append(cur)
                cur = []
        if len(cur) >= 2:
            runs.append(cur)
        if not runs:
            out[name] = ("??", "")
            continue
        block = max(runs, key=len)
        regs = [r for r, _ in block]
        offs = [o for _, o in block]
        verdict = dirof(offs) + dirof(regs)
        out[name] = (verdict, ",".join(str(r) for r in regs))
    return out


def probe(tag, cc, extra_flags=None, prelude=None, src=SRC, flags=None):
    flags = list(flags if flags is not None else BASE_FLAGS)
    if extra_flags:
        flags += extra_flags
    use_src = src
    if prelude is not None:
        use_src = os.path.join(WT, "fpnum_var.c")
        with open(src) as f:
            base = f.read()
        with open(use_src, "w") as f:
            f.write(prelude + "\n" + base)
    obj = os.path.join(WT, "tmp_out.o")
    asm = os.path.join(WT, "tmp_out.s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    try:
        r = subprocess.run([cc] + flags + ["-c", use_src, "-o", obj],
                           capture_output=True, text=True, cwd=WT, timeout=60)
    except Exception as e:
        line = f"{tag}\tCFAIL\t{e}"
        print(line, flush=True)
        return line
    if r.returncode != 0 or not os.path.exists(obj):
        msg = (r.stdout + r.stderr).replace("\n", " | ")[:160]
        line = f"{tag}\tCFAIL\t{msg}"
        print(line, flush=True)
        return line
    r2 = subprocess.run([DTK, "elf", "disasm", obj, asm],
                        capture_output=True, text=True, cwd=WT, timeout=60)
    if r2.returncode != 0:
        line = f"{tag}\tDFAIL\t{(r2.stdout + r2.stderr)[:160]}"
        print(line, flush=True)
        return line
    with open(asm) as f:
        res = classify(f.read())
    parts = []
    hit = "-"
    for k in sorted(res):
        v, regs = res[k]
        parts.append(f"{k}={v}[{regs}]")
        if k in ASC_FNS and v == "ad":
            hit = "HIT"
    line = f"{tag}\t{hit}\t" + " ".join(parts)
    print(line, flush=True)
    return line


if __name__ == "__main__":
    cc132 = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2",
                         "mwcceppc.exe")
    probe("baseline_1.3.2", cc132)
