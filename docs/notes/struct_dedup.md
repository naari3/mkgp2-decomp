# One definition per type: tools/struct_dedup.py

Goal (naari3, 2026-11-10): the port (mkgp2-pc) needs every type defined once.
Today most TUs carry their own copy of the structs they touch (about 6,900
definitions at file scope, 728 names defined in more than one file). The
copies agree at 32 bit and break silently once a pointer member changes size.

## What the tool does

    python3 tools/struct_dedup.py scan          # census -> docs/reports/struct_dedup.md
    python3 tools/struct_dedup.py groups NAME   # every definition of NAME, and why each can or cannot move
    python3 tools/struct_dedup.py hashes save   # before: sha1 of every build/GNLJ82/src/**/*.o
    python3 tools/struct_dedup.py apply --max-groups 20
    ninja && python3 tools/struct_dedup.py hashes diff [--revert]

`apply` takes groups of definitions with the same name, the same kind and
the same member list (white space, comments and `float x, y, z;` versus one
member per line do not count), writes `include/game/types/<Name>.h` and puts
`#include "game/types/<Name>.h"` where each copy stood. The largest group of
a name wins; copies with other member lists keep their local definition and
show up in `groups NAME`.

A struct definition emits no code, so **every object file must stay
byte-identical**. `hashes diff` checks that; `--revert` restores the sources
of objects that changed. `main.dol: OK` alone is not enough, because a
NonMatching unit links the original object.

## Rules the tool follows (each one came from a real difference)

- A definition is moved only when its member types are C built-ins, pointers,
  or types the file already takes from `include/game/types`. Rerun the tool
  after a batch lands: structs that contain `Vec3` become movable once
  `Vec3` is shared. Types with methods, base classes, bitfield tricks under
  `#if`, or a forward declaration in the same file are left alone.
- `typedef struct { ... } Name;` (no tag) is not moved in C++ code: the
  shared header has the tag, and Metrowerks mangles `Name` differently for a
  tagged and an untagged struct (JumpDistanceMode_Init, NokoNoko_801287F8).
  `.c` files compiled with `-lang=c++` or `#pragma cplusplus on` count as C++.
- Files are read and written as bytes (CRLF and Shift-JIS comments stay).
- Units under an open unit-claim are skipped: put their configure.py paths
  (`game/Foo.c`) in `build/open_claims.txt`, one per line, before `apply`.

## Classes that are only reported

- B: same name, same byte layout, different member names or padding
  spelling. Needs one spelling chosen and the field names in the other TUs
  renamed; no code change, but a human (or a later tool mode) must pick.
- C: same byte layout under different names (`Vec`, `Vec3`, `Vec3f` are the
  obvious set). Renaming changes C++ mangled names, so these go one set at
  a time with the hash check.

## Landing

Announce on the agent board first, land in batches of a few hundred files,
check the board and open claims before each batch, and do not touch a TU
somebody has claimed.
