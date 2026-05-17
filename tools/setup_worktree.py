#!/usr/bin/env python3
"""Create a git worktree for orchestrator dispatch and populate orig/.

Background:
  `git worktree add` produces a worktree where `.gitignore`d files are
  absent. orig/GNLJ82/sys/main.dol is gitignored (orig/*/*) but required
  by `ninja build/GNLJ82/main.dol` (the build matches against the target
  DOL). Without it, a sub-agent's first build fails with
  "orig/GNLJ82/sys/main.dol not found".

This script: (1) `git worktree add` if missing, (2) copy required files
from the main checkout's orig/ into the worktree.

Usage:
  python tools/setup_worktree.py <batch_id>
      [--branch orch/<batch_id>] [--base main]

Idempotent: re-running on an existing worktree skips the git add and
re-syncs orig/ (in case main's orig/ changed).

Schema reference: docs/orchestrator_role.md "Cycle CASE 4: dispatch"
"""
from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
ORIG_SRC = ROOT / "orig"
WORKTREES_DIR = ROOT / ".worktrees"


def populate_orig(worktree: Path) -> tuple[int, int]:
    """Copy non-.gitkeep files from ROOT/orig/ into worktree/orig/.

    Returns (copied, skipped) counts.
    """
    if not ORIG_SRC.exists():
        print(f"main checkout orig/ not found at {ORIG_SRC}", file=sys.stderr)
        return 0, 0
    copied = 0
    skipped = 0
    for src_file in ORIG_SRC.rglob("*"):
        if src_file.is_dir():
            continue
        rel = src_file.relative_to(ORIG_SRC)
        if rel.name == ".gitkeep":
            continue  # worktree already has it
        dst_file = worktree / "orig" / rel
        # Skip if same size (cheap mtime/content check)
        if (
            dst_file.exists()
            and dst_file.stat().st_size == src_file.stat().st_size
        ):
            skipped += 1
            continue
        dst_file.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src_file, dst_file)
        copied += 1
    return copied, skipped


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("batch_id")
    parser.add_argument("--branch", default=None,
                        help="branch name (default: orch/<batch_id>)")
    parser.add_argument("--base", default="main",
                        help="base branch for worktree (default: main)")
    args = parser.parse_args()

    branch = args.branch or f"orch/{args.batch_id}"
    worktree = WORKTREES_DIR / args.batch_id

    if not worktree.exists():
        result = subprocess.run(
            ["git", "worktree", "add", "-b", branch,
             str(worktree), args.base],
            cwd=ROOT, capture_output=True, text=True
        )
        if result.returncode != 0:
            print(f"git worktree add failed:\n{result.stderr}", file=sys.stderr)
            return 1
        if result.stdout:
            print(result.stdout, end="")
    else:
        print(f"worktree exists at {worktree}, skipping git worktree add")

    copied, skipped = populate_orig(worktree)
    print(f"orig/: copied {copied} file(s), skipped {skipped} unchanged")
    print(f"worktree ready: {worktree}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
