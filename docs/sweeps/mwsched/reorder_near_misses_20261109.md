# mwsched explain over pure-reordering near misses (2026-11-09)

Functions >= 95% whose ours/target instructions are the same multiset in a different order
(register numbers ignored), run through `python3 tools/mwsched.py explain UNIT FN --run`
at main e1e979c. Each line: an instruction pair in our order (target has the opposite) and
the scheduler's reason. How to act on a reason (docs/mwcc_internals.md):

- `order`: full tie, the earlier PCode wins. Swap the two source statements/expressions.
- `rank`: tie broken by opcode rank (stores 1 < ALU 2 < loads 3, mr 0). Needs a different DAG, not a different order.
- `critical` / `height` / `uncovering`: change the DAG (add/remove a dependence; a shared variable gives a WAR edge).
- `dependence ... memory (may_alias)`: the two accesses may alias. `__restrict`/const on a pointer PARAMETER, or a different base object.
- `dependence ... RAW`: a real data dependence: the target computes it differently.
- `not ready` / `unit busy`: an earlier pick or a latency decides; look at the previous picks (`mwsched.py log`).
- no rows: the order difference is outside the pre-RA scheduler (post-RA blocks, peephole) or the pairing failed.

| fn | unit | % | diff rows | reasons |
|---|---|---|---|---|
| `fn_80227B98` | game/DNBress_nm3 | 99.17 | 2 | debugger failed |
| `Effect_DustBurst4_Update` | game/EffectDustBurst4 | 98.43 | 2 | not ready, order, critical |
| `EffectItemChainIndicator_Tick` | game/EffectItemChainIndicator_Tick | 99.70 | 2 | rank |
| `fn_80245E6C` | game/HudFlow20Update | 98.92 | 2 | uncovering |
| `SpriteGroup_CreateOrInit` | game/SpriteGroupCreate | 95.65 | 2 | not ready x2, memory |
| `Terrain_WallEdgeTest` | game/Terrain_WallEdgeTest | 99.42 | 2 | - |
| `CalcEarnedCoins` | game/anon_80216568 | 98.53 | 2 | - |
| `fn_801C0568` | game/fn_801BAA88 | 99.86 | 2 | not ready, order, critical |
| `fn_801D7610` | game/fn_801D7610 | 99.94 | 2 | - |
| `fn_80243074` | game/fn_80243074 | 99.28 | 2 | order |
| `fn_8028CB64` | triforce/amnet_nm3 | 96.55 | 2 | - |
| `fn_802854B0` | triforce/jvsio | 99.88 | 2 | - |
| `CardData_InitDefaults` | game/CardData_InitDefaults | 99.92 | 3 | - |
| `fn_8018F8A8` | game/objview/fn_8018F8A8 | 99.05 | 3 | rank x2 |
| `VoiceEvent_PushRace` | game/sprite/VoiceEvent_PushRace | 98.71 | 3 | order, unit was busy |
| `Card_VerifyChecksum` | game/Card_VerifyChecksum | 96.21 | 4 | - |
| `fn_8022ACE4` | game/EnemyFace | 98.61 | 4 | debugger failed |
| `Terrain_GetGroundHeightWithPenetration` | game/Terrain_GetGroundHeight | 98.91 | 4 | - |
| `fn_801D4DC0` | game/fn_801D4DC0 | 96.49 | 4 | - |
| `fn_801AC208` | game/sprite/fn_801AC208 | 99.68 | 4 | - |
| `BackupReadRecord` | triforce/ambackup_nm2 | 97.46 | 5 | not ready, critical, height, rank |
| `CardSaveData_Parser` | game/CardSaveData_Parser | 97.98 | 6 | - |
| `KartPhysics_ApplyCollisionForce` | game/KartPhysics_ApplyCollisionForce | 98.64 | 6 | uncovering x3, not ready |
| `TaMode_FrameUpdate` | game/TaMode_FrameUpdate | 99.64 | 6 | - |
| `fn_801AECF4` | game/sprite/fn_801AECF4 | 99.42 | 7 | critical |
| `AI_SystemDtor` | game/AI_SystemDtor | 99.53 | 8 | memory x4 |
| `GabyouItem_Tick_HeldAndHoming_2Eto31` | game/GabyouItemHeld | 99.38 | 8 | - |
| `fn_802386E0` | game/ItemSelectRefill | 95.05 | 8 | order, RAW x2 |
| `fn_802867B8` | triforce/random_nm1 | 95.23 | 8 | - |
| `SetCourseParams` | game/SetCourseParams | 95.44 | 10 | uncovering x9, critical, order |
| `fn_8028D8CC` | triforce/amnet_setup_nm | 99.25 | 14 | - |
| `fn_80172948` | game/HomingMarkerUpdate | 95.86 | 30 | - |

