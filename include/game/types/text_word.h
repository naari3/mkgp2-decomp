#ifndef GAME_TYPES_TEXT_WORD_H
#define GAME_TYPES_TEXT_WORD_H

/*
 * Four characters of text stored in a word of a word or pointer array.
 *
 * Some tables keep a file name or a label inline between pointers and
 * numbers, and the source describes the whole table as an array of words.
 * Written as a number (0x65665F73 for "ef_s") the text comes out reversed
 * on a little-endian host. TEXT_WORD gives the word whose bytes in memory
 * are a, b, c, d in that order: the same number as before under MWCC.
 *
 *   (void *)TEXT_WORD('e', 'f', '_', 's'), (void *)TEXT_WORD('.', 'd', 'a', 't'), ...
 *
 * tools/port_abi/text_words.py lists and rewrites such runs.
 * docs/notes/port_abi.md, "Text stored as words".
 */
#if defined(__MWERKS__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define TEXT_WORD(a, b, c, d) \
    (((unsigned int)(unsigned char)(a) << 24) | ((unsigned int)(unsigned char)(b) << 16) | \
     ((unsigned int)(unsigned char)(c) << 8) | (unsigned int)(unsigned char)(d))
#else
#define TEXT_WORD(a, b, c, d) \
    (((unsigned int)(unsigned char)(d) << 24) | ((unsigned int)(unsigned char)(c) << 16) | \
     ((unsigned int)(unsigned char)(b) << 8) | (unsigned int)(unsigned char)(a))
#endif

/*
 * HALF_WORDS(a, b): the word whose two 16-bit halves in memory are a, then
 * b, for a { short; short; } pair kept in a word or pointer array (the frame
 * of an animation key that sits behind a table of pointers in one object).
 */
#if defined(__MWERKS__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define HALF_WORDS(a, b) (((unsigned int)(unsigned short)(a) << 16) | (unsigned int)(unsigned short)(b))
#else
#define HALF_WORDS(a, b) (((unsigned int)(unsigned short)(b) << 16) | (unsigned int)(unsigned short)(a))
#endif

#endif
