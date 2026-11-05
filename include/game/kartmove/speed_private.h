#ifndef KARTMOVE_SPEED_PRIVATE_H
#define KARTMOVE_SPEED_PRIVATE_H
#include "game/KartMovement.h"
/* Private view for fields beyond the public position-only layout. */
typedef struct KartSpeedState {
    unsigned char pad0[0x17c];
    Vec3 velocity;
    unsigned char pad188[0x2e0-0x188];
    float coinBonus;
} KartSpeedState;
typedef struct KartForceState {
    unsigned char pad0[0x58];
    Vec3 forward;
    unsigned char pad64[0x1f8 - 0x64];
    Vec3 impulse;
} KartForceState;
extern const float lbl_806D96D0, lbl_806D96D4, lbl_806D96DC;
extern const double lbl_806D96E0, lbl_806D96E8;
#define KART_SPEED_ROOT(x) do { \
    volatile float y; \
    if ((x) > lbl_806D96D0) { \
        double g = __frsqrte(x); \
        g = lbl_806D96E0 * g * (lbl_806D96E8 - (x) * (g * g)); \
        g = lbl_806D96E0 * g * (lbl_806D96E8 - (x) * (g * g)); \
        g = lbl_806D96E0 * g * (lbl_806D96E8 - (x) * (g * g)); \
        y = (float)((x) * g); \
        (x) = y; \
    } \
} while (0)
#endif