## Details

### Effect_DustBurst4_Update (game/EffectDustBurst4)
```
ours: addi    r28,r28,4  before  cmpwi   r31,4   (lines 110, 110)
   -> #3 not ready at cycle 0: earliest 1 (latency of a predecessor)
ours: addi    r28,r28,4  before  addi    r30,r30,36   (lines 110, 110)
   -> cycle 0: both ready, #1 wins on order: #1 {'critical': False, 'uncovering': 0, 'height': 1, 'rank': 2} vs #2 {'critical': False, 'uncovering': 0, 'height': 1, 'rank': 2}
ours: cmpwi   r31,4  before  addi    r30,r30,36   (lines 110, 110)
   -> cycle 1: both ready, #3 wins on critical: #3 {'critical': True, 'uncovering': 0, 'height': 3, 'rank': 1} vs #2 {'critical': False, 'uncovering': 0, 'height': 1, 'rank': 2}
```

### EffectItemChainIndicator_Tick (game/EffectItemChainIndicator_Tick)
```
ours: mr      r31,r28  before  addi    r30,r1,156   (lines 0, 0)
   -> cycle 0: both ready, #1 wins on rank: #1 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 0} vs #2 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2}
```

### fn_80245E6C (game/HudFlow20Update)
```
ours: lwz     r30,28(r31)  before  addi    r3,r3,0   (lines 56, 55)
   -> cycle 1: both ready, #6 wins on uncovering: #6 {'critical': False, 'uncovering': 1, 'height': 3, 'rank': 3} vs #3 {'critical': False, 'uncovering': 0, 'height': 6, 'rank': 2}
```

### SpriteGroup_CreateOrInit (game/SpriteGroupCreate)
```
ours: li      r3,48  before  stw     r0,0(r28)   (lines 4, 4)
   -> #1 not ready at cycle 0: earliest 1 (latency of a predecessor)
ours: li      r3,48  before  lwz     r30,0(r30)   (lines 4, 4)
   -> #2 not ready at cycle 0 when #3 issued: waits on preds #1 stw r44,r33,0
ours: stw     r0,0(r28)  before  lwz     r30,0(r30)   (lines 4, 4)
   -> dependence: #1 stw r44,r33,0 -> #2 lwz r40,r35,0 [memory (may_alias)]
```

### fn_801C0568 (game/fn_801BAA88)
```
ours: lwz     r3,0(r31)  before  subfic  r0,r0,1   (lines 1261, 1260)
   -> #1 not ready at cycle 1: earliest 2 (latency of a predecessor)
ours: lwz     r3,0(r31)  before  lwz     r4,20(r30)   (lines 1261, 1261)
   -> cycle 1: both ready, #5 wins on order: #5 {'critical': False, 'uncovering': 0, 'height': 2, 'rank': 3} vs #6 {'critical': False, 'uncovering': 0, 'height': 2, 'rank': 3}
ours: subfic  r0,r0,1  before  lwz     r4,20(r30)   (lines 1260, 1261)
   -> cycle 2: both ready, #1 wins on critical: #1 {'critical': True, 'uncovering': 1, 'height': 4, 'rank': 2} vs #6 {'critical': False, 'uncovering': 0, 'height': 2, 'rank': 3}
```

### fn_80243074 (game/fn_80243074)
```
ours: lfs     f5,68(r1)  before  lfs     f7,72(r1)   (lines 60, 60)
   -> cycle 0: both ready, #2 wins on order: #2 {'critical': False, 'uncovering': 1, 'height': 20, 'rank': 3} vs #4 {'critical': False, 'uncovering': 1, 'height': 20, 'rank': 3}
```

### fn_8018F8A8 (game/objview/fn_8018F8A8)
```
ours: mr      r31,r27  before  addi    r30,r1,8   (lines 24, 24)
   -> cycle 0: both ready, #2 wins on rank: #2 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 0} vs #0 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2}
ours: mr      r31,r27  before  addi    r29,r1,16   (lines 24, 24)
   -> cycle 0: both ready, #2 wins on rank: #2 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 0} vs #1 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2}
```

