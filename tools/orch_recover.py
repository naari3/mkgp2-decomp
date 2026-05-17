#!/usr/bin/env python3
"""Recover .orchestrator/state.json after a non-graceful stop.

Invoked at the start of a new orchestrator session (when state.session_id
does not match the new session, or when explicitly asked).

For each entry in state.active_subs:
  - worktree missing                       -> batch.status=cancelled, functions->pending
  - worktree present + HANDOFF.md present  -> batch.status=completed,
                                              record handoff_path for main's merge queue
  - worktree present + HANDOFF.md missing  -> batch.status=interrupted,
                                              functions->interrupted, escalate via
                                              HANDOFF_TO_USER.md

Then a second pass cleans up batches/functions that are stuck in
"in flight" status but not covered by any active_sub.

active_subs is fully cleared at the end (all sub-agents from the previous
session are assumed dead — Agent tool's run_in_background does not survive
parent session restart).

Schema reference: docs/orchestrator_state_schema.md
"""
from __future__ import annotations

import argparse
import datetime as dt
import json
import os
import sys
import tempfile
from pathlib import Path
from typing import Optional


HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
ORCH_DIR = ROOT / ".orchestrator"
STATE_PATH = ORCH_DIR / "state.json"
LOG_PATH = ORCH_DIR / "log.jsonl"
DRAIN_FLAG = ORCH_DIR / "drain.flag"
HANDOFF_TO_USER = ORCH_DIR / "HANDOFF_TO_USER.md"


