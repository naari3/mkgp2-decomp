# c13-u11-terrain-unlock

Source: Codex worker c13_u11_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 192 B.

Terrain_FlagsToTypeId split at 800A5284 unlocks first 3 functions (192B). Remaining two factor functions retain r4/r5 low-flags/high-mask coloring and final OR destination residual. Low-patch helper call regresses to 62.24138/79.71429%; accumulator |= and in-place high-patch pointer helper are byte-identical negatives at 97.586205/98.0. All probes reverted. Both TUs own text only; no EH/data split required. Full source-linked first run DOL SHA-1 OK.
