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

## Context mode (`apply --context`, 2026-11-10)

Plain mode (above) only moves structs whose members are all data. Most
duplicated names are C++ classes (methods, constructors, base classes).
`--context` groups copies whose whole text is identical token for token
(string literals included, comments and white space ignored), writes the
first copy as written into the header, and replaces each copy with the
`#include`. Types the class uses and that are not shared stay whatever the
including file declares before the `#include` (the copy saw the same thing in
place); the header lists them in a comment. Same-batch types every user also
moved (e.g. a base class) are `#include`d. Inline method bodies emit code,
so the hash check matters here as much as before; batch 4 was clean.

Plain mode also spells typedef names (`u8`, `u32`, `Mtx`, ...) as the C
built-ins they resolve to in each copy's file (all copies must agree), so it
needs no SDK header. Include checks follow `#include`s transitively (until
2026-11-10 they matched blanked string literals and never saw any include).

`struct_dedup_batch.sh` removes headers whose every copy was reverted.

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

## State and next steps (handover, 2026-11-10 09:20Z)

Done on main: tool (aec71a4), batch 1 (58fea97: Vec3, Vec, Vec3f, Vec2,
GXColor, KartCond; 347 definitions) and batch 2 (6f6b17c: 150 more types,
445 definitions). 156 types are in `include/game/types`. Both batches left
all 2,743 objects byte-identical.

One batch, start to finish (about 3 minutes):

    git fetch origin main && git checkout -B work origin/main     # clean tree
    # open unit-claims (list with explicit page numbers) -> build/open_claims.txt, one `game/Foo.c` per line
    bash tools/helpers/struct_dedup_batch.sh                      # all movable groups; or --name X / --max-groups N
    git add -A include src docs && git commit -m "struct_dedup batch N: ..."
    bash tools/helpers/land.sh

Order from here:
1. Rerun the batch until `apply` reports 0 types (the census said 23 groups /
   56 definitions were movable right after batch 2; each landing unlocks
   structs that contain the types just shared).
2. Then the reasons table in docs/reports/struct_dedup.md is the work list,
   biggest first. Each needs a tool extension, not hand edits:
   - "needs another type": typedef names such as u8/u32/f32 (give the header
     one fixed include for them, or spell the built-in type) and pointers to
     SDK/HSD types (the header must include the same SDK header every member
     TU uses).
   - "non-plain member": structs with methods, nested types or access
     labels (C++ classes; inline method bodies do emit code, so compare
     bodies as well as members).
   - "has base class", "class": same, plus the base must be shared first.
   - "forward declaration in file" / "separate typedef in file": drop the
     local forward declaration together with the definition.
3. Class B (same name and layout, different member names): choose one
   spelling per type and rename the fields in the other TUs.
4. Class C (same layout, different names, e.g. Vec/Vec3/Vec3f): one set at a
   time; renaming changes C++ mangled names.

Pitfalls seen so far:
- `git stash` leaves the untracked `include/game/types/*.h` behind, and
  `apply` then treats those names as already shared and does nothing. Start
  from a really clean tree (`git status --short` empty).
- A header named after a generic type (`Node`, `ListNode`, `Obj`) holds the
  largest identical group only; other TUs keep a different local `Node`.
- Data symbol naming (the second half of this task) has not been started.

Pitfall (2026-11-10): objects restored from the setup build cache have no
header dependencies in ninja's deps log (`ninja -t deps X.o` lists only the
source), so a header-only change does not rebuild them and `hashes diff` /
main.dol say nothing about those TUs. Before landing a batch that edits
headers (copies in include/game/*.h, shared headers), run one clean build:
`rm -rf build/GNLJ82/src && ninja` (about 2 minutes). Batches 3-6 and the
data names were confirmed with a clean build on 88e7a64.

Member-name tiers (2026-11-10): `unify` renames members of minority copies
whose members agree by position; `relayout` re-cuts copies with the same
byte layout to the canonical member list when every accessed member has a
counterpart at the same offset and type. Both rename only `.x` / `->x`
in the copy's own file and skip copies in headers, files with an aggregate
initialiser of the type, and names other structs in reach also use. Run
`apply` afterwards. What is left differs in method signatures or layout:
changing those changes mangled names or code, so each needs a human.

## Merging views: tools/struct_merge.py (2026-11-10)

What `struct_dedup.py` leaves behind are *views*: every TU declares only the
members it touches, pads the rest and invents its own member names. For a
name that is one real type, `struct_merge.py` builds the union of the views
(member by offset, typed pointer over `void *`, the most used descriptive
name), writes `include/game/types/<Name>.h` with offsets in comments,
replaces each copy by the `#include` and renames the accesses in that file.

    python3 tools/struct_merge.py show Name     # merged layout + CONFLICT / TYPES / NAMES lines
    python3 tools/struct_merge.py run Name...   # clean tree; builds and checks every object hash

`run` puts back every file that no longer compiles or whose object changed
(a file that used the old shared header gets the old definition as a local
copy), so what stays is byte-identical by construction. It still needs the
clean build before pushing (stale header deps, see above).

What to read in `show` before running a name:
- `NAMES 0x.. -> a: a x6, b x3`: the views disagree about a member name.
  Synonyms (`pos`/`position`) are fine. Different meanings (`model` vs
  `state`) usually mean two different types share the name: do not merge,
  split the name instead.
- `TYPES`: different member types at one offset. Pointer targets are
  resolved (typed beats `void *`, spelled `struct T *` with a forward
  declaration so files with their own `T` still compile); int/float
  disagreements make the minority file fall out at the hash check.
- `CONFLICT`: overlapping members of different extent. An array or embedded
  struct that the scalars tile exactly wins and the scalar accesses become
  `name[i]` / `name.x`; anything else leaves the minority copies local.

Decisions a human made are recorded in `tools/struct_merge_hints.json`, per
type: `names` (offset -> member name), `fields` (offset -> full declaration),
`aliases` (other type names that are the same real object, e.g. `KartStatus`
= `ItemEffectBus`), `header` (an existing header already has the full
definition; views move onto it), `exclude`, `size`, and `why`.

Limits: a name whose shared header is included by another header is skipped
("by hand"); classes with methods, bitfields and unions are left alone; the
member-name test is `GENERIC_RE` in struct_merge.py (struct_dedup's version
counts all-hex words such as `eff` as placeholders, do not reuse it).

### C++ classes: `struct_merge.py classes Name...`

A class with methods or virtuals cannot be merged member by member. `classes`
tries the shared header's spelling (or, without one, each of the most common
spellings) in every other file that has a copy and keeps the files whose
object stays byte-identical. Result on 2026-11-10 over the first 26 class
names: about 50 copies, most classes 0-3. What stops the rest: every TU
declares only the virtuals it calls and gives the others placeholder names
and `void` returns (InputPlayer has 14 spellings of one vtable), inline
bodies name a per-TU constant (`ScopedTimer` divides by a different
`lbl_806D....` in each file), and data members are spelled differently.
These need one hand-written class per name, tried file by file; the loop
costs about a minute per class (it rebuilds the big units twice).
