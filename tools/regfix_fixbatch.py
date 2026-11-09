#!/usr/bin/env python3
"""Run `regfix.py fix` over the unclaimed register-only near misses, sharded.

Candidates = rows of docs/sweeps/regfix/results.jsonl with no opcode diffs
(metric[0] == 0) and at least one mismatching vreg, whose function is still
< 100% in build/GNLJ82/report.json and whose unit is not in --claims.
They are sorted by function name; shard K/N takes index i with i % N == K-1.
By default the list is the frozen snapshot docs/sweeps/regfix/fix_inline_candidates.txt
(51 fns, claims of 2026-11-09 12:55Z already removed), so shards agree even
after the report changes; --claims then only drops units claimed since.

  python3 tools/regfix_fixbatch.py --shard 2/4 --claims claims.txt
  python3 tools/regfix_fixbatch.py --shard 2/4 --claims claims.txt --list   # just print

claims.txt: one unit per line (configure.py path without src/ and extension,
e.g. `game/JointTracks`) for every OPEN unit-claim issue, anyone's.
One jsonl row per function goes to docs/sweeps/regfix/fix_inline_shardK.jsonl;
functions already in that file are skipped (restartable). A match is written
by regfix to /tmp/regfix/FN.match.* and logged in tools/patterns/hits.jsonl;
claim the TU before landing it.
"""
import argparse
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BEST = ROOT / "docs" / "sweeps" / "autopipe99" / "best"
FROZEN = ROOT / "docs" / "sweeps" / "regfix" / "fix_inline_candidates.txt"   # 2026-11-09 snapshot


def candidates(claims):
    rep = json.load(open(ROOT / "build" / "GNLJ82" / "report.json"))
    pct = {f["name"]: f.get("fuzzy_match_percent", 0) for u in rep["units"] for f in u.get("functions", [])}
    out = {}
    for line in open(ROOT / "docs" / "sweeps" / "regfix" / "results.jsonl"):
        if not line.strip():
            continue
        d = json.loads(line)
        m = d.get("metric")
        if not m or m[0] != 0 or not any(d.get("bad", {}).values()):
            continue
        if d["unit"] in claims or pct.get(d["fn"], 0) >= 100:
            continue
        start = None
        if d.get("start"):
            b = BEST / os.path.basename(d["start"])
            start = str(b) if b.exists() else None
        out[d["fn"]] = (d["unit"], d["fn"], start)
    return [out[k] for k in sorted(out)]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--shard", default="1/1")
    ap.add_argument("--claims", help="file: one claimed unit per line")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--fresh", action="store_true", help="recompute candidates instead of the frozen list")
    ap.add_argument("--minutes", default="3")
    ap.add_argument("-j", "--jobs", default="4")
    a = ap.parse_args()
    k, n = map(int, a.shard.split("/"))
    claims = set()
    if a.claims:
        claims = {l.strip().replace("src/", "").rsplit(".", 1)[0] if l.strip().startswith("src/") else l.strip()
                  for l in open(a.claims) if l.strip()}
    if a.fresh:
        cands = candidates(claims)
    else:   # frozen list so every shard sees the same order
        cands = [tuple((l.split() + [None])[:3]) for l in open(FROZEN) if l.strip()]
        cands = [(u, f, s or None) for u, f, s in cands]
    todo = [c for i, c in enumerate(cands) if i % n == k - 1 and c[0] not in claims]
    if a.list:
        for u, f, s in todo:
            print(u, f, s or "")
        return
    out = ROOT / "docs" / "sweeps" / "regfix" / f"fix_inline_shard{k}.jsonl"
    done = {json.loads(l)["fn"] for l in open(out)} if out.exists() else set()
    print(f"[fixbatch] shard {k}/{n}: {len(todo)} fns, {len(done)} done", flush=True)
    for unit, fn, start in todo:
        if fn in done:
            continue
        cmd = [sys.executable, str(ROOT / "tools" / "regfix.py"), "fix", unit, fn, "--rounds", "3",
               "--sample", "90", "--minutes", a.minutes, "-j", a.jobs]
        if start:
            cmd += ["--start-tu", start]
            m = re.search(r"_GC([\d.]+[a-z]?)\.c", start)
            if m:
                cmd += ["--cc", m.group(1)]
        t0 = time.time()
        try:
            p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=900)
            log = p.stdout + p.stderr
        except subprocess.TimeoutExpired:
            log = "timeout"
        res = " ".join(l for l in log.splitlines() if re.search(r"MATCH via|best:|start:", l))
        row = {"unit": unit, "fn": fn, "secs": int(time.time() - t0),
               "outcome": "already" if "already matching" in log else "MATCH" if "MATCH via" in log else "nomatch", "res": res or log[-300:]}
        with open(out, "a") as f:
            f.write(json.dumps(row) + "\n")
        print(f"[fixbatch] {fn}: {row['outcome']} ({row['secs']}s)", flush=True)


if __name__ == "__main__":
    main()
