#ifndef GAME_TYPES_CAMERA_H
#define GAME_TYPES_CAMERA_H
#include "game/types/arg_order.h"

struct Camera { char data[0x2C]; Camera ARGS_ORDER((float a, float b, int w, int h, int target), (int w, int h, int target, float a, float b)); };

#endif /* GAME_TYPES_CAMERA_H */
