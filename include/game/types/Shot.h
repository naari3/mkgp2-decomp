#ifndef GAME_TYPES_SHOT_H
#define GAME_TYPES_SHOT_H

#include "game/types/Trail.h"
#include "game/types/Vec3.h"

typedef struct Shot {
    char pad0[0x14];
    int active;
    char pad18[4];
    int timer;
    Vec3 pos;
    Vec3 vel;
    float rot;
    float alpha;
    Trail trail[18];
    char pad160[0xc];
} Shot;

#endif /* GAME_TYPES_SHOT_H */
