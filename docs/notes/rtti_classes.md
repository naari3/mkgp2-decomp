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

## What a real class needs (measured on clScreenEffect)

The table says where each class really lives. For `clScreenEffect`:

- its destructor is `TransitionEffect_Dtor` (unit `TransitionEffect_Dtor.cpp`),
  the first function of the original file; the rest of that file is
  `TransitionEffect.cpp`, which ends with the weak destructors of its member
  templates and of `teSingleton<clScreenEffect>`;
- `.data` of the original file runs from the vertex tables through the base
  list, the vtable, two jump tables and the weak `teSingleton<clScreenEffect>`
  table (0x803FDF28..0x803FE3D0, today three units);
- the two class-name strings and `"warp.dat"` are consecutive in `.rodata`.

So letting MWCC emit this one table means: merge two units, own their data
and strings, switch the unit to `-RTTI on`, write the class, its template
base and its members as real C++ (constructors and destructors are C
functions with a hand-stored table and a flag parameter today), and
renumber the unit's `@NNN` rows in `extab_user_renames.json`. That is the
size of one hard matching job per class, not a mechanical edit.
