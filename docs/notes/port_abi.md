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

Left open: `arity_census.py --all` also lists about 650 pairs where the call
passes *more* arguments than the definition takes. Most are harmless on
cdecl (wrappers with unused trailing arguments), but the list also holds the
reverse of the by-value case (a caller with a `Vec` by value, a definition
that takes the pointer, e.g. `SoundMgr_PlaySE_WithChannel`) and K&R
prototypes with `float` arguments. Not swept.

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
