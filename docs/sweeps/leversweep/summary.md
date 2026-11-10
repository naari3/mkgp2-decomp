# leversweep results

175 near misses swept by `tools/leversweep.py batch` (diagnosis-triggered levers).
"fired" = both triggers matched, "improved" = fewer diff lines than the current source, "matched" = objdiff 100% (0 diff lines alone is not enough).

| lever | rule | landed by | fired (fns) | variants | improved | matched |
| --- | --- | --- | --- | --- | --- | --- |
| restrict-input-ptrs | restrict-input-ptrs | fa1d62e (§30) | 59 | 250 | 1 | 0 |
| arg-order-prototype | arg-order-prototype | 28b9fb6 (§37) | 13 | 97 | 1 | 0 |
| index-for-walk | addr-on-demand | 025713e | 11 | 32 | 3 | 0 |
| inline-to-named-locals | inline-boundary | a4d82de, 963b6e1 | 78 | 8252 | 12 | 0 |
| mul-fuse | inline-mul-blocks-fmadd | d38113c (§39) | 28 | 621 | 8 | 0 |
| local-array-init | local-array-init | 5eca6fc | 13 | 118 | 1 | 0 |
| single-expr | single-expr-local | 0b362350 | 77 | 203 | 10 | 0 |
| try-scope-inside-if | try-scope-inside-if | 11f056f | 0 | 0 | 0 | 0 |
| nonconst-zero-arm | nonconst-zero-arm | gave_up clFlowCourse_Dtor | 5 | 10 | 1 | 0 |
| dead-def-split | dead-def-split | 8d77ba2 | 37 | 130 | 2 | 0 |
| block-local-counter | later-loops-block-local-counter | b879fcb | 2 | 6 | 2 | 0 |

## Improvements

