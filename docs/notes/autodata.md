# Data-only TUs for initialised data (`src/game/autodata`, `tools/autodata.py`)

Started 2026-11-10 for the PC port (mkgp2-pc `docs/port/readiness.md`): a port
cannot use data that is linked from the original binary. Every object has to be
defined in source, with a type, so another compiler can lay it out for another
byte order. About 688 KB of `.rodata`/`.data`/`.sdata`/`.sdata2` had no C
definition.

## What the tool does

`python3 tools/autodata.py gen --all` turns each unowned run of a data section
into one data-only TU, `src/game/autodata/<section>_<address>.c`, with the
objects in address order. Functions keep their `extern` declarations, so no
function changes and no TU gets a section anchor it did not have. The units are
linked like any other (`lib "autodata"` in configure.py takes the directory
content, so there is no per-unit line to add), main.dol stays OK, and
`autodata.py check` compares every built object with its target object (bytes,
relocations, symbol offsets).

This is the mechanical half. It does not claim the data belongs in these files:
the original game had it in the TUs that use it. Giving it to those TUs
(`tools/own_data.py`) is blocked in many places by link-order cycles, section
anchors and shared tables (docs/gave_up.md, "Data-ownership wind-down"). A
definition here can be moved later: cut it out of the autodata file, paste it
into its TU, and move the range in splits.txt.

## Where the types come from

1. The declared type: every `extern` declaration in `src/` and `include/` is
   indexed. A scalar or pointer type is used as declared (typedef names are
   spelled with builtin types, pointers to project types become `void *`).
2. Content: strings, pointer tables (relocations; `const char *` when every
   target is a string), float tables, small-data scalars.
3. `unk32` / `unk16` / `unk8` (include/game/autodata.h) when the layout is not
   known. **These are the objects that still need a real type.** `unk32` only
   says the disassembly showed 32-bit words; a struct with byte or short fields
   read through it would be wrong on a little-endian build. When a user TU
   declares a struct type, the comment above the definition names it
   (`/* decl: ItemClassEntry */`): the next step for that object is a struct
   initialiser with that type.

`python3 tools/autodata.py report` prints bytes per section: no C definition /
defined but `unk` / typed. State on 2026-11-10 after the first run (252 units):

| | bytes |
|---|---|
| no C definition yet | 137,668 |
| defined, layout unknown (`unk*`) | 138,305 |
| defined and typed | 280,360 |

(The 131 KB sine table went to `LUT_Sine.c` directly, commit 44f521b.)

## Mechanics worth knowing

- `.rodata`/`.data` units compile with `-sdata 0 -sdata2 0`, `.sdata`/`.sdata2`
  units with `-sdata 4096 -sdata2 4096`, so every object lands in the section
  the unit is split for.
- `#pragma explicit_zero_data on` keeps zero-initialised objects out of .bss,
  `#pragma force_active on` keeps unreferenced ones.
- MWCC aligns every object in .rodata/.data to 4. An object that sits on an
  8-byte boundary the 4-byte rule does not explain gets
  `__attribute__((aligned(8)))` and a comment: in the original that was most
  likely the first object of a TU, so these comments mark TU boundaries.
- Post-compile step `tools/postprocess_autodata.py`: removes `.comment` (MWLD
  takes alignment and dead-stripping from it) and pins the section alignment to
  4 for the units in `src/game/autodata/align4.txt` (run starts on a 4-byte
  boundary).
- dtk needs 4-aligned split ends. A unit whose last object ends on an odd
  address gets a `pad_XXXXXXXX` symbol in symbols.txt for the pad bytes;
  without it dtk's gap symbol crosses the unit end and objdiff stops with
  "size out of section bounds".
- dtk prints `.double 4503601774854144` without a decimal point: it is a double.
- Left in the auto units on purpose: compiler jump tables, objects with a
  relocation to a local label, and dtk's `pad_NN_` objects (padding in front of
  a 32-byte-aligned unit; a C object there gets dropped and the image shrinks).

## Commands

    python3 tools/autodata.py runs [--sec .rodata]     # unowned runs, largest first
    python3 tools/autodata.py gen SEC LO [HI] [--dry]  # one run or range
    python3 tools/autodata.py gen --all                # everything it can do
    python3 tools/autodata.py check                    # built objects == target objects
    python3 tools/autodata.py drop UNIT ...            # undo a unit (file, splits, pad symbol)
    python3 tools/autodata.py report [--md FILE]

After `gen`: rerun configure with the flags from tools/cloud_setup.sh, `ninja`,
main.dol OK. `gen` reads build/GNLJ82/asm, so build once before generating
again.

## To do

- Runs the tool skips: an object that starts on an odd address (dtk split a
  string or byte table in the middle; fix the object in symbols.txt), and a
  relocation inside an object that is not word-shaped.
- Struct initialisers for the `/* decl: T */` objects, then the `unk` objects
  nobody declares (read how the code indexes them).
- Moving definitions into their real TUs where that is possible.
