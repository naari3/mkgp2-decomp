#!/usr/bin/env python3
"""regfix.py: diagnose a register-only near miss, then try targeted rewrites.

Most near misses that pragmasweep / autopipe99 / shapesweep / decomp-permuter
leave behind differ only in register numbers. Random source search is blind to
WHY the allocator chose differently. This tool reproduces MWCC's allocator
offline and asks what would have to change in its input for it to produce the
target's registers:

1. mwcc-debugger (tools/mwccdbg.py) dumps the interference graph of OUR build
   (regalloc-{gpr,fpr}-pass-1-all.txt: every virtual register, its neighbours,
   coalesced flags) and the colouring order.
2. `simulate` re-runs MWCC's Chaitin allocator on that graph (see
   build/mwccdbg/mwcc-debugger/README.md):
     simplify: loop over the vregs in ascending number; a vreg with fewer than
       K=29 (GPR) / 32 (FPR) remaining neighbours is pushed; machine registers
       and coalesced vregs never leave the graph (MWCC bug); repeat until all
       are pushed (levels). Colouring order = reverse push order.
     select: first free of r0,r3..r12, then used saved regs low to high, then
       a new saved reg from r31 down (f0..f13 / f31 down for FPR).
   It is checked against the real colouring before anything else is trusted.
3. `want`: each vreg's target machine register, from the register-only diff
   (the PCode is aligned with our object and the target object).
4. `solve`: searches small edits of the allocator input - renumber one vreg
   (= create its value earlier/later), drop or add one interference edge
   (= shorten/extend a live range), add a phantom neighbour (= an extra
   coalesced copy, moves the vreg one level), merge two vregs (= one variable
   instead of two) - and their pairs, for edits under which the simulated
   allocator yields exactly the target registers.
5. Each edit is translated into concrete source rewrites aimed at the source
   lines that define/use the vregs involved (decl order of named locals,
   hoisting the vreg's expression into a local declared first/last, unvar of
   an inline-return temp, statement moves), which are compiled and scored
   (pragmasweep scoring). With --search the rewrites seed a shapesweep beam
   search restricted to the diagnosed lines.

The allocator model and the declaration-order solver also exist in Rust
(tools/regfix_sim, built automatically into build/regfix_sim on first use;
~4 us per simulated allocation vs ~220 us in Python, so 9! orders take ~1.5 s
and up to RS_MAXN=11 locals are permuted exhaustively). REGFIX_PY=1 forces
the Python model; both give identical colourings (checked on every dump).

Usage (repo root, after a build and `python3 tools/mwccdbg_install.py`; on
Windows the debugger runs mwcceppc.exe natively under a 32-bit gdb, see
tools/mwccdbg.py):
    python3 -I tools/regfix.py diag game/Sci2Card_BuildItemGetReceiptLine Sci2Card_BuildItemGetReceiptLine
    python3 -I tools/regfix.py fix  game/Sci2Card_BuildItemGetReceiptLine Sci2Card_BuildItemGetReceiptLine [--start F] [--search]
`diag` only explains; `fix` also tries rewrites. Nothing is written to src/.
"""
from __future__ import annotations

import argparse
import glob
import subprocess
import hashlib
import itertools
import shlex
import time
import json
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import mwccdbg as md  # noqa: E402

ROOT = md.ROOT
K_FREE = {"gpr": 29, "fpr": 32}
RS_MAXN = 11      # locals permuted exhaustively by the Rust solver


# ---------------------------------------------------------------------------
# allocator model

def num(v: str) -> int:
    return int(v[1:])


def parse_dump(path: Path):
    """{vreg: {phys, name, flags, nb}} and the file order."""
    out, order, cur = {}, [], None
    for l in path.read_text().splitlines():
        m = re.match(r"^([rf]\d+) -> ([rf]\d+)\s*(.*)$", l)
        if m:
            cur = {"v": m.group(1), "phys": m.group(2), "name": m.group(3).strip(), "flags": "", "nb": [], "cost": 0}
            out[cur["v"]] = cur
            order.append(cur["v"])
            continue
        if cur is None:
            continue
        m = re.match(r"^\s+flags:\s*(.*)$", l)
        if m:
            cur["flags"] = m.group(1)
        m = re.match(r"^\s+cost:\s*(-?\d+)", l)
        if m:
            cur["cost"] = int(m.group(1))
        m = re.match(r"^\s+neighbors: \d+ \((.*)\)", l)
        if m:
            cur["nb"] = m.group(1).split()
    return out, order


class Graph:
    """Allocator input for one register class."""

    def __init__(self, rc, nodes, key, nb, perm, names, phys):
        self.rc = rc
        self.nodes = list(nodes)          # vregs that get coloured
        self.key = dict(key)              # vreg -> sort key (vreg number; float after a renumber)
        self.nb = {v: set(s) for v, s in nb.items()}   # vreg -> neighbours among nodes
        self.perm = dict(perm)            # vreg -> (#permanent neighbours, set of fixed machine regs)
        self.names = names
        self.phys = phys                  # real result (for the self check)

    @classmethod
    def load(cls, out: Path, rc: str):
        fa = md.find(out, f"regalloc-{rc}-pass-1-all")
        fs = md.find(out, f"regalloc-{rc}-pass-1-assigned")
        if not fa or not fs:
            return None
        allv, _ = parse_dump(fa)
        asg, order = parse_dump(fs)
        S = set(order)
        nb, perm = {}, {}
        for v in order:
            n = allv[v]["nb"] if v in allv else asg[v]["nb"]
            nb[v] = {x for x in n if num(x) >= 32 and x in S}
            fixed = {x for x in n if num(x) < 32}
            perm[v] = (sum(1 for x in n if num(x) < 32 or x not in S), fixed)
        names = {v: (allv.get(v) or asg[v])["name"] for v in order}
        g = cls(rc, order, {v: num(v) for v in order}, nb, perm, names, {v: asg[v]["phys"] for v in order})
        g.params = set()
        vf = out / "variables.txt"
        if vf.exists():
            sec = None
            for l in vf.read_text().splitlines():
                if l.endswith(":") and not l.startswith(" "):
                    sec = l[:-1]
                    continue
                m = re.search(r"([rf]\d+) ->\s+\S+\s+(\S+)\s*$", l)
                if m and sec == "arguments":
                    g.params.add(m.group(2))
        g.real_order = order
        g.allv = allv
        g.cost = {v: (allv.get(v) or asg[v]).get("cost", 0) for v in order}
        return g

    def copy(self):
        g = Graph(self.rc, self.nodes, self.key, self.nb, self.perm, dict(self.names), self.phys)
        g.params = getattr(self, "params", set())
        g.cost = getattr(self, "cost", {})
        return g

    # --- the model ---
    def simplify(self):
        K = K_FREE[self.rc]
        nodes = sorted(self.nodes, key=lambda v: self.key[v])
        deg = {v: self.perm[v][0] + len(self.nb[v]) for v in nodes}
        removed, push = set(), []
        while len(push) < len(nodes):
            prog = False
            for v in nodes:
                if v in removed:
                    continue
                if deg[v] < K:
                    removed.add(v)
                    push.append(v)
                    prog = True
                    for x in self.nb[v]:
                        deg[x] -= 1
            if not prog:
                # stuck: MWCC (mweppc Coloring.c) pushes the cheapest spill
                # candidate, lowest cost/degree; ties -> lowest number
                cost = getattr(self, "cost", {})
                v = min((v for v in nodes if v not in removed),
                        key=lambda v: (cost.get(v, 0) / max(deg[v], 1), self.key[v]))
                removed.add(v)
                push.append(v)
                for x in self.nb[v]:
                    deg[x] -= 1
        return push[::-1]

    def colour(self, order=None):
        order = order or self.simplify()
        if self.rc == "gpr":
            vol = ["r0"] + [f"r{i}" for i in range(3, 13)]
            saved = [f"r{i}" for i in range(31, 13, -1)]
        else:
            vol = [f"f{i}" for i in range(0, 14)]
            saved = [f"f{i}" for i in range(31, 13, -1)]
        ph, used = {}, []
        for v in order:
            forb = set(self.perm[v][1])
            forb.update(ph[x] for x in self.nb[v] if x in ph)
            r = next((r for r in vol if r not in forb), None)
            if r is None:
                r = next((r for r in sorted(used, key=num) if r not in forb), None)
            if r is None:
                r = next((r for r in saved if r not in used and r not in forb), None)
                if r is None:
                    r = "spill"
                else:
                    used.append(r)
            ph[v] = r
        return ph, order


# ---------------------------------------------------------------------------
# target registers per vreg

def align_final(post, final):
    """index into final for every post-regalloc instruction (or None):
    exact-text match, preferring the candidate nearest to the running position."""
    by = {}
    for k, f in enumerate(final):
        by.setdefault((f[1], f[2]), []).append(k)
    used = set()
    res, last = [], -1
    for p in post:
        c = [k for k in by.get((p[1], p[2]), []) if k not in used]
        if not c:
            res.append(None)
            continue
        k = min(c, key=lambda k: (abs(k - (last + 1)), k))
        used.add(k)
        res.append(k)
        last = k
    return res


def want_map(out: Path, ours_obj: Path, tgt_obj: Path, fn: str):
    """{vreg: {target reg: count}} and {vreg: [(line, op, operands)]} defs/uses."""
    pre = md.parse_pcode(md.find(out, "before-regalloc"))
    post = md.parse_pcode(md.find(out, "after-regalloc"))
    fz = md.find(out, "after-scheduling", last=True)
    final = md.parse_pcode(fz) if fz else None
    phys = {}
    for rc in ("gpr", "fpr"):
        f = md.find(out, f"regalloc-{rc}-pass-1-all")
        if f:
            phys.update({v: d["phys"] for v, d in parse_dump(f)[0].items()})

    def subst(t):
        return md.REG.sub(lambda m: phys.get(m.group(0), m.group(0)) if int(m.group(2)) >= 32 else m.group(0), t)
    pair, j = [], 0
    for ins in pre:
        s_ = subst(ins[2])
        if j < len(post) and post[j][1] == ins[1] and post[j][2] == s_:
            pair.append((ins, post[j]))
            j += 1
        elif ins[1] in ("mr", "fmr") and len(set(md.pc_regs(ins[1], s_))) == 1:
            continue                      # coalesced copy, deleted by regalloc
        elif j < len(post) and post[j][1] == ins[1]:
            pair.append((ins, post[j]))   # unexpected text: keep in step
            j += 1
    if final is None:      # native trace: no post-RA listing; map post-regalloc PCode by opcode
        final = [p for _, p in pair]
    idx = align_final([p for _, p in pair], final)
    ours = md.objdump_fn(ours_obj, fn)
    tgt = md.objdump_fn(tgt_obj, fn)
    info = {"ours": len(ours), "tgt": len(tgt), "final": len(final),
            "opcode_diffs": sum(1 for o, t in zip(ours, tgt) if o.split()[0] != t.split()[0])}
    if len(final) != len(ours):
        # stand-in compiler output differs a little: map PCode positions to our
        # object by opcode sequence (PCode cmp == objdump cmpw etc. are normalised)
        import difflib

        def op(x):
            x = x.replace(".", "")
            return {"cmp": "cmpw", "cmpi": "cmpwi", "cmpl": "cmplw", "cmpli": "cmplwi"}.get(x, x)
        A = [op(f[1]) for f in final]
        B = [op(o.split()[0]) for o in ours]
        m = {}
        for blk in difflib.SequenceMatcher(None, A, B, autojunk=False).get_matching_blocks():
            for t in range(blk.size):
                m[blk.a + t] = blk.b + t
        idx = [m.get(k) if k is not None else None for k in idx]
    want, sites = {}, {}
    for (pv, pp), k in zip(pair, idx):
        for v in md.pc_regs(*pv[1:]):
            if num(v) >= 32:
                sites.setdefault(v, []).append(pv)
        if k is None or k >= len(ours) or k >= len(tgt):
            continue
        vr, pr = md.pc_regs(*pv[1:]), md.pc_regs(*pp[1:])
        orr, tr = md.regs(ours[k], True), md.regs(tgt[k], True)
        if len(orr) != len(tr) or orr != pr or len(vr) != len(pr):
            continue
        for v, t in zip(vr, tr):
            if num(v) >= 32:
                want.setdefault(v, {}).setdefault(t, 0)
                want[v][t] += 1
                info.setdefault("at", {}).setdefault(v, []).append(k)
    info["ours_asm"], info["tgt_asm"] = ours, tgt
    return want, sites, info


def resolve_want(g: Graph, want):
    """vreg -> single target reg (majority), dropping vregs whose sites
    disagree with each other when the majority is weak."""
    w = {}
    for v in g.nodes:
        c = want.get(v)
        if not c:
            continue
        best = max(c, key=c.get)
        if c[best] * 2 > sum(c.values()) or len(c) == 1:
            w[v] = best
    return w


def mismatch(ph, w):
    return [v for v, t in w.items() if ph.get(v) != t]


# ---------------------------------------------------------------------------
# solver over allocator-input edits

