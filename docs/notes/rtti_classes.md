# The original classes, from RTTI

Written 2026-11-10 for "turn hand-written vtables into real classes"
(mkgp2-pc `docs/port/cxx_abi_decision.md`).

The game was built with `-RTTI on`, so main.dol still says what its
polymorphic classes are called and what they derive from. For every such
class MWCC leaves:

| object | layout | where |
| --- | --- | --- |
| record | `{ const char *name; void *baseList; }` (base list 0 without bases) | `.sdata` (8 bytes) |
| base list | `{ record, offset }` per ancestor, then `0` | `.data`, just before the vtable |
| vtable | `{ record, offset to top, slot 0, slot 1, ... }` | `.data` |

A class with two bases has its secondary tables right after the primary one
in the same object (`{ record, -offset, slots }`). Pure virtual slots are 0.
A class defined entirely in a header gets one table per unit that needs it
(for example `clJobRunner`, 8 copies).

`python3 tools/rtti_classes.py` reads all of it (from `orig/.../main.dol`, or
from the committed `docs/notes/rtti_classes.tsv` when there is no dol) and
prints one row per vtable: real class name, ancestors, the symbol the table
has today, the unit its data is in, the functions in its slots.
`--class clScreenEffect` shows one class with its slots; `--tsv` regenerates
the table.

Numbers on 2026-11-10: **416 vtables, 388 class names**, 353 of the tables
written by hand in `src/game/autodata`. Only 62 symbols carry the real class
name: `TripletFaderOwner_vtable_804EECDC` is `clRnkDisp : clCDispInterface`,
`TransitionEffect_data_803FE37C` is `clScreenEffect :
teSingleton<clScreenEffect>`. The sources use 445 invented class names for
these (`tools/extab_user_renames.json`, `__vt__` rows). The common ancestors
are `clYTaskInterface` (47 classes), `clSceneInterface` (35), `clJobRunner`
(30), `clMapEffectParts` (26), `clMnTaskInterface` (26).

`tools/port_readiness.py` reports "Vtables written out by hand as data" and
"Vtables whose symbol carries the real class name" from the same data.

## Turning one hand-written vtable into a real class: clScreenEffect

Done 2026-11-10 (`src/game/TransitionEffect.cpp`), main.dol unchanged. It took
about 35 minutes and 22 compiles, most of them spent finding the rules below;
with the rules known the next class of this shape should be much quicker.

What the RTTI table said: `TransitionEffect_data_803FE37C` is the vtable of
`clScreenEffect : teSingleton<clScreenEffect>`, its only slot is the
destructor `TransitionEffect_Dtor`, which was a unit of its own in front of
`TransitionEffect.cpp`; the weak table of the template base sits after that
unit's jump tables, and the two class-name strings sit just before its
`"warp.dat"` literal.

Steps:

1. Merge the destructor's unit into the unit that follows it (splits.txt,
   configure.py, extab_user_renames.json).
2. Take the class data out of the data-only units with
   `python3 tools/autodata_carve.py SEC LO HI` (base list + vtable, the weak
   base vtable, the two RTTI records in `.sdata`, the name strings in
   `.rodata`) and add the ranges to the unit. String literals that follow
   the names up to the next 8-byte boundary have to come along, written as
   literals in the code.
3. Write the classes: `template <class T> struct teSingleton { teSingleton();
   virtual ~teSingleton(); }`, `class clScreenEffect : public
   teSingleton<clScreenEffect>` with its members as member objects, an inline
   constructor and `virtual ~clScreenEffect();` defined in the unit.
4. Flags: `-RTTI on -rostr -inline deferred,auto`.
5. Renames for `__dt__`, `__vt__`, `__RTTI__` and the `@N` data labels, then
   `python3 tools/extab_renumber.py <unit> --write`.

Rules found on the way (GC/1.3.2):

- **Data order tells the mode.** Without `-inline deferred` the compiler emits
  vtables, base lists and RTTI names at the very end of the unit, after all
  jump tables, in every compiler version. With it they come first. A base
  list and vtable in front of the unit's jump tables therefore means
  deferred code generation (the same sign as matching_rules section 6).
