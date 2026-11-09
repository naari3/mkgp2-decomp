#!/usr/bin/env python3
"""Explain MWCC's instruction schedule from a traced mwcc-debugger run.

`python3 tools/mwccdbg.py UNIT FN --trace` records, inside the real GC/2.6
compiler, the scheduler's dependence DAG and every pick (sched.json) and every
copy the coalescer looked at (coalesce.json); see tools/mwccdbg_trace.py and
docs/mwcc_internals.md for the algorithms. This module reads those files.

    python3 tools/mwsched.py log UNIT FN [--run]     per-cycle pick log with the deciding key
    python3 tools/mwsched.py explain UNIT FN [--run] instruction pairs ours vs target in the
                                                     other order, and why the scheduler kept ours
    python3 tools/mwsched.py coalesce UNIT FN [--run] every move and why it was / was not merged
    python3 tools/mwsched.py resched UNIT FN         which blocks give the target order if the
                                                     post-RA scheduler re-schedules them (native)

log/explain use the native trace-patched compiler (tools/mwtrace.py, ~0.1 s)
when build/mweppc is built, and the emitted schedule of each block: a block
scheduled again after regalloc (post-RA, see docs/mwcc_internals.md) is
explained from its post-RA DAG. --gdb uses the mwcc-debugger dumps in
build/mwccdbg/out/FN instead (--run reruns the traced debugger); coalesce
always does (mwtrace.py --only COALESCE is the native equivalent).

Programmatic (tools/regfix.py diag):
    explain_schedule(out_dir, ours_obj, tgt_obj, fn) -> [{"ours": (a, b), "target": (b, a),
        "reason": str, "kind": str, "line": (la, lb)}]

The selection rule replayed here is MWCC's selectinstruction (Scheduler.c):
the ready list (predCount 0, earliest <= cycle, unit free) is walked in the
block's original instruction order; a later candidate replaces the current
best when, in this order: it is critical (latest <= cycle) and the best is
not; it uncovers more nodes (successors whose only remaining pred it is); it
is higher (longer path to the block end); before regalloc only, its opcode
rank is lower. A full tie keeps the earlier instruction.
"""
from __future__ import annotations

import argparse
import difflib
import json
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import mwccdbg as md  # noqa: E402

ROOT = md.ROOT
KEYS = ("critical", "uncovering", "height", "rank", "order")


# ---------------------------------------------------------------------------
# selection replay

def cand_keys(c, cycle, rank, pre_ra):
    """c = [node, earliest, latest, height, uncover]"""
    return {"critical": c[2] <= cycle, "uncovering": c[4], "height": c[3],
            "rank": rank[c[0]] if pre_ra else 0}


def better(cand, best, cycle, rank, pre_ra):
    """(True/False, deciding key) for 'cand replaces best' (cand is later in order)."""
    kc, kb = cand_keys(cand, cycle, rank, pre_ra), cand_keys(best, cycle, rank, pre_ra)
    if kb["critical"] and not kc["critical"]:
        return False, "critical"
    if kc["critical"] and not kb["critical"]:
        return True, "critical"
    if kb["uncovering"] != kc["uncovering"]:
        return kc["uncovering"] > kb["uncovering"], "uncovering"
    if kb["height"] != kc["height"]:
        return kc["height"] > kb["height"], "height"
    if pre_ra and kb["rank"] != kc["rank"]:
        return kc["rank"] < kb["rank"], "rank"
    return False, "order"


def select(ready, cycle, rank, pre_ra, skip=()):
    best = None
    for c in ready:
        if c[1] > cycle or c[0] in skip:
            continue
        if best is None or better(c, best, cycle, rank, pre_ra)[0]:
            best = c
    return best


def why_over(win, lose, cycle, rank, pre_ra, order):
    """Key that makes `win` beat `lose` under MWCC's rule (whichever comes first in order)."""
    if order[win[0]] < order[lose[0]]:
        repl, key = better(lose, win, cycle, rank, pre_ra)
        return key if not repl else None
    repl, key = better(win, lose, cycle, rank, pre_ra)
    return key if repl else None


def picks_by_block(blk):
    """[(cycle, slot, node, ready_at_pick, unit_blocked)] for the real picks."""
    rank = {n["i"]: n["rank"] for n in blk["nodes"]}
    pre = blk["phase"] == "pre-RA"
    out = []
    for p in blk["picks"]:
        if p["pick"] is None:
            continue
        blocked = []
        skip = set()
        while True:
            s = select(p["ready"], p["cycle"], rank, pre, skip)
            if s is None or s[0] == p["pick"]:
                break
            blocked.append(s[0])        # the rule prefers it, but its unit could not issue
            skip.add(s[0])
        out.append((p["cycle"], p["slot"], p["pick"], p["ready"], blocked))
    return out


