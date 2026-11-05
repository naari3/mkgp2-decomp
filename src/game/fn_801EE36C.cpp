/* Native candidate: 99.81315% text. Remaining differences are two
 * square-root scratch slots and FP registers in the transit interpolation.
 * The primary EH payload is exact; the extra weak Vec destructor is unowned. */
#include "game/kartmove/collision_private.h"

extern "C" {
void KartBody_SetWarpTransitFlag(void *, int);
}

#define STEP_F(p, o) (*(float *)((char *)(p) + (o)))
#define STEP_I(p, o) (*(int *)((char *)(p) + (o)))
#define STEP_P(p, o) (*(void **)((char *)(p) + (o)))

template <class V> static inline float MovementLength(const V &v)
{
    float squared = (v.x * v.x + v.y * v.y) + v.z * v.z;
    if (squared > 0.0f) {
        double estimate = __frsqrte(squared);
        estimate = 0.5 * estimate * (3.0 - squared * (estimate * estimate));
        estimate = 0.5 * estimate * (3.0 - squared * (estimate * estimate));
        estimate = 0.5 * estimate * (3.0 - squared * (estimate * estimate));
        volatile float rounded = squared * estimate;
        return rounded;
    }
    return squared;
}

extern "C" void fn_801EE36C(char *self)
{
    if (STEP_I(self, 0x158) > 0) {
        CollisionVec delta(STEP_F(self, 0x4C), STEP_F(self, 0x50), STEP_F(self, 0x54));
        delta.x -= STEP_F(self, 0x58);
        delta.y -= STEP_F(self, 0x5C);
        delta.z -= STEP_F(self, 0x60);
        float length = MovementLength(delta);
        if (length) {
            float scale = STEP_F(self, 0x154) * (1.0f / MovementLength(delta));
            delta.x *= scale;
            delta.y *= scale;
            delta.z *= scale;
            STEP_F(self, 0x4C) = delta.x + STEP_F(self, 0x4C);
            STEP_F(self, 0x50) = delta.y + STEP_F(self, 0x50);
            STEP_F(self, 0x54) = delta.z + STEP_F(self, 0x54);
            --STEP_I(self, 0x158);
            KartBody_SetWarpTransitFlag(STEP_P(self, 0xC), 1);
            return;
        }
    } else if (0.0f < STEP_F(self, 0x154)) {
        CollisionVec delta(STEP_F(self, 0x4C), STEP_F(self, 0x50), STEP_F(self, 0x54));
        delta.x -= STEP_F(self, 0x58);
        delta.y -= STEP_F(self, 0x5C);
        delta.z -= STEP_F(self, 0x60);
        float length = MovementLength(delta);
        if (length) {
            float scale = STEP_F(self, 0x154) * (1.0f / MovementLength(delta));
            delta.x *= scale;
            delta.y *= scale;
            delta.z *= scale;
            STEP_F(self, 0x4C) = delta.x + STEP_F(self, 0x4C);
            STEP_F(self, 0x50) = delta.y + STEP_F(self, 0x50);
            STEP_F(self, 0x54) = delta.z + STEP_F(self, 0x54);
            STEP_F(self, 0x154) *= 0.8f;
            if (STEP_F(self, 0x154) < 0.1f) STEP_F(self, 0x154) = 0.0f;
        }
    }
    if (STEP_I(self, 0xC8) > 0) {
        float scale = 0.0125f * (float)STEP_I(self, 0xC8) + 1.0f;
        CollisionVec delta(STEP_F(self, 0x4C), STEP_F(self, 0x50), STEP_F(self, 0x54));
        delta.x -= STEP_F(self, 0x58);
        delta.y -= STEP_F(self, 0x5C);
        delta.z -= STEP_F(self, 0x60);
        delta.x *= scale;
        delta.y *= scale;
        delta.z *= scale;
        STEP_F(self, 0x4C) = delta.x + STEP_F(self, 0x58);
        STEP_F(self, 0x50) = delta.y + STEP_F(self, 0x5C);
        STEP_F(self, 0x54) = delta.z + STEP_F(self, 0x60);
        --STEP_I(self, 0xC8);
        if (STEP_I(self, 0xC8) <= 0) {
            STEP_I(self, 0xC4) = 0;
            STEP_I(self, 0xC8) = 0;
        }
    } else if (STEP_I(self, 0xC4) != 0) {
        STEP_I(self, 0xC8) = 120;
    }
    if (STEP_I(self, 0xC4) == 2) KartBody_SetWarpTransitFlag(STEP_P(self, 0xC), 1);
    else KartBody_SetWarpTransitFlag(STEP_P(self, 0xC), 0);
}
