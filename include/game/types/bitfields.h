#ifndef GAME_TYPES_BITFIELDS_H
#define GAME_TYPES_BITFIELDS_H

/* Bit-fields of one storage unit, in the order the game's compiler lays them
 * out: MWCC for PowerPC allocates from the most significant bit, most other
 * compilers (x86, ARM little-endian) from the least significant. The game
 * also reads the same storage as a whole integer (`(half >> 7) & 7` next to
 * `ids.id`), so the members have to land on the same bits everywhere.
 *
 *   BITFIELDS4(u16 local:1, u16 reserved:5, u16 id:3, u16 blocks:7)
 *
 * declares the members in this order under MWCC and in reverse order
 * elsewhere, which gives the storage unit the same integer value on both.
 * Each argument is a full declaration with its own type; each macro call is
 * exactly one storage unit (8, 16 or 32 bits).
 *
 *   BITFIELDS3_PAD(u16 :3, u16 a:7, u16 b:3, u16 c:3)
 *
 * is for a unit the members do not fill: the first argument is the unnamed
 * rest. MWCC does not see it (the source never had it); elsewhere it is
 * declared first, so that the reversed members start at the right bit.
 *
 * tools/bitfield_runs.py writes these (and `--check` lists bit-fields that
 * are still declared directly). This only fixes the bit order inside one
 * storage unit. The byte order of a multi-byte unit that is also viewed as
 * bytes, or sent on the wire, is a separate matter.
 */
#ifdef __MWERKS__
#define BITFIELDS1(a) a;
#define BITFIELDS2(a, b) a; b;
#define BITFIELDS3(a, b, c) a; b; c;
#define BITFIELDS4(a, b, c, d) a; b; c; d;
#define BITFIELDS5(a, b, c, d, e) a; b; c; d; e;
#define BITFIELDS6(a, b, c, d, e, f) a; b; c; d; e; f;
#define BITFIELDS7(a, b, c, d, e, f, g) a; b; c; d; e; f; g;
#define BITFIELDS8(a, b, c, d, e, f, g, h) a; b; c; d; e; f; g; h;
#define BITFIELDS1_PAD(pad, a) a;
#define BITFIELDS2_PAD(pad, a, b) a; b;
#define BITFIELDS3_PAD(pad, a, b, c) a; b; c;
#define BITFIELDS4_PAD(pad, a, b, c, d) a; b; c; d;
#define BITFIELDS5_PAD(pad, a, b, c, d, e) a; b; c; d; e;
#define BITFIELDS6_PAD(pad, a, b, c, d, e, f) a; b; c; d; e; f;
#define BITFIELDS7_PAD(pad, a, b, c, d, e, f, g) a; b; c; d; e; f; g;
#else
#define BITFIELDS1(a) a;
#define BITFIELDS2(a, b) b; a;
#define BITFIELDS3(a, b, c) c; b; a;
#define BITFIELDS4(a, b, c, d) d; c; b; a;
#define BITFIELDS5(a, b, c, d, e) e; d; c; b; a;
#define BITFIELDS6(a, b, c, d, e, f) f; e; d; c; b; a;
#define BITFIELDS7(a, b, c, d, e, f, g) g; f; e; d; c; b; a;
#define BITFIELDS8(a, b, c, d, e, f, g, h) h; g; f; e; d; c; b; a;
#define BITFIELDS1_PAD(pad, a) pad; a;
#define BITFIELDS2_PAD(pad, a, b) pad; b; a;
#define BITFIELDS3_PAD(pad, a, b, c) pad; c; b; a;
#define BITFIELDS4_PAD(pad, a, b, c, d) pad; d; c; b; a;
#define BITFIELDS5_PAD(pad, a, b, c, d, e) pad; e; d; c; b; a;
#define BITFIELDS6_PAD(pad, a, b, c, d, e, f) pad; f; e; d; c; b; a;
#define BITFIELDS7_PAD(pad, a, b, c, d, e, f, g) pad; g; f; e; d; c; b; a;
#endif

#endif
