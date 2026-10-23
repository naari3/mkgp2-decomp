# Effect native matching — 2026-10-23

## SparkSpray PlaceChildren (800C5C80, 300 bytes)

CW 1.3.2, automatic EH, individual r28-r31 saves (no lmw). Three structural approaches produced 98.13333%, 98.26667%, then complete text/EH/index agreement. Separate child local declared before the loop index gives group r31 / child r30 / index r29 / position r28; the short-lived parent register can be reused. Reusing the parameter pinned child to r28; declaring child after the index swapped the two loop homes. This was one targeted plain-local lifetime alignment, not a blind permutation search.

The position is caller-owned and slot placement takes Vec3 by value. Views are narrow, target-observed layouts; no live Ghidra type lookup was performed. Main independently verifies the source link and full DOL SHA-1 on acceptance.
