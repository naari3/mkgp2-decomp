# The 158 inline-asm functions, split for sharing out (2026-11-09)

`tools/scan_asm_fns.py` at main of 2026-11-09 13:15Z lists 158 functions
still written as `asm` inside Matching TUs (122 344 bytes). objdiff counts
them as matched; the project is not at a real 100 % until each is either C/C++
or confirmed to be asm in the original source as well. Proposed split, posted
on the agent board (`to_onmokoworks.md`, n3-20261109 proposal):

| group | functions | bytes | notes |
|---|---|---|---|
| A. SDK / libraries | 91 | 10 028 | Dolphin OS/PPCArch/OSCache/OSContext/PSMTX, TRK, `__start`/init, MusyX (reverb/chorus/snd_service), HSD. Many of these are asm in the original SDK/library source too (paired-single math, exception vectors, cache ops): compare with doldecomp/mkdd, doldecomp/melee and AxioDL/musyx first and mark those as done. The rest is mostly compiler-flag work. |
| B. Card / THP / net | 5 | 11 968 | the magnetic-card state machines. No THP or network function is left in asm. |
| C. Game functions | 62 | 100 348 | the big ones (CGameCoin_Update 8.5 KB, ShadowBillboard_Tick 7.7 KB, VSMode_*, RaceHud/Scene/SceneList fns, the ONKARTHIT block). Most were parked by the asm->C threads; drafts in `docs/wip/` and rows in `docs/gave_up.md`. |

Regenerate: `python3 tools/scan_asm_fns.py --json` (the lists below were
made from it; card group = the five `card_*` / `CardSave_*` TUs).

## Group A checked against reference decomps (n3, 2026-11-09)

Every group A function was looked up in doldecomp/dolsdk2004, doldecomp/mkdd,
doldecomp/melee, AxioDL/musyx and projectPiki/pikmin2 (TRK `targimpl.c`).

- **89 functions are `asm` in the references too** (the SDK itself for
  `__start`/`__ppc_eabi_init`, PPCArch, db, OS, OSAlarm, OSCache, OSContext,
  OSExec, OSInterrupt, OSMemory, OSReset, OSSync, OSTime, PS mtx/mtxvec/mtx44/vec,
  ai; TRK targimpl; MusyX snd_service/reverb/chorus). They stay asm and are
  done. One caveat: `Run` (OSExec) is asm in dolsdk2004 and in melee's
  OSReboot.c.
- **`HSD_SaveContext`** has no reference (melee calls `OSSaveContext`
  instead), but its body is `mtsprg`/`mfspr GQRn`/`stmw r0` and a tail
  branch, which MWCC cannot emit from C. Stays asm, done.
- **`HSD_MtxInverseConcat`** was compiled C (MWCC prologue with
  `stfd`/`psq_st` saves; C in melee). mkgp2's version returns int and tests
  `det == 0`. Converted to C at 100 % (main.dol OK).

So group A has no C work left.

## A. SDK / libraries (Dolphin OS/PPC/mtx, TRK, init, MusyX, HSD): 91 functions, 10028 bytes

