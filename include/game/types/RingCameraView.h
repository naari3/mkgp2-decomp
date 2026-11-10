#ifndef GAME_TYPES_RINGCAMERAVIEW_H
#define GAME_TYPES_RINGCAMERAVIEW_H

#include "game/types/Vec3.h"

typedef struct RingCameraView {
    unsigned char pad00[0x80];
    Vec3 position;
} RingCameraView;

#endif /* GAME_TYPES_RINGCAMERAVIEW_H */
