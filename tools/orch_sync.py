#!/usr/bin/env python3
"""Re-derive .orchestrator/state.json functions section from SoT.

Called at the start of each orchestrator cycle so that:

  - Object(Matching|NonMatching, ...) added to configure.py reflects as
    matched/nonmatching in state
  - Symbol renames in config/GNLJ82/symbols.txt propagate to function.name
    and recompute has_named_symbol
  - splits.txt range edits recompute tu_hint via range lookup
  - build/GNLJ82/report.json refreshes fuzzy_match_percent
  - Latest tools/ghidra_symbol_dump.json updates ghidra_named (informational)

Preserves orchestrator-owned function fields:
  batch_id, last_attempt_at, notes, dependencies, callers

Preserves entire batches and active_subs sections untouched.

Status re-derivation rule (same as init_orchestrator.py):
  1. tu_hint + Matching     -> matched
  2. tu_hint + NonMatching  -> nonmatching
  3. has_named_symbol=false -> excluded
  4. else                   -> pending (UNLESS already in_progress / interrupted /
     blocked / skipped — those are preserved as-is to avoid wiping cycle state)

New functions appearing in symbols.txt are added.
Functions removed from symbols.txt are deleted from state (cleaned up).

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
sys.path.insert(0, str(HERE))
# Reuse loaders from init_orchestrator.py to avoid drift
from init_orchestrator import (  # noqa: E402
    DUMP_PATH,
    ROOT,
    derive_status,
    find_tu,
    is_placeholder_name,
    load_configure_objects,
    load_ghidra_named_addrs,
    load_report_fuzzy,
    load_splits,
    load_symbols,
)

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


# Statuses that orch_sync must NOT overwrite even if SoT-derive disagrees.
# These represent live cycle state that the main agent is managing.
PROTECTED_STATUSES = {"in_progress", "interrupted", "blocked", "skipped"}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--quiet", action="store_true")
    parser.add_argument("--dry-run", action="store_true",
                        help="report diff stats without writing state.json")
    args = parser.parse_args()

    if not STATE_PATH.exists():
        sys.exit(f"state.json not found at {STATE_PATH}. "
                 "Run tools/init_orchestrator.py first.")

    state = json.loads(STATE_PATH.read_text(encoding="utf-8"))
    old_functions: dict[str, dict] = state.get("functions", {})

    symbols = load_symbols()
    splits = load_splits()
    ghidra_addrs = load_ghidra_named_addrs()
    configure_objs = load_configure_objects()
    fuzzy = load_report_fuzzy()

    ranges: list[tuple[int, int, str]] = []
    for tu, sections in splits.items():
        for _sec, start, end in sections:
            ranges.append((start, end, tu))
    ranges.sort()

    new_functions: dict[str, dict] = {}
    status_changes: list[tuple[str, str, str]] = []  # (addr, old, new)
    added = 0
    removed_addrs: list[str] = []

    sot_addrs: set[int] = set()
    for addr, sym in sorted(symbols.items()):
        if sym.get("kind") != "function":
            continue
        sot_addrs.add(addr)
        addr_key = f"0x{addr:08x}"
        existing = old_functions.get(addr_key)

        ghidra_named = addr in ghidra_addrs
        has_named_symbol = not is_placeholder_name(sym["name"])
        tu_hint = find_tu(addr, ranges)
        matching_flag = configure_objs.get(tu_hint) if tu_hint else None
        fpct = fuzzy.get(sym["name"])
        derived_status = derive_status(
            has_named_symbol=has_named_symbol,
            tu_hint=tu_hint,
            matching_flag=matching_flag,
        )

        if existing is None:
            # Newly discovered function (e.g. after dtk re-detected boundaries)
            new_functions[addr_key] = {
                "name": sym["name"],
                "section": sym["section"],
                "size": sym.get("size"),
                "has_named_symbol": has_named_symbol,
                "ghidra_named": ghidra_named,
                "tu_hint": tu_hint,
                "status": derived_status,
                "batch_id": None,
                "dependencies": [],
                "callers": [],
                "fuzzy_match_percent": fpct,
                "last_attempt_at": None,
                "notes": "",
            }
            added += 1
            continue

        # Preserve orchestrator-owned fields
        preserved_status = existing.get("status")
        if preserved_status in PROTECTED_STATUSES:
            final_status = preserved_status
        else:
            final_status = derived_status
            if preserved_status != final_status:
                status_changes.append((addr_key, preserved_status, final_status))

        new_functions[addr_key] = {
            "name": sym["name"],
            "section": sym["section"],
            "size": sym.get("size"),
            "has_named_symbol": has_named_symbol,
            "ghidra_named": ghidra_named,
            "tu_hint": tu_hint,
            "status": final_status,
            "batch_id": existing.get("batch_id"),
            "dependencies": existing.get("dependencies", []),
            "callers": existing.get("callers", []),
            "fuzzy_match_percent": fpct,
            "last_attempt_at": existing.get("last_attempt_at"),
            "notes": existing.get("notes", ""),
        }

    # Detect removed addresses (in old but not in SoT anymore)
    for addr_key in old_functions:
        if int(addr_key, 16) not in sot_addrs:
            removed_addrs.append(addr_key)

    state["functions"] = new_functions
    state["synced_from_sot_at"] = now_iso()
    if DUMP_PATH.exists():
        ts = dt.datetime.fromtimestamp(DUMP_PATH.stat().st_mtime, tz=dt.timezone.utc)
        state["ghidra_dump_mtime"] = ts.strftime("%Y-%m-%dT%H:%M:%SZ")

    if not args.dry_run:
        atomic_write_json(STATE_PATH, state)
        with LOG_PATH.open("a", encoding="utf-8") as f:
            f.write(json.dumps({
                "ts": now_iso(),
                "event": "sync",
                "session_id": state.get("session_id"),
                "added": added,
                "removed": len(removed_addrs),
                "status_changes": len(status_changes),
            }, ensure_ascii=False) + "\n")

    if not args.quiet:
        print(f"synced. added={added} removed={len(removed_addrs)} "
              f"status_changes={len(status_changes)}")
        for addr, old, new in status_changes[:20]:
            print(f"  {addr}: {old} -> {new}")
        if len(status_changes) > 20:
            print(f"  ... and {len(status_changes) - 20} more")
        for addr in removed_addrs[:10]:
            print(f"  removed: {addr}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
