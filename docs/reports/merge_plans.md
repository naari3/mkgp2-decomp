# Pool / TU-merge plans for onmokoworks' below-100% functions (2026-11-07)

Read-only diagnosis by naari3's thread B. The input was the 324 onmokoworks-claimed
functions below 100%. Functions that R5's pragmasweep already solves (0 diff lines in
docs/reports/pragmasweep_results.md) were skipped. Nothing in these TUs or their issues was
changed on main.

The candidates below were picked because their objdiff diff is (mostly) a pool or
section-anchor difference. Either the target addresses several objects as `base+off`
from one register (`addi rX, rBase, 0`, `addi rX, rBase, 0x18`), and ours uses
`mr`/separate `lis/addi`, or the reverse. CW only pools objects that are defined in the
same TU, so the fix is always one of two things:

* The TU defines (owns) the data itself, as separate static/global objects in the right
  order, instead of `extern`-ing one big auto-split blob.
* The TU is merged with the neighbour TU that already owns the data, because the
  original was one file.

Patches are in `docs/archive/onmoko_patches/merge/` (`git apply`).

## Verified

| Function | Issue | TU | Before | Fix | After | Patch |
| --- | --- | --- | --- | --- | --- | --- |
| fn_8020B234 (ItemShowcase ctor) | #2361 | game/anon_8020AF08_nm1.cpp | 97.54% (13 lines) | The TU owns `.rodata 0x803C2E50..0x803C3508` (new split line). The 0x6B8-byte blob `lbl_803C2E50` is really three static arrays (0x18C / 0x344 / 0x1E8 bytes) passed to the three `new ShowAnim(...)`. Defined as `static const unsigned int lbl_803C2E50[] / lbl_803C2FDC[] / lbl_803C3320[]`, they pool, giving the target's `addi r30, r5, @l` + `addi r7, r30, 0 / 0x18C / 0x4D0`. | 99.86% (6 lines: `itemId` compare is loaded into r0, target r3; pragmasweep k=2 + 100 decl orders does not fix it) | anon_8020AF08_nm1_pool.patch. Clean build `main.dol: OK` with it applied. |
| fn_80192F04 (sound volume/pan from listener) | #2394 | game/clsound/fn_80192F04.c | 97.74% (9 lines) | Defining the listener vectors in the same TU as three objects, in the order `lbl_80495F20` (right) / `lbl_80495F2C` (forward) / `lbl_80495F38` (pos + w), instead of one extern `ClSoundListener` struct, gives every instruction. Only the reloc name differs (`...data.0` vs `lbl_80495F20`), which goes away once the data is really in this TU. | instructions 100% | fn_80192F04_codegen_probe.patch. This is a codegen probe, not a link-ready patch: those three objects are owned by game/fog/Fog_UpdateFromCourseScene3D.c (`.data 0x80495F20..F48`). See the merge plan below. |
| fn_801913B0 | #2439 | game/clsound/fn_801913B0.c | 95.42% (16 diff lines) | Same probe as fn_80192F04. | The pool part is fixed. About 10 lines are left: scheduling around the `lbl_80379554` load, and pragmasweep finds nothing. | fn_801913B0_codegen_probe.patch (probe) |

### Merge plan: clsound listener TU (fn_801913B0, fn_80192F04, Fog_UpdateFromCourseScene3D)

`lbl_80495F20/2C/38` are used by fn_801913B0, fn_80192F04 and Fog_UpdateFromCourseScene3D.
They pool in all three, so all three were one file. That file is
`.text 0x801913B0..0x801933D0` (or at least 0x80192F04..0x801933D0 for a first step).
It owns `.data 0x80495F20..0x80495F48`, and probably `.rodata` around the `lbl_80379554`
sound table too.

The text range today holds 22 split TUs: fn_801913B0 … fn_80192688, SoundMgr_Play (asm),
fn_80192F04, fn_80193134, WeatherSystem_PickVariant, fn_801932F8, and Fog. Two steps:

1. Smallest step: merge `fn_80192F04.c + fn_80193134.c + WeatherSystem_PickVariant.c +
   fn_801932F8.c + fog/Fog_UpdateFromCourseScene3D.c` (0x80192F04..0x801933D0). Move the
   `.data` line from the Fog split into the merged one, and define the three vectors
   before fn_80192F04, using Fog's definitions. Flags differ: Fog has
   `extab_padding=b"\x00\x00"` and fn_80192F04 has none. Check extab with
   extab_order.json.
2. Later, fold the 0x801913B0..0x80192F04 TUs into it, once SoundMgr_Play is C.
   SoundMgr_Play is still asm; see docs/wip/soundmgr_play_280lines.c.

## Plans only (not verified)

All of these show the pool pattern in the diff. The "owner" column comes from
config/GNLJ82/splits.txt on main 8984e0a.