| address | size | TU (src/) | function |
|---|---|---|---|
| 800032B0 | 144 | init/__start.c | __init_registers |
| 80003400 | 36 | init/__init_hardware.c | __init_hardware |
| 80003424 | 52 | init/__flush_cache.c | __flush_cache |
| 802557C0 | 8 | dolphin/base/PPCArch.c | PPCMfmsr |
| 802557C8 | 8 | dolphin/base/PPCArch.c | PPCMtmsr |
| 802557D0 | 8 | dolphin/base/PPCArch.c | PPCMfhid0 |
| 802557D8 | 8 | dolphin/base/PPCArch.c | PPCMthid0 |
| 802557E0 | 8 | dolphin/base/PPCArch.c | PPCMfl2cr |
| 802557E8 | 8 | dolphin/base/PPCArch.c | PPCMtl2cr |
| 802557F0 | 8 | dolphin/base/PPCArch.c | PPCMtdec |
| 802557F8 | 8 | dolphin/base/PPCArch.c | PPCSync |
| 80255800 | 20 | dolphin/base/PPCArch.c | PPCHalt |
| 80255814 | 8 | dolphin/base/PPCArch.c | PPCMtmmcr0 |
| 8025581C | 8 | dolphin/base/PPCArch.c | PPCMtmmcr1 |
| 80255824 | 8 | dolphin/base/PPCArch.c | PPCMfpmc1 |
| 8025582C | 8 | dolphin/base/PPCArch.c | PPCMtpmc1 |
| 80255834 | 8 | dolphin/base/PPCArch.c | PPCMfpmc2 |
| 8025583C | 8 | dolphin/base/PPCArch.c | PPCMtpmc2 |
| 80255844 | 8 | dolphin/base/PPCArch.c | PPCMfpmc3 |
| 8025584C | 8 | dolphin/base/PPCArch.c | PPCMtpmc3 |
| 80255854 | 8 | dolphin/base/PPCArch.c | PPCMfpmc4 |
| 8025585C | 8 | dolphin/base/PPCArch.c | PPCMtpmc4 |
| 802558AC | 8 | dolphin/base/PPCArch.c | PPCMfhid2 |
| 802558B4 | 8 | dolphin/base/PPCArch.c | PPCMthid2 |
| 802558BC | 8 | dolphin/base/PPCArch.c | PPCMtwpar |
| 802558EC | 8 | dolphin/base/PPCArch.c | PPCSetFpNonIEEEMode |
| 80255964 | 16 | dolphin/db/db.c | __DBExceptionDestination |
| 802559E0 | 296 | dolphin/os/OS.c | __OSFPRInit |
| 802562CC | 36 | dolphin/os/OS.c | __OSDBIntegrator |
| 802562F0 | 4 | dolphin/os/OS.c | __OSDBJump |
| 80256324 | 156 | dolphin/os/OS.c | OSExceptionVector |
| 802563C0 | 88 | dolphin/os/OS.c | OSDefaultExceptionHandler |
| 80256B18 | 80 | dolphin/os/OSAlarm.c | DecrementerExceptionHandler |
| 80256EE8 | 20 | dolphin/os/OSCache.c | DCEnable |
| 80256EFC | 44 | dolphin/os/OSCache.c | DCInvalidateRange |
| 80256F28 | 48 | dolphin/os/OSCache.c | DCFlushRange |
| 80256F58 | 48 | dolphin/os/OSCache.c | DCStoreRange |
| 80256F88 | 44 | dolphin/os/OSCache.c | DCFlushRangeNoSync |
| 80256FB4 | 44 | dolphin/os/OSCache.c | DCStoreRangeNoSync |
| 80256FE0 | 52 | dolphin/os/OSCache.c | ICInvalidateRange |
| 80257014 | 16 | dolphin/os/OSCache.c | ICFlashInvalidate |
| 80257024 | 20 | dolphin/os/OSCache.c | ICEnable |
| 80257038 | 40 | dolphin/os/OSCache.c | LCDisable |
| 8025734C | 292 | dolphin/os/OSContext.c | __OSLoadFPUContext |
| 80257470 | 296 | dolphin/os/OSContext.c | __OSSaveFPUContext |
| 80257598 | 8 | dolphin/os/OSContext.c | OSSaveFPUContext |
| 802575A0 | 92 | dolphin/os/OSContext.c | OSSetCurrentContext |
| 80257608 | 128 | dolphin/os/OSContext.c | OSSaveContext |
| 80257688 | 216 | dolphin/os/OSContext.c | OSLoadContext |
| 80257760 | 8 | dolphin/os/OSContext.c | OSGetStackPointer |
| 8025778C | 188 | dolphin/os/OSContext.c | OSInitContext |
| 80257AF0 | 132 | dolphin/os/OSContext.c | OSSwitchFPUContext |
| 80257BBC | 300 | dolphin/os/OSContext.c | OSFillFPUContext |
| 80258370 | 60 | dolphin/os/OSExec.c | Run |
| 80259A1C | 20 | dolphin/os/OSInterrupt.c | OSDisableInterrupts |
| 80259A30 | 20 | dolphin/os/OSInterrupt.c | OSEnableInterrupts |
| 80259A44 | 36 | dolphin/os/OSInterrupt.c | OSRestoreInterrupts |
| 8025A238 | 80 | dolphin/os/OSInterrupt.c | ExternalInterruptHandler |
| 8025A558 | 128 | dolphin/os/OSMemory.c | Config24MB |
| 8025A5D8 | 128 | dolphin/os/OSMemory.c | Config48MB |
| 8025A658 | 24 | dolphin/os/OSMemory.c | RealMode |
| 8025A9D0 | 112 | dolphin/os/OSReset.c | Reset |
| 8025BA14 | 32 | dolphin/os/OSSync.c | SystemCallVector |
| 8025CC68 | 24 | dolphin/os/OSTime.c | OSGetTime |
| 8025CC80 | 8 | dolphin/os/OSTime.c | OSGetTick |
| 8025D1B8 | 52 | dolphin/mtx/mtx.c | PSMTXCopy |
| 8025D494 | 204 | dolphin/mtx/mtx.c | PSMTXConcat |
| 8025D5B0 | 248 | dolphin/mtx/mtx.c | PSMTXInverse |
| 8025D6A8 | 200 | dolphin/mtx/mtx.c | PSMTXInvXpose |
| 8025DA20 | 76 | dolphin/mtx/mtx.c | PSMTXTransApply |
| 8025DF40 | 84 | dolphin/mtx/mtxvec.c | PSMTXMultVec |
| 8025DF94 | 84 | dolphin/mtx/mtxvec.c | PSMTXMultVecSR |
| 8025E220 | 68 | dolphin/mtx/mtx44.c | PSMTX44Copy |
| 8025E264 | 36 | dolphin/mtx/vec.c | PSVECAdd |
| 8025E388 | 60 | dolphin/mtx/vec.c | PSVECCrossProduct |
| 80260D5C | 88 | dolphin/ai/ai.c | __AICallbackStackSwitch |
| 8026DA7C | 8 | TRK_MINNOW_DOLPHIN/targimpl.c | __TRK_get_MSR |
| 8026DA84 | 8 | TRK_MINNOW_DOLPHIN/targimpl.c | __TRK_set_MSR |
| 8026DA8C | 60 | TRK_MINNOW_DOLPHIN/targimpl.c | TRK_ppc_memcpy |
| 8026DAC8 | 404 | TRK_MINNOW_DOLPHIN/targimpl.c | TRKInterruptHandler |
| 8026DC5C | 156 | TRK_MINNOW_DOLPHIN/targimpl.c | TRKExceptionHandler |
| 8026DCF8 | 196 | TRK_MINNOW_DOLPHIN/targimpl.c | TRKSwapAndGo |
| 8026DDBC | 84 | TRK_MINNOW_DOLPHIN/targimpl.c | TRKInterruptHandlerEnableInterrupts |
| 802B94F4 | 84 | musyx/runtime/snd_service.c | sndSqrt |
| 802B9548 | 212 | musyx/runtime/snd_service.c | sndCos |
| 802BBFE4 | 388 | musyx/runtime/reverb.c | DoCrossTalk |
| 802BC168 | 1292 | musyx/runtime/reverb.c | HandleReverb |
| 802BC754 | 408 | musyx/runtime/chorus_fx.c | do_src1 |
| 802BC8EC | 492 | musyx/runtime/chorus_fx.c | do_src2 |
| 802D61E8 | 1072 | sysdolphin/baselib/mtx.c | HSD_MtxInverseConcat |
| 802E51F4 | 152 | sysdolphin/baselib/debug.c | HSD_SaveContext |

