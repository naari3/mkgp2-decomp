#ifndef GAME_TYPES_FLASHPOINT_H
#define GAME_TYPES_FLASHPOINT_H

#include "game/types/Vec3f.h"

typedef struct FlashPoint {
    Vec3f pos;
    unsigned char used;
} FlashPoint;

#endif /* GAME_TYPES_FLASHPOINT_H */
