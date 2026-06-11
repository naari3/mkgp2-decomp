"""Compile a standalone OnKartHit probe TU and compare its fn against the target.
Usage: python tmp/cpp_probe_run.py <src.c|src.cpp> <label> [--lang=c++] [--show=N]

Comparison is dtk-disasm based (both sides use the same formatter), so it works
for mangled C++ symbols too. Reports: GPR homes (self/victim/bus), difflib
similarity, per-row diff count, and the first N differing rows.
"""
import difflib
import io
import os
import re
import subprocess
import sys

MWCC = r"build\compilers\GC\1.3.2\mwcceppc.exe"
DTK = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp\build\tools\dtk.exe"
TARGET_OBJ = r"build/GNLJ82/obj/game/auto_ONKARTHIT_block.o"
TARGET_S = r"tmp/target_tu.s"

CFLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "off", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off", "-maxerrors", "1",
    "-nosyspath", "-RTTI", "off", "-fp_contract", "on", "-str", "reuse",
    "-multibyte", "-i", "include", "-i", "build/GNLJ82/include", "-i", "tmp",
    "-DBUILD_VERSION=0", "-DVERSION_GNLJ82", "-DNDEBUG=1",
    "-Cpp_exceptions", "on", "-use_lmw_stmw", "on",
]


def disasm(obj_path, s_path):
    subprocess.run([DTK, "elf", "disasm", obj_path, s_path],
                   capture_output=True, text=True, check=True)
    return io.open(s_path, encoding="utf-8").read()


def extract_fn(s_text, name_substr):
    m = re.search(r"^\.fn (\S*" + re.escape(name_substr) + r"\S*?),", s_text, re.M)
    if not m:
        raise SystemExit(f"fn containing '{name_substr}' not found")
    fname = m.group(1)
    body = s_text[m.end():s_text.index(f".endfn {fname}")]
    rows = []
    labels = {}
    for line in body.splitlines():
        line = line.strip()
        if not line:
            continue
        lm = re.match(r"^(\.L_\w+):$", line)
        if lm:
            labels[lm.group(1)] = len(rows)  # label points at next row index
            continue
        im = re.match(r"^/\* \w+ \w+  [0-9A-F ]+\*/\t(.+)$", line)
        if im:
            rows.append(im.group(1))
    # normalize label operands to row indices
    norm = []
    for r in rows:
        def sub(mo):
            return f"L{labels.get(mo.group(0), -1)}"
        norm.append(re.sub(r"\.L_\w+", sub, r))
    return fname, norm


def homes_of(rows):
    h = {}
    for r in rows[:12]:
        m = re.match(r"mr (r\d+), r3$", r)
        if m:
            h["self"] = m.group(1)
        m = re.match(r"mr (r\d+), r4$", r)
        if m:
            h["victim"] = m.group(1)
        m = re.match(r"lwz (r\d+), 0x304\(r3\)", r)
        if m:
            h["bus"] = m.group(1)
    return h


def main():
    src = sys.argv[1]
    label = sys.argv[2]
    lang = "c"
    show = 30
    for a in sys.argv[3:]:
        if a.startswith("--lang="):
            lang = a.split("=", 1)[1]
        if a.startswith("--show="):
            show = int(a.split("=", 1)[1])

    obj = os.path.splitext(src)[0] + ".o"
    cmd = [MWCC] + CFLAGS + [f"-lang={lang}", "-c", src, "-o", obj]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0 or not os.path.exists(obj):
        print(f"[{label}] COMPILE FAILED (lang={lang})")
        print(r.stdout[-4000:])
        print(r.stderr[-4000:])
        sys.exit(1)
    if r.stdout.strip() or r.stderr.strip():
        print(f"[{label}] compiler output: {r.stdout.strip()} {r.stderr.strip()}"[:500])

    if not os.path.exists(TARGET_S):
        disasm(TARGET_OBJ, TARGET_S)
    tname, target = extract_fn(io.open(TARGET_S, encoding="utf-8").read(), "KartItem_OnKartHit")

    ps = disasm(obj, os.path.splitext(src)[0] + ".s")
    pname, mine = extract_fn(ps, "OnKartHit")

    th, mh = homes_of(target), homes_of(mine)
    sm = difflib.SequenceMatcher(a=target, b=mine, autojunk=False)
    ratio = sm.ratio()
    same = sum(tr.size for tr in sm.get_matching_blocks())
    print(f"[{label}] fn={pname} rows target={len(target)} mine={len(mine)} "
          f"lcs={same}/{len(target)} ratio={ratio*100:.2f}%")
    print(f"[{label}] homes: self={mh.get('self','?')} (target {th.get('self','?')})  "
          f"victim={mh.get('victim','?')} (target {th.get('victim','?')})  "
          f"bus={mh.get('bus','?')} (target {th.get('bus','?')})")
    shown = 0
    for op, a1, a2, b1, b2 in sm.get_opcodes():
        if op == "equal":
            continue
        for k in range(max(a2 - a1, b2 - b1)):
            lt = target[a1 + k] if a1 + k < a2 else "---"
            rt = mine[b1 + k] if b1 + k < b2 else "---"
            print(f"  XX {a1+k:4d}  {lt:40s} || {rt}")
            shown += 1
            if shown >= show:
                return
    if shown == 0:
        print(f"[{label}] BYTE-IDENTICAL instruction stream vs target")


if __name__ == "__main__":
    main()
