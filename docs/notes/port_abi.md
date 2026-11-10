# Calls and bit-fields that only work on the original ABI

Written 2026-11-10 for the PC port (mkgp2-pc `docs/port/upstream_requests.md`
items 11 and 12). The matching build compares machine code, so source that
relies on the PowerPC EABI and on MWCC's layout matches fine and breaks on
any other target. Two such things were swept; this note says what the
conventions are and what is left.

## Arguments the original leaves in a register (item 11)

`python3 port/tools/arity_census.py` in mkgp2-pc compares every direct call
with the definition. Pairs with fewer arguments than the definition: 130
before, 5 after (the 5 are `static inline` helpers that happen to share a
name across units: `Item_TickFallFade`, `Item_TickFall`, `UpdateParticles`).

What the pairs turned out to be, and what to write:

| pattern | fix |
| --- | --- |
| `A(); B();` where B's argument is A's result (still in r3) | `B(A());` and real prototypes. Same code. |
| a function that only forwards its own arguments to the callee | give the wrapper its real parameters and pass them on. Same code in most cases. |
| the value sits in a register across other instructions (`buf = Alloc(n); if (buf) Init();`) | `Init(REG_ARGS1(buf));` (`include/game/types/reg_args.h`: nothing under MWCC, the argument elsewhere). `MORE_REG_ARGSn` follows written arguments. Also usable in prototypes and parameter lists. |
| the plain argument changes MWCC's code in a wrapper | `REG_ARGS`/`MORE_REG_ARGS` in the parameter list and the call, or `#ifdef __MWERKS__` around both (VfxSlot_SetScaleVec3.c) |
| the definition has a parameter nothing ever passes or reads (`void fn(int p0)`) | remove it from the definition |
| a struct by value (`Vec pos`), which MWCC passes as the address of a caller-made copy, called from units that pass that address by hand | outside MWCC those units are pointed at a `_ByAddress` entry defined beside the function: `#ifndef __MWERKS__ #define SoundMgr_PlaySE_Positional SoundMgr_PlaySE_Positional_ByAddress #endif` in front of their prototype (also `Item_RenderCharacterScaledFromJoint12`) |

Always try the plain form first and check the object hash; fall back to the
macro only when the object changes.

### The reverse: the caller declares a struct by value, the definition takes its address

About 330 caller/callee pairs (45 callees: `Mtx44_TransformVec3`,
`ItemObject_GetGroundTypeAt`, `VfxSlot_SetPositionFromVec`, `Mtx44_Translate`,
`VfxSlotMgr_Update`, `SoundMgr_PlaySE_WithChannel`, ...) declare
`void Foo(Mtx44 m, Vec3 v)` and call `Foo(m, pos)` while the definition is
`void Foo(float (*m)[4], Vec3 *v)`; some also declare a `Vec3` return where
the definition has a leading result pointer. MWCC produces exactly that
(address of a caller-made copy, hidden result pointer first), so the objects
match. For other compilers each such prototype is wrapped:

```c
#ifdef __MWERKS__
extern void SoundMgr_PlaySE_WithChannel(int se, Vec3 pos, int ch);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SoundMgr_PlaySE_WithChannel(int, Vec3 *, int);
static inline void SoundMgr_PlaySE_WithChannel_ByValue(int se, Vec3 pos, int ch) { SoundMgr_PlaySE_WithChannel(se, &pos, ch); }
#define SoundMgr_PlaySE_WithChannel SoundMgr_PlaySE_WithChannel_ByValue
#endif
```

The MWCC branch is the original line, so the objects cannot change, and the
call sites are untouched. Write the same block when a new unit declares one
of these callees by value. (`Scene_8014E0C4.cpp` uses a function-like macro
for `VfxSlotMgr_Update` because the struct is still incomplete at that
point.)

### K&R prototypes and floats

`extern void Foo();` followed by `Foo(p, 1.0f)` promotes the float to double.
PowerPC passes both in the same register; nothing else does. The units that
did this (`MukadeItem.c`, `StarItem.c`, `Effect.c`, the `TornadoItem`
fragments) now declare the parameter lists. Do not use empty parentheses for
a callee that takes floats.

### int and float parameters in another order

