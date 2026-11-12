# Source restoration numbers

Written 2026-11-12. The Pages site has two pages:

| Page | Says | Made by |
| --- | --- | --- |
| [index.html](https://naari3.github.io/mkgp2-decomp/) "Matching" | the compiled bytes are the original ones | `tools/gen_progress_page.py` from `report.json` |
| [restoration.html](https://naari3.github.io/mkgp2-decomp/restoration.html) "Source restoration" | how far the sources are from the form the game was written in | `tools/gen_restoration_page.py` from `tools/restoration.py` |

The matched percentage does not move when a hand-written vtable becomes a
class, a struct gets one definition or a function gets a name. The second
page is where that work shows.

```
python3 tools/restoration.py              # table, about 5 s, no build needed
python3 tools/restoration.py --json       # everything, with one row per vtable
python3 tools/restoration.py --summary    # the flat numbers of one history row
python3 tools/gen_restoration_page.py --out-dir site   # the page alone
```

## What is counted

Everything is read from tracked files (`src/game`, `include/game`,
`config/GNLJ82/symbols.txt` and `splits.txt`, `tools/extab_user_renames.json`)
plus the RTTI of the original program (`tools/rtti_classes.py`: main.dol, or
the committed `docs/notes/rtti_classes.tsv` when there is no dol).

| Number | History key | How |
| --- | --- | --- |
| Vtables emitted by the compiler | `vt_real` / `vt_total` | One row per vtable the RTTI names. **hand** when the table sits in a data-only unit (`src/game/autodata`), in no unit, or is an initialised array in a normal unit (`Foo_vtable[] = {`, `__vt__3Foo[] = {`). Otherwise the compiler emits it from a class definition: **real**. |
| ... with the original name | `vt_named` | A real table whose `__vt__` name in `extab_user_renames.json` (or whose symbol) carries the class name the RTTI record gives. The rest are real classes under an invented name. |
| Type names with one definition | `type_names`, `type_dup_names`, `type_extra_copies` | `struct` / `union` / `class` definitions at file scope; a name defined in more than one file is a duplicate. Same rule as `tools/port_readiness.py`. |
| Members without a name | `unk_members` | Member declarations called `unk_10`, `unk10`, `field_0x10`. |
| Initialised data by owner | `data_in_tu`, `data_typed`, `data_unk`, `data_no_c`, `data_total` | Bytes of `.rodata/.data/.sdata/.sdata2` objects: in the unit that uses them, in a data-only unit with a type, in a data-only unit as `unk`, or in no unit. |
| Symbols with a name | `fn_named` / `fn_total`, `dsym_named` / `dsym_total` | symbols.txt names that are not `fn_`, `lbl_`, `..._80xxxxxx` and the like. |
| Accesses by byte offset | `offset_accesses` | `*(T *)((char *)p + 0x10)` written out, and uses of the per-file macros that wrap it (`F(o)`, `P(o)`). Same patterns as mkgp2-pc `port/tools/pointer_width_census.py`. |
| Units named by address | `units_addr_named` / `units`, `units_data_only` | Source files whose name holds an address (`anon_80209FA4.cpp`); data-only units are counted apart. |
| Inline-asm functions | `asm_fns`, `asm_with_c` | Game functions that are inline asm in the default build, and how many have a C body under `NON_MATCHING`. |

Two of these go the "wrong" way while code is still being turned into C:
byte-offset accesses and unnamed members appear when an asm function becomes
C. They only fall once that has stopped.

Pointer-to-integer casts are not here: counting them needs clang over every
file (mkgp2-pc `pointer_width_census.py`, about 10 minutes).

## History

CI keeps one JSON line per main commit in `history/GNLJ82_restoration.jsonl`
on the `progress-data` branch, next to the matching history (build.yml,
"Update progress history"):

```
python3 tools/restoration.py append   --history F --sha SHA --ts ISO
python3 tools/restoration.py backfill --history F --ref SHA --limit 40
```

`backfill` adds one row per past day that the file has no row for (the last
first-parent commit of the day, UTC). It checks those commits out into a
temporary worktree and measures them with today's tools, so the whole past is
counted by one rule; rows it made carry `"backfilled": true`. If a counting
rule changes, delete the file on `progress-data` and the next runs rebuild it
day by day. The page charts the last row of each day and starts after the
last pause longer than 30 days.

## Adding a number

1. Count it in `tools/restoration.py` (`collect`) and give it a key in `summary`.
2. Add a `SERIES` row (chart) or a tile in `tools/gen_restoration_page.py`.
3. Add a row to the table above.