- **Deferred means reverse source order** for ordinary functions, and an
  inline function that is needed out of line (here: member destructors named
  in exception tables) is emitted right after the function that first needs
  it. Explicit instantiation, defining the destructors out of class, or an
  earlier unused user of them does not move them.
- In the target those ten destructors are the last functions of the unit, in
  destruction order. The only arrangement found that gives this is to make
  them ordinary functions at the top of the file (explicit specializations,
  marked fakematch) and let `-inline deferred,auto` inline them into
  `~clScreenEffect`. `auto` then also wants to inline a large function into
  its caller; `#pragma dont_inline on` around that callee stops it.
- `delete p` of a class with a destructor has its own null check;
  `if (p != 0) delete p` adds a second one (4 bytes).
- Under `-RTTI on` the unit owns the RTTI records of every class it emits,
  and the linker keeps one copy of a weak table per unit that needs it.

### Second class: clMenuInput (4 minutes, 2 compiles)

`src/game/clMenuInput.cpp` replaces four one-function units and the first
function of a fifth. Differences from clScreenEffect:

- **Not deferred.** The data order is weak base vtable, base list, vtable,
  and the functions are in source order with the weak base destructor last,
  which is what the compiler does without `-inline deferred`. So the mode is
  per unit; read it from the data order before starting.
- `OpenFullServiceMenu` had a hand-written exception table to imitate an
  allocation that is freed when the constructor throws. As
  `new ServiceMenu(-1)` the compiler writes that table itself.
- Where the unit ends: the weak destructor of `teSingleton<X>` is the last
  function of X's file (slot 0 of the `teSingleton<X>` vtable in
  `rtti_classes.py`), so the file runs from X's own destructor to there.
  For the ten singleton classes this gives 1 to 5 of today's units each.

### Third class: clLineManager (about 50 minutes, 30 compiles)

`src/game/clLineManager.cpp` replaces `CourseData_LoadPathTable.cpp` (the
constructor), `CourseData_Lookup.c` and two data-only units. Deferred mode
again (data order base list, vtable, weak base vtable). New rules:

- **Under deferred mode the file does not start at the class destructor.**
  The constructor sits before it in the binary, so it is later in the
  source; look at the function before the destructor too.
- **String literals are pooled in the order the functions are generated**,
  i.e. from the last function of the source backwards, and inside one
  function in the order of the generated code. Static `const char x[]`
  arrays come before the RTTI name strings, literals after them, so the
  place of the class-name strings in `.rodata` tells which of the two the
  original used.
- **A function the linker dropped can still be seen in the pool.** The
  target has "line %08x" and the member-count text before the two load
  messages, although the constructor uses them after. No arrangement of the
  inline loaders gives that (ten tried: helper first or last, member or
  static, in-class body, default arguments, locals, `-str` flags). A member
  function nobody calls, defined after the constructor, does: it is
  generated first, puts its literals first, and mwld strips its code and
  exception table. `clLineManager::PrintLines` is that function, body
  guessed, marked in the source.
- **Exception table order is not function order.** The target has the weak
  base destructor's entry right after the constructor's (where the compiler
  generates an inline destructor the constructor needs) while its code is
  last. The explicit specialization gives the code order;
  `tools/extab_order.json` declares the table order.
- **The unit's `.data` must start where the original file's did.** The
  class data starts at 0x80419DA4, not 8-aligned, because the built-in path
  table (0x7C4C bytes) of the same file comes first. The table moved into
  the unit (`include/game/clLineManager_kp_castle_short_line.inc`).
- `-rostr` literals replaced the named format arrays and the separate
  "create line manager" unit.

### Fourth class: clDrawManager (about 15 minutes, 3 compiles)

`src/game/clDrawManager.cpp` replaces five units (`clDrawMan.cpp`, the
destructor, two array-element destructors, the node constructors) and
`include/game/clDrawMan_private.h`, which already had the class almost
written. Went straight through with the rules above:

- The data order (base list, vtable, weak base vtable) was again the
  deferred one; the same source without `-inline deferred` gives weak base
  vtable first, also when the destructor is the first function. **So far:
  base vtable first = not deferred, base list first = deferred.**
