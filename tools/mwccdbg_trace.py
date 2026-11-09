"""gdb-side decision tracer for GC/2.6 mwcceppc.exe (loaded by tools/mwccdbg.py --trace).

Runs cadmic/mwcc-debugger's gdb half unchanged (it still writes the backend-*/
regalloc-* dumps) and adds breakpoints inside the compiler's own instruction
scheduler and copy coalescer, so the dump directory also gets an exact record
of every decision those passes made for the traced function:

  sched.json      one entry per scheduled basic block (pre-RA and post-RA):
                  the dependence DAG exactly as the compiler built it (every
                  successor edge with its latency, so may_alias memory edges
                  are included), each node's latency/height/latest, the
                  critical path, and every pick with the ready list at that
                  moment (predCount, earliest, latest, height, uncovering).
  coalesce.json   one entry per register class and colouring round: every
                  move the coalescer looked at, its two union-find roots,
                  whether they interfere, the temp range, and the outcome.

tools/mwsched.py turns these into readable logs and explanations.

Addresses and struct layouts are GC/2.6 (build 107) only. They were found by
matching the binary against the CC0 decompilation github.com/doldecomp/mweppc
(src/compiler/backend/Scheduler.c scheduleblock, InterferenceGraph.c
coalescenodes); see docs/mwcc_internals.md. On another compiler the tracer
does nothing and the normal dumps are still written.

Loaded as
    gdb -batch -nx -ex "py FUNCTION_NAME=...; OUTPUT_DIR=...; MWCCDBG_SCRIPT=...; MWCCDBG_NATIVE=0|1"
        -x tools/mwccdbg_trace.py [--args mwcceppc.exe ...]
"""
import json
import os
import sys
import types

import gdb

# --- GC/2.6 addresses -------------------------------------------------------
SCHED_DAG_READY = 0x507E34    # scheduleblock: DAG built, deadlines computed; ebp = head
SCHED_PICKED = 0x507E9B       # scheduleblock: selectinstruction returned; eax = node or 0
CRITICALPATH = 0x5E185C       # u16
MACHINEINFO_PTR = 0x5E1858    # MachineInfo* (issue_width first)
COALESCE_CHECK = 0x57BB83     # coalescenodes: dx = path(dest), bx = path(src), [esp+0xc] = instr
INTERFERENCE_MATRIX = 0x5E414C
COLORING_CLASS = 0x5EB2CF     # u8
N_REAL_REGISTERS = 0x5EA710   # s32[class]
FIRST_FE_TEMP = 0x5EB210      # s16[class]
LAST_TEMP = 0x5EA640          # s32[class]
USED_VIRTUAL = 0x5EAA2C       # s32[class]
OPCODEINFO_SIZE = 0x12        # name, format, operand_count, rank, flags, insn
CLASS_NAME = {4: "gpr", 3: "fpr"}
REG_PREFIX = {4: "r", 3: "f"}

if os.environ.get("MWCCDBG_NATIVE", "0") == "1" or globals().get("MWCCDBG_NATIVE") == "1":
    _execute = gdb.execute

    def _patched(cmd, *a, **k):
        c = cmd.strip()
        if c.startswith("target remote"):
            return _execute("starti", *a, **k)
        if c.startswith("set osabi"):
            return None
        if c == "quit":
            try:
                _execute("kill", *a, **k)
            except gdb.error:
                pass
        return _execute(cmd, *a, **k)

    gdb.execute = _patched
gdb.execute("set pagination off")
gdb.execute("set confirm off")

_mod = types.ModuleType("mwcc_debugger_lib")
sys.modules["mwcc_debugger_lib"] = _mod  # dataclasses look the module up
NS = _mod.__dict__
NS.update({"FUNCTION_NAME": FUNCTION_NAME, "OUTPUT_DIR": OUTPUT_DIR,  # noqa: F821
           "__file__": MWCCDBG_SCRIPT})  # noqa: F821
