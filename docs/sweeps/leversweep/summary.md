# leversweep results

174 near misses swept by `tools/leversweep.py batch` (diagnosis-triggered levers).
"fired" = both triggers matched, "improved" = fewer diff lines than the current source, "matched" = objdiff 100% (0 diff lines alone is not enough).

| lever | rule | landed by | fired (fns) | variants | improved | matched |
| --- | --- | --- | --- | --- | --- | --- |
| restrict-input-ptrs | restrict-input-ptrs | fa1d62e (§30) | 60 | 255 | 1 | 0 |
| arg-order-prototype | arg-order-prototype | 28b9fb6 (§37) | 14 | 112 | 2 | 0 |
| index-for-walk | addr-on-demand | 025713e | 12 | 37 | 5 | 0 |
| inline-to-named-locals | inline-boundary | a4d82de, 963b6e1 | 83 | 8496 | 16 | 0 |
| try-scope-inside-if | try-scope-inside-if | 11f056f | 0 | 0 | 0 | 0 |
| nonconst-zero-arm | nonconst-zero-arm | gave_up clFlowCourse_Dtor | 5 | 10 | 1 | 0 |
| dead-def-split | dead-def-split | 8d77ba2 | 40 | 138 | 4 | 1 |

## Improvements

| fn | TU | % | base lines | best lines | objdiff % | lever | variant |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `PCBCheck_ProcessLinks` | game/PCBCheckProcess | 99.96 | 4 | 0 | 99.96 -> 100.0 | dead-def-split | dead base |
| `fn_80243464` | game/fn_80243464 | 99.76 | 16 | 0 | 99.55 -> 99.79 | inline-to-named-locals | AddOffset@1636 locals front |
| `ClSound_InitSoundSystem` | game/clsound/ClSound_InitSoundSystem | 99.81 | 30 | 8 | 99.81 -> 99.92 | inline-to-named-locals | [LoadSoundFile] ReadSoundFile@522 subst back |
| `fn_8028CB64` | triforce/amnet_nm3 | 96.55 | 18 | 9 | 96.55 -> 93.92 | dead-def-split | dead sem |
| `acBind` | triforce/acsocket_nm5 | 97.65 | 13 | 11 | 97.65 -> 96.12 | inline-to-named-locals | [ClearBindBuffer] GetSocketBuffer@52 locals front |
| `AI_CalcLapSpeedBonus` | game/AI_CalcLapSpeedBonus | 98.70 | 22 | 20 | 98.51 -> 99.23 | dead-def-split | dead variant |
| `fn_8018E538` | game/objview/fn_8018E538 | 99.42 | 24 | 22 | 99.42 -> 97.74 | dead-def-split | dead q |
| `KartPhysics_ApplyCollisionForce` | game/KartPhysics_ApplyCollisionForce | 98.64 | 54 | 46 | 98.35 -> 97.61 | inline-to-named-locals | apply_push@1498 subst front order timer,scale_,dz_,dy_,dx_ |
| `PCBComm_Init` | game/PCBCommLifecycle | 97.08 | 59 | 55 | 96.97 -> 97.05 | inline-to-named-locals | [ResetScratch] ClearPackets@203 subst front order cursor,count |
| `fn_8022ACE4` | game/EnemyFace | 98.61 | 60 | 56 | 98.49 -> 98.48 | inline-to-named-locals | TirePosition@1788 locals front order z,y,x |
| `fn_801E2FD4` | game/fn_801DEF94 | 71.24 | 69 | 67 | 71.06 -> 72.89 | restrict-input-ptrs | restrict s |
| `fn_8019F5BC` | game/sprite/fn_8019F5BC | 97.67 | 86 | 78 | 97.67 -> 97.74 | inline-to-named-locals | SpriteAnim_ScaleTranslate@1455 subst front |
| `Card_VerifyChecksum` | game/CardSaveData_Parser | 96.38 | 84 | 82 | 96.38 -> 96.49 | index-for-walk | expected -> lbl_806D34A4[j] |
| `fn_8021DAB8` | game/anon_8021BC44_nm1 | 98.88 | 100 | 86 | 98.32 -> 98.32 | arg-order-prototype | fn_801695E0 order [3, 4, 5, 0, 1, 2] |
| `ranking_display` | game/ranking_display | 96.10 | 130 | 128 | 96.09 -> 96.09 | inline-to-named-locals | SetTrack@1198 subst front |
| `CalcEarnedCoins` | game/anon_80216568 | 98.53 | 146 | 144 | 98.53 -> 97.18 | nonconst-zero-arm | zero@1808 +prop off |
| `fn_801E9E74` | game/fn_801E9E74 | 98.70 | 161 | 159 | 98.7 -> 92.66 | index-for-walk | record -> record[i] |
| `VoiceSystem_Init` | game/VoiceSystem_Init | 90.41 | 191 | 189 | 89.8 -> 90.52 | inline-to-named-locals | VoiceSystem_ClearPlayCounts@3668 subst front order i_,clips |
| `KartMovement_RotateByYaw` | game/kartmove/KartMovement_RotateByYaw | 96.12 | 286 | 284 | 96.12 -> 96.16 | inline-to-named-locals | TransformVector@110 subst front |
| `DrawEffect_ItemHitBurst_Spawn` | game/DrawEffect_ItemHitBurst_Spawn | 96.97 | 295 | 288 | 96.57 -> 96.14 | arg-order-prototype | Item_ProbeForwardGroundPitch order [1, 2, 3, 0] |
| `Race_PerFrameTickAndAudio` | game/RacePerFrame | 96.41 | 376 | 330 | 95.55 -> 95.67 | index-for-walk | other -> other[j] |
| `ExplosionTumble_Init` | game/ExplosionTumble_Init | 94.86 | 407 | 381 | 94.86 -> 95.15 | inline-to-named-locals | NormalizeCopy@487 subst front |
| `fn_80234840` | game/FlowCardCheck_nm2 | 95.73 | 427 | 418 | 95.73 -> 95.56 | inline-to-named-locals | SetCharaGroupForPlayer@2701 subst front |
| `RaceFlow_ResetState_FullColdInit` | game/RaceFlow_ResetState_FullColdInit | 90.00 | 598 | 597 | 90.0 -> 75.66 | inline-to-named-locals | RaceEntries_Reset@171 subst front |
| `NameCheck_ScanBannedWords` | game/NameCheck_CardName | 97.46 | 799 | 771 | 97.35 -> 97.44 | index-for-walk | sets -> sCharacterSets[group] |
| `TransitionEffect_RenderPass` | game/TransitionEffect | 99.77 | 824 | 818 | 99.75 -> 99.14 | inline-to-named-locals | ScreenFlatQuad@4391 locals front order a_,b_,g_,r_ |
| `fn_8022BFA8` | game/EnemyFaceDraw | 88.04 | 996 | 976 | 86.82 -> 86.88 | inline-to-named-locals | FillFaceUV@3989 subst front |
| `fn_8018B31C` | game/bitread/fn_8018B31C | 94.34 | 1474 | 1466 | 94.26 -> 94.28 | inline-to-named-locals | WriteBits@2089 subst front |

## Levers not automated here

| lever | rule | class | landed by | why |
| --- | --- | --- | --- | --- |
| rolled-loop + opt_unroll_instr_count | loop-unroll-budget | semi | 833c85a | pragma half is automatic (pragmasweep --set extended sweeps opt_unroll_instr_count 8/16/32); rolling a hand-unrolled loop back needs the loop count and the induction step, which differ per site |
| base vtable store in the ctor body | base-init-in-body | semi | §36 | needs the base class vtable symbol and a ctor that has address locals; trigger (prologue lis/addi swap) is cheap but there were 2 C++ ctors near misses with that shape, done by hand |
| avoid IRO CSE temps | - | semi | 3cc4b0e | the rewrite (read through a cast pointer / hoist before) is a fakematch-flavoured choice per site; shapesweep hoist covers the hoist half, the trigger needs a mwtrace TEMPNEW trace |
| pool-owner TU merges | merge-pool-owner | semi | 7653d99 | pool_audit.py finds them; the merge edits splits.txt/configure.py/symbols and has to respect claims |
| TU merges (correct structure) | merge-pool-owner | manual | 5d5f466b | tu_audit.py proposes; each merge is a splits/configure/extab job checked against main.dol |
