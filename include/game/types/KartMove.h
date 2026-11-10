#ifndef GAME_TYPES_KARTMOVE_H
#define GAME_TYPES_KARTMOVE_H

#include "game/types/V3.h"

struct SpeedTable;

/* Merged from 5 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartMove KartMove;
struct KartMove {
    /* 0x000 */ unsigned char pad_000[0x8];
    /* 0x008 */ int table;
    /* 0x00C */ float progress;
    /* 0x010 */ unsigned char pad_010[0x12];
    /* 0x022 */ unsigned char limited;
    /* 0x023 */ unsigned char pad_023[0x1];
    /* 0x024 */ struct SpeedTable *tables;
    /* 0x028 */ unsigned char pad_028[0x18];
    /* 0x040 */ V3 pos;
    /* 0x04C */ V3 prevPos;
    /* 0x058 */ float mtx[16];
    /* 0x098 */ unsigned char pad_098[0x130];
    /* 0x1C8 */ float yaw;
};

#endif /* GAME_TYPES_KARTMOVE_H */
