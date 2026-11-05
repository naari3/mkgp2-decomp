#ifndef GAME_AI_GP_SPEED_PRIVATE_H
#define GAME_AI_GP_SPEED_PRIVATE_H
#include "game/AISpeedPrivate.h"
typedef struct GPOwner { AISpeedOwner common; int field10, followDistance; } GPOwner;
typedef struct GPStatus { char pad[0x10]; unsigned long long flagsA, flagsB; } GPStatus;
typedef struct GPDriver {
    char pad[0x1F4]; int state; char pad1F8[0x44]; int rank;
    char pad240[0xC4]; GPStatus *status;
} GPDriver;
typedef struct GPSpeedParams { float normalDistance, normalA, normalB, retreatDistance, retreatA, retreatB, cooldown; } GPSpeedParams;
#endif
