#ifndef GAME_TYPES_CARDTEXTLINE_H
#define GAME_TYPES_CARDTEXTLINE_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CardTextLine CardTextLine;
struct CardTextLine {
    /* 0x000 */ float x;
    /* 0x004 */ float y;
    /* 0x008 */ char *format;
    /* 0x00C */ int font;
    /* 0x010 */ int r;
    /* 0x014 */ int g;
    /* 0x018 */ int b;
    /* 0x01C */ int a;
};

#endif /* GAME_TYPES_CARDTEXTLINE_H */
