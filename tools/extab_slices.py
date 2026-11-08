#!/usr/bin/env python3
"""Split the shared extab jsons into one small file per source, for ninja.

tools/extab_user_renames.json and tools/extab_order.json are read by the
post-compile step of every object, but ninja did not know that, so editing a
rename never rebuilt the object and every landing needed a clean build
(`rm -rf build/GNLJ82/src`). Making every object depend on the whole json
would rebuild all ~2700 objects on any edit instead.

This script writes build/<ver>/extab_deps/<src path>.json holding only that
source's entries from both files, and rewrites a slice only when its content
changes. Ninja runs it with `restat = 1` and each object depends on its own
slice, so an edit rebuilds exactly the TUs whose entries changed.

Usage (from ninja): extab_slices.py <list file> <out dir>
The list file (written by configure.py) has one source path per line; a slice
is written for every listed source, `{}` when it has no entries.
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parent


def main() -> int:
    list_file, out_dir = Path(sys.argv[1]), Path(sys.argv[2])
    renames = json.loads((TOOLS / "extab_user_renames.json").read_text(encoding="utf-8"))
    order = json.loads((TOOLS / "extab_order.json").read_text(encoding="utf-8"))
    for src in list_file.read_text(encoding="utf-8").split("\n"):
        if not src:
            continue
        part = {}
        if isinstance(renames.get(src), dict):
            part["renames"] = renames[src]
        if src in order and isinstance(order[src], (list, dict)):
            part["order"] = order[src]
        text = json.dumps(part, indent=1, ensure_ascii=False, sort_keys=False) + "\n"
        out = out_dir / (src + ".json")
        try:
            if out.read_text(encoding="utf-8") == text:
                continue
        except FileNotFoundError:
            out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(text, encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())