- Deferred, so the source is in reverse address order, the destructor last.
- The element destructors and constructors (`DrawNode`, `DrawBucket`) are
  plain out-of-line definitions; `delete[]` of a class with a destructor is
  the `__destroy_new_array` call the old C file spelled by hand.
- The weak `ScopedTimer` destructor lands in the middle of the object and
  the linker drops it, as before.

### Fifth: clTPLLoad / clTPLexp, parked after 75 minutes

Code, vtables, RTTI and strings match as one deferred unit, but mwld puts
the constructor's exception table entry 4 bytes late and the cause was not
found. Draft, findings and every test: `docs/wip/real_classes/clTPLLoad.md`.
Two rules from it that hold in general:

- MWCC puts the vtable pointer where the first virtual function is
  declared, so declare the virtual destructor before the data members of a
  class without bases (also what other ABIs expect).
- A member that the constructor stores before it stores the class's own
  vtable pointer belongs to the base class.

### Rules for every converted class

- **Check with clang before landing**; compiling off MWCC is the point.
  `clang -target i686-pc-linux-gnu -fsyntax-only -nostdinc -x c++
  -std=gnu++98` with the include paths and `-include mwcc_compat.h` of
  mkgp2-pc `port/tools/compile_census.py`. First catch: an explicit
  specialization has to be declared before the class that uses it
  (`template <> teSingleton<X>::~teSingleton();` ahead of `class X`), the
  definition can stay where the order needs it.
- **Base class tail padding** (from the port, mkgp2-pc
  `docs/port/cxx_classes.md`): the Itanium ABI puts the first members of a
  derived class into the tail padding of a non-POD base, MWCC does not. A
  base whose last member leaves padding (a `char` after an `int`, say) must
  spell the padding as a member (`unsigned char pad[3];`), as clScreenEffect
  does with `align[2]`, so both compilers lay the derived class out alike.

### Working notes for whoever converts the next ones

Order of work that avoided rework in the five tries:

1. `python3 tools/rtti_classes.py --class NAME` for the class and each base;
   list the units between the first and the last function of the file.
   Skip, for now, a class with a slot function in a NonMatching unit (the
   build links the original object there, so nothing is verified) and a
   file whose units need different compiler versions (clItemBoxManager:
   GC/1.3.2 and GC/2.0 pieces).
2. Write the merged unit, remove the old ones from `configure.py` and
   `splits.txt`. Edit only the `Object(...)` line of your unit: a `sed`
   over flag strings twice changed other units' lines. Check with
   `git diff configure.py`.
3. `python3 tools/autodata_carve.py SEC LO HI` for the vtables, base lists,
   RTTI records and name strings, **before** adding those ranges to the new
   unit in `splits.txt`. When another commit has retyped the same data unit
   in between, redo the carve on the new version instead of merging by hand.
4. `tools/extab_user_renames.json`: one block per unit, edited as text
   (never `json.dump`: duplicate keys). Mangled names of the class
   (`__dt__13clDrawManagerFv`, `__vt__...`, `__RTTI__...`; the number is the
   length of the name, templates count whole, e.g.
   `28teSingleton<13clDrawManager>`) map to the symbols.txt names. Drop all
   `@N` keys of the old units, build the object, read the new `@N` of the
   strings and base list with `objdump -t`, add them, then
   `python3 tools/extab_renumber.py <src> --write`.
5. Compare the object's symbol order (`nm -n`) with the target before
   linking; a link takes minutes, a compile seconds. Text order, `.data`
   order, `.rodata` order and extab order are four separate things to get
   right, in that order of difficulty.
6. `rm -f build/GNLJ82/main.dol && ninja` must print `main.dol: OK` and the
   function count must not drop; `tools/nonmatching_check.py`; clang check;
   regenerate `docs/notes/rtti_classes.tsv` (`rtti_classes.py --tsv`); one
   line in matching_rules.md section 0 and one board note per landing.

Things that are easy to get wrong:

