#!/usr/bin/env python3
"""Phase 2f-2: enable the CW 1.3.2 mwcceppc IR-optimizer per-pass dump.

Background (see docs/notes/cw132-allocator-phase2f-research.md "## Dump enablement"):

mwcceppc.exe GC 1.3.2 has TWO dump systems, found by static analysis (Ghidra + byte scan):

  (1) Per-pass *listing* dump (banners "AFTER REGISTER COLORING",
      "[FUNCTION-LEVEL ASM] AFTER REGISTER COLORING") emitted from CodeGen
      FUN_00433310 and FuncLevelAsmPPC FUN_00524f60, gated by .bss byte
      DAT_005e90ec. BUT the emit function FUN_004ffdb0 (and siblings
      FUN_004ffd90 / FUN_004ffda0) are STUBBED to a single RET in this release
      build. Setting 0x5e90ec=1 calls them; they do nothing. -> This dump,
      including the register-coloring listing, is DEAD and cannot be revived by
      any flag (the body was compiled out of the shipping build).

  (2) IR-optimizer per-pass dump (format "Dumping function %s after %s",
      "Flowgraph node %d First=%d, Last=%d", "Dumps for pass=%d"), emitted from
      IrOptimizer FUN_0042ddd0 via FUN_00454400 / FUN_004540c0 / FUN_00454240.
      This one is LIVE. It is gated by .bss byte DAT_005e9409 and writes to a
      FILE* DAT_005ddebc opened by FUN_00454110 as "<source-basename>.log"
      (mode "wt"; suffix ".log" at 0x5a79b4). Crucially, byte-scan of the whole
      .text shows DAT_005e9409 is ONLY ever written to 0 (init/reset at
      0x42dd79 + fopen-fail disable at 0x454190). The instruction that would set
      it to 1 (a -irdump style option handler in a debug build) was stripped.
      So we force it on with a 1-byte patch.

This script produces a PRIVATE patched copy (never touches the shipped exe).

Patch A (gate on):  VA 0x42dd79  "mov byte [0x5e9409], 0"  imm8 00 -> 01
Patch B (verbose, optional): VA 0x454405  JZ short (74 41) -> NOP NOP (90 90)
    forces FUN_00454400's `if (param_2 != 0)` to always dump the full flowgraph
    + named expression IR for every pass (callers pass param_2=0, so without B
    you only get progress markers, not the IR body).

NOTE: the IR dump is PRE-CODEGEN. It shows the named-web / temp IR the colorer
consumes (variable names in source order, flowgraph, use/def) but NOT the
physical register assignment -- coloring runs later in CodeGen, whose listing
dump is the stubbed system (1). So this dump does not by itself reveal the
colorer's web visit order; it reveals the IR feeding it.
"""
import struct
import sys
import os

IMG = 0x400000
TEXT_FO = 0x400  # .text raw file offset; .text RVA = 0x1000


def v2f(va):
    return va - IMG - 0x1000 + TEXT_FO


def patch(src, dst, verbose=True):
    data = bytearray(open(src, "rb").read())

    # Patch A: gate on
    fo = v2f(0x42DD79)
    assert data[fo:fo + 7] == bytes.fromhex("c60509945e0000"), \
        "unexpected bytes at gate-reset site 0x42dd79: " + data[fo:fo + 7].hex()
    data[fo + 6] = 0x01

    if verbose:
        # Patch B: force FUN_00454400 verbose body (JZ -> NOP NOP)
        fo2 = v2f(0x454405)
        assert data[fo2:fo2 + 2] == bytes.fromhex("7441"), \
            "unexpected bytes at JZ site 0x454405: " + data[fo2:fo2 + 2].hex()
        data[fo2] = 0x90
        data[fo2 + 1] = 0x90

    open(dst, "wb").write(data)
    print("wrote %s (gate=on%s)" % (dst, ", verbose IR body" if verbose else ""))


if __name__ == "__main__":
    src = sys.argv[1] if len(sys.argv) > 1 else "mwcceppc_priv.exe"
    dst = sys.argv[2] if len(sys.argv) > 2 else "mwcceppc_dump2.exe"
    verbose = "--quiet" not in sys.argv
    patch(src, dst, verbose=verbose)
    print("Output dump file lands next to the .c source as <basename>.log")
