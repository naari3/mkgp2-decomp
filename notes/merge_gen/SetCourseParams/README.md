# SetCourseParams 14-TU merge generator (2026-11-09)

Scratch scripts that produced `src/game/SetCourseParams.c` (d6170022). Paths
inside point at the original scratch directory; they are kept as a recipe for
the next multi-TU merge, not as a maintained tool.

- `merge.py`: concatenates the parts (from `git show HEAD:src/...`), wraps each
  in per-part `#define X X_pN` / `#undef`, per-part exception / lmw pragmas,
  and writes the `X_pN -> X` rename map.
- `head.txt`: pool definitions in C++ mode (definition order = .bss order).
- `hand.json`: per-part hand edits.
- `mkjson.py` / `eto.py`: `tools/extab_user_renames.json` and
  `tools/extab_order.json` entries for the merged unit.
- `b.sh`: regenerate, build twice (renames need the first object), score.