About 90 prototypes list the same parameters as the definition but with the
floats moved (`fn_80181790`: caller `(ptr, int, float, int, int, int, int)`,
definition `(ptr, int, int, int, int, float, int)`). PowerPC numbers integer
and float argument registers separately, so only the order inside each class
matters and the declared order is free; it is sometimes a matching lever
(matching_rules §74). The same is true of x86-64 System V, but not of Win64
or 32-bit x86. Same shape of fix, pairing the n-th integer and the n-th float
of the caller with the n-th of each in the definition:

```c
#ifdef __MWERKS__
extern void Object_DriveAnimAndSkin(clNormal3D *obj, float a, float b, clNormal3D *src);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void Object_DriveAnimAndSkin(clNormal3D *, clNormal3D *, float, float);
static inline void Object_DriveAnimAndSkin_Reordered(clNormal3D *obj, float a, float b, clNormal3D *src) { Object_DriveAnimAndSkin(obj, src, a, b); }
#define Object_DriveAnimAndSkin Object_DriveAnimAndSkin_Reordered
#endif
```

### Tools

`tools/port_abi/` holds what found and rewrote these: `types_census.py`
(argument classes of every call against the definition, from clang's LLVM
IR), `shapes_census.py` (all shapes per callee, C++ callers included),
`byvalue_fix.py` and `order_fix.py` (the two generators). They need clang and
a mkgp2-pc checkout for its compile flags; see the header of each file.
After the sweep `types_census.py` reports only the open items below plus the
generated wrappers themselves.

### Still open

- Seven calls pass an explicit result pointer to a definition that returns a
  small class by value (`fn_80157940`, `fn_80157B38`, `fn_80157C60`,
  `fn_80157D30`, `fn_80157DE0` from `Scene_8014E0C4.cpp`; `fn_80247C3C` from
  `RaceDigitLap.cpp`). The classes have user-written copy operations, so
  Itanium-style ABIs pass and return them by address like MWCC does; the only
  difference is 32-bit x86, where a struct-returning callee pops the result
  pointer. Left as they are.
- `AnimState_New.c` and `AnimState_Reset.c` call `AnimState_Init(self, 0.0f)`
  through a `(AnimState *, float)` prototype; the definition
  (`AnimState_Step.c`) takes `(AnimState *, AnimEntry *entries)`. On PowerPC
  the callee therefore reads whatever r4 held. Not changed: what the
  original passes there is not known from the callers alone.
- Units that do not compile with clang yet (7 in `src/game`, for example
  `auto_ONKARTHIT_block.c`) were not seen by the census; they may hold more
  of all three kinds.
- The remaining `arity_census.py --all` pairs are calls with trailing
  arguments the definition does not read; harmless where the caller cleans
  the stack.

## Results read from a function defined `void` (request 19, 2026-11-10)

On the console a caller may read r3 after calling a function whose definition
says `void`: the register still holds whatever the callee left there. A host
compiler returns garbage. Fifteen such functions were listed by the port
census (definition `void`, some caller declares a result). For every one of
them the plain C form, returning the value the code leaves in r3, compiles to
the same object under MWCC, so no macro was needed:

| function | now returns |
|---|---|
| `CollisionFile_FixupPointers` | its argument (the file base) |
| `Allocator_Identity_VoidVoid` | its argument |
| `CourseData_GetDefaultPathKey_Safe` | result of `CourseData_GetDefaultPathKey` |
| `DrawEffect_SetU32CC` | `self` |
| `HSD_MemCallback4` | result of the callback (`s32`) |
| `NamCam_LoadImage` | result of `Asset_LoadAndDecompressByType` |
| `TCPConn_LogError` | `acGetLastError(socket)` when result is -1, otherwise `result` |
| `Vtable_CallSlot2` | result of the virtual call |
| `fn_8014D4F0` | result of `runner->m18()` |
| `fn_80169DF0` | result of `Sci2Card_GetByteFlag1224` (`unsigned char`; the two callers that declared `int` now declare `unsigned char`) |
| `fn_801E6594` | result of `fn_801E9290` (`unsigned char`) |
| `fn_80241C08` | its argument (it is a constructor passed to `__construct_array`) |

Three were the caller's mistake, and the caller was corrected instead; their
definitions stay `void`:

- `fn_801A1128`, `fn_801A1174`: `fn_801DA46C.c` nested the three calls
  (`fn_801A0DF0(fn_801A1128(fn_801A1174(...), x, y))`) although
  `fn_801A1128` takes two floats and `fn_801A0DF0` takes nothing. Written as
  three statements it gives the same object.