- `main.dol: OK` only checks units marked `Matching` in configure.py. For
  a `NonMatching` unit the original object is linked, whatever the source
  says. clScreenEffect landed that way; linked from source its exception
  table order was wrong. Flip the unit to `Matching` for the check, or
  leave the class alone until the unit matches.

- A weak table of a header-only base (`clMapEffectParts`, the interface
  classes) is emitted by every unit that needs it and the linker keeps one
  copy per unit in this binary, so the same class has several vtable rows
  in the tsv. Each belongs to the unit whose data it sits in; do not try to
  merge them into one.
- A function that is in the object but not in the target (weak
  `ScopedTimer` destructor, an uncalled member) is fine as long as mwld
  drops it; check the linked addresses, not the object size.
- The unit's first `.data` object must be where the original file's was.
  If the vtable is not 8-aligned, data of the same file precedes it and has
  to move into the unit too.
- Other units that name the vtable symbol (`extern void *X_vtable[]`,
  stores of the vptr by hand in constructors written as C) keep linking,
  because the symbol name is kept by the rename; converting those
  constructors is part of the same class and should go in the same unit.
- Open problem: mwld put one exception table entry 4 bytes late
  (clTPLLoad, `docs/wip/real_classes/clTPLLoad.md`). If you see a 4-byte
  shift that starts in extab, compare with that note before spending time.

What this says about the other 345: each needs the unit that holds the
class's first non-inline virtual function to own the class data, which often
means merging units first, and the constructors and destructors written as
real ones. That is matching-grade work per class, helped by the table but
not mechanical.

## r1_c8_20261111
Source: Codex worker r1_c8_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Added working-note paragraph on vtable symbol sizes including inter-unit alignment, lens successful size correction and camera following-unit alignment blocker.

## r2_c11_20261111
Source: Codex worker r2_c11_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clMRAirShip converted in game/objview/fn_801869F8.cpp: four source units merged, deferred reverse definitions, canonical clMapEffectParts base, compiler RTTI and vtable 80495BBC, SHA-1 unchanged. A Vec3f snapshot uses copy initialization before declaring its delta local to preserve the original integer copy and stack layout; assigning the same POD later in C++ instead emitted scalar FP loads/stores. Assertion helpers use literals so strings pool after compiler RTTI names. No new general compiler rule was traced.

## r2_c17_20261111
Source: Codex worker r2_c17_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clRBSatellite is a small deferred clMapEffectParts descendant: ctor, dtor, Update definitions in reverse target order emit all owned text/data/RTTI exactly. Its vtable symbol included four bytes of inter-unit alignment; correct size is 0x18. Existing ctor-only bridge for fn_8018E510.cpp hard-codes the TU filename, so this conversion retains that path as the merged owner without editing build logic.

## r3_c7_20261111
Source: Codex worker r3_c7_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

When expanding a converted TU backwards from an existing 4-aligned jump-table section to its 8-aligned class data, remove its obsolete DATA_ALIGN4_TUS opt-in. clMnCardT02 changed .data start 804EC044 -> 804EBFF0; retaining the override left the compiler vtable four bytes early despite 100% object comparisons. Restoring default MWLD alignment gave the exact DOL.

## r3_c20_20261111
Source: Codex worker r3_c20_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clRsContinueTaskBT converted in game/BattleContinueScene.cpp using canonical clMnCardClasses.h bases, deferred reverse definitions and explicit VHolder<Panel> dtor specialization; compiler vtable 804EF054, base lists, RTTI and name pool exact, clang OK, main.dol SHA1 unchanged. No new compiler rule found.

## r3_c21_20261111
Source: Codex worker r3_c21_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clStartNum/clStartGo: deferred reverse function definitions plus -inline deferred,noauto preserve the out-of-line clStartGo constructor (auto would inline it into the factory). Existing reorder_extab declarations match the complete function-name set exactly; preserve the legacy weak-base-destructor bridge when renaming the real base class, otherwise the reorder silently does not apply. Six owned sections and all 15 functions match; full DOL SHA-1 unchanged.

