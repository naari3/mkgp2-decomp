#ifndef GAME_GABYOU_ITEM_HAND_TRANSFORM_PRIVATE_H
#define GAME_GABYOU_ITEM_HAND_TRANSFORM_PRIVATE_H

/* Private ABI views for the hand-joint transform. */
#include "game/objview/item_state_private.h"
typedef struct HandDriver { unsigned char pad[0x1f8]; unsigned int kind; } HandDriver;
typedef struct GabyouHandItem {
    unsigned char pad0[0x2c]; float growth;
    unsigned char pad30[0x18]; float matrix[3][4];
    unsigned char pad78[0x28]; Vec3 position;
    unsigned char padac[0x18]; float scale;
    unsigned char padc8[0xbc]; HandDriver *driver;
} GabyouHandItem;

#endif
