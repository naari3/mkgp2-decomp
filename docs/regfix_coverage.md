# regalloc_patterns sections vs `tools/regfix.py diag` (audit 2026-11-10 04:30Z)

Which sections of `docs/regalloc_patterns.md` (54 onward) the diag output
points at. Update this table when a section or a hint is added.

| state | sections |
|---|---|
| diag prints a dedicated hint | 54, 57, 58, 59, 61, 64, 66, 67, 69, 70, 71, 72, 73, 75, 77, 78, 79, 81, 83, 85 (operand order), 89, 93, 94 (1) |
| diag shows the leversweep lever | 62, 74 (arg-order-prototype), 84 |
| readable from the colouring-sequence / neighbour sections (70, 89), no dedicated hint | 56, 65, 68, 80, 86, 88, 92 |
| not detected | 55, 60, 63, 76, 82, 87, 90, 91, 94 (2, 3) |

Why the last row is hard: diag only diagnoses register-only diffs (same
instruction count, at most a few opcode diffs). 55, 76, 87, 90 change the
instruction sequence (extra saved register, an extra `mr`, a second load
set, another struct-copy shape); 60, 63, 82, 91 are scheduling or
multi-step shapes with no single signature. 90 is partly caught by the
anchor-offset hint (an object starts where the target adds a constant to an
anchor).

Hints older than 54 that diag also prints: 35 (inline wrapper, named
locals), 40 (anchor offsets inside a symbol), 46 (shared loop counter),
52/53 (list sentinel).
