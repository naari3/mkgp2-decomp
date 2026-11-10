#ifndef GAME_TYPES_DEBRISARRAY_H
#define GAME_TYPES_DEBRISARRAY_H

#include "game/types/DebrisVec.h"

struct DebrisBlock;
struct DebrisResponder;

/* Merged from 4 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DebrisArray DebrisArray;
struct DebrisArray {
    /* 0x000 */ struct DebrisBlock *block;
    /* 0x004 */ unsigned char pad_004[0x74];
    /* 0x078 */ void (*draw) (DebrisArray *);
    /* 0x07C */ struct DebrisArray *drawSelf;
    /* 0x080 */ unsigned char pad_080[0xC];
    /* 0x08C */ DebrisVec position;
    /* 0x098 */ unsigned char pad_098[0xC];
    /* 0x0A4 */ DebrisVec velocity;
    /* 0x0B0 */ float scale;
    /* 0x0B4 */ signed char state;
    /* 0x0B5 */ unsigned char pad_0B5[0x14];
    /* 0x0C9 */ signed char cleanup;
    /* 0x0CA */ unsigned char pad_0CA[0x2];
    /* 0x0CC */ struct DebrisResponder *responder;
};

#endif /* GAME_TYPES_DEBRISARRAY_H */