| Function | Issue | Pool object(s) | Who owns the data | Plan |
| --- | --- | --- | --- | --- |
| fn_8016E568 CoursePropList ctor | #2373 | `CoursePropCtor_data_80491150` (.data, the 4 prop lists, 0x50) plus the vtable `Scene_8016E1C0_data_804911AC` at base+0x5C | unowned (`auto_07_80491100_data`) | The base also covers `sdata_806CF750_data_804911A0` (RTTI {name,0,0}) and the vtable `Scene_8016E1C0_data_804911AC` {RTTI,0,fn_8016E358,fn_8016E308,fn_8016E1C0,fn_8016A26C}. That vtable points into game/Scene_8016E1C0.cpp, so the original TU is `Scene_8016E1C0.cpp + mapeffect/CoursePropCtor.cpp` (`.text 0x8016E1C0..0x8016E7E4`). It owns `.data 0x80491150..~0x804911D0`, and the class is a real polymorphic class with RTTI (the compiler-generated vtable pools, like clFlowRound_Init). Write the 4 lists as separate static `CoursePropData *[]` arrays (7/7/3/3 entries). |
| fn_80227B98 | #2311 | `DNBress_nm3_rodata_803C6ED0` (.rodata) + `DNBress_nm3_data_804EDF80` (.data) | unowned; `DNBress_nm3_data_804EDF80` is used by many DNBress_* TUs | Every DNBress_* TU around 0x80224ECC..0x80227FA4 is one file. Neighbours anon_80224ECC / anon_802253EC already own `.data 0x804EDF08..` and `.rodata 0x803C6E58..`. Merge DNBress_nm3 into the DNBress group TU and extend its .data/.rodata to cover 0x804EDF80 / 0x803C6ED0. |
| TaMode_Init | #2259 | `TaMode_vtable_8040F0B0` = base 0x8040EA58 + 0x658, plus `TaMode_FrameUpdate_rodata_80321980` (.rodata) | the base is the first byte of **TaMode_FrameUpdate.cpp's** `.data 0x8040EA58..0x8040F0A4`; 0x8040F0A4..F0C4 is unowned | Merge `TaMode_FrameUpdate.cpp + TaMode_Dtor.cpp + TaMode_Init.cpp` (`.text 0x800A2B90..0x800A4578`, `.data 0x8040EA58..0x8040F0E8`). TaMode_Dtor uses the same objects. This looks like the cleanest real merge of the list. |
| fn_80245C1C HudFlow24Ctor | #2436 | `HudSelectionUpdate_data_804EE7C8` + `HudFlow24_vtable_804EE83C` (base+0x74) | unowned (0x804EE760..0x804EE854) | `HudFlow24_vtable_804EE83C` is also used by HudSelectionDestroy (0x80245B10..0x80245C1C), so merge `HudSelectionDestroy.cpp + HudFlow24Ctor.cpp` and own `.data 0x804EE7C8..0x804EE854`. Check whether HudSelectionUpdate (data at 0x804EE854) is the same file. |
| fn_8021ABFC | #2257 | `lbl_804EDC88` base, `clCSOrgKartModel_vtable_804EDCFC` at +0x74, plus `lbl_803C4E60` | unowned (after anon_80218F40_exact3's .data ending 0x804EDC84) | Merge `anon_8021A7C8.cpp + anon_8021A7C8_nm1.cpp` (`.text 0x8021A7C8..0x8021B568`) and own `.data 0x804EDC88..` (end: first object not used by these two). |
| fn_80170B5C | #2381 | `Scene_80170B5C_rodata_8036E220` (.rodata) + `GrowSet_vtable_8049128C` (.data) | unowned | `GrowSet_vtable_8049128C` is also used by Scene_801709FC (0x801709FC..0x80170B5C), so merge `Scene_801709FC.cpp + Scene_80170B5C.cpp` and own `.data ~0x80491280..0x804912F8` (ZoneVisibility starts at 0x804912F8) and `.rodata` from 0x8036E220. |
| fn_801967F0 | #2415 | `lbl_8037D888` (.rodata) + `ParticleView_vtable_80495FA4` (.data) | unowned | Also used by fn_8019618C and fn_80196758, so merge `objview/fn_8019618C.cpp + fn_80196758.c + fn_801967F0.cpp` (`.text 0x8019618C..0x80196AA0`). Own `.data 0x80495F98..` (after MapWaterEffect_Init) and `.rodata ..0x8037DA90` (before fn_80197D20). |
| clFlowCourse_Init | #2203 | `clFlowCourse_data_8049B1E0` + `clFlowCourse_vtable_8049B3B4` | unowned (before fn_801CE800's .data at 0x8049B3C8) | These are also used by fn_801CE918, fn_801CEB78, clFlowCourse_Update and clFlowCourse. The clFlowCourse family (0x801CE800..0x801D1800) is probably one TU, like clFlowChara (07e057e). That is a large merge with several claims; do it last. |
| clFlowTaPlease_Init | #2337 | `clFlowTaPlease_Init_rodata_8039B470` (.rodata) | unowned (between clFlowRound 0x8039B3C8 and clFlowCourse_Update 0x8039B990) | Own `.rodata 0x8039B3C8..` in clFlowTaPlease_Init (0x801CE324..0x801CE800) and define the objects in it. Single-TU fix; same recipe as clFlowCup_Init 747c96d. |
| fn_801BF644 | #2194 | `lbl_80399E9C` (.rodata) | unowned | Only scheduling of the `lis/addi` pair differs, so this may not be a pool. If fn_801BAA88.cpp (0x801BAA88..0x801C1F88) owns the .rodata and defines it, the address may be CSE'd earlier. Low confidence. |
| fn_8021D780 / fn_8021C070 / fn_8021DAB8 | #2206 | `lbl_803C5400` | the computed base 0x803C44C8 falls in anon_80216568's .rodata, which is probably a wrong base guess | Needs a closer look. fn_8021E0FC from the same TU is already fixed by R5's pragma patch. |
| CourseData_LoadPathTable | #2418 | `lbl_803285C0` | WarpDashMgr_Init owns `.rodata 0x80326CB0..0x803284C0`, so the base guess looks wrong | Needs a closer look. |
| fn_801F0ECC | #2252 | `lbl_804E4C28` (.data) | unowned | Menu801F0CC0 (0x801F0CC0..0x801F26C8) together with fn_801F27B4, which is its `__sinit` (docs/gave_up.md). Merge and own the .data from 0x804E4C28. |
| fn_8028D8CC | #2181 | `amnet_setup_nm_rodata_803F2798` (.rodata) | owned by triforce/amnet_nm3.c (`.rodata 0x803F2798..0x803F2880`) | amnet_nm3 (0x8028C1B8..0x8028D3E4) and amnet_nm2_rest (0x8028D8CC..) share the pool, but amnet_io (0x8028D3E4..) and amnet_nm2 sit in between. So the original amnet.c spans all of them: merge amnet_nm3 + amnet_io + amnet_nm2 + amnet_nm2_rest. |

