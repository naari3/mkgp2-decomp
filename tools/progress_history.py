#!/usr/bin/env python3
"""Maintain per-commit decomp progress history (JSONL, one line per commit).

The history file lives on the orphan `progress-data` branch as
history/<VERSION>.jsonl. Each line:

  {"sha": "...", "ts": "2026-07-18T18:37:51+09:00", "matched_code": 123,
   "total_code": 456, "matched_code_percent": 26.97, ...}

Subcommands:
  append    Add one entry from a report.json (idempotent by sha). Used by CI.
  backfill  Rebuild history from past GitHub Actions report artifacts via the
            gh CLI. One-time local seeding; safe to re-run (merges by sha).

Examples:
  python tools/progress_history.py append \
      --report build/GNLJ82/report.json \
      --history .progress-data/history/GNLJ82.jsonl \
      --sha $GITHUB_SHA --ts "$(git log -1 --format=%cI $GITHUB_SHA)"

  python tools/progress_history.py backfill \
      --repo naari3/mkgp2-decomp --artifact GNLJ82_report \
      --history history/GNLJ82.jsonl
"""
from __future__ import annotations

import argparse
import io
import json
import subprocess
import sys
import zipfile
from pathlib import Path
from typing import Any, Dict, List, Optional

MEASURE_KEYS = [
    "matched_code",
    "total_code",
    "matched_code_percent",
    "complete_code",
    "complete_code_percent",
    "matched_functions",
    "total_functions",
    "complete_units",
    "total_units",
    "fuzzy_match_percent",
]


def _to_num(v: Any) -> Any:
    """objdiff serializes u64 measures as strings; normalize to int/float."""
    if isinstance(v, str):
        return int(v) if v.isdigit() else 0
    if isinstance(v, float):
        return round(v, 4)
    return v or 0


def entry_from_report(report_path: Path, sha: str, ts: str) -> Dict[str, Any]:
    with report_path.open("r", encoding="utf-8") as f:
        report = json.load(f)
    m = report.get("measures", {})
    entry: Dict[str, Any] = {"sha": sha, "ts": ts}
    for k in MEASURE_KEYS:
        entry[k] = _to_num(m.get(k))
    return entry


def load_history(path: Path) -> List[Dict[str, Any]]:
    if not path.is_file():
        return []
    rows = []
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if line:
            rows.append(json.loads(line))
    return rows


def write_history(path: Path, rows: List[Dict[str, Any]]) -> None:
    rows = sorted(rows, key=lambda r: (r["ts"], r["sha"]))
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as f:
        for r in rows:
            f.write(json.dumps(r, separators=(",", ":")) + "\n")


def cmd_append(args: argparse.Namespace) -> int:
    rows = load_history(args.history)
    if any(r["sha"] == args.sha for r in rows):
        print(f"{args.sha} already in history, nothing to do")
        return 0
    rows.append(entry_from_report(args.report, args.sha, args.ts))
    write_history(args.history, rows)
    print(f"appended {args.sha} ({len(rows)} entries total)")
    return 0


def _gh_json(argv: List[str]) -> Any:
    out = subprocess.run(
        ["gh"] + argv, check=True, capture_output=True, encoding="utf-8"
    ).stdout
    return json.loads(out)


def _gh_bytes(argv: List[str]) -> bytes:
    return subprocess.run(["gh"] + argv, check=True, capture_output=True).stdout


def cmd_backfill(args: argparse.Namespace) -> int:
    rows = {r["sha"]: r for r in load_history(args.history)}
    runs: List[Dict[str, Any]] = []
    page = 1
    while True:
        resp = _gh_json([
            "api",
            f"repos/{args.repo}/actions/runs"
            f"?branch={args.branch}&status=success&per_page=100&page={page}",
        ])
        batch = resp.get("workflow_runs", [])
        runs.extend(batch)
        if len(batch) < 100:
            break
        page += 1
    runs = [r for r in runs if r.get("path", "").endswith(args.workflow)]
    # Newest first from the API; keep the newest run per sha.
    seen_shas = set()
    todo = []
    for r in runs:
        sha = r["head_sha"]
        if sha in seen_shas:
            continue
        seen_shas.add(sha)
        if sha in rows:
            continue
        todo.append(r)
    print(f"{len(runs)} runs, {len(todo)} new shas to fetch")

    fetched = skipped = 0
    for i, run in enumerate(todo, 1):
        sha = run["head_sha"]
        arts = _gh_json([
            "api", f"repos/{args.repo}/actions/runs/{run['id']}/artifacts"
        ]).get("artifacts", [])
        art = next(
            (a for a in arts if a["name"] == args.artifact and not a["expired"]),
            None,
        )
        if art is None:
            print(f"[{i}/{len(todo)}] {sha[:9]} no {args.artifact} artifact, skip")
            skipped += 1
            continue
        zip_bytes = _gh_bytes([
            "api", f"repos/{args.repo}/actions/artifacts/{art['id']}/zip"
        ])
        with zipfile.ZipFile(io.BytesIO(zip_bytes)) as zf:
            with zf.open("report.json") as f:
                report = json.load(f)
        ts = (run.get("head_commit") or {}).get("timestamp") or run["created_at"]
        m = report.get("measures", {})
        entry: Dict[str, Any] = {"sha": sha, "ts": ts}
        for k in MEASURE_KEYS:
            entry[k] = _to_num(m.get(k))
        rows[sha] = entry
        fetched += 1
        print(f"[{i}/{len(todo)}] {sha[:9]} {entry['matched_code_percent']}%")

    write_history(args.history, list(rows.values()))
    print(f"done: +{fetched} fetched, {skipped} skipped, "
          f"{len(rows)} entries -> {args.history}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("append", help="append one report.json entry")
    p.add_argument("--report", type=Path, required=True)
    p.add_argument("--history", type=Path, required=True)
    p.add_argument("--sha", required=True)
    p.add_argument("--ts", required=True, help="commit time, ISO 8601")
    p.set_defaults(func=cmd_append)

    p = sub.add_parser("backfill", help="seed history from CI artifacts (gh)")
    p.add_argument("--repo", default="naari3/mkgp2-decomp")
    p.add_argument("--branch", default="main")
    p.add_argument("--workflow", default="build.yml")
    p.add_argument("--artifact", default="GNLJ82_report")
    p.add_argument("--history", type=Path, required=True)
    p.set_defaults(func=cmd_backfill)

    args = ap.parse_args()
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
