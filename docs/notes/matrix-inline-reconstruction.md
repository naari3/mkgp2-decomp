# matrix-inline-reconstruction

Source: Codex worker c7_s11_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

For 0x800D3278, target is identity, native X/Y/Z rotations, then translation; LUT_Sine supplies diagonal and LUT_Cosine off-diagonal values exactly as existing matched Matrix4RotXY/Z sources. Full-size rotation wrappers exceed CW auto-inline threshold even when marked static inline. Expanded native blocks or small fill helpers produce the exact 2396-byte frame/loop structure. For 0x800D4174, scalar copy plus translate by negated original translation and transform +Z produces 876 bytes with only initial load scheduling remaining. See worktree HANDOFF evidence before retrying.

## c14_u6_20261106
Source: Codex worker c14_u6_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u6: 0x800D3278 literal identity constants in TU-local helpers raise text 94.61436 to 94.71452, still2396B, EH8/index12 exact. Residual lies in initial angle load scheduling, f1/f2 copy temporaries at X/Y and Y/Z transitions, and translation-copy tail scheduling. Loop copy with original constants94.63105; separate const-input multiply/copy helpers92.978294 and EH changed, both reverted. One function only; remainsNonMatching. Full fallback DOL SHA1 exact, native gain0.

## c16_u34_20261106
Source: Codex worker c16_u34_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 492 B.

c16_u34: Matrix4_PreMultiplyTranslation 800D50FC492B now native100 text/EH/index. Mirror matched Matrix4RotZ: typedef float Matrix4[4][4], explicit identity assignments, inline float-parameter translation setter, translation then product locals, nested row/column multiply left[row][0]*right[0][column] + right[1][column]*left[row][1] + right[2][column]*left[row][2] + right[3][column]*left[row][3], nested scalar copy product[(unsigned int)row][column]. This restores target coefficient forwarding, two-row unrolling, scratch slots and all FP homes in one structural trial. Earlier flat scalar/accumulator helper failed; nested shape matters. Matching flag only; source-linked main.elf range and whole DOL SHA1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 verified by coordinator build service.

## c16_u54_20261106
Source: Codex worker c16_u54_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 324 B.

c16_u54: Matrix4_Multiply 800D5C0C (324 B) now native, 100% text/EH/index. Replace flat 16-float scratch plus four staged accumulators with typedef float Matrix4[4][4], nested row/column loops and complete per-column four-term expression in the same operand order as Matrix4RotZ. Nested scalar scratch-to-output copy uses unsigned row. First structural approach fixes all FP scheduling/register differences from 80.48148%; no pragma, flags, EH bridges or split edits needed beyond Matching flag. Source-linked full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65 confirmed by coordinator build service.

## c18_u169_20261107
Source: Codex worker c18_u169_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 2396 B.

c18_u169: Mtx44_FromEulerXYZTrans 800D3278/2396B promoted Matching. Fresh untouched source under current-main GC/2.0 Object config is 100% text/extab8/index12; c14 residual/94.71452% was measured under GC/1.3.2. Independently compared all 599 instruction strings against target: equal. Only NonMatching->Matching flag changed; source, compiler selection and ranges unchanged. Source main.elf edge and symbol 800D3278/2396 verified, full DOL SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. Native gain +1/+2396B.
