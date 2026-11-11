# Matching and acceptance rules (shared between contributors)

This page is the one place for the rules both sides of the project (naari3's
Claude threads and onmokoworks's Codex/Claude workers) use to decide whether a
change is acceptable and how to get there. It is a summary: register-allocation
fixes are collected in `docs/regalloc_patterns.md`, functions people gave up on
in `docs/gave_up.md`, and older long-form notes in `docs/notes/`.

If a rule here is wrong or missing, fix it in a small commit and say so in the
commit message, so the other side sees it.

**Messages between the two sides' agents** (techniques that just worked,
hints on the other side's claimed TUs, requests, questions) go on the board in
[`docs/agents/`](agents/README.md): read `to_onmokoworks.md` / `to_naari3.md`
first (`python3 tools/agent_board.py open --for om` or `--for n3`), answer with
a `re:` entry in your own outbox. Append only.

## 0. What changed recently (read this first)

The rules below are current practice, not permanent law: naari3 changes them
as the project moves, and the newest dated line wins over older text anywhere
in `docs/`. Whoever changes a rule adds ONE line here (newest on top, date in
UTC, where the full text is) and posts the same line on the agent board
(`docs/agents/`). Drop lines older than about two weeks once the sections
below say the same thing.

- 2026-11-11 07:57Z Port readiness (n3): g_itemClassTable (autodata/data_8041C9D4.c) is ItemClassRow[278] with byte members instead of void *[1390]. Byte-identical.
- 2026-11-11 07:56Z Port readiness (n3): AnimState description tables are AnimEntry arrays (include/game/types/AnimEntry.h) instead of void * arrays with the type in the top byte: fn_80116DD0.c, fn_801152B0.c, autodata/data_80419FB8.c, autodata/data_8041A4F8.c; tool tools/port_abi/anim_tables.py. Byte-identical.
- 2026-11-11 07:53Z Port readiness (n3): cabinet-link slot fields that cross a byte boundary (scene, wins, track, id) are accessed through include/game/types/pcb_link.h in PCBCommBroadcast.c, PCBCheckRecv.c, PCBCheckProcess.c, fn_801D1890.cpp, FaceEffect.cpp; notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-11 06:41Z Port readiness (n3): src/game/dlistutil and its three private headers read display lists and vertex buffers through GXDATA_U16 / GXDATA_SET_U16 / GXDATA_F32 (include/game/types/gx_data.h); notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-11 06:05Z Port readiness (n3): CObjProject.c declares and calls GXProject in the SDK's parameter order; sweep tool tools/port_abi/arg_class_order.py (prototype against library definition/header by float/other parameter order), notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-11 03:34Z (naari3): onmokoworks may convert hand-written vtables to
  real classes too, any class or family it likes (`docs/notes/rtti_classes.md`
  rules: clang check, `main.dol` identical). No fixed split: one unit-claim
  per unit before starting, never touch a unit the other side has claimed,
  and each side posts on the board which family it is starting.
- 2026-11-11 02:44Z Port readiness (n3): prototypes of fn_8020A734 are preceded by game/types/tween_set_order.h (host-only macro that reorders (tween, frames, from, to) to the definition's (tween, from, to, frames)); a new unit declaring fn_8020A734 must include it ahead of the prototype. Notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-11 02:08Z Port readiness (n3): 16-bit reads of Shift-JIS char text use SJIS_WORD / SJIS_WORD_LOAD (include/game/types/sjis_word.h) in TexMgr_SetTexture.cpp, TitleNameHud_nm1.cpp, RankPanel_80144430.cpp; notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-11 02:30Z (n3, one-off by naari3's request; our matching stop otherwise stands) CardSaveData_Parser 99.81 -> 100 %: opt_propagation off plus a load local declared before the constant's local inside an inline; new docs/regalloc_patterns.md section 100. Card_VerifyChecksum in the same unit is still 96.49, so the unit stays NonMatching.
- 2026-11-10 21:46Z Port readiness (n3): src/musyx compiles on a host compiler (27 of 27): declaration fixes in include/musyx/sal.h, vsamples.h, debugger.h and src/musyx/runtime/hw_dolphin.c, snd3d.c. Byte-identical.
- 2026-11-10 20:55Z Port readiness (n3): StlList_RemoveByValueField takes its key struct by value, as its caller passes it; census tool tools/port_abi/byvalue_struct.py for struct-by-value against pointer mismatches between prototypes or casts and definitions (369 places, listed in docs/notes/port_abi.md, not changed). Same code, main.dol OK.
- 2026-11-10 20:23Z Port readiness (n3): prototypes whose return class (float vs integer vs void) differed from the definition are corrected (fn_8019EA8C, KartEffectFadeTransit_GetActiveValue, KartItem_AdvanceAnim3c, Saturate_Double); sweep tool tools/port_abi/return_class.py, notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-10 19:53Z Port readiness (n3): data that was defined as bytes or shorts but read as wider types is defined with the read type (lbl_806D97E8, sprite resource ids, records in autodata/rodata_80355078.c, Scene_8015BF18_rodata_80368C84); sweep tool tools/port_abi/data_width.py, notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-10 19:01Z Port readiness (n3): wrappers that took fewer parameters than their callers pass and left the rest in the registers now name and forward them (clItemBoxResponder_CmdGetWorldPos, fn_801E4524); sweep tool tools/port_abi/forwarded_args.py, notes in docs/notes/port_abi.md. Same code, main.dol OK.
- 2026-11-10 18:50Z Port readiness (n3): PathManager_UpdateAll passes a float[3] to Math_Segment2DIntersect (it writes three floats); sweep tool tools/port_abi/out_vector.py, notes in docs/notes/port_abi.md. Byte-identical.
- 2026-11-10 18:15Z 2026-11-10 (n3): wrappers that forwarded arguments through registers now name them (HUD_RegisterOverlay third parameter, KartItem_ForwardToCarMovement_8019a4e0 matrix, FaceModelSub::Reset(int), DbgMenu SoundDriver_GetOrCreate, TitleStats call in auto_ONKARTHIT_block.c). Same objects; rename key Reset__12FaceModelSubFv is now ...Fi.
- 2026-11-10 18:12Z 2026-11-10 (n3): EnemyRunType1_Init / EnemyRunType2_Init take and forward the five constructor arguments (same objects).
- 2026-11-10 18:06Z 2026-11-10 (n3): five more prototypes with another int/float order than the definition wrapped off MWCC (CarObject_ApplyInput, CarObject_ApplyDriftBoost, fn_802090F0, InputCmd_PushSample, KartMovement_PhysicsStep); AnimState_New/AnimState_Reset have their real second parameter. Same objects.
- 2026-11-10 17:29Z 2026-11-10 (n3): card-name check patterns (banned words in NameCheck_CardName.c and autodata/sdata2_806D3060.c) are unsigned short arrays of Shift-JIS codes; the byte functions on them are NAMECODE_STRSTR etc. (plain functions under MWCC). Same objects.
- 2026-11-10 16:51Z 2026-11-10 (n3): static HSD light/camera descriptors are structs (include/game/types/hsd_desc.h); HSD_LObjLoadDesc(GetCourseDataPtr()) written as one call in six units; Scene3D_GetCameraPos / Scene3D_SetupProjection have their real three parameters. Same objects.
- 2026-11-10 16:45Z 2026-11-10 (n3): autodata/data_8040E780.c: g_courseDataInstance typed as an HSD light descriptor struct (u16 flags, colour bytes) instead of pointer words. Same object.
- 2026-11-10 16:36Z 2026-11-10 (n3): constructor declarations whose float/int order differs from the definition are written ARGS_ORDER((as written), (as defined)) (include/game/types/arg_order.h); MWCC uses the first list. 18 files, same objects. docs/notes/port_abi.md.
- 2026-11-10 16:32Z 2026-11-10 (n3): all text held inside word arrays is now TEXT_WORD(...) (30 files, incl. NameCheck_CardName.c banned-word tables and many autodata units). Same objects.
- 2026-11-10 16:29Z 2026-11-10 (n3): text held inside word/pointer arrays is written TEXT_WORD('e','f','_','s') (include/game/types/text_word.h) instead of 0x65665F73; same object, needed off MWCC. tools/port_abi/text_words.py lists and rewrites them. docs/notes/port_abi.md "Text stored as words".
- 2026-11-10 16:20Z 2026-11-10 (n3): Scene_8014E0C4.cpp frees its two text-drawer arrays with delete[] instead of an explicit __destroy_new_array (same code; needed off MWCC). Rule: an array made with new T[n] is freed with delete[]. docs/notes/port_abi.md.
- 2026-11-10 16:12Z 2026-11-10 (n3): 15 functions defined void whose callers read a result: 12 definitions now return the value (CollisionFile_FixupPointers, TCPConn_LogError, Vtable_CallSlot2 ...), 3 callers corrected. Objects byte-identical. docs/notes/port_abi.md "Results read from a function defined void".
- 2026-11-10 15:58Z (n3 structure, fourth real class): `clDrawManager : teSingleton<clDrawManager>` is src/game/clDrawManager.cpp (replaces clDrawMan.cpp, clDrawMan_Dtor.c, clDrawMan_NodePool_Free.c, clDrawMan_Buckets_Free.c, clDrawMan_NodeList.c, include/game/clDrawMan_private.h; autodata rodata_80311B30.c is now rodata_80311BA8.c, new data_803FE078.c and sdata_806CEF88.c). main.dol OK, 7513/7612; hand-written vtables 347 -> 345. Also c72769e: GpPanelBase spells its two tail padding bytes as a member (rule in docs/notes/rtti_classes.md).
- 2026-11-10 15:49Z Follow-up to the 15:47Z line: four more byte tables inside normal units are typed the same way, and `tools/autodata_bytes.py` no longer takes all-float bytes for text.
- 2026-11-10 15:47Z Data units: byte arrays that hold numbers are now typed (`tools/autodata_bytes.py`, docs/notes/autodata.md). When a unit needs a table it reads through casts, do not add it to a data unit as `unsigned char[]` bytes; write floats/ints. Objects unchanged.
- 2026-11-10 15:47Z (n3 structure, third real class): `clLineManager : teSingleton<clLineManager>` is src/game/clLineManager.cpp (replaces CourseData_LoadPathTable.cpp, CourseData_Lookup.c, include/game/CoursePathTablePrivate.h and the autodata units rodata_80328B7C.c and data_80412158.c; the built-in path table is include/game/clLineManager_kp_castle_short_line.inc). main.dol OK, 7513/7612; hand-written vtables 349 -> 347. New rules in docs/notes/rtti_classes.md: deferred units have the constructor after the destructor in source; literal pool order follows generation order and can show a function the linker dropped; extab order via tools/extab_order.json; every converted class is checked with clang before landing (TransitionEffect.cpp now declares its specializations before the class for that reason); spell base-class tail padding as a member.
- 2026-11-10 15:31Z (n3 structure, second real class): `clMenuInput : teSingleton<clMenuInput>` is src/game/clMenuInput.cpp (replaces SmallObj_Dtor_VtableA.c, ServiceMenu.c, PostRace_StartScoreEntryFlow.c, PostRace_StartScoreEntryFlow_WithCardSave.c and the first function of PcbIdToIpAndModify.c; the hand-written extab of OpenFullServiceMenu became `new ServiceMenu(-1)`). This unit is NOT deferred: weak base vtable, base list, vtable in that order at the end of .data is the sign. 4 minutes with the recipe in docs/notes/rtti_classes.md.
- 2026-11-10 15:25Z (n3 structure, first real class from a hand-written vtable): `clScreenEffect : teSingleton<clScreenEffect>` in src/game/TransitionEffect.cpp now has compiler-emitted vtables and RTTI (TransitionEffect_Dtor.cpp merged into it; the unit is `-inline deferred,auto -RTTI on`, source in reverse address order). Recipe and the rules found (data order tells deferred mode; where out-of-line inline destructors land) in docs/notes/rtti_classes.md; `tools/autodata_carve.py SEC LO HI` takes a range out of a data-only unit. main.dol and the count unchanged.
- 2026-11-10 15:20Z (n3 tool, no source change): `python3 tools/rtti_classes.py` reads the game's RTTI from main.dol: the real name and ancestors of every polymorphic class, per vtable, with the functions in its slots (416 vtables, 388 classes; table in docs/notes/rtti_classes.tsv, notes docs/notes/rtti_classes.md). Use it before naming a class or a vtable: `--class <name or vtable symbol>`. Correction to the 14:56Z line: 353 of 416 vtables are hand-written (not 255 of 300). port_readiness.py has two new rows for it.
- 2026-11-10 14:56Z (naari3's decision for the PC port): the C++ object model is fixed in the SOURCE, not in the port's compiler output. Destination: one real class definition per class, with vtables and pointer-to-member constants generated by the compiler (today 255 of 300 vtables are hand-written arrays and 1,483 class names alias them). Steps, each byte-identical: fold per-unit alias classes into one header definition; real constructors and member functions; then let MWCC emit the table (section 6). New code: do not add hand-written vtable arrays or new per-unit copies of a polymorphic class. Full text: mkgp2-pc docs/port/cxx_abi_decision.md.
- 2026-11-10 14:18Z docs/notes/byte_order.md now points at libs/melee/src/sysdolphin/baselib/*.h for the on-disc HSD structs; docs/notes/port_abi.md records MWCC's vtable pointer position (at the first virtual declaration).
- 2026-11-10 14:17Z Member function pointers go through `PMF_TYPE` / `PMF_CALL` / `PMF_OF` / `PMF_IS_SET` (include/game/types/pmf.h; plain C++ under MWCC, MWCC's 12-byte layout elsewhere). Do not write `Ret (Class::*name)(...)` or `(obj->*pmf)(...)` directly. docs/notes/port_abi.md.
- 2026-11-10 14:12Z tools/port_abi/: clang-based census of calls whose argument classes disagree with the definition, and the generators for the `_ByValue` / `_Reordered` wrappers (docs/notes/port_abi.md).
- 2026-11-10 14:11Z Prototypes that order int and float parameters differently from the definition (a PowerPC-only freedom, sometimes a matching lever) are wrapped for other compilers with a `Foo_Reordered` inline in the `#else` branch (docs/notes/port_abi.md). ~90 prototypes, objects unchanged.
- 2026-11-10 14:06Z By-value struct prototypes (`Foo(Mtx44, Vec3)` against a definition taking `Vec3 *`) are wrapped for non-MWCC compilers: the original line stays under `#ifdef __MWERKS__`, the `#else` branch has the real prototype and a `Foo_ByValue` inline (docs/notes/port_abi.md). ~330 pairs, objects unchanged. Copy the block when a new unit declares such a callee.
- 2026-11-10 13:55Z Empty-parenthesis prototypes (`extern void Foo();`) must not be used for callees that take floats: the call promotes float to double, which breaks off PowerPC. Write the parameter list. Fixed in MukadeItem.c, StarItem.c, Effect.c, tornado_fragments.
- 2026-11-10 13:52Z Correction to 13:49Z: `LE_AS_WRITTEN` is gone; media-board swaps (BSWAP16/32, fd_set words) stay real swaps on every host. `LE32`/`LE16` are only for little-endian file values. See docs/notes/byte_order.md.
- 2026-11-10 13:51Z docs/notes/byte_order.md: which files the game reads from disc, the struct types laid over each (per `PORT_DATA_LOADED` kind) and every hand-written byte swap.
- 2026-11-10 13:49Z Port hooks: `PORT_DATA_LOADED(kind, pointer, size)` (include/game/types/port_hooks.h, empty under MWCC) sits after every file read; hand-written byte swaps go through `LE32`/`LE16`/`LE_AS_WRITTEN` (include/game/types/le.h). Keep the hook line when you rewrite a loader; objects are unchanged.
- 2026-11-10 13:35Z Portability: docs/notes/port_abi.md lists the patterns behind calls with fewer arguments than the definition (nested call, forwarding wrapper, REG_ARGS, by-value struct passed as address) and the bit-field convention, with what is left open.
- 2026-11-10 13:31Z Portability: a struct argument by value is what MWCC passes as the address of a caller-made copy. Units that pass that address by hand keep doing so; outside MWCC they are pointed at a by-address entry (`#define SoundMgr_PlaySE_Positional SoundMgr_PlaySE_Positional_ByAddress` in front of the prototype; the entry is defined beside the function). And: `B(A())` compiles to the same code as `A(); B();` when B's argument is A's result, so write the nested call.
- 2026-11-10 13:26Z Portability: a call that relies on a value already sitting in the argument register names it with `REG_ARGSn(...)` / `MORE_REG_ARGSn(...)` (include/game/types/reg_args.h; nothing under MWCC, the real arguments elsewhere). Try the plain argument first: it often compiles to the same code. Read the value from the disassembly of the call site.
- 2026-11-10 13:21Z Portability: bit-fields are declared per storage unit with `BITFIELDSn(type a:1, type b:7, ...)` (include/game/types/bitfields.h; reversed off MWCC so the unit's integer value is the same everywhere). `python3 tools/bitfield_runs.py` rewrites direct declarations, `--check` lists them. Same tokens under MWCC.
- 2026-11-10 13:03Z Portability: docs/notes/shared_data.md lists every way a unit's data is used by other units under another name or linkage, the convention for each (SHARED_*, non-MWCC definitions for float literals read by name), and what stays open (vtables, RTTI, string-literal pools).
- 2026-11-10 12:55Z Portability: a data object that its unit defines as `static` (or internal C++ const) while other units use its symbols.txt name is defined with SHARED_STATIC / SHARED_BSS / SHARED_EXTERN (include/game/types/shared_data.h), plus `#ifndef __MWERKS__ #define local Shared_Name` when the names differ. Nothing changes under MWCC. `python3 tools/alias_census.py --list` shows pairs still open.
- 2026-11-10 12:47Z Portability: file-scope `const` definitions with an initializer in .c units compiled as C++ are written `extern const T x = ...;` (tools/extern_const.py, `--check` lists the ones lacking it). Byte-identical under MWCC; other compilers otherwise treat them as internal.
- 2026-11-10 12:29Z (n3 portability, 1 file, default build unchanged): the NON_MATCHING C++ side of KartDriver_InitFull compiles again (it had stopped compiling when its structs were merged into the shared KartDriver header); 96.26 % now. After merging or renaming shared structs, run `python3 tools/nonmatching_check.py`: the default build does not compile those sides.
- 2026-11-10 12:27Z (n3 portability, 5 files, no code change; PC port request 6): in merged units where each former TU sits in its own namespace, a redeclaration of an extern "C" function or object with other types is written `#ifdef __MWERKS__ <the redeclaration> #else static T &name = *(T *)&::name; (or a static inline forwarding function) #endif` (clFlowKart_Init.c, clFlowCourse.cpp, TaMode_FrameUpdate_private.h). When you merge TUs and keep per-namespace declarations, use the same form, or better, one shared declaration.
- 2026-11-10 12:21Z (n3 portability, 22 files, no code change; PC port requests 6-8): more sources made acceptable to standard C++ without changing objects. Points worth copying in new code: cast when a `void *` goes to a typed pointer or an int literal to a GX enum; do not define a struct inside a cast; declare an explicit template specialization in the header before its first use; a redeclaration of a function with other parameter types (an argument-order trick) goes under `#ifdef __MWERKS__` with an inline wrapper in the `#else`; fragments that are only ever `#include`d are named `.inc` (TmpActionShake/Split/Vibrate, TmpSplit). clCab::Update (VolumeCalibration.cpp) now has its C++ under NON_MATCHING.
- 2026-11-10 12:17Z (n3 portability, 16 files, no code change; PC port requests 7 and 9): (a) `extern void f();` followed by calls with arguments does not compile as C++; about 170 such declarations in 8 game units now have parameter lists (pointers as `void *`, integers as `int`). New code: declare callees with their parameters. Two wrappers that the K&R form had hidden now forward their real second argument (KartItem_StopCarObjectSE, KartItem_ForwardToCarMovement_8019a6a4). (b) sysdolphin baselib units that define a `static` copy of a function the melee header declares extern give the copy its own name outside MWCC (`#ifndef __MWERKS__ #define X X__unit`).
- 2026-11-10 12:12Z (n3 portability, 96 files, no code change; PC port request 6): in units that switch language with `#pragma cplusplus on/off/reset`, every part MWCC compiles as C is now bracketed by `C_REGION_BEGIN` / `C_REGION_END` (`include/game/types/c_region.h`: `extern "C" { }` for other compilers, nothing for MWCC), so those names keep C linkage on PC. After adding or moving such a pragma run `python3 tools/c_regions.py` (it skips files already marked: place the two markers by hand there, END before `cplusplus on`, BEGIN after `off`/`reset`).
- 2026-11-10 12:09Z (n3 portability, 4 files, no code change; PC port request 5): a value-less `return;` in a non-void function (regalloc_patterns 54) is now written `#ifdef __MWERKS__ return; #else return <what r3 holds there>; #endif`, because C++ compilers reject it (ItemHandler_Star, Item_OrbitAnchorKart, NokoNoko_CheckHitAndKill, fn_801B4548). New uses of the section 54 lever: write the same guard and read the r3 value from the disassembly.
- 2026-11-10 12:07Z (n3 portability, ~55 files, no code change; PC port requests 1-4): absolute-address variables are written `T name AT_ADDRESS(0xADDR);` (`include/game/types/at_address.h`, same macro as dolphin/types.h) instead of `T name : 0xADDR;`; the private MWCC `va_list` copies are inside `#ifdef __MWERKS__ ... #else #include <stdarg.h> #endif`; prototypes no longer say `asm` (only the definition does); no parameter is named `this` (use `self`). New code: follow the same four points.
- 2026-11-10 11:58Z (n3 portability, 136 files, no code change): `operator new` / `operator new[]` are now declared with `size_t` instead of `unsigned long` (all overloads, placement forms too), with `#include "game/types/size_t.h"` at the top of the file. Metrowerks' size_t is unsigned long, so the mangled names (`__nw__FUl`) and every object are unchanged; clang/MSVC reject the `unsigned long` spelling where size_t is another type. `include/libc/stddef.h` now also says unsigned long (it said unsigned int). New code: write `void *operator new(size_t);` and include that header, never `unsigned long`.
- 2026-11-10 12:25Z (n3 naming, ~200 files, no code change): about 110 more data objects renamed, this time by reading their users: globals such as `g_itemObjectManager` (was `lbl_80638300`), `g_itemClassTable`, `g_itemDescriptorTable`, `g_drawEffectSlots`, the card reader state words, 8 vtables, plus what they point to. Chosen names are listed in `tools/data_names_manual.tsv`; after rebasing work in flight run `python3 tools/data_names.py fixup` as before.
- 2026-11-10 11:15Z (n3 structure, touches ~270 files, no code change): per-TU *views* of one struct (same name, each TU with its own padding and member names) are now merged into one full definition in `include/game/types/<Name>.h` by `tools/struct_merge.py`; member accesses in the TUs were renamed to the merged names (e.g. KartDriver, PlayerData, ItemEffectBus = the old KartStatus). Every object stayed byte-identical. If your work in flight has a local copy of such a struct, keep it or `#include` the header and use its member names. docs/notes/struct_dedup.md, "Merging views".
- 2026-11-10 10:50Z (naari3's answer to om-20261110-1041): the stop at 7512 ("no new matches until the user says resume", 04:40Z line below) binds naari3's threads only. onmokoworks keeps matching, landing and opening unit-claims as usual.
- 2026-11-10 10:10Z (n3 tool): `python3 tools/port_readiness.py` prints the PC-port prerequisite numbers the function count does not show (data typed / unk / no C, duplicated type names, named symbols, asm functions with a NON_MATCHING C body); `--md` for landing reports, and the Pages site has the same table. Report the before/after of your row when you land such work. docs/notes/port_readiness.md.
- 2026-11-10 (n3, NON_MATCHING sweep finished): every game function that is still inline asm now has an equivalent C side under `NON_MATCHING` (33 functions in 21 units, last one CGameCoin_Update at 90.8 %; `python3 tools/nonmatching_check.py --list`). The asm left without a C side is genuine SDK/runtime asm (dolphin os/base/mtx, musyx runtime, init). The C sides are equivalent, not matching: percentages and what was checked are in docs/nonmatching_c.md. If you match one of these for real, delete the guard and the asm together.
- 2026-11-10 10:45Z (n3 naming, touches MANY files, naari3's decision for the port): about 6,200 `lbl_` data objects got provisional names from their users (`Foo_data_80401234`, `Class_vtable_ADDR`; tools/data_names.py, notes docs/notes/data_names.md). main.dol and report unchanged. Work in flight that still uses an old `lbl_` name: after rebasing run `python3 tools/data_names.py fixup` (map in tools/data_names_map.tsv). Struct dedup also gained `--context` (C++ classes with identical text). naari3 10:12Z: these mechanical, byte-identical port-readiness changes (struct sharing, data names, data typing) may also touch TUs under an open unit-claim; rebase and run `fixup`.
- 2026-11-10 09:46Z (n3 structure, many new units, no code change): initialised data that no source defined now has C definitions in data-only TUs, `src/game/autodata/<section>_<address>.c` (252 units, about 420 KB, generated by `tools/autodata.py`; functions keep their `extern` declarations). They are ordinary units in splits.txt; configure.py lists them from the directory. To make a TU own data that sits in one of them, cut the definition out of the autodata file and move the range in splits.txt. `unk32/unk16/unk8` there mean "layout not known yet". Also: the sine table is now `float LUT_Sine_rodata_802EE580[0x8001]` in LUT_Sine.c. Details: docs/notes/autodata.md.
- 2026-11-10 09:10Z (n3 structure, touches MANY TUs, naari3's decision): per-TU struct copies are being moved into shared headers `include/game/types/<Name>.h` by `tools/struct_dedup.py` (same name + same member list only; every object must stay byte-identical, `hashes save` / `hashes diff`). Lands in batches; each batch replaces a local definition by one `#include` line in a few hundred TUs. Units under an open unit-claim are skipped. If you add a struct a shared header already defines, include the header instead. Notes: docs/notes/struct_dedup.md, census docs/reports/struct_dedup.md. Data symbols get provisional names next (tool to follow).
- 2026-11-10 09:10Z (RULE CHANGE, naari3's decision for the PC port): exception to "land asm -> C only at 100 %". A game function that is still inline asm may get a behaviourally equivalent C version beside the asm: `#ifdef NON_MATCHING` C `#else` the unchanged asm `#endif`. The default build never defines NON_MATCHING, so main.dol, the report and configure/splits/symbols do not change. The C side must compile: `python3 tools/nonmatching_check.py` (prints the objdiff percent per guarded function). Claims as usual. This is not a new way to land non-matching C for functions that already are C. Full text: docs/nonmatching_c.md.
- 2026-11-10 04:40Z: TaMode_FrameUpdate matched (93c2667c). Before more work on a near miss, check for a leftover function-wide `#pragma opt_propagation off` and try `x = !c ? A : B` for assign-then-override selections (regalloc_patterns 99). Main is past the user's stop line (7512): no new matches until the user says resume.
- 2026-11-10 04:14Z: when the native tracer (tracesweep/regfix) reports diff 0 but the real compile still differs, the unit's `mw_version` is wrong: compile the same source with every GC/* compiler (clItemBoxResponder_SpawnDebris: GC/1.3.2 93.7, GC/2.6 100, a016a6ca).
- 2026-11-10 04:02Z (n3 tool): `python3 tools/regfix.py diag UNIT FN` now also
  diagnoses near misses whose instruction sequence differs (extra `mr`,
  reload, argument/constant/store order, pool addressing, saved-register
  count, instruction selection, ...): it calls the new `tools/shapediag.py`,
  which classifies every differing run and prints the levers and sections for
  that class. Census of all non-matching functions by class:
  docs/reports/shapediag_census.md; notes in docs/thread_tips.md (last section).
- 2026-11-10 03:38Z (n3 technique): regalloc_patterns §91: argument load order
  in a C++ ctor. Prototype int/float interleave (§74), a getter with a local
  to load one argument first, and "declare in colour order, load in statement
  order" inside an inline ctor. Also: a weak `__dt__11ScopedTimerFv` must be
  listed in tools/extab_order.json or reorder_extab skips the TU (CarObject_Init).
- 2026-11-10 03:35Z: the board's `open` list no longer shows receipts
  (seen/done/declined), so anything it prints still wants a reaction.
  `agent_board.py open --fetch` reads a fresh `origin/main`. n3 threads see
  it on every wake (`.claude/settings.json`); whoever sees an open message
  tells naari3, acts, and answers it so it stops showing
  (`docs/agents/README.md`).
- 2026-11-10 04:10Z (n3 technique): regalloc_patterns §90: a struct view
  laid over a pool base and read past the end of that object changes copy
  shape and scheduling. Declare the real objects (symbols.txt split) and let
  the compiler pool them; `base + big offset` in asm is usually pooling
  (CarObjectManager_RunKartKartCollisionSweep asm -> C).
- 2026-11-10 03:35Z (n3 technique): regalloc_patterns §87: a local vector
  loaded twice in one block (instruction count 3 short). No spelling of `d[i]`
  keeps the loads apart; an access through the neighbouring object
  (`&mtx[-3]`) does, volatile gives wrong registers. Plus literal doubles in
  the sqrt inline (KartItem_ApplyImpactImpulseAndRumble asm -> C).
- 2026-11-10 03:36Z (n3 technique): regalloc_patterns §89: r20..r24 permuted
  over many loops (VSMode_Init 99.60 -> 100). Print the colouring order with
  `tracesweep.py trace ... --want`, then use an inline getter (coloured first)
  or a later-declared named local (coloured later) per value. tracesweep on the
  native compiler is 4 s per 24 variants even when the real TU takes 2 min.
- 2026-11-10 03:15Z (n3 structure, SETUP CHANGE, naari3's decision "for now"):
  seven TUs now compile against the genuine Metrowerks MSL C++ headers
  (`MslObject(...)` in configure.py, +11 functions). The headers stay out of
  the repo: run `python3 tools/fetch_msl.py` once (standard library only,
  downloads to git-ignored `build/msl_cw25`), then rerun configure. Without
  them configure prints a notice, those TUs link the target objects, main.dol
  is still OK and the report shows about 165 functions fewer. Never commit
  anything from `build/msl_cw25`. CI and `tools/cloud_setup.sh` fetch them.
  Details: `docs/notes/msl_cpp.md`; board n3-20261110-0308.
- 2026-11-10 01:25Z (n3 technique): regalloc_patterns §83: vector block
  (copy, length, scale) with only f-registers permuted. Literal instead of
  `extern const float`, multiplier through a pointer inline, load statement
  order, and reuse of named locals with the sum in the last-coloured one;
  the four only match together (ItemEffect_Projectile 98.9 -> 100).
- 2026-11-10 01:05Z (n3 technique): regalloc_patterns §80: a big inline
  expanded several times in one function. A one-line wrapper inline puts
  every `self` temp one level up (all get the same register), the first
  expansion colours its locals descending and the later ones ascending, in
  reverse declaration order. CarObject_HandleItemEffect asm -> C (fakematch:
  one copy of the inline per expansion).
- 2026-11-10 00:50Z (n3 technique): regalloc_patterns §78: two float constants in
  swapped registers = constant temps are numbered in expression walk order.
  Write the earlier statement inside the later expression
  (`a = (int)(255.0f * (t = 1.0f - t));`) or repeat the expression in both
  users. game/RaceHud_80147470.cpp is GC/2.6 now (72f59e72).
- 2026-11-09 23:50Z (n3 technique): regalloc_patterns §74: when only the
  evaluation order of one call's arguments differs (target computes the float
  args before an int arg), redeclare the callee with the float parameters
  first (`namespace alt { extern "C" ... }`). Int and float argument registers
  are numbered separately, so the guessed prototype order is a free lever.
- 2026-11-09 23:35Z (n3 structure): TU merge, 3 -> 1: game/EnemyFaceDraw.cpp +
  game/fn_8022CDE4.c + game/EnmyFaceEffect.cpp -> game/EnmyFaceEffect.cpp
  (.text 0x8022BFA8..0x802300C8, .rodata from 0x803DA710). The unit is
  NonMatching until fn_8022BFA8 (88.65%) matches; see docs/gave_up.md.
- 2026-11-09 22:55Z (n3 structure): TU merge, 4 -> 1: CoinChallengeRender /
  CoinChallengeUpdate / anon_80214B3C / CoinChallengeInit are now
  `game/CoinChallenge.cpp` (clCGameYI, GC/2.6 `-inline deferred -RTTI on -rostr`).
- 2026-11-10 04:30Z (n3 regfix): audit of regalloc_patterns §54-§94 against
  `tools/regfix.py diag` in docs/regfix_coverage.md; new diag hints for §58/§78
  (float constant creation order), §64/§85 (commutative operand order), §71
  (inline return type), §79 (lfs/fmr direction), §93 (reused pointer local for
  inline `this`), §94 (1). Add a row there when you add a section
- 2026-11-10 04:05Z (n3 regfix): `tools/regfix.py diag` neighbour section now
  says per off vreg whether it must move EARLIER or LATER in the colouring
  order and which lever does that for its kind (named local / frontend temp /
  backend temp: inline getter, named local, declaration order;
  regalloc_patterns §89)
- 2026-11-10 00:45Z (n3 regfix): `tools/regfix.py diag` flags an off `@temp`
  that may be an inline's RETURN temp (regalloc_patterns §81: return through a
  reference out-parameter); checked on the pre-match fn_8018E6FC. fn_8017DF00
  matched from the §70 diag section (7889058)
- 2026-11-10 00:10Z (n3 regfix): `tools/regfix.py diag` hint for two saved
  GPRs swapped between a pointer local and a shared loop counter
  (regalloc_patterns §73) or between two split-off temps (§57/§72); checked on
  the pre-match fn_8018E538
- 2026-11-09 23:59Z (n3 regfix): `tools/regfix.py diag` lists, for every off
  vreg (up to 8), its neighbours split into coloured-before/after with their
  registers and says who holds the wanted register
- 2026-11-09 23:55Z (n3 regfix): `tools/regfix.py diag` prints, when a saved
  register is off, the colouring sequence of all saved-register vregs and the
  sequence the target implies (who opens r31, r30, ... first), plus a
  declaration order for inline locals (regalloc_patterns §70)
- 2026-11-09 23:40Z (n3 regfix): `tools/regfix.py diag` hint for
  regalloc_patterns §69: a run of 2-6 differing instructions that is a pure
  reordering (same registers) points at a block scheduled twice (dead
  truncation deleted after regalloc); checked on VoiceSystem_Init
- 2026-11-09 23:25Z (n3 regfix): `tools/regfix.py diag` hints for
  regalloc_patterns §66 (vreg in r3 the target avoids, `void` function: missing
  non-void return type) and §67 (target `li; mr` vs ours `li; li`: variables
  are locals of an inline); the copy-direction hint (§57) now also works for
  C++ units whose target symbol is still `fn_ADDR`
- 2026-11-09 23:20Z: `game/Scene_8015AE3C.cpp` and `game/Scene_8015AFCC.cpp` are merged into `game/SceneList_80157EA8.cpp`
  (.text 0x80157EA8..0x8015B698, still Matching). Evidence: the three shared one .sdata2 literal pool (0x806D8390..0x806D85E4; the next
  TU restarts with the same 0.7f/0.0f at 0x806D85E8). Shared float literals across adjacent splits = one original TU.
  The TU cannot own .sdata2 (literals) until its four asm functions are C.
- 2026-11-09 23:05Z (n3 regfix): regalloc_patterns §65 (new): saved GPRs
  permuted between switch cases = declare the per-case value locals first at
  function scope and the payload pointer as a block local per case; one case's
  stack objects misplaced = move its setup into a nested inline owning them
- 2026-11-09 22:37Z (n3 regfix): `tools/regfix.py diag` prints a hint when a
  bad vreg is a frontend CSE temp (`@NNN`): numbering rule regalloc_patterns
  §59, and §61 (new) for shared float constants: literals + the zero passed as
  inline parameters + reverse-declared locals
  (TransitionEffect_DrawCarRouletteOverlay matched).
- 2026-11-09 22:20Z (n3 structure): the game's containers are the genuine
  Metrowerks MSL C++ (`std::deque`, `cdeque`, `vector`, `length_error`); the
  CW GC 2.5 headers compiled with GC/2.6 match exactly. Headers are not in
  the repo (`tools/fetch_msl.py` downloads them to `build/msl_cw25`); main
  does not depend on them yet (naari3 decides). Details and the name mapping:
  `docs/notes/msl_cpp.md`.
- 2026-11-09 21:55Z (n3 structure): TU merge `game/EnmyFaceEffect.cpp` +
  `game/EnmyFaceEffect_nm1.cpp` -> `game/EnmyFaceEffect.cpp` landed (2ce236c2,
  Matching, owns both vtables/RTTI; board n3-20261109-2105). New rename
  directives in `tools/extab_user_renames.json`: `"@N": "active:lbl_X"` keeps
  an unreferenced literal alive, `"#align4": ".rodata"` pins a section to
  4-byte alignment (`docs/thread_tips.md`, last two bullets).
- 2026-11-09 22:25Z (n3 regfix): `regfix.py diag` prints two more sections. "copy direction between an address and its walker" fires when ours has `addi rA,..; mr rB,rA` and the target `addi rB,..; mr rA,rB` at the same place (regalloc_patterns 57). "source-shape hints" fires for: FPR registers off while the TU reads extern float constants (float_literal_sweep.py, then reshape by hand); a vreg in r3 that the target has in r4 in a value-returning function without a valueless `return;` (regalloc_patterns 54); saved GPRs off in a TU with begin()/end()/`&x->head` (regalloc_patterns 52/53). Hints are clues, not fixes.
- 2026-11-09 22:00Z (n3 regfix): `regfix.py diag` now (1) prints a section "loop counters shared by
  several loops" when a saved GPR is off and a function-level counter drives >= 2 `for` loops: try
  regalloc_patterns §46 (block-local counter per later loop) first; (2) resolves the §40 anchor
  hint from symbols.txt. Hints printed before 6759bb0 could name the wrong base symbol, so
  re-run diag before splitting a symbol on an old hint.
- 2026-11-10 01:10Z: the last 8 test-menu units (`FlashFadeOverlay_Draw.c` .. `ServiceMenu_Page.c`, .text 0x80070EA8..0x80073E20)
  are appended to `game/CardCreate_Page.cpp`: the test-menu TU is complete (40 functions, .text 0x800668FC..0x80073E20, Matching).
- 2026-11-09 22:45Z: 14 more test-menu units (`CardRW_Renew_Page.c` .. `CameraTest_Page.cpp`, .text 0x8006B32C..0x80070EA8)
  are appended to `game/CardCreate_Page.cpp` (27 units, still Matching). The 9 remaining pages from
  `FlashFadeOverlay_Draw.c` on stay split until their two near misses match.
- 2026-11-09 22:15Z: `game/fn_801C9288.cpp` is merged into `game/clFlowRound.c` (Matching).
- 2026-11-09 21:50Z: when merging TUs, take each TU's flags from its real compile command
  (`ninja -t commands`): lib groups such as `game_extab`, `game_ai`, `game_801077C8` set
  `-Cpp_exceptions on` for every unit, and a section merged with exceptions off loses its extab
  entries and the exception-safe `new`. `tools/merge_tus.py` does this since 3edd2cdc; check a
  merged unit by comparing its extabindex function list with the target object.
- 2026-11-09 21:40Z: 18 units 0x801B7EF8..fn_801B9928 are one TU, `game/fn_801B7EF8.c`
  (board n3-20261109-2110).
- 2026-11-09 21:15Z: test-menu pages UI_PageDispatcher..CardCreate_Page (13 units) are one TU,
  `game/CardCreate_Page.cpp`; the 23 pages after it belong to the same TU and are not merged yet
  (`docs/gave_up.md`, board n3-20261109-2053).
- 2026-11-09 21:10Z (n3 regfix): two things for `regfix.py diag` users. (1) The
  allocator model changed (r31 frame pointer, spilling functions, inline asm):
  old dumps are stale, rerun diag before trusting an earlier diagnosis; on
  GC/1.0-1.2.5 units diag now prints a warning because the trace is a newer
  stand-in. (2) New `docs/regalloc_patterns.md` 45: registers of values loaded
  inside an inlined helper are steered by naming them as uninitialised locals
  of the inline; inline locals number in FORWARD declaration order.
- 2026-11-09 20:55Z (naari3): the game inline-asm functions (group C of
  `docs/agents/asm_fn_split_20261109.md`) are open to BOTH sides. Only
  unit-claims coordinate them: claim the TU right before working it, never
  touch a TU the other side has claimed. This replaces the 13:38Z line below
  for group C.
- 2026-11-09 21:10Z: `tools/tu_audit.py` no longer discounts merges that take
  the `Matching` flag from some TUs; `docs/reports/tu_boundary_audit.md`
  regenerated with that ranking (follows the 18:47Z rule).
- 2026-11-09 20:50Z: big changes (TU merges, tools, build rules) are announced
  on the board no later than the push that lands them (section 1).
- 2026-11-09 18:47Z: the original TU structure wins over the `Matching` flag;
  a merge may leave a TU `NonMatching` if `main.dol` is OK and the count of
  100% functions rises (section 2, rule 5; section 5 "Over-split TUs").
- 2026-11-09 18:39Z: pool ownership is checked before moving data
  (`pool_audit.py`, `own_data.py` guard; section 5).
- 2026-11-09 15:19Z: diagnose before guessing; a new `docs/gave_up.md` row
  names the compiler rule (section 7, `AGENTS.md`).
- 2026-11-09 13:38Z: the 158 inline-asm functions are shared out (n3: SDK and
  card, om: game group C); claims stay the binding rule
  (`docs/agents/asm_fn_split_20261109.md`).
- 2026-11-09 12:20Z: messages between the two sides go on the agent board
  instead of through naari3.

## 1. Coordination

- **Claim before you start.** Right before touching a TU, open a GitHub issue
  titled `[unit-claim] retrofit:<configure.py path>` (or `newtu:<unit>`), label
  `unit-claim`, assigned to yourself. Any client works (gh, the GitHub API or
  MCP); the convention is the rule, not a script. Close it as soon as you stop
  working on that TU, whatever the outcome (landed, no gain, abandoned;
  `completed` or `not_planned` with a short status comment). Keep the number of
  open claims close to the number of TUs you are actively working on.
- **Check open claims first.** GitHub search tokenizes titles, so searching a
  full TU name can miss a claim. List all open `unit-claim` titles and grep, or
  search a directory prefix.
- **Never touch a TU with someone else's open claim**, even indirectly (for
  example as part of a TU merge, a shared `splits.txt` block, or a rename in
  `tools/extab_user_renames.json` that belongs to that TU).
- **Big changes get announced on the board.** Changes to `tools/`, the build
  rules in `configure.py`, TU splits/merges, and anything that renumbers
  shared data get a post on the agent board (`docs/agents/`) no later than the
  push that lands them, naming the old and new TU paths and the address range,
  so the other side can re-point its work lists. Small per-TU edits do not
  need this. (naari3's threads landed about fifteen merges on 2026-11-09
  between 18:20Z and 20:50Z with only a late summary, n3-20261109-2050; that
  was a miss on our side, not the rule.)
- **Shared lists:** insert new entries next to neighbours from the same address
  range in `configure.py`, `config/GNLJ82/splits.txt`, `symbols.txt`,
  `tools/extab_user_renames.json`, `tools/extab_order.json`,
  `DATA_ALIGN4_TUS`, `SDATA2_ALIGN4_TUS`. Never append at the end, never
  reformat or reorder lines you do not own.

## 2. What "done" means

A change can land on `main` (directly or by PR) when all of these hold:

1. Rebased on the latest `origin/main`.
2. **A full build** gives `main.dol: OK`:
   `rm -f build/GNLJ82/main.dol && ninja`. Check ninja's exit code, not only
   the last line. Since `tools/extab_slices.py`, ninja tracks
   `tools/extab_user_renames.json`, `tools/extab_order.json` (per TU: an edit
   rebuilds only the TUs whose entries changed) and the `tools/postprocess_*.py`
   / `reorder_extab.py` scripts, so the old clean step
   (`rm -rf build/GNLJ82/src`) is no longer needed. It is still harmless, and
   still needed on a checkout older than that change.
3. The report's function % is not the final word. The report normalizes some
   symbol names, so a TU can show 100% and still break the DOL. Always trust
   the SHA-1 (and `doldiff` for the first differing byte) over the report.
4. A TU flips to `Matching` only when every function in it is 100% and the DOL
   still links byte-identical. A TU with one unmatched function stays
   `NonMatching` even if the rest is perfect.
5. **The original TU structure wins over the Matching flag** (naari3,
   2026-11-09 18:47Z). When the evidence says several split files were one
   original source file (shared section anchor / pool, link-order cycle, weak
   inline copy placement, section 5 and 6), merge them even if the merged TU
   becomes `NonMatching` and TUs that were `Matching` lose that flag, as long
   as `main.dol` is OK and the number of 100% functions goes up. A merge that
   is right but raises no function count yet is not landed: its evidence and
   recipe go into `docs/gave_up.md` until a function matches with it. The
   report's "matched code %" can therefore go down in a commit that is
   progress; compare function counts. onmokoworks's side may count this
   differently in its own numbers; the rule is about what may land on `main`.
6. **asm -> C lands only at 100%.** A function that is inline asm in a
   `Matching` TU is replaced by C/C++ only when the C matches; a partial draft
   goes to `docs/wip/` with a row in `docs/gave_up.md`. Both sides work this
   way (om-20261109-1418).

## 3. What source is acceptable

- **Natural code first.** Prefer code a person would have written: real types,
  real control flow, C++ classes where the target has vtables/extab.
- **Fakematches are allowed but must be marked** (rule from 2026-10-26):

  ```c
  /* fakematch (permuter): <what this fixes>
   * natural: <the code the original most likely had> */
  ```

  This covers per-function `#pragma opt_*` / `#pragma scheduling` tricks,
  permuter output, odd casts that exist only to steer register allocation, and
  `__rlwimi`-style intrinsics where plain C would also be correct.
- **onmokoworks's side does not write fakematches.** Its Codex workers are
  told not to, and its progress numbers count only natural C/C++. A marked
  fakematch from either side is still fine on `main`; it just is not counted
  as finished there, and those functions stay candidates for a natural
  rewrite. ASM bodies, manual EH and opcode-embedding are counted the same way.
- **No manual EH or hand-written extab in new work** unless the TU already
  uses it and there is no C/C++ form that emits the same table. Prefer letting
  `-Cpp_exceptions on` / C++ objects with destructors generate extab.
- **Asm that is asm in the original stays asm.** Dolphin SDK
  (`PPCArch`, `OSContext`, `OSCache`, `OSInterrupt`, PS `mtx`/`vec`), TRK
  `targimpl`, MusyX `sndSqrt`/`sndCos`/reverb/chorus, `HSD_SaveContext` are
  hand-written asm in the original sources. Do not count them as "remaining
  work". The full check against reference decomps (2026-11-09, 90 of the 91
  SDK/library asm functions) is in `docs/agents/asm_fn_split_20261109.md`.
  `HSD_MtxInverseConcat` was compiled C (MWCC prologue, C in melee) and is C
  now.
- Inline-asm bodies with hard-coded small-data addresses
  (`addi r3, r13, -0x7AE8`) must use relocations instead (`la r3, sym(r13)`,
  `sym@ha` / `sym@l`), with the symbol declared with a size
  (`extern unsigned char sym[N];`). Otherwise objdiff cannot match them.

## 4. Compiler version (`mw_version`)

Defaults per lib block in `configure.py`: game `GC/1.3.2`, Dolphin SDK
`GC/1.2.5n`, sysdolphin/HSD `GC/1.3.2`, `.init` `GC/1.0`. Override per
`Object(..., mw_version=...)` only with evidence from the target asm:

| Telltale in target | Try |
| --- | --- |
| Field load scheduled above `stw r0, 0x14(r1)` in a tiny wrapper | `GC/2.6` + read through a `const` self (`const T *self`) |
| Loads hoisted over stores / interleaved `lfs; lwz; lfs` before stores | `GC/2.6` |
| `x \| ~0xFF` as `li rN, -0x100; or` (1.3.2 gives `oris/ori`); `li -0x100; rlwimi` colour inserts | `GC/2.6` |
| `stmw`/`lmw` prologues instead of `_savegpr` calls | `GC/2.6` + `-use_lmw_stmw on` |
| Everything matches except one `mr` and one `lfs` swapped in a loop preheader (`mr r29,r28; lfs f30; mr r27,r31` in the target, `mr; mr; lfs` from 1.3/1.3.2/1.3.2r) | `GC/2.0` or later (RivalRun.c uses `GC/2.6`). `for v in 1.3.2 2.0 2.6` on the unit's ninja command line is a 5 second probe |
| Target does not auto-inline earlier-defined functions | add `-inline noauto` |
| Leaf with `addi rX, rY, 0` for an offset-0 member (no `mr`) | `GC/1.2.5n` |
| Some byte-compare / extab-order shapes (StrPcb) | `GC/1.3` (then check `tools/extab_order.json`) |
| C++ TU that needs newer template/ctor behaviour (ZoneList, ItemBox factory) | `GC/2.7` |

Most game TUs at `0x801FC1E0..` already build with `GC/2.6`. Switching a
whole TU's version is a cheap first probe, but check every function in the TU
still matches, not just the one you are working on. `GC/3.0a*` does not compile
the game's C++.

**Whole-TU version and flag sweeps (onmokoworks, 2026-11-07).** Recompiling
each `NonMatching` TU with every version above (and `GC/2.0`, `GC/2.5`,
`GC/1.3.2r`, `GC/3.0a5`) and scoring the object with
`objdiff-cli diff -1 <target.o> -2 <base.o> --format json` found three TUs
that went straight to 100% (`fn_800D4174` 1.3, `fn_801D680C` 2.5,
`fn_801D5C88` 1.2.5n) and eleven that moved closer. A second pass over flags
found `-O4,s` (instead of `-O4,p`) better for `PCBCommSendPeers`,
`EnemyFace`, `anon_8021A7C8_nm1` and `fn_801B9928`. Setting `mw_version` or
`extra_cflags` on a `NonMatching` TU is SHA-safe (the object is not linked),
so these are cheap to land even before the TU matches. Get the exact compile
command with `ninja -t commands <obj>` and write sweep objects outside
`build/GNLJ82/src`. Run the sweep in its own worktree: `ninja -t` holds
`build.ninja` open, which made a concurrent `configure.py` fail on Windows.

Always run configure as
`python3 configure.py --binutils build/binutils --compilers build/compilers --wrapper build/tools/wibo`;
without those flags ninja tries to download tools and fails.

## 5. Data, literals and pools

- **Float literals are fine anywhere.** `tools/postprocess_sdata2.py` runs on
  every compile and renames the compiler's anonymous `@N` `.sdata2` constants
  to the shared `lbl_806DAxxx` names by matching target relocations. Writing
  `0.5f` instead of `extern const float lbl_X;` often fixes FPR order
  (clamps, `x -= k; if (x < lo) x = lo;`). Use `extern const float lbl_X`
  when two identical constants exist (the postprocess maps a literal to the
  first one), or to stop constant folding.
- **Owned literals another TU needs by name:** postprocess_sdata2 exports a
  literal under the target's global name when the target defines it in this
  TU. For `.data`/`.rodata` labels use a rename
  `"@108": "global:lbl_XXXX"` in `tools/extab_user_renames.json`.
- **`@N` numbers shift when source changes.** In a C++ TU with `@N` renames,
  re-dump `objdump -t` of the raw mwcc object after any edit and fix the json;
  an unrenamed `@N` becomes `@etb_...` and the SHA fails while the report still
  says 100%.
- **Pooled base registers.** `addi rX, rBase, 0x0` (or `lis/addi` once, then
  `rX + off`) means the original TU owned that data section and touched 3+
  objects in it. The fix is to give the TU its `.data`/`.rodata` range in
  `splits.txt` and define every object in order, not to fake it with pointer
  arithmetic. If a vtable defined there loses its only C user, wrap it in
  `#pragma force_active on/reset`.
- **Over-split TUs.** If a near miss differs only in `addi rX, r31, OFF` where
  `OFF` reaches data belonging to a neighbouring split TU, the original was one
  file. Merge the split TUs back into one (concatenate sources, merge the
  `splits.txt` blocks, delete stale `build/GNLJ82/asm/*.s`). Keep the original
  file name (it matters for `__FILE__` strings). Only do this when no part of
  the merge is claimed by someone else, and announce it (rule 1). The merged
  TU may end up `NonMatching` (section 2, rule 5). `tools/merge_tus.py`
  (`plan` / `apply` / `prune-renames`, see its docstring and
  `docs/thread_tips.md`) does the mechanical part for C TUs: it rewrites
  `splits.txt`, `configure.py` and the two extab json files. Worked examples
  and what had to change on the way: `docs/regalloc_patterns.md` §32 (item
  select, ten files), §40 (race voice, 53 files).
- **Which TU owns a pool: check before moving data.** `tools/pool_audit.py`
  (output `docs/reports/pool_audit.md`) lists functions whose target reaches
  several objects from one base; an `OTHER` or `UNOWNED` row on a near miss is
  an ownership bug, not a register problem. Never give the middle of another
  TU's anchor pool to a different TU: `tools/own_data.py apply` refuses such a
  range since 7653d99 (NameCheck_CardName sat at 99.81% for exactly this).
- **Object boundaries inside a pool.** Every distinct `N` in the target's
  `addi rX, anchor, N` is the first byte of a real source object; split the
  pool there (in the source and in `symbols.txt`) and index that object
  directly instead of `base + CONST` (`docs/regalloc_patterns.md` §40;
  `python3 tools/leversweep.py detect` lists candidates in
  `docs/sweeps/leversweep/anchor_detect.md`).
- **Identical instruction, still `DIFF_ARG_MISMATCH` (pooled offsets).**
  objdiff resolves `addi/lfs rX, rBase, OFF` inside an owned pool to the data
  symbol at that address. If `symbols.txt` has one big target object
  (e.g. `lbl_X size:0x44`) where the source defines two (`lbl_X` + `lbl_Y`),
  the same instruction reads `lbl_X+0x20` vs `lbl_Y` and counts as a miss.
  Fix: split the object in `symbols.txt` to match the source objects
  (e263a5ca, Jungle16ACtor fn_8016AB58 99.79 -> 100). Find them with
  `objdiff-cli diff -p . -u main/<unit> -o out.json <fn>`: same `formatted`
  text on both sides, `R_PPC_NONE` relocation, left addend != 0.
  Found 2026-11-08 in: fn_8017EFFC (16 of 18 diff lines), fn_801F7604 (10/14),
  fn_801F3BD8 (8/12), TaMode_FrameUpdate (6/21), fn_8023AC14 (4/22),
  Race_PerFrameTickAndAudio, fn_801F36D0, fn_80209C88, fn_80283154.
- **Jump tables** need the TU to own the table (`.data start:end:` in
  `splits.txt`). If the owned range starts at 4 mod 8, add the TU to
  `DATA_ALIGN4_TUS` (`.sdata2` equivalent: `SDATA2_ALIGN4_TUS`).
- **Pooled `.bss` order (multi-TU merges):** a C TU emits pooled `.bss`
  objects in first-use order, a C++ TU in definition order. When one merged TU
  must own a `.bss` pool in address order, define the objects up front inside
  `#pragma cplusplus on` / `extern "C" { ... }` / `#pragma cplusplus off`
  and leave the functions in C (SetCourseParams merge, .bss
  0x805AC600..0x805D2AA8). Give each object its real element type: a
  `((T *)lbl)[i]` cast macro over an `unsigned char` blob changes regalloc in
  small indexed accessors (addi/add operand order, 91-99%).
- **Read-only tables:** `extern const T tbl[N]`. Non-const changes load
  scheduling.
- **s64 globals** split by dtk into `XHi`/`XLo`: merge into one 8-byte symbol in
  `symbols.txt`.

## 6. C++ / extab conventions

- `lwz r12, 0(r3); lwz r12, X(r12)` is a real C++ `virtual` call (slot
  `(X-8)/4`). `if (p) p->vt[8](p, 1)` is `delete p` with a virtual dtor.
- Singleton getters / allocators with a 16-byte extab and `DELETEPOINTER` are
  `new T(...)` with an inline ctor. Declare
  `void *operator new(unsigned long); void operator delete(void *);` (do not
  define an inline `operator delete`). Rename `__ct__...` per TU through
  `tools/extab_user_renames.json`.
- A C++ TU with renames needs `extab_padding=b""` on its `Object` so the rename
  postprocess runs.
- **Singleton instance reads** that the target compiles as
  `cmplwi r3, 0; bne; li r3, 0` (a defensive null check on the global) use
  `SINGLETON_INSTANCE(g)` from `include/game/singleton.h` (it expands to
  `((g) == 0 ? 0 : (g))`). See `docs/notes/singleton-getter.md`. Prefer the
  macro over open-coding the ternary.
- When the compiler emits functions with extab in a different order than the
  target, add the TU to `tools/extab_order.json`. `reorder_extab.py` silently
  skips an entry whose function set does not equal the real extabindex rows.
- **Merging TUs that mix manual and automatic extab** (asm functions or C
  functions with `.extab_user` entries next to non-leaf C/C++ functions that
  get automatic extab) is not blocked: the object then has two
  extab/extabindex pairs, and `reorder_extab.py` interleaves them once the
  merged TU's key in `tools/extab_order.json` lists every function that has an
  extabindex row, in target order. Also: rename the automatic `@N` extab and
  extabindex symbols to the target `@etb_`/`@eti_` names in the TU's
  `tools/extab_user_renames.json` key; wrap a C++ part in
  `#pragma cplusplus on` / `#pragma cplusplus off` (not `reset`); and put
  `#pragma exceptions off` / `reset` around a C function that keeps a manual
  entry, or it gets an automatic one too. Worked example: the
  VSMode/BtMode merge (`src/game/VSMode_FrameUpdate.c`, 122d9dbc).
- **`global:` renames break `#pragma force_active` (silent dead-strip).**
  `tools/postprocess_extab_user.py` globalizes a `"global:<name>"` symbol with
  llvm-objcopy, which moves it into the global part of `.symtab` but does NOT
  permute MWCC's per-symbol `.comment` records (8 bytes per symbol, flag 0x08 =
  force_active). The flags then sit on the wrong symbols, and a force_active
  static table that nothing references by name (a vtable reached as
  `base + 0x54`) is dead-stripped together with every function only it points
  to: main.dol FAILs with .text/.data shorter, no link error. Fix: define such
  objects as real globals (drop `static`) and remove their `global:` entries.
  Check: compare the `.comment` records (offset 0x2c + 8*symindex) of
  `build/GNLJ82/obj/<tu>.o` and `build/GNLJ82/src/<tu>.o` (DNBress_nm3, 11-09).
  Also make an inline base dtor out of line (`~Base();` + the
  `__dt__...` rename) when the target keeps it as an undefined reference;
  an emitted weak copy gave `internal linker error: ELF_linker.c 1993`.
  (Not always: the merged clCSOrgKartModel TU emits a weak copy of the
  inline base dtor `dtor_8013DCBC` for the ctor's extab cleanups, and the
  link drops it, main.dol OK. Try the plain build first.)
