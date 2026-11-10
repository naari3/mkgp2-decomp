# Split-table / pooled-base candidates (2026-11-08, mid-range thread)

Scan: functions <100% whose TARGET uses `addi rB, rX, lbl@l` followed by
`addi rA, rB, 0x0` (pooled section base, first object at offset 0), but whose
OUR build has no `...section.0` anchor in that function. The fix is to own the
section range in the TU and define the objects there, split per offset the
target uses (see TIPS.md, "`addi rX, rBase, 0x0` from one big const table").

| % | function | base label (section, size) | TU |
| --- | --- | --- | --- |
| 99.93 | fn_801F7604 | lbl_803BEDC0 (rodata, 0x20) | game/fn_801F7604 |
| 97.44 | fn_801F894C | lbl_803BEDC0 (rodata, 0x20) | game/fn_801F894C |
| 98.47 | fn_801913B0 | lbl_80495F20 (data, 0x18) | game/clsound/fn_801913B0 |
| 98.22 | clFlowCourse_Init | clFlowCourse_data_8049B1E0 (data, 0x168) | game/clFlowCourse |
| 98.13 | fn_801A4F38 | lbl_80496C38 (data, 0x1c) | game/sprite/fn_801A4F38 |
| 96.91 | DrawEffect_ItemHitBurst_Spawn | DrawEffect_KartDustRing_Update_data_8041A4D0 (data, 0xc) | game/DrawEffect_ItemHitBurst_Spawn |
| 96.33 | fn_8021ABFC | lbl_804EDC88 (data), lbl_803C4E60 (rodata) | game/anon_8021A7C8_nm1 |
| 96.03 | Race_PerFrameTickAndAudio | g_voiceQueue (bss, 0x180) | game/RacePerFrame |
| 94.45 | TaMode_Init | BATTLE (data, 0x64c) | game/TaMode_Init |
| 93.74 | fn_801B9928 | lbl_80679280 (bss, 0xc) | game/fn_801B9928 |
| 93.44 | CardCreate_Page | CardCreate_Page_data_803FBF80 (data, 0x98) | game/CardCreate_Page |
| 92.45 | IsItemSelectAllowed | IsItemSelectAllowed_rodata_803DC378 (rodata, 0x1b8) | game/ItemSelectAllowed |
| 92.40 | PCBComm_SendToAllPeers | PCBCheckRecv_bss_805A5EC0 (bss, 0x204) | game/PCBCommSendPeers |
| 91.87 | fn_801B7EF8 | lbl_80679280 (bss, 0xc) | game/fn_801B7EF8 |
| 91.65 | ranking_display | ranking_display_data_8049B4A8 (data, 0x68) | game/ranking_display |
| 91.27 | fn_801C9288 | clFlowRound_data_8049AE70 (data, 0x11c) | game/fn_801C9288 |
| 91.11 | Sci2Card_BuildItemGetReceiptLine | Sci2Card_BuildRetryReceiptLine_data_803FFDF0 (data, 0x68) | game/Sci2Card_BuildItemGetReceiptLine |
| 90.00 | RaceFlow_ResetState_FullColdInit | SetCourseParams_bss_805AC600 (bss, 0xc0) | game/RaceFlow_ResetState_FullColdInit |
| 89.32 | VoiceSystem_Init | g_voiceQueue (bss, 0x180) | game/VoiceSystem_Init |

Some of these (fn_801F894C, fn_801913B0, fn_801A4F38, the g_voiceQueue users)
are already known to need TU merges, because the data belongs to a
neighbouring TU. Nothing at >= 0x80240000 qualifies except amnet fn_8028D8CC
(done, 4b7fe5f). Scanner: /tmp/claude-0/anchorscan.py (ephemeral). The method
is in this file's header.

## Below 0x80180000: results (asm->C (A) thread, 2026-11-08)

- DrawEffect_ItemHitBurst_Spawn: defining the three tint Vecs in the TU fixes the
  anchor, but the body still differs (missing speed clamp, r27/r28 swap). The data
  0x8041A4D0.. is owned by DrawEffect_KartDustRing_Update.c, so a fix would mean a
  7-TU merge (6 of them Matching). Skipped.
- CardCreate_Page: CardCreate_Page_data_803FBF80 sits before UI_PageDispatcher's .data (0x803FDE78),
  whose .text is before the service-menu pages. So the original TU spans
  UI_PageDispatcher..CardCreate_Page (~15 TUs). Skipped.
- Sci2Card_BuildItemGetReceiptLine: Sci2Card_BuildRetryReceiptLine_data_803FFDF0 sits right before the
  BuildRetryReceiptLine/BuildScoreReceiptLine jump tables, so the original TU spans
  0x80094D80..0x800997E4 (17 TUs, 2 of them NonMatching). Skipped.
- RaceFlow_ResetState_FullColdInit: uses SetCourseParams' .bss pool (base+0x20000).
  If it is rewritten with SetCourseParams' named objects in the same TU (scratch test),
  the anchor matches and the diff goes 598 -> 236 (a register swap is left). But the
  merge also needs SetCourseParams (stuck at ~95%, see gave_up) and 3 small Matching
  TUs in between. Parked. Scratch copy: docs/wip/asm-a/RaceFlow_in_SetCourseParams.c
- TaMode_Init: needs BATTLE plus the vtable (BATTLE+0x658) owned in one TU together
  with TaMode_FrameUpdate (99.48%, register allocation) and TaMode_Dtor. Parked.
