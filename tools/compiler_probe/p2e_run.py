#!/usr/bin/env python3
# Phase 2e probe driver (batch_research_phase2e).
# Compiles a probe TU with the production flags of game/auto_ONKARTHIT_block.c,
# disasms with dtk, and classifies per-fn loop shapes:
#   deadctr classifier: does any bdnz loop contain an `addi rX, rX, 0x1` whose
#   rX is never read inside the fn after the loop (dead up-counter)?
#   mtx classifier: stfsx/slwi in a bdnz loop (integer out-index kept) vs
#   stfs-const-offset only (SR-coalesced pointer).
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
WROOT = os.path.normpath(os.path.join(HERE, "..", ".."))
WT = os.path.join(HERE, "tmp_p2e")
DTK = os.path.join(WROOT, "build", "tools", "dtk.exe")
CC = os.path.join(WROOT, "build", "compilers", "GC", "1.3.2", "mwcceppc.exe")

BASE_FLAGS = [
    "-nodefaults", "-proc", "gekko", "-align", "powerpc", "-enum", "int",
    "-fp", "hardware", "-Cpp_exceptions", "on", "-O4,p", "-inline", "auto",
    "-pragma", "cats off", "-pragma", "warn_notinlined off",
    "-maxerrors", "1", "-nosyspath", "-RTTI", "off", "-fp_contract", "on",
    "-str", "reuse", "-multibyte", "-use_lmw_stmw", "on",
]


def parse_fns(asm_text):
    out = {}
    for m in re.finditer(r"\.fn (\w+), (?:global|local)(.*?)\.endfn", asm_text, re.S):
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


def regs_read(mn, ops):
    """Crude read-set: every rN in ops except a pure destination (first reg
    of non-store ops). Covers the shapes we classify."""
    regs = re.findall(r"\br(\d+)\b", ops)
    if not regs:
        return set()
    if mn.startswith("st") or mn in ("cmpw", "cmplw", "cmpwi", "cmplwi"):
        return set(regs)
    return set(regs[1:])


def regs_written(mn, ops):
    regs = re.findall(r"\br(\d+)\b", ops)
    if not regs:
        return set()
    if mn.startswith("st") or mn.startswith("cmp"):
        if mn.endswith("u") or mn.endswith("ux"):  # update-form store
            return {regs[1]} if len(regs) > 1 else set()
        return set()
    if mn.endswith("u") and mn.startswith("l"):  # lwzu etc: dest + base
        return {regs[0]} | ({regs[1]} if len(regs) > 1 else set())
    return {regs[0]}


def classify_deadctr(insns):
    """Find addi rX,rX,0x1 in a bdnz region; check rX dead (no read after,
    anywhere in fn, before any re-write)."""
    has_bdnz = any(mn == "bdnz" for mn, ops in insns)
    counters = []
    for idx, (mn, ops) in enumerate(insns):
        m = re.match(r"r(\d+), r(\d+), 0x1$", ops)
        if mn == "addi" and m and m.group(1) == m.group(2):
            reg = m.group(1)
            # scan forward for a read of reg before a write
            dead = True
            for mn2, ops2 in insns[idx + 1:]:
                if mn2 == "LABEL":
                    continue
                if reg in regs_read(mn2, ops2):
                    dead = False
                    break
                if reg in regs_written(mn2, ops2):
                    break
            # backward scan: target counter is also unread between loop head
            # and the addi (true for an up-counter). We only need forward.
            if dead:
                counters.append("r" + reg)
    if not has_bdnz:
        return "NOCTR" + ("+deadinc" if counters else "")
    return "KEPT:" + ",".join(counters) if counters else "DCE"


def classify_mtx(insns):
    has_bdnz = any(mn == "bdnz" for mn, ops in insns)
    has_stfsx = any(mn == "stfsx" for mn, ops in insns)
    has_slwi = any(mn in ("slwi", "rlwinm") for mn, ops in insns)
    dead = classify_deadctr(insns)
    tag = []
    tag.append("ctr" if has_bdnz else "noctr")
    tag.append("stfsx" if has_stfsx else "stfs")
    tag.append("slwi" if has_slwi else "noslwi")
    tag.append(dead)
    return "|".join(tag)


def dump_fn(insns, limit=200):
    return "\n".join(f"  {mn} {ops}" for mn, ops in insns[:limit])


def probe(src, mode, tag, extra_flags=None, dump=None):
    flags = list(BASE_FLAGS) + (extra_flags or [])
    os.makedirs(WT, exist_ok=True)
    base = os.path.splitext(os.path.basename(src))[0]
    obj = os.path.join(WT, base + ".o")
    asm = os.path.join(WT, base + ".s")
    for p in (obj, asm):
        if os.path.exists(p):
            os.remove(p)
    r = subprocess.run([CC] + flags + ["-c", os.path.join(HERE, src), "-o", obj],
                       capture_output=True, text=True, cwd=WT, timeout=60)
    if r.returncode != 0 or not os.path.exists(obj):
        msg = (r.stdout + r.stderr).replace("\n", " | ")[:200]
        print(f"{tag}\tCFAIL\t{msg}", flush=True)
        return [f"{tag}\tCFAIL\t{msg}"]
    r2 = subprocess.run([DTK, "elf", "disasm", obj, asm],
                        capture_output=True, text=True, cwd=WT, timeout=60)
    if r2.returncode != 0:
        print(f"{tag}\tDFAIL", flush=True)
        return [f"{tag}\tDFAIL"]
    with open(asm) as f:
        fns = parse_fns(f.read())
    lines = []
    cls = classify_deadctr if mode == "deadctr" else classify_mtx
    for name in sorted(fns):
        verdict = cls(fns[name])
        line = f"{tag}\t{name}\t{verdict}\t{len(fns[name])}insn"
        print(line, flush=True)
        lines.append(line)
        if dump and name in dump:
            print(dump_fn(fns[name]), flush=True)
    return lines


if __name__ == "__main__":
    src = sys.argv[1]
    mode = sys.argv[2] if len(sys.argv) > 2 else "deadctr"
    dump = set(sys.argv[3].split(",")) if len(sys.argv) > 3 else None
    lines = probe(src, mode, f"GC/1.3.2 prod {src}", dump=dump)
    out = os.path.join(HERE, "results_p2e_%s.tsv" % os.path.splitext(src)[0])
    with open(out, "a") as f:
        f.write("\n".join(lines) + "\n")