## r4_c2_20261111
Source: Codex worker r4_c2_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clCSSceneCardBrowse converted in game/SceneList_80157EA8.cpp, merging game/Scene_8015B698.cpp. Deferred reverse definitions and direct member Update/Draw preserve 13 native functions; compiler vtable 8049003C, base list, RTTI/name pool exact. Uncalled marked diagnostic member preserves the final clCSPartsInerface pooled string, following clLineManager precedent. Canonical clSceneInterface explicitly spells its three tail-padding bytes. Clang OK; coordinator full DOL SHA-1 unchanged. No new general compiler rule traced.

## r4_c17_20261111
Source: Codex worker r4_c17_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clResultType01 (HudResultFlow.cpp) is a deferred multiple-inheritance case. A public clSceneInterface ancestor and a private 8-byte polymorphic list-owner base reproduce its primary/secondary table layout without adding a list-owner RTTI record. Inherited clResultInterface ctor/dtor/Update/Draw can stay external under per-TU bridges. Reverse definitions emit all six functions, including the secondary destructor thunk, exactly; existing EH ordering remains valid. Remove the old DATA_ALIGN4_TUS opt-in when expanding the jump-table-only range backwards to 8-aligned class data. These are object/full-link observations, not a compiler-source trace.

## r6_c12_20261111
Source: Codex worker r6_c12_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clTitleDisp2 converted in game/TitleNameHudUpdate.cpp: five code units merged, canonical clCDispInterface base unchanged, deferred/noauto reverse definitions and compiler RTTI/vtable 804F202C. Eight functions/2252 bytes and all six owned sections 100%; clang OK and full DOL SHA-1 unchanged. Removed obsolete DATA_ALIGN4_TUS entry when extending the jump-table range backward to 8-aligned class data. This follows existing clMnCardT02/clResultType01 rules; no new compiler rule.

## r6_c29_20261111
Source: Codex worker r6_c29_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

r6_c29 yes/no family observation: shared interleaved RTTI lists require family-level data ownership, but keeping the public service tail as a separate TU avoids deferred/auto factory inlining without new function pragmas. Compiler RTTI may need global: bridges when a retained external-view tail references legacy aliases. The original force_active autodata pool included eleven otherwise unreferenced real format/helper-name strings; an approved uncalled pool-order member emits them, and existing active: data renames preserve their retention. All six owned sections, 40 linked functions and DOL SHA-1 verified exact. These are object/full-link observations, not a compiler-source trace.

## r7_c4_20261111
Source: Codex worker r7_c4_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clCallback/clShadow: preserve the standalone base destructor TU separately from the derived shadow TU, because the binary has two distinct clCallback RTTI/name copies. clShadow data starts with a base list, so its methods use deferred generation/reverse definitions while clCallback remains nondeferred. Vtable size 0x14 included four alignment bytes; actual clShadow table is 0x10. Both real-class TUs and all 7 functions match, clang OK, full DOL SHA1 unchanged. Observations follow existing rules, not a new compiler-source trace.

## r7_c9_20261111
Source: Codex worker r7_c9_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

nsEffectSpeed::clActionMueScale/clAction/clActionSpeedScale converted together in game/EffectSpeedAction_SpeedScale_Dtor.cpp (four code TUs merged). Deferred reverse definitions retain all 14 functions / 1968 B. Declaring MueScale::Reset first and SpeedScale::Process first chooses vtable keys whose generation reproduces MueScale/base/SpeedScale data order; RTTI names and sdata then match too. Last vtable symbol size corrected 0x18 -> 0x14, excluding 4-byte inter-unit alignment. All six owned sections, clang, 25 linked symbol addresses and full DOL SHA-1 verified. This is an object/full-link observation, not a compiler-source trace.

## r7_c11_20261111
Source: Codex worker r7_c11_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clGameSingle converted in game/RaceScene_RenderPass.cpp, merging FrameUpdate/Dtor/Init. Deferred reverse definitions plus compiler RTTI/vtable and pooled literal strings preserve all four native methods and seven owned sections at 100%; clang OK and full DOL SHA-1 unchanged. Split the old compound string-pool symbol into actual literal boundaries to eliminate R_PPC_NONE pseudo-relocation mismatches (existing matching_rules section 5 rule). No new compiler rule discovered.

