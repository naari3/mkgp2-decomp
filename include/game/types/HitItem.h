#ifndef GAME_TYPES_HITITEM_H
#define GAME_TYPES_HITITEM_H

#include "game/types/HitVec3.h"

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HitItem HitItem;
struct HitItem {
    /* 0x000 */ signed char state;
    /* 0x001 */ unsigned char pad_001[0x7];
    /* 0x008 */ int kind;
    /* 0x00C */ unsigned char pad_00C[0x10];
    /* 0x01C */ unsigned char kind_01C;
    /* 0x01D */ unsigned char pad_01D[0x83];
    /* 0x0A0 */ HitVec3 position;
    /* 0x0AC */ unsigned char pad_0AC[0x18];
    /* 0x0C4 */ float radiusScale;
};

#endif /* GAME_TYPES_HITITEM_H */
