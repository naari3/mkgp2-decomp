# leversweep results

134 near misses swept by `tools/leversweep.py batch` (diagnosis-triggered levers).
"fired" = both triggers matched, "improved" = fewer diff lines than the current source, "matched" = objdiff 100% (0 diff lines alone is not enough).

| lever | rule | landed by | fired (fns) | variants | improved | matched |
| --- | --- | --- | --- | --- | --- | --- |
| restrict-input-ptrs | restrict-input-ptrs | fa1d62e (§30) | 45 | 211 | 1 | 0 |
| arg-order-prototype | arg-order-prototype | 28b9fb6 (§37) | 9 | 57 | 0 | 0 |
| index-for-walk | addr-on-demand | 025713e | 8 | 19 | 0 | 0 |
| inline-to-named-locals | inline-boundary | a4d82de, 963b6e1 | 62 | 6278 | 11 | 0 |
| mul-fuse | inline-mul-blocks-fmadd | d38113c (§39) | 20 | 509 | 6 | 0 |
| local-array-init | local-array-init | 5eca6fc | 10 | 100 | 2 | 0 |
| single-expr | single-expr-local | 0b362350 | 67 | 178 | 10 | 0 |
| try-scope-inside-if | try-scope-inside-if | 11f056f | 0 | 0 | 0 | 0 |
| nonconst-zero-arm | nonconst-zero-arm | gave_up clFlowCourse_Dtor | 3 | 6 | 0 | 0 |
| dead-def-split | dead-def-split | 8d77ba2 | 27 | 80 | 2 | 0 |
| block-local-counter | later-loops-block-local-counter | b879fcb | 2 | 6 | 1 | 0 |
| chain-assign-split | chain-assign-split | f96d5c26 | 5 | 24 | 1 | 0 |

## Improvements

