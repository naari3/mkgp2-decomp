# matrix-inline-reconstruction

Source: Codex worker c7_s11_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

For 0x800D3278, target is identity, native X/Y/Z rotations, then translation; LUT_Sine supplies diagonal and LUT_Cosine off-diagonal values exactly as existing matched Matrix4RotXY/Z sources. Full-size rotation wrappers exceed CW auto-inline threshold even when marked static inline. Expanded native blocks or small fill helpers produce the exact 2396-byte frame/loop structure. For 0x800D4174, scalar copy plus translate by negated original translation and transform +Z produces 876 bytes with only initial load scheduling remaining. See worktree HANDOFF evidence before retrying.

## c14_u6_20261106
Source: Codex worker c14_u6_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u6: 0x800D3278 literal identity constants in TU-local helpers raise text 94.61436 to 94.71452, still2396B, EH8/index12 exact. Residual lies in initial angle load scheduling, f1/f2 copy temporaries at X/Y and Y/Z transitions, and translation-copy tail scheduling. Loop copy with original constants94.63105; separate const-input multiply/copy helpers92.978294 and EH changed, both reverted. One function only; remainsNonMatching. Full fallback DOL SHA1 exact, native gain0.
