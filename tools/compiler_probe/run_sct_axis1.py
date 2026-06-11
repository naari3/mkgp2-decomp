#!/usr/bin/env python3
# Phase 2d: ScopedTimer inline-dtor subi/lwz pair order probe.
# Classifier: for each fn, locate `subi rX, rY, 0x217d` and the nearest
# r1-based lwz within a +/-5 insn window; TARGET = subi before lwz.
import os
import re
import subprocess
import sys

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
WT = os.path.join(ROOT, ".worktrees", "batch_research_scopedtimer_phase2d")
PROBE = os.path.join(WT, "tools", "compiler_probe")
TMP = os.path.join(WT, "tmp_probe")
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")
CC132 = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "off", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]


def fn_insns(asm_text):
    out = {}
    for m in re.finditer(r"\.fn (\w+), (?:global|local)(.*?)\.endfn", asm_text, re.S):
        name, body = m.group(1), m.group(2)
        insns = []
        for line in body.splitlines():
            im = re.match(r"^/\*.*?\*/\s+(\S+)\s*(.*)$", line.strip())
            if im:
                insns.append((im.group(1) + " " + im.group(2)).strip())
        out[name] = insns
    return out


def classify_fn(insns):
    subi_i = None
    for i, v in enumerate(insns):
        if re.match(r"subi r\d+, r\d+, 0x217d$", v):
            subi_i = i
            break
    if subi_i is None:
        return "NOSUBI", None
    lwz_i = None
    best = 99
    for j in range(max(0, subi_i - 5), min(len(insns), subi_i + 6)):
        if re.match(r"lwz r\d+, 0x[0-9a-f]+\(r1\)$", insns[j]):
            d = abs(j - subi_i)
            if d < best:
                best = d
                lwz_i = j
    if lwz_i is None:
        return "NOLWZ", subi_i
    return ("TARGET" if subi_i < lwz_i else "miss"), (subi_i, lwz_i)


def window(insns, subi_i, n=6):
    lo = max(0, subi_i - n)
    return insns[lo:subi_i + n]


def probe(tag, src, cc=CC132, extra_flags=None, dump=False):
    flags = list(BASE_FLAGS)
    if extra_flags:
        flags += extra_flags
    base = os.path.splitext(os.path.basename(src))[0]
    obj = os.path.join(TMP, base + ".o")
    asm = os.path.join(TMP, base + ".s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    r = subprocess.run([cc] + flags + ["-c", src, "-o", obj],
                       capture_output=True, text=True, cwd=TMP, timeout=60)
    if r.returncode != 0 or not os.path.exists(obj):
        msg = (r.stdout + r.stderr).replace("\n", " | ")[:200]
        line = f"{tag}\tCFAIL\t{msg}"
        print(line, flush=True)
        return [line]
    r2 = subprocess.run([DTK, "elf", "disasm", obj, asm],
                        capture_output=True, text=True, cwd=TMP, timeout=60)
    if r2.returncode != 0:
        line = f"{tag}\tDFAIL\t{(r2.stdout + r2.stderr)[:200]}"
        print(line, flush=True)
        return [line]
    with open(asm) as f:
        fns = fn_insns(f.read())
    lines = []
    for name, insns in sorted(fns.items()):
        verdict, pos = classify_fn(insns)
        line = f"{tag}\t{name}\t{verdict}\t{pos}"
        print(line, flush=True)
        lines.append(line)
        if dump and verdict in ("TARGET", "miss"):
            for v in window(insns, pos[0]):
                print(f"      {v}", flush=True)
    return lines


if __name__ == "__main__":
    os.makedirs(TMP, exist_ok=True)
    dump = "--dump" in sys.argv
    results = probe("sct_min 1.3.2", os.path.join(PROBE, "sct_min.c"), dump=dump)
    with open(os.path.join(PROBE, "results_sct_axis1.tsv"), "w") as f:
        f.write("\n".join(results) + "\n")
