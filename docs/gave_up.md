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
| `acInetAddr` (also acConnect/acBind/acModifyMyIPaddr) | triforce/acsocket_nm3 (nm2/nm4/nm5) | 95.82 | 3 lines: target keeps a `+ 0` as `addi r26, r5, 0x0; add r26, r0, r26` for `bufAddr + (bufOff + 0)`; every inline/const/static-const/`n * 1` form folds it to one `add`, pointer-difference forms do not fold at all | CW 1.0-2.7; thread B (2026-11-07) also tried a bufOff-typed struct/array member at offset 0, `*off = bufOff; *off += base` (splits the add but loads bufOff straight into the callee-saved reg), a loop/do-while n, a struct/array-held 0, `static const` 0, and declsweep (120 orders): best acConnect 9 lines with `*off = (u32)((T*)State.bufOff)->data + base` |
| `acAccept` | triforce/acsocket_nm5 | 89.5 | same `+ 0` copy (`addi r28, r4, 0` next to `addi r29, r4, 4`), plus the `(addr == NULL || len == NULL) && (addr != NULL || len != NULL)` branch order and a one-register shift. `(u32)&((u8*)b + 4)[State.bufOff]` gives the +4 form (96.2%) | notes/shard1/acsocket_nm5_acAccept_score45.c, notes/shard2/acsocket_and_leftovers.md |
| `fn_80292AD8` (tx DMA write) | triforce/acsocket_nm6 | 93.4 | 27 lines: target computes `p` in r7 and copies it to r28, and copies `len` to r5 for memcpy before the `mis && size > 0x4000` check, so `len + 0x1F` and CheckRange read r31; ours coalesces both copies and reads the incoming r5 | thread B: inline helpers for the check/memcpy/send or the whole body, an inline returning `p` (like fn_80292D18), ternary `p`, extra `buf = p; n = len` copies, all GC versions (3.0a3+ best), -O2/-O3/-opt flags, declsweep 200 orders |
| all 28 fns (cLNormal3DWrap) | game/cLNormal3DWrap | 100 (TU NonMatching) | layout only. Real virtual dtors + `-RTTI on` + `#pragma readonly_strings on` at the end, `-inline noauto,deferred`, functions written in reverse address order, owning .rodata 0x80312810..50 / .data 0x803FE458..80 / .sdata 0x806CEFD0..E0: all sizes and data/rodata/sdata order match. Left: the weak template base dtor copy (dtor_800897B8) is emitted right after the ctor instead of last (10 bl bytes off). Defining it out of class after Mgr_Dtor moves it last but then Mgr_Dtor stops inlining it; dtk refuses a separate split for it ("reversed extab group") | thread B: wip/cLNormal3DWrap_rtti_deferred_wip.cpp + .patch, TIPS.md |
| all 7 fns (WarpZoneVector_Reserve) | game/WarpZoneVector_Reserve | 100 (TU NonMatching) | over-split from WarpZoneVector_Insert: the throw type string `!std::exception!!std::logic_error!!std::length_error!!` is lbl_803284C0, owned by Insert (-rostr). Flipping alone emits a second copy in .data. A merged TU needs Reserve's functions before Insert in source (reverse emission), the Insert header's placement new without `throw()` vs Reserve's with it, and the Storage dtor not inlining Clear (Reserve uses a renamed ClearCall) | thread B: tried a straight concatenation, Insert 21 / Reserve 19 lines off |
| `CollisionFile_Load` | game/CollisionFile_Load | 97.0 | now C++ (c215945); left: target reuses the loop counter's zero register for the three member stores, and one `add` operand order | 15 min permuter, ~40 variants |
| `fn_8024AD8C` | game/CardSetupFlowInitial | 95.88 | `lwz lbl_806D1AB0` scheduling | |
| `fn_8022BBC8` | game/EnemyFace_nm3 | 98.72 | scheduling | |
| `clFlowCourse_Dtor` | game/clFlowCourse | 99.62 | `selected % 2` register swap | |
| `fn_8015E608` | game/resultscene/resultscene | 99.21 | `li -0x100` register in the `rlwimi` alpha insert | |
| `fn_8015DEBC` | game/resultscene/resultscene | 99.62 | `fdivs` temporaries | |
| `result_screen_update` | game/resultscene/resultscene | 99.93 | input pointer r29 vs `ItemMsg` new-temp r30 swapped | third params of fn_80160588/fn_801618CC are `bool` |
| `fn_8019EB9C` | game/kartmove/carobject | 85.29 | FP register homes; decl-order permutations plateau at 44 lines | |

## onmokoworks Codex near misses (>= 99%)

