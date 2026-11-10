#ifndef GAME_TYPES_CAMERAVIEW_H
#define GAME_TYPES_CAMERAVIEW_H

#include "game/types/Vec.h"

typedef struct CameraView {
    unsigned char pad0[0x80];
    Vec eye;
} CameraView;

#endif /* GAME_TYPES_CAMERAVIEW_H */
