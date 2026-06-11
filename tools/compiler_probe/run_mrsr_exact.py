#!/usr/bin/env python3
# Exact-diff runner: compile a probe TU, normalize each probe fn's insn list,
# diff against target_getmaxspeed.txt (sda21 symbol names normalized).
import os
import re
import subprocess
import sys

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
HERE = os.path.dirname(os.path.abspath(__file__))
WT = os.path.join(HERE, "tmp_mrsr")
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]

SYMMAP = {"F_ZERO": "lbl_806D26EC", "F_ONE": "lbl_806D26FC",
          "F_CAP": "lbl_806D276C", "F_MUL": "lbl_806D2770"}


def norm_probe(body):
    out = []
    for line in body.splitlines():
        line = line.strip()
        if re.match(r"^\.L_\w+:", line):
            out.append("LABEL")
            continue
        im = re.match(r"^/\*.*?\*/\s+(\S+)\s*(.*)$", line)
        if not im:
            continue
        mn, ops = im.group(1), im.group(2)
        ops = re.sub(r"\.L_\w+", "L", ops)
        for k, v in SYMMAP.items():
            ops = ops.replace(k + "@sda21(r0)", v + "(r2)")
        out.append((mn + " " + ops).strip())
    return out


def load_target(path):
    return [l.rstrip("\n") for l in open(path) if l.strip()]


def run(src, target_file, fn_filter=None, extra_flags=None, tag=""):
    flags = list(BASE_FLAGS) + (extra_flags or [])
    os.makedirs(WT, exist_ok=True)
    obj = os.path.join(WT, "exact_out.o")
    asm = os.path.join(WT, "exact_out.s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    cc = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")
    r = subprocess.run([cc] + flags + ["-c", src, "-o", obj],
                       capture_output=True, text=True, cwd=WT, timeout=60)
    if r.returncode != 0:
        print(tag, "CFAIL", (r.stdout + r.stderr)[:300])
        return
    subprocess.run([DTK, "elf", "disasm", obj, asm], capture_output=True,
                   text=True, cwd=WT, timeout=60)
    target = load_target(target_file)
    t = open(asm).read()
    results = []
    for m in re.finditer(r"\.fn (\w+), global(.*?)\.endfn", t, re.S):
        name, body = m.group(1), m.group(2)
        if fn_filter and not fn_filter(name):
            continue
        got = norm_probe(body)
        ndiff = sum(1 for a, b in zip(got, target) if a != b)
        ndiff += abs(len(got) - len(target))
        results.append((ndiff, name, got))
    for ndiff, name, got in sorted(results):
        print(f"{tag}\t{name}\tdiff={ndiff}\tlen={len(got)}/{len(target)}")
        if 0 < ndiff <= 12:
            for k, (a, b) in enumerate(zip(got, target)):
                if a != b:
                    print(f"    [{k:3}] got: {a:40} want: {b}")
            if len(got) != len(target):
                print(f"    len mismatch tail got={got[len(target):]} want={target[len(got):]}")


if __name__ == "__main__":
    run(os.path.join(HERE, sys.argv[1]),
        os.path.join(HERE, sys.argv[2] if len(sys.argv) > 2 else "target_getmaxspeed.txt"),
        tag=sys.argv[1])