exec(compile(open(MWCCDBG_SCRIPT).read(), MWCCDBG_SCRIPT, "exec"), NS)  # noqa: F821

INF = gdb.selected_inferior


def mem(addr, n):
    return bytes(INF().read_memory(addr, n))


def u8(a):
    return mem(a, 1)[0]


def u16(a):
    return int.from_bytes(mem(a, 2), "little")


def s16(a):
    return int.from_bytes(mem(a, 2), "little", signed=True)


def u32(a):
    return int.from_bytes(mem(a, 4), "little")


def s32(a):
    return int.from_bytes(mem(a, 4), "little", signed=True)


def reg(name):
    return int(gdb.parse_and_eval("$" + name)) & 0xFFFFFFFF


STATE = {"blocks": [], "coalesce": [], "cur": None, "rank": {}}


def in_target():
    # breakpoints are only armed from the target's codegen start, and the
    # debugger quits at its codegen end
    return bool(STATE.get("armed"))


def phase():
    return "post-RA" if NS["REGALLOC_PASS"] else "pre-RA"


def insn_text(pc_addr):
    pc = NS["MwccPcode"].load(pc_addr)
    info = NS["MWCC_OPCODE_INFO"][pc.op]
    return pc.op, (pc.line or 0), f"{info.mnemonic.lower()} {NS['format_operands'](pc)}".strip()


def rank(op):
    r = STATE["rank"].get(op)
    if r is None:
        r = u8(NS["MWCC_VERSION"].opcodeinfo_addr + op * OPCODEINFO_SIZE + 9)
        STATE["rank"][op] = r
    return r


def node(addr):
    m = mem(addr, 0x1A)
    g = lambda o, n=2: int.from_bytes(m[o:o + n], "little")  # noqa: E731
    return {"next": g(0, 4), "succ": g(8, 4), "instr": g(0xC, 4), "latency": g(0x10),
            "earliest": g(0x12), "latest": g(0x14), "height": g(0x16),
            "pred": int.from_bytes(m[0x18:0x1A], "little", signed=True)}


def successors(addr):
    out, s = [], u32(addr + 8)
    while s:
        m = mem(s, 0xA)
        out.append((int.from_bytes(m[4:8], "little"), int.from_bytes(m[8:10], "little")))
        s = int.from_bytes(m[0:4], "little")
    return out


class DagReady(gdb.Breakpoint):
    def stop(self):
        if not in_target():
            return False
        head = reg("ebp")
        nodes, idx, a = [], {}, head
        while a:
            n = node(a)
            idx[a] = len(nodes)
            n["addr"] = a
            nodes.append(n)
            a = n["next"]
        out = []
        for n in nodes:
            op, line, text = insn_text(n["instr"])
            out.append({"i": idx[n["addr"]], "insn": text, "line": line, "op": op, "rank": rank(op),
                        "latency": n["latency"], "height": n["height"], "latest": n["latest"],
                        "preds": n["pred"],
                        "succ": [[idx.get(b, -1), lat] for b, lat in successors(n["addr"])]})
        blk = u32(reg("esp") + 0x24)
        STATE["cur"] = {"phase": phase(), "block": blk, "criticalpath": u16(CRITICALPATH),
                        "issue_width": u32(u32(MACHINEINFO_PTR)), "nodes": out, "picks": [],
                        "_idx": idx}
        STATE["blocks"].append(STATE["cur"])
        return False


class Picked(gdb.Breakpoint):
    def stop(self):
        cur = STATE["cur"]
        if cur is None or not in_target():
            return False
        esp = reg("esp")
        counter = u16(esp + 0xC)
        slot = u16(esp + 0x4)
        chosen = reg("eax")  # bp sits on `mov %eax,%ebx`
        idx = cur["_idx"]
        ready = []
        a = reg("ebp")
        while a:
            n = node(a)
            if n["pred"] == 0:
                unc = sum(1 for b, _ in successors(a) if s16(b + 0x18) == 1)
                ready.append([idx[a], n["earliest"], n["latest"], n["height"], unc])
            a = n["next"]
        cur["picks"].append({"cycle": counter, "slot": slot, "pick": idx.get(chosen, -1) if chosen else None,
                             "ready": ready})
        return False