class Edit:
    def __init__(self, kind, a, b=None, extra=None):
        self.kind, self.a, self.b, self.extra = kind, a, b, extra

    def apply(self, g: Graph):
        g = g.copy()
        if self.kind == "renumber":       # a gets a key just past b's (extra = +-0.5)
            g.key[self.a] = g.key[self.b] + self.extra
        elif self.kind == "swapnum":
            g.key[self.a], g.key[self.b] = g.key[self.b], g.key[self.a]
        elif self.kind == "drop-edge":
            g.nb[self.a].discard(self.b)
            g.nb[self.b].discard(self.a)
        elif self.kind == "add-edge":
            g.nb[self.a].add(self.b)
            g.nb[self.b].add(self.a)
        elif self.kind == "phantom":      # extra permanent neighbour(s)
            n, f = g.perm[self.a]
            g.perm[self.a] = (n + self.extra, f)
        elif self.kind == "name":         # temp a becomes a named local: lowest numbers
            g.key[self.a] = min(g.key.values()) - 0.5
        elif self.kind == "lownb":        # n new named locals numbered first, live across a
            lo = min(g.key.values()) if g.key else 32
            for k in range(self.extra):
                x = f"{g.rc[0]}_new{k}_{self.a}"
                g.nodes.append(x)
                g.key[x] = lo - 1 - k
                g.nb[x] = {self.a}
                g.nb[self.a].add(x)
                g.perm[x] = (0, set())
                g.names[x] = f"new{k}"
        elif self.kind == "forbid":       # a machine register live across a
            n, f = g.perm[self.a]
            g.perm[self.a] = (n + 1, f | {self.extra})
        elif self.kind == "merge":        # b coalesced into a
            for x in g.nb[self.b]:
                g.nb[x].discard(self.b)
                if x != self.a:
                    g.nb[x].add(self.a)
                    g.nb[self.a].add(x)
            na, fa = g.perm[self.a]
            nb_, fb = g.perm[self.b]
            g.perm[self.a] = (na + 1, fa | fb)   # b stays as a coalesced (permanent) neighbour of others
            g.nodes = [v for v in g.nodes if v != self.b]
            del g.nb[self.b]
        return g

    def key(self):
        return (self.kind, self.a, self.b, self.extra)

    def text(self, g: Graph, sites):
        def d(v):
            return describe(g, v, sites)
        if self.kind == "renumber":
            rel = "after" if self.extra > 0 else "before"
            return f"create {d(self.a)} {rel} {d(self.b)} (vreg number {rel} {self.b})"
        if self.kind == "swapnum":
            return f"swap the creation order (vreg numbers) of {d(self.a)} and {d(self.b)}"
        if self.kind == "drop-edge":
            return f"make {d(self.a)} and {d(self.b)} NOT live at the same time"
        if self.kind == "add-edge":
            return f"make {d(self.a)} live across {d(self.b)}"
        if self.kind == "phantom":
            return f"give {d(self.a)} {self.extra:+d} neighbour(s) (an extra coalesced copy, e.g. `t = x;`), moving it one simplify level"
        if self.kind == "name":
            return (f"hold {d(self.a)} in a NAMED local (named locals get the lowest vreg numbers, so it is "
                    f"pushed in simplify sweep 1; rule low-numbered-neighbours-sweep1)")
        if self.kind == "lownb":
            return (f"add {self.extra} named local(s) declared FIRST (lowest vreg numbers) that are live while "
                    f"{d(self.a)} is live (e.g. keep a value used across its range in a named local): they are "
                    f"pushed early in simplify sweep 1 and drop its degree below K, so it is pushed in sweep 1 "
                    f"too (rule low-numbered-neighbours-sweep1)")
        if self.kind == "forbid":
            return (f"keep {self.extra} busy while {d(self.a)} is live (e.g. the argument/return value in "
                    f"{self.extra} is set before it, or it is computed after a call)")
        if self.kind == "merge":
            return f"use one variable for {d(self.a)} and {d(self.b)}"
        return self.kind


def describe(g: Graph, v, sites):
    nm = g.names.get(v, "")
    s = sites.get(v, [])
    lines = sorted({int(x[0]) for x in s if x[0].isdigit()})
    dfn = next((x for x in s if md.pc_regs(x[1], x[2])[:1] == [v]), s[0] if s else None)
    where = f"line {dfn[0]} `{dfn[1]} {dfn[2]}`" if dfn else "?"
    ln = (",".join(map(str, lines[:6])) + ("..." if len(lines) > 6 else "")) if lines else "-"
    tag = f"'{nm}'" if nm and not nm.startswith("@") else (f"temp {nm}" if nm else "temp")
    return f"{v}({tag}, def {where}, lines {ln})"


def candidate_edits(g: Graph, w, ph):
    bad = mismatch(ph, w)
    focus = set(bad)
    for v in bad:
        # whoever holds the register v wants, and whoever v's register should go to
        for x in g.nodes:
            if ph.get(x) == w[v]:
                focus.add(x)
    focus = [v for v in g.nodes if v in focus]
    E = []
    allk = sorted(g.nodes, key=lambda v: g.key[v])
    for a in focus:
        for b in allk:
            if b != a:
                E.append(Edit("renumber", a, b, 0.5))
                E.append(Edit("renumber", a, b, -0.5))
        for b in g.nb[a]:
            if b not in focus or num(a) < num(b):
                E.append(Edit("drop-edge", a, b))
        for b in focus:
            if b != a and b not in g.nb[a] and num(a) < num(b):
                E.append(Edit("add-edge", a, b))
                E.append(Edit("merge", a, b))
                E.append(Edit("merge", b, a))
        for b in focus:
            if num(a) < num(b):
                E.append(Edit("swapnum", a, b))
        if a in ph and ph[a] != "spill" and ph[a] not in g.perm[a][1]:
            E.append(Edit("forbid", a, None, ph[a]))
        for n in (1, 2, -1):
            E.append(Edit("phantom", a, None, n))
        for n in (1, 2, 3):
            E.append(Edit("lownb", a, None, n))
    # dedupe renumbers that do not move a in the order
    seen, out = set(), []
    for e in E:
        if e.kind == "renumber":
            g2 = e.apply(g)
            sig = ("renumber", e.a, tuple(sorted(g2.nodes, key=lambda v: g2.key[v])))
        else:
            sig = e.key()
        if sig in seen:
            continue
        seen.add(sig)
        out.append(e)
    return out


def solve_order(g: Graph, w, maxn=8, limit=4):
    """Keep the graph, permute the colouring positions of the focus vregs
    (mismatching ones + current holders of the wanted registers). Returns
    [(new order, [(x, y) pairs whose relative order flipped])], fewest flips first."""
    ph, order = g.colour()
    bad = mismatch(ph, w)
    if not bad:
        return []
    F = set(bad)
    for v in bad:
        F.update(x for x in g.nodes if ph.get(x) == w[v])
    F = [v for v in order if v in F]
    if len(F) > maxn:   # keep the earliest-coloured ones
        F = F[:maxn]
    slots = [i for i, v in enumerate(order) if v in F]
    res = []
    t_end = time.time() + float(os.environ.get("REGFIX_SOLVE_SECS", "20"))
    for k, perm in enumerate(itertools.permutations(F)):
        if list(perm) == F:
            continue
        if k % 256 == 0 and time.time() > t_end:
            print(f"  (order search stopped after {float(os.environ.get("REGFIX_SOLVE_SECS", "20")):.0f} s, REGFIX_SOLVE_SECS)", file=sys.stderr)
            break
        o2 = list(order)
        for i, v in zip(slots, perm):
            o2[i] = v
        p2, _ = g.colour(o2)
        if not mismatch(p2, w):
            pi = {v: i for i, v in enumerate(perm)}
            flips = [(y, x) for x, y in itertools.combinations(F, 2) if pi[y] < pi[x]]
            res.append((o2, flips, perm))
    res.sort(key=lambda r: len(r[1]))
    return res[:limit]


def solve_decl(classes, maxn=8, tlimit=120, only=None):
    """Declaration-order solver. Named function locals are numbered in reverse
    declaration order (per register class), and the order changes nothing else
    in the graph, so every order can be simulated without compiling.
    classes: {rc: (Graph, want)}. Returns the local names in the declaration
    order (first declared first) that give the target registers, or None.
    Only the locals involved (mismatching, holders of wanted regs, same level)
    are permuted when there are more than maxn."""
    t0 = time.time()
    locs, info = [], {}
    for rc, (g, w) in classes.items():
        L = decl_locals(g, only)
        info[rc] = (g, w, L, sorted(g.key[v] for v in L))
        locs += [g.names[v] for v in L]
    if not any(mismatch(g.colour()[0], w) for g, w, _, _ in info.values()):
        return None
    # current declaration order of the graph locals = descending number
    cur = []
    for rc, (g, w, L, nums) in info.items():
        cur += [(g.key[v], rc, g.names[v]) for v in L]
    names = []
    for rc, (g, w, L, nums) in info.items():
        for v in sorted(L, key=lambda v: -g.key[v]):
            if g.names[v] not in names:
                names.append(g.names[v])
    use_rs = sim_bin() is not None
    cap = RS_MAXN if use_rs else maxn
    if len(names) > cap:
        focus = set()
        for rc, (g, w, L, nums) in info.items():
            ph = g.colour()[0]
            bad = mismatch(ph, w)
            lv = levels(g)
            blv = {lv[v] for v in bad}
            for v in L:
                if v in bad or any(ph.get(v) == w.get(b) for b in bad) or lv[v] in blv:
                    focus.add(g.names[v])
        fixed = [n for n in names if n not in focus]
        free = [n for n in names if n in focus][:cap]
        fixed += [n for n in names if n in focus][cap:]
    else:
        fixed, free = [], list(names)
    rs_ok, rs_res = rs_solve_decl(names, free, [(g, w, L) for g, w, L, _ in info.values()], cap, tlimit) \
        if use_rs else (False, None)
    if rs_ok:
        return rs_res
    slots = [i for i, n in enumerate(names) if n in free]
    for perm in itertools.permutations(free):
        if time.time() - t0 > tlimit:
            return None
        order = list(names)
        for i, n in zip(slots, perm):
            order[i] = n
        rank = {n: i for i, n in enumerate(order)}
        ok = True
        for rc, (g, w, L, nums) in info.items():
            g2 = g.copy()
            for v, k in zip(sorted(L, key=lambda v: -rank[g.names[v]]), nums):
                g2.key[v] = k        # last declared gets the lowest number
            if mismatch(g2.colour()[0], w):
                ok = False
                break
        if ok:
            return order if order != names else None
    return None


# ---------------------------------------------------------------------------
# Rust hot path (tools/regfix_sim): same model, ~100x faster

SIM_DIR = ROOT / "tools" / "regfix_sim"
SIM_BIN = ROOT / "build" / "regfix_sim" / "release" / f"regfix_sim{md.EXE}"


def sim_bin():
    """Path of the Rust simulator (built on first use), or None (then Python is used)."""
    if os.environ.get("REGFIX_PY"):
        return None
    src = max(p.stat().st_mtime for p in SIM_DIR.rglob("*") if p.is_file() and "target" not in p.parts)
    if not SIM_BIN.exists() or SIM_BIN.stat().st_mtime < src:
        r = md.sh(["cargo", "build", "--release", "-q", "--manifest-path", str(SIM_DIR / "Cargo.toml")],
                  env={**os.environ, "CARGO_TARGET_DIR": str(ROOT / "build" / "regfix_sim")})
        if r.returncode != 0 or not SIM_BIN.exists():
            print("[regfix] cargo build failed, using the Python model:\n" + r.stderr[-800:], file=sys.stderr)
            return None
    return SIM_BIN


def sim_input(classes, names=None):
    """classes: [(Graph, want)] -> protocol text and per-class node lists."""
    out, idxs, nid = [], [], {}
    for n in names or []:
        nid.setdefault(n, len(nid))
    for c in classes:
        g, w = c[0], c[1]
        locs = set(c[2]) if len(c) > 2 else set(decl_locals(g))
        out.append(f"class {g.rc}")
        nodes = list(g.nodes)
        ix = {v: i for i, v in enumerate(nodes)}
        idxs.append(nodes)
        for v in nodes:
            n, fixed = g.perm[v]
            mask = 0
            for r in fixed:
                mask |= 1 << num(r)
            wv = num(w[v]) if v in w and w[v] != "spill" else -1
            out.append(f"node {ix[v]} {g.key[v]} {n} {mask} {wv} " + " ".join(str(ix[x]) for x in g.nb[v] if x in ix))
            if getattr(g, "cost", {}).get(v):
                out.append(f"cost {ix[v]} {g.cost[v]}")
            if v in locs:
                out.append(f"local {ix[v]} {nid.setdefault(g.names[v], len(nid))}")
    return out, idxs, nid


def rs_colour(g: Graph):
    b = sim_bin()
    if not b:
        return None
    txt, idxs, _ = sim_input([(g, {})])
    r = md.sh([str(b)], input="task colour\n" + "\n".join(txt) + "\n")
    t = r.stdout.split()[1:]
    nodes = idxs[0]
    order = [nodes[int(t[i])] for i in range(0, len(t), 2)]
    pref = "r" if g.rc == "gpr" else "f"
    ph = {nodes[int(t[i])]: (pref + t[i + 1] if t[i + 1] != "99" else "spill") for i in range(0, len(t), 2)}
    return ph, order