def atomic_write_json(path: Path, data: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(prefix=".", suffix=".tmp", dir=path.parent)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
        os.replace(tmp, path)
    except Exception:
        try:
            os.unlink(tmp)
        except OSError:
            pass
        raise


def now_iso() -> str:
    return dt.datetime.now(dt.timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def revert_functions_to(state: dict, batch_id: str, new_status: str) -> None:
    """Set functions belonging to batch_id back to new_status if currently in_progress."""
    batch = state["batches"].get(batch_id)
    if not batch:
        return
    for addr_key in batch.get("function_addresses", []):
        fn = state["functions"].get(addr_key)
        if not fn:
            continue
        if fn.get("status") == "in_progress" and fn.get("batch_id") == batch_id:
            fn["status"] = new_status
            if new_status == "pending":
                fn["batch_id"] = None


def append_handoff_to_user(lines: list[str]) -> None:
    """Append an entry to HANDOFF_TO_USER.md (in .orchestrator/)."""
    HANDOFF_TO_USER.parent.mkdir(parents=True, exist_ok=True)
    header = f"## Recovery {now_iso()}\n\n"
    body = header + "\n".join(lines) + "\n\n"
    with HANDOFF_TO_USER.open("a", encoding="utf-8") as f:
        f.write(body)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--new-session", help="session_id for the recovery log entry")
    parser.add_argument("--quiet", action="store_true", help="suppress per-batch print")
    args = parser.parse_args()

    if not STATE_PATH.exists():
        print("no state.json; nothing to recover")
        return 0

    state = json.loads(STATE_PATH.read_text(encoding="utf-8"))
    active_subs: dict[str, dict] = state.get("active_subs", {})
    batches: dict[str, dict] = state.get("batches", {})
    functions: dict[str, dict] = state.get("functions", {})

    actions: list[tuple[str, str, Optional[str]]] = []  # (batch_id, action, detail)
    interrupted_for_user: list[str] = []

    # Pass 1: process each known active_sub
    for sub_key, sub in list(active_subs.items()):
        batch_id = sub.get("batch_id")
        worktree_str = sub.get("worktree_path")
        worktree = Path(worktree_str) if worktree_str else None

        if batch_id not in batches:
            actions.append((batch_id or "<unknown>", "orphan_sub_no_batch", sub_key))
            continue

        batch = batches[batch_id]

        if worktree is None or not worktree.exists():
            revert_functions_to(state, batch_id, "pending")
            batch["status"] = "cancelled"
            batch["assigned_sub"] = None
            actions.append((batch_id, "cancelled_no_worktree", sub_key))
            continue

        handoff = worktree / "HANDOFF.md"
        if handoff.exists():
            batch["status"] = "completed"
            batch["handoff_path"] = str(handoff.resolve()).replace("\\", "/")
            batch["assigned_sub"] = None
            actions.append((batch_id, "pending_merge", sub_key))
            continue

        # worktree present, no HANDOFF.md -> mid-work crash
        revert_functions_to(state, batch_id, "interrupted")
        batch["status"] = "interrupted"
        batch["assigned_sub"] = None
        actions.append((batch_id, "interrupted", sub_key))
        interrupted_for_user.append(
            f"- `{batch_id}` worktree: `{worktree}` — sub `{sub_key}` died mid-work, "
            f"no HANDOFF.md. Inspect manually."
        )

    # Pass 2: catch batches stuck in dispatched but not in active_subs
    for batch_id, batch in batches.items():
        if batch.get("status") != "dispatched":
            continue
        assigned = batch.get("assigned_sub")
        if assigned and assigned in active_subs:
            continue
        # orphan dispatched batch
        wt_str = batch.get("worktree_path")
        worktree = Path(wt_str) if wt_str else None
        if worktree is None or not worktree.exists():
            revert_functions_to(state, batch_id, "pending")
            batch["status"] = "cancelled"
            actions.append((batch_id, "orphan_dispatched_cancelled", None))
            continue
        if (worktree / "HANDOFF.md").exists():
            batch["status"] = "completed"
            batch["handoff_path"] = str((worktree / "HANDOFF.md").resolve()).replace("\\", "/")
            actions.append((batch_id, "orphan_dispatched_pending_merge", None))
            continue
        revert_functions_to(state, batch_id, "interrupted")
        batch["status"] = "interrupted"
        actions.append((batch_id, "orphan_dispatched_interrupted", None))
        interrupted_for_user.append(
            f"- `{batch_id}` worktree: `{worktree}` — dispatched but no active_sub "
            f"tracked, no HANDOFF.md. Inspect manually."
        )

    # Pass 3: catch functions stuck in in_progress with no live batch
    for addr_key, fn in functions.items():
        if fn.get("status") != "in_progress":
            continue
        bid = fn.get("batch_id")
        if bid and batches.get(bid, {}).get("status") in ("dispatched", "in_progress"):
            continue
        fn["status"] = "pending"
        fn["batch_id"] = None

    # Active_subs are all dead — clear unconditionally
    state["active_subs"] = {}

    # Drain flag has no meaning after recovery
    drain_removed = False
    if DRAIN_FLAG.exists():
        DRAIN_FLAG.unlink()
        drain_removed = True

    atomic_write_json(STATE_PATH, state)

    # Log
    LOG_PATH.parent.mkdir(parents=True, exist_ok=True)
    with LOG_PATH.open("a", encoding="utf-8") as f:
        f.write(json.dumps({
            "ts": now_iso(),
            "event": "recover",
            "session_id": args.new_session,
            "actions": [
                {"batch_id": b, "action": a, "sub": s}
                for b, a, s in actions
            ],
            "drain_flag_removed": drain_removed,
        }, ensure_ascii=False) + "\n")

    if interrupted_for_user:
        append_handoff_to_user([
            "Recovery detected batches that were interrupted mid-work. "
            "Their worktrees may contain partial C source you want to inspect "
            "before discarding:",
            "",
            *interrupted_for_user,
            "",
            "After inspection, either:",
            "  - Commit anything valuable from the worktree manually, then "
            "`git worktree remove --force <path>` to delete.",
            "  - Or rerun `python tools/init_orchestrator.py --force` to "
            "fully rebuild state and clean up.",
        ])

    if not args.quiet:
        print(f"recovered: {len(actions)} batch action(s)")
        for b, a, s in actions:
            sub_tag = f" sub={s}" if s else ""
            print(f"  {b}: {a}{sub_tag}")
        if drain_removed:
            print("removed drain.flag")
        if interrupted_for_user:
            print(f"wrote {len(interrupted_for_user)} entries to {HANDOFF_TO_USER}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
