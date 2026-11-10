#ifndef GAME_TYPES_BOMBITEM_H
#define GAME_TYPES_BOMBITEM_H

#include "game/types/Vec.h"

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BombItem BombItem;
struct BombItem {
    /* 0x000 */ unsigned char pad_000[0xA0];
    /* 0x0A0 */ Vec pos;
    /* 0x0AC */ unsigned char pad_0AC[0x1C];
    /* 0x0C8 */ signed char state;
    /* 0x0C9 */ unsigned char pad_0C9[0x27];
    /* 0x0F0 */ unsigned int timers[4];
    /* 0x100 */ unsigned char pad_100[0x80];
    /* 0x180 */ void *owner;
    /* 0x184 */ void *driver;
    /* 0x188 */ unsigned char pad_188[0x4];
    /* 0x18C */ signed char armed;
    /* 0x18D */ unsigned char pad_18D[0x4F];
    /* 0x1DC */ unsigned char team;
    /* 0x1DD */ unsigned char pad_1DD[0x3];
    /* 0x1E0 */ unsigned int tag;
};

#endif /* GAME_TYPES_BOMBITEM_H */