| fn | TU | % | base lines | best lines | objdiff % | lever | variant |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `fn_8028CB64` | triforce/amnet_nm3 | 96.55 | 18 | 9 | 96.55 -> 93.92 | dead-def-split | dead sem |
| `acBind` | triforce/acsocket_nm5 | 97.65 | 13 | 11 | 97.65 -> 96.12 | inline-to-named-locals | [ClearBindBuffer] GetSocketBuffer@52 locals front |
| `AI_CalcLapSpeedBonus` | game/AI_CalcLapSpeedBonus | 99.88 | 14 | 12 | 99.88 -> 99.89 | single-expr | single expr: ccOffset -> (g_ccClass * 128) |
| `fn_8015B790` | game/Scene_8015B790 | 98.79 | 29 | 12 | 98.78 -> 98.48 | mul-fuse | fp_contract on |
| `fn_8018E538` | game/objview/fn_8018E538 | 99.42 | 24 | 22 | 99.42 -> 97.74 | dead-def-split | dead q |
| `fn_80225C2C` | game/anon_802253EC_nm1 | 94.65 | 40 | 38 | 94.57 -> 93.93 | single-expr | single expr: nextJoin -> (lbl_806D1A78 + 1) |
| `fn_80229998` | game/DNStartDino | 91.34 | 47 | 43 | 90.02 -> 89.88 | single-expr | single expr: sz -> (DNStartDino_tail_data_804EE0E0.z) |
| `KartPhysics_ApplyCollisionForce` | game/KartPhysics_ApplyCollisionForce | 98.64 | 54 | 46 | 98.35 -> 97.61 | inline-to-named-locals | apply_push@1498 subst front order timer,scale_,dz_,dy_,dx_ |
| `fn_8022ACE4` | game/EnemyFace | 98.61 | 60 | 56 | 98.49 -> 98.48 | inline-to-named-locals | TirePosition@1788 locals front order z,y,x |
| `TaMode_Init` | game/TaMode_FrameUpdate | 99.66 | 58 | 58 | 99.63 -> 99.66 | single-expr | single expr: laps -> (params[-6].laps) |
| `fn_801E2FD4` | game/fn_801DEF94 | 71.24 | 69 | 67 | 71.06 -> 72.89 | restrict-input-ptrs | restrict s |
| `fn_801E435C` | game/fn_801DEF94 | 99.48 | 70 | 68 | 99.48 -> 99.34 | single-expr | [ResizeEnd] single expr: ptr -> (it.ptr) |
| `fn_8019F5BC` | game/sprite/fn_8019F5BC | 97.67 | 86 | 78 | 97.67 -> 97.74 | inline-to-named-locals | SpriteAnim_ScaleTranslate@1455 subst front |
| `Card_VerifyChecksum` | game/CardSaveData_Parser | 96.38 | 84 | 82 | 96.38 -> 96.49 | index-for-walk | expected -> lbl_806D34A4[j] |
| `fn_8021DAB8` | game/anon_8021BC44_nm1 | 98.88 | 100 | 86 | 98.32 -> 98.32 | arg-order-prototype | fn_801695E0 order [3, 4, 5, 0, 1, 2] |
| `fn_801D92D0` | game/fn_801D92D0 | 90.39 | 112 | 108 | 90.39 -> 89.83 | single-expr | single expr: mode -> (entry->mode) |
| `ranking_display` | game/ranking_display | 96.10 | 130 | 128 | 96.09 -> 96.09 | inline-to-named-locals | SetTrack@1198 subst front |
| `HSD_LObjSetupInit` | sysdolphin/baselib/lobj_nm1 | 98.28 | 134 | 133 | 98.14 -> 97.94 | single-expr | [setup_spot_lightobj] single expr: spot_func -> (lobj->u.spot.spot_func) |
| `CalcEarnedCoins` | game/anon_80216568 | 98.53 | 146 | 144 | 98.53 -> 97.18 | nonconst-zero-arm | zero@1808 +prop off |
| `fn_801E9E74` | game/fn_801E9E74 | 98.70 | 161 | 159 | 98.7 -> 92.66 | index-for-walk | record -> record[i] |
| `fn_8019C6B4` | game/kartmove/fn_8019C6B4 | 97.49 | 181 | 171 | 97.45 -> 97.45 | mul-fuse | mul inline: stmt@85 except @102 |
| `VoiceSystem_Init` | game/VoiceSystem_Init | 90.41 | 191 | 179 | 89.8 -> 90.11 | single-expr | single expr: duration -> ((float)(lbl_80598A60.duration ) |
| `SpecialFace_RaycastSegment` | game/SpecialFaceMesh_Raycast | 96.16 | 243 | 207 | 96.08 -> 93.0 | mul-fuse | fuse: all single-use product locals |
| `fn_80172948` | game/HomingMarkerUpdate | 95.86 | 230 | 225 | 94.95 -> 94.23 | mul-fuse | mul inline: stmt@593 |
| `KartController_Update` | game/KartController_Update | 97.38 | 247 | 246 | 96.94 -> 97.05 | mul-fuse | [TransformPoints] mul inline: stmt@260 |
| `QuadFrame_FromCornerPtrs` | game/QuadFrame_FromCornerPtrs | 93.97 | 267 | 255 | 93.97 -> 87.75 | mul-fuse | [mid] mul inline: h*p->x@42 |
| `KartMovement_RotateByYaw` | game/kartmove/KartMovement_RotateByYaw | 96.12 | 286 | 284 | 96.12 -> 96.16 | inline-to-named-locals | TransformVector@110 subst front |
| `Race_PerFrameTickAndAudio` | game/RacePerFrame | 96.41 | 376 | 330 | 95.55 -> 95.67 | index-for-walk | other -> other[j] |
| `ExplosionTumble_Init` | game/ExplosionTumble_Init | 94.86 | 407 | 381 | 94.86 -> 95.15 | inline-to-named-locals | NormalizeCopy@487 subst front |
| `fn_80234840` | game/FlowCardCheck_nm2 | 95.73 | 427 | 399 | 95.73 -> 93.64 | local-array-init | kCharaY -> local array at top |
| `KartMovement_CollisionUpdate` | game/kartmove/KartMovement_CollisionUpdate | 96.96 | 714 | 705 | 96.95 -> 96.43 | mul-fuse | mul inline: stmt@2606 except @2657 |
| `NameCheck_ScanBannedWords` | game/NameCheck_CardName | 99.81 | 140 | 771 | 97.35 -> 97.44 | index-for-walk | sets -> sCharacterSets[group] |
| `TransitionEffect_RenderPass` | game/TransitionEffect | 99.77 | 824 | 818 | 99.75 -> 99.14 | inline-to-named-locals | ScreenFlatQuad@4391 locals front order a_,b_,g_,r_ |
| `fn_8022BFA8` | game/EnemyFaceDraw | 88.04 | 996 | 976 | 86.82 -> 86.88 | inline-to-named-locals | FillFaceUV@3989 subst front |
| `fn_8018B31C` | game/bitread/fn_8018B31C | 94.34 | 1474 | 1440 | 94.26 -> 94.34 | block-local-counter | i: later loops block-local |

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
