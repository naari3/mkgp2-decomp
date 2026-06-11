#!/usr/bin/env python3
# Phase 2f allocator-order probe driver.
# Compile a probe TU with CW 1.3.2 (production flags), disasm with dtk, and for
# each fn print, in instruction order, the `mr rArg, rSrc` moves feeding the
# sink call args plus any `mr`/`stw` that reveal web homes. The mapping
# arg-slot(r3,r4,..) -> source reg is the web's physical home.
import re
import subprocess
import sys
import os

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")
CC = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")
HERE = os.path.dirname(os.path.abspath(__file__))

# Production flags (match game_extab TU; same set probe.py uses).
BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]


def disasm(src, extra=None):
    flags = list(BASE_FLAGS) + (extra or [])
    obj = os.path.join(HERE, "alloc_out.o")
    asm = os.path.join(HERE, "alloc_out.s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    r = subprocess.run([CC] + flags + ["-c", src, "-o", obj],
                       capture_output=True, text=True, cwd=HERE, timeout=60)
    if r.returncode != 0 or not os.path.exists(obj):
        return None, (r.stdout + r.stderr)
    r2 = subprocess.run([DTK, "elf", "disasm", obj, asm],
                        capture_output=True, text=True, cwd=HERE, timeout=60)
    if r2.returncode != 0:
        return None, (r2.stdout + r2.stderr)
    with open(asm) as f:
        return f.read(), None


def fn_blocks(asm):
    out = {}
    for m in re.finditer(r"\.fn (\w+), \w+(.*?)\.endfn", asm, re.S):
        out[m.group(1)] = m.group(2)
    return out


def insns(body):
    res = []
    for line in body.splitlines():
        line = line.strip()
        im = re.match(r"^/\*.*?\*/\s+(\S+)\s+(.*)$", line)
        if im:
            res.append((im.group(1), im.group(2).strip()))
        else:
            im2 = re.match(r"^/\*.*?\*/\s+(\S+)\s*$", line)
            if im2:
                res.append((im2.group(1), ""))
    return res


def summarize(name, body):
    ins = insns(body)
    # collect the mr moves into argument registers r3..r10 right before a bl
    arg_map = {}  # argreg -> srcreg, last write wins before the bl
    lines = []
    saw_bl = False
    for mn, ops in ins:
        if mn == "mr":
            m = re.match(r"r(\d+), r(\d+)", ops)
            if m:
                dst, srcr = int(m.group(1)), int(m.group(2))
                if 3 <= dst <= 10 and not saw_bl:
                    arg_map[dst] = srcr
        if mn == "bl":
            saw_bl = True
        lines.append(f"{mn} {ops}".strip())
    argstr = " ".join(f"r{a}<-r{arg_map[a]}" for a in sorted(arg_map))
    return argstr, lines


def main():
    src = sys.argv[1] if len(sys.argv) > 1 else os.path.join(HERE, "alloc_gpr.c")
    extra = sys.argv[2:]
    asm, err = disasm(src, extra)
    if asm is None:
        print("COMPILE/DISASM FAIL:\n" + (err or ""))
        return
    for name, body in fn_blocks(asm).items():
        argstr, lines = summarize(name, body)
        print(f"### {name}")
        print(f"    arg homes: {argstr}")
        for l in lines:
            print("      " + l)
        print()


if __name__ == "__main__":
    main()
