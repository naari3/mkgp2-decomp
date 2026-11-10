#ifndef GAME_TYPES_WARPZONEVALUE_H
#define GAME_TYPES_WARPZONEVALUE_H

#include "game/types/WarpCorner.h"
#include "game/types/WarpPlainVector.h"

typedef struct WarpZoneValue {
    unsigned long flags;
    WarpCorner corners[4];
    WarpPlainVector vector1;
    WarpPlainVector vector2;
    float distance;
} WarpZoneValue;

#endif /* GAME_TYPES_WARPZONEVALUE_H */
