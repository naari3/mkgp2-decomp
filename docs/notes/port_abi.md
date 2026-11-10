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