Already known before this pass:

* fn_801F8250 / fn_801F894C / fn_801F7604 share table `lbl_803BEDC0`. Merge
  0x801F7604..0x801F89F0 (claims #2434, #2320, #2376, #2395).
* fn_801ECA14 uses the pool `lbl_803BD920`.

## RaceHud..Scene .rodata pool (0x80362858..0x803678D8)

The unsplit range is several original TUs' pools. Two of them have section anchors:

* **0x80362D90..0x80363D30, anchor CSSceneGetTitle_8014ADB4_rodata_80362D90: DONE.** The original TU is
  0x8014ADB4..0x8014D540 (clCSSceneGetTitle plus CSPartsHolders). 924f64a split RaceHud at
  0x8014ADB4 into game/CSSceneGetTitle_8014ADB4.cpp. That TU owns this .rodata and the
  fn_8014B118 jumptable .data, and has typed tables. fn_8014BBE4 is matched (bf4e838).
  fn_8014ADB4 is ~93% (anchor addressing now right; only scheduling is left, see gave_up).
  Lessons:
  - GC/2.6 anchors the TU's own objects (`...rodata.0`) when a function uses them
    enough.
  - The linker deadstrips pool objects that nothing references, so wrap them in
    `#pragma force_active on` while their users are still asm.
  - The weak inline-dtor copy (dtor_800869D0) needs its own entry at the end of the
    TU's tools/extab_order.json list.
* **0x80363D30..0x803678D8, anchor Scene_8014E0C4_rodata_80363D30 (Scene_8014E0C4): parked.** Defining the
  pool inside Scene_8014E0C4.cpp (WIP:
  docs/wip/asm-a/Scene_8014E0C4_pool_wip.cpp + Scene_pool_splits.patch)
  builds the layout correctly.
  - Typed objects (`AttractEntry Scene_8014E0C4_rodata_80367488[12]`, `CourseModeInfo Scene_8014E0C4_rodata_80366EF0[21]`,
    `SprEntry Scene_8014E0C4_rodata_803644D0[81]`) keep fn_8014E618, fn_80150C1C and fn_80154FB0 matching.
  - Still broken: DrawColoredQuad, fn_8015376C and fn_80153C00, which read the CamVecs at
    `(char *)Scene_8014E0C4_rodata_80363D30 + 0x30B0/0x30D4/0x30F8`. Once Scene_8014E0C4_rodata_80363D30 is a 0x4D4-byte
    object defined in the TU, CW interleaves the 9-word copy loads and stores, and the
    frame is 0x10 smaller.
  - Separate named CamVecs objects get direct `lis/addi` instead of the anchor, even as
    file statics.
  - Next idea: the original probably had all of 0x80363D30..0x80366E4C as file statics
    that every function reached through `...rodata.0`. Try the CamVecs as statics used by
    a function that also touches another pool object, or check which pool objects these
    three functions really read.
  - Blocked by this: fn_801500F4, fn_8015061C and fn_801540E0 (docs/gave_up.md).

## Not pool, naming only

Some near-100% functions differ only in symbol names (`jumptable_X` vs `@N`, `lbl_` vs
`...rodata.0`): for example fn_8017CE1C (99.98%) and clFlowClass_Update. These need a
rename in tools/extab_user_renames.json, or an in-TU definition with the right name, not
a merge.
