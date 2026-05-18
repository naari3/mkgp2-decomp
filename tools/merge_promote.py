#!/usr/bin/env python3
"""Merge sub-agent promote_asm_fn results from worktree(s) into main checkout.

Each sub-agent produces uncommitted changes in its `.worktrees/batch_promote_<addr>/`
worktree plus a `HANDOFF.md` summarising the result. This tool:

  1. Parses HANDOFF.md (json blob, possibly wrapped in markdown code fence)
  2. For each `results[].status == "matched"`:
       - `git -C <worktree> diff <base> -- <src_path>`  produces a patch
       - `git apply --3way -` on the main checkout applies it
  3. After all batches are applied, `ninja build/GNLJ82/ok` verifies SHA-1
  4. `state.json` flips the matched fns to status `matched` (with cycles /
     wall-clock from HANDOFF.md in notes)
  5. `git worktree remove --force` + `git branch -D` cleans up

Designed for parallel-wave dispatch: `--all` merges every present
`.worktrees/batch_promote_*/` in one shot. Patches for different fns of the
same TU don't conflict at the text level (sub changes are line-disjoint),
and `git apply --3way` resolves struct-extension overlaps when sub-agents
add fields at non-overlapping offsets.

Usage:
  python tools/merge_promote.py --batch <batch_id>
  python tools/merge_promote.py --all
  python tools/merge_promote.py --all --no-build       # skip verify
  python tools/merge_promote.py --all --no-cleanup     # keep worktrees
  python tools/merge_promote.py --all --no-state       # skip state.json
  python tools/merge_promote.py --all --dry-run        # print plan, no edits
"""
from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
WORKTREES_DIR = REPO_ROOT / ".worktrees"
STATE_JSON = REPO_ROOT / ".orchestrator" / "state.json"

JSON_FENCE_RE = re.compile(r'```(?:json)?\s*\n(.*?)\n```', re.DOTALL)


def parse_handoff(path: Path) -> dict:
    """Extract the json blob from HANDOFF.md (handles markdown code fence)."""
    if not path.is_file():
        raise FileNotFoundError(f"HANDOFF.md not found: {path}")
    content = path.read_text(encoding="utf-8")
    m = JSON_FENCE_RE.search(content)
    blob = m.group(1) if m else content
    return json.loads(blob)


def base_commit_of(worktree: Path) -> str:
    """Resolve the commit the worktree branched from (merge-base with main)."""
    return subprocess.check_output(
        ["git", "-C", str(worktree), "merge-base", "HEAD", "main"],
        text=True,
    ).strip()


def collect_diff(worktree: Path, base: str, files: list[str]) -> bytes:
    """`git diff <base> -- <files>` against the worktree's working tree.

    HANDOFF's `src_path` follows configure.py / splits.txt convention (no
    `src/` prefix, e.g. `init/debug_bba.c`). Actual git tree has them under
    `src/<src_path>`. Resolve each path against the worktree, preferring
    the on-disk form. Falls back to the raw value so git diff can report
    a meaningful error if neither resolves.
    """
    resolved: list[str] = []
    for f in files:
        if (worktree / f).is_file():
            resolved.append(f)
        elif (worktree / "src" / f).is_file():
            resolved.append(f"src/{f}")
        else:
            resolved.append(f)
    cmd = ["git", "-C", str(worktree), "diff", base, "--"] + resolved
    return subprocess.check_output(cmd)


def apply_patch(patch: bytes) -> int:
    """git apply --3way against main checkout. Returns the subprocess rc."""
    res = subprocess.run(
        ["git", "apply", "--3way", "-"],
        input=patch, cwd=REPO_ROOT, check=False,
    )
    return res.returncode


