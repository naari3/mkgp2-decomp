# Functions naari3's threads gave up on

These are functions naari3's Claude threads tried and parked. The point of the
list is to give a fresh pair of eyes a head start: what the % is, what is
still different, and where the work in progress lives. Please read the
"Tried" notes before starting, so you do not repeat the same variants.

- `%` is the objdiff fuzzy match from `build/GNLJ82/report.json` at main
  `69cde57` (2026-11-07). Functions that have reached 100% since are dropped.
- "WIP" paths starting with `wip/` or `notes/` live in naari3's shared project
  folder, not in this repo. Ask naari3 for any of them; the drafts are plain
  `.c`/`.cpp` files or `git diff` patches against main.
- Many of these TUs are now under open onmokoworks claims. That is fine: this
  list is information, not a claim. Check the open `unit-claim` issues before
  starting any of them (see `docs/matching_rules.md`).
- Rules and techniques that already worked are in `docs/matching_rules.md`.

When you match one, delete its row in the same commit. When you give up on a
new one, add a row.

## Register allocation / scheduling only

The code shape is right; what is left is which register gets which value, or
the order of a few independent instructions. Compiler-version sweeps
(1.2.5n/1.3/1.3.2/2.0/2.6/2.7) and 15-45 minute permuter runs found nothing for
all of these.

