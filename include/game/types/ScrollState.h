#ifndef GAME_TYPES_SCROLLSTATE_H
#define GAME_TYPES_SCROLLSTATE_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ScrollState ScrollState;
struct ScrollState {
    /* 0x000 */ float x;
    /* 0x004 */ float y;
    /* 0x008 */ unsigned char pad_008[0x8];
    /* 0x010 */ float speed;
    /* 0x014 */ unsigned char pad_014[0x1C];
    /* 0x030 */ float velX;
    /* 0x034 */ float velY;
};

#endif /* GAME_TYPES_SCROLLSTATE_H */
