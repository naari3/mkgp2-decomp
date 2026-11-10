#ifndef GAME_TYPES_HANDHELDPOSE_H
#define GAME_TYPES_HANDHELDPOSE_H

#include "game/types/Vec.h"

typedef struct HandheldPose {
    int pad;
    float scale;
    Vec ofs;
    Vec rot;
} HandheldPose;

#endif /* GAME_TYPES_HANDHELDPOSE_H */