### VoiceEvent_PushRace (game/sprite/VoiceEvent_PushRace)
```
ours: addi    r6,r31,5428  before  add     r7,r0,r4   (lines 69, 0)
   -> cycle 3: both ready, #0 wins on order: #0 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2} vs #4 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2}
ours: subf    r3,r5,r27  before  add     r7,r0,r4   (lines 0, 0)
   -> #4 preferred but its unit was busy at cycle 3
```

### BackupReadRecord (triforce/ambackup_nm2)
```
ours: addi    r6,r4,0  before  and     r25,r7,r5   (lines 37, 36)
   -> #10 not ready at cycle 6: earliest 7 (latency of a predecessor)
ours: addi    r6,r4,0  before  rlwinm  r4,r8,28,31,31   (lines 37, 37)
   -> cycle 6: both ready, #15 wins on critical: #15 {'critical': True, 'uncovering': 1, 'height': 2, 'rank': 2} vs #12 {'critical': False, 'uncovering': 0, 'height': 1, 'rank': 2}
ours: lwz     r5,16(r24)  before  rlwinm  r4,r8,28,31,31   (lines 37, 37)
   -> cycle 8: both ready, #13 wins on height: #13 {'critical': True, 'uncovering': 0, 'height': 2, 'rank': 3} vs #12 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2}
ours: mr      r7,r25  before  rlwinm  r4,r8,28,31,31   (lines 37, 37)
   -> cycle 8: both ready, #16 wins on rank: #16 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 0} vs #12 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2}
```

### KartPhysics_ApplyCollisionForce (game/KartPhysics_ApplyCollisionForce)
```
ours: stfs    f5,28(r1)  before  mr      r4,r3   (lines 136, 138)
   -> cycle 1: both ready, #0 wins on uncovering: #0 {'critical': False, 'uncovering': 1, 'height': 2, 'rank': 1} vs #6 {'critical': False, 'uncovering': 0, 'height': 1, 'rank': 0}
ours: stfs    f5,28(r1)  before  fadds   f0,f0,f6   (lines 136, 137)
   -> #4 not ready at cycle 1: earliest 2 (latency of a predecessor)
ours: lfs     f2,208(r31)  before  lfs     f5,212(r31)   (lines 154, 154)
   -> cycle 1: both ready, #1 wins on uncovering: #1 {'critical': True, 'uncovering': 1, 'height': 4, 'rank': 3} vs #0 {'critical': True, 'uncovering': 0, 'height': 4, 'rank': 3}
ours: lfs     f1,16(r1)  before  lfs     f0,76(r31)   (lines 154, 154)
   -> cycle 0: both ready, #0 wins on uncovering: #0 {'critical': True, 'uncovering': 1, 'height': 21, 'rank': 3} vs #3 {'critical': True, 'uncovering': 0, 'height': 21, 'rank': 3}
```

### fn_801AECF4 (game/sprite/fn_801AECF4)
```
ours: add     r6,r7,r6  before  addi    r0,r3,0   (lines 60, 60)
   -> cycle 6: both ready, #8 wins on critical: #8 {'critical': True, 'uncovering': 1, 'height': 6, 'rank': 2} vs #19 {'critical': False, 'uncovering': 0, 'height': 2, 'rank': 2}
```

### AI_SystemDtor (game/AI_SystemDtor)
```
ours: stw     r4,4(r5)  before  stw     r3,0(r5)   (lines 44, 44)
   -> dependence: #0 stw r45,r37,4 -> #1 stw r46,r37,0 [memory (may_alias)]
ours: stw     r4,60(r5)  before  stw     r3,56(r5)   (lines 0, 0)
   -> dependence: #11 stw r45,r37,0x3c -> #12 stw r46,r37,0x38 [memory (may_alias)]
ours: stw     r4,116(r5)  before  stw     r3,112(r5)   (lines 0, 0)
   -> dependence: #22 stw r45,r37,0x74 -> #23 stw r46,r37,0x70 [memory (may_alias)]
ours: stw     r4,172(r5)  before  stw     r3,168(r5)   (lines 0, 0)
   -> dependence: #33 stw r45,r37,0xac -> #34 stw r46,r37,0xa8 [memory (may_alias)]
```