- `fn_801E93A0`: `Scene_80164614.cpp` passed its "result" to
  `ReplayRandCursor_Reset`, which ignores its parameter. Now
  `fn_801E93A0(); ReplayRandCursor_Reset(REG_ARGS1(0));`.

When a new case turns up: read the tail of the callee's asm for what r3 holds
at `blr`, write that as the return value, and check the object hash. If r3 is
only a leftover that the callee never set, correct the caller.

## `new T[n]` must be freed with `delete[]` (request 20, 2026-11-10)

MWCC's `new T[n]` writes a 16-byte header (element size, count) in front of
the array and `delete[]` calls `__destroy_new_array(p, dtor)`. A host compiler
keeps its own cookie, so an explicit `__destroy_new_array(arr, dtor)` on an
array made with `new T[n]` frees a wrong pointer there. Write `delete[]
(T *)arr;` with the element class: it compiles to the same call. The two
sites in `Scene_8014E0C4.cpp` (`fn_8014FE10` and the demo scene destructor)
were changed this way; the code and relocations are identical, only the order
of two undefined symbols in the object's symbol table moved, and main.dol is
unchanged. No other source calls `__destroy_new_array` or
`__construct_new_array` explicitly. `__construct_array` / `__destroy_arr` on
member arrays carry no header and are fine as they are.

## Text stored as words (request 21, 2026-11-10)

Some tables keep a file name or a label inline between pointers and numbers,
and the source describes the table as an array of words (`void *const
lbl_8037D7DC[9] = { 0x65665F73, ... }` is "ef_st_dino_sazanami.dat" followed
by three words). A little-endian host stores each word reversed, so the text
is scrambled. Such words are written with `TEXT_WORD('e', 'f', '_', 's')`
(`include/game/types/text_word.h`): the same number under MWCC, the bytes in
reading order on any host. The object's type and every use of it stay as
they are.

`python3 tools/port_abi/text_words.py` lists the runs it recognises (two or
more words that decode as ASCII or Shift-JIS text, start at a boundary and
end in a NUL; floats that look like text, such as 0x3F333333 0x3F666666, are
kept out). `--fix <files>` rewrites them. Bytes outside ASCII are written as
numbers (`TEXT_WORD(0x83, 0x5E, 0x83, 0x43)`).

All recognised runs are converted (about 3200 words in 30 files: the map
effect and joint name tables in the autodata units, the banned-word tables
in `NameCheck_CardName.c`, the card and printer messages, scene labels). In
an `int` array that wrote the word as a negative decimal the tool adds
`(int)`. Not converted, because they are not strings but would need the same
care on a host that reads them as bytes: `KartDriver_InitFull_data_803F5928`
in `autodata/data_803F57E0.c` (a byte table typed as 30 words). Single words
of one to three characters outside a run are left as numbers unless they
follow the rules above; check a table by eye when one misbehaves.

## Constructors declared in another order (request 22, 2026-11-10)

A unit that only uses a class declares its constructor itself, and
`tools/extab_user_renames.json` joins the mangled name to the real symbol.
Several such declarations list floats and integers in another order than the
definition: `RaceCamera(float, int, float, int, void *)` for
`clShadow::clShadow(int width, int height, HSD_LObj *lobj, float far, float
near)` (`Camera_Create`). PowerPC does not care; another ABI does.

The written order cannot simply be corrected: it decides the order in which
MWCC loads the arguments at the call (tried on `RaceSceneC`; the three loads
swap). So both orders are written with `ARGS_ORDER((as written), (as
defined))` from `include/game/types/arg_order.h`, in the declaration and in
every `new` expression. MWCC sees the first list, everything else the second.
The keys in the rename table stay the MWCC names.

`python3 tools/port_abi/rename_order.py -v` lists the targets reached under
differing orders (constructors and member functions). Four, all fixed:

| target | definition | declarations rewritten |
|---|---|---|
| `Camera_Create` | (int, int, lobj, float, float) | `Camera` (types/Camera.h, CoinChallenge.cpp), `RaceCamera` (types/RaceCamera.h, Scene_8014E0C4.cpp), `BLCamera`, `RCCamera`, `RICamera`, `VSCamera`, `Camera163` |
| `CarObject_Init` | 8 integers, then x, y, yaw | `CarObject` (RaceScene_Init.cpp, TaModeInitPrivate.h), `Car163` |
| `TornadoEffect_Ctor` | 4 integers, then 3 floats | `Owned80052B50` (auto_ONKARTHIT_block.c) |
| `fn_801A08B8` | (int id, unsigned char flag, float x, float y) | `FKSprite` (clFlowKart_Init.c) |

