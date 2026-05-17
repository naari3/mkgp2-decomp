#!/usr/bin/env python3
"""[FALLBACK / DEBUG ONLY] Mechanically enqueue 1 function = 1 batch.

本番 orchestrator 動作では使わない。batch 編成は main agent の判断責務で、
cycle 内で Ghidra MCP の xref / callees / namespace を引いて related function
を grouping する設計 (see prompts/cycle.md CASE 5、docs/orchestrator_role.md)。

このスクリプトは以下の限定用途のために残してある:

- Ghidra MCP が使えない環境での dry-run / 動作テスト
- state schema や cycle 動作を Ghidra 抜きで検証したい開発時
- main agent が batch 編成中に詰まったときの emergency fallback

機械的に「pending function 1 つ = 1 batch」を生成するだけで、関連関数の
bundling や依存解決判定は一切行わない。本番 cycle が動いている間に呼ぶと
main が動的に作る batch と衝突するので **絶対に並行実行しない**。

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


HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
ORCH_DIR = ROOT / ".orchestrator"
STATE_PATH = ORCH_DIR / "state.json"
LOG_PATH = ORCH_DIR / "log.jsonl"


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


def short_section(section: str) -> str:
    """`.init` -> `init`, `.text` -> `text`, etc."""
    return section.lstrip(".") or section


def addr_int(addr_key: str) -> int:
    return int(addr_key, 16)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--max-batches", type=int, default=None,
                        help="cap on number of new batches to create this run")
    parser.add_argument("--section", action="append", default=None,
                        help="limit to functions in this section (repeatable, "
                             "e.g. --section .init)")
    parser.add_argument("--reset-pending", action="store_true",
                        help="delete all batches currently in 'pending' status "
                             "before planning (does not touch dispatched/completed)")
    parser.add_argument("--dry-run", action="store_true",
                        help="print plan without writing state.json")
    args = parser.parse_args()

    if not STATE_PATH.exists():
        sys.exit(f"state.json not found at {STATE_PATH}. "
                 "Run tools/init_orchestrator.py first.")

    state = json.loads(STATE_PATH.read_text(encoding="utf-8"))
    functions: dict[str, dict] = state["functions"]
    batches: dict[str, dict] = state.setdefault("batches", {})

    # Optionally drop existing pending batches
    if args.reset_pending and not args.dry_run:
        dropped = []
        for bid in list(batches):
            if batches[bid].get("status") == "pending":
                # Free up function batch_id assignment too
                for addr_key in batches[bid].get("function_addresses", []):
                    fn = functions.get(addr_key)
                    if fn and fn.get("batch_id") == bid:
                        fn["batch_id"] = None
                del batches[bid]
                dropped.append(bid)
        print(f"reset_pending: dropped {len(dropped)} pending batch(es)")

    # Collect candidate functions
    candidates: list[tuple[str, dict]] = []
    for addr_key, fn in functions.items():
        if fn.get("status") != "pending":
            continue
        if fn.get("batch_id") is not None:
            continue
        if args.section and fn.get("section") not in args.section:
            continue
        candidates.append((addr_key, fn))

    # Order: smallest size first (early wins), then by address
    candidates.sort(
        key=lambda kv: (kv[1].get("size") or 0xFFFFFFFF, addr_int(kv[0]))
    )

    if args.max_batches is not None:
        candidates = candidates[: args.max_batches]

    created: list[str] = []
    for addr_key, fn in candidates:
        addr_int_ = addr_int(addr_key)
        section_short = short_section(fn.get("section", "unknown"))
        batch_id = f"batch_{section_short}_{addr_int_:08x}"
        if batch_id in batches:
            # Skip silently — batch already exists (e.g., from a previous run
            # that wasn't reset). Don't overwrite, don't claim the function.
            continue
        batches[batch_id] = {
            "status": "pending",
            "tu_hint": None,
            "function_addresses": [addr_key],
            "assigned_sub": None,
            "worktree_path": None,
            "branch": None,
            "created_at": now_iso(),
            "dispatched_at": None,
            "completed_at": None,
            "retry_count": 0,
            "blocked_reason": None,
            "handoff_path": None,
        }
        fn["batch_id"] = batch_id
        created.append(batch_id)

    if args.dry_run:
        print(f"DRY RUN: would create {len(created)} batch(es)")
        for bid in created[:20]:
            b = batches[bid]
            print(f"  {bid}  fn={b['function_addresses'][0]}")
        if len(created) > 20:
            print(f"  ... and {len(created) - 20} more")
        return 0

    atomic_write_json(STATE_PATH, state)

    with LOG_PATH.open("a", encoding="utf-8") as f:
        f.write(json.dumps({
            "ts": now_iso(),
            "event": "plan",
            "session_id": state.get("session_id"),
            "created_count": len(created),
            "first_batches": created[:5],
        }, ensure_ascii=False) + "\n")

    # Summarize
    by_status: dict[str, int] = {}
    for b in batches.values():
        by_status[b.get("status", "?")] = by_status.get(b.get("status", "?"), 0) + 1
    print(f"created {len(created)} new batch(es)")
    print(f"total batches by status:")
    for st in sorted(by_status):
        print(f"  {st}: {by_status[st]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
