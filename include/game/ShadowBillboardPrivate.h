#ifndef GAME_SHADOW_BILLBOARD_PRIVATE_H
#define GAME_SHADOW_BILLBOARD_PRIVATE_H

#include "game/MathInline.h"

#include "game/types/PCPathSeg.h"

typedef struct LineCamCObj {
    unsigned char pad00[0x8];
    unsigned int flags; /* 0x08 */
} LineCamCObj;

typedef struct LineCam {
    unsigned char pad00[0x4];
    LineCamCObj *cobj; /* 0x04 */
} LineCam;

#endif