### fn_802386E0 (game/ItemSelectRefill)
```
ours: addi    r29,r26,432  before  addi    r28,r26,476   (lines 33, 34)
   -> cycle 4: both ready, #7 wins on order: #7 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2} vs #8 {'critical': True, 'uncovering': 0, 'height': 1, 'rank': 2}
ours: add     r3,r3,r0  before  addi    r0,r3,192   (lines 37, 37)
   -> dependence: #2 add r76,r74,r75 -> #3 addi r77,r76,0xc0 [RAW r76]
ours: add     r3,r3,r0  before  addi    r0,r3,192   (lines 45, 45)
   -> dependence: #2 add r100,r98,r99 -> #3 addi r101,r100,0xc0 [RAW r100]
```

### SetCourseParams (game/SetCourseParams)
```
ours: li      r4,1  before  addi    r7,r30,25416   (lines 140, 130)
   -> cycle 1: both ready, #26 wins on uncovering: #26 {'critical': True, 'uncovering': 6, 'height': 3, 'rank': 4} vs #1 {'critical': True, 'uncovering': 2, 'height': 3, 'rank': 2}
ours: li      r4,1  before  li      r0,-1   (lines 140, 151)
   -> cycle 1: both ready, #26 wins on uncovering: #26 {'critical': True, 'uncovering': 6, 'height': 3, 'rank': 4} vs #55 {'critical': True, 'uncovering': 0, 'height': 3, 'rank': 4}
ours: li      r4,1  before  stw     r5,0(r8)   (lines 140, 133)
   -> cycle 1: both ready, #26 wins on critical: #26 {'critical': True, 'uncovering': 6, 'height': 3, 'rank': 4} vs #3 {'critical': False, 'uncovering': 0, 'height': 2, 'rank': 1}
ours: addi    r6,r29,24428  before  addi    r7,r30,25416   (lines 129, 130)
   -> cycle 2: both ready, #0 wins on uncovering: #0 {'critical': True, 'uncovering': 3, 'height': 3, 'rank': 2} vs #1 {'critical': True, 'uncovering': 2, 'height': 3, 'rank': 2}
ours: addi    r6,r29,24428  before  li      r0,-1   (lines 129, 151)
   -> cycle 2: both ready, #0 wins on uncovering: #0 {'critical': True, 'uncovering': 3, 'height': 3, 'rank': 2} vs #55 {'critical': True, 'uncovering': 0, 'height': 3, 'rank': 4}
ours: addi    r6,r29,24428  before  stw     r5,0(r8)   (lines 129, 133)
   -> cycle 2: both ready, #0 wins on uncovering: #0 {'critical': True, 'uncovering': 3, 'height': 3, 'rank': 2} vs #3 {'critical': True, 'uncovering': 0, 'height': 2, 'rank': 1}
ours: addi    r6,r29,24428  before  stw     r5,4(r8)   (lines 129, 134)
   -> cycle 2: both ready, #0 wins on uncovering: #0 {'critical': True, 'uncovering': 3, 'height': 3, 'rank': 2} vs #4 {'critical': True, 'uncovering': 0, 'height': 2, 'rank': 1}
ours: li      r3,4  before  li      r0,-1   (lines 148, 151)
   -> cycle 3: both ready, #50 wins on order: #50 {'critical': True, 'uncovering': 1, 'height': 3, 'rank': 4} vs #55 {'critical': True, 'uncovering': 1, 'height': 3, 'rank': 4}
ours: li      r3,4  before  stw     r5,0(r8)   (lines 148, 133)
   -> cycle 3: both ready, #50 wins on uncovering: #50 {'critical': True, 'uncovering': 1, 'height': 3, 'rank': 4} vs #3 {'critical': True, 'uncovering': 0, 'height': 2, 'rank': 1}
ours: li      r3,4  before  stw     r5,4(r8)   (lines 148, 134)
   -> cycle 3: both ready, #50 wins on uncovering: #50 {'critical': True, 'uncovering': 1, 'height': 3, 'rank': 4} vs #4 {'critical': True, 'uncovering': 0, 'height': 2, 'rank': 1}
ours: li      r0,-1  before  stw     r5,0(r8)   (lines 151, 133)
   -> cycle 3: both ready, #55 wins on uncovering: #55 {'critical': True, 'uncovering': 1, 'height': 3, 'rank': 4} vs #3 {'critical': True, 'uncovering': 0, 'height': 2, 'rank': 1}
```
