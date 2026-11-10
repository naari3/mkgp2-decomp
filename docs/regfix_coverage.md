# regalloc_patterns sections vs `tools/regfix.py diag` (audit 2026-11-10 04:30Z)

Which sections of `docs/regalloc_patterns.md` (54 onward) the diag output
points at. Update this table when a section or a hint is added.

| state | sections |
|---|---|
| diag prints a dedicated hint | 54, 57, 58, 59, 61, 64, 66, 67, 69, 70, 71, 72, 73, 75, 77, 78, 79, 81, 83, 85 (operand order), 89, 93, 94 (1) |
| diag shows the leversweep lever | 62, 74 (arg-order-prototype), 84 |
| readable from the colouring-sequence / neighbour sections (70, 89), no dedicated hint | 56, 65, 68, 80, 86, 88, 92 |
| instruction sequence differs: `tools/shapediag.py` (diag calls it by itself) | 55 (`saved-regs`), 63 lever 3 (`order:regswap`), 76 (`copy:target-extra` / `copy:direction`), 82 and 91 (`order:args`), 87 (`load:target-reloads`, "stack float loaded twice"), 90 (`order:copyrun`) |
| not detected | 60 (the near miss is a pure register rotation; `select:indexed` only fires once ours has the walker instead of the `add`), 63 levers 1-2, 94 (2, 3) |

Since 2026-11-10 diag no longer stops at "not a register-only diff": it
prints the `shapediag` classes of every differing run with the levers for
each class (`python3 tools/shapediag.py classes` lists all of them). How the
rows above were checked (`python3 tools/shapediag.py replay`, which rebuilds
the source just before the fix commit): 63, 76 and the older rules 7.8
(`__restrict` -> `order:load`, loop step order -> `order:loopstep`), 84
(`order:expr`), 40/69 (VoiceSystem_Init) fire on the real pre-fix source. 82
and 87 were checked by undoing the lever in today's source
(`shapediag.py fn UNIT FN --src FILE`). 55, 90 and 91 only have synthetic
cases in `shapediag.py selftest` (their pre-fix sources were never
committed, or no longer build). The pre-fix states of 60, AI_CalcGPTargetSpeed,
PtrVec_InsertFill and DetermineTitle are register-only diffs, so they stay
with the allocator model.

Hints older than 54 that diag also prints: 35 (inline wrapper, named
locals), 40 (anchor offsets inside a symbol), 46 (shared loop counter),
52/53 (list sentinel).
