#ifndef GAME_TYPES_RACECAMERA_H
#define GAME_TYPES_RACECAMERA_H
#include "game/types/arg_order.h"

struct RaceCamera {
    unsigned char data[0x2C];
    RaceCamera ARGS_ORDER((float fovy, int width, float aspect, int height, void *renderTarget), (int width, int height, void *renderTarget, float fovy, float aspect));
};

#endif /* GAME_TYPES_RACECAMERA_H */