def rs_solve_decl(names, free, classes, maxn, tlimit):
    b = sim_bin()
    if not b:
        return False, None
    txt, _, nid = sim_input(classes, names)
    inv = {i: n for n, i in nid.items()}
    head = [f"task decl", f"maxn {maxn}", f"tlimit {tlimit}",
            "names " + " ".join(str(nid[n]) for n in names), "free " + " ".join(str(nid[n]) for n in free)]
    r = md.sh([str(b)], input="\n".join(head + txt) + "\n")
    for l in r.stdout.splitlines():
        if l.startswith("decl "):
            t = l.split()[1:]
            return True, (None if t == ["none"] else [inv[int(x)] for x in t])
    return False, None


def levels(g: Graph):
    """vreg -> simplify level (0 = pushed in the first sweep = coloured last)."""
    K = K_FREE[g.rc]
    nodes = sorted(g.nodes, key=lambda v: g.key[v])
    deg = {v: g.perm[v][0] + len(g.nb[v]) for v in nodes}
    removed, lv, L = set(), {}, 0
    while len(removed) < len(nodes):
        prog = False
        for v in nodes:
            if v not in removed and deg[v] < K:
                removed.add(v)
                lv[v] = L
                prog = True
                for x in g.nb[v]:
                    deg[x] -= 1
        if not prog:
            v = next(v for v in nodes if v not in removed)
            removed.add(v)
            lv[v] = L
            for x in g.nb[v]:
                deg[x] -= 1
        L += 1
    return lv


def solve(g: Graph, w, depth=2, beam=12, limit=8):
    ph, _ = g.colour()
    base = len(mismatch(ph, w))
    sols, scored = [], []
    E = candidate_edits(g, w, ph)
    t_end = time.time() + float(os.environ.get("REGFIX_SOLVE_SECS", "20"))
    for e in E:
        if time.time() > t_end:
            print(f"  (edit search stopped after {float(os.environ.get("REGFIX_SOLVE_SECS", "20")):.0f} s, REGFIX_SOLVE_SECS)", file=sys.stderr)
            return base, sols[:limit], len(E)
        g2 = e.apply(g)
        p2, _ = g2.colour()
        m = len(mismatch(p2, w))
        if m == 0:
            sols.append(([e], g2))
        scored.append((m, e))
    if depth < 2:
        return base, sols[:limit], len(E)
    # temps next to the focus turned into named locals, two at a time (fn_8023AC14 8f0fdc0)
    foc = set(mismatch(ph, w))
    near = {x for v in foc for x in g.nb[v]} | foc
    N = sorted(g.nodes, key=lambda v: (v not in near, g.key[v]))     # neighbours of the focus first
    N = [x for x in N if not (g.names.get(x) and not g.names[x].startswith("@"))]
    tried = 0
    for x, y in itertools.combinations(N, 2):
        if time.time() > t_end:
            break
        tried += 1
        es = [Edit("name", x), Edit("name", y)]
        g2 = es[1].apply(es[0].apply(g))
        if not mismatch(g2.colour()[0], w):
            sols.append((es, g2))
            if len(sols) >= limit + 2:
                break
    if sols:
        return base, sols[:limit + 2], len(E) + tried
    scored.sort(key=lambda x: x[0])
    for m, e in scored[:beam]:
        g1 = e.apply(g)
        p1, _ = g1.colour()
        for e2 in candidate_edits(g1, w, p1):
            if e2.key() == e.key():
                continue
            if time.time() > t_end:
                return base, sols, len(E) + tried
            tried += 1
            g2 = e2.apply(g1)
            p2, _ = g2.colour()
            if not mismatch(p2, w):
                sols.append(([e, e2], g2))
                if len(sols) >= limit:
                    return base, sols, len(E) + tried
    return base, sols, len(E) + tried


# ---------------------------------------------------------------------------
# driver

def print_schedule(out, ours_obj, tgt_obj, fn, src_lines=None):
    """Scheduling-order differences explained from the traced real scheduler
    (tools/mwsched.py, RE thread e1e979c): why ours keeps A before B."""
    try:
        import mwsched
    except ImportError:
        return
    if not isinstance(out, dict) and not (Path(out) / "sched.json").exists():
        print("\n== schedule: no trace (run diag with --sched; GC/2.6 only) ==")
        return
    try:
        res = mwsched.explain_schedule(out, ours_obj, tgt_obj, fn)
    except Exception as e:
        print(f"\n== schedule: explain failed: {e} ==")
        return
    print(f"\n== schedule: {len(res)} order differences ==")
    for r in res[:20]:
        la, lb = r.get("line") or (None, None)
        print(f"  ours {r['ours'][0]}  before  {r['ours'][1]}   [{r.get('kind', '')}]")
        print(f"     -> {r['reason']}")
        for l in (la, lb):
            if src_lines and isinstance(l, int) and 0 < l <= len(src_lines):
                print(f"     {l:>5} | {src_lines[l - 1].rstrip()[:110]}")
    if any(str(r.get("kind", "")).startswith(("dependence:memory", "priority:uncovering")) for r in res):
        print("  hint: memory edges (may-alias load/store pairs) decide these picks, directly or through "
              "'uncovering': try `regfix probe` (__restrict on pointer params) or load into a local before the store")


def print_coalesce(out, src_lines=None):
    """Copies the coalescer refused only because a named variable is involved
    (coalesce.json from the traced run, rules in docs/mwcc_internals.md): making
    that variable a temp (inline it / unname it / compute it in an inline) lets
    the copy merge, and the merged web takes the LOWER number."""
    f = Path(out) / "coalesce.json"
    rows = []
    tf = Path(out) / "trace.txt"
    if not f.exists() and tf.exists():
        for l in tf.read_text().splitlines():
            m = re.match(r"COALESCE ([rf]) (\d+) <- (\d+) .*?\bnamed\b(?: off=(-?\d+))?\s*(.*)$", l)
            if m:
                p, a, b = m.group(1), int(m.group(2)), int(m.group(3))
                line = int(m.group(4)) if m.group(4) else -1
                rows.append((line, m.group(5)[:18], f"{p}{a} <- {p}{b}", "the named one of " + f"{p}{a}/{p}{b}",
                             min(a, b)))
        f = None
    if f is None:
        d = {"rounds": []}
    elif not f.exists():
        return
    else:
        d = json.loads(f.read_text())
    for r in d.get("rounds", []):
        ft, lt, nr = r["first_temp"], r["last_temp"], r["n_real"]
        p = r["class"][0]

        def kind(x):
            return "phys" if x < nr else ("temp" if ft <= x <= lt else "named")
        for m in r["moves"]:
            if m["outcome"].startswith("both virtual"):
                a, b = m["dst_root"], m["src_root"]
                named = [x for x in (a, b) if kind(x) == "named"]
                rows.append((m["line"], m["insn"], f"{p}{a}({kind(a)}) <- {p}{b}({kind(b)})",
                             ", ".join(f"{p}{x}" for x in named), min(a, b)))
    print(f"\n== coalescing: {len(rows)} copies kept only because a named variable is involved ==")
    for line, insn, what, named, low in rows[:20]:
        print(f"  line {line:>4}  {insn:<18} {what}: make {named} a temp to merge (merged web = {low})")
        if src_lines and isinstance(line, int) and 0 < line <= len(src_lines):
            print(f"           | {src_lines[line - 1].rstrip()[:110]}")
    if rows:
        print("  (copies marked 'interfere' in `tools/mwsched.py coalesce` need a liveness change instead)")


def diagnose(unit, fn, out: Path, rerun=True, quiet=False, depth=2, sched=False):
    if rerun:
        run_dbg(unit, fn, out, trace=sched and not native_ok())
    import pragmasweep as ps
    src = ps.Unit(unit).src
    if native_ok():
        # order-only diffs that vanish when one block is re-scheduled after
        # regalloc (mwsched.resched, RE thread 27f348a): the fix is to make
        # regalloc insert/delete PCode in that block, not a register trick
        try:
            ours = md.objdump_fn(ROOT / f"build/{md.VERSION}/src/{unit}.o", ps.Unit(unit).compiled_name(fn))
            tgt = md.objdump_fn(ROOT / f"build/{md.VERSION}/obj/{unit}.o", ps.Unit(unit).compiled_name(fn))
            if ours != tgt and sorted(x.split()[0] for x in ours) == sorted(x.split()[0] for x in tgt):
                import mwsched
                print("== order-only diff: post-RA re-schedule probe ==")
                for l in mwsched.resched(unit, ps.Unit(unit).compiled_name(fn)):
                    print("  " + l)
        except Exception as e:
            print(f"(resched probe failed: {e})")
    if sched:
        sched_src = out
        if native_ok():
            import mwsched
            sched_src = mwsched.load_native(unit, ps.Unit(unit).compiled_name(fn))
        print_schedule(sched_src, ROOT / f"build/{md.VERSION}/src/{unit}.o", ROOT / f"build/{md.VERSION}/obj/{unit}.o",
                       ps.Unit(unit).compiled_name(fn), open(src, errors="replace").read().splitlines())
        print_coalesce(out, open(src, errors="replace").read().splitlines())
    return diagnose_dir(out, ROOT / f"build/{md.VERSION}/src/{unit}.o",
                        ROOT / f"build/{md.VERSION}/obj/{unit}.o", fn, quiet, depth,
                        src_lines=open(src, errors="replace").read().splitlines())


def run_dbg(unit, fn, out, timeout=int(os.environ.get("REGFIX_DBG_TIMEOUT", "900")), trace=False):
    import pragmasweep as ps
    fn = ps.Unit(unit).compiled_name(fn)
    md.sh(["ninja", f"build/{md.VERSION}/src/{unit}.o"], cwd=ROOT)
    if not trace and native_ok():
        u = ps.Unit(unit)
        out.mkdir(parents=True, exist_ok=True)
        for f in [*out.glob("*.txt"), *out.glob("*.json")]:
            f.unlink(missing_ok=True)
        if native_run(shlex.split(u.cmd.split("&&")[0].replace("\\", "/")), u.src, fn, out):
            return "native mweppc trace"
    cmd, note = md.compile_command(unit, out / "dbg.o")
    if not md.run_debugger(cmd, fn, out, timeout, trace=trace):
        sys.exit(f"mwcc-debugger failed; see {out}/run.log")
    return note


def vkind(g: Graph, v):
    nm = g.names.get(v, "")
    if nm.startswith("@"):
        return "ftemp"
    if nm and nm in getattr(g, "params", ()):
        return "param"
    return "local" if nm else "btemp"


def decl_locals(g: Graph, only=None):
    """vregs of named locals whose declaration the solver may move: not
    parameters, one vreg per name (no inline/block duplicates), and in `only`
    (the names declared in the function's leading block) when given."""
    L = [v for v in g.nodes if vkind(g, v) == "local"]
    cnt = {}
    for v in L:
        cnt[g.names[v]] = cnt.get(g.names[v], 0) + 1
    return [v for v in L if cnt[g.names[v]] == 1 and (only is None or g.names[v] in only)]


def advice(g: Graph, x, y):
    """Source-level reading of 'x must get a higher vreg number than y'.
    Numbering (checked on MWCC 2.6 dumps): the function's named locals first, in
    REVERSE declaration order (first declared = highest local number); then
    frontend temps @N (inline params/locals/returns, CSE temps) in reverse @
    order (@ allocated earlier = higher number); then backend temps in codegen
    order (generated later = higher number)."""
    kx, ky = vkind(g, x), vkind(g, y)
    nx, ny = g.names.get(x, ""), g.names.get(y, "")
    if kx == ky == "local":
        return f"declare '{nx}' before '{ny}'"
    if kx == "local":
        return (f"'{nx}' is a named local, numbered below every temp: turn it into a temp (compute it in an inline "
                f"helper / pass it as an inline argument / drop the variable) or make {ny or y} a named local that "
                f"survives (assign it to a local declared after '{nx}', not copy-propagated)")
    if ky == "local":
        return f"already true for a temp vs local '{ny}' unless {x} becomes a named local: keep {x} as a temp"
    if kx == ky == "ftemp":
        return f"frontend temp {nx} must be created BEFORE {ny} (reorder the inline calls / temps that make them)"
    if kx == "btemp" and ky == "btemp":
        return f"backend temp {x} must be generated AFTER {y} (evaluate its expression later: operand/argument order, statement order)"
    if kx == "btemp":
        return f"already true (backend temps are numbered above frontend temps) unless the numbers come from elsewhere"
    return f"frontend temp {nx} must become a backend temp (e.g. no inline / no CSE) or {y} a frontend temp"


def show_context(P, bad, sites, info, src_lines, maxl=12):
    """Source lines and our/target instructions around the mismatching vregs
    (for hand work: what to rewrite, and what the target does there)."""
    lines = sorted({int(x[0]) for v in bad for x in sites.get(v, []) if x[0].isdigit()})
    if src_lines and lines:
        P("  source lines involved:")
        for ln in lines[:maxl]:
            if 0 < ln <= len(src_lines):
                P(f"    {ln:>5} | {src_lines[ln - 1].rstrip()}")
    ks = sorted({k for v in bad for k in info.get("at", {}).get(v, [])})
    O, T = info.get("ours_asm", []), info.get("tgt_asm", [])
    if ks:
        P("  instructions (ours | target), * = differs:")
        shown = set()
        for k in ks[:maxl]:
            for j in range(max(0, k - 1), min(len(O), k + 2)):
                if j in shown or j >= len(T):
                    continue
                shown.add(j)
                mark = "*" if O[j] != T[j] else " "
                P(f"    {mark}{j * 4:>5x}  {O[j]:<32} | {T[j]}")