class Coalesce(gdb.Breakpoint):
    def stop(self):
        if not in_target():
            return False
        cls = u8(COLORING_CLASS)
        p1 = int(gdb.parse_and_eval("$edx")) & 0xFFFF
        p2 = int(gdb.parse_and_eval("$ebx")) & 0xFFFF
        p1 = p1 - 0x10000 if p1 & 0x8000 else p1
        p2 = p2 - 0x10000 if p2 & 0x8000 else p2
        instr = u32(reg("esp") + 0xC)
        _, line, text = insn_text(instr)
        nreal = s32(N_REAL_REGISTERS + cls * 4)
        fe = s16(FIRST_FE_TEMP + cls * 2)
        last = s32(LAST_TEMP + cls * 4)
        a, b = min(p1, p2), max(p1, p2)
        inter = False
        if a != b:
            bit = (b * b) // 2 + a
            inter = bool(u32(u32(INTERFERENCE_MATRIX) + (bit >> 5) * 4) & (1 << (bit & 31)))
        key = (CLASS_NAME.get(cls, str(cls)), NS["REGALLOC_PASS"].get(NS["RegType"].GPR if cls == 4 else NS["RegType"].FPR, 0) + 1)
        if not STATE["coalesce"] or STATE["coalesce"][-1]["key"] != list(key):
            STATE["coalesce"].append({"key": list(key), "class": key[0], "round": key[1], "n_real": nreal,
                                      "first_temp": fe, "last_temp": last,
                                      "used_virtual": s32(USED_VIRTUAL + cls * 4), "moves": []})
        if p1 == p2:
            outcome = "same root (deleted)"
        elif inter:
            outcome = "interfere"
        elif p1 >= nreal and p2 >= nreal and not (fe <= p1 <= last and fe <= p2 <= last):
            outcome = "both virtual, not both temps"
        else:
            outcome = "coalesced"
        STATE["coalesce"][-1]["moves"].append({"insn": text, "line": line, "dst_root": p1, "src_root": p2,
                                               "interfere": inter, "outcome": outcome})
        return False


def dump():
    for b in STATE["blocks"]:
        b.pop("_idx", None)
    d = NS["OUTPUT_DIR"]
    with open(os.path.join(d, "sched.json"), "w") as f:
        json.dump({"function": NS["FUNCTION_NAME"], "blocks": STATE["blocks"]}, f)
    with open(os.path.join(d, "coalesce.json"), "w") as f:
        for c in STATE["coalesce"]:
            c.pop("key", None)
        json.dump({"function": NS["FUNCTION_NAME"], "rounds": STATE["coalesce"]}, f)


_orig_variables = NS["print_variables"]


def _print_variables():
    try:
        dump()
    finally:
        _orig_variables()


NS["print_variables"] = _print_variables


_orig_find = NS["find_current_function"]


def _find():
    # run_compiler calls this at every codegen start until it meets the target;
    # set our breakpoints only then (gdb breakpoints are slow under retrowin32)
    f = _orig_find()
    if f.linkname == NS["FUNCTION_NAME"] and not STATE.get("armed") and NS["MWCC_VERSION"].name == "GC/2.6":
        STATE["armed"] = True
        DagReady(f"*{SCHED_DAG_READY:#x}", internal=True)
        Picked(f"*{SCHED_PICKED:#x}", internal=True)
        Coalesce(f"*{COALESCE_CHECK:#x}", internal=True)
    return f


NS["find_current_function"] = _find
NS["run_compiler"]()
