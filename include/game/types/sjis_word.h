#ifndef GAME_TYPES_SJIS_WORD_H
#define GAME_TYPES_SJIS_WORD_H

/* Shift-JIS text held as a char string is tested and looked up two bytes at a
 * time: the word made of a lead byte and the byte after it (`& 0x8000` tells
 * a two-byte character, the word is compared with a character code). On the
 * console that is a plain 16-bit load. A little-endian host has to build the
 * word from the two bytes, so the reads go through these macros and a port
 * predefines them, for example
 *   #define SJIS_WORD(p) \
 *       ((unsigned short)(((const unsigned char *)(p))[0] << 8 | ((const unsigned char *)(p))[1]))
 *   #define SJIS_WORD_LOAD(dst, p) ((void)((dst) = SJIS_WORD(p)))
 * Not for text that is stored as 16-bit codes (card names, the NameCode
 * tables): those are read natively. Notes: docs/notes/port_abi.md. */
#ifndef SJIS_WORD
#define SJIS_WORD(p) (*(const unsigned short *)(p))
#endif
/* the same word copied into an unsigned short variable */
#ifndef SJIS_WORD_LOAD
#define SJIS_WORD_LOAD(dst, p) memcpy(&(dst), (p), 2)
#endif

#endif
