#ifndef GAME_TYPES_GOALPLANE_H
#define GAME_TYPES_GOALPLANE_H

#include "game/types/Vec3.h"

typedef struct GoalPlane {
    Vec3 *point;
    Vec3 normal;
} GoalPlane;

#endif /* GAME_TYPES_GOALPLANE_H */