Floats keep their relative order and integers theirs, which is exactly what
the registers do.

## Pointers to member functions (item 14)

MWCC's pointer to member function is 12 bytes, `{ long thisDelta; long
vtableOffset; union { void *func; long vptrOffset; }; }`, with
`vtableOffset == -1` for a non-virtual function and all zero for null
(`src/Runtime.PPCEABI.H/ptmf.c`). Clang and GCC use 8 bytes with another
meaning. The game's tables are hand-written in MWCC's layout
(`void *x[3] = { 0, (void *)-1, fn }` in `src/game/autodata`) and read
through real pointer-to-member types, and the objects holding one are laid
out for 12 bytes.

`include/game/types/pmf.h` gives four macros that are the plain C++ forms
under MWCC and keep the 12-byte layout elsewhere:

| macro | MWCC | elsewhere |
|---|---|---|
| `PMF_TYPE(Name, Class, Ret, Args);` | `typedef Ret (Class::*Name) Args;` | `typedef PortPmf<Ret (Class::*) Args> Name;` (12-byte struct) |
| `PMF_CALL(obj, pmf)(args)` | `((obj)->*(pmf))(args)` | adds `thisDelta`, takes `func` or the vtable entry at `*(this + vptrOffset) + vtableOffset`, calls it with `this` first |
| `PMF_OF(&Class::Method)` | the constant | built at run time from the host's `{ ptr, adj }` (Itanium ABI; a virtual function gets `vptrOffset` 0) |
| `PMF_IS_SET(pmf)` | `(pmf)` | any of the three words non-zero |

All 12 typedefs (24 with the per-unit copies in the `DNBress_*` units), the
two in-struct declarations (`ItemEffectMgr::poll`,
`CardTaskPrintJob::is_running`), the 10 call sites and the constants in
`clItemBox.cpp` and `fn_801F27B4.cpp` use them. Write new ones the same way;
`grep -rnE '::\s*\*|->\*' src/game include/game` should only find
`include/game/types/pmf.h`.

Limits of the non-MWCC side: up to three arguments; the object pointer is
reinterpreted rather than converted (the game calls through view structs
unrelated to the class named in the type), which is right for the single
inheritance the game uses; the call assumes member functions take `this` as
an ordinary first argument (true for Itanium-ABI targets, not for 32-bit
MSVC `thiscall`).

## Vtable pointer position (measured by the port thread, 2026-11-10)

MWCC GC/1.3.2 puts the vtable pointer where the first virtual function is
declared, not at the start of the class: `struct { int a; virtual void f();
int b; }` has it at +4 and `b` at +8; at +0 when the virtual comes first;
after a non-polymorphic base when there is one. A virtual destructor takes
one vtable slot. Itanium-ABI compilers always put the pointer first and use
two destructor slots. The port rewrites clang's output for the vtable target
and the destructor slot (mkgp2-pc `port/tools/mwcc_cxx_abi.py`); the pointer
position is not handled there yet and affects base-less classes with data
members before the first virtual (about 12 in `src`, 5 in `include`:
`PropNode`, `CoursePropNode`, `clCSPartsInerface`, mapobject `Obj` /
`clModel`, the `*Base0` classes). Nothing was changed here for it.

## Bit-field order (item 12)

MWCC for PowerPC allocates bit-fields from the most significant bit, x86
compilers from the least significant, and the game reads the same storage as
integers. Every run of bit-fields is declared per storage unit with
`BITFIELDSn(...)` / `BITFIELDSn_PAD(...)` from `include/game/types/bitfields.h`
(source order under MWCC, reversed elsewhere). `python3 tools/bitfield_runs.py`
rewrites direct declarations and `--check` lists them (0 now; 235 members in
22 files were rewritten).

Left open: a view made of `u8` bit-fields over a `u16`/`u32` (PCBCheckRecv.c
`union SlotFlags` member `bits`, `union PacketHead`). Each byte's bits are
right now, but on a little-endian host the bytes themselves trade places.
That is byte order, and stays with the port.
