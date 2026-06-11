#!/usr/bin/env python3
# mr-SR-init probe driver (batch_research_mrsrinit_phase2c).
# Compiles mrsr_min.c per (compiler, flags) combo, disasms with dtk, classifies
# the loop preheader of every probe fn:
#   TARGET  : li rA,0 ... mr rB,rA   (single li-0, copy survives)
#   LI2     : two li *,0x0 in preheader (const-prop folded the copy)
#   LI1     : single li-0, no mr (no second IV in preheader)
#   SLWI    : preheader computes the init with a shift (SR init not folded)
#   STACK   : preheader touches the stack for the IVs (promotion failed)
#   CFAIL/DFAIL on tool errors.
# Also reports loop step shape: SR (addi +8 step present) or SHIFT (slwi in
# the loop condition/body path = no separate byte IV).
import os
import re
import subprocess
import sys

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
HERE = os.path.dirname(os.path.abspath(__file__))
WT = os.path.join(HERE, "tmp_mrsr")
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")
SRC = os.path.join(HERE, "mrsr_min.c")

# production flags for game/auto_ONKARTHIT_block.c (cflags_base with
# -Cpp_exceptions on override + extra -use_lmw_stmw on)
BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]


def parse_fns(asm_text):
    out = {}
    for m in re.finditer(r"\.fn (\w+), global(.*?)\.endfn", asm_text, re.S):
        name, body = m.group(1), m.group(2)
        insns = []
        for line in body.splitlines():
            line = line.strip()
            im = re.match(r"^/\*.*?\*/\s+(\S+)\s*(.*)$", line)
            if im:
                insns.append((im.group(1), im.group(2)))
            lm = re.match(r"^(\.L_\w+):", line)
            if lm:
                insns.append(("LABEL", lm.group(1)))
        out[name] = insns
    return out


def classify_fn(insns):
    # preheader = everything before the first unconditional `b` (rotated loop)
    pre = []
    for mn, ops in insns:
        if mn == "b":
            break
        pre.append((mn, ops))
    li0 = [(mn, ops) for mn, ops in pre if mn == "li" and ops.endswith(", 0x0")]
    mrs = [(mn, ops) for mn, ops in pre if mn == "mr"]
    slwis = [(mn, ops) for mn, ops in pre if mn in ("slwi", "rlwinm")]
    stack = [(mn, ops) for mn, ops in pre
             if mn in ("stw", "lwz") and "(r1)" in ops]
    # loop step shape: addi rX, rX, 0x8 anywhere = separate byte IV
    sr_step = any(mn == "addi" and re.match(r"(r\d+), \1, 0x8$", ops)
                  for mn, ops in insns)
    body_shift = any(mn in ("slwi", "rlwinm") for mn, ops in insns[len(pre):])

    verdict = "other"
    if stack:
        verdict = "STACK"
    elif li0 and mrs:
        li_regs = {ops.split(",")[0] for mn, ops in li0}
        for mn, ops in mrs:
            dst, src = [x.strip() for x in ops.split(",")]
            if src in li_regs:
                verdict = "TARGET" if len(li0) == 1 else "TARGETli2"
                break
        else:
            verdict = "mr-other"
    elif len(li0) >= 2:
        verdict = "LI2"
    elif slwis:
        verdict = "SLWI"
    elif len(li0) == 1:
        verdict = "LI1"
    step = "SR" if sr_step else ("SHIFT" if body_shift else "?")
    prestr = ";".join(f"{mn} {ops}" for mn, ops in pre[:7])
    return verdict, step, prestr


def probe(tag, cc, extra_flags=None, flags=None, src=SRC, fn_filter=None):
    flags = list(flags if flags is not None else BASE_FLAGS)
    if extra_flags:
        flags += extra_flags
    os.makedirs(WT, exist_ok=True)
    obj = os.path.join(WT, "mrsr_out.o")
    asm = os.path.join(WT, "mrsr_out.s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    r = subprocess.run([cc] + flags + ["-c", src, "-o", obj],
                       capture_output=True, text=True, cwd=WT, timeout=60)
    if r.returncode != 0 or not os.path.exists(obj):
        msg = (r.stdout + r.stderr).replace("\n", " | ")[:160]
        line = f"{tag}\tCFAIL\t{msg}"
        print(line, flush=True)
        return [line]
    r2 = subprocess.run([DTK, "elf", "disasm", obj, asm],
                        capture_output=True, text=True, cwd=WT, timeout=60)
    if r2.returncode != 0:
        line = f"{tag}\tDFAIL\t{(r2.stdout + r2.stderr)[:160]}"
        print(line, flush=True)
        return [line]
    with open(asm) as f:
        fns = parse_fns(f.read())
    lines = []
    for name in sorted(fns):
        if fn_filter and not fn_filter(name):
            continue
        verdict, step, prestr = classify_fn(fns[name])
        line = f"{tag}\t{name}\t{verdict}\t{step}\t{prestr}"
        print(line, flush=True)
        lines.append(line)
    return lines


if __name__ == "__main__":
    cc132 = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")
    all_lines = probe("GC/1.3.2 prod", cc132)
    with open(os.path.join(HERE, "results_mrsr_axis1.tsv"), "w") as f:
        f.write("\n".join(all_lines) + "\n")
