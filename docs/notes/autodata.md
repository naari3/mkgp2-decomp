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
defined but `unk` / typed. State on 2026-11-10 (263 units):

| | first run | after the symbol fixes |
|---|---|---|
| no C definition yet | 137,668 | 1,584 (jump tables) |
| defined, layout unknown (`unk*`) | 138,305 | 152,093 |
| defined and typed | 280,360 | 402,635 |

After `retype` (struct initialisers, same day): unk 69,827, typed 484,901.

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

## Struct types (`autodata.py retype`, `tools/cstruct.py`)

`retype` looks at every definition that carries a `/* decl: T */` comment,
reads the layout of `T` from the TU that declares the object (preprocessed with
that TU's own flags, parsed by `tools/cstruct.py`), and rewrites the blob as
`T name[n] = { { ... }, ... };`. It is refused when the object size is not a
multiple of the struct size, when padding bytes are not zero, when a relocation
sits in a member that is not a pointer, or when a float member holds something
that is not a float; the reason is printed. When several TUs declare different
types, the one with the most members that still fits wins.

The type itself comes from `include/game/types/<T>.h` when that header exists
with the same layout (tools/struct_dedup.py writes those), otherwise a
definition with builtin member types is written into the autodata file with a
comment naming the TU it was read from. Pointer members become `void *` with
the original target in a comment.

`python3 tools/cstruct.py src/game/Foo.c TypeName` prints a layout.

## Row types read off the values (`autodata.py infer`)

For `unk32` word tables nobody declares: finds the smallest row length where
every column is either all floats or all small integers and writes
`struct <name>_Row { float f_00; int i_04; ... }` (or a plain `float`/`int`
array). The comment above the type says it was read off the values, not from
code; member names are offsets. 2026-11-10: 14 KB.

Second pass (same day, 18 KB more): two more column kinds and text.
- `b`: every word is `0xNN000000`: `unsigned char b_XX; unsigned char pad_XX[3];`
- `s`: both halves are small signed 16-bit values: `short s_XX; short s_XX+2;`
- an object that is nothing but text (strings back to back, dtk merged them
  because the code reaches them through one anchor) becomes one `char[]` of
  string literals joined by `"\0"`. Text needs no byte swap, so one object is fine.
A column that fits none of these stays `unk32`.

Third pass (26 KB): anchor pools that mix strings and numbers (`mixed_pool`).
The object is cut at each NUL-terminated string (zero padded to 4), the words
between are floats or small integers, and it becomes one
`struct <name>_Pool { char s_000[28]; float f_01C[3]; ... }`. A port swaps the
numeric members and leaves the `char` members alone.

`infer --raw <source files>` does the same for one-line `unsigned int x[N] = {...};`
word dumps inside normal TUs (32 KB on 2026-11-10: path point tables of RivalRun
and others became `float` arrays or row structs). Build afterwards: a TU that
indexes the array as integers would change or fail, then revert that file.
`tools/port_readiness.py` counts what is left as "plain unsigned int array".

## Byte arrays that hold numbers (`tools/autodata_bytes.py`, 2026-11-10)

`gen` keeps the declared type, so every object a unit declares as
`extern const unsigned char x[]` and reads through casts
(`*(float *)(x + 0x10)`, a struct copied out of `x + 0x3FC`) was written as
bytes in the console's order: right under MWCC, wrong for every number on a
little-endian build (mkgp2-pc upstream request 15; first seen in
`clFlowClass_Update`, whose animation ids came out byte-swapped).

`python3 tools/autodata_bytes.py --evidence bytes_evidence.pkl` rewrites
those definitions. 886 byte arrays: about 700 are text (ASCII, Shift-JIS,
half-width katakana) and stay; 25 KB in 28 units became numbers:

- one column kind per row (`autodata.py infer` on the words): `float` /
  `int` arrays and row structs;
- otherwise a `<name>_Pool` struct cut into `char s_XXX[]` strings,
  `float f_XXX[]`, `int i_XXX[]`, `double d_XXX` and `unsigned char x_XXX[]`
  for bytes that fit none of these (three objects, 36 bytes: byte-wide fields,
  left as they were).

The cut uses how the code reaches the object, collected by
`tools/port_abi/bytes_evidence.py` from clang's optimised IR of every unit:
an offset whose address is passed on starts a new member (and is what lets a
string start there), a block copy marks numbers, a byte-wide load or store on
a member that would become a number vetoes the object. Where bytes read as
text and as floats alike (`42 85 55 56 44 7A 00 00` is 66.6667, 1000.0, and
also "B\x85UVDz"), they are floats; a string whose first word alone is also a
float needs the code to take its address, and a string never runs across an
address the code takes (the last float of a table can be followed by a joint
name with no terminator between).
`0x43300000 00000000` / `...80000000` are doubles (the int-to-float conversion
constants). Everything else is read off the values, as in `infer`: a small
word is an `int`, which is a guess when nothing reads it directly.

Four tables of the same kind were defined inside normal units
(`fn_8010FA60.c`, `ItemObject_Tick_Kind2c_Horn.c`, `MapWaterEffect_Init.c`,
`BoomerangItem_Tick.c`); they got the same pool structs, cut at the offsets
the unit adds to the table pointer, and the unit takes the address with a
cast.

Still bytes on purpose: text, all-zero objects, sizes that are not a multiple
of 4, and six small-data objects whose values fit nothing
(`autodata_bytes.py --list`). The units that declare these objects still say
`unsigned char[]`; only the definition changed, so nothing else in the
matching build moves (all objects and `autodata.py check` identical).

An embedded file image is typed as bytes on purpose: the 31.8 KB object at
0x80412158 is a `*_line.bin` course file (dtk had cut it in two), read by
`CourseLookup::LoadMemory`. A port swaps it with the loader, like the files.

## Symbol fixes that were needed (symbols.txt)

- An object that starts on an odd address right after another one is a wrong
  split: `lbl_80383FFD` was the middle of a float (kart parameter block
  `rodata_803175A0_rodata_80383F28`, now 0xF0 bytes of float plus `lbl_80384018`), `"M"` + `"KA"`
  was the card magic `"MKA"` (`lbl_806D34A4`, `lbl_806DA110`).
- A one-byte variable in .sdata followed by zero bytes had the padding counted
  in its size (`lbl_806CEF69`, `lbl_806CFBA1`, `lbl_806CFCA2`, `lbl_806CFCAB`:
  size 1 now).
- When one object cannot be placed (`left out:` in the gen output) the tool
  leaves it in its auto unit and continues with a new unit after it.
- MWCC ignores `__attribute__((aligned(8)))` on pointer types; the tool starts
  a new unit at such an object instead.

## To do

- The `unk` objects nobody declares with a struct type (read how the code
  indexes them), and the `/* decl: T */` objects `retype` refused.
- Moving definitions into their real TUs where that is possible.