## r7_c13_20261111
Source: Codex worker r7_c13_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clSeqEnding/clStageSelect/clTitle share one nondeferred TU: ordinary address-order definitions preserve all 12 functions, and the compiler emits class data SeqEnding/StageSelect/Title in reverse at the end. Base-list-first alone cannot distinguish deferred mode when the external canonical base emits no weak vtable in the TU. Deferred reverse definitions matched text but reversed all class data; all-inline deferred recovered data but moved methods after factories. Keep debug-label strings external here so compiler RTTI names alone occupy 80328D90..80328DB8. Existing #align4 .sdata2 directive handles short clTitle name at 806D4F34. Object/full-link observations, not a traced general compiler rule. Full DOL exact.

## r7_c18_20261111
Source: Codex worker r7_c18_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clCGameDemoRB converted in game/ChallengeDemoUra.cpp with canonical clCGameDemo/clJobRunner, deferred,noauto reverse definitions and -rostr. Existing bridges remained valid. Four functions/2348 B and all six owned sections exact, clang OK, full DOL SHA-1 unchanged. No new compiler rule.

## r7_c20_20261111
Source: Codex worker r7_c20_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clCSKartModel converted in game/KartPreview.c without merging PreviewModel.c: inline base dtor plus external base Draw preserves the existing base table, while global: on the compiler-emitted base RTTI lets the untouched table reference it. Deferred reverse definitions and pooled ctor literals retain text/string order. All 12 methods and six sections 100%; DATA_ALIGN4_WEAK_TUS for 8048EACC start, clang OK, full DOL SHA-1 unchanged. Uses existing rules; no new compiler-source rule.

## r7_c24_20261111
Source: Codex worker r7_c24_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Added the requested working-note paragraph tracing the raw/processed symbol-index and .comment misassociation caused by unnecessary global: bridges. Does not claim every previous parked gap has the same cause. This docs edit follows the explicit real-class-lane new-rule instruction.

## r7_c22_20261111
Source: Codex worker r7_c22_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Added object/link observation on shared TA/Ghost RTTI-name pooling via approved uncalled diagnostic member; not a compiler-source trace.

## r7_c44_20261111
Source: Codex worker r7_c44_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clEnemyFace/clEFace3D converted in EnemyFace_exact2.cpp + EnemyFace_nm4.cpp: four assigned EnemyFace units merged into exact2, deferred/noauto reverse definitions, canonical clCDispInterface unchanged. Existing extern: RTTI-name bridges retain names in the unassigned renderer pool; no need to absorb EnemyFace.cpp/exact5. Both vtables and owned RTTI/base-list compiler emitted; all ten functions/2960 B and five owned sections per TU 100%, clang OK, DOL SHA-1 exact. DATA_ALIGN4_TUS on nm4 preserves 804EE134. Existing-mechanism observation, no new compiler-source rule.

## r7_c47_20261111
Source: Codex worker r7_c47_20261111 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clMnCardRenew: if carving all ancestor names would leave an 8-aligned autodata tail at 803EF454, the existing extern: string rename mechanism can leave the ancestor names in autodata and carve only the derived name (803EF408..418). Tail 803EF418 is 8 aligned; compiler still emits all RTTI records/base lists and the derived vtable. DATA_ALIGN4_TUS only pins .data and does not fix a .rodata tail. All sections, ten functions and full DOL SHA-1 exact.

## r8_c9_20261112
Source: Codex worker r8_c9_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clCGameDK can convert independently of CoinBase/DKCoin in the same code TU: keep nondeferred address-order definitions and the old Coin aliases, and own only .data 8048E318..34C / .sdata 806CF548..560. Approved uncalled PrintTypeNames pools the DK/JobRunner names at the original position; compiler RTTI reuses the literal strings. Exact pool symbol boundaries remove pseudo-relocation mismatches. All seven methods/EH/data and full source-linked DOL verified. Existing mechanisms, not a compiler-source rule.

## r8_c14_20261112
Source: Codex worker r8_c14_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clCSSceneNextRace converted using existing mechanisms: own name pool at 80369684 needs #align4 .rodata in its bridge, while autodata tail 803696AC independently needs align4.txt. Own six sections and six functions 100%, exact linked addresses and full DOL SHA-1 verified. This is an object/link observation; no new compiler-source rule.

