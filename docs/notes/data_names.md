# Provisional data symbol names: tools/data_names.py

Goal (naari3, 2026-11-10, for the PC port): data symbols should say who owns
them. Until 2026-11-10 only about 970 of 32,250 data objects in
`config/GNLJ82/symbols.txt` had a name; the rest were `lbl_<ADDR>`.

`python3 tools/data_names.py apply` (right after a build, since it reads
the disassembly under `build/GNLJ82/asm`) names every `lbl_` object it can
from its users, keeping the address:

| Users | Name |
|---|---|
| vtable / RTTI a TU maps a class to (extab_user_renames.json) | `<Class>_vtable_<ADDR>`, `<Class>_RTTI_<ADDR>` |
| one named function | `<Function>_<kind>_<ADDR>` |
| methods of one class only | `<Class>_<kind>_<ADDR>` |
| functions of one unit (unit has a real name) | `<Unit>_<kind>_<ADDR>` |
| only a named data object points to it | `<Object>_<kind>_<ADDR>` (repeat until 0) |

`kind` is `data` (.data/.sdata), `bss` (.bss/.sbss) or `rodata`. These are
provisional: rename freely to a real name once you know what the object is
(rename the word everywhere, as `apply` does). Not named on purpose:
strings, .sdata2/.sbss2 (float literals), compiler literal pools (`@N`
targets), objects used only by unnamed `fn_` functions or several unrelated
functions. `python3 tools/data_names.py census` writes the counts to
docs/reports/data_names.md.

A rename touches `symbols.txt` and replaces the whole word in every tracked
file (sources, inline asm, extab_user_renames.json, docs) except the
append-only board. main.dol and the report do not change.

Work in flight that still uses an old `lbl_` name: after rebasing, run
`python3 tools/data_names.py fixup` (rewrites old names, from
tools/data_names_map.tsv, in files that differ from origin/main and in
untracked files) or `fixup FILE...`.

Do not use the mangled `__vt__...` name for a vtable symbol: a TU that emits
its own weak copy of that vtable then defines it twice (link error).

## Names chosen by reading the users (2026-11-10)

`tools/data_names_manual.tsv` (old, new, why) holds names a person picked
after reading every user of the object: globals as `g_<what>` (the existing
convention, e.g. `g_itemObjectManager`, `g_itemClassTable`), vtables as
`<Class>_vtable_<ADDR>`. `python3 tools/data_names.py apply --manual` applies
the lines whose old name still exists; a plain `apply` afterwards names what
those objects point to. Add a line, do not rename by hand, so the map
(`data_names_map.tsv`, used by `fixup`) stays complete.

Where the candidates are: `python3 tools/data_names.py plan` prints nothing
for them, so list the `lbl_` objects whose users are all named functions in
more than one unit (about 85 left) and read the users; objects used only by
`fn_` functions need the function named first.

The "one unit" rule no longer takes the name of a data-only unit
(`src/game/autodata/data_804EEFE4.c` would have produced
`data_804EEFE4_data_806D09B0` for about 1,760 objects).