_SNODE = re.compile(r"SNODE (\d+) lat=(\d+) height=(\d+) latest=(\d+) preds=(\d+) off=(-?\d+) (.*?) succ=(.*)$")
_SPICK = re.compile(r"SPICK (\d+)\.(\d+) .* node=(-?\d+) ready=(.*)$")


def native_insn(t: str) -> str:
    """mwtrace "STW r0!,r1,_" -> "stw r0,r1" (the PCode text mwccdbg dumps)."""
    op, _, rest = t.partition(" ")
    parts = [x.rstrip("!") for x in rest.split(",") if x and x != "_"]
    if op in ("BL", "BLR", "BCTR", "BCTRL", "BLRL", "B"):
        parts = parts[:1] if op in ("BL", "B") else []   # drop the implicit clobber list
    parts = [re.sub(r"^c(\d)$", r"cr\1", x) for x in parts if not re.fullmatch(r"s\d+", x)]
    return op.lower() + (" " + ",".join(parts) if parts else "")


def load_native(unit: str, fn: str):
    """Same shape as sched.json, from tools/mwtrace.py (native trace-patched compiler).
    "line" is the PCode sourceoffset, which is the source line number."""
    import mwtrace
    lines, _ = mwtrace.trace(unit, fn)
    blocks, cur = [], None
    for l in lines:
        if l.startswith("SBLOCK "):
            f = l.split()
            cur = {"phase": f[1], "criticalpath": int(f[2].split("=")[1]),
                   "block": f[3] if len(f) > 3 else len(blocks), "issue_width": 2, "nodes": [], "picks": []}
            blocks.append(cur)
        elif l.startswith("SNODE ") and cur is not None:
            m = _SNODE.match(l)
            i, lat, h, latest, preds, off, insn, succ = m.groups()
            cur["nodes"].append({"i": int(i), "insn": native_insn(insn), "line": int(off), "rank": 0,
                                 "latency": int(lat), "height": int(h), "latest": int(latest),
                                 "preds": int(preds),
                                 "succ": [[int(a), int(b)] for a, b in (x.split(":") for x in succ.split(",") if x)]})
        elif l.startswith("SPICK ") and cur is not None:
            m = _SPICK.match(l)
            if not m:
                continue
            cyc, slot, nd, ready = m.groups()
            rk = re.search(r" rank=(\d+)", l)
            if int(nd) >= 0 and rk:
                cur["nodes"][int(nd)]["rank"] = int(rk.group(1))
            cur["picks"].append({"cycle": int(cyc), "slot": int(slot), "pick": int(nd),
                                 "ready": [[int(v) for v in x.split(":")] for x in ready.split(",") if x]})
    for b in blocks:                      # ready lists list nodes; ranks of nodes known only once picked
        for p in b["picks"]:
            p["ready"].sort(key=lambda c: c[0])
    return {"blocks": blocks} if blocks else None


def final_blocks(d):
    """[(index in d["blocks"], blk)] for the schedule that was emitted: a block scheduled
    again after regalloc (post-RA) replaces its pre-RA schedule. Block order = first
    appearance (pcbasicblocks order)."""
    last, order = {}, []
    for bi, blk in enumerate(d["blocks"]):
        k = blk.get("block", bi)
        if k not in last:
            order.append(k)
        last[k] = bi
    return [(last[k], d["blocks"][last[k]]) for k in order]


def load(out_dir):
    if isinstance(out_dir, dict):
        return out_dir
    f = Path(out_dir) / "sched.json"
    if not f.exists():
        return None
    return json.loads(f.read_text())