| Function | TU | % | What is left | Tried / WIP |
| --- | --- | --- | --- | --- |
| `fn_8024D3D4` (ContinueSceneTick) | game/ContinueSceneTick | 99.87 | r28/r29 swapped between credits and alternate | ~20 variants |
| `__THPHuffDecode` | thp/THPDec | 99.71 | `Vij + valPtr` add order (reassociation) | all CW 1.x give the same |
| `fn_8029B54C` | thp/THPDec | 99.97 | mask register choice | |
| `ClRomTable_PurgeAll` | game/ClRomTable_PurgeAll | 99.70 | r27/r29 swap | 8 loop shapes; 40 min permuter |
| `fn_801F1EE0`, `fn_801F2400`, `fn_801F230C` | game/Menu801F0CC0 | 99.54 / 99.48 / 97.60 | target does `mr rX, r_i` copy of the induction var at loop start; not reproducible so far | decl orders, scoped `i` |
| `fn_8018E538` | game/objview/fn_8018E538 | 99.42 | same `mr rX, r_i` IV init copy as above | |
| `CardData_InitDefaults` | game/CardData_InitDefaults | 99.92 | epilogue `lwz r0` order | no flag or version fixes it |
| `fn_801E96BC` | game/fn_801E96BC | 99.85 | base / iterator register swap | |
| `SpecialFaceMesh_Dtor` | game/SpecialFaceMesh_Dtor | 99.46 | base / iterator register swap (same pattern as fn_801E96BC) | 40 min permuter |
| `AI_PerKartUpdate`, `fn_801E9CBC` | game/AI_PerKartUpdate, game/fn_801E9CBC | 99.80 / 99.73 | ItemList items register | all 6 decl orders of mode/round/cup in ItemList, for/while count loops; 5 min permuter |
| `SwitchTest_Page` | game/SwitchTest_Page | 99.91 | `steer` / `st` not coalesced | |
| `fn_801DABFC` | game/fn_801DABFC | 99.20 | 4 lines: the two `switch (out[k])` tests are `cmplwi` in the target | int/u8/bool; a `u8 out[2]` field fixes the `cmplwi` but then `out = !out` becomes `extrwi` instead of `srwi` (16 lines); casts, unions, `*(u8 *)&`, inline u8 helpers all keep `cmpwi` |
| `EffectItemChainIndicator_Tick` | game/EffectItemChainIndicator_Tick | 99.70 | register coloring | |
| `fn_801C64DC` | game/clFlowFigure_Unlocks | 99.94 | register coloring | |
| `PlayStats_CopyStatsBlock` | game/PlayStats_CopyStatsBlock | 98.64 | copy scheduling barrier (target interleaves differently) | `__restrict`, temps |
| `fn_80162D90` | game/Scene_80162D90 | 99.82 | register swap | |
| `fn_8017CE1C` | game/mapobject/fn_8017CE1C | 99.98 | register swap | |
| `fn_8017EFFC` | game/miyazakiconsole/fn_8017EFFC | 97.79 | register swap | |
| `fn_8017BCF8` | game/mapobject/fn_8017BCF8 | 99.28 | f0/f1 swap | |
| `fn_8016C94C` (PointList ctor) | game/mapeffect/PointListConstruct | 99.84 | one load order | |
| `fn_8020615C` | game/anon_80205DCC | 99.78 | f29/f30 swap | |
| `fn_801BDEB4` | game/fn_801BAA88 | 99.71 | ResCtrl t0/t1/t2 store order vs `li` registers | |
| `fn_8028A3EC` | triforce/amcoin_nm2 | 99.49 | r0/r3 swap | |
| `fn_8028A934` | triforce/amjvs_nm2 | 99.6 | target reuses r3 (`nodes`) for `n = &nodes[node]`; we copy to r5 | `nodes += node`, direct `nodes[node].x`, u32/u8 idx casts, split early return |
| `BackupWriteRecord` | triforce/ambackup_nm1 | 94.6 | with GC/1.3 the permuter got 64 -> 31: recSize/hdr r29/r31 swap plus Checksum p/sum r3/r4 | 5+20 min permuter at GC/1.3; open-coded checksum loops |
| `fn_80286864` | triforce/random_nm1 | 84.8 | target shares `ret`'s `li r31, 0` with the zero high word of the inlined u64 range; we emit a separate `li r8, 0` | ret/range variants; 10+20 min permuter |
| `clItemBoxManager_InitStateTable` | game/clItemBoxManager_StepTable | 91.8 | target __sinit addresses both tables from one pool base (`lbl_803F9C60`); CW pools only static objects and only when a function touches 3+, and the sinit touches 2. Other clItemBox_* TUs use the tables by name | statics (still per-symbol), hand-written sinit through a base pointer (becomes a leaf, extab lost), GC/1.2.5n..2.7 |
| `fn_80291134` | triforce/amsrv_nm1 | 93.71 | target keeps `mr r3, ch` late so temps use r3; `p` not coalesced into r3 | |
| `KartShellRibbonDraw` | game/KartShellRibbonDraw | 99.91 | f30/f31 swap only (GC/2.6) | |
| `fn_8023A148` | game/fn_8023A148 | 99.44 | title / color r0/r4 swap | |
| `fn_8023AC14` | game/ItemSelectChoiceUpdate | 97.91 | register coloring | `notes/r4/fn_8023AC14_9889.diff` |
| `fn_801D2F0C` | game/anon_801D2F0C | 99.91 | `PSMTXTrans` y/z argument registers | locals for y/z/x in both orders, `const &` placement, non-const placement member, Vec temp, GC/1.3..2.7: all identical |
| `fn_80242E80` | game/fn_80242E80 | 99.40 | scheduling | |
| `fn_80228394` | game/DNFlash_nm2 | 94.60 | sibling `fn_802281F0` matched with `extern const` tables + `dx` then `nx = -dx`; this one did not follow | |
| `SpriteGroup_CreateOrInit` | game/SpriteGroupCreate | 95.65 | `lwz`/`stw` (and `li`) order | |
| `fn_80245E6C` | game/HudFlow20Update | 98.92 | one `lwz` scheduled differently | |
| `fn_80246988`, `fn_80246DE4` | game/RaceDigitLap, game/RaceDigits | 99.90 / 99.92 | `DigitPanel::SetPos` `lfs` order | |
| `fn_80243C70` | game/ItemPanelDraw | 99.97 | f28/f30 swap | |
| `fn_8021995C` (MinimapHud dtor) | game/anon_80218F40_nm2 | 99.08 | this/flag/cursor coloring (target this r30, cursor r29, i r28, delete flag r27; ours gives the flag r30) | 8 loop/decl variants, 15 min permuter |
| `fn_8021B68C` (TeamIconRow::Update) | game/anon_8021B568_nm1 | 98.84 | cursor/t swap (target t r31, `this+i*4` r30) and one `cmpw` operand order in inline `SlotTeam` | 8 variants incl. hand-inlined SlotTeam, 15 min permuter |
| `PCBCheck_ProcessLinks` | game/PCBCheckProcess | 99.90 | 10 lines: base/slot registers swapped, one ClearSlotData loop counter (r24 vs r29) | 178 -> 10 lines in d36e695; 20 min permuter |
| `fn_80219538` (MinimapHud::UpdateMarkers) | game/anon_80218F40_nm1_tail | 85.31 | target keeps px/pz in stack slots (0xc/0x8, stored at entry, reloaded after sin/cos) while every ref/pointer/array/struct/non-inline variant gets promoted to f28/f29; only `volatile` reproduces the frame (174 -> 109 lines with locals declared at the top), rest is GPR coloring | pragma sweep, CW 1.3.2-2.7 same |
| `HSD_SetupChannelMode` | sysdolphin/baselib/state | 85.44 | target keeps `chan_table` in r30 but never folds `&chans[k]` into the displacement (`addi r4, r30, 0x0; stw r3, 0x20(r4)`, `addi r5, r30, 0x30; addi r5, r5, 0xc`); using `chan_table` directly gives that shape but rematerializes lis/addi each time; local pointer / `&chan_table[0]` / const / register / index vars / inline-helper all fold | CW 1.0-2.7, 6 opt pragmas |
| `acInetAddr` (also acConnect/acBind/acModifyMyIPaddr) | triforce/acsocket_nm3 (nm2/nm4/nm5) | 95.82 | 3 lines: target keeps a `+ 0` as `addi r26, r5, 0x0; add r26, r0, r26` for `bufAddr + (bufOff + 0)`; every inline/const/static-const/`n * 1` form folds it to one `add`, pointer-difference forms do not fold at all | CW 1.0-2.7 |
| `CollisionFile_Load` | game/CollisionFile_Load | 97.0 | now C++ (c215945); left: target reuses the loop counter's zero register for the three member stores, and one `add` operand order | 15 min permuter, ~40 variants |
| `fn_8024AD8C` | game/CardSetupFlowInitial | 95.88 | `lwz lbl_806D1AB0` scheduling | |
| `fn_8022BBC8` | game/EnemyFace_nm3 | 98.72 | scheduling | |
| `clFlowCourse_Dtor` | game/clFlowCourse | 99.62 | `selected % 2` register swap | |
| `fn_8015E608` | game/resultscene/resultscene | 99.21 | `li -0x100` register in the `rlwimi` alpha insert | |
| `fn_8015DEBC` | game/resultscene/resultscene | 99.62 | `fdivs` temporaries | |
| `result_screen_update` | game/resultscene/resultscene | 99.93 | input pointer r29 vs `ItemMsg` new-temp r30 swapped | third params of fn_80160588/fn_801618CC are `bool` |
| `fn_8019EB9C` | game/kartmove/carobject | 85.29 | FP register homes; decl-order permutations plateau at 44 lines | |

