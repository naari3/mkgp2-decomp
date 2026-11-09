#!/usr/bin/env python3
"""Run `regfix.py diag UNIT FN --tracesweep --run` over the gave_up near misses.

Candidates = function names in backticks in docs/gave_up.md that are still
< 100% (and >= --min %) in build/GNLJ82/report.json, in a unit that is not in
--claims. Sorted by name; shard K/N takes index i with i % N == K-1.

  python3 tools/regfix_diagsweep.py --list
  python3 tools/regfix_diagsweep.py --shard 1/4 --claims claims.txt

One jsonl row per function goes to docs/sweeps/regfix/diagsweep_shardK.jsonl
(restartable: functions already there are skipped):
  {fn, unit, pct, status, levers:[rule ids], axes:[...], base, best, confirm, secs}
status: hit (a variant reaches diff 0 and real-compiler 100%), better (best
variant has fewer diff lines), same, no_template (diag gave no source-visible
solution), not_reg_only, error/timeout. A hit's source is
/tmp/tracesweep/FN.diag.best.*; claim the TU before landing it. Nothing is
written to tools/patterns/hits.jsonl by this batch.
"""
import argparse
import json
import re
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "docs" / "sweeps" / "regfix"


def candidates(claims, lo):
    rep = json.load(open(ROOT / "build" / "GNLJ82" / "report.json"))
    pct = {}
    for u in rep["units"]:
        for f in u.get("functions", []):
            pct[f["name"]] = (f.get("fuzzy_match_percent", 0), re.sub(r"^main/", "", u["name"]))
    names = set(re.findall(r"`([A-Za-z_]\w*)`", open(ROOT / "docs" / "gave_up.md").read()))
    out = []
    for n in sorted(names):
        if n in pct and lo <= pct[n][0] < 100 and pct[n][1] not in claims:
            out.append((pct[n][1], n, pct[n][0]))
    return out


def parse(text):
    r = {"levers": re.findall(r"^  \[([\w-]+)\] ", text, re.M),
         "axes": re.findall(r"^   ([hcw]\d+): ", text, re.M)}
    m = re.search(r"current source: diff (\d+)", text)
    r["base"] = int(m.group(1)) if m else None
    rows = re.findall(r"^  diff\s+(\d+)\s+want=(\w+)\s*(.*)$", text, re.M)
    rows = [x for x in rows if int(x[0]) < 10**6]
    if rows:
        b = min(rows, key=lambda x: int(x[0]))
        r["best"] = int(b[0])
        r["best_pick"] = b[2].strip()[:80]
        r["want_true"] = sum(1 for x in rows if x[1] == "True")
    cf = re.findall(r"confirm \(real [^)]*\) pick=\[[^\]]*\]: objdiff ([\d.]+)%, diff (\d+)", text)
    if cf:
        r["confirm"] = max(float(p) for p, _ in cf)
    if "not a register-only diff" in text:
        r["status"] = "not_reg_only"
    elif "nothing generated" in text or not r["axes"]:
        r["status"] = "no_template"
    elif r.get("confirm") == 100.0:
        r["status"] = "hit"
    elif r.get("best") is not None and r["base"] is not None and r["best"] < r["base"]:
        r["status"] = "better"
    elif r.get("best") is not None:
        r["status"] = "same"
    else:
        r["status"] = "error"
    return r


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--shard", default="1/1")
    ap.add_argument("--claims", help="file: one claimed unit per line")
    ap.add_argument("--min", type=float, default=90.0)
    ap.add_argument("--timeout", type=int, default=420)
    ap.add_argument("--sample", type=int, default=1500)
    ap.add_argument("-j", "--jobs", type=int, default=4)
    ap.add_argument("--list", action="store_true")
    a = ap.parse_args()
    claims = set()
    if a.claims:
        claims = {l.strip() for l in open(a.claims) if l.strip()}
    k, n = (int(x) for x in a.shard.split("/"))
    cs = [c for i, c in enumerate(candidates(claims, a.min)) if i % n == k - 1]
    if a.list:
        for c in cs:
            print(*c)
        print(len(cs), "functions", file=sys.stderr)
        return
    out = OUT / f"diagsweep_shard{k}.jsonl"
    done = set()
    if out.exists():
        done = {json.loads(l)["fn"] for l in open(out) if l.strip()}
    for unit, fn, pct in cs:
        if fn in done:
            continue
        t0 = time.time()
        cmd = [sys.executable, str(ROOT / "tools" / "regfix.py"), "diag", unit, fn, "--tracesweep", "--run",
               "--sample", str(a.sample), "-j", str(a.jobs)]
        try:
            p = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=a.timeout)
            r = parse(p.stdout + p.stderr)
            if r["status"] == "error":
                r["tail"] = (p.stdout + p.stderr)[-300:]
        except subprocess.TimeoutExpired:
            r = {"status": "timeout"}
        r = {"fn": fn, "unit": unit, "pct": pct, **r, "secs": round(time.time() - t0)}
        with open(out, "a") as f:
            f.write(json.dumps(r) + "\n")
        print(f"{fn:40s} {pct:6.2f} {r['status']:12s} base={r.get('base')} best={r.get('best')} "
              f"axes={len(r.get('axes', []))} levers={','.join(r.get('levers', []))}", flush=True)


if __name__ == "__main__":
    main()