def fmt_log(d) -> str:
    L = []
    for bi, blk in enumerate(d["blocks"]):
        nodes = blk["nodes"]
        rank = {n["i"]: n["rank"] for n in nodes}
        pre = blk["phase"] == "pre-RA"
        L.append(f"== block {bi} ({blk['phase']}, {len(nodes)} insns, critical path {blk['criticalpath']}, "
                 f"issue width {blk['issue_width']}) ==")
        L.append("DAG (original order): i  line  insn  lat height latest preds -> succ(lat)")
        for n in nodes:
            s = " ".join(f"{a}({b})" for a, b in n["succ"])
            L.append(f"  {n['i']:>3} {n['line']:>5}  {n['insn']:<28} {n['latency']:>2} {n['height']:>4} "
                     f"{n['latest']:>4} {n['preds']:>3} -> {s}")
        L.append("picks: cycle.slot  insn   [why it beat the other ready insns]")
        for cyc, slot, pk, ready, blocked in picks_by_block(blk):
            win = next(c for c in ready if c[0] == pk)
            order = {n["i"]: n["i"] for n in nodes}
            reasons = []
            for c in ready:
                if c[0] == pk or c[1] > cyc:
                    continue
                if c[0] in blocked:
                    reasons.append(f"{c[0]}:unit-busy")
                    continue
                k = why_over(win, c, cyc, rank, pre, order)
                reasons.append(f"{c[0]}:{k or '?'}")
            waiting = [c[0] for c in ready if c[1] > cyc]
            L.append(f"  {cyc:>3}.{slot}  #{pk:<3} {nodes[pk]['insn']:<28} crit={int(win[2] <= cyc)} "
                     f"unc={win[4]} h={win[3]} rank={rank[pk]}  beats " + (" ".join(reasons) or "-")
                     + (f"  (latency-wait: {' '.join(map(str, waiting))})" if waiting else ""))
        L.append("")
    return "\n".join(L)


# ---------------------------------------------------------------------------
# ours vs target

def norm(ins: str) -> str:
    """objdump/PCode text without register numbers (identity of an instruction
    across a register-only or schedule-only diff)."""
    t = re.sub(r"\b[rf]\d+\b", "R", ins)
    t = t.replace("(", ",").replace(")", "")
    t = re.sub(r"\s+", " ", t).strip()
    return t


def pcode_norm(ins: str) -> str:
    # PCode "lfs f34,r5,0" vs objdump "lfs f1,0(r5)"; "cmp" vs "cmpw"
    op, _, rest = re.sub(r"\s+", " ", ins.strip()).partition(" ")
    op = {"cmp": "cmpw", "cmpi": "cmpwi", "cmpl": "cmplw", "cmpli": "cmplwi"}.get(op.rstrip("."), op)
    parts = [p for p in rest.split(",") if p]
    regs = [p for p in parts if re.fullmatch(r"[rf]\d+", p)]
    imms = [p for p in parts if not re.fullmatch(r"[rf]\d+|cr\d", p)]
    return op + " " + ",".join(["R"] * len(regs)) + "|" + ",".join(
        str(int(x.split("(")[0], 0)) if re.fullmatch(r"-?(0x)?[0-9a-f]+(\(.*\))?", x) else "?" for x in imms)


def obj_norm(ins: str) -> str:
    op, _, rest = re.sub(r"\s+", " ", ins.strip()).partition(" ")
    op = op.rstrip(".")
    rest = re.sub(r"\s*<[^>]*>", "", rest)
    parts = [p for p in re.split(r"[,()]", rest) if p]
    regs = [p for p in parts if re.fullmatch(r"[rf]\d+", p)]
    imms = [p for p in parts if not re.fullmatch(r"[rf]\d+|cr\d", p)]

    def num(x):
        try:
            return str(int(x, 0))
        except ValueError:
            return "?"
    return op + " " + ",".join(["R"] * len(regs)) + "|" + ",".join(num(x) for x in imms)


def map_nodes_to_ours(d, ours):
    """{(block, node): index in our object} via the scheduled pick order."""
    seq = []                                   # (block, node) in emitted order
    for bi, blk in final_blocks(d):
        for _, _, pk, _, _ in picks_by_block(blk):
            seq.append((bi, pk))
    A = [pcode_norm(d["blocks"][b]["nodes"][n]["insn"]).split("|")[0] for b, n in seq]
    B = [obj_norm(o).split("|")[0] for o in ours]
    m = {}
    for blk in difflib.SequenceMatcher(None, A, B, autojunk=False).get_matching_blocks():
        for t in range(blk.size):
            m[seq[blk.a + t]] = blk.b + t
    return m


def edge_kind(a, b):
    """why a -> b is an edge (a earlier): RAW / WAR / WAW / memory / serial."""
    ra, rb = md.REG.findall(a["insn"]), md.REG.findall(b["insn"])
    ra = [x + y for x, y in ra]
    rb = [x + y for x, y in rb]
    da = ra[:1] if not a["insn"].startswith(("st", "cmp", "fcmp", "b", "mt")) else []
    db = rb[:1] if not b["insn"].startswith(("st", "cmp", "fcmp", "b", "mt")) else []
    if da and da[0] in rb[len(db):]:
        return f"RAW {da[0]}"
    if db and db[0] in ra[len(da):]:
        return f"WAR {db[0]}"
    if da and da == db:
        return f"WAW {da[0]}"
    mem = lambda x: re.match(r"(l|st)[bhwfdm]", x["insn"]) is not None  # noqa: E731
    if mem(a) and mem(b):
        return "memory (may_alias)"
    return "serialisation (call / side effect / volatile / branch)"