## Data layout / TU split problems

The code is probably right; the target addresses data through a section base
the current TU does not own, or the TU was split out of a bigger file.
See "Pooled base registers" and "Over-split TUs" in `docs/matching_rules.md`.

| Function | TU | % | What is left | Tried / WIP |
| --- | --- | --- | --- | --- |
| `RaceScene_GetPerspFovyForCup` | game/RaceScene_GetPerspFovyForCup | 80.98 | needs TU-owned `.data` base `0x80401118` (+0x10000) | |
| `fn_801ECA14` | game/fn_801ECA14 | 74.07 | pool base `lbl_803BD920` owned by another TU | |
| `Card_VerifyChecksum` | game/Card_VerifyChecksum | 91.97 | pooled data base | |
| `fn_8020B234` | game/anon_8020AF08_nm1 | 97.54 | with TU-owned rodata it reaches 99.92; left is r3 vs r0 for itemId in the 0x9B/0x9D compares | `notes/r4/anon_8020AF08_nm1_rodata_99.92.diff` |
| `WarpDashMgr_Init` | game/WarpDashMgr_Init | 94.48 | target adds `course*8 + alt*4` then `lwzx` from `pool+0x1660` | |
| `LObjInfoInit`, `CObjInfoInit` | sysdolphin/baselib/lobj_load_nm, cobj_info_nm | 93.12 / 99.94 | `addi r3, r31, 0` + string offsets = class data and strings in one `.data` block; needs the whole-file TU merge (as done for tobj/mobj/jobj) | merge blocked by open claims |
| `fn_8015C41C` (ResultPartY ctor) | game/resultscene/resultscene | 97.75 | pooled-data base `lis/addi` hoisted above member ctors in target; i/id register swap | |
| `fn_8015CD74` | game/resultscene/resultscene | 98.08 | not recorded | |
| `fn_801E35FC` | game/fn_801DEF94 | 86.79 | 2-line `cmplw` scheduling once the pool is owned | `notes/r4/fn_801E35FC_sched2.diff` |

