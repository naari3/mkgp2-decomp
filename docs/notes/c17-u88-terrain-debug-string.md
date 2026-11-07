# c17-u88-terrain-debug-string

Source: Codex worker c17_u88_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Terrain_FlagsToDebugString800A5384: baseline direct body with chained keep=set=0 measures98.84% objdiff (assignment report99.12). Value-returning high-patch inline with independently initialized keep/set gives target li r3,0;mr r0,r3 and target oris forms, improving99.48 with text500/extab8/index12 unchanged. Remaining g web r3 vs targetr4 and AND source r28 vs targetr4. Whole normalization helper regresses95.992 (492B, save set shrinks); returned keep/set aggregate regresses91.584. Both reverted; passing g vs flags to high helper is byte-invariant. Single function cannot split. .rodata target104 vs source99: existing five tail zero bytes0x80322183..0x80322188, no padding object added. Full fallback-linked DOL SHA-1 OK; no native gain.
