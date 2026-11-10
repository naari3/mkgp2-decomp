#ifndef GAME_TYPES_SPRITEANIM_H
#define GAME_TYPES_SPRITEANIM_H

#include "game/types/SpriteAnimData.h"

typedef struct SpriteAnim {
    unsigned char flag;
    unsigned char pad1[7];
    float time;
    float c[6];
    const char *name;
    SpriteAnimData *data;
} SpriteAnim;

#endif /* GAME_TYPES_SPRITEANIM_H */