| fn | TU | % | base lines | best lines | objdiff % | lever | variant |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `fn_8018E538` | game/objview/fn_8018E538 | 99.42 | 24 | 4 | 99.42 -> 96.42 | block-local-counter | i: later loops block-local |
| `fn_8028CB64` | triforce/amnet_nm3 | 96.55 | 18 | 9 | 96.55 -> 93.92 | dead-def-split | dead sem |
| `acBind` | triforce/acsocket_nm5 | 97.65 | 13 | 11 | 97.65 -> 96.12 | inline-to-named-locals | [ClearBindBuffer] GetSocketBuffer@52 locals front |
| `AI_CalcLapSpeedBonus` | game/AI_CalcLapSpeedBonus | 99.88 | 14 | 12 | 99.88 -> 99.89 | single-expr | single expr: ccOffset -> (g_ccClass * 128) |
| `fn_801B4548` | game/sprite/fn_801A1798 | 99.93 | 36 | 29 | 99.92 -> 99.86 | inline-to-named-locals | FindNearestVoiceKart801B_p47@1997 subst front order best_p47,distance_p47_,e_p47,nearest_p47_,i_p47_ |
| `KartPhysics_ApplyCollisionForce` | game/KartPhysics_ApplyCollisionForce | 98.64 | 54 | 38 | 98.35 -> 97.75 | inline-to-named-locals+single-expr | apply_push@1498 subst front order timer,scale_,dz_,dy_,dx_ & [subtract_vector] single expr: az -> (src.z) |
| `fn_80225C2C` | game/anon_802253EC_nm1 | 94.65 | 40 | 38 | 94.57 -> 93.93 | single-expr | single expr: nextJoin -> (lbl_806D1A78 + 1) |
| `fn_80229998` | game/DNStartDino | 91.34 | 47 | 43 | 90.02 -> 89.88 | single-expr | single expr: sz -> (DNStartDino_tail_data_804EE0E0.z) |
| `fn_8022ACE4` | game/EnemyFace | 98.61 | 60 | 56 | 98.49 -> 98.48 | inline-to-named-locals | TirePosition@1788 locals front order z,y,x |
| `fn_801E2FD4` | game/fn_801DEF94 | 71.24 | 69 | 67 | 71.06 -> 72.89 | restrict-input-ptrs | restrict s |
| `fn_801E435C` | game/fn_801DEF94 | 99.48 | 70 | 68 | 99.48 -> 99.34 | single-expr | [ResizeEnd] single expr: ptr -> (it.ptr) |
| `fn_8019F5BC` | game/sprite/fn_8019F5BC | 97.67 | 86 | 78 | 97.67 -> 97.74 | inline-to-named-locals | SpriteAnim_ScaleTranslate@1455 subst front |
| `fn_801D92D0` | game/fn_801D92D0 | 90.39 | 112 | 108 | 90.39 -> 89.83 | single-expr | single expr: mode -> (entry->mode) |
| `HSD_LObjSetupInit` | sysdolphin/baselib/lobj_nm1 | 99.07 | 128 | 127 | 98.93 -> 98.73 | single-expr | [setup_spot_lightobj] single expr: spot_func -> (lobj->u.spot.spot_func) |
| `ranking_display` | game/ranking_display | 96.10 | 130 | 128 | 96.09 -> 96.09 | inline-to-named-locals | SetTrack@1198 subst front |
| `fn_801A6538` | game/sprite/fn_801A1798 | 99.75 | 162 | 155 | 99.71 -> 98.38 | local-array-init | chaseCur_p11 -> static const table, direct |
| `VoiceSystem_Init` | game/sprite/fn_801A1798 | 90.41 | 191 | 177 | 89.3 -> 90.32 | inline-to-named-locals+single-expr | VoiceSystem_ClearPlayCounts_p52@3893 subst front order i_p52_,clips_p52 & single expr: duration_p52 -> ((float)(lbl_80598A60_p52.durat) |
| `SpecialFace_RaycastSegment` | game/SpecialFaceMesh_Raycast | 96.16 | 243 | 207 | 96.08 -> 93.0 | mul-fuse | fuse: all single-use product locals |
| `fn_80172948` | game/HomingMarkerUpdate | 96.08 | 216 | 211 | 95.16 -> 94.44 | mul-fuse | mul inline: stmt@593 |
| `KartController_Update` | game/KartController_Update | 97.61 | 225 | 224 | 97.44 -> 96.57 | mul-fuse | [UpdateTerrainColors] mul inline: stmt@619 |
| `ExplosionTumble_Init` | game/ExplosionTumble_Init | 95.71 | 270 | 227 | 95.43 -> 94.18 | inline-to-named-locals+mul-fuse | NormalizeCopy@401 subst front & [QuaternionMatrix] mul inline: q->x*q->x@197 |
| `QuadFrame_FromCornerPtrs` | game/QuadFrame_FromCornerPtrs | 93.97 | 267 | 255 | 93.97 -> 87.75 | mul-fuse | [mid] mul inline: h*p->x@42 |
| `fn_80234840` | game/FlowCardCheck_nm2 | 95.97 | 426 | 398 | 95.97 -> 93.87 | local-array-init | kCharaY -> local array at top |
| `KartMovement_CollisionUpdate` | game/kartmove/KartMovement_CollisionUpdate | 96.96 | 714 | 697 | 96.95 -> 96.44 | chain-assign-split+mul-fuse | all chains split, source order & mul inline: stmt@2606 except @2657 |
| `fn_8022BFA8` | game/EnemyFaceDraw | 88.04 | 996 | 976 | 86.82 -> 86.88 | inline-to-named-locals | FillFaceUV@3989 subst front |
| `fn_8018B31C` | game/bitread/fn_8018B31C | 94.41 | 1440 | 1432 | 94.34 -> 94.36 | inline-to-named-locals | WriteBits@2100 subst front |

## Levers not automated here

| lever | rule | class | landed by | why |
| --- | --- | --- | --- | --- |
| inline-asm r2/r13 fixed offsets -> symbol refs | - | auto (nothing left) | 71b5ffd4 | grep: no game TU has a numeric r2/r13 displacement in inline asm any more (only TRK, already matching) |
| split the pool at `addi rX, anchor, N` | anchor-addi-object-boundary | semi (detect only) | §40 | `leversweep.py detect` lists the functions and offsets; the split edits the pool source and symbols.txt |
| rolled-loop + opt_unroll_instr_count | loop-unroll-budget | semi | 833c85a | pragma half is automatic (pragmasweep --set extended sweeps opt_unroll_instr_count 8/16/32); rolling a hand-unrolled loop back needs the loop count and the induction step, which differ per site |
| base vtable store in the ctor body | base-init-in-body | semi | §36 | needs the base class vtable symbol and a ctor that has address locals; trigger (prologue lis/addi swap) is cheap but there were 2 C++ ctors near misses with that shape, done by hand |
| avoid IRO CSE temps | - | semi | 3cc4b0e | the rewrite (read through a cast pointer / hoist before) is a fakematch-flavoured choice per site; shapesweep hoist covers the hoist half, the trigger needs a mwtrace TEMPNEW trace |
| pool-owner TU merges | merge-pool-owner | semi | 7653d99 | pool_audit.py finds them; the merge edits splits.txt/configure.py/symbols and has to respect claims |
| TU merges (correct structure) | merge-pool-owner | manual | 5d5f466b | tu_audit.py proposes; each merge is a splits/configure/extab job checked against main.dol |
