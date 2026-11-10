#ifndef GAME_TYPES_MARKERPATH_H
#define GAME_TYPES_MARKERPATH_H

#include "game/types/Vec3f.h"

typedef struct MarkerPath {
    Vec3f start;
    Vec3f trigger;
    Vec3f end;
} MarkerPath;

#endif /* GAME_TYPES_MARKERPATH_H */
