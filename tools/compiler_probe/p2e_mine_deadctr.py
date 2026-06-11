#!/usr/bin/env python3
# Mine the whole target binary disasm (build/GNLJ82/asm/*.s) for ctr loops
# (bdnz back-edge) that contain an `addi rX, rX, 0x1` whose register is never
# read again in the function before being rewritten (dead up-counter web).
# Goal: how common is the dead-counter-in-ctr-loop idiom, and in which fns?
import os
import re
import sys
import glob

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
ASMDIR = os.path.join(ROOT, "build", "GNLJ82", "asm")

INSN_RE = re.compile(r"^/\* (\w{8}) .*?\*/\s+(\S+)\s*(.*)$")
LABEL_RE = re.compile(r"^(\.L_\w+):")
FN_RE = re.compile(r"^\.fn (\w+), (?:global|local)")


def regs_read(mn, ops):
    regs = re.findall(r"\br(\d+)\b", ops)
    if not regs:
        return set()
    if mn.startswith("st") or mn.startswith("cmp"):
        return set(regs)
    return set(regs[1:])


def regs_written(mn, ops):
    regs = re.findall(r"\br(\d+)\b", ops)
    if not regs:
        return set()
    if mn.startswith("st") or mn.startswith("cmp"):
        if mn.endswith(("u", "ux")):
            return {regs[1]} if len(regs) > 1 else set()
        return set()
    if mn.endswith(("u", "ux")) and mn.startswith("l"):
        return {regs[0]} | ({regs[1]} if len(regs) > 1 else set())
    return {regs[0]}


def scan_fn(name, insns):
    """insns: list of (addr, mn, ops) with LABEL entries (addr=None)."""
    hits = []
    label_pos = {}
    for idx, (addr, mn, ops) in enumerate(insns):
        if mn == "LABEL":
            label_pos[ops] = idx
    for idx, (addr, mn, ops) in enumerate(insns):
        if mn != "bdnz":
            continue
        tgt = ops.strip()
        if tgt not in label_pos or label_pos[tgt] > idx:
            continue
        lo, hi = label_pos[tgt], idx
        for j in range(lo, hi):
            a2, mn2, ops2 = insns[j]
            m = re.match(r"r(\d+), r(\d+), 0x1$", ops2 or "")
            if mn2 == "addi" and m and m.group(1) == m.group(2):
                reg = m.group(1)
                # dead check: walk the rest of the loop body then fall-through
                # after the loop linearly; conservative (ignores branches out).
                dead = True
                seq = insns[j + 1:hi] + insns[hi + 1:]
                for a3, mn3, ops3 in seq:
                    if mn3 == "LABEL":
                        continue
                    if reg in regs_read(mn3, ops3):
                        dead = False
                        break
                    if reg in regs_written(mn3, ops3):
                        break
                # also require an init (li/mr to reg) before the loop
                init = None
                for a4, mn4, ops4 in reversed(insns[:lo]):
                    if mn4 in ("li", "mr") and (ops4 or "").startswith("r%s," % reg):
                        init = "%s %s" % (mn4, ops4)
                        break
                    if mn4 != "LABEL" and reg in regs_written(mn4, ops4):
                        break
                if dead:
                    hits.append((a2, "r" + reg, init or "?"))
    return hits


def main():
    results = []
    for path in sorted(glob.glob(os.path.join(ASMDIR, "*.s"))):
        with open(path, encoding="utf-8", errors="replace") as f:
            text = f.read()
        cur = None
        insns = []
        for line in text.splitlines():
            line = line.strip()
            fm = FN_RE.match(line)
            if fm:
                cur = fm.group(1)
                insns = []
                continue
            if line.startswith(".endfn") and cur:
                for addr, reg, init in scan_fn(cur, insns):
                    results.append((cur, addr, reg, init, os.path.basename(path)))
                cur = None
                continue
            if cur is None:
                continue
            im = INSN_RE.match(line)
            if im:
                insns.append((im.group(1), im.group(2), im.group(3)))
                continue
            lm = LABEL_RE.match(line)
            if lm:
                insns.append((None, "LABEL", lm.group(1)))
    for fn, addr, reg, init, f in results:
        print(f"{fn}\t{addr}\t{reg}\tinit:{init}\t{f}")
    print(f"# total {len(results)} dead up-counters in ctr loops", file=sys.stderr)


if __name__ == "__main__":
    main()
