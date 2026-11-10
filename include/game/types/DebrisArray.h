#ifndef GAME_TYPES_DEBRISARRAY_H
#define GAME_TYPES_DEBRISARRAY_H

#include "game/types/DebrisResponder.h"
#include "game/types/DebrisVec.h"

typedef struct DebrisArray {
    char pad00[0x78];
    void (*draw) (DebrisArray *);
    DebrisArray *drawSelf;
    char pad80[0xC];
    DebrisVec position;
    char pad98[0xC];
    DebrisVec velocity;
    float scale;
    signed char state;
    char padB5[0x14];
    signed char cleanup;
    char padCA[2];
    DebrisResponder *responder;
} DebrisArray;

#endif /* GAME_TYPES_DEBRISARRAY_H */