## Control-flow / branch shape

| Function | TU | % | What is left | Tried / WIP |
| --- | --- | --- | --- | --- |
| `fn_80204218` (SceneListImpl::Draw) | game/anon_80203EA0_nm2 | 98.42 | target keeps one more ListIter stack copy after `Erase` (result at 0x10 then `it` at 0x14); every inline/temp/ctor/operator= variant gets copy-propagated | ~20 variants |
| `fn_8020A788`, `fn_8020A6CC` (Tween Value) | game/anon_80209FA4_nm3 / _nm2 | 93.82 / 92.88 | final `add r0; mr r3, r0` tail | onmokoworks also tried |
| `fn_80288BCC` | triforce/ambackup_nm3 | 92.94 | `opt_propagation off` gets it to 1 line; target keeps a dead `b` after `li r3,1; b ret` | |
| `fn_801934F4` | game/clsound/fn_801934F4 | 90.86 | `opt_dead_assignments off` + `peephole off` gets 5 lines; target `mr r30, r29` (i = row copy) | |
| `fn_801F8250` | game/fn_801F8250 | 96.33 | `slwi`/`addi` order (4 lines); table shared with fn_801F7604..fn_801F8A34 TUs | |
| `fn_801F894C` | game/fn_801F894C | 97.44 | rodata table `lbl_803BEDC0` shared by 4 TUs | target `addi r3, r31, 0` = section-pool base, so 0x801F7604..0x801F89F0 was one TU owning that .rodata (merge). `opt_propagation off` only gives `mr` |
| `Effect_KartAuraCompound_Update` | game/EffectKartAuraCompound | 94.68 | `opt_common_subs off` gets 48 lines; `li 0` / `li 1` order | |
| `RankLog_OnMatchEnd` | game/RankLog | 93.43 | table index shape | |
| `fn_8015E928` | game/resultscene/resultscene | 61.37 | not tuned much | |
| `KartMovement_Init` | game/kartmove/carobject | 66.69 | large schedule difference; GC/2.6 no help | |
| `fn_8020F080` (TaskListImpl::Draw) | game/anon_8020E3D0_nm1 | 96.61 | WIP is 4 lines off: needs `opt_dead_assignments off`, `operator*` returning node->task, `bool operator!=(TaskNode*)`, Remove by value with a `result` temp; left is one dead Remove-param store | `wip/fn_8020F080_draw_wip.cpp` |
| `ItemSelectState_Init` | game/ItemSelectState_Init | 91.52 | WIP at 99.3 (MakeCell inline fixed the stack order) | `notes/r4/ItemSelectState_Init_wip.cpp`, `_regs.diff` |
| `QuadFrame_FromCornerPtrs` | game/QuadFrame_FromCornerPtrs | 52.02 | `Vec ~Vec(){}` gives mem structs + `fmadds`; not finished | `notes/r4/QuadFrame_wip.c` |

## Still inline asm (the report counts these as 100%)

TUs with inline asm count as matched in the report, so these show 100% there
but are still asm. Each has a C/C++ draft that did not match.
`tools/scan_asm_fns.py` lists all of them. Rows marked "naari3 claim" are being
retried by one of naari3's threads right now; skip those until the claim closes.

