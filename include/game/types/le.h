#ifndef GAME_TYPES_LE_H
#define GAME_TYPES_LE_H

/* Values that are little-endian where the game finds them.
 *
 * The game's CPU is big-endian and nearly all of its data is too, so it reads
 * that data directly. A few values are little-endian instead (the size word
 * in front of a compressed file, anything exchanged with the Triforce media
 * board's network stack), and there the code swaps the bytes by hand. On a
 * little-endian host those are the values that need no conversion.
 *
 *   LE32(x), LE16(x)          x is little-endian in memory; gives its value.
 *                             Byte swap on a big-endian host, x elsewhere.
 *   LE_AS_WRITTEN(swap, x)    the same, for a site whose swap expression has
 *                             to stay as written to keep MWCC's code: `swap`
 *                             on a big-endian host, x elsewhere.
 *
 * The conversion is its own inverse, so the same macros serve for writing a
 * little-endian value. Sites: docs/notes/byte_order.md.
 */
#if defined(__MWERKS__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define LE32(x) ((((x) >> 24) & 0xff) | (((x) >> 8) & 0xff00) | (((x) << 8) & 0xff0000) | ((x) << 24))
#define LE16(x) ((((x) << 8) & 0xFF00) | (((x) >> 8) & 0xFF))
#define LE_AS_WRITTEN(swap, x) (swap)
#else
#define LE32(x) (x)
#define LE16(x) (x)
#define LE_AS_WRITTEN(swap, x) (x)
#endif

#endif