def diagnose_dir(out: Path, ours_obj, tgt_obj, fn, quiet=False, depth=2, src_lines=None):
    want, sites, info = want_map(out, Path(ours_obj), Path(tgt_obj), fn)
    rep = {"fn": fn, "info": info, "classes": {}}
    P = (lambda *a: None) if quiet else print
    P(f"{fn}: {info['ours']} insns ours / {info['tgt']} target, {info['opcode_diffs']} opcode diffs"
      + ("" if info["final"] == info["ours"] or (out / "trace.txt").exists()
         else f" (PCode {info['final']}: stand-in compiler differs)")
      + (" [native mweppc trace]" if (out / "trace.txt").exists() else ""))
    if info["ours"] != info["tgt"] or info["opcode_diffs"] > max(8, info["ours"] // 20):
        # the vreg -> target-register pairing needs (almost) the same instruction
        # sequence; otherwise every register looks wrong and the solver burns time
        P(f"  not a register-only diff ({info['ours']} vs {info['tgt']} insns, {info['opcode_diffs']} opcode "
          f"diffs): fix the instruction sequence first (objdiff / `tools/mwsched.py explain`); "
          f"set REGFIX_FORCE=1 to diagnose anyway")
        if not os.environ.get("REGFIX_FORCE"):
            rep["not_reg_only"] = True
            return rep
    for rc in ("gpr", "fpr"):
        g = Graph.load(out, rc)
        if g is None:
            continue
        ph, order = g.colour()
        model_ok = order == g.real_order and all(ph[v] == g.phys[v] for v in g.nodes)
        w = resolve_want(g, want)
        bad = mismatch(g.phys, w)
        cr = {"model_ok": model_ok, "bad": bad, "solutions": [], "g": g, "w": w}
        rep["classes"][rc] = cr
        if not bad:
            continue
        P(f"\n== {rc.upper()}: {len(g.nodes)} vregs, model {'reproduces' if model_ok else 'DOES NOT reproduce'} the real colouring; "
          f"{len(bad)} vregs off ==")
        pos = {v: i for i, v in enumerate(g.real_order)}
        for v in sorted(bad, key=lambda v: pos[v]):
            P(f"  #{pos[v]:<3} {describe(g, v, sites)}: {g.phys[v]} -> want {w[v]}")
        show_context(P, bad, sites, info, src_lines)
        if not model_ok:
            P("  (model mismatch: solutions below are unreliable)")
        lv = levels(g)
        ords = solve_order(g, w)
        cr["orders"] = []
        if ords:
            P("  colouring orders (same graph) that give the target registers:")
        for o2, flips, perm in ords:
            P("   * coloured in the order " + " ".join(perm) + ":")
            need = []
            for x, y in flips:
                same = lv[x] == lv[y]
                if same:
                    need.append(f"{x} numbered above {y} (same level {lv[x]}: higher vreg = coloured first): "
                                + advice(g, x, y))
                else:
                    need.append(f"{x} coloured before {y}: they are in levels {lv[x]}/{lv[y]} "
                                f"(move {x} to a later level = more neighbours, or {y} earlier = fewer)")
                P("       - " + need[-1])
            cr["orders"].append({"perm": list(perm), "flips": flips, "need": need})
        base, sols, ntried = solve(g, w, depth=depth)
        P(f"  tried {ntried} allocator-input edits; {len(sols)} give exactly the target registers:")
        for es, _ in sols:
            P("   * " + "\n     + ".join(e.text(g, sites) for e in es))
            cr["solutions"].append([{"kind": e.kind, "a": e.a, "b": e.b, "extra": e.extra,
                                     "text": e.text(g, sites)} for e in es])
        if not sols:
            P("   (none at depth 2: the target graph differs more, e.g. a different temp structure)")
        cr["g"] = g
        cr["w"] = w
    rep["sites"] = sites
    cl = {rc: (c["g"], c["w"]) for rc, c in rep["classes"].items() if "g" in c}
    if cl:
        order = solve_decl(cl, tlimit=int(os.environ.get("REGFIX_DECL_TLIMIT", "30")))
        rep["decl_order"] = order
        if order:
            P("\n== declaration order that gives the target registers (first declared first): ==\n   "
              + ", ".join(order))
    return rep


# ---------------------------------------------------------------------------
# fix: diagnosis-guided rewrite search (shapesweep moves, regfix ranking)

NETNS = [sys.executable, str(ROOT / "tools" / "netns_lo.py")]


def can_unshare():
    if os.name == "nt":
        return False
    try:
        r = md.sh(["unshare", "-n", *NETNS, "true"])
    except OSError:
        return False
    return r.returncode == 0


TMPDIR = Path(os.environ.get("REGFIX_TMP", os.path.join(__import__("tempfile").gettempdir(), "regfix")))
OBJCOPY = ROOT / "build" / "binutils" / f"powerpc-eabi-objcopy{md.EXE}"


# ---------------------------------------------------------------------------
# native trace backend (tools/mwtrace.py, RE thread 456a88c/60206cc): the
# decompiled GC/2.x compiler built for Linux prints PCODE / IGNODE / COLOR / VREG
# lines in ~0.1 s, no emulator or gdb. trace_to_dumps writes them in the
# mwccdbg dump layout so the analysis above runs unchanged.

def native_ok():
    if os.environ.get("REGFIX_MWCCDBG"):
        return False
    try:
        import mwtrace
    except ImportError:
        return False
    return any(mwtrace.NATIVE.glob("GC_*/native/mwcceppc"))


def _pc_text(ins):
    ins = ins.replace("!", "")
    ins = re.sub(r"(,_)+$", "", ins)
    op, _, rest = ins.partition(" ")
    return op.lower(), rest.replace("c0", "cr0")


def trace_to_dumps(lines, d: Path):
    pre, post, var_args = [], [], []
    nodes = {"r": {}, "f": {}}
    color = {"r": [], "f": []}
    seen_ig, seen_col = {"r": set(), "f": set()}, {"r": set(), "f": set()}
    done_ig, done_col = {"r": False, "f": False}, {"r": False, "f": False}
    for l in lines:
        t = l.split(" ", 4)
        if t[0] == "PCODE" and len(t) >= 5:
            ln = t[3] if t[3] != "-1" else ""
            op, rest = _pc_text(t[4])
            (pre if t[1] == "pre" else post).append(f"    {ln:>4}  {op:<8} {rest}")
        elif t[0] == "VREG" and l.split()[1] == "argument":
            x = l.split()
            var_args.append((x[2], x[3] if len(x) > 3 else ""))
        elif t[0] in ("IGNODE", "COLOR"):
            m = re.match(r"^(IGNODE|COLOR) ([rf]) (\d+) -> (-?\d+)(.*)$", l)
            if not m:
                continue
            k, c, v, col, rest = m.group(1), m.group(2), int(m.group(3)), int(m.group(4)), m.group(5)
            seen, done = (seen_ig, done_ig) if k == "IGNODE" else (seen_col, done_col)
            if done[c]:
                continue
            if v in seen[c]:          # next colouring attempt: keep pass 1 only
                done[c] = True
                continue
            seen[c].add(v)
            f = dict(re.findall(r"(\w+)=(\S*)", rest))
            rec = {"v": v, "col": col if "[spilled]" not in rest else 99, "cost": f.get("cost", "0"),
                   "flags": f.get("flags", ""), "name": "" if f.get("name", "-") == "-" else f.get("name", ""),
                   "nb": [int(x) for x in f.get("nb", "").split(",") if x]}
            if k == "IGNODE":
                nodes[c][v] = rec
            else:
                color[c].append(rec)
    (d / "backend-16-before-regalloc.txt").write_text("\n".join(pre) + "\n")
    (d / "backend-17-after-regalloc.txt").write_text("\n".join(post) + "\n")
    for c, rc in (("r", "gpr"), ("f", "fpr")):
        def fmt(r):
            name = r["name"] or nodes[c].get(r["v"], {}).get("name", "")
            nb = r["nb"] or nodes[c].get(r["v"], {}).get("nb", [])
            return (f"{c}{r['v']} -> {c}{r['col']} {name}\n  flags: {r['flags']}\n  cost: {r['cost']}\n"
                    f"  neighbors: {len(nb)} ({' '.join(c + str(x) for x in nb)})\n")
        if nodes[c] or color[c]:
            (d / f"regalloc-{rc}-pass-1-all.txt").write_text("".join(fmt(r) for r in sorted(nodes[c].values(), key=lambda r: r["v"])))
            (d / f"regalloc-{rc}-pass-1-assigned.txt").write_text("".join(fmt(r) for r in color[c]))
    (d / "variables.txt").write_text("arguments:\n" + "".join(f"    {v} -> {v}   {n}\n" for v, n in var_args))


def native_run(cmd_toks, src, fn_sym, d: Path):
    """Compile src with the native traced compiler (command = production
    command tokens) and write mwccdbg-layout dumps into d. True on success."""
    import mwtrace
    toks = list(cmd_toks)
    i = next(k for k, t in enumerate(toks) if t.endswith("mwcceppc.exe"))
    ver = re.search(r"GC/([^/]+)/mwcceppc\.exe", toks[i])
    nv = mwtrace.TO_NATIVE.get(ver.group(1)) if ver else None
    exe = mwtrace.NATIVE / f"GC_{nv}" / "native" / "mwcceppc" if nv else None
    if not exe or not exe.exists():
        return False
    args = [a for a in toks[i + 1:] if a != "-MMD"]
    args[args.index("-c") + 1] = src
    args[args.index("-o") + 1] = str(d / "native.o")
    tf = d / "trace.txt"
    env = dict(os.environ, MWCC_TRACE=str(tf), MWCC_TRACE_FN=fn_sym)
    r = subprocess.run([str(exe)] + args, cwd=ROOT, env=env, capture_output=True, text=True)
    (d / "run.log").write_text(r.stdout + r.stderr)
    if r.returncode or not tf.exists():
        return False
    trace_to_dumps(tf.read_text().splitlines(), d)
    return True


class Evaluator:
    """Compile a TU text, score it (diff lines), and diagnose it with the debugger.
    Debugger runs go into separate network namespaces so up to `jobs` run at once."""

    def __init__(self, sw, fn_sym, jobs, fn=None):
        import pragmasweep as ps
        self.ps, self.sw, self.sym, self.jobs = ps, sw, fn_sym, jobs
        self.fn = fn or fn_sym
        self.u = sw.u
        # retrowin32's gdb stub has a fixed port: parallel runs need a network
        # namespace each (Linux); native gdb (Windows) needs nothing
        self.netns = not md.NATIVE and can_unshare()
        self.native = native_ok()
        self.par = md.NATIVE or self.netns or self.native
        self.cache = {}
        self.tmp = TMPDIR
        self.tmp.mkdir(parents=True, exist_ok=True)

    def toks(self, src, out_o):
        toks = shlex.split(self.u.cmd.replace("\\", "/"))
        i = next(k for k, t in enumerate(toks) if t.endswith("mwcceppc.exe"))
        toks = toks[i:]
        cc = self.sw.cc
        sup = md.TO_SUPPORTED.get(cc)
        toks[0] = re.sub(r"GC/[^/]+/", f"GC/{sup}/", toks[0])
        toks[toks.index("-c") + 1] = src
        oi = toks.index("-o")
        toks[oi + 1] = out_o
        toks[oi:oi] = ["-sym", "on"]
        toks = [t for t in toks if t != "-MMD"]
        return toks

    def diag(self, text, slot, only=None):
        """(metric tuple, report dict) for a TU text."""
        h = hashlib.sha1(text.encode()).hexdigest()
        if h in self.cache:
            return self.cache[h]
        d = self.run(text, slot)
        res = analyze_dir(d, d / "ours.o", ROOT / f"build/{md.VERSION}/obj/{self.u.obj}.o", self.fn, only=only)
        self.cache[h] = res
        return res

    def run(self, text, slot):
        """compile text (ours.o) and dump it with the debugger; returns the dump dir."""
        d = self.tmp / f"s{slot}"
        d.mkdir(exist_ok=True)
        for f in d.glob("*"):
            if f.is_file():
                f.unlink()
        sp = os.path.join(os.path.dirname(os.path.abspath(self.u.src)), f".regfix_{os.getpid()}_{slot}{self.u.ext}")
        open(sp, "w").write(text)
        try:
            # our object with the production compiler
            c = self.ps.swap_cc(self.u.cmd, self.sw.cc)
            ours = (d / "ours.o").as_posix()
            c = re.sub(r"-c \S+ -o \S+", lambda m: f"-c {sp} -o {ours}", c)
            subprocess.run(c, shell=True, cwd=ROOT, capture_output=True)
            for x in self.u.post:
                subprocess.run(x.replace(f"build/GNLJ82/src/{self.u.obj}.o", ours), shell=True, cwd=ROOT,
                               capture_output=True)
            if self.sym != self.fn:   # only the symbol we disassemble (the full map has duplicate targets)
                md.sh([str(OBJCOPY), f"--redefine-sym={self.sym}={self.fn}", ours], cwd=ROOT)
            if self.native and native_run(shlex.split(self.ps.swap_cc(self.u.cmd, self.sw.cc).split("&&")[0].replace("\\", "/")),
                                          Path(sp).as_posix(), self.sym, d):
                return d
            cmd = self.toks(Path(sp).as_posix(), (d / "dbg.o").as_posix())
            argv = md.debugger_argv(cmd, self.sym, d)
            if argv:
                pre = ["unshare", "-n", *NETNS] if self.netns else []
                r = md.sh(pre + argv, cwd=ROOT, timeout=int(os.environ.get("REGFIX_DBG_TIMEOUT", "900")))
                (d / "run.log").write_text(r.stdout + r.stderr)
        finally:
            try:
                os.remove(sp)
            except OSError:
                pass
        return d


def top_decls(st):
    import shapesweep as ss
    a, b = ss.decl_front(st)
    return {v[0] for d in st.stmts[a:b] for v in d["vars"]}


def analyze_dir(out, ours_obj, tgt_obj, fn, depth=1, only=None):
    """metric = (opcode diffs, mismatching vregs, flips needed, 0/1 graph edit known), plus report."""
    if not md.find(out, "before-regalloc"):
        return (99, 999, 99, 1), None
    try:
        want, sites, info = want_map(out, Path(ours_obj), Path(tgt_obj), fn)
    except Exception:
        return (99, 999, 99, 1), None
    if not info["ours"] or info["ours"] != info["tgt"]:
        return (99 + abs(info["ours"] - info["tgt"]), 999, 99, 1), None
    nbad, flips, edit = 0, 0, 0
    rep = {"info": info, "sites": sites, "classes": {}}
    for rc in ("gpr", "fpr"):
        g = Graph.load(out, rc)
        if g is None:
            continue
        w = resolve_want(g, want)
        bad = mismatch(g.phys, w)
        nbad += len(bad)
        cls = {"g": g, "w": w, "bad": bad, "orders": [], "sols": []}
        rep["classes"][rc] = cls
        if not bad:
            continue
        o = solve_order(g, w, maxn=6, limit=1)
        cls["orders"] = o
        flips += len(o[0][1]) if o else 20
        _, sols, _ = solve(g, w, depth=depth, limit=2)
        cls["sols"] = sols
        if not sols:
            edit = 1
    rep["decl_order"] = None
    if nbad and not info["opcode_diffs"]:
        rep["decl_order"] = solve_decl({rc: (c["g"], c["w"]) for rc, c in rep["classes"].items()}, tlimit=40,
                                       only=only)
    return (info["opcode_diffs"], nbad, flips, edit), rep


def focus_of(rep):
    """source lines and local names implicated by a report."""
    lines, names = set(), set()
    if not rep:
        return lines, names
    sites = rep["sites"]
    for cls in rep["classes"].values():
        g = cls["g"]
        vs = set(cls["bad"])
        for o2, flips, perm in cls["orders"]:
            for x, y in flips:
                vs.update((x, y))
        for es, _ in cls["sols"]:
            for e in es:
                vs.update(v for v in (e.a, e.b) if v)
        for v in vs:
            for x in sites.get(v, []):
                if x[0].isdigit():
                    lines.add(int(x[0]))
            nm = g.names.get(v, "")
            if nm and not nm.startswith("@"):
                names.add(nm)
    return lines, names


def decl_moves(st, names):
    """Move the declaration of a diagnosed local (no initialiser) to every slot of the
    leading declaration block (locals are numbered in reverse declaration order)."""
    import shapesweep as ss
    a, b = ss.decl_front(st)
    for i in range(a, b):
        d = st.stmts[i]
        if len(d["vars"]) != 1 or d["vars"][0][3] is not None or d["vars"][0][0] not in names:
            continue
        for j in range(a, b):
            if j == i or j == i + 1:
                continue
            def f(i=i, j=j):
                s2 = st.clone()
                x = s2.stmts.pop(i)
                s2.stmts.insert(j if j < i else j - 1, x)
                return s2
            yield (f"declmove {d['vars'][0][0]}->{j - a}", f, i)
        # split a multi-var or initialised decl? (left to shapesweep's declswap)


# --------------------------------------------------------------------------
# rule inline-matched-sibling (tools/patterns/rules.jsonl), machine form:
# "named local X must be numbered above temp Y" -> move a statement run that
# holds X's whole live range into a static inline (its locals become inline
# temps, numbered above the caller's locals).

ID_RE = re.compile(r'(?<![\w.])(?<!->)\b([A-Za-z_]\w*)\b')
STR_RE = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')
WRITE_RE = r'(?:\b{n}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|\b{n}\s*(?:\+\+|--)|(?:\+\+|--)\s*{n}\b|&\s*{n}\b)'


def _ids(text):
    return ID_RE.findall(STR_RE.sub('""', text))


def _param_decls(sig):
    import shapesweep as ss
    out = {}
    for prm in ss.split_top(sig, ','):
        prm = re.sub(r'=.*', '', prm).strip()
        m = re.match(r'(.*?)([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)$', prm, re.S)
        if not m or not m.group(1).strip() or prm == 'void':
            continue
        out[m.group(2)] = m.group(1).strip() + ('*' if m.group(3) else '')
    return out


def extract_moves(st, sw, names, fn, maxn=24, focus=()):
    """Yield (label, f, si): stmts[i:j] -> `Helper(args);` + static inline Helper."""
    import shapesweep as ss
    L = [ss.render_stmt(s) for s in st.stmts]
    n = len(L)
    void = re.match(r'\s*(?:static\s+|inline\s+|extern\s+"C"\s+)*void\b', sw.head) is not None
    end = n
    while end > 0 and not L[end - 1].strip():
        end -= 1
    # brace depth before each statement
    dep, d = [], 0
    for t in L:
        dep.append(d)
        s = STR_RE.sub('""', t)
        d += s.count('{') - s.count('}')
    dep.append(d)
    params = _param_decls(sw.sig)
    decl_at = {}           # outer local name -> (stmt index, var index)
    for i, s in enumerate(st.stmts):
        if s['k'] == 'decl':
            for k, v in enumerate(s['vars']):
                decl_at.setdefault(v[0], (i, k))
    ids = [_ids(t) for t in L]

    def ok_range(i, j):
        if not (0 <= i < j <= n) or dep[i] != dep[j]:
            return False
        lo = dep[i]
        for k in range(i, j):
            if dep[k + 1] < lo:
                return False
        first = L[i].strip()
        if first.startswith(('else', '}', 'case', 'default')) or not first:
            return False
        if j < n and re.match(r'\s*(\}\s*)?else\b', L[j]):
            return False
        if i > 0:
            prev = L[i - 1].rstrip()
            if prev.strip() and not prev.endswith((';', '{', '}')):
                return False     # body of a brace-less if/for/else
        if L[j - 1].rstrip().endswith(')') or re.match(r'\s*else\s*$', L[j - 1]):
            return False
        txt = '\n'.join(L[i:j])
        w = set(_ids(txt))
        if w & {'break', 'continue', 'goto', 'case', 'default'} and not w & {'for', 'while', 'do', 'switch'}:
            return False
        if 'return' in w:
            if not (void and j >= end):
                return False
            if re.search(r'\breturn\s*[^;\s]', STR_RE.sub('""', txt)):
                return False
        return True

    seeds = []
    for nm in sorted(names):
        occ = [k for k in range(n) if nm in ids[k]]
        if not occ or nm in params:
            continue
        seeds.append((nm, occ[0], occ[-1] + 1))
    # no diagnosed named local: seed with the diagnosed statements (temps there)
    if not seeds and focus:
        fs = sorted(focus)
        seeds.append((f"L{fs[0]}", fs[0], fs[-1] + 1))
        for x in fs[:3]:
            seeds.append((f"L{x}", x, x + 1))
    tried = set()
    cnt = 0
    for nm, a0, b0 in seeds:
        cand = []
        for i in range(a0, -1, -1):
            for j in list(range(b0, min(n, b0 + 40) + 1)) + [end]:
                if ok_range(i, j):
                    cand.append((i, j))
            if len(cand) > 60:
                break
        # smallest ranges first, plus "to the end of the function / block"
        cand = sorted({(i, min(j, end) if j >= end else j) for i, j in cand if i < min(j, end)},
                      key=lambda r: (r[1] - r[0]))
        for i, j in cand:
            if (i, j) in tried:
                continue
            tried.add((i, j))
            for variant in ("plain", "argdecl"):
                f = _mk_extract(st, sw, L, ids, i, j, params, decl_at, fn, variant)
                if f is None:
                    continue
                yield (f"inline[{variant}] {nm}: stmts {i}..{j - 1}", f, i)
                cnt += 1
                if cnt >= maxn:
                    return


def _mk_extract(st, sw, L, ids, i, j, params, decl_at, fn, variant):
    import shapesweep as ss
    n = len(L)
    inner = set(x for k in range(i, j) for x in ids[k])
    after = set(x for k in range(j, n) for x in ids[k])
    before = set(x for k in range(0, i) for x in ids[k])
    txt = '\n'.join(L[i:j])
    plain_txt = STR_RE.sub('""', txt)
    # locals declared inside the range must not be used after it
    for k in range(i, j):
        s = st.stmts[k]
        if s['k'] == 'decl':
            for v in s['vars']:
                if v[0] in after:
                    return None
    outer = []
    moved = []          # outer decls without initialiser used only inside the range
    local = []          # outer locals written first in the range, dead after it
    for nm in sorted(inner, key=lambda x: plain_txt.find(x)):
        if nm in params:
            ty = params[nm]
        elif nm in decl_at and decl_at[nm][0] < i:
            di, vi = decl_at[nm]
            s = st.stmts[di]
            name, stars, arr, init = s['vars'][vi]
            if 'static' in s['ty'].split():
                continue
            only_here = nm not in after and sum(1 for k in range(0, i) if nm in ids[k]) == 1
            if only_here and init is None:
                moved.append(nm)
                continue
            m0 = re.search(r'\b' + re.escape(nm) + r'\b', plain_txt)
            if (nm not in after and not arr and
                    re.match(r'\s*=(?!=)', plain_txt[m0.end():])):
                local.append((nm, (s['ty'] + ' ' + stars).strip()))
                continue
            ty = s['ty'] + ' ' + stars + ('*' if arr else '')
        else:
            continue
        if nm in after and re.search(WRITE_RE.format(n=re.escape(nm)), plain_txt):
            return None          # value would be lost
        outer.append((nm, ty.strip()))
    body = list(L[i:j])
    args = [nm for nm, _ in outer]
    pdecl = [f"{ty} {nm}" for nm, ty in outer]
    if variant == "argdecl":
        # leading `T x = e;` of the range become parameters (argument e)
        k = i
        lead = []
        keepb = []
        while k < j and st.stmts[k]['k'] == 'decl' and len(st.stmts[k]['vars']) == 1:
            s = st.stmts[k]
            name, stars, arr, init = s['vars'][0]
            rest = '\n'.join(L[k + 1:j])
            if init is None and not arr:
                keepb.append(k)
                k += 1
                continue
            if init is None or arr or re.search(WRITE_RE.format(n=re.escape(name)), STR_RE.sub('""', rest)):
                break
            if set(_ids(ss.pr(init))) & {x[0] for x in lead}:
                break
            lead.append((name, (s['ty'] + ' ' + stars).strip(), ss.pr(init)))
            k += 1
        if not lead:
            return None
        body = [L[kk] for kk in keepb] + list(L[k:j])
        # parameters used only by the moved initialisers drop out
        rest_ids = set(x for kk in list(keepb) + list(range(k, j)) for x in ids[kk])
        keep = [(nm, ty) for nm, ty in outer if nm in rest_ids]
        args = [e for _, _, e in lead] + [nm for nm, _ in keep]
        pdecl = [f"{ty} {nm}" for nm, ty, _ in lead] + [f"{ty} {nm}" for nm, ty in keep]
    # re-indent the body one level in
    ind0 = st.stmts[i].get('ind') if st.stmts[i]['k'] != 'raw' else re.match(r'\s*', L[i]).group(0)
    ind0 = ind0 or ''
    mov_lines = []
    for nm in moved:
        di, vi = decl_at[nm]
        s = st.stmts[di]
        _, stars, arr, _ = s['vars'][vi]
        mov_lines.append(f"    {s['ty']} {stars}{nm}{arr};")
    for nm, ty in local:
        mov_lines.append(f"    {ty} {nm};")
    bl = [("    " + t[len(ind0):] if t.startswith(ind0) else t) for t in body]
    hname = f"{re.sub(r'[^A-Za-z0-9_]', '_', fn)}_Inl{i}_{j}"
    code = f"static inline void {hname}({', '.join(pdecl) or 'void'}) {{\n" + '\n'.join(mov_lines + bl) + "\n}"

    def f():
        s2 = st.clone()
        s2.helpers[hname] = ("void", code)
        s2.stmts[i:j] = [{'k': 'raw', 'text': f"{ind0}{hname}({', '.join(args)});"}]
        # drop moved declarations
        for nm in moved:
            di, vi = decl_at[nm]
            d = s2.stmts[di]
            d['vars'] = [v for v in d['vars'] if v[0] != nm]
        s2.stmts = [s for s in s2.stmts if not (s['k'] == 'decl' and not s['vars'])]
        return s2
    return f


BOOL_RE = re.compile(r'(?P<lhs>(?<![=!<>])=\s*)(?P<a>[^;=?&|]+?)\s*(?P<op>!=|==|<=|>=|<|>)\s*(?P<b>[^;=?&|]+?)\s*;')
TERN_RE = re.compile(r'(?P<lhs>(?<![=!<>])=\s*)(?P<a>[^;=?]+?)\s*\?\s*1\s*:\s*0\s*;')


def _boolnorm_text(t):
    """`x = a != 0;` <-> `x = a ? 1 : 0;` (and `(a op b) ? 1 : 0` for other comparisons)."""
    out = []
    for m in BOOL_RE.finditer(t):
        a, op, b = m.group('a').strip(), m.group('op'), m.group('b').strip()
        if op == '!=' and b == '0':
            new = f"{a} ? 1 : 0;"
        elif op == '==' and b == '0':
            new = f"!({a}) ? 1 : 0;" if not re.fullmatch(r'[\w.\->\[\]]+', a) else f"!{a} ? 1 : 0;"
        else:
            new = f"({a} {op} {b}) ? 1 : 0;"
        out.append(t[:m.start()] + m.group('lhs') + new + t[m.end():])
    for m in TERN_RE.finditer(t):
        out.append(t[:m.start()] + m.group('lhs') + f"{m.group('a').strip()} != 0;" + t[m.end():])
    return out


def boolnorm_moves(st, focus):
    """bool-valued assignment shape (rule expr-shape): in the caller's statements
    on diagnosed lines and anywhere in extracted helpers."""
    import shapesweep as ss
    for si, s in enumerate(st.stmts):
        if s['k'] not in ('expr', 'decl') or si not in focus:
            continue
        for k, t2 in enumerate(_boolnorm_text(ss.render_stmt(s))):
            def f(si=si, t2=t2):
                s2 = st.clone()
                s2.stmts[si] = {'k': 'raw', 'text': t2}
                return s2
            yield (f"boolnorm stmt {si}#{k}", f, si)
    for name, (ty, code) in st.helpers.items():
        if "_Inl" not in name:
            continue
        for k, c2 in enumerate(_boolnorm_text(code)):
            def f(name=name, ty=ty, c2=c2):
                s2 = st.clone()
                s2.helpers[name] = (ty, c2)
                return s2
            yield (f"boolnorm {name}#{k}", f, None)


# --------------------------------------------------------------------------
# rule one-named-local-per-def (tools/patterns/rules.jsonl), machine form:
# expand a `VoidInline(args);` statement in place. The inline's locals become
# caller locals (same name + type: reuse; otherwise one fresh named local per
# expansion: c, c2, ...), initialisers become assignments in place, params are
# substituted by the arguments. The decl-order solver then orders the new
# named locals.

VOID_INL = re.compile(r'(?:static\s+)?inline\s+void\s+([A-Za-z_]\w*)\s*\(([^)]*)\)\s*\{')


def void_inlines(text):
    import shapesweep as ss
    out = {}
    for m in VOID_INL.finditer(text):
        b = m.end()
        e = ss.brace_end(text, b)
        body = text[b:e - 1]
        if re.search(r'\breturn\b', body):
            continue
        params = []
        for p in ss.split_top(m.group(2), ','):
            p = p.strip()
            if not p or p == 'void':
                continue
            mm = re.match(r'(.*?)([A-Za-z_]\w*)\s*$', p, re.S)
            if not mm:
                params = None
                break
            params.append((mm.group(1).strip(), mm.group(2)))
        if params is not None:
            out[m.group(1)] = (params, body)
    return out


def _subst(text, mp):
    if not mp:
        return text
    pat = re.compile(r'(?<![\w.])(?<!->)\b(' + '|'.join(map(re.escape, mp)) + r')\b')
    parts = re.split(r'("(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')', text)
    return ''.join(p if k % 2 else pat.sub(lambda m: mp[m.group(1)], p) for k, p in enumerate(parts))


def expand_moves(st, sw, VI):
    import shapesweep as ss
    if not VI:
        return
    L = [ss.render_stmt(s) for s in st.stmts]
    for si, t in enumerate(L):
        m = re.match(r'^(\s*)([A-Za-z_]\w*)\s*\((.*)\);\s*$', t)
        if not m or m.group(2) not in VI:
            continue
        for share in ("loop", "all", "none"):
            f = _mk_expand(st, sw, L, si, m, VI[m.group(2)], share)
            if f:
                yield (f"expand-void {m.group(2)}@{si} share={share}", f, si)


def _mk_expand(st, sw, L, si, m, inl, share):
    import shapesweep as ss
    params, body = inl
    args = [x.strip() for x in ss.split_top(m.group(3), ',')] if m.group(3).strip() else []
    if len(args) != len(params):
        return None
    ind = m.group(1)
    callers = {}           # caller local name -> type text
    for s in st.stmts:
        if s['k'] == 'decl':
            for v in s['vars']:
                callers[v[0]] = (s['ty'] + ' ' + v[1]).strip()
    for ty, nm in _param_decls(sw.sig).items():
        callers[ty] = nm
    used = set(_ids('\n'.join(L)))
    mp = {}
    for (pty, pn), arg in zip(params, args):
        mp[pn] = arg if re.fullmatch(r'[\w.\->]+|-?\d+[uUlL]*|0x[0-9a-fA-F]+[uUlL]*', arg) else f"({arg})"
    blines = [l for l in body.split('\n') if l.strip()]
    bst = ss.parse_body('\n'.join(blines), sw.ti.types)
    loopv = {x for l in blines if re.match(r'\s*for\s*\(', l) for x in _ids(l)}
    new_decls, out = [], []
    ren = {}
    # top-level declarations of the inline body (first indentation level)
    base = min((len(s.get('ind', '')) for s in bst if s['k'] != 'raw'), default=0)
    for s in bst:
        if s['k'] == 'decl' and len(s['ind']) == base:
            for name, stars, arr, init in s['vars']:
                ty = (s['ty'] + ' ' + stars).strip()
                ok = share == "all" or (share == "loop" and name in loopv)
                if ok and name in callers and callers[name].replace(' ', '') == ty.replace(' ', '') and not arr:
                    nn = name
                else:
                    nn, k = name, 2
                    while nn in used or nn in callers:
                        nn = f"{name}{k}"
                        k += 1
                    new_decls.append({'k': 'decl', 'ind': st.stmts[0].get('ind', '    ') if st.stmts else '    ',
                                      'ty': s['ty'], 'vars': [[nn, stars, arr, None]]})
                    used.add(nn)
                if nn != name:
                    ren[name] = nn
                if init is not None:
                    out.append(('asg', nn, ss.pr(init)))
            continue
        out.append(('stmt', s))
    mp2 = dict(mp)
    mp2.update(ren)
    lines = []
    for kind, *x in out:
        if kind == 'asg':
            lines.append(f"{ind}{x[0]} = {_subst(x[1], mp2)};")
        else:
            s = x[0]
            t = ss.render_stmt(s)
            t = t[base:] if t[:base].strip() == '' else t.lstrip()
            lines.append(ind + _subst(t, mp2))

    def f():
        s2 = st.clone()
        a, b = __import__('shapesweep').decl_front(s2)
        txt = '\n'.join(ss.render_stmt(x) for x in s2.stmts[:si]) + '\n' + '\n'.join(lines) + '\n' + \
            '\n'.join(ss.render_stmt(x) for x in s2.stmts[si + 1:])
        nb = ss.parse_body(txt, sw.ti.types)
        a2, b2 = ss.decl_front(State_like(nb))
        s2.stmts = nb[:b2] + new_decls + nb[b2:]
        return s2
    return f


class State_like:
    def __init__(self, stmts):
        self.stmts = stmts


# --------------------------------------------------------------------------
# "un-name" a local (SpecialFaceMesh_Dtor 9e7c73b, TripleBladeRing a34ac4b):
# a local whose every assignment stores the same side-effect-free expression E
# (global, literal, member chain) is replaced by E everywhere, so the value
# becomes a backend temp; usually paired with a pragma pseudo-move.

PURE_RE = re.compile(r'^[\w.\->\[\] ]+$')


def unname_moves(st, sw, single=False):
    import shapesweep as ss
    cands = [] if not single else None
    L = [ss.render_stmt(s) for s in st.stmts]
    txt = '\n'.join(L)
    plain = STR_RE.sub('""', txt)
    names = []
    for s in st.stmts:
        if s['k'] == 'decl':
            for v in s['vars']:
                if not v[2]:
                    names.append(v[0])
    for nm in names:
        en = re.escape(nm)
        if re.search(r'(?:\+\+|--)\s*' + en + r'\b|\b' + en + r'\s*(?:\+\+|--|[-+*/%&|^]=|<<=|>>=)|&\s*' + en + r'\b', plain):
            continue
        rhs = set(x.strip() for x in re.findall(r'(?<![\w.])(?<!->)\b' + en + r'\s*=(?!=)\s*([^;),]+)', plain))
        if len(rhs) != 1:
            continue
        E = rhs.pop()
        if not PURE_RE.match(E) or re.search(r'\b' + en + r'\b', E):
            continue

        def f(nm=nm, E=E, en=en):
            out = []
            for t in L:
                if re.match(r'^\s*' + en + r'\s*=(?!=)[^;]*;\s*$', t):
                    continue        # plain `x = E;`
                t = re.sub(r'\(\s*' + en + r'\s*=(?!=)\s*' + re.escape(E) + r'\s*\)', E, t)
                out.append(t)
            body = '\n'.join(out)
            body = _subst(body, {nm: E})
            nb = ss.parse_body(body, sw.ti.types)
            # drop the declaration (now `T E;` or `T E = E;`) -- rebuild from st
            s2 = st.clone()
            res = []
            for x in nb:
                if x['k'] == 'decl':
                    x['vars'] = [v for v in x['vars'] if v[0] != E.strip()]
                    if not x['vars']:
                        continue
                res.append(x)
            s2.stmts = res
            return s2
        if cands is not None:
            cands.append(nm)
        yield (f"unname {nm}={E}", f, None)
    if cands and len(cands) > 1:
        def g():
            s2 = st
            for nm in cands:
                m = [x for x in unname_moves(s2, sw, single=True) if x[0].startswith(f"unname {nm}=")]
                if m:
                    s2 = m[0][1]()
            return s2
        yield (f"unname-all {','.join(cands)}", g, None)


def apply_decl_order(st, order):
    """New State with the leading declarations in `order` (names first declared
    first; others keep their place in front). Initialisers become assignments
    right after the declaration block, in their original order."""
    import shapesweep as ss
    a, b = ss.decl_front(st)
    s2 = st.clone()
    decls, inits = [], []
    for d in s2.stmts[a:b]:
        for var in d["vars"]:
            name, stars, arr, init = var
            if init is not None:
                if arr or "const" in d["ty"].split():
                    return None
                inits.append({"k": "expr", "ind": d["ind"],
                              "e": ss.N("asg", op="=", kids=[ss.N("atom", t=name), init])})
            decls.append({"k": "decl", "ind": d["ind"], "ty": d["ty"], "vars": [[name, stars, arr, None]]})
    rank = {n: i for i, n in enumerate(order)}
    rest = [d for d in decls if d["vars"][0][0] not in rank]
    mine = sorted([d for d in decls if d["vars"][0][0] in rank], key=lambda d: rank[d["vars"][0][0]])
    s2.stmts[a:b] = rest + mine + inits
    return s2


def fix(a, rep0):
    import shapesweep as ss
    import pragmasweep as ps
    from concurrent.futures import ThreadPoolExecutor
    ns = argparse.Namespace(unit=a.unit, fn=a.fn, demangled=None, start=a.start, start_tu=a.start_tu,
                            pragma=a.pragma, cc=a.cc, moves=None)
    sw = ss.Sweep(ns)
    if a.objdiff:
        ps.OBJDIFF = True
        a.slack *= 10
    ev = Evaluator(sw, sw.sym or a.fn, a.jobs, a.fn)
    print(f"[regfix] parallel debugger: {'yes (native gdb)' if md.NATIVE else 'yes (netns)' if ev.par else 'no (unshare failed)'}", flush=True)
    allowed = set(ss.REG_ONLY_MOVES) | {"expand", "swap"}
    t0 = time.time()
    PROP = "opt_propagation off"
    # pragma pseudo-moves: label -> pragma. propagation off keeps named locals;
    # strength_reduction / common_subs off stop the backend temps the target
    # does not have (SpecialFaceMesh_Dtor 9e7c73b, TripleBladeRing a34ac4b),
    # usually after un-naming a local (unvar) or a plain-loop rewrite.
    PRAGMA_MOVES = {"propoff": PROP, "pragma-sr": "opt_strength_reduction off",
                    "pragma-cse": "opt_common_subs off", "pragma-lifetimes": "opt_lifetimes off"}

    def prag(st):
        return tuple(getattr(st, "pragmas", ()))

    def rend(st):
        """render with the state's pseudo-move pragmas pushed around the function."""
        extra = [p for p in prag(st) if p not in (a.pragma or [])]
        if extra:
            old = sw.a.pragma
            sw.a.pragma = list(old or []) + extra
            try:
                return sw.render(st)
            finally:
                sw.a.pragma = old
        return sw.render(st)

    def pragma_moves(st):
        for label, p in PRAGMA_MOVES.items():
            if p in prag(st) or p in (a.pragma or []):
                continue

            def f(p=p):
                s2 = st.clone()
                s2.pragmas = prag(st) + (p,)
                return s2
            yield (label, f, None)
    VI = void_inlines(sw.text[:sw.d[0]])
    text0 = rend(sw.init)
    s0 = sw.score(text0, 0)
    m0, r0 = ev.diag(text0, 0, top_decls(sw.init))
    print(f"[regfix] start: {s0} diff lines, metric {m0}", flush=True)
    if s0 == 0:
        print("[regfix] already matching", flush=True)
        return ((0, 0, 0, 0), 0, sw.init, text0, None)

    def try_decl(st, rep):
        if not rep or not rep.get("decl_order"):
            return None
        s2 = apply_decl_order(st, rep["decl_order"])
        if s2 is None:
            return None
        s2.hist = st.hist + ("declorder " + ",".join(rep["decl_order"]),)
        s2.pragmas = prag(st)
        t = rend(s2)
        sc = sw.score(t, 0)
        print(f"[regfix] decl-order solver proposes {rep['decl_order']}: {sc} diff lines", flush=True)
        return (s2, t) if sc == 0 else None

    def done(s2, t):
        out = TMPDIR / f"{a.fn}.match{sw.u.ext}"
        out.write_text(t)
        print(f"[regfix] MATCH via {' | '.join(s2.hist)}; full TU written to {out}", flush=True)
        if not getattr(a, "no_log", False):
            log_hit(a.fn, a.unit, s2.hist, s0)
        return ((0, 0, 0, 0), 0, s2, t, None)
    h0 = try_decl(sw.init, r0)
    if h0:
        return done(*h0)
    beam = [(m0, s0, sw.init, text0, r0)]
    best = beam[0]
    bestl = (s0, sw.init)      # fewest diff lines seen (may differ from the metric-best)
    seen = {hashlib.sha1(text0.encode()).hexdigest()}
    log = open(TMPDIR / f"{a.fn}.log.jsonl", "a")
    for rnd in range(a.rounds):
        cands = []
        for m, s, st, txt, rep in beam:
            lines, names = focus_of(rep)
            sl = sw.stmt_lines(st)
            foc = {i for i, l in enumerate(sl) if l in lines}
            extra = list(pragma_moves(st))
            ext = extract_moves(st, sw, names, a.fn, focus=foc) if not a.no_inline else ()
            for label, f, si in itertools.chain(extra, ext, expand_moves(st, sw, VI), unname_moves(st, sw), boolnorm_moves(st, foc),
                                                decl_moves(st, names),
                                                ss.moves(st, sw.ctx, allowed)):
                pri = 0 if (si in foc or label.startswith(("declmove", "propoff", "pragma-", "inline", "boolnorm", "expand-void", "unname"))) else 1
                if pri == 1 and a.focus_only:
                    continue
                cands.append((pri, len(cands), st, label, f))
        cands.sort(key=lambda c: c[:2])
        new = []
        for pri, _, st, label, f in cands:
            if len(new) >= a.sample:
                break
            try:
                s2 = f()
            except Exception:
                continue
            if s2 is None:
                continue
            s2.hist = st.hist + (label,)
            if label not in PRAGMA_MOVES:
                s2.pragmas = prag(st)
            txt = rend(s2)
            h = hashlib.sha1(txt.encode()).hexdigest()
            if h in seen:
                continue
            seen.add(h)
            new.append((s2, txt))
        if not new:
            print("[regfix] no new variants", flush=True)
            break
        with ThreadPoolExecutor(a.jobs, initializer=ps._init_worker) as ex:
            sc = list(ex.map(lambda it: sw.score(it[1], ps.worker_id()), new))
        hit = [(s2, t) for (s2, t), x in zip(new, sc) if x == 0]
        if hit:
            return done(*hit[0])
        # debugger on the best-scored few (diff lines within slack of the best)
        order = sorted(range(len(new)), key=lambda i: sc[i])
        lim = min(sc) + a.slack
        pick = [i for i in order if sc[i] <= lim][:a.dbg]
        # catalog-rule rewrites usually only pay off after the decl-order
        # solver: always diagnose a few of them whatever their score
        RULE = ("expand", "inline[", "boolnorm", "pragma-", "propoff", "unname")
        pick += [i for i in order if i not in pick and new[i][0].hist[-1].startswith(RULE)][:a.dbg]
        with ThreadPoolExecutor(a.jobs if ev.par else 1) as ex:
            res = list(ex.map(lambda k: ev.diag(new[pick[k]][1], k, top_decls(new[pick[k]][0])), range(len(pick))))
        for k, (m, rep) in zip(pick, res):
            h1 = try_decl(new[k][0], rep)
            if h1:
                return done(*h1)
        pool = list(beam)
        for k in range(len(new)):
            if sc[k] < bestl[0]:
                bestl = (sc[k], new[k][0])
        for k, (m, rep) in zip(pick, res):
            pool.append((m, sc[k], new[k][0], new[k][1], rep))
            log.write(json.dumps({"fn": a.fn, "score": sc[k], "metric": m, "hist": list(new[k][0].hist)}) + "\n")
        log.flush()
        # ties: keep catalog-rule states (inline / expand / unname / boolnorm) in the
        # beam, their payoff usually needs a follow-up move
        pool.sort(key=lambda r: (r[0], r[1], 0 if any(h.startswith(("inline[", "expand", "unname", "boolnorm"))
                                                       for h in r[2].hist) else 1, len(r[2].hist)))
        uniq, seen_t = [], set()
        for r in pool:
            if r[3] not in seen_t:
                seen_t.add(r[3])
                uniq.append(r)
        beam = uniq[:a.beam]
        if (beam[0][0], beam[0][1]) < (best[0], best[1]):
            best = beam[0]
        print(f"[regfix] round {rnd + 1}: {len(new)} variants, {len(pick)} diagnosed; best {best[1]} lines metric {best[0]} "
              f"({time.time() - t0:.0f}s) via {' | '.join(best[2].hist) or '-'}", flush=True)
        if a.minutes and time.time() - t0 > a.minutes * 60:
            break
    out = TMPDIR / f"{a.fn}.best{sw.u.ext}"
    pp = prag(best[2])
    out.write_text(("#pragma push\n" + "".join(f"#pragma {p}\n" for p in pp) if pp else "")
                   + sw.func_text(best[2]) + ("\n#pragma pop\n" if pp else ""))
    pcs = objdiff_pcts(sw, [text0, rend(best[2]), rend(bestl[1])], a.jobs)
    print(f"[regfix] objdiff: start {pcs[0]}, best {pcs[1]}, fewest-lines {pcs[2]}")
    print(f"[regfix] best: {best[1]} {'objdiff units' if a.objdiff else 'diff lines'}, metric {best[0]}; definition written to {out}")
    if bestl[0] < best[1]:
        o2 = TMPDIR / f"{a.fn}.fewest{sw.u.ext}"
        pp = prag(bestl[1])
        o2.write_text(("#pragma push\n" + "".join(f"#pragma {p}\n" for p in pp) if pp else "")
                      + sw.func_text(bestl[1]) + ("\n#pragma pop\n" if pp else ""))
        print(f"[regfix] fewest diff lines: {bestl[0]} via {' | '.join(bestl[1].hist)}; written to {o2}")
    return best


def print_levers(a, rep, src_text, d, ext):
    """Hand-landed source levers whose shape fits (tools/diag2sweep.levers)."""
    try:
        import diag2sweep as d2s
        import pragmasweep as ps
        u = ps.Unit(a.unit)
        tf = Path(d) / "trace.txt"
        tl = tf.read_text(errors="replace").splitlines() if tf.exists() else []
        lv = d2s.levers(src_text, a.fn, rep, tl, lambda t, f: ps.find_def(t, f, mangled=u.compiled_name(f)),
                        ext in (".cpp", ".cp", ".cc"))
    except Exception as e:  # noqa: BLE001 - advice only
        print(f"[regfix] levers: {e}")
        return []
    if lv:
        print("\n== source levers that fit this function's shape ==")
        for rid, text in lv:
            print(f"  [{rid}] {text}")
        print("  (try them together with:  regfix diag ... --tracesweep --run)")
    return lv


def emit_tracesweep(a, rep, src_text, d: Path, ext):
    """diag -> tracesweep template + --want (tools/diag2sweep.py); --run runs it."""
    import diag2sweep as d2s
    import pragmasweep as ps
    tf = Path(d) / "trace.txt"
    if not rep or rep.get("not_reg_only"):
        print("\n== tracesweep: not a register-only diff, nothing generated ==")
        return None
    if not tf.exists():
        print("\n== tracesweep: needs the native trace (sh tools/install_mweppc.sh --build) ==")
        return None
    u = ps.Unit(a.unit)
    g = d2s.generate(src_text, a.fn, rep, tf.read_text(errors="replace").splitlines(),
                     lambda t, f: ps.find_def(t, f, mangled=u.compiled_name(f)), ext in (".cpp", ".cp", ".cc"))
    if not g:
        print("\n== tracesweep: no diag solution / definition found, nothing generated ==")
        return None
    TMPDIR.mkdir(parents=True, exist_ok=True)
    path = TMPDIR / f"{a.fn}.diag.tmpl"
    head = f"// unit: {a.unit}\n// fn: {a.fn}\n" + (f"// want: {g['want']}\n" if g["want"] else "")
    head += "".join(f"// note: {n}\n" for n in g["notes"])
    path.write_text(head + g["template"])
    print(f"\n== tracesweep template (diag lines {g['lines']}): {path} ==")
    for n in g["notes"]:
        print("   " + n)
    print(f"   want: {g['want']}")
    print(f"   run: python3 tools/tracesweep.py run {a.unit} {a.fn} {path}")
    if getattr(a, "run", False):
        import tracesweep as ts
        res, axes = ts.run(a.unit, a.fn, ts.strip_header(path.read_text()), g["want"], a.jobs,
                           sample=a.sample, confirm=3, show=10, log_name=f"{a.fn}.diag",
                           base_text=src_text if getattr(a, "start_tu", None) else None)
        g["best"] = res[0] if res else None
    return g


def suggest_rules(unit, fn, n=4):
    """Top rewrite rules from the shared catalog (tools/rewrite_rules.py, catalog thread)."""
    rr = ROOT / "tools" / "rewrite_rules.py"
    if not rr.exists():
        return
    r = md.sh([sys.executable, "-I", str(rr), "suggest", unit, fn], cwd=ROOT)
    rows = [l for l in r.stdout.splitlines() if re.match(r"^\s*\d+\.\d+\s", l)]
    if rows:
        print("\n== catalog rules that fit (tools/patterns/rules.jsonl) ==")
        for l in rows[:n]:
            print("  " + l.strip())


def log_hit(fn, unit, hist, before):
    """Record a match in the shared hit log (rewrite_rules.record_hit)."""
    try:
        import rewrite_rules
    except ImportError:
        return
    kinds = {h.split()[0] for h in hist}
    rule = ("inline-matched-sibling" if any(k.startswith("inline[") for k in kinds) else
            "one-named-local-per-def" if kinds & {"expand-void", "expand"} else
            "unname-pragma" if any(k.startswith("unname") for k in kinds) else
            "regfix-declorder" if "declorder" in kinds else "regfix-" + "+".join(sorted(kinds)))
    try:
        rewrite_rules.record_hit(fn, unit, rule, "regfix", before, 0, note=" | ".join(hist)[:300])
    except Exception as e:  # never fail a match on logging
        print(f"[regfix] hit log failed: {e}", file=sys.stderr)


def cmd_batch(a):
    """diag every `unit fn` line of a.list (current sources; --best-dir FILEs
    named FN_* are used as start TUs), run the decl-order solver, and verify
    proposals by compiling. One jsonl row per fn in a.out."""
    import shapesweep as ss
    import pragmasweep as ps
    from concurrent.futures import ThreadPoolExecutor
    rows = [l.split() for l in open(a.list) if l.strip() and not l.startswith("#")]
    claims = set()
    if a.claims:
        claims = {l.strip().replace("src/", "").rsplit(".", 1)[0] for l in open(a.claims) if l.strip()}
    rep = json.load(open(ROOT / f"build/{md.VERSION}/report.json"))
    pct = {}
    for u in rep["units"]:
        for f in u.get("functions", []):
            pct[f["name"]] = f.get("fuzzy_match_percent", 0)
    done = set()
    if os.path.exists(a.out) and not a.retry:
        done = {json.loads(l)["fn"] for l in open(a.out) if l.strip()}
    todo = [(u, f) for u, f in rows if f not in done and u not in claims and pct.get(f, 0) < 100]
    print(f"[regfix batch] {len(todo)} functions", flush=True)
    outf = open(a.out, "a")
    import threading
    lock = threading.Lock()
    slots = iter(range(10**6))

    def one(item):
        unit, fn = item
        slot = next(slots)
        row = {"unit": unit, "fn": fn, "pct": pct.get(fn)}
        try:
            start = None
            if a.best_dir:
                c = sorted(glob.glob(os.path.join(a.best_dir, fn + "_*")))
                start = c[0] if c else None
            cc = None
            if start:
                m = re.search(r"_GC([\d.]+[a-z]?)\.c", start)
                cc = m.group(1) if m else None
            with lock:
                sw = ss.Sweep(argparse.Namespace(unit=unit, fn=fn, demangled=None, start=None, start_tu=start,
                                                 pragma=None, cc=cc, moves=None))
            ev = Evaluator(sw, sw.sym or fn, 1, fn)
            text = sw.render(sw.init)
            s0 = sw.score(text, slot % 8)
            row.update(start=start, score=s0)
            if s0 == 0:
                row["outcome"] = "already"
            else:
                m, r = ev.diag(text, f"b{slot}", top_decls(sw.init))
                row["metric"] = m
                if r:
                    row["bad"] = {rc: c["bad"] for rc, c in r["classes"].items()}
                    row["decl_order"] = r.get("decl_order")
                    hits = []
                    for rc, c in r["classes"].items():
                        for es, _ in c.get("sols", []):
                            hits.append([e.text(c["g"], r["sites"]) for e in es])
                    row["edits"] = hits[:3]
                    if r.get("decl_order"):
                        st = apply_decl_order(sw.init, r["decl_order"])
                        if st is not None:
                            t2 = sw.render(st)
                            s2 = sw.score(t2, slot % 8)
                            row["decl_score"] = s2
                            if s2 == 0:
                                p = Path(a.hits) / f"{fn}{sw.u.ext}"
                                p.parent.mkdir(parents=True, exist_ok=True)
                                p.write_text(t2)
                                row["outcome"] = "MATCH"
                                row["file"] = str(p)
                                log_hit(fn, unit, ("declorder",), s0)
                row.setdefault("outcome", "nomatch")
        except BaseException as e:
            row["outcome"] = f"error: {type(e).__name__}: {e}"[:200]
        with lock:
            outf.write(json.dumps(row) + "\n")
            outf.flush()
            print(f"[regfix batch] {fn}: {row['outcome']} score={row.get('score')} metric={row.get('metric')} "
                  f"decl={row.get('decl_order') is not None} decl_score={row.get('decl_score')}", flush=True)
        return row
    with ThreadPoolExecutor(a.jobs, initializer=ps._init_worker) as ex:
        list(ex.map(one, todo))


PROBE_PRAGMAS = ["opt_propagation off", "opt_strength_reduction off", "opt_common_subs off",
                 "opt_lifetimes off", "opt_dead_assignments off", "opt_loop_invariants off"]


def objdiff_pcts(sw, texts, jobs=4):
    """objdiff fuzzy match % per TU text (as strings), next to the diff-line
    metric: fewer differing lines does not always mean a higher % (fn_802386E0)."""
    import pragmasweep as ps
    from concurrent.futures import ThreadPoolExecutor
    if not os.path.exists(ps.OBJDIFF_CLI):
        return ["n/a"] * len(texts)
    old = ps.OBJDIFF
    ps.OBJDIFF = True
    try:
        with ThreadPoolExecutor(jobs, initializer=ps._init_worker) as ex:
            r = list(ex.map(lambda t: sw.u.compile_score(t, sw.a.fn, sw.cc, 100 + ps.worker_id()), texts))
    finally:
        ps.OBJDIFF = old
    return ["fail" if x >= 10**6 else f"{100 - x / 100:.2f}%" for x in r]


def cmd_probe(a):
    """One compile per lever that hand landings used on register-only diffs, so
    the person rewriting sees which levers move the registers at all:
    each pragma, un-naming locals (+ each pragma), each void-inline expansion,
    each inline-call expansion, and the decl-order solver's proposal."""
    import shapesweep as ss
    import pragmasweep as ps
    from concurrent.futures import ThreadPoolExecutor
    sw = ss.Sweep(argparse.Namespace(unit=a.unit, fn=a.fn, demangled=None, start=a.start, start_tu=a.start_tu,
                                     pragma=a.pragma, cc=a.cc, moves=None))

    def rend(st, prag=()):
        old = sw.a.pragma
        sw.a.pragma = list(old or []) + [p for p in prag if p not in (old or [])]
        try:
            return sw.render(st)
        finally:
            sw.a.pragma = old
    base = sw.init
    variants = [("start", base, ())]
    for p in PROBE_PRAGMAS:
        variants.append((f"#pragma {p}", base, (p,)))
    un = [(l, f) for l, f, _ in unname_moves(base, sw)]
    for l, f in un:
        if l.startswith("unname-all") or len(un) == 1:
            st = f()
            variants.append((l, st, ()))
            for p in PROBE_PRAGMAS[:4]:
                variants.append((f"{l} + #pragma {p}", st, (p,)))
    for l, f, _ in expand_moves(base, sw, void_inlines(sw.text[:sw.d[0]])):
        variants.append((l, f(), ()))
    for l, f, _ in ss.moves(base, sw.ctx, {"expand"}):
        if l.startswith("expand"):
            try:
                st = f()
            except Exception:
                continue
            if st is not None:
                variants.append((l, st, ()))
    texts = [rend(st, pr) for _, st, pr in variants]
    # __restrict on pointer parameters (fn_8019EB9C fa1d62e, rule restrict-input-ptrs):
    # the scheduler keeps a load after a store only when they may alias
    ptrs = [n for n, t in _param_decls(sw.sig).items() if "*" in t and "__restrict" not in t]
    head0 = sw.head
    sets = [(n,) for n in ptrs] + ([tuple(ptrs)] if len(ptrs) > 1 else [])
    if 2 < len(ptrs) <= 4:
        sets += list(itertools.combinations(ptrs, 2))
    for ns in sets:
        h = head0
        for n in ns:
            h = re.sub(r'\*\s*' + re.escape(n) + r'\b(?=\s*[,)\[])', '*__restrict ' + n, h, count=1)
        if h == head0:
            continue
        sw.head = h
        try:
            variants.append((f"__restrict {','.join(ns)}", base, ()))
            texts.append(rend(base))
        finally:
            sw.head = head0
    with ThreadPoolExecutor(a.jobs, initializer=ps._init_worker) as ex:
        sc = list(ex.map(lambda t: sw.score(t, ps.worker_id()), texts))
    pct = objdiff_pcts(sw, texts, a.jobs)
    s0 = sc[0]
    print(f"{a.fn}: start {s0} diff lines / objdiff {pct[0]}; one compile per lever "
          f"(sorted by objdiff %, which the progress report counts; lines: 0 = match)")
    def pkey(r):
        try:
            return (-float(r[2].rstrip("%")), r[1])
        except ValueError:
            return (1, r[1])
    for (l, _, _), x, pc in sorted(zip(variants, sc, pct), key=pkey):
        mark = "MATCH" if x == 0 else ("better" if x < s0 else ("same" if x == s0 else "worse"))
        print(f"  {x:>6}  {pc:>7}  {mark:<6}  {l}")
    if not a.no_dbg:
        ev = Evaluator(sw, sw.sym or a.fn, 1, a.fn)
        # the solver on the start and on every structural lever: those often
        # only pay off after re-ordering the declarations
        best = [r for r in zip(variants, sc, texts) if not r[0][0].startswith("#pragma")][:8]
        for (l, st, pr), x, t in best:
            if x >= 10**6 or x == 0:
                continue
            m, rep = ev.diag(t, f"probe{abs(hash(l)) % 1000}", top_decls(st))
            dor = rep.get("decl_order") if rep else None
            if dor:
                s2 = apply_decl_order(st, dor)
                if s2 is not None:
                    y = sw.score(rend(s2, pr), 0)
                    print(f"  decl-order solver on [{l}]: {dor} -> {y} diff lines")
                    continue
            print(f"  decl-order solver on [{l}]: no order (metric {m})")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("diag", "fix"):
        p = sub.add_parser(name)
        p.add_argument("unit")
        p.add_argument("fn", help="symbol (mangled for C++)")
        p.add_argument("--no-run", action="store_true", help="reuse the last dumps")
        p.add_argument("--depth", type=int, default=2)
        p.add_argument("--start", help="replacement definition to start from")
        p.add_argument("--start-tu", help="full TU source to start from")
        p.add_argument("--pragma", action="append")
        p.add_argument("--cc")
        if name == "diag":
            p.add_argument("--tracesweep", action="store_true",
                           help="write a tracesweep template + --want from the diag solutions (tools/diag2sweep.py)")
            p.add_argument("--run", action="store_true", help="with --tracesweep: run it (native compiles)")
            p.add_argument("--sample", type=int, default=3000, help="with --run: max variants")
            p.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
        p.add_argument("--sched", action="store_true",
                       help="trace the real scheduler too and explain order differences (GC/2.6; tools/mwsched.py)")
        if name == "fix":
            p.add_argument("--rounds", type=int, default=8)
            p.add_argument("--beam", type=int, default=4)
            p.add_argument("--sample", type=int, default=150, help="variants compiled per round")
            p.add_argument("--dbg", type=int, default=8, help="variants diagnosed per round")
            p.add_argument("--slack", type=int, default=6, help="diff-line slack for the diagnosed set")
            p.add_argument("--focus-only", action="store_true", help="only moves on diagnosed lines/locals")
            p.add_argument("--no-inline", action="store_true", help="no extract-to-static-inline moves")
            p.add_argument("--no-log", action="store_true", help="do not record a match in tools/patterns/hits.jsonl (replays)")
            p.add_argument("--objdiff", action="store_true",
                           help="rank variants by objdiff fuzzy %% ((100-%%)*100) instead of diff lines")
            p.add_argument("--minutes", type=float, default=0)
            p.add_argument("-j", "--jobs", type=int, default=4)
    pr = sub.add_parser("probe", help="one compile per known lever (pragmas, unname, inline expansion, decl order)")
    pr.add_argument("unit")
    pr.add_argument("fn")
    pr.add_argument("--start")
    pr.add_argument("--start-tu")
    pr.add_argument("--pragma", action="append")
    pr.add_argument("--cc")
    pr.add_argument("--no-dbg", action="store_true", help="skip the decl-order solver (needs mwccdbg)")
    pr.add_argument("-j", "--jobs", type=int, default=4)
    b = sub.add_parser("batch")
    b.add_argument("list", help="file of `unit fn` lines")
    sweeps = ROOT / "docs" / "sweeps"   # in the repo: commit results/hits
    b.add_argument("--best-dir", default=str(sweeps / "autopipe99" / "best"))
    b.add_argument("--claims")
    b.add_argument("--out", default=str(sweeps / "regfix" / "results.jsonl"))
    b.add_argument("--hits", default=str(sweeps / "regfix" / "hits"))
    b.add_argument("--retry", action="store_true")
    b.add_argument("-j", "--jobs", type=int, default=4)
    a = ap.parse_args()
    if a.cmd == "batch":
        return cmd_batch(a)
    if a.cmd == "probe":
        return cmd_probe(a)
    out = md.DBG_DIR / "out" / a.fn
    out.mkdir(parents=True, exist_ok=True)
    if a.cmd == "diag" and (a.start or a.start_tu):
        import shapesweep as ss
        sw = ss.Sweep(argparse.Namespace(unit=a.unit, fn=a.fn, demangled=None, start=a.start,
                                         start_tu=a.start_tu, pragma=a.pragma, cc=a.cc, moves=None))
        ev = Evaluator(sw, sw.sym or a.fn, 1, a.fn)
        d = ev.run(sw.render(sw.init), "diag")
        print(f"[regfix] score {sw.score(sw.render(sw.init), 0)} diff lines")
        if a.sched:
            # traced rerun of the same source (fixed gdb port: not in the netns pool)
            tsrc = Path(sw.u.src).with_name(f".regfix_sched_{os.getpid()}{sw.u.ext}")
            tsrc.write_text(sw.render(sw.init))
            try:
                cmd, _ = md.compile_command(a.unit, d / "dbg.o")
                cmd = [str(tsrc) if c.replace("\\", "/").endswith(sw.u.src.replace("\\", "/")) else c for c in cmd]
                md.run_debugger(cmd, sw.sym or a.fn, d, int(os.environ.get("REGFIX_DBG_TIMEOUT", "900")), trace=True)
            finally:
                tsrc.unlink(missing_ok=True)
            print_schedule(d, d / "ours.o", ROOT / f"build/{md.VERSION}/obj/{sw.u.obj}.o", sw.sym or a.fn,
                           sw.render(sw.init).splitlines())
            print_coalesce(d, sw.render(sw.init).splitlines())
        rep = diagnose_dir(d, d / "ours.o", ROOT / f"build/{md.VERSION}/obj/{sw.u.obj}.o", a.fn, depth=a.depth,
                           src_lines=sw.render(sw.init).splitlines())
        print_levers(a, rep, sw.render(sw.init), d, sw.u.ext)
        if a.tracesweep:
            emit_tracesweep(a, rep, sw.render(sw.init), d, sw.u.ext)
    elif a.cmd == "diag":
        rep = diagnose(a.unit, a.fn, out, rerun=not a.no_run, depth=a.depth, sched=a.sched)
        suggest_rules(a.unit, a.fn)
        import pragmasweep as ps
        u = ps.Unit(a.unit)
        print_levers(a, rep, open(u.src, errors="replace").read(), out, u.ext)
        if a.tracesweep:
            emit_tracesweep(a, rep, open(u.src, errors="replace").read(), out, u.ext)
    else:
        fix(a, None)


if __name__ == "__main__":
    main()