## r8_c11_20261112
Source: Codex worker r8_c11_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

r8_c11: clCSPartsPlatform converts in PodiumPose.c without merging the surrounding CSParts units. As already observed for r7_c13, base-list-first is not proof of deferred mode when the canonical base vtable is external: nondeferred ordinary source order preserves the existing eager PoseChar asm ctor. An approved marked uncalled diagnostic member pools RTTI names before ceremony/trpy/flower filenames. Split the existing 80360B81 padding+pointer-table symbol at 80360B84 and the resource filename pool at 80360C44/54/64; this removes synthetic R_PPC_NONE objdiff mismatches. Six sections, ten retained functions, clang and full source-linked SHA-1 exact. This is an application of existing rules and object/link evidence, not a new compiler-source trace.

## r8_c16_20261112
Source: Codex worker r8_c16_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

r8_c16 observation: clKPCharaData_MKoopa and NokoPata can convert independently of their base table by leaving CoursePropCtor.cpp separate (RTTI off), merging append+MKoopa Update, and retaining NokoPata Update separately. Existing extern: bridges reuse the original base RTTI/name. DATA_ALIGN4_TUS dropped .comment and kept +32-byte duplicate pools; existing #align4 on .rodata,.data preserves symbol chunk information and gives an exact full DOL. This is an object/link observation, not a compiler-source rule.

## r8_c17_20261112
Source: Codex worker r8_c17_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clMiyazaki uses the approved uncalled diagnostic member to emit its trailing labels. A TU already in DATA_ALIGN4_TUS must move to DATA_ALIGN4_WEAK_TUS when it needs MWLD dead stripping: the ordinary alignment hook removes .comment and therefore retains the otherwise unused diagnostic and EH. The keep-comment hook restored the original DOL. This follows the existing hooks, not a newly traced compiler rule.

## r8_c28_20261112
Source: Codex worker r8_c28_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

clRsCardT1 converts without merging the nondeferred setup and deferred transition TUs: declare Finish first so its existing definition in SceneRoleTransitions selects the vtable key owner, ahead of the continue-family data. Canonical shared class/header, existing extern ancestor bridges and DATA_ALIGN4_WEAK_TUS preserve 35 primary functions, owned sections, exact linked addresses and full DOL SHA-1. Existing-mechanism object/link observation, not a new compiler-source rule.

## r9_c4_20261112
Source: Codex worker r9_c4_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RULE (GC/2.7, clAreaData family): vtable order follows the LIFO class-action queue, not class declaration or destructor-body order. CDecl_SetupClassLayout selects the first lexically declared non-inline, non-pure virtual as the key; CClass_MemberDef queues its class when that key is defined. Without a key, CClass_MakeStaticActionClass installs a lazy vtable callback, queued by CInline_ObjectAddrRef on the first generated address reference. CParser_NewClassAction prepends, and CParser_GlobalCleanup(TRUE) emits one class then drains inline exports before the next class. In a simple non-template class, CScope list insertion, CClass_BuildOVClassTree, vtable relocation-list construction and CInline_ObjectAddrRef reverse the lists in succession, so otherwise-unreferenced inline virtual copies follow their declaration order, independent of body-definition order. Probes: all keyed area classes emit Simple/Exact/base; making both Simple virtuals inline gives Exact/Simple/base; swapping only their definitions does not change Contains/dtor order, while declaring the inline dtor first gives dtor/Contains. The matching source keeps base Contains and Exact Contains as keys, makes Simple keyless with dtor declared before Contains, uses Vec3* throughout, and splits the already-matched clAttract tail at 80123F34 so its later key cannot precede the area actions. All 24 functions, EH and data remain 100%, and the source-linked DOL SHA-1 is unchanged.