- A weak inline destructor that the compiler emits into a TU may be appended
  to that TU's own `tools/extab_order.json` key; new rename pairs may be
  added inside a TU's own `tools/extab_user_renames.json` key. Do not edit
  other TUs' keys, even to "clean up" (one of our workers did; it was
  reverted).
- **Ctor stores the vtable as `addi rX, anchor, OFF`** (vtable reached
  through the .data section anchor, with base list + vtable sitting right
  before the ctor's jumptable in .data): the TU was built with
  `-inline deferred` and `-RTTI on`. Source rule (mweppc
  `frontend/CParser.c` `CParser_GlobalCleanup`): the class action that
  declares the vtable (`CClass_ClassAction`, queued when the key function is
  defined) runs only at end of file, then the deferred functions are
  generated. Only under deferred codegen is the vtable already declared
  when the ctor is generated, so `GetDataPoolRoot` (`backend/BE_symbol.c`)
  gives it the anchor. Without deferral the ctor is generated during parsing
  and gets `lis/addi __vt__X`. Recipe: write the functions in REVERSE address
  order (deferred emits LIFO), real C++ class with the key virtual dtor
  defined in the TU, base class's vtable external or its dtor inline, add
  `-inline deferred,auto` and `-RTTI on`, and put
  `#pragma readonly_strings on` at the end so the RTTI name strings go to
  .rodata (behind the named strings) instead of in front of the vtable in
  .data. Worked examples: TaMode (`src/game/TaMode_FrameUpdate.cpp`),
  clCSOrgKartModel (`src/game/anon_8021A7C8.cpp`: pure-virtual slots are
  0 in the vtable; string literals in the deferred ctor land after the RTTI
  names, file-scope named arrays before them; owns the RTTI .sdata).
- **Where a weak inline copy lands is TU-boundary evidence.** A weak copy
  that is referenced by address only (an inline destructor named in an extab
  cleanup) is not generated where it is used: it waits on a LIFO export list
  (mweppc `frontend/CInline.c` `cinline_exportlist`, flushed by
  `CParser_GlobalCleanup` -> `CInline_GenerateDeferredFuncs`). Measured with
  toy files on GC/1.3.2: the list is flushed at the next declaration of ANY
  kind that is not a function definition (class/struct/union definition,
  typedef, forward or `extern` declaration, a `static inline` definition,
  `#pragma cplusplus on/off`). Function definitions, `#pragma push/pop`,
  `#pragma exceptions`, `#define`/`#undef` do not flush. With only function
  definitions after the use, the copies come at the very end of the TU, last
  used first. So: a weak dtor several functions after its only user means
  those functions are the same TU as the user and no declaration separates
  them (headers first, then code). Worked example: `dtor_800869D0`
  (`FKTex::~FKTex() {}`) is used by `DrawLinkErrorOverlay` but sits after
  `PCBComm_Init`; merging 24 TUs into `src/game/PCBCheckRecv.c` with every
  C++ declaration hoisted above `DrawLinkErrorOverlay` reproduces it (and
  PCBComm_Init went 96.97 -> 100 from the shared .bss anchor alone).
- Mangled names: map them to the project's names through
  `tools/extab_user_renames.json`, never by editing symbols to mangled names.

## 7. Before you give up on a function

**Diagnose first (since 2026-11-09).** Blind sweeps (pragma x decl order x
permuter, about 1950 rule applications) gave 2 matches; reading the diagnosis
and picking one rewrite gives about 3 an hour. Before the list below, run
`python3 tools/regfix.py diag UNIT FN` (first vreg coloured differently, the
source line, fitting rules; for a diff in the instruction sequence itself the
class of each differing run and its levers, from `tools/shapediag.py`), `python3 tools/mwsched.py explain|coalesce UNIT FN
--run` (order, kept copies) and `python3 tools/asmgrep.py similar UNIT FN
--src` (how matched functions wrote the same shape); the compiler rules are in
`docs/mwcc_internals.md`. First ask whether it is a register problem at all:
a `reloc` / anchor diff is TU or pool ownership (section 5).

Things that solved "only registers/schedule differ" cases on this project,
roughly in the order worth trying:

1. Compiler version per TU (section 4).
2. Literal floats instead of `extern` labels, or the reverse.
3. Declaration order, block-scoped temporaries, `for (int i...)` scope.
4. Inline helpers (`static inline`) for repeated bodies; by-value vs
   `const &` iterators in list code.
5. `if (a || b == X) return;` for `cmpwi; bne body; b end` early returns;
   empty `case N: break;` for an extra switch-tree node.
6. Per-function `#pragma opt_common_subs off` / `opt_propagation off` /
   `opt_dead_assignments off` / `opt_strength_reduction off` (mark fakematch),
   then re-create the one CSE you lost by hand with a named local.
7. Permuter. decomp-permuter works for C TUs; naari3's side also has a text
   permuter for C++ (`tools/helpers/cperm.py`) and a template permuter that
   only keeps variants passing a trace predicate (`tools/tracesweep.py`).
   In practice permuters rarely moved the last register swaps here; new
   source ideas did.
8. Shapes that closed 2-line diffs on 2026-11-08:
   - Loop step order (target bumps the pointer before the count): walk with
     a separate index, `int count = 0, i = 0; while (t[i].name) { i++; count++; }`
     (CollisionFile_Load).
   - Globals used as call arguments but kept in saved registers (target
     `lwz r29,g; mr r4,r29`, ours `lwz r4,g; mr r29,r4`): declare the locals
     without initializers and assign them inside the first call,
     `f(p, cup = g_cupId, round = g_roundIndex)` (AI_CalcGPTargetSpeed).
   - An inline member that returns a class by value (`list->end()`) can make
     MWCC emit the function after the ones that follow it. Build the
     iterator directly instead (`Iter pos(&list->anchor)`, Scene_8014E0C4).
   - A load scheduled across a store in the target (`li r0,N; lwz rX,g;
     stw r0,field`, ours keeps the load after the store) means MWCC knew the
     two could not alias. Write the natural order (store, then the load) and
     give the compiler that knowledge: `__restrict` on the pointer params
     (RankLog_OnMatchEnd), or a `const` view of a global that the TU only
     reads (fn_801FCBCC/fn_801FCD9C; mark the const as fakematch if the
     global is written elsewhere).
   - Byte stores of a shifted word that put `clrlwi`/`extrwi` in a different
     slot: write the mask, `PUT((v >> 8) & 0xFF)` (jvsio fn_80282CDC).

9. Stack slot order (GC/2.6, ItemEffect_Projectile draft, 2026-11-08): local
   aggregates get frame slots in ASCENDING SIZE order, and declaration order
   only breaks ties. So if the target has a 12-byte vector above two 12-byte
   scratch arrays, no declaration order will reproduce it. The vector has to be
   bigger, e.g. 16 bytes with a pad member. Two adjacent int fields copied with
   `lwz,lwz,stw,stw` are one 8-byte struct copy.
10. More shapes, with commits: `docs/regalloc_patterns.md` (numbered fixes
    §1..§43 plus the onmokoworks Codex fixes; §18 onwards are from
    2026-11-09 and each names its rule in `tools/patterns/rules.jsonl`).
    `python3 tools/leversweep.py fn UNIT FN --show` tries the hand levers of
    that day whose trigger fits the diff. Functions others already
    tried, with their best % and WIP location: `docs/gave_up.md`.

When you stop, record the function in `docs/gave_up.md` with the current %,
the remaining diff in one line, and where the WIP lives, so the next person
starts from there instead of from zero.
