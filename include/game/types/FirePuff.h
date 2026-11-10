#ifndef GAME_TYPES_FIREPUFF_H
#define GAME_TYPES_FIREPUFF_H

#include "game/types/Vec3f.h"

typedef struct FirePuff {
    unsigned char active;
    Vec3f vel;
    Vec3f pos;
    float scale;
    float alpha;
    float speed;
    float dscale;
    float pad2c;
    float lift;
    float pad34;
    float fade;
} FirePuff;

#endif /* GAME_TYPES_FIREPUFF_H */
