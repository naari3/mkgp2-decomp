# matrix-inline-reconstruction

Source: Codex worker c7_s11_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

For 0x800D3278, target is identity, native X/Y/Z rotations, then translation; LUT_Sine supplies diagonal and LUT_Cosine off-diagonal values exactly as existing matched Matrix4RotXY/Z sources. Full-size rotation wrappers exceed CW auto-inline threshold even when marked static inline. Expanded native blocks or small fill helpers produce the exact 2396-byte frame/loop structure. For 0x800D4174, scalar copy plus translate by negated original translation and transform +Z produces 876 bytes with only initial load scheduling remaining. See worktree HANDOFF evidence before retrying.
