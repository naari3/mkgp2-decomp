# Data that one unit owns and other units use by name

Written 2026-11-10 for the PC port (mkgp2-pc `docs/port/upstream_requests.md`
item 10). Under MWCC the link works by address, so it does not matter whether
the unit that owns an object and the units that use it agree on its name or
its linkage. Any other compiler links by name, and ends up with two objects
or with none. This note records the cases, what was done, and what is left.

Tools: `python3 tools/alias_census.py --list` (pairs still open),
`python3 tools/extern_const.py --check` (const definitions lacking `extern`).

## The cases

| case | how MWCC gets away with it | what the source does now |
| --- | --- | --- |
| `const T x = ...;` at file scope in a `.c` unit compiled as C++ | MWCC emits it as a global either way | `extern const T x = ...;` (237 definitions, `tools/extern_const.py`) |
| `static` object under a source name, other units use the symbols.txt name | `tools/postprocess_extab_user.py` renames the symbol after compiling (`tools/extab_user_renames.json`, `"global:"` entries make it global) | `SHARED_STATIC` / `SHARED_BSS` and `#ifndef __MWERKS__ #define local Shared` |
| `static` object already called by its symbols.txt name, other units declare it `extern` | the owner is NonMatching, so the original object is linked and it has the global | `SHARED_STATIC` (CardChecksumPoolPrivate.h, 63 objects) |
| C++ `const` (internal) in a real `.cpp`, other units declare it `extern` | as above | `SHARED_EXTERN const T x = ...;` |
| float literal of the owner that another unit reads as `extern const float lbl_...` | `tools/postprocess_sdata2.py` names the anonymous literal after compiling | `#ifndef __MWERKS__ extern const float lbl_... = value; #endif` in the owner (RaceScene_FrameUpdate.cpp, clFlowCourse.cpp, FaceEffect.cpp) |
| code addresses an object from another object's name plus an offset | one contiguous section | non-MWCC base expression (CardUnpackLegacy.cpp: its messages are `lbl_803175A0`, 0x2228 past the previous unit's first .rodata label) |

The storage classes are in `include/game/types/shared_data.h`. They expand to
exactly the old tokens under MWCC; every landing was checked with
`tools/struct_dedup.py hashes diff` (3006 objects, 0 changed).

Where one merged unit sees the shared name under two types, the declaration
that conflicts is hidden from the defining unit only outside MWCC
(`ANON_8021F088_POOL_OWNER`, NamCamFlow_missing_private.h), or the second view
becomes a cast of the defining table (fn_801F27B4.cpp `lbl_804E5050`).
jvsio.c puts its `#define cmd ...` in front of the headers because a struct
member is also called `cmd`.

## Left open, and why

- **Vtables and RTTI records** (`alias_census.py --unnamed`, about 1,550
  rows, almost all `__vt__` / `__RTTI__`): the build names the compiler's own
  vtable after compiling, and hand-written constructors store that address
  (`self->vt14 = clCSParts_vtable_8048EE48`). There is no source object to put
  the name on, and another compiler's vtable has another layout anyway. This
  needs the classes to be real C++ classes on the port side, unit by unit.
  Named examples the port stubs today: `clCSParts_vtable_8048EE48`,
  `data_804EE3A8_data_806D06E4` / `_806D06EC` (RTTI records that an autodata
  table points at).
- **String-literal pools read by name**: `lbl_803BD228` (fn_801E4544.cpp `@129`,
  read by three units), `lbl_803BF440` (fn_801F9B64.cpp's whole .rodata, read
  by fn_801F9DA4.cpp as one `CourseRodata` struct), `sdata_806CEFE0_data_8040F0A4`
  (TaMode_FrameUpdate.cpp `@279`, pointed at by an autodata table). Giving the
  literal a name in the owner changes MWCC's pooling, so these stay until the
  units are merged or the user is rewritten.
- **Per-unit copies** (`lbl_xxx_pN` in the rename table, 41 pairs): several
  units each define their own copy of one object and the build folds them.
  The port folds the `_pN` names itself.
- `_ctors` / `_dtors` and `THPDec_bss_806A4A40`: runtime and SDK, replaced on
  the port side.
- Not a source problem: `auto_ONKARTHIT_block.c` and `RankPanel_80144430.cpp`
  define their names correctly, but the port's link census compiles with
  `-fno-exceptions` and both units contain a `throw`.
- Types: a shared object is still declared with different types in different
  units (`const Int5` and `const int[5]`, `char[]` views of float tables).
  That links wherever data symbols are not type-mangled; a compiler that
  mangles variable types (MSVC, for C++ linkage) needs the views unified
  first.