## B. Card / THP / net: 5 functions, 11968 bytes

| address | size | TU (src/) | function |
|---|---|---|---|
| 800937D4 | 1108 | game/CardSave_Tick_CaptureAndStart.c | CardSave_Tick_CaptureAndStart |
| 80093C28 | 2276 | game/card_save_trigger.c | card_save_trigger |
| 80096034 | 2600 | game/card_rw_state_machine_short.c | card_rw_state_machine_short |
| 80096A5C | 2816 | game/card_rw_state_machine.c | card_rw_state_machine |
| 800976C0 | 3168 | game/card_read_state_machine.c | card_read_state_machine |

## C. Game functions: 62 functions, 100348 bytes

| address | size | TU (src/) | function |
|---|---|---|---|
| 80044D50 | 3072 | game/KartDriver_InitFull.c | KartDriver_InitFull |
| 8004A238 | 1664 | game/auto_ONKARTHIT_block.c | KartItem_OnKartHit |
| 8004B140 | 596 | game/auto_ONKARTHIT_block.c | KartItem_ApplyImpactReflectAndDampVelocity |
| 8004B49C | 1312 | game/auto_ONKARTHIT_block.c | KartItem_ApplyImpactImpulseAndRumble |
| 8004BAAC | 2164 | game/auto_ONKARTHIT_block.c | KartItem_Tick |
| 8004C320 | 3140 | game/auto_ONKARTHIT_block.c | KartItem_PerFrameStep |
| 8004D404 | 2760 | game/auto_ONKARTHIT_block.c | CarObject_MainUpdate |
| 8004E618 | 1980 | game/auto_ONKARTHIT_block.c | CarObject_Init |
| 8004F858 | 1976 | game/auto_ONKARTHIT_block.c | CarObject_HandleItemEffect |
| 80051834 | 572 | game/auto_ONKARTHIT_block.c | ItemEffect_Trap |
| 80051A70 | 584 | game/auto_ONKARTHIT_block.c | ItemEffect_Projectile |
| 80051DEC | 876 | game/auto_ONKARTHIT_block.c | CarObjectManager_RunKartKartCollisionSweep |
| 800522D0 | 452 | game/auto_ONKARTHIT_block.c | Bitset_Init |
| 8005249C | 8 | game/auto_ONKARTHIT_block.c | fn_8005249C |
| 800524A4 | 8 | game/auto_ONKARTHIT_block.c | KartItem_TryDropCoinsAndPlaySE_AdjThunk |
| 800524AC | 8 | game/auto_ONKARTHIT_block.c | fn_800524AC |
| 800524B4 | 8 | game/auto_ONKARTHIT_block.c | fn_800524B4 |
| 800524BC | 8 | game/auto_ONKARTHIT_block.c | KartItem_PlayHitSE_DifferentVictim_AdjThunk |
| 800524C4 | 8 | game/auto_ONKARTHIT_block.c | KartItem_ApplyEffectToVictim_AdjThunk |
| 8005E46C | 796 | game/clItemBoxResponder_SpawnDebris.c | clItemBoxResponder_SpawnDebris |
| 80061054 | 832 | game/clMiyoshiCardCreate.c | clMiyoshiCardCreate_Draw |
| 80061394 | 724 | game/clMiyoshiCardCreate.c | clMiyoshiCardCreate_Tick |
| 80061A88 | 7700 | game/ShadowBillboard.c | ShadowBillboard_Tick |
| 80091438 | 1060 | game/ItemEffectBus.c | ItemEffectBus_ApplyItemEventClear |
| 8009D6CC | 1460 | game/RaceContext_InitDefaults.c | RaceContext_InitDefaults |
| 8009E0D4 | 5032 | game/VSMode_FrameUpdate.c | VSMode_FrameUpdate |
| 8009F814 | 3516 | game/VSMode_FrameUpdate.c | VSMode_Init |
| 800A981C | 368 | game/auto_800A8F4C_block.c | WarpZone_CheckEntry |
| 801232E0 | 412 | game/ZoneList.c | fn_801232E0 |
| 801289B8 | 3260 | game/NokoNoko_801287F8.cpp | NokoNokoChallenge_Update |
| 8012C538 | 8548 | game/CGameCoin_8012BF5C.cpp | CGameCoin_Update |
| 80135EFC | 588 | game/RivalRun.c | RivalRun_UpdatePathFollower |
| 80136148 | 1708 | game/RivalRun.c | RivalRun_RivalTactics |
| 801367F4 | 948 | game/RivalRun.c | RivalRun_CalcPathDistance |
| 8013732C | 604 | game/RivalRun.c | RivalRun_RivalInit |
| 80139898 | 3228 | game/CoinSystem_UpdateAll.c | CoinSystem_UpdateAll |
| 8013AE20 | 1248 | game/csAnim.c | fn_8013AE20 |
| 8013CC24 | 2188 | game/KartPreview.c | fn_8013CC24 |
| 8013DA00 | 200 | game/PreviewModel.c | fn_8013DA00 |
| 80141454 | 1124 | game/LogoAnim.c | fn_80141454 |
| 80147900 | 500 | game/RaceHud_80147470.cpp | fn_80147900 |
| 80147AF4 | 500 | game/RaceHud_80147470.cpp | fn_80147AF4 |
| 80147CE8 | 512 | game/RaceHud_80147470.cpp | fn_80147CE8 |
| 80148A44 | 1848 | game/RaceHud_80147470.cpp | fn_80148A44 |
| 80149E44 | 2636 | game/RaceHud_80147470.cpp | fn_80149E44 |
| 8014ADB4 | 868 | game/RaceHud_80147470.cpp | fn_8014ADB4 |
| 8014BBE4 | 924 | game/RaceHud_80147470.cpp | fn_8014BBE4 |
| 8014C53C | 2360 | game/RaceHud_80147470.cpp | fn_8014C53C |
| 8014E804 | 2400 | game/Scene_8014E0C4.cpp | fn_8014E804 |
| 801500F4 | 440 | game/Scene_8014E0C4.cpp | fn_801500F4 |
| 801502AC | 880 | game/Scene_8014E0C4.cpp | fn_801502AC |
| 80154304 | 3244 | game/Scene_8014E0C4.cpp | fn_80154304 |
| 80157DE0 | 200 | game/SceneList_80157EA8.cpp | fn_80157DE0 |
| 80158CE4 | 1144 | game/fn_80157DE0.cpp | fn_80158CE4 |
| 8015915C | 1400 | game/fn_80157DE0.cpp | fn_8015915C |
| 801596D4 | 1276 | game/fn_80157DE0.cpp | fn_801596D4 |
| 80159BD0 | 2836 | game/fn_80157DE0.cpp | fn_80159BD0 |
| 8015A6E4 | 1880 | game/SceneList_80157EA8.cpp | fn_8015A6E4 |
| 80192884 | 1664 | game/SoundMgr_Play.c | SoundMgr_Play |
| 801C9EAC | 3856 | game/clFlowRound.c | clFlowRound_Update |
| 801D7920 | 560 | game/clFlowKart_UpdateDisplay.c | clFlowKart_UpdateDisplay |
| 80211E6C | 1680 | game/JumpDistanceMode_Update.c | JumpDistanceMode_Update |


