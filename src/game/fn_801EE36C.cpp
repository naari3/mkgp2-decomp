/* Native candidate: 99.9135% text. Remaining differences are five
 * FP register operands in the transit interpolation.
 * The primary EH payload is exact; the extra weak Vec destructor is unowned. */
#include "game/PhysicsGroundPrivate.h"

extern "C" {
void KartBody_SetWarpTransitFlag(void *, int);
}

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

static inline float MovementInverseLength(const CollisionVec &v)
{
    return 1.0f / MovementLength(v);
}

static inline void ScaleTransit(CollisionVec &v, float scale)
{
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;
}

extern "C" void fn_801EE36C(PhysicsGroundState *self)
{
    if (self->forceTimer > 0) {
        CollisionVec delta(self->position.x, self->position.y, self->position.z);
        delta.x -= self->previous.x;
        delta.y -= self->previous.y;
        delta.z -= self->previous.z;
        float length = MovementLength(delta);
        if (length) {
            float scale = self->movementForce * MovementInverseLength(delta);
            delta.x *= scale;
            delta.y *= scale;
            delta.z *= scale;
            self->position.x = delta.x + self->position.x;
            self->position.y = delta.y + self->position.y;
            self->position.z = delta.z + self->position.z;
            --self->forceTimer;
            KartBody_SetWarpTransitFlag(self->body, 1);
            return;
        }
    } else if (0.0f < self->movementForce) {
        CollisionVec delta(self->position.x, self->position.y, self->position.z);
        delta.x -= self->previous.x;
        delta.y -= self->previous.y;
        delta.z -= self->previous.z;
        float length = MovementLength(delta);
        if (length) {
            float scale = self->movementForce * MovementInverseLength(delta);
            delta.x *= scale;
            delta.y *= scale;
            delta.z *= scale;
            self->position.x = delta.x + self->position.x;
            self->position.y = delta.y + self->position.y;
            self->position.z = delta.z + self->position.z;
            self->movementForce *= 0.8f;
            if (self->movementForce < 0.1f) self->movementForce = 0.0f;
        }
    }
    if (self->transitTimer > 0) {
        CollisionVec delta(self->position.x, self->position.y, self->position.z);
        delta.x -= self->previous.x;
        delta.y -= self->previous.y;
        delta.z -= self->previous.z;
        ScaleTransit(delta, 0.0125f * (float)self->transitTimer + 1.0f);
        self->position.x = delta.x + self->previous.x;
        self->position.y = delta.y + self->previous.y;
        self->position.z = delta.z + self->previous.z;
        --self->transitTimer;
        if (self->transitTimer <= 0) {
            self->transitMode = 0;
            self->transitTimer = 0;
        }
    } else if (self->transitMode != 0) {
        self->transitTimer = 120;
    }
    if (self->transitMode == 2) KartBody_SetWarpTransitFlag(self->body, 1);
    else KartBody_SetWarpTransitFlag(self->body, 0);
}
