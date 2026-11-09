#!/usr/bin/env python3
"""Compile one unit with the native, trace-patched mweppc compiler and print
the compiler's decisions for one function. No emulator, no gdb, ~0.1 s, and
any number can run in parallel.

    python3 tools/mwtrace.py UNIT FN [--only VREG,COALESCE,COLOR,IGNODE,PCODE,SBLOCK,SNODE,SPICK,SSKIP] [-o trace.txt]

Needs `sh tools/install_mweppc.sh --build` (cloud_setup.sh runs it). The unit's
exact production command line is taken from `ninja -t commands`; GC/1.x and
GC/2.x units are compiled with the nearest native build (1.3.2 -> 2.6: same
code for 2437 of our 2470 1.3.2 units on 2026-11-09; float-heavy units differ).

Trace lines (tools/mweppc_trace/trace.patch; FN = mangled link name):
  VREG <exception|argument|local|temp|toc> r<n>|f<n> <name>  vreg numbering
  COALESCE r|f <dst root> <- <src root> first_temp=.. last_temp=.. <same|interfere|named|merge> off=<src offset> <insn>
  COLOR r|f <vreg> -> <reg> [spilled] cost=<c> name=<var|-> nb=<neighbours>   in colouring order
  IGNODE r|f <vreg> -> <reg> flags=<f> cost=<c> name=<var|-> nb=<neighbours>
        every vreg after colouring, coalesced ones included (flags: 1 spilled,
        2 pushed, 4 coalesced, 8 coalesced-into). nb lists machine regs too and
        still counts coalesced nodes. cost is 0 unless colouring needed a spill
        (estimatespillcosts runs lazily).
  PCODE pre|post B<block> <srcline> <insn>                    all PCode right before / after
        colorinstructions (post = physical regs, coalesced moves gone, before
        prologue/epilogue and the post-RA scheduler); srcline = PCode sourceoffset
        (a line number of the file; -1 = none)
  SBLOCK pre-RA|post-RA critical=<n> B<block>                 one per scheduled block
  SNODE i lat= height= latest= preds= off=<srcline> insn succ=i:lat,...  the block's DAG
  SPICK cycle.slot insn crit unc height rank node=<i> ready=<i:earliest:latest:height:unc>,...
        scheduler picks; ready = every node with no unscheduled pred (pick included)
  SSKIP pre-RA|post-RA B<block> count=<n> flags=0x.. <already-scheduled|too-short|prolog/epilog>
        blocks the scheduler skipped. A block keeps its pre-RA order only while no
        PCode is inserted into / deleted from it (PCode.c clears fScheduled).
What-if knob: MWCC_TRACE_RESCHED=all|<n>[,<n>] makes the post-RA scheduler
schedule those blocks again (as if regalloc had changed them); used by
`tools/mwsched.py resched`. Unset, the patched compiler's output is unchanged.
Opcodes print in upper case; registers end in "!" when written. Before regalloc
registers are virtual (r32+/f32+), as in mwccdbg dumps.
"""
from __future__ import annotations

import argparse
import os
import re
import shlex
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
NATIVE = ROOT / "build" / "mweppc" / "build"
TO_NATIVE = {
    **{v: "2_6" for v in ("1.0", "1.1", "1.1p1", "1.2.5", "1.2.5e", "1.2.5n", "1.3", "1.3.2", "1.3.2r", "2.6")},
    "2.0": "2_0", "2.0p1": "2_0", "2.5": "2_5", "2.7": "2_7",
}


def command(unit: str):
    obj = f"build/GNLJ82/src/{unit}.o"
    r = subprocess.run(["ninja", "-t", "commands", obj], cwd=ROOT, capture_output=True, text=True)
    line = [l for l in r.stdout.splitlines() if "mwcceppc.exe" in l]
    if not line:
        sys.exit(f"no mwcceppc command for {obj}")
    t = shlex.split(line[-1].split("&&")[0])
    i = next(k for k, x in enumerate(t) if x.endswith("mwcceppc.exe"))
    ver = re.search(r"GC/([^/]+)/mwcceppc\.exe", t[i]).group(1)
    nv = TO_NATIVE.get(ver)
    if nv is None:
        sys.exit(f"no native stand-in for GC/{ver}")
    exe = NATIVE / f"GC_{nv}" / "native" / "mwcceppc"
    if not exe.exists():
        sys.exit("build it first: sh tools/install_mweppc.sh --build")
    args = [a for a in t[i + 1:] if a != "-MMD"]
    return [str(exe)] + args, ver, nv


def trace(unit: str, fn: str, obj_out: str | None = None, env: dict | None = None) -> tuple[list[str], str]:
    """env: extra variables, e.g. {"MWCC_TRACE_RESCHED": "18"} (what-if: the post-RA
    scheduler schedules block B18 again, as if regalloc had changed it)."""
    cmd, ver, nv = command(unit)
    with tempfile.TemporaryDirectory() as d:
        o = cmd.index("-o")
        cmd[o + 1] = obj_out or os.path.join(d, "out.o")
        tf = os.path.join(d, "trace.txt")
        e = dict(os.environ, MWCC_TRACE=tf, MWCC_TRACE_FN=fn, **(env or {}))
        r = subprocess.run(cmd, cwd=ROOT, env=e, capture_output=True, text=True)
        if r.returncode:
            sys.exit(r.stdout + r.stderr)
        lines = Path(tf).read_text().splitlines() if os.path.exists(tf) else []
    return lines, f"GC/{ver} -> native GC/{nv.replace('_', '.')}"


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("unit")
    ap.add_argument("fn")
    ap.add_argument("--only", help="comma list of line kinds to keep")
    ap.add_argument("-o", "--out")
    a = ap.parse_args()
    lines, note = trace(a.unit, a.fn)
    if not lines:
        sys.exit(f"no trace for {a.fn} ({note}); check the mangled name")
    if a.only:
        keep = tuple(a.only.split(","))
        lines = [l for l in lines if l.startswith(keep)]
    text = f"# {a.unit} {a.fn} ({note})\n" + "\n".join(lines) + "\n"
    if a.out:
        Path(a.out).write_text(text)
    else:
        sys.stdout.write(text)


if __name__ == "__main__":
    main()
