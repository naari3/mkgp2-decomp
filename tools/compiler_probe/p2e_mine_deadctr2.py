#!/usr/bin/env python3
# Stricter re-mine: ctr loops with an `addi rX, rX, 0x1` where rX is NEVER
# read anywhere in the whole function (only writes: its init and the addi).
# These are the truly-dead up-counter webs (CarObject_HandleItemEffect class).
import os
import re
import sys
import glob

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
ASMDIR = os.path.join(ROOT, "build", "GNLJ82", "asm")

INSN_RE = re.compile(r"^/\* (\w{8}) .*?\*/\s+(\S+)\s*(.*)$")
LABEL_RE = re.compile(r"^(\.L_\w+):")
FN_RE = re.compile(r"^\.fn (\w+), (?:global|local)")


def reg_operands(mn, ops):
    """(reads, writes) crude model."""
    regs = re.findall(r"\br(\d+)\b", ops)
    if not regs:
        return set(), set()
    if mn.startswith("cmp"):
        return set(regs), set()
    if mn.startswith("st"):
        if mn.endswith(("u", "ux")):
            return set(regs), {regs[1]} if len(regs) > 1 else set()
        return set(regs), set()
    if mn.startswith("l") and mn.endswith(("u", "ux")):
        return set(regs[1:]), {regs[0], regs[1]} if len(regs) > 1 else {regs[0]}
    return set(regs[1:]), {regs[0]}


def scan_fn(name, insns):
    hits = []
    label_pos = {}
    for idx, (addr, mn, ops) in enumerate(insns):
        if mn == "LABEL":
            label_pos[ops] = idx
    # collect all bdnz loop bodies
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
                # locate the init (last write to reg before the loop head)
                init = None
                init_idx = 0
                for k4 in range(lo - 1, -1, -1):
                    a4, mn4, ops4 = insns[k4]
                    if mn4 == "LABEL":
                        continue
                    _rd, wr = reg_operands(mn4, ops4)
                    if reg in wr:
                        init = "%s %s" % (mn4, ops4)
                        init_idx = k4
                        break
                # truly dead = no read of reg from the init until the web
                # ends (next write to reg after the loop, excluding the
                # up-count addi itself, whose read feeds only itself)
                read_after = False
                for k in range(init_idx + 1, len(insns)):
                    if k == j:
                        continue
                    a3, mn3, ops3 = insns[k]
                    if mn3 == "LABEL":
                        continue
                    rd, wr = reg_operands(mn3, ops3)
                    if reg in rd:
                        read_after = True
                        break
                    if reg in wr and k > hi:
                        break  # new web starts after the loop
                if not read_after:
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
    print(f"# total {len(results)} truly-unread up-counters in ctr loops", file=sys.stderr)


if __name__ == "__main__":
    main()
