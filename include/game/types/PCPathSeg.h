#ifndef GAME_TYPES_PCPATHSEG_H
#define GAME_TYPES_PCPATHSEG_H

#include "game/types/Vec3f.h"

typedef struct PCPathSeg {
    Vec3f a;
    Vec3f b;
    Vec3f c;
} PCPathSeg;

#endif /* GAME_TYPES_PCPATHSEG_H */
