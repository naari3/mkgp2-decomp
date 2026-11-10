#ifndef GAME_TYPES_LE_H
#define GAME_TYPES_LE_H

/* Values that are little-endian in a file the game reads.
 *
 * The game's CPU is big-endian and nearly all of its data is too, so it reads
 * that data directly. A few file values are little-endian instead (the size
 * word in front of a compressed file), and there the code swaps the bytes by
 * hand. On a little-endian host those are the values that need no conversion.
 *
 *   LE32(x), LE16(x)   x is little-endian in memory; gives its value.
 *                      Byte swap on a big-endian host, x elsewhere.
 *
 * NOT for the media-board code (BSWAP16/BSWAP32 in the triforce am* units,
 * the fd_set words in NamCam / TCPConn): those swaps stay real swaps on
 * every host. That code also compares the same fields against raw constants,
 * so it is only consistent when the swaps always happen; a port emulates the
 * media board as the mirror image. See docs/notes/byte_order.md.
 */
#if defined(__MWERKS__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define LE32(x) ((((x) >> 24) & 0xff) | (((x) >> 8) & 0xff00) | (((x) << 8) & 0xff0000) | ((x) << 24))
#define LE16(x) ((((x) << 8) & 0xFF00) | (((x) >> 8) & 0xFF))
#else
#define LE32(x) (x)
#define LE16(x) (x)
#endif

#endif