def update_state(matched: list[dict]) -> int:
    """Flip state.json entries for matched fns. Returns count updated."""
    if not STATE_JSON.is_file():
        return 0
    data = json.loads(STATE_JSON.read_text(encoding="utf-8"))
    fns = data.get("functions", {})
    ts = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    n = 0
    for r in matched:
        addr = r["addr"].lower()
        fn = fns.get(addr)
        if not fn:
            continue
        fn["status"] = "matched"
        fn["last_attempt_at"] = ts
        meta = r.get("_handoff_meta", {})
        wall = meta.get("wall_clock_minutes")
        cycles = meta.get("cycles")
        notes_src = (r.get("notes") or "")[:120]
        if wall is not None and cycles is not None:
            fn["notes"] = f"promoted via sub-agent ({cycles} cycle / {wall} min). {notes_src}"
        else:
            fn["notes"] = f"promoted via sub-agent. {notes_src}"
        n += 1
    STATE_JSON.write_text(json.dumps(data, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    return n


def cleanup_worktree(batch_id: str) -> None:
    """Remove worktree directory and its branch (force, post-merge)."""
    subprocess.run(
        ["git", "worktree", "remove", "--force", f".worktrees/{batch_id}"],
        cwd=REPO_ROOT, check=False, capture_output=True,
    )
    subprocess.run(
        ["git", "branch", "-D", f"orch/{batch_id}"],
        cwd=REPO_ROOT, check=False, capture_output=True,
    )


def merge_batch(batch_id: str, dry_run: bool) -> tuple[list[dict], dict | None]:
    """Apply one batch's patch. Returns (matched_results, handoff_metadata) or ([], None)."""
    wt = WORKTREES_DIR / batch_id
    if not wt.is_dir():
        print(f"[{batch_id}] worktree missing — skip", file=sys.stderr)
        return [], None
    try:
        handoff = parse_handoff(wt / "HANDOFF.md")
    except Exception as e:
        print(f"[{batch_id}] HANDOFF parse error: {e}", file=sys.stderr)
        return [], None
    matched = [r for r in handoff.get("results", []) if r.get("status") == "matched"]
    if not matched:
        print(f"[{batch_id}] no matched results (status: {[r.get('status') for r in handoff.get('results', [])]})")
        return [], handoff
    files = sorted({r["src_path"] for r in matched})
    base = base_commit_of(wt)
    patch = collect_diff(wt, base, files)
    if not patch.strip():
        print(f"[{batch_id}] no diff against base {base[:8]}")
        return [], handoff
    print(f"[{batch_id}] applying patch ({len(patch)} bytes, {len(matched)} fn, base {base[:8]})")
    if dry_run:
        print(f"[{batch_id}]   (dry-run, skipping apply)")
    else:
        rc = apply_patch(patch)
        if rc != 0:
            print(f"[{batch_id}] git apply failed (rc={rc}) — likely a 3-way merge conflict", file=sys.stderr)
            return [], handoff
    # Tag results with handoff meta for state.json update.
    meta = {
        "wall_clock_minutes": handoff.get("wall_clock_minutes"),
        "cycles": handoff.get("cycles"),
    }
    for r in matched:
        r["_handoff_meta"] = meta
    return matched, handoff


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--batch", help="single batch_id to merge")
    g.add_argument("--all", action="store_true", help="merge all .worktrees/batch_promote_*/")
    ap.add_argument("--no-build", action="store_true", help="skip post-merge ninja verify")
    ap.add_argument("--no-state", action="store_true", help="skip state.json update")
    ap.add_argument("--no-cleanup", action="store_true", help="keep worktrees and branches")
    ap.add_argument("--dry-run", action="store_true", help="print plan, no edits")
    args = ap.parse_args(argv)

    if args.all:
        if not WORKTREES_DIR.is_dir():
            print("no .worktrees/ dir", file=sys.stderr)
            return 1
        batch_ids = sorted(
            p.name for p in WORKTREES_DIR.iterdir()
            if p.is_dir() and p.name.startswith("batch_promote_")
        )
    else:
        batch_ids = [args.batch]

    if not batch_ids:
        print("no batches to merge", file=sys.stderr)
        return 0

    all_matched: list[dict] = []
    successful_batches: list[str] = []
    for bid in batch_ids:
        matched, _ = merge_batch(bid, args.dry_run)
        if matched:
            all_matched.extend(matched)
            successful_batches.append(bid)

    if args.dry_run:
        print(f"[dry-run] would merge {len(all_matched)} matched fn(s) from {len(successful_batches)} batch(es)")
        return 0

    if not all_matched:
        print("nothing merged")
        return 0

    if not args.no_build:
        print("running ninja build/GNLJ82/ok ...")
        res = subprocess.run(["ninja", "build/GNLJ82/ok"], cwd=REPO_ROOT)
        if res.returncode != 0:
            print("BUILD FAILED — patches applied but not verified. Inspect / fix / revert.", file=sys.stderr)
            return res.returncode

    if not args.no_state:
        n = update_state(all_matched)
        print(f"state.json: flipped {n} fn(s) to matched")

    if not args.no_cleanup:
        for bid in successful_batches:
            cleanup_worktree(bid)
        print(f"cleaned up {len(successful_batches)} worktree(s)")

    print(f"merged {len(all_matched)} matched fn(s) from {len(successful_batches)} batch(es)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
