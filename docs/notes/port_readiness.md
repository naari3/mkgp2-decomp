# Port-readiness numbers (`tools/port_readiness.py`)

The matched-function count stays where it is while the PC-port prerequisites
move. This script prints what does move, from tracked files only (no build,
about one second):

    python3 tools/port_readiness.py          # table
    python3 tools/port_readiness.py --md     # markdown, for a landing report
    python3 tools/port_readiness.py --json   # same numbers, machine readable

The GitHub Pages progress site shows the same table ("Port readiness", built by
`tools/gen_progress_page.py` on every push to main) and publishes
`port_readiness.json` next to `report.json`.

| Row | Counts | Moved by |
|---|---|---|
| Initialised data defined in the TU that uses it | bytes of .rodata/.data/.sdata/.sdata2 objects inside a normal source unit | tools/own_data.py, TU work |
| ... in data-only TUs with a real type | objects in `src/game/autodata` not typed `unk*` | tools/autodata.py `retype`, hand typing |
| ... in data-only TUs, layout unknown | objects typed `unk32/unk16/unk8` there | goes down as types are added |
| ... with no C definition | objects outside every unit of splits.txt | tools/autodata.py `gen` |
| Type names defined in more than one file | struct/union/class names defined at file scope in several files of src/game + include/game | tools/struct_dedup.py |
| Types shared through include/game/types | headers there | tools/struct_dedup.py |
| Data / function symbols with a name | symbols.txt names that are not `lbl_`, `fn_`, address-suffixed or generated | naming work |
| Asm-only game functions with an equivalent C body | inline-asm functions in src/game larger than 16 bytes that have a `NON_MATCHING` C side | docs/nonmatching_c.md |

Not measured yet: whether data owned by a normal TU is typed or still a
`unsigned int`/`unsigned char` array written by tools/data2c.py.

When you land port-prerequisite work, put the before and after of your row in
the commit message or landing report.

Baseline, 2026-11-10 09:00Z (before the data-typing thread): no C definition
about 688,000 bytes, autodata 0. At 10:10Z: no C 1,604, unk 69,827, typed
484,901, in its TU 1,658,867.
