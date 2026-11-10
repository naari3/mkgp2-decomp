/* Native C++ candidate: 98.70982% text, exact owned EH.
 * Vector-length inline boundaries reproduce the target square-root FP homes.
 * Typed state and literal constants recover the damping/zero-load schedule.
 * The push helper snapshots all three input components before updating them.
 * Remaining differences: angle/offset and push FP allocation/scheduling.
 * The empty canonical vector destructor supplies compiler-generated cleanup.
 */
#include "game/KartPhysicsCollisionForcePrivate.h"

struct Vec3 {
    float x;
    float y;
    float z;

    inline void set(float ax, float ay, float az) volatile {
        x = ax;
        y = ay;
        z = az;
    }

    inline void copyFrom(volatile const Vec3 &other) volatile {
        x = other.x;
        y = other.y;
        z = other.z;
    }

};

extern "C" {
extern void PSVECScale(Vec3 *dst, Vec3 *src, float scale);

extern float lbl_806D1940;
extern float lbl_806D1944;
}

static inline float vector_length(const Vec3 &v) {
    float value = (v.x * v.x + v.y * v.y) + v.z * v.z;
    volatile float result;

    if (value > 0.0f) {
        double estimate = __frsqrte(value);
        estimate = 0.5 * estimate * (3.0 - value * (estimate * estimate));
        estimate = 0.5 * estimate * (3.0 - value * (estimate * estimate));
        estimate = 0.5 * estimate * (3.0 - value * (estimate * estimate));
        result = value * estimate;
        return result;
    }

    return value;
}

static inline void subtract_vector(Vec3 &dest, volatile const Vec3 &src) {
    float ax = src.x;
    float ay = src.y;
    float az = src.z;
    dest.x -= ax;
    dest.y -= ay;
    dest.z -= az;
}

static inline void set_scaled(volatile Vec3 &dest, float ax, float ay, float az, float factor) {
    dest.x = ax * factor;
    dest.y = ay * factor;
    dest.z = az * factor;
}

static inline void apply_push(CollisionForceState *self, volatile Vec3 &push) {
    float dx;
    float dy;
    float dz;
    float scale;
    int timer;
    dz = self->push.z;
    dy = self->push.y;
    dx = self->push.x;
    push.y = dy;
    push.x = dx;
    push.z = dz;

    if (self->airborne == 0) {
        /* Original damping is one ULP below 0.6f. */
        scale = 0.599999964f;
        dx *= scale;
        dy *= scale;
        dz *= scale;
        push.set(dx, dy, dz);

        timer = self->landingTimer;
        if (timer > 0) {
            scale = (float)(20 - timer) / 20.0f;
            set_scaled(push, dx, dy, dz, scale);
        }
    }

    subtract_vector(*(Vec3 *)&self->position, push);
}

#pragma exceptions on
extern "C" void KartPhysics_ApplyCollisionForce(CollisionForceState *self) {
    float dx;
    PhysicsCollisionVec offset;
    volatile Vec3 callVec;
    volatile Vec3 push;
    float len;
    float limit;
    float scale;
    float angleDelta;
    float dz;
    float dy;

    len = vector_length(*(Vec3 *)&self->impact);
    limit = lbl_806D1940;
    if (limit < len) {
        scale = limit / len;
        self->impact.x *= scale;
        self->impact.y *= scale;
        self->impact.z *= scale;
    }

    if (self->applyForce != 0) {
        self->position.x -= self->impact.x;
        self->position.y -= self->impact.y;
        self->position.z -= self->impact.z;
    }

    scale = 0.92f;
    self->impact.x *= scale;
    self->impact.y *= scale;
    self->impact.z *= scale;

    dx = self->position.x - self->previous.x;
    dy = self->position.y - self->previous.y;
    dz = self->position.z - self->previous.z;
    angleDelta = (float)__fabs(self->yaw - self->collisionYaw);
    offset.set(dx, dy, dz);

    if (0.0f < angleDelta) {
        callVec.set(dx, dy, dz);
        scale = 1.1f + angleDelta;
        PSVECScale((Vec3 *)&callVec, (Vec3 *)&callVec, (scale * scale) * 0.009f);
        self->push.x += callVec.x;
        self->push.y += callVec.y;
        self->push.z += callVec.z;
    }

    len = vector_length(*(Vec3 *)&self->push);
    limit = lbl_806D1944;
    if (limit < len) {
        scale = limit / len;
        self->push.x *= scale;
        self->push.y *= scale;
        self->push.z *= scale;
    }

    if (self->applyForce != 0) {
        apply_push(self, push);
    }

    scale = 0.88f;
    self->push.x *= scale;
    self->push.y *= scale;
    self->push.z *= scale;
}

#pragma exceptions reset