## r9_c6_20261112
Source: Codex worker r9_c6_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Nondeferred weak-copy exports are flushed by the normal CParser_ParseDeclaration default path even after ordinary function definitions. A single extern C or extern C++ declaration goes through CParser_ParseLinkageSpecification -> scandeclaratorlist and bypasses that cleanup; a brace linkage block does not. CInline_ObjectAddrRef pushes inline bodies onto a LIFO export list, drained after pending actions by CInline_GenerateDeferredFuncs. CInline_CheckDependencies can defer even a nondeferred enclosing constructor for implicit special-member generation. Explicit empty inline base construction, single-declaration C++ linkage on the two member definitions, ordinary final-factory cleanup, and a late inline list ctor reproduce the exact target order. See the directly appended working-note paragraph and pinned compiler-source citations.

## r9_c5_20261112
Source: Codex worker r9_c5_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

RULE (r9_c5, GC/1.3.2 verified; compiler-source model at pinned mweppc 919828d): vtable order is the class-action stack, not a universal base-first/deferred test. [CClass_MemberDef](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CClass.c#L1940) queues a key-function class when its definition is parsed; [CParser_NewClassAction/GlobalCleanup](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CParser.c#L3666) prepend/pop this stack, while inline-base vtables queue lazily through CInline_ObjectAddrRef callbacks. Ordinary deferred code uses a separate reverse-definition export list ([CInline_GenFunc/GenerateDeferredFuncs](https://github.com/doldecomp/mweppc/blob/919828d97d33d236da675824d43c5d57332afe74/src/compiler/frontend/CInline.c#L4375)). For DK/Coin, -inline deferred,noauto, ordinary methods in reverse target order, a non-inline DKCoin destructor and an inline CoinBase destructor give .data DK lists/vtable -> CoinBase weak vtable -> DKCoin list/vtable. The early weak destructor body is harmless because the existing strong native dtor_8012A5AC bridge remains separate and MWLD discards the copies. Names can be placed independently: the CRTTI dynamic_cast parser calls ConstructTypeInfoObject immediately, allocating the name before its recursive ancestor records/base lists. The approved marked uncalled CheckType member after icon positions seeds DK/JobRunner/clCGame names; explicit real log-string arrays then filenames follow; a second CheckType after filenames seeds CoinBase; DKCoin names/list arrive with its later class action. Reproduction: build/r9_c5_probe/order*.cpp separates declarations, key definitions and inline/deferred mode; Noko_probe.cpp has the right table order but wrong name pool; Noko_rtti_probe.cpp fixes pooling; Noko_members_probe.cpp removes the unnecessary local self and makes all seven native methods 100%. Final production owner is game/NokoNoko_801287F8.cpp; all 14 touched-TU methods, owned EH/data and full source-linked DOL verified, SHA-1 ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65. No new function pragma, table payload, or filler was used.

## r9_c5_20261112
Source: Codex worker r9_c5_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

r9_c5 metadata observation (existing r7_c24 mechanism, not a new compiler rule): the first full link had exact class/text addresses but extab grew 32 B. Raw ctor @730 had .comment symbol index 37/alignment 4; after extern: globalization/llvm-objcopy it was @etb_8000C484 at index 36 reading alignment 8 and linked at 8000C488 instead of 8000C484. Carving the genuine clCGame name .sdata2 806D7040..806D7048 into its owner and using a plain rename removes that needless global/undefined transition; processed ctor alignment returns to 4 and the final DOL is exact. Do not generalize this diagnosis to every old clTPLLoad park without its raw/processed-index evidence.

## r9_c5_20261112
Source: Codex worker r9_c5_20261112 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

r9_c5 RTTI inventory correction: 8048E3B4 is NOT a second clCGameCoinBase vtable. Its words are {806CF5B4,0,0}; the real clCGameKPCoin RTTI record at 806CF5BC is {80356FE0,8048E3B4}, so it is that derived class's base list. symbols.txt gives the latter record size 0xC (8-byte record plus four alignment bytes); tools/rtti_classes.py collect() only accepts z==8, misses clCGameKPCoin and consequently mislabels its base list as a zero-slot CoinBase table. Actual KPCoin vtable is 8048E3C0. No tool, symbol-size or unassigned KPCoin range was edited. This removes the packet's supposed second-CoinBase-table/asm dependency; the sole actual CoinBase table 8048E34C is now compiler emitted.
