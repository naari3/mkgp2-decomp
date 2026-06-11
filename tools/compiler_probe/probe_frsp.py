#!/usr/bin/env python3
# Probe driver for class-2 "frsp store-forward interleave" (Phase 2b, C++ axis).
#
# For each (compiler, flags) combo: compile frsp_min.c, disasm with dtk,
# classify each probe fn by:
#   n_frsp     : count of frsp instructions
#   n_stfs_sp  : count of stfs to r1 (scratch stores; raw copy block marker)
#   n_lfs_sp   : count of lfs from r1 (real stack reloads)
#   n_stw_sp   : count of stw to r1 with offset >= 8 (integer block-copy marker)
#   n_bl       : count of bl/bctrl (helper did not inline)
#   frsp_lfs   : count of frsp whose source reg was last defined by a non-r1 lfs
#                (the exact target idiom: frsp copy of a raw load register)
# Verdict (3-value + diagnostics):
#   TARGET    : frsp_lfs >= 3 and n_stfs_sp >= 16 (raw copy retained) -- the
#               store-forward interleave reproduced
#   no-frsp   : copy block retained raw (n_stfs_sp >= 16) but zero frsp
#   degenerate: anything else (DSE'd block, integer copy, frsp flood, calls)
import re
import subprocess
import os

ROOT = r"C:\Users\naari\src\github.com\naari3\mkgp2-decomp"
WT = os.path.join(ROOT, ".worktrees", "batch_research_frsp_phase2b")
TMP = os.path.join(WT, "tmp_probe")
DTK = os.path.join(ROOT, "build", "tools", "dtk.exe")
SRC = os.path.join(WT, "tools", "compiler_probe", "frsp_min.c")

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]


def classify(asm_text):
    out = {}
    for m in re.finditer(r"\.fn (\w+), (?:global|local)(.*?)\.endfn",
                         asm_text, re.S):
        name, body = m.group(1), m.group(2)
        insns = []
        for line in body.splitlines():
            line = line.strip()
            im = re.match(r"^/\*.*?\*/\s+(\S+)\s*(.*)$", line)
            if im:
                insns.append((im.group(1), im.group(2)))
        n_frsp = n_stfs_sp = n_lfs_sp = n_stw_sp = n_bl = frsp_lfs = 0
        # last definer of each fp reg: "lfs", "lfs_sp", or "other"
        last_def = {}
        for mn, args in insns:
            fm = re.match(r"f(\d+), (-?(?:0x[0-9a-fA-F]+|\d+))\((r\d+)\)", args)
            if mn == "lfs" and fm:
                reg, off, base = int(fm.group(1)), int(fm.group(2), 0), fm.group(3)
                if base == "r1":
                    n_lfs_sp += 1
                    last_def[reg] = "lfs_sp"
                else:
                    last_def[reg] = "lfs"
            elif mn == "stfs" and fm:
                if fm.group(3) == "r1":
                    n_stfs_sp += 1
            elif mn == "frsp":
                n_frsp += 1
                rm = re.match(r"f(\d+), f(\d+)", args)
                if rm:
                    dst, src = int(rm.group(1)), int(rm.group(2))
                    if last_def.get(src) == "lfs":
                        frsp_lfs += 1
                    last_def[dst] = "other"
            elif mn in ("bl", "bctrl"):
                n_bl += 1
            else:
                dm = re.match(r"f(\d+),", args)
                if dm and mn.startswith(("f", "ps_", "lfd", "psq_l")):
                    last_def[int(dm.group(1))] = "other"
                wm = re.match(r"r\d+, ((?:0x[0-9a-fA-F]+|\d+))\(r1\)", args)
                if mn == "stw" and wm and int(wm.group(1), 0) >= 8:
                    n_stw_sp += 1
        if frsp_lfs >= 3 and n_stfs_sp >= 16:
            verdict = "TARGET"
        elif n_stfs_sp >= 16 and n_frsp == 0:
            verdict = "no-frsp"
        else:
            verdict = "degenerate"
        detail = (f"frsp={n_frsp}/{frsp_lfs} stfs_sp={n_stfs_sp} "
                  f"lfs_sp={n_lfs_sp} stw_sp={n_stw_sp} bl={n_bl}")
        out[name] = (verdict, detail)
    return out


def probe(tag, cc, extra_flags=None, src=SRC, flags=None, keep_asm=None):
    flags = list(flags if flags is not None else BASE_FLAGS)
    if extra_flags:
        flags += extra_flags
    os.makedirs(TMP, exist_ok=True)
    obj = os.path.join(TMP, "frsp_out.o")
    asm = os.path.join(TMP, "frsp_out.s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    try:
        r = subprocess.run([cc] + flags + ["-c", src, "-o", obj],
                           capture_output=True, text=True, cwd=TMP, timeout=60)
    except Exception as e:
        line = f"{tag}\tCFAIL\t{e}"
        print(line, flush=True)
        return line
    if r.returncode != 0 or not os.path.exists(obj):
        msg = (r.stdout + r.stderr).replace("\n", " | ")[:200]
        line = f"{tag}\tCFAIL\t{msg}"
        print(line, flush=True)
        return line
    r2 = subprocess.run([DTK, "elf", "disasm", obj, asm],
                        capture_output=True, text=True, cwd=TMP, timeout=60)
    if r2.returncode != 0:
        line = f"{tag}\tDFAIL\t{(r2.stdout + r2.stderr)[:200]}"
        print(line, flush=True)
        return line
    with open(asm) as f:
        asm_text = f.read()
    if keep_asm:
        with open(os.path.join(TMP, keep_asm), "w") as f:
            f.write(asm_text)
    res = classify(asm_text)
    hit = "HIT" if any(v == "TARGET" for v, _ in res.values()) else "-"
    parts = [f"{k}={v}[{d}]" for k, (v, d) in sorted(res.items())]
    line = f"{tag}\t{hit}\t" + " ".join(parts)
    print(line, flush=True)
    return line


if __name__ == "__main__":
    cc132 = os.path.join(ROOT, "build", "compilers", "GC", "1.3.2",
                         "mwcceppc.exe")
    probe("c_baseline_1.3.2", cc132)
    probe("cpp_baseline_1.3.2", cc132, ["-lang", "c++"])
