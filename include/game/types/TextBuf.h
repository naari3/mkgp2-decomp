#ifndef GAME_TYPES_TEXTBUF_H
#define GAME_TYPES_TEXTBUF_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TextBuf TextBuf;
struct TextBuf {
    /* 0x000 */ char c[256];
};

#endif /* GAME_TYPES_TEXTBUF_H */
