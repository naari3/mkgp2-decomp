#ifndef GAME_TYPES_COINJUMPCAMERA_H
#define GAME_TYPES_COINJUMPCAMERA_H

#include "game/types/CoinJumpVec.h"

typedef struct CoinJumpCamera {
    char pad[0x80];
    CoinJumpVec position;
} CoinJumpCamera;

#endif /* GAME_TYPES_COINJUMPCAMERA_H */
