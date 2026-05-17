#!/usr/bin/env python3
"""Parse HANDOFF.md (sub-agent return artifact) into a Python dict.

Format spec: docs/sub_agent_role.md "HANDOFF.md format 仕様"

HANDOFF.md is markdown with one ```json``` fenced block. Free-form prose
outside the block is ignored. If multiple json blocks exist, only the
first is used.

Validates required fields:
  - batch_id (str)
  - results (list of dicts with required keys: addr, name, status, src_path)
  - build_verified (dict with sha1_ok bool)

Returns the parsed dict. Raises HandoffParseError on any validation failure.

CLI usage:
  python tools/parse_handoff.py <path/to/HANDOFF.md>
  python tools/parse_handoff.py --validate-only <path>
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path


JSON_FENCE = re.compile(r"```json\s*\n(.*?)\n```", re.DOTALL)
VALID_STATUSES = {"matched", "asm_fn", "nonmatching", "skipped", "failed"}
ADDR_HEX = re.compile(r"^0x[0-9a-fA-F]+$")


class HandoffParseError(ValueError):
    pass


def extract_json_block(content: str) -> str:
    m = JSON_FENCE.search(content)
    if not m:
        raise HandoffParseError(
            "no ```json fenced block found in HANDOFF.md"
        )
    return m.group(1)


def validate(data: dict) -> None:
    if not isinstance(data, dict):
        raise HandoffParseError(f"top-level must be object, got {type(data).__name__}")

    batch_id = data.get("batch_id")
    if not isinstance(batch_id, str) or not batch_id:
        raise HandoffParseError("batch_id must be a non-empty string")

    results = data.get("results")
    if not isinstance(results, list):
        raise HandoffParseError("results must be a list")
    if not results:
        raise HandoffParseError("results must contain at least one entry")

    for i, r in enumerate(results):
        if not isinstance(r, dict):
            raise HandoffParseError(f"results[{i}] must be object")
        for req in ("addr", "name", "status"):
            if req not in r:
                raise HandoffParseError(f"results[{i}] missing required field: {req}")
        if not ADDR_HEX.match(str(r["addr"])):
            raise HandoffParseError(f"results[{i}].addr not hex literal: {r['addr']!r}")
        if r["status"] not in VALID_STATUSES:
            raise HandoffParseError(
                f"results[{i}].status invalid: {r['status']!r}. "
                f"Must be one of {sorted(VALID_STATUSES)}"
            )

    bv = data.get("build_verified")
    if not isinstance(bv, dict):
        raise HandoffParseError("build_verified must be object")
    if "sha1_ok" not in bv or not isinstance(bv["sha1_ok"], bool):
        raise HandoffParseError("build_verified.sha1_ok must be bool")

    # Optional nested sections — validate shape if present
    cp = data.get("configure_py")
    if cp is not None:
        if not isinstance(cp, dict):
            raise HandoffParseError("configure_py must be object")
        for i, ao in enumerate(cp.get("add_objects", []) or []):
            if not isinstance(ao, dict) or "lib" not in ao or "object" not in ao:
                raise HandoffParseError(
                    f"configure_py.add_objects[{i}] needs 'lib' and 'object'"
                )

    sp = data.get("splits_txt")
    if sp is not None:
        if not isinstance(sp, dict):
            raise HandoffParseError("splits_txt must be object")
        for i, ae in enumerate(sp.get("add_entries", []) or []):
            if not isinstance(ae, dict) or "path" not in ae or "sections" not in ae:
                raise HandoffParseError(
                    f"splits_txt.add_entries[{i}] needs 'path' and 'sections'"
                )
            for j, sec in enumerate(ae["sections"]):
                for req in ("section", "start", "end"):
                    if req not in sec:
                        raise HandoffParseError(
                            f"splits_txt.add_entries[{i}].sections[{j}] missing {req}"
                        )

    sym = data.get("symbols_txt")
    if sym is not None:
        if not isinstance(sym, dict):
            raise HandoffParseError("symbols_txt must be object")
        for i, r in enumerate(sym.get("rename", []) or []):
            if not isinstance(r, dict) or "old" not in r or "new" not in r:
                raise HandoffParseError(
                    f"symbols_txt.rename[{i}] needs 'old' and 'new'"
                )


def parse(path: Path) -> dict:
    content = path.read_text(encoding="utf-8")
    raw_json = extract_json_block(content)
    try:
        data = json.loads(raw_json)
    except json.JSONDecodeError as e:
        raise HandoffParseError(f"json decode failed: {e}") from e
    validate(data)
    return data


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("path", type=Path)
    parser.add_argument("--validate-only", action="store_true",
                        help="exit 0 if valid, non-zero otherwise; no stdout output")
    args = parser.parse_args()

    if not args.path.exists():
        print(f"file not found: {args.path}", file=sys.stderr)
        return 2

    try:
        data = parse(args.path)
    except HandoffParseError as e:
        print(f"HANDOFF parse error: {e}", file=sys.stderr)
        return 1

    if args.validate_only:
        return 0

    print(json.dumps(data, indent=2, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    sys.exit(main())
