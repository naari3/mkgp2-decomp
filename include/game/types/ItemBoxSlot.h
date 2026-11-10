#ifndef GAME_TYPES_ITEMBOXSLOT_H
#define GAME_TYPES_ITEMBOXSLOT_H

#include "game/types/BoxShadow.h"
#include "game/types/Vec3f.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemBoxSlot ItemBoxSlot;
struct ItemBoxSlot {
    /* 0x000 */ unsigned char pad_000[0x4];
    /* 0x004 */ float peakY;
    /* 0x008 */ unsigned char pad_008[0x4];
    /* 0x00C */ Vec3f start;
    /* 0x018 */ Vec3f end;
    /* 0x024 */ Vec3f pos;
    /* 0x030 */ float rotX;
    /* 0x034 */ float rotY;
    /* 0x038 */ float rotZ;
    /* 0x03C */ float t;
    /* 0x040 */ int hidden;  /* also: delay */
    /* 0x044 */ unsigned char visible;
    /* 0x045 */ unsigned char pad_045[0x3];
    /* 0x048 */ BoxShadow shadows[10];
    /* 0x0E8 */ int cooldown;
    /* 0x0EC */ int randIdx;
};

#endif /* GAME_TYPES_ITEMBOXSLOT_H */
