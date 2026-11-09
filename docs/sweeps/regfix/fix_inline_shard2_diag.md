# regfix fix_inline shard 2/4 (2026-11-09)

`regfix_fixbatch.py --shard 2/4`: 13 fns, 0 match, 0 diff-line improvement
(fn_8019A9BC metric 34 -> 32 vregs off, same 98 diff lines). Per-fn `regfix.py diag`:

| fn | model | vregs off | depth-2 edits that give target regs | catalog rules |
|---|---|---|---|---|
| AI_CalcVSTargetSpeed | ok | GPR 5 | 0 / 5360 | - |
| CoinJumpFx_UpdateParticleGrid | ok | GPR 3 | 2 / 135: frontend temp @57 (line 45 `lwz +0x10`) must be created after @64/@63, i.e. @60/@62 before @57 (reorder inline calls/temps) | lifetime-block-reuse, ref-local-across-loop, temp-to-local |
| Effect_DustBurst4_Update | ok | GPR 9, FPR 2 | GPR 0; FPR 8: temp @78 (line 110 `lfs +0x84`) created after the other line-110 loads | lifetime-block-reuse |
| Object_DriveAnimAndSkin | ok | GPR 10 | 0 / 67686 | - |
| Terrain_WallEdgeTest | ok | GPR 7 | 0 / 65992 (also stack slot order differs: seg.ax/az stores swapped) | - |
| clFlowGpPlease_Init | - | - | diag timed out (>300 s); fix ran 487 s, nomatch | - |
| fn_8017DF00 | ok | GPR 1 | 2 / 552: local `node` (line 90) created after temp @238 (line 87), or r28 busy while node live | lifetime-block-reuse, decl-order, inline-matched-sibling, nested-inline-level |
| fn_8019A9BC | ok | FPR 34 | 0 / 125756 | - |
| fn_801EE36C | ok | FPR 2 | 4 / 11698: temp @140 (line 76 `lfs previous.x`, reused line 80) created after the line-79 literal temps | lifetime-block-reuse |
| fn_801F8404 | - | - | diag sees 0 target insns with the autopipe99 best start TU (tool issue) | - |
| fn_8023AC14 | MISMATCH | GPR 1 | 8 (unreliable): `self` numbered after early temps + r27 busy over `li 0x1422` | - |
| fn_80282F54 | ok | GPR 15 | 0 / 43879 | - |
| fn_80291134 | MISMATCH | GPR 3 | 1 (unreliable): swap r38/r54 + r0 busy | - |

Diagnosed but untranslated (fix found no source rewrite): CoinJumpFx, Effect_DustBurst4 FPR,
fn_8017DF00, fn_801EE36C -> all "temp must be created later/earlier", i.e. the temp->local /
statement-reorder translations are what is missing.
