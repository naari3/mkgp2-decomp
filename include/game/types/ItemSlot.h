#ifndef GAME_TYPES_ITEMSLOT_H
#define GAME_TYPES_ITEMSLOT_H

#include "game/types/Vec3.h"

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemSlot ItemSlot;
struct ItemSlot {
    /* 0x000 */ signed char active;
    /* 0x001 */ unsigned char pad_001[0x13];
    /* 0x014 */ unsigned char sprite[0x14];
    /* 0x028 */ signed char shadow;
    /* 0x029 */ unsigned char pad_029[0x3];
    /* 0x02C */ float alpha;
    /* 0x030 */ unsigned char pad_030[0xC];
    /* 0x03C */ signed char shadowEnabled;
    /* 0x03D */ unsigned char pad_03D[0x3B];
    /* 0x078 */ void (*draw) (void *arg);
    /* 0x07C */ void *drawArg;
    /* 0x080 */ unsigned char pad_080[0x4C];
    /* 0x0CC */ Vec3 pos;
    /* 0x0D8 */ float radius;
    /* 0x0DC */ signed char visible;
    /* 0x0DD */ unsigned char pad_0DD[0x10F];
};

#endif /* GAME_TYPES_ITEMSLOT_H */
