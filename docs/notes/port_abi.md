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

### More int/float order cases (request 25, 2026-11-10)

`mkgp2-pc port/tools/arg_order_census.py` (declarations against definitions
in the port's LLVM IR) found five functions the sweep above had missed. Their
misordered prototypes got the same `Foo_Reordered` wrapper:
`fn_802090F0`, `InputCmd_PushSample`, `KartMovement_PhysicsStep` (in
auto_ONKARTHIT_block.c), `CarObject_ApplyInput` (eight units) and
`CarObject_ApplyDriftBoost` (three units).

`AnimState_Init(self, 0.0f)` in `AnimState_New` / `AnimState_Reset` was not
an order case: the definition takes `(AnimState *, AnimEntry *entries)`, and
the callers of `AnimState_New` / `AnimState_Reset` pass two arguments. The
second one went through r4 untouched. Both functions now have the parameter
and pass it on (same objects).

C++ names: a definition and a declaration with different parameter lists have
different mangled names and cannot link, unless
`tools/extab_user_renames.json` joins them; `tools/port_abi/rename_order.py`
checks exactly those (see "Constructors declared in another order").

### Arguments that pass through a wrapper (request 26, 2026-11-10)

A thin wrapper that forwards to another function needs no code for arguments
it does not touch, so several were written with too few parameters. The
port's argument-count census (mkgp2-pc docs/port/arg_count_census.txt) listed
52 callees; what they were:

- real, fixed with plain C that compiles to the same object:
  `EnemyRunType1_Init` / `EnemyRunType2_Init` (five constructor arguments
  forwarded to `EnemyRun_BaseInit`), `KartItem_ForwardToCarMovement_8019a4e0`
  (matrix pointer), `HUD_RegisterOverlay` (third argument to
  `HudManager::CreatePart`), `clEFaceModel::Trigger` (its `arg` goes to
  `clEFacePolyEffect::Start`, declared there as `FaceModelSub::Reset(int)`),
  `SoundDriver_GetOrCreate(GetCourseBgmEntry())` in DbgMenu.cpp,
  `TitleStats_MarkAllCoursesClearedIfDistance(t, score, self->timerB4)` (the
  float was still in f1 from the comparison just before), and
  `fn_801B7C1C` / `fn_801B7C40`, whose unused `int` parameter is gone.
- about 35 destructors "called with 1, take 2": every one is a C++
  destructor (`~T()`, `delete`, a member or base) joined to its C definition
  by `tools/extab_user_renames.json`. MWCC passes the hidden second argument
  (the delete flag) itself, so r4 is always set by the caller; there is
  nothing to write in the source. A host C++ compiler has no such argument:
  that belongs to the port's C++ ABI bridge.
- not real: `Clear`, `Next`, `Item_Explode`, `RankReached` and
  `ItemObject_GetGroundTypeAt` are different `static inline` functions that
  share a name across units.

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

## Static HSD descriptors (request 23, 2026-11-10)

The game defines a few HSD descriptors as static data and hands them to
`HSD_LObjLoadDesc` / `HSD_CObjLoadDesc`. Written as arrays of words
(`(void *)0xD0000, (void *)0x7F7F7F00` for `u16 flags = 0x000D; u16 attnflags
= 0; GXColor = {7F,7F,7F,00}`) they read wrongly on a little-endian host.
They are now structs from `include/game/types/hsd_desc.h` (`BuiltinWObjDesc`,
`BuiltinLightDesc`, `BuiltinCObjDesc`; melee's layouts, plain C types):

- `g_courseDataInstance` and its position (autodata/data_8040E780.c)
- the two-light chain behind `SceneModel_Init_data_803FDFF8`
  (autodata/data_803FDF50.c)
- `RenderTargetSingleton_data_8048EA78` and its second light
  (autodata/data_8048E548.c)
- `OrthoCam_data_8048E510` with its eye and interest (OrthoCam.c)

These are all the static descriptors passed to an HSD `LoadDesc` in game code;
the other calls pass descriptors read from files. Other tables that keep
16-bit or 8-bit fields inside pointer words exist (words such as
`(void *)0x10000` in "pointers mixed with values" objects); they are typed
when one is found to matter.

## Arguments left in a register for a library function

`mkgp2-pc port/tools/arity_census.py` cannot see callees in the library
directories. `python3 tools/port_abi/lib_arity.py` is a text scan for calls
from game code that pass fewer arguments than the library definition. It
found eight, all fixed with plain C that compiles to the same object:

- six `GetCourseDataPtr(); x = HSD_LObjLoadDesc();` pairs, now
  `HSD_LObjLoadDesc(GetCourseDataPtr())`;
- `Scene3D_GetCameraPos` and `Scene3D_SetupProjection` were defined with one
  parameter although every caller passes three; the two extra ones went
  straight through to `HSD_CObjGetPerspective` / `HSD_CObjSetPerspective`.
  They are parameters now.

## Card-name check (request 24, 2026-11-10)

`NameCheck_CardName.c` holds a name as `NameCode` (unsigned short) values,
one Shift-JIS character each, compares single codes as numbers
(`sHiragana`, `sKatakana`, ...) and searches whole strings with the byte
functions. Everything such a string is compared with must therefore be a
`NameCode` array written as 16-bit numbers; bytes, strings or 32-bit words
give another layout on a little-endian host. Retyped by
`tools/port_abi/namecode_fix.py` (same objects):

- the 1067 entries of `sBannedWords`: 532 in `NameCheck_CardName.c`
  (`NameCheck_CardName_rodata_*`, six codes each) and 532 in
  `autodata/sdata2_806D3060.c` (`lbl_806D3624` ..., four codes each);
- the delimiter patterns of `NameCheck_ScanBannedWords_data_8040E450` and
  `_8040E4B0` (`lbl_806D46E4` .. `lbl_806D473C`), `lbl_806D4740`,
  `lbl_806D4754`, `lbl_806D4758`.

This replaces the `TEXT_WORD` form request 21 gave the first group: that kept
the bytes in reading order, which is right for text read as bytes and wrong
for text read as 16-bit codes.

The byte functions themselves are called through `NAMECODE_STRCMP`,
`NAMECODE_STRNCMP`, `NAMECODE_STRSTR`, `NAMECODE_STRCPY`, `NAMECODE_STRCAT`
(`include/game/types/namecode_str.h`): the plain functions unless the build
defines them. On the console a code below 0x100 starts with a zero byte and
ends the byte string; a port that wants exactly that supplies versions working
on the big-endian byte view.

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

## Out parameters that receive more than one element

`Math_Segment2DIntersect(float *outT, float *outPos, ...)` writes three floats
through `outPos` (x, 0, z). `PathManager_UpdateAll` passed the address of a
single `float u`, so the callee wrote past it; on the console the frame happens
to have room, on a host the neighbouring local (`finish`) was overwritten. The
local is now `float u[3]` and is passed as `u`; MWCC lays the frame out the
same way, the object is unchanged.

`python3 tools/port_abi/out_vector.py` looks for the pattern: a callee that
indexes a pointer parameter beyond `[0]` (`p[N]`, `((float *)p)[N]`,
`(char *)p + N`) and a call that passes `&local` there with `local` a plain
scalar, or a scalar local cast to a struct pointer. It follows the
`Foo_Reordered` wrappers. It reports 0 after this change. It is text based and
does not see C++ member functions or callees that index through a copy of the
parameter.

## Definitions that take fewer parameters than their callers pass

MWCC leaves r4.. and f1.. alone when a function does not name them, so a
wrapper written with fewer parameters than its callers pass still delivers
the rest to whatever it calls. A host compiler passes nothing on. Two
definitions did that and now name and forward the arguments (same code):

- `clItemBoxResponder_CmdGetWorldPos(self, float *x, float *y, float *z)`
  calls `self->GetWorldPos(x, y, z)`.
- `fn_801E4524(self, unsigned long n, const void *value)`
  (`cdeque<DriveStep *>::resize`) calls `fn_801E435C(self, n, value)`.

`python3 tools/port_abi/forwarded_args.py` lists definitions that have a wider
prototype somewhere and whose body contains a member or pointer call, or a
call with fewer arguments than the callee takes; `-a` lists all 106
definitions with a wider prototype. The rest are harmless: empty hooks, stubs
and functions that ignore the extra arguments, and their calls inside pass
everything the callee takes. What it still prints:

- `ItemEffectDamp_TryArm`: its one caller casts to the five-parameter type;
  the virtual `Reset()` inside is declared without parameters.
- `fn_80157C60`, `fn_80157DE0`, `fn_80247C3C`: the fourth argument in the C
  prototypes is the hidden pointer for the returned struct, not a forwarded
  argument.

## Data defined with a narrower element than its users read

An object defined as bytes (or shorts) keeps the console's byte order when a
little-endian host compiles it; a user that reads it as short, int or float
then gets swapped values. `lbl_806D97E8` was six bytes read as three shorts
(voice ids). Each such object is now defined with the type it is read through,
values written as numbers of that type (MWCC output unchanged):

- `lbl_806D97E8`: `const short[3]`.
- twelve one-entry sprite resource lists passed to `SpriteGroup_CreateOrInit`
  (`int *resource`), e.g. `ResultFx_data_806CF688`: `int[1]`.
- twelve float-and-count records in autodata/rodata_80355078.c
  (`lbl_803551C8`.., `NokoNokoChallenge_GetCoinDivisor_rodata_80355630`..):
  `Rodata80355078_FloatInt`; two five-word records there: `Rodata80355078_Row5`.
- `Scene_8015BF18_rodata_80368C84`: `const int[6]`.

`python3 tools/port_abi/data_width.py --content` finds them: definitions with a
1- or 2-byte element whose `extern` declarations or pointer casts elsewhere
use a wider type, and byte arrays whose bytes look like big-endian words. It
reports 0 now. It does not see a byte pool that is read through a local
pointer plus offset (`strings + 0x4E8`) when the bytes at that offset look
like text. `lbl_802EB4E0` (declared `NamCamPool` by one user) is all text
bytes and stays `char`.

## Prototypes whose return class differs from the definition

A float result that the caller does not expect (or expects and does not get)
costs nothing on PowerPC; on 32-bit x86 it unbalances the x87 register stack
and later float loads give NaN. Fixed, all with unchanged objects:

- `fn_8019EA8C` returns float; KartMovement_PhysicsStep.cpp declared it void.
- `KartEffectFadeTransit_GetActiveValue` returns the timer in r3 (`lwz r3,
  24(r3)`); auto_ONKARTHIT_block.c declared it float, and
  `KartItem_AdvanceAnim3c`, which only passes that result on, was float too
  while its callers compare the result with 4. Both are `unsigned int` now.
- `Saturate_Double`: an inline-asm `extern void` list entry, now the real
  prototype.

`python3 tools/port_abi/return_class.py` compares every non-member definition
with all prototypes of the name and of its `name_pN` aliases (classes: float /
double, void, anything else) and reports 0. `-a` adds void against
integer/pointer (611 names; harmless for the calling convention). Not read:
prototypes inside class bodies, in src/game/autodata, and the
`extern void name();` lists of inline-asm blocks in files that also carry the
right prototype.

## Structs passed by value where the definition takes a pointer

MWCC passes a struct argument as the address of a copy the caller makes, so a
by-value call reaches a definition written with a pointer parameter and the
PowerPC code is the same as for a by-value definition. A host compiler pushes
the struct's bytes instead.

`StlList_RemoveByValueField` (auto_ONKARTHIT_block.c) was defined with
`StlListValRef *key` and called through a function-pointer cast with the key
by value. The definition now takes `StlListValRef key` (same code): both sides
are by value. The cast stays because the caller's key is a C++ class with a
constructor (`KartItemListKey`, same layout) and the C part of the unit cannot
name it.

`python3 tools/port_abi/byvalue_struct.py` compares function-pointer casts
applied to a function name, and prototypes (also `name_pN`), with the
definition, parameter by parameter. State on 2026-11-10: 369 places, 43
functions.

- One cast: Scene_8014E0C4.cpp calls `fn_80157D30` (returns `ListPos`, takes
  two `ListPos` by value) as `(ListIter *ret, List *, ListIter *, ListIter *)`.
- 316 prototypes of 38 functions pass a `Vec3`-like struct by value where the
  definition takes a pointer (`Mtx44_TransformVec3`, `ItemObject_GetGroundTypeAt`,
  `VfxSlot_SetPositionFromVec`, `Mtx44_Translate`, ...). The callers are right
  (they make the copy); the definitions were written with pointers.
- 52 prototypes of 5 functions do the reverse (`SoundMgr_PlaySE_Positional`
  takes `Vec pos` by value, many callers declare `Vec *pos` and copy by hand).

These stay as they are (decided 2026-11-10): the port drops `byval` on every
game definition, declaration and call in the host IR (mkgp2-pc
port/tools/mwcc_byvalue.py), so a struct argument is always the address of the
caller's copy, as under MWCC, and both spellings meet. The tool is a census
only.

## src/musyx on a host compiler

All 27 units pass the port's `compile_census.py musyx` (clang, gnu99) after
four declaration fixes, objects unchanged:

- `salInitDsp` is defined `bool salInitDsp(u32 flags)` as include/musyx/sal.h
  declares it; `salStartDsp` is static in hw_dolphin.c and no longer declared
  in sal.h.
- `extern VS vs;` in vsamples.h only for non-Dolphin targets (static in
  synth_vsamples.c on Dolphin).
- debugger.h includes `<stdint.h>` for `uintptr_t`.
- snd3d.c's own inline `sqrtf` is under `#ifdef __MWERKS__`.

## Shift-JIS text read two bytes at a time

Text held as a char string is decoded by loading 16 bits at the cursor
(`& 0x8000` for a two-byte character, then a comparison with a character
code). On a little-endian host the bytes arrive swapped. These reads use
`SJIS_WORD(p)` / `SJIS_WORD_LOAD(dst, p)` (include/game/types/sjis_word.h),
plain 16-bit loads by default, which a port predefines to build the word from
the two bytes:

- TexMgr_SetTexture.cpp: `LookupWide` and `DecodeText`.
- TitleNameHud_nm1.cpp: the character count of the title name.
- RankPanel_80144430.cpp: the title label loop (`memcpy(&ch, c, 2)` before).

Not changed, read natively on purpose: fn_801F9014.cpp (card name, already
unsigned short codes), the name entry in fn_801BAA88.cpp and the card pack /
unpack code (16-bit codes), and the display-list readers in
src/game/dlistutil (`*(unsigned short *)(p + 1)`: big-endian asset data, not
text).

## fn_8020A734: argument order by macro

`fn_8020A734` is `Tween::Set(float from, float to, short frames)`, reached
under its address name through the rename table. 23 prototypes (and about 280
calls in 46 files) are written `fn_8020A734(tween, frames, from, to)`. The
written order fixes MWCC's argument loads, so it stays; each prototype is
preceded by `#include "game/types/tween_set_order.h"`, whose macro (host
compilers only) reorders every prototype and call after it to
`(tween, from, to, frames)`. A function-like macro was chosen over the
`Foo_Reordered` wrapper because the first parameter's type differs from unit to
unit. A new unit that declares the function must include the header ahead of
its prototype.

## Library functions declared in another parameter order

`CObj_ProjectPoint` (CObjProject.c) declared `GXProject` with the pointers
first and the three floats last; the SDK takes `(x, y, z, mtx, pm, vp, sx, sy,
sz)`. The prototype and the call are now written in the SDK order (object
unchanged).

`python3 tools/port_abi/arg_class_order.py` compares every prototype with the
function's definition, or with its library header when there is no C
definition, by the sequence of parameter classes (float by value / other).
For functions of the SDK, MSL, HSD and MusyX it reports 0 after this change;
`-v` adds prototypes with another parameter count (20, none of them called
from game code with a float involved; most are MetroTRK and Melee headers);
`--all` adds functions defined in src/game, which the port's
arg_order_census.py covers (those are handled by ARGS_ORDER, `_Reordered`
wrappers or tween_set_order.h, which this text tool reads as written).

## GX stream data read on the CPU

Display lists and vertex buffers stay big-endian in a port (the GX layer
consumes them that way). The game's own readers, src/game/dlistutil (11 of
the 13 units) with DListBoundsPrivate.h, DListGeometryPrivate.h and
dlistutil_extract_private.h, go through include/game/types/gx_data.h:

- `GXDATA_U16(p)`: the vertex count of a primitive (`p + 1`, also in
  `CmdSize` for command 0x10) and a 16-bit vertex index in a display list;
- `GXDATA_SET_U16(p, v)`: `SetIndex` (fn_80182ED0.c, fn_801831F8.c);
- `GXDATA_F32(p)`: the three position floats of a vertex.

Plain loads and stores by default (objects unchanged); a port predefines them.
8-bit indices need nothing. Outside dlistutil the game only hands these
buffers to GX (`GXSetArray`, `GXCallDisplayList` in GXChannel_*.c). The HSD
library has one more CPU reader, the shape-animation path of
src/sysdolphin/baselib/pobj.c (`get_shape_vertex_xyz`, `get_shape_normal_xyz`,
`get_shape_nbt_xyz`, `interpretShapeAnimDisplayList`); it is not converted.

## Cabinet-link slot fields that cross a byte boundary

The link slot travels as bytes and is mostly read through byte views. Four
fields cross a byte boundary and are read or written through a 16- or 32-bit
view of the same bytes (a bit-field unit wider than a byte, or a shifted
word), which agrees with the byte views only on a big-endian machine. They go
through include/game/types/pcb_link.h, the plain expressions by default
(objects unchanged); the header gives the byte formula of each field.

| field | bytes | macros | used in |
|---|---|---|---|
| scene | header 1-2 | `PCB_HDR_SCENE(w)`, `PCB_HDR_SET_SCENE(h, v)` | PCBCheckRecv.c (13 reads), fn_801D1890.cpp, PCBCommBroadcast.c (write) |
| wins | class 0-1 (slot 6-7) | `PCB_CLASS_SET_WINS(c, v)`, `PCB_SLOT_WINS(s, field)` | PCBCommBroadcast.c, FaceEffect.cpp |
| track | choice 0-1 | `PCB_CHOICE_SET_TRACK(c, v)` | PCBCheckRecv.c |
| id | flags 0-1 | `PCB_FLAGS_ID(f, view)`, `PCB_FLAGS_SET_ID(f, view, v)`, `PCB_FLAGS16_ID(h)` | PCBCheckRecv.c, PCBCheckProcess.c |

The other bit-field units wider than a byte have no byte view next to them:
the sound slot flags in clsound/fn_801913B0.c are only read as the same word,
and the colour words in misc3d/fn_80167*.cpp, Scene_8014E0C4.cpp and
clFlowRound.c are declared but not used. Every other reader of the link slot
(18 units) uses byte views. `unsigned short name[6]` at slot offset 0x16 is
copied as 16-bit codes on both ends.

## Tables written as words whose readers take bytes

`(void *)0x8000000` in a `void *[]` table is the byte 8 and three padding
bytes on the console; on a little-endian host it is a word whose first byte
is 0. Such tables are defined with the struct their readers use.

AnimState descriptions (`AnimEntry { char type; pad[3]; void *data; }`,
include/game/types/AnimEntry.h, read by `AnimState_InitEntries`): six tables,
found and rewritten by `tools/port_abi/anim_tables.py`: `lbl_80422064`
(fn_80116DD0.c), `lbl_80421E34`, `lbl_80421EE8` (fn_801152B0.c),
`TwinSpriteOverlay_Update_data_8041A0E0` / `_8041A14C`
(autodata/data_80419FB8.c), `DbgMenu_data_8041C8A0` (autodata/data_8041A4F8.c).

`g_itemClassTable` (autodata/data_8041C9D4.c) was `void *[1390]` with words
like `(void *)0x1050000`; it is `ItemClassRow[278]` now (function pointer,
four flag bytes, a signed byte, a name pointer, the effect byte), matching the
members its readers use through `ItemClassEntry` (`def`, `flag0`, `flag1`) and
`ItemKindEntry` (`effect`).

### The sweep (request 38, part 3)

Tools, all listing only unless told to rewrite:

- `tools/port_abi/byte_words.py [-v]`: word arrays holding values such as
  `0x01000000` or `0x003C0000` (a byte or a 16-bit value at the top of a word).
- `tools/port_abi/word_readers.py`: word arrays that another unit declares
  with, or casts to, a type that is not made of words.
- `tools/port_abi/track_keys.py [--fix]`, `word_rows.py`, `word_bytes.py`: the
  rewrites (key tracks, rows of a hand-written struct, plain bytes).

Changed, object files unchanged unless noted:

| Data | Was | Is |
| --- | --- | --- |
| 504 joint animation tracks in JointTracks.cpp and DNStartDino_tail.cpp | `unsigned int[2n]`, frame in the top half of a word | `TrackKey[n]` (include/game/types/TrackKey.h) |
| `g_itemDescriptorTable` (autodata/data_8041A4F8.c) | `void *[1015]` | `ItemModelRow[203]`, `hasJoint` is a byte |
| `g_characterDataTable` (RaceScene_GetPerspFovyForCup.c) | `void *[165]` | `CharacterDataRow[15]`, byte at 0x20 |
| flash material of KartItem_FlushRender.c: image, image desc, TObj desc, two materials, two MObj descs | words | `Builtin*Desc` of hsd_desc.h; the 128x128 CMPR image is `unsigned char[0x2000]` |
| `lbl_80499F84`, `lbl_8049A010`, `lbl_8049A038` (sprite/fn_801A1798.c) | `unsigned int[]` | `lbl_80499F98_Row[]` like their neighbour |
| `lbl_80498158` (same file), `ParticleBurst_Draw_rodata_803292B4` | `unsigned int[5]` | `unsigned char[20]` |
| `s_defaultCourse` (CGameCoin_8012BF5C.cpp) | `unsigned int[5]` | a struct, `loseShellOnHit` is a byte |
| `CardRW_TestTopMenu_Page_data_803FDB18` (CardCreate_Page.cpp) | `void *[16]` | `CardRWTopStep[8]` |
| `CarObject_HandleItemEffect_data_803F75D0` | `unsigned int[7]` | `short[14]` |
| `lbl_80399E9C` (autodata/rodata_80399830.c) | `unk32[35]` | rows with the layout of `KeyGroup` |
| receipt text and 24x24 printer bitmaps in Sci2Card_BuildRetryReceiptLine.c (72 arrays) | `unsigned int[]` | `unsigned char[]` |
| 3 arrays and 14 single words of Shift-JIS text in autodata/sdata2_806D3060.c, sdata2_806D5658.c, sdata2_806DB6E0.c | `unk32` / `unsigned int` | `unsigned char[]` |
| `CourseScene_Load_data_803F5CE8` (CourseEnvironment.cpp) | kind/variant bytes as `(void *)0x1010000` | `(void *)TEXT_WORD(1, 1, 0, 0)` |
| "name    : " in autodata/rodata_8039D9A4.c | raw words | `TEXT_WORD` |

The image in KartItem_FlushRender.c held one word, 0x80606060, written as
`&KartItem_FlushRender_bss_80606060`: pixels that happen to look like an
address. As bytes the object no longer has that relocation (the only
difference in the object file; main.dol is the same).

Left as they are, with the reason:

- Floats and whole numbers stored in `void *` tables (most of the hits in
  autodata/rodata_80383CF8.c): a word is a word on both machines.
- `main_rodata_80328C94` (scene table, third word 0x10000 / 0x1000000),
  `RaceScene_GetPerspFovyForCup_data_8040B7AC` (0x01000000 in 7-word rows),
  `lbl_8041FF60` / `lbl_804203B4` (0xB0000): no C reader of those words, so the
  source does not say whether they are bytes, halves or a mask. Retype them
  when a reader is decompiled.
- Tables already written with `TEXT_WORD`, and tables another unit declares as
  `char[]` only to take their address.

## Data defined with one width and read with another (request 39, 2026-11-11)

`lbl_806D7F70` was `const int[2] = { 255, -65536 }` (autodata reads the type
off the values when no reader names one) and is read as two RGB triples; on a
little-endian machine black came out red. Checked after that:

- the port's list of 707 symbols whose definition and some `extern` disagree
  on element width (mkgp2-pc docs/port/data_width_census.txt);
- every autodata definition marked "element type read off the values" (128);
- every autodata definition whose `/* decl: */` comment names a reader type
  of another width (204);
- every definition whose readers declare a 64-bit type.

Changed (objects unchanged):

| Data | Was | Is |
| --- | --- | --- |
| `lbl_806D7F70` | `int[2]` | `unsigned char[8]` |
| 22 `ItemEffectMask` constants `lbl_806D34B8`..`lbl_806D3570` (sdata2_806D3060.c) | `int[2]`, `short[4]`, `unk32[2]` | `unsigned long long`, the type ItemEffectBus.c reads |
| 7 `GXColor` constants `lbl_806D28A8`..`lbl_806D28C4` (sdata2_806D2490.c) | `unsigned int` | `unsigned char[4]` |
| `KartDriver_InitFull_data_803F5928` | `unsigned int[30]` | `unsigned char[120]` |
| `clFlowKart_UpdateDisplay_data_8049BB30` | `short[60]` | `unsigned char[120]` (reader: `signed char[][13][3]`) |
| `lbl_80495988` (12 bytes copied into an HSD pixel-engine block) | `short[6]` | `unsigned char[12]` |
| `lbl_8039E9F8` | `short[12]` | a struct with the layout of `KartInfoEntry` (`int res` first) |

Declarations only: the banned words of NameCheck_CardName.c are declared
`const unsigned short[]` like their definitions (they are NameCode strings
compared through `NAMECODE_STRCMP`, see "Card-name check"; they stay 16-bit),
and four byte flags declared `unsigned int` for asm blocks are `unsigned char`.

Not a width problem, left alone: `extern char x[]` used only to take an
address (most of the list); int tables handed to `SpriteGroup_CreateOrInit`
(`int *resource`); the NokoNoko coin tables; pools of ints or floats that a
reader holds as `char *` and casts back.

Float pools: none of the float-typed pools has text or bytes inside the
object itself. But ten readers go past the end of the pool object with a
constant offset and land in the objects that follow it (strings, tables):
`DNBress_nm3_rodata_803C6ED0`, `FinalLapBanner_Init_rodata_803123B0`,
`GabyouItem_BuildOrUpdateAttachTransform_rodata_8032D9C8`,
`ItemObject_Tick_rodata_8032E060`, `KartAlertPanel_rodata_803F0AD8`,
`KartFxExhaustRay_rodata_80329E20`, `RaceScene_rodata_803211D8`,
`RankLog_rodata_80324B98`, `lbl_803311D0`, `lbl_8039C718`. That is the
"object addressed from another object's name plus an offset" case of
shared_data.md: right only while the objects keep the original order and
spacing.

## Tail padding of base classes (request 40, 2026-11-11)

MWCC starts the members of a derived class at `sizeof(base)`. clang (Itanium
C++ ABI) starts them at the end of the base's data when the base is not a
plain struct (virtual functions, a constructor), so a base ending in one or
two bytes loses its padding to the first small member of the derived class:
`PanelIcon::resId` sat at 0x86 on the host and at 0x88 in the game, and code
that fills the object through a flat view wrote the wrong place.

The padding is now a member of the base (`unsigned char pad86[2];` and the
like; nothing changes for MWCC): `PanelItem` (RankPanel_80144430.cpp),
`FadeObj` (fn_801BAA88.cpp, anon_8021F088_private.h, anon_8021BC44Types.h),
`clGetCoinLine`, `clFlowCCInterface` (both headers), `SceneRoot163`, `JobTask`
(types/JobTask.h) and the `SceneBase` copies that end in `done`.

`tools/port_abi/tail_padding.py` lists the cases over every game .cpp from
clang's record layouts; it reports none after this change. A new class with
virtual functions that ends in a `char`, `bool` or `short` and is derived from
needs the same member.

## Library prototypes (request 41, 2026-11-11)

Sixteen units declared `atan2`, `atan` and `tan` with `float` parameters. On
PowerPC a float and a double argument use the same register, so the objects
are the same either way; a 32-bit x86 caller pushes 4 bytes where libm reads
8, and every yaw and pitch computed that way was garbage. All declarations of
C library functions in src/game and include/game now have the standard
parameter and return types (`double atan2(double, double)`,
`unsigned long strlen(const char *)`, `void *memset(void *, int, unsigned long)`,
`int snprintf(char *, unsigned long, const char *, ...)` and so on); no
object changed.

`tools/port_abi/libc_decls.py [--fix]` lists and rewrites them. It does not
compare pointer types with each other and leaves the `wcs*` functions alone.
Left: src/game/Rand.c declares `unsigned short rand(void)`; with `int` the
object changes (the truncation is how the original was written), and the low
16 bits of the result are the same on the host.

## Tables reached only through another table's pointer (request 42, 2026-11-11)

The earlier sweeps looked for a function that reads a table as bytes. A table
whose only reader gets it through a pointer stored in a second table was
missed, because no function names it. The ZoneObject lists were the case that
showed on the PC build (decoration loop ended on the first entry).

Changed, all byte-identical under MWCC:

- `src/game/autodata/data_803F60B4.c`: 32 lists are now
  `ZoneObjectRow x[] = { { kind, variant, slot, filename, jointName }, ... }`
  (`signed char kind, variant; short slot;`). The two objects that hold both
  ZoneObject lists and the CourseZone tables that point at them
  (`lbl_803F63F0`, `lbl_803F6FE8`) stay `void *` arrays with the header word
  written as `(void *)TEXT_WORD(kind, variant, 0xFF, 0xFF)`; the terminator
  word stays `0xFFFFFFFF` and the CourseZone `int` kinds stay plain numbers.
  All of them are still writable data.
- `src/game/autodata/data_8041EEC0.c`: shell pile configuration blocks
  (readers `ShellPile_Spawn.c`, `ShellPilePiece_Tick.c` take a name string at
  +1 and bytes at +0x80..0x82): 12 words to `TEXT_WORD`.
- `JointTracks_rodata_803EB3DC`, `DNStartDino_tail_rodata_803D6850`: nine
  track pointers followed by six inline keys. The key frames are 16-bit, so
  they use the new `HALF_WORDS(a, b)` in `include/game/types/text_word.h`
  (the word whose two 16-bit halves in memory are a, then b).
- `ConfettiField_rodata_80360520`: six colours read through a
  `{ r, g, b, a }` byte union, now `TEXT_WORD(r, g, b, a)`.
- `lbl_8036BF90` (fn_80167C60.cpp) and three words of
  `sdata_806CF750_rodata_8036A308` (Scene_801661FC.cpp): format string text
  that was still raw words.

How the search was done: every word table in `src/game` (arrays of
`void *`, `int`, `unsigned int`) was scanned for words that are not an
address, a small integer, a float in a plausible range, zero or all ones;
what is left is a word with several meaningful bytes. Fifteen tables came
out; the ones above were real.

Looked at and left alone:

- `RaceScene_GetPerspFovyForCup_data_8040B7AC` (one word `0x01000000`): no C
  reader names it, so its width is unknown.
- `lbl_803C2DE8`, `lbl_803C2E04`, `lbl_806D4E00`: read as whole words.
- Unions of a word and four bytes also exist in `PCBCheckRecv.c` and
  `clFlowRound.c`; their words come from the media board or from code, not
  from a table in the source.

Limit of the search: a table whose packed bytes are all small (for example
`{ 0, 0, 0, 1 }` as one word `1`) looks the same as an integer and cannot be
found from the values alone. Those can only be found from the reader, and a
reader that takes the table through an untyped pointer in another table gives
no type to follow.

## Out-pointer arguments smaller than what the callee writes (request 43, 2026-11-11)

`Terrain_GetGroundHeightWithPenetration` writes a three-float normal through
its third argument when it is not null. `ItemObject_GetGroundTypeAt`
(`ItemObject_GetGroundTypeAt.c`, and the inline copy in
`ItemObjectManager_RenderImpl.c`) passes the address of its own third `int`
parameter. Under MWCC the other eight bytes land in stack space nothing else
uses. Under clang on x86 they overwrote the caller's saved ground height
(item shadows ten times too large and black, item heights NaN).

Both places now give the callee a `float normal[3]` under `#ifndef
__MWERKS__`; the MWCC branch is the old text, objects unchanged.

Other callers checked by hand: every non-null out-normal / out-position
argument of `Terrain_GetGroundHeightWithPenetration`, `Terrain_GetGroundHeight`
and `Terrain_RaycastWall` (and of `ItemObject_RaycastWallStub`) is a
three-float vector (`KartController_Update.cpp`, `kartmove/fn_8019C15C.cpp`,
`NokoNoko_Update.c`, `JumpDistanceMode_*.c`, `PhysicsState_WallCollisionCheck.cpp`,
`AI_CalcRivalAvoidance.cpp`, `RivalRun.c`, `SuikaBallObj_UpdatePhysics.c`,
`kartmove/KartMovement_CollisionUpdate.cpp`, `ItemHoming.c`, `ItemMotion.c`,
`BombExplosion_UpdateShockwaveVfx.c`). The callers of
`ItemObject_GetGroundTypeAt` pass 0 or a pointer as the third argument; the
function never reads it.

`tools/port_abi/param_address.py` lists calls that pass `&scalar` where the
callee's definition (not the caller's own extern, which is often written to
suit the caller) takes a pointer to another type. It is text based. On the
tree at this commit it prints 71 lines: the two calls above (MWCC branch),
46 `float` passed as `void *`, signedness differences, and the rest are
local names that the tool confuses across functions of one file
(`Item_AdvanceFallingDrop` wrappers that reorder arguments, `Scene_8014E0C4.cpp`
iterators) or one-pointer struct returns (`RaceDigitLap.cpp`). Nothing else
writes past its target. Not covered: addresses of struct members and of
array elements.
