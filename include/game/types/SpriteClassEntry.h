#ifndef GAME_TYPES_SPRITECLASSENTRY_H
#define GAME_TYPES_SPRITECLASSENTRY_H

#include "game/types/SpriteAnimEntry.h"

typedef struct SpriteClassEntry {
    unsigned char pad0[4];
    SpriteAnimEntry *anims;
    unsigned char pad8[0xC];
} SpriteClassEntry;

#endif /* GAME_TYPES_SPRITECLASSENTRY_H */