## Status of group C at 2026-11-09 20:50Z (main 8e38341)

The table above is the list as of 13:15Z. Since then (`tools/scan_asm_fns.py`):

| function | was in | now | by |
|---|---|---|---|
| ShadowBillboard_Tick | game/ShadowBillboard.c | C, 100 % (52a998d) | om |
| NokoNokoChallenge_Update | game/NokoNoko_801287F8.cpp | C, 100 % (45398a4) | om |
| clMiyoshiCardCreate_Draw | game/clMiyoshiCardCreate.c | C, 100 % (ce9aa1f) | om |
| Bitset_Init | game/auto_ONKARTHIT_block.c | C, 100 % (8a5f463) | om |
| JumpDistanceMode_Update | game/JumpDistanceMode_Update.c | C, 100 % (d38113c) | n3 |
| clFlowKart_UpdateDisplay | game/clFlowKart_UpdateDisplay.c | C, 100 %, inside the merged game/clFlowKart_Init.c (5eca6fc) | n3 |
| clFlowRound_Update | game/clFlowRound.c | C, 100 % (3f6d3c7) | n3 |
| fn_801502AC | game/Scene_8014E0C4.cpp | C, 100 % (cf30eee) | n3 |
| fn_80154304 | game/Scene_8014E0C4.cpp | C, 100 % (regalloc_patterns §48) | n3 |
| fn_801500F4 | game/Scene_8014E0C4.cpp | C, 100 % since 163c054f (`TextPanelC::TextPanelC`; the init template is placed by an inline function defined among the pool statics in Scene_8014E0C4_rodata.inc). The list still showed it because of a stale `asm void fn_801500F4(void);` declaration, now removed | om |
| RaceContext_InitDefaults | game/RaceContext_InitDefaults.c | still asm; the file is now part of game/SetCourseParams.c (887c513, 14-TU merge) | n3 merge |
| SoundMgr_Play | game/SoundMgr_Play.c | still asm; the file is now part of game/clsound/fn_801913B0.c (a4d82de, 19-TU merge) | n3 merge |
| WarpZone_CheckEntry | game/auto_800A8F4C_block.c | C, 100 % (regalloc_patterns §50) | n3 |
| fn_80141454 | game/LogoAnim.c | C, 100 % (regalloc_patterns §51) | n3 |
| fn_80158CE4 | game/fn_80157DE0.cpp | C, 100 %, in game/SceneList_80157EA8.cpp (regalloc_patterns §74) | n3 |
| fn_8015915C | game/fn_80157DE0.cpp | C, 100 %, in game/SceneList_80157EA8.cpp (regalloc_patterns §74) | n3 |
| fn_80159BD0 | game/fn_80157DE0.cpp | C, 100 %, in game/SceneList_80157EA8.cpp (regalloc_patterns §71) | n3 |
| fn_8015A6E4 | game/SceneList_80157EA8.cpp | C, 100 % (literal floats) | n3 |
| fn_80147AF4 | game/RaceHud_80147470.cpp | C, 100 % (4ef95b5f, unit now GC/2.6, regalloc_patterns §78) | n3 |
| fn_80147CE8 | game/RaceHud_80147470.cpp | C, 100 % (4ef95b5f, regalloc_patterns §78) | n3 |
| fn_80147900 | game/RaceHud_80147470.cpp | still asm, 99.52 (`li`+`mr` colour copy; docs/gave_up.md) | n3 parked |

The four `n3` conversions and the two merges touched group C although
n3-20261109-1338 said n3 would stay out of it: they came out of TU merges and
hand threads working by address range. None of the TUs had an open claim.
See n3-20261109-2050 on the board. 52 group C functions are unchanged
(same TU, still asm); the corrections in om-20261109-1608 (fn_80157DE0 /
SceneList_80157EA8 rows, fn_8015A6E4 is NonMatching) still apply.

## Group C is open to both sides (naari3, 2026-11-09 20:55Z)

The split "om takes group C, n3 stays out" (n3-20261109-1338) no longer
holds. Either side may convert any group C function. The only coordination
is the unit-claim: open `[unit-claim] retrofit:<TU>` right before working a
TU, close it on leaving, and never touch a TU the other side has claimed.
Check the open claims and the latest `main` first (a function may already be
C; `python3 tools/scan_asm_fns.py` gives the current list). Partial drafts go
to `docs/wip/` / `docs/notes/` so the other side can pick them up. asm -> C
still lands only at 100 %. Groups A and B are unchanged (A is finished).
