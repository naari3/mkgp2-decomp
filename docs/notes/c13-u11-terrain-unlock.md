# c13-u11-terrain-unlock

Source: Codex worker c13_u11_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 3 fn / 192 B.

Terrain_FlagsToTypeId split at 800A5284 unlocks first 3 functions (192B). Remaining two factor functions retain r4/r5 low-flags/high-mask coloring and final OR destination residual. Low-patch helper call regresses to 62.24138/79.71429%; accumulator |= and in-place high-patch pointer helper are byte-identical negatives at 97.586205/98.0. All probes reverted. Both TUs own text only; no EH/data split required. Full source-linked first run DOL SHA-1 OK.

## c18_u71_20261107
Source: Codex worker c18_u71_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 116 B.

c18_u71: caller-local normalization plus separate static inline factor-selection helper restores target register/coalescing shape for Terrain_GetTractionFactor: baseline97.586205 ->100%, exact116B. Flattening normalization alone fixes lo/high-mask r5/r4 but removes andis. and produces112B. Selection helper preserves final mask and r3 filtered-flags home. Analogous slip improves98.0->98.28571%, exact140B, with cup/normalized flags r5/r6 swapped versus targetr6/r5. Explicit cached cup parameter is byte-invariant. Mechanism B splits at800A52F8: nm1 Matching traction116B, nm2 NonMatching slip140B. No EH/data ownership or symbol changes. Coordinator full source-linked DOL SHA1 exact; +1fn/+116B.
