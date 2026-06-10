#!/usr/bin/env python3
# Probe driver for class-1 branch-over-branch bool materialization.
# For each (compiler, flags, prelude) combo: compile tmp_min.c, disasm with dtk,
# classify each probe fn as TARGET / invert / branchless / other / CFAIL.
import re
import subprocess
import sys
import os

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
WT = os.path.join(ROOT, ".worktrees", "batch_research_class1_phase0", "tmp_probe")
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")
SRC = os.path.join(WT, "tmp_min.c")

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]

def classify(asm_text):
    # split into .fn blocks
    out = {}
    for m in re.finditer(r"\.fn (\w+), global(.*?)\.endfn", asm_text, re.S):
        name, body = m.group(1), m.group(2)
        # build token stream: labels and mnemonics(+first op)
        toks = []
        for line in body.splitlines():
            line = line.strip()
            lm = re.match(r"^(\.L_\w+):", line)
            if lm:
                toks.append(("label", lm.group(1)))
                continue
            im = re.match(r"^/\*.*?\*/\s+(\S+)\s*(.*)$", line)
            if im:
                toks.append(("insn", im.group(1) + " " + im.group(2)))
        verdict = "other"
        for i in range(len(toks)):
            k, v = toks[i]
            if k != "insn":
                continue
            mn = v.split()[0]
            # TARGET: bne L1 ; b L2 ; L1: ; li rX,0x1 ; L2:
            if mn == "bne" and i + 4 < len(toks):
                l1 = v.split()[1]
                if (toks[i+1][0] == "insn" and toks[i+1][1].split()[0] == "b"
                        and toks[i+2] == ("label", l1)
                        and toks[i+3][0] == "insn"
                        and re.match(r"li r\d+, 0x1$", toks[i+3][1])):
                    l2 = toks[i+1][1].split()[1]
                    if toks[i+4] == ("label", l2):
                        verdict = "TARGET"
                        break
            # invert: beq L2 ; li rX,0x1 ; L2:
            if mn == "beq" and i + 2 < len(toks):
                l2 = v.split()[1]
                if (toks[i+1][0] == "insn"
                        and re.match(r"li r\d+, 0x1$", toks[i+1][1])
                        and toks[i+2] == ("label", l2)):
                    if verdict == "other":
                        verdict = "invert"
            if mn == "subfe" and verdict == "other":
                verdict = "branchless"
        out[name] = verdict
    return out

def probe(tag, cc, extra_flags=None, prelude=None, src=SRC, flags=None):
    flags = list(flags if flags is not None else BASE_FLAGS)
    if extra_flags:
        flags += extra_flags
    use_src = src
    if prelude is not None:
        use_src = os.path.join(WT, "tmp_var.c")
        with open(src) as f:
            base = f.read()
        with open(use_src, "w") as f:
            f.write(prelude + "\n" + base)
    obj = os.path.join(WT, "tmp_out.o")
    asm = os.path.join(WT, "tmp_out.s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    r = subprocess.run([cc] + flags + ["-c", use_src, "-o", obj],
                       capture_output=True, text=True, cwd=WT, timeout=60)
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
    summary = " ".join(f"{k}={v}" for k, v in sorted(res.items()))
    hit = "HIT" if any(v == "TARGET" for v in res.values()) else "-"
    line = f"{tag}\t{hit}\t{summary}"
    print(line, flush=True)
    return line

if __name__ == "__main__":
    cc132 = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")
    probe("baseline_1.3.2", cc132)
