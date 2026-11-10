#ifndef GAME_TYPES_EMBER_H
#define GAME_TYPES_EMBER_H

#include "game/types/Vec3f.h"

typedef struct Ember {
    unsigned char active;
    Vec3f pos;
    Vec3f vel;
    int color;
    float speed;
    float scale;
    float alpha;
    Vec3f accel;
} Ember;

#endif /* GAME_TYPES_EMBER_H */
