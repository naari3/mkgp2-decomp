#!/usr/bin/env python3
"""Post-process a CW-built .o so manual extab/extabindex emissions land where
dtk expects them.

Two steps via llvm-objcopy:

1. Section rename:
     .extab_user      -> extab
     .extabindex_user -> extabindex
   mwcceppc reserves the bare names extab/extabindex and rejects
   __declspec(section "extab"). Emitting into ".extab_user" sidesteps the
   compiler check; renaming here merges the user entries into mwldeppc's
   default extab/extabindex output sections.

2. Symbol redefine (per-TU mapping):
   dtk dol split regenerates symbols.txt on every build and writes the
   anonymous local extab/extabindex symbols it observes in the target as
   `@etb_<addr>` / `@eti_<addr>` (scope:local hidden). dtk's dol diff then
   asserts these symbols exist at those addresses. C source can't declare
   identifiers starting with `@`, so we rename our user-side named symbols
   into the @-prefixed names llvm-objcopy expects.

   Mappings are read from a sibling json file `tools/extab_user_renames.json`
   (one entry per TU). Format:
     {
       "src/game/HeapStats.c": {
         "extab_dtor_8002F910":          "@etb_80005858",
         ...
         "extabindex_fn_8002F640":       "@eti_8001F490",
         ...
       }
     }
   The TU is identified by `.file` (-MMD or the first STT_FILE symbol);
   we fall back to scanning all rename keys against the object's local
   symbols if `.file` is missing.

Idempotent: if no .extab_user/.extabindex_user sections are present and no
mapped symbols match, this is a no-op.
"""
from __future__ import annotations

import json
import shutil
import subprocess
import sys
from pathlib import Path

LLVM_OBJCOPY_CANDIDATES = [
    "llvm-objcopy",
    r"C:\Program Files\LLVM\bin\llvm-objcopy.exe",
]

RENAMES_JSON = Path(__file__).resolve().parent / "extab_user_renames.json"


def find_llvm_objcopy() -> str:
    for c in LLVM_OBJCOPY_CANDIDATES:
        if shutil.which(c) or Path(c).is_file():
            return c
    sys.exit(
        "llvm-objcopy not found. Install LLVM (provides llvm-objcopy.exe) or "
        "add a candidate path to tools/postprocess_extab_user.py."
    )


def load_all_renames() -> dict[str, str]:
    """Collect rename pairs from every TU entry (flat name->name map).

    The same source name should not appear under two TUs with different
    targets; tools.extab_user_renames.json is hand-maintained.
    Returning a flat map lets us pass `--redefine-sym old=new` for every
    pair and rely on llvm-objcopy silently skipping ones not present in
    this particular .o.
    """
    if not RENAMES_JSON.is_file():
        return {}
    data = json.loads(RENAMES_JSON.read_text(encoding="utf-8"))
    flat: dict[str, str] = {}
    for tu, mapping in data.items():
        if not isinstance(mapping, dict):
            continue
        for src, dst in mapping.items():
            flat[src] = dst
    return flat


def main() -> int:
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_extab_user.py <object.o>")
    obj = Path(sys.argv[1])
    if not obj.is_file():
        sys.exit(f"file not found: {obj}")

    objcopy = find_llvm_objcopy()
    cmd: list[str] = [
        objcopy,
        "--rename-section=.extab_user=extab",
        "--rename-section=.extabindex_user=extabindex",
    ]
    for src, dst in load_all_renames().items():
        cmd.append(f"--redefine-sym={src}={dst}")
    cmd.append(str(obj))
    subprocess.check_call(cmd)
    return 0


if __name__ == "__main__":
    sys.exit(main())