| Function | TU | Best draft / what is left | WIP |
| --- | --- | --- | --- |
| `JumpDistanceMode_Update` | game/JumpDistanceMode_Update | 4 instructions off at the XZ sqrt (flags `-Cpp_exceptions on -lang=c++ -use_lmw_stmw on`). Locals `x = d.x; z = d.z` give the right colors but get fused into `fmadds`; separate `x2/z2` stay unfused but load z first. ~300 expression forms swept | `notes/r4-6/JumpDistanceMode_Update_draft.cpp` |
| `JumpDistanceMode_CopyKartMovement` | game/JumpDistanceMode_CopyKartMovement | not drafted far | |
| `SoundMgr_Play` | game/SoundMgr_Play | draft | `notes/SoundMgr_Play_draft.c` |
| `clFlowRound_Update`, `clFlowRound_Init` | game/clFlowRound | drafts; pool base vs self register (naari3 claim #2492) | `notes/clFlowRound_*_draft.cpp` |
| `clFlowCup_Init`, `clFlowChara_Update` | game/clFlowCup, game/clFlowChara_Update | tried 5+ times on both sides | |
| `clFlowKart_UpdateDisplay` | game/clFlowKart_UpdateDisplay | 36 lines with an inline helper; the top needs a TU-owned pool (fakematch `opt_propagation off` breaks the helper) | `wip/clflowkart_updatedisplay_wip2.patch` |
| `WarpZone_CheckEntry` | game/auto_800A8F4C_block | 99.2% / 24-line plateau: mgr r7 vs r6 swap with the zone pointer. Calling the inlined `WarpZone_FindContainingOBB` with a local zone gets 30 lines, `obbs[i]` form 24. ~20 loop/caller forms, pragmas no effect. The C version also grew main.dol by 0x20 (check extab) | `wip/asm-a/warpzone_checkentry_99pct.patch` |
| `fn_80147900`, `fn_80147AF4`, `fn_80147CE8` | game/RaceHud_80147470 | 2 lines (`mr r3, r4` copy of `-0x100`), 10 lines (f2/f3 swap in branch 2), not tuned. Whole TU matches under GC/2.6 too (naari3 claim #2468) | `wip/racehud_80147900_wip.patch` |
| `fn_80146000` (RankPanel) | game/RankPanel_80144430 | throws `out_of_range`, but the typeinfo string `lbl_80361E60` lives in another TU's rodata | |
| `CarrotItemEffect_Render` | game/CarrotItemEffect_Render | stack order of eye/at/a/b locals reversed vs target; decl permutations don't help | `wip/carrot_render_wip.patch` |
| `CardTaskManager_RenderOverlay` | game/CardTaskManager_RenderOverlay | 18 lines (`-lang=c++`, `opt_strength_reduction off`, `% 4U`); names/offset/0x4330 register 3-cycle (naari3 claim #2482) | `wip/cardtaskmanager_renderoverlay_wip.patch` |
| `RivalRun_UpdatePathFollower` | game/RivalRun | ~120 lines, GPR/FPR coloring; target caches position floats in locals | `wip/rivalrun_updatepathfollower_wip.patch` |
| `NokoNokoChallenge_CalcResultText` | game/NokoNokoChallenge | 3 lines (`opt_common_subs` + `opt_lifetimes` off); cup index lands in r3 instead of r0 | `wip/asm-a/nokonoko_calcresulttext_4line.patch` |
| `KartItem_Tick`, `KartItem_OnKartHit`, `KartItem_ApplyImpact*`, `KartItem_PerFrameStep` | game/auto_ONKARTHIT_block | GC/2.6 TU; drafts 24-130 lines off; some need header edits first (naari3 claim #2171) | `docs/drafts/*.handoff.md` in this repo |
| `clNormal3D_Exec` | auto_clNormal3D_Exec_text | 1844 bytes; C++ draft ~149 diff lines (register webs, same as sibling Object_DriveAnimAndSkin) | `r1-drafts/clNormal3D_Exec.cpp` |