def path(nodes, a, b):
    """shortest edge path a -> ... -> b in the DAG, or None."""
    prev, todo = {a: None}, [a]
    while todo:
        x = todo.pop(0)
        if x == b:
            p = [b]
            while prev[p[-1]] is not None:
                p.append(prev[p[-1]])
            return p[::-1]
        for s, _ in nodes[x]["succ"]:
            if s >= 0 and s not in prev:
                prev[s] = x
                todo.append(s)
    return None


def explain_schedule(out_dir, ours_obj, tgt_obj, fn):
    d = load(out_dir)
    if d is None:
        return []
    ours = md.objdump_fn(Path(ours_obj), fn)
    tgt = md.objdump_fn(Path(tgt_obj), fn)
    if not ours or not tgt:
        return []
    on, tn = [obj_norm(x) for x in ours], [obj_norm(x) for x in tgt]
    # pair each target instruction with one of ours carrying the same opcode+immediates
    pos_t = {}
    used = set()
    for j, t in enumerate(tn):
        k = next((k for k, o in enumerate(on) if o == t and k not in used), None)
        if k is not None:
            used.add(k)
            pos_t[k] = j
    nodemap = map_nodes_to_ours(d, ours)
    rev = {v: k for k, v in nodemap.items()}
    out = []
    ks = sorted(pos_t)
    seen = set()
    for x in range(len(ks)):
        for y in range(x + 1, len(ks)):
            a, b = ks[x], ks[y]            # a before b in ours
            if pos_t[a] < pos_t[b] or abs(a - b) > 12:
                continue
            na, nb = rev.get(a), rev.get(b)
            if not na or not nb or na[0] != nb[0]:
                continue
            key = (na, nb)
            if key in seen:
                continue
            seen.add(key)
            blk = d["blocks"][na[0]]
            nodes = blk["nodes"]
            A, B = nodes[na[1]], nodes[nb[1]]
            p = path(nodes, na[1], nb[1])
            if p:
                chain = " -> ".join(f"#{i} {nodes[i]['insn']}" for i in p)
                kinds = [edge_kind(nodes[p[i]], nodes[p[i + 1]]) for i in range(len(p) - 1)]
                reason = f"dependence: {chain} [{'; '.join(kinds)}]"
                kind = "dependence:" + kinds[0].split()[0]
            else:
                reason, kind = pick_reason(blk, na[1], nb[1])
            out.append({"ours": (ours[a], ours[b]), "target": (tgt[pos_t[b]], tgt[pos_t[a]]), "phase": blk["phase"],
                        "nodes": (na[1], nb[1]), "reason": reason, "kind": kind,
                        "line": (A["line"], B["line"])})
    return out


def pick_reason(blk, a, b):
    """a was emitted before b with no dependence; say why at a's pick."""
    nodes = blk["nodes"]
    rank = {n["i"]: n["rank"] for n in nodes}
    pre = blk["phase"] == "pre-RA"
    for cyc, slot, pk, ready, blocked in picks_by_block(blk):
        if pk != a:
            continue
        cb = next((c for c in ready if c[0] == b), None)
        win = next(c for c in ready if c[0] == a)
        if cb is None:
            preds = [n["i"] for n in nodes if any(s == b for s, _ in n["succ"])]
            return (f"#{b} not ready at cycle {cyc} when #{a} issued: waits on preds "
                    f"{', '.join('#%d %s' % (q, nodes[q]['insn']) for q in preds)}", "not-ready:preds")
        if cb[1] > cyc:
            return (f"#{b} not ready at cycle {cyc}: earliest {cb[1]} (latency of a predecessor)",
                    "not-ready:latency")
        if b in blocked:
            return f"#{b} preferred but its unit was busy at cycle {cyc}", "unit-busy"
        k = why_over(win, cb, cyc, rank, pre, {n["i"]: n["i"] for n in nodes})
        kc, kb = cand_keys(win, cyc, rank, pre), cand_keys(cb, cyc, rank, pre)
        return (f"cycle {cyc}: both ready, #{a} wins on {k}: "
                f"#{a} {kc} vs #{b} {kb}", f"priority:{k}")
    return "no pick record", "?"


# ---------------------------------------------------------------------------
# what-if: re-schedule a block after regalloc