Functions onmokoworks's Codex workers (cycles c10-c19, 2026-11-05..08) stopped
on at 99% or more. `%` is from `report.json` at main on 2026-11-08; "What is
left" is the worker's own summary of the remaining diff, trimmed. Most of these
are register-allocation residuals that six source-level hypotheses (decl order,
temporaries, expression forms, inline helpers, literal vs extern float, types)
did not move. The batch id names the worker's archive (HANDOFF + `worker.patch`)
in onmokoworks's local orchestrator folder; ask onmokoworks for one. Some of
these TUs are still under onmokoworks claims while cycle c19 runs.

| Function | TU | % | What is left | Tried / WIP |
| --- | --- | --- | --- | --- |
| `fn_801D1890` | game/fn_801D1890 | 99.99 | Three stack displacements only: +0x2B4/0x801D1B44 hidden return buffer target SP+0x10, source SP+0x0C; +0x448/0x801D1CD8 second iterator argument target SP+0x0C, source SP+0x10; +0x468/0x801D1CF8 second iterator... | 6 approaches (c19_u73_20261107) |
| `RenderObj_ItemStateMachine` | game/RenderObj_ItemStateMachine | 99.97 | Nine FP operand rows in overlay projection:443BC fabs f3 vs targetf0;443C4 coefficient f2 vsf3;443C8 coefficient f0 vsf2;443CC frsp f3 vsf0;443D4 fmuls coefficient f2 vsf3;443D8 conversion cookie f2 vsf3;443E0... | 6 approaches (c19_u1_20261107) |
| `fn_801046C4` | game/fn_801046C4 | 99.96 | Three register-operand rows at 0x801049E8/F0/F8: weighted yaw product f1 vs target f2, complement f2 vs target f1, matching swapped FMADD inputs. Same 2064B instruction skeleton, scheduling and relocations otherwise. | 6 approaches (c19_u35_20261107) |
| `fn_8020579C` | game/anon_802052E0_nm1 | 99.96 | At target 0x80205AA8 (+0x30C): fadds f2,f2,f30; source emits fadds f2,f30,f2. Every other function instruction/relocation matches. | 6 approaches (c18_u210_20261107) |
| `LakituStart_UpdateCountdown` | game/LakituStart_UpdateCountdown | 99.95 | Five instruction rows differ only in FPR fields: cached dir.x is f28 versus target f27; cached dir.y is f27 versus target f28. Addresses 8003D46C, 8003D47C, 8003D488, 8003D508, 8003D594. Yaw now uses exact f29. All... | 6 approaches (c19_u40_20261107) |
| `CharaSelect_SetupCharacterDisplay` | game/CharaSelect_SetupCharacterDisplay | 99.94 | At target 0x801C366C addi r26,r25,2, source emits addi r25,r25,2; at 0x801C3694 target lbz r0,0(r26), source lbz r0,0(r25). All other instructions match. No missing functions in the sole-function 801C3470..801C3714... | 6 approaches (c18_u54_20261107) |
| `clFlowClass_Update` | game/clFlowClass_Update | 99.94 | Input pointer r3 vs target r4 and old-selection r4 vs target r5; current selection/input-delta load order reversed at target +0x4B8/+0x4BC. Source loads delta into r3 then selection into r0, target selection into r3... | 6 approaches (c19_u15_20261107) |
| `fn_801D7610` | game/fn_801D7610 | 99.94 | Only epilogue scheduling: target 0x801D790C lwz r0,0x14(r1); 0x801D7910 lwz r30,8(r1). Native restores r30 then r0. Every other instruction and owned EH section is exact. | 3 approaches (c18_u185_20261107) |
| `fn_8018DAD0` | game/objview/fn_8018DAD0 | 99.94 | Final-loop byte stride source r30 versus target r26 at +0x400 mr r26,r28; +0x408 add r29,r0,r26; +0x4C4 addi r26,r26,0x2C. Everything else exact, 1268B text. | 6 approaches (c19_u74_20261107) |
| `VfxSlotMgr_Update` | game/VfxSlotMgr | 99.94 | Eight instruction rows retain swapped outer Vec stack copies: position is source SP+4C vs target SP+58; target is source SP+58 vs target SP+4C. Six stw destinations and two addi r4 argument addresses differ. All... | 6 approaches (c18_u218_20261107) |
| `fn_8016D2D0` | game/ItemBoxConstruct | 99.93 | Four register-only rows at +0x24,+0x28,+0x30,+0x34: target pool high-address scratch r7/source r3; target base-vtable low-address/store r3/source r6. Resource base r28 and every subsequent instruction agree. | 6 approaches (c18_u90_20261107) |
| `fn_801F7604` | game/fn_801F7604 | 99.93 | Mixed-format offset uses r28 instead of target r29 at 0x801F79DC (li 0), 0x801F79F0 (li 4), 0x801F7A08 and 0x801F7A20 (slwi). Ten additional default-objdiff differences have identical formatted instructions and arise... | 6 approaches (c18_u62_20261107) |
| `fn_8019C15C` | game/kartmove/fn_8019C15C | 99.93 | Five initial volatile FP register differences: target Y=f2/X=f0, emitted Y=f0/X=f2, at 8019C1A0/1A8/1AC/1B0/1B4 (offsets 44/4C/50/54/58). All other primary instructions exact. | 6 approaches (c19_u66_20261107) |
| `PlayerData_Construct` | game/PlayerData_Construct | 99.92 | Mileage index is r21 rather than target r19 at 0x801D7568 (li), 0x801D7570 (mr r3), 0x801D75F0 (addi), and 0x801D75F4 (cmpw). All other formatted instructions/relocations and the owned EH/index match. | 6 approaches (c18_u161_20261107) |
| `fn_8015A6E4` | game/OptionMenuDraw | 99.91 | Seven register-only rows: English heading cached Y=f24 versus target f30 (3 rows); second rising pulse duration=f1/product=f0 versus target duration=f0/product=f1 (4 rows). | 6 approaches (c19_u41_20261107) |
| `fn_801EE36C` | game/fn_801EE36C | 99.91 | Five FP operand differences only: previous-X is f10 instead of target f2 at 0x801EE6FC/0x801EE70C/0x801EE734; coefficient is f2 instead of target f3 at 0x801EE704/0x801EE714. Scale f9, scratch layout, control flow,... | 6 approaches (c18_u162_20261107) |
| `MenuScene_Dispatch` | game/MenuScene_Dispatch | 99.91 | Seven FP register/operand differences at801B9460,9468,946C,9470,9474,9478,947C: y product/result f0 versus targetf1; scale conversion f1 versus targetf3, basef3 versus targetf0, productf1 versus targetf2. All other... | 6 approaches (c19_u32_20261107) |
| `fn_801869F8` | game/objview/fn_801869F8 | 99.89 | Nine GPR-operand differences, all final render-pass path pointer: target r26 versus source r27 at +0x4EC..+0x630. All earlier instructions, loop counters, joint-pointer homes, FPR operands, control flow, size and... | 6 approaches (c19_u75_20261107) |
| `ItemObject_Tick_Kind2d_ChainShellPair` | game/ItemObject_Tick_Kind2d_ChainShellPair | 99.89 | Original restored source: 12 register argument mismatches in final child-transform loop, cursor target r31/source r30 and counter target r30/source r31. Offsets... | 6 approaches (c19_u24_20261107) |
| `AI_CalcGPTargetSpeed` | game/AI_CalcGPTargetSpeed | 99.89 | Six instruction rows: cup/round loaded into argument r4/r5 then copied to saved r29/r25 instead of loaded into saved registers first at 801EA7D0..801EA7E0; final render rank uses r25 instead of target r26 at... | 6 approaches (c19_u59_20261107) |
| `HSD_CObjSetRoll` | sysdolphin/baselib/cobj_nm4 | 99.89 | Five operand-only instructions: eye.y home f2 instead of target f3, with the double 1.0 constant in f3 instead of target f2. Addresses 802C7FFC, 802C8000, 802C8004, 802C8010, 802C8020; all other primary instructions... | 3 approaches (c18_u7_20261107) |
| `fn_801C0568` | game/fn_801BAA88 | 99.86 | Only panel and direction lwz instructions are scheduled in reverse order. Inherited cast marked fakematch remains in the honest NonMatching TU. | 2 approaches (c19_u21_20261107) |
| `fn_8017F538` | game/miyazakiconsole/fn_8017F538 | 99.85 | Ten register-only rows: bank menu target r30/source r29 and bank walker target r29/source r30 at 8017F5BC/5CC/5D0/5D4/5E0; numbered menu target r31/source r29 at 8017F694/6B8; stream menu target r29/source r31 at... | 6 approaches (c19_u57_20261107) |
| `fn_8017DF00` | game/mapobject/fn_8017DF00 | 99.85 | Selected editing node uses r28 instead of target r29: 15 instruction rows / 17 register operands at offsets 0x51C..0x640. All other instructions, 1960-byte text, owned extab/extabindex and relocation targets match. | 6 approaches (c19_u38_20261107) |
| `clFlowGpPlease_Init` | game/GpPleaseInit | 99.84 | 21 formatted instruction rows, all r0/r7 exchange between tween active=1 and End() sentinel scratch values. No remaining callee-saved register, stack slot, loop update, EH payload or relocation residual. | 6 approaches (c19_u25_20261107) |
| `DrawEffect_Cb_KartWheel_DualSpawn` | game/DrawEffect_Cb_KartWheel_DualSpawn | 99.83 | Eight register-operand differences only. Target child cursor r31 / phase-table cursor r30; source child cursor r30 / phase-table cursor r31. First difference 0x800B7E90, then 0x800B7E94, 0x800B7E9C, 0x800B7F10,... | 6 approaches (c18_u173_20261107) |
| `DriveBehavior_HandleWpType` | game/DriveBehavior_HandleWpType | 99.82 | Five post-sin FPR rows at 801DEA44/48/4C/50/54: complement f0 vs target f4, first FMA result f3 vs f0, second FMA result f0 vs f1 and corresponding store operands. Rounded wave f3, amplitude f2 and bias f1 now exact.... | 6 approaches (c18_u198_20261107) |
| `EffectVfx10_KartTrail_Tick` | game/EffectVfx10_KartTrail_Tick | 99.82 | Only pool/item GPR home swap: target pool r30, item r31; source pool r31, item r30. Ten differing instruction rows, no control-flow, size, scheduling, FP, EH or data mismatch. | 3 approaches (c17_u67_20261107) |
| `KartFx_Slot5C_TripleStreakTick` | game/KartFxBoost | 99.82 | Seven FP identity rows at 800B9DF4/9DF8/9DFC/9E00/9E08/9E0C/9E14. Target current f2, decrement f1, minimum f0, post-store opacity reload f1; source current f1, decrement f0, minimum f2, reload f0. Subtraction... | 6 approaches (c18_u167_20261107) |
| `HSD_TExpMakeDag` | sysdolphin/baselib/texpdag_nm1 | 99.82 | Sort outer/inner indices r7/r8 swapped (802E2218..802E2284); diagnostic relocations point to synthetic local ...data.0 instead of exported lbl_804FDCF0 pool. Draft additionally emits 67 B .data, absent from target TU. | 6 approaches (c19_u29_20261107) |
| `PathManager_UpdateAll` | game/PathManager_UpdateAll | 99.81 | 8003CA54/CA58: node lwz r0,0x14(r6) scheduled before addi r3,r6,0x10 instead of after. Feedback 8003CC54..8003CDB0: entry r24 vs target r31, outer index r25 vs r28, inner index r28 vs r24; slot cursor r27 exact. All... | 6 approaches (c19_u3_20261107) |
| `HSD_LObjSetupSpecularInit` | sysdolphin/baselib/lobj_init_nm | 99.81 | Five GPR operand rows swap count/cursor: target count r30 and cursor r29, source count r29 and cursor r30. Light pointer now agrees at r31. Six owned literal relocation rows still use anonymous local names. Size644... | 6 approaches (c19_u13_20261107) |
| `fn_8022D9E4` | game/EnmyFaceEffect_nm1 | 99.81 |  | 6 approaches (c19_u43_20261107) |
| `NameCheck_CardName` | game/NameCheck_CardName | 99.81 | Destination-table pointer source r5 versus target r4; current-code-unit source r4 versus target r5 in both conversion loops. Exactly eight argument-mismatch instructions at... | 6 approaches (c18_u180_20261107) |
| `fn_80187410` | game/objview/fn_80187410 | 99.81 | Exactly six operand-only rows: +0x1BC/+0x1F8 mulli r0,r3,12 instead of r3,r3,12; +0x1C0/+0x1FC points load r3 instead of r4; +0x1C4/+0x200 add r3,r3,r0 instead of r3,r4,r3. Third lookup exact. No remaining saved-GPR,... | 6 approaches (c18_u237_20261107) |
| `clNormal3D_SetScale` | game/Normal3DScale | 99.80 | 11 GPR-only instructions: self Request cursor/count r31/r28 instead of r28/r31 (6 instructions); final Animate count/cursor r27/r30 instead of r30/r27 (5 instructions). Source Request is exact at baseline. | 6 approaches (c19_u69_20261107) |
| `CourseEnvironment_UpdateAndCullZones` | game/CourseEnvironment | 99.80 | Nine instruction rows differ only in zone byte-offset r5 versus target r6 and object walker r6 versus target r5. Final fcmpo/cror/mfcr/extrwi./beq sequence now exact. Native size 1112 B equals target. | 6 approaches (c19_u17_20261107) |
| `CardRegister_Session_Tick` | game/CardRegister_Session_Tick | 99.80 | Polling and failure-decoder card pointer uses r30 instead of target r31 at 12 mr instructions (0x800926B4 through 0x80092808). All other instructions, branch targets, relocations and owned EH match. | 3 approaches (c17_u31_20261107) |
| `fn_8016AB58` | game/mapeffect/Jungle16ACtor | 99.79 | Four argument mismatches at +0x30/+0x34/+0x3C/+0x40: target pool HA in r6 and base-vtable value in r3; source pool HA in r3 and base-vtable value in r5. Loop and owned EH are exact in retained original. | 6 approaches (c18_u232_20261107) |
| `TransitionEffect_DrawCarRouletteOverlay` | game/TransitionEffect | 99.78 | Eight differing instructions: y-origin and zero f6/f5 swapped; resulting y fsubs operands and x/y fadds operand association. Target/source both 900 bytes. | 6 approaches (c19_u48_20261107) |
| `fn_8018F1E0` | game/objview/fn_8018F1E0 | 99.77 | Eight instruction rows, exclusively first input vector pointer a / destination dst r4-r5 swap. Target a=r4,dst=r5; source a=r5,dst=r4. Offsets +1EC,+1F4,+1F8,+210,+218,+224,+22C,+238. Instruction order, FPR operands,... | 6 approaches (c18_u192_20261107) |
| `fn_80190D24` | game/clsound/fn_80190D24 | 99.77 | 18 queue instructions at function offsets 0x3D0..0x444 use current/predecessor r9/r8 versus target r8/r9. All floating-point instructions now exact; instruction order, size and owned EH exact. | 6 approaches (c19_u52_20261107) |
| `fn_80271340` | Runtime.PPCEABI.H/MWRTTI | 99.77 | Seven instruction argument mismatches: offset uses r31 instead of target r12 (load, mask tests, final addition); final strcmp character uses r12 instead of target r31 (three rows). Two additional relocation-name... | 3 approaches (c17_u8_20261107) |
| `TransitionEffect_RenderPass` | game/TransitionEffect | 99.77 | Fade/iris/flash payload r29 versus target r27; fade alpha r29 versus r31; flash color homes; case 3/4/5 camera Vec stack regions; table f5/f6 constant homes and commuted fadds. Matrices now exact; no... | 6 approaches (c19_u48_20261107) |
| `clItemBoxManager_Update_Inner` | game/clItemBoxManager_nm1 | 99.74 | Final countdown walker is r31 instead of target r30; preceding body exact. | 2 approaches (c18_u9_20261107) |
| `fn_801980C8` | game/objview/fn_801980C8 | 99.73 | 15 FP operand differences in five random arithmetic sites: constant/sample f0/f1 at +0x370/+0x380 and +0x478/+0x488, f1/f2 at +0x3AC/+0x3C0 and +0x3F0/+0x404, f2/f3 at +0x430/+0x444. Source reverses these pairs and... | 6 approaches (c19_u54_20261107) |
| `RaceAnnouncer_TickAndEnqueue` | game/sprite/RaceAnnouncer_TickAndEnqueue | 99.70 | 60 register-only instruction rows: clip base/loop/queue cursor r4-r7 rotation at 801A8738..801A882C; case-1 solo character/enqueue scratch homes at 801A8DFC..801A8E64; rank1/rank3 pointer load homes swapped at... | 6 approaches (c19_u4_20261107) |
| `fn_8028C644` | triforce/amnet_nm3 | 99.70 | 16 argument-mismatch rows: seven handler command/array/index scratch-register differences and three trace base/index r3/r8 exchanges (three rows each). Same 1312-byte size. | 6 approaches (c19_u55_20261107) |
| `fn_801BC2EC` | game/fn_801BAA88 | 99.66 | TextNode x FPR f30 vs target f31; quote-block layer/state store scheduling. Language bases/offsets and cursor interpolation now exact. | 6 approaches (c19_u21_20261107) |
| `fn_801A7D0C` | game/sprite/fn_801A7D0C | 99.63 | Item lookup 0x801A8308..0x801A831C: target computes entry base in r4 then item-column base +0x40 before mulli/lwzx; baseline computes +0x40 in the scaled index and exchanges r3/r4 temporary homes. All other text and... | 6 approaches (c19_u27_20261107) |
| `clFlowCourse_Update` | game/clFlowCourse_Update | 99.62 | 62 argument-mismatch rows plus one inserted/deleted row pair for scheduling: color pack r0/r3/r4 instead of target r4/r0/r3 at +1F8..24C, +F5C..FB8 and +186C..1894; selection load scheduled at +478 instead of +480;... | 6 approaches (c19_u2_20261107) |
| `fn_8021C778` | game/anon_8021BC44 | 99.60 | Pressed/banner/name-destructor shared webs use r25/r26 versus r23/r24; name normalization lacks one retained base/mr; coin sum operand order. Source 3228 B versus target 3232 B. | 6 approaches (c19_u33_20261107) |
| `fn_80203224` | game/anon_8020314C_nm1 | 99.56 | Loop index/byte-stride r28/r27 vs target r27/r28; index initialization mr r27,r29 vs target li r27,0; dy and byte-stride increment scheduling differs. Unbridged switch table @99 vs jumptable_804EC3C4 remains. X/Y... | 6 approaches (c18_u171_20261107) |
| `ItemObject_Tick_Kind29_LightAttachment` | game/ItemObject_Tick_Kind29_LightAttachment | 99.56 | 15 instruction rows differ only in registers: target/source curve base r3/r4, time cursor r4/r5, byte index r5/r3; initialization constant/scale/frame f1,f2,f0 versus f2,f0,f1. Branches, operations, instruction order... | 6 approaches (c18_u69_20261107) |
| `fn_801987C4` | game/objview/fn_801987C4 | 99.55 | Sixteen GPR operand differences: resource r28 versus target r27; placements and reused loop index r27 versus target r28. All instructions, byte lengths, other homes, owned EH and data exact. | 6 approaches (c18_u126_20261107) |
| `FlashFadeOverlay_Draw` | game/FlashFadeOverlay_Draw | 99.55 | 14 FPR-operand mismatches in UV setup 0x8007119C..0x800711F8; instruction count, opcodes, scheduling, stack and persistent FPR homes are exact. Target/current: U-offset f3/f0, V-offset f2/f4, U-plus/product f1/f3,... | 3 approaches (c17_u58_20261107) |
| `KartPhysics_UpdateSmoothing` | game/KartPhysics_UpdateSmoothing | 99.53 | 31 argument-only rows: 801F0050..801F0064 divided speed/divisor target f1/f2 versus source f2/f1 (5 rows); 801F01B8..801F0230 zero/one/factor target f2/f1/f0 versus source f1/f0/f2 (26 rows). Fresh baseline and final... | 6 approaches (c19_u56_20261107) |
| `fn_801BE170` | game/fn_801BAA88 | 99.48 | Two SelectGroupOf loops rotate index/stride/pointer r3/r5/r4 vs r4/r3/r5; final FadeObj::Tick owner r28 vs r26. Timer FP web exact. | 3 approaches (c19_u21_20261107) |
| `TaMode_FrameUpdate` | game/TaMode_FrameUpdate | 99.48 | Idle-reset zero at800A2DB0/2DB8 is r3 rather thanr0; six started-web instructions use r28 rather thanr26; record selection800A36B8..36D8 loads long-round before reversed and delays cmpwi/time load until after index... | 6 approaches (c19_u14_20261107) |
| `ItemGridState_Init` | game/ItemGridState_Init | 99.47 | Only grid-loop GPR rotation remains: row base source r29 vs target r26; row counter r27 exact; column counter source r26 vs target r28; cell cursor source r28 vs target r24; new pointer source r24 vs target r29.... | 6 approaches (c18_u207_20261107) |
| `AI_CalcTargetSpeed_PairTracking` | game/AI_CalcTargetSpeed_PairTracking | 99.47 | 15 GPR-only differing instructions, identical 568-byte instruction skeleton. Initial scaled kart index: target r26, source r24 (offsets 0x03C/048/07C). Normal base-speed setup: target cup/param/round r27/r26/r25,... | 3 approaches (c17_u61_20261107) |
| `ServiceMode_UpdateScheduleGate` | game/ServiceMode_UpdateScheduleGate | 99.44 | Pure volatile GPR three-cycle: weekday target r11 / source r9; schedule hour base target r9 / source r10; minute base target r10 / source r11. Nine differing operand rows at function offsets... | 3 approaches (c17_u62_20261107) |
| `Object_DriveAnimAndSkin` | game/Object_DriveAnimAndSkin | 99.44 | 40 GPR-only instruction rows: save 19, clear-flags 3, two request loops 14, animation 4. Restore and conversion exact. Save target rotation r26/index r29/offset r27/joint r28 versus source rotation r28/index... | 6 approaches (c19_u44_20261107) |
| `CalcDistance` | sysdolphin/baselib/texpdag_nm1 | 99.43 | Outer cursor/index r3/r4 swapped; extra mr r4,r24; initial dist/tevs save moves reversed. Target 1080 B, draft 1084 B. Recursive inline bodies otherwise match. | 6 approaches (c19_u29_20261107) |
| `SoundDriver_GetOrCreate` | game/clItemBoxManager_nm1 | 99.42 | Spawn-table entry cursor r30 versus target r31; cached list sentinel r31 versus target r30 (six differing instructions). | 2 approaches (c18_u9_20261107) |
| `fn_80243464` | game/fn_80243464 | 99.40 | 16 instruction operand differences at 0x8024360C..0x80243694: scale conversion/constants scratch f4/f5/f6/f7 cycling, x f1 versus target f2, scale f0 versus target f1, and final addition operand order. Identical... | 3 approaches (c17_u69_20261107) |
| `clItemBoxManager_Dtor` | game/clItemBoxManager | 99.37 | Box walker r28 and sentinel r29 remain swapped against target r29/r28. | 3 approaches (c17_u7_20261107) |
| `EnemyRun_BaseInit` | game/EnemyRun_BaseInit | 99.37 | Only matrix row-base setup: target mr r9,r29 then addi r7,r31,0x30; source addi r9,r31,0x70 then addi r7,r31,0x30. Same 1300 B. All loop GPR colors, increment order and FP arithmetic now match. | 6 approaches (c19_u72_20261107) |
| `AnimState_Step` | game/AnimState_Step | 99.36 | Remaining text is saved-register partition (s r25 vs target r26; offset r30 vs r25; track i r26 vs r30; scalar j r27 vs r29; result r29 vs r27), initialization scheduling, plus interpolation data/first-key r8/r7 vs... | 6 approaches (c18_u178_20261107) |
| `GabyouItem_Tick_HeldAndHoming_2Eto31` | game/GabyouItemHeld | 99.36 | Aggregate-copy tail +0x700..0x710: subphase lbz is hoisted, final copied word uses r3 rather than r0. Yaw blend +0xA84/+0xA8C/+0xA90: product f1 versus f3 and complement f2 versus f1. Retarget bus +0xD34..0xD50:... | 6 approaches (c19_u9_20261107) |
| `Effect_CompoundRing_PlaceChildren` | game/EffectCompoundRing | 99.33 | 21 instruction rows: mode0/mode1 quotient result r5 versus target r0, quotient*3 r0 versus target r5, sign/offset bases r4/r3 versus target r3/r4; mode0 FMADD multiplicands f30,f1 versus target f1,f30. One additional... | 3 approaches (c17_u75_20261107) |
| `RankingMgr_UpdatePositions` | game/RankingMgr_UpdatePositions | 99.30 | Nine final-loop instruction rows have register operands changed: index r26 vs target r27; synthesized array cursor r28 vs target r26; controller r27 vs target r28. Collection r29 and all earlier instructions are exact. | 2 approaches (c17_u76_20261107) |
| `fn_8028EAA8` | triforce/amnet_nm2_rest | 99.28 | 21 aligned diff rows: four trace records each have five index/increment/multiply/add scratch operand mismatches (r3/r4/r8); missing target unreachable unconditional branch at 0x8028EEE0. Source 1224 B vs target 1228... | 6 approaches (c19_u8_20261107) |
| `setupTopHalfCamera` | sysdolphin/baselib/cobj_nm1 | 99.28 | First bottom clamp: extra fmr f0,f2 at source +0x90; target retains bottom in f2 and emits fsubs f2,f0,f1 at +0xA0, then fsubs f1,f2,f31. Source instead updates f0. Source text is 616 B versus target 612 B. Following... | 3 approaches (c18_u3_20261107) |
| `fn_80243074` | game/fn_80243074 | 99.28 | Index/position saved GPRs r28/r29 are swapped; both RotatedAngle expansions use different callee-saved FP homes; projection copy loads x,y,z instead of target y,x,z with f5/f6/f7 rotation. Newton iterations now exact. | 3 approaches (c18_u25_20261107) |
| `fn_801F7F50` | game/fn_801F7F50 | 99.12 | Constructor FP web homes only at +0x44..+0xC8: source w=f3/h=f2/cos=f0/sinWidth=f9/dy=f1/top=f7 versus target f5/f6/f3/f7/f2/f9. All instructions from +0xCC through function end now match, including first depth... | 6 approaches (c18_u193_20261107) |
| `fn_8022CE34` | game/EnmyFaceEffect_nm1 | 99.11 |  | 6 approaches (c19_u43_20261107) |
| `fn_801BEDF0` | game/fn_801BAA88 | 99.11 | Nested row/group/key induction and row-base homes differ across r20-r29; 684-byte control flow unchanged. | 1 approaches (c19_u21_20261107) |
| `HSD_LObjSetupInit` | sysdolphin/baselib/lobj_init_nm | 99.07 | Source3024 versus target3016: extra active_lights lis/addi before allocation traversal, initial active-base/vmtx/type/spec-id GPR partition and later loop count/cursor homes differ; owned literal relocation names remain. | 3 approaches (c19_u13_20261107) |
| `AssocTree_FreeAll` | game/AssocTree_FreeAll | 99.03 | All 47 differing instruction rows are the global tree r30 versus target r31 / root node r31 versus target r30 swap. 242 instructions, control flow, call order, offsets, 8-byte extab and 12-byte index otherwise exact. | 6 approaches (c18_u172_20261107) |
| `STLContainer_DisposeRecursive` | game/STLContainer | 99.03 | Tree and node parameter webs are swapped: target tree r31/node r30; source tree r30/node r31. All 242 instructions otherwise have matching shape. | 2 approaches (c17_u22_20261107) |
| `CourseScene_Load` | game/CourseEnvironment | 99.00 | Zone byte-offset r28 versus target r26 and object walker r26 versus target r28; initial guarded-copy scheduling differs. Debug byte counts use r22/r23 versus target r24. Both WarpDash calls still lack the second... | 3 approaches (c19_u17_20261107) |

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
| `fn_801F8250` | game/fn_801F8250 | 96.33 | `slwi`/`addi` order (4 lines); table shared with fn_801F7604..fn_801F8A34 TUs | R4 2026-11-07: the TU merge is blocked by onmokoworks claims #2434 (fn_801F7604, owns .rodata 0x803BEDC0), #2320, #2376, #2395. Only fn_801F7604, fn_801F8250, fn_801F8668 and fn_801F894C reference the table; fn_801F7604 and fn_801F894C use `addi rX, r31, 0` off the pool base. So the original TU spans at least 0x801F7604..0x801F89F0 and owns that .rodata. |
| `fn_801F894C` | game/fn_801F894C | 97.44 | rodata table `lbl_803BEDC0` shared by 4 TUs | target `addi r3, r31, 0` = section-pool base, so 0x801F7604..0x801F89F0 was one TU owning that .rodata (merge). `opt_propagation off` only gives `mr` R4 2026-11-07: the TU merge is blocked by onmokoworks claims #2434 (fn_801F7604, owns .rodata 0x803BEDC0), #2320, #2376, #2395. Only fn_801F7604, fn_801F8250, fn_801F8668 and fn_801F894C reference the table; fn_801F7604 and fn_801F894C use `addi rX, r31, 0` off the pool base. So the original TU spans at least 0x801F7604..0x801F89F0 and owns that .rodata. |
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
| `clFlowRound_Update` | game/clFlowRound | Init done (b36c4cd). Update draft compiles in the real TU (namespace `upd` view, `wip/clflowround_update_integrated_wip.cpp`) at ~700 lines: the pool base takes r31 and self r26, every other register shifts by one. Decl-order sweep, member vs free function, deferred vs in-place codegen: no change | `wip/clflowround_update_integrated_wip.cpp` |
| `clFlowKart_UpdateDisplay` | game/clFlowKart_UpdateDisplay | Needs the clFlowKart TU merged (0x801D7920..0x801D878C, like clFlowChara in 07e057e). With pooled statics the need-table addressing matches, but the CSE'd `kart*4` is colored last (r27, target r30): 112 lines; decl-order sweeps do not move it. Unpooled `rd` pointer form: 8 lines (fold) | `wip/clflowkart_updatedisplay_wip3.c` |
| `WarpZone_CheckEntry` | game/auto_800A8F4C_block | 99.2% / 24-line plateau: mgr r7 vs r6 swap with the zone pointer. Calling the inlined `WarpZone_FindContainingOBB` with a local zone gets 30 lines, `obbs[i]` form 24. ~20 loop/caller forms, pragmas no effect. The C version also grew main.dol by 0x20 (check extab) | `wip/asm-a/warpzone_checkentry_99pct.patch` |
| `fn_80147900`, `fn_80147AF4`, `fn_80147CE8` | game/RaceHud_80147470 | 2 lines (`mr r3, r4` copy of `-0x100`), 10 lines (f2/f3 swap in branch 2), not tuned. Whole TU matches under GC/2.6 too (naari3 claim #2468) | `wip/racehud_80147900_wip.patch` |
| `fn_80146000` (RankPanel) | game/RankPanel_80144430 | throws `out_of_range`, but the typeinfo string `lbl_80361E60` lives in another TU's rodata | |
| `CarrotItemEffect_Render` | game/CarrotItemEffect_Render | stack order of eye/at/a/b locals reversed vs target; decl permutations don't help | `wip/carrot_render_wip.patch` |
| `CardTaskManager_RenderOverlay` | game/CardTaskManager_RenderOverlay | 18 lines (`-lang=c++`, `opt_strength_reduction off`, `% 4U`); names/offset/0x4330 register 3-cycle (naari3 claim #2482) | `wip/cardtaskmanager_renderoverlay_wip.patch` |
| `RivalRun_UpdatePathFollower` | game/RivalRun | ~120 lines, GPR/FPR coloring; target caches position floats in locals | `wip/rivalrun_updatepathfollower_wip.patch` |
| `NokoNokoChallenge_CalcResultText` | game/NokoNokoChallenge | 3 lines (`opt_common_subs` + `opt_lifetimes` off); cup index lands in r3 instead of r0 | `wip/asm-a/nokonoko_calcresulttext_4line.patch` |
| `KartItem_Tick`, `KartItem_OnKartHit`, `KartItem_ApplyImpact*`, `KartItem_PerFrameStep` | game/auto_ONKARTHIT_block | GC/2.6 TU; drafts 24-130 lines off; some need header edits first (naari3 claim #2171) | `docs/drafts/*.handoff.md` in this repo |
| `clNormal3D_Exec` | auto_clNormal3D_Exec_text | 1844 bytes; C++ draft ~149 diff lines (register webs, same as sibling Object_DriveAnimAndSkin) | `r1-drafts/clNormal3D_Exec.cpp` |
