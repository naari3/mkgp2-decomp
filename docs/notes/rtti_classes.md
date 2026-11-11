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