def resched(unit: str, fn: str) -> list[str]:
    """For every block the post-RA pass skipped because it kept its pre-RA schedule,
    compile with MWCC_TRACE_RESCHED=<block> and compare FN with the target.
    A block that matches (or gets closer) only when re-scheduled after regalloc
    means: in the original source, regalloc or a later pass inserted or deleted an
    instruction in that block (docs/mwcc_internals.md, 'Post-RA scheduler')."""
    import tempfile
    import mwtrace
    tgt = md.objdump_fn(ROOT / f"build/{md.VERSION}/obj/{unit}.o", fn)

    def score(env):
        with tempfile.TemporaryDirectory() as d:
            lines, _ = mwtrace.trace(unit, fn, os.path.join(d, "o.o"), env)
            ours = md.objdump_fn(Path(d) / "o.o", fn)
        sm = difflib.SequenceMatcher(None, ours, tgt, autojunk=False)
        return lines, sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != "equal")

    lines, base = score(None)
    out = [f"{fn}: {base} differing lines as compiled (native stand-in)"]
    blocks = [int(m) for m in re.findall(r"SSKIP post-RA B(\d+) count=\d+ flags=\S+ already-scheduled",
                                          "\n".join(lines))]
    for b in blocks + ["all"]:
        _, n = score({"MWCC_TRACE_RESCHED": str(b)})
        if n != base:
            out.append(f"  re-schedule {'B' if b != 'all' else ''}{b} after regalloc: {n} differing lines"
                       + ("  <- MATCH" if n == 0 else ""))
    if len(out) == 1:
        out.append("  no block changes the result when re-scheduled after regalloc")
    return out


# ---------------------------------------------------------------------------
# coalescing

def fmt_coalesce(out_dir) -> str:
    f = Path(out_dir) / "coalesce.json"
    if not f.exists():
        return "no coalesce.json (run tools/mwccdbg.py with --trace)"
    d = json.loads(f.read_text())
    L = []
    for r in d["rounds"]:
        L.append(f"== {r['class']} round {r['round']}: machine regs <{r['n_real']}, "
                 f"temps {r['first_temp']}..{r['last_temp']} (args/named locals below {r['first_temp']}) ==")
        p = r["class"][0]
        for m in r["moves"]:
            def nm(x):
                kind = "phys" if x < r["n_real"] else ("temp" if r["first_temp"] <= x <= r["last_temp"] else "named")
                return f"{p}{x}({kind})"
            L.append(f"  {m['line']:>5}  {m['insn']:<20} {nm(m['dst_root'])} <- {nm(m['src_root'])}: {m['outcome']}")
    return "\n".join(L)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("cmd", choices=["log", "explain", "coalesce", "resched"])
    ap.add_argument("unit")
    ap.add_argument("fn")
    ap.add_argument("--run", action="store_true", help="(gdb mode) rerun the traced debugger")
    ap.add_argument("--gdb", action="store_true",
                    help="use the mwcc-debugger trace (real exe under retrowin32) instead of the native build")
    a = ap.parse_args()
    out = md.DBG_DIR / "out" / a.fn
    if a.cmd == "resched":
        md.sh(["ninja", f"build/{md.VERSION}/src/{a.unit}.o"], cwd=ROOT)
        print("\n".join(resched(a.unit, a.fn)))
        return
    native = not a.gdb and a.cmd != "coalesce" and (ROOT / "build/mweppc/build/GC_2_6/native/mwcceppc").exists()
    if native:
        md.sh(["ninja", f"build/{md.VERSION}/src/{a.unit}.o"], cwd=ROOT)
        d = load_native(a.unit, a.fn)
        if d is None:
            sys.exit(f"no scheduler trace for {a.fn}; check the mangled name")
    else:
        if a.run or not (out / "sched.json").exists():
            cmd, note = md.compile_command(a.unit, out / "dbg.o")
            md.sh(["ninja", f"build/{md.VERSION}/src/{a.unit}.o"], cwd=ROOT)
            if not md.run_debugger(cmd, a.fn, out, 300, trace=True):
                sys.exit(f"debugger failed; see {out}/run.log")
        d = out
    if a.cmd == "log":
        d = load(d)
        print(fmt_log(d) if d else "no sched.json")
    elif a.cmd == "coalesce":
        print(fmt_coalesce(out))
    else:
        res = explain_schedule(d, ROOT / f"build/{md.VERSION}/src/{a.unit}.o",
                               ROOT / f"build/{md.VERSION}/obj/{a.unit}.o", a.fn)
        if not res:
            print("no schedule-order differences found (or no trace)")
        for r in res:
            where = "lines"
            print(f"ours: {r['ours'][0]}  before  {r['ours'][1]}   ({r['phase']}, {where} {r['line'][0]}, {r['line'][1]})")
            print(f"   -> {r['reason']}")


if __name__ == "__main__":
    main()
