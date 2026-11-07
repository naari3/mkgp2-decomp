/* Native C++ candidate: 95.62054% text, exact owned EH.
 * Vector-length inline boundaries reproduce the target square-root FP homes.
 * Separate scaled-set and vector-subtraction helpers retain native snapshots.
 * Remaining differences: angle/offset and push FP allocation/scheduling.
 * The empty canonical vector destructor supplies compiler-generated cleanup.
 */
#include "game/PhysicsCollisionPrivate.h"

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

union IntToDouble {
    double d;
    struct {
        unsigned int hi;
        unsigned int lo;
    } w;
};

extern "C" {
extern void PSVECScale(Vec3 *dst, Vec3 *src, float scale);
extern void dtor_80036E40(void *ptr, short flag);

extern float lbl_806D1940;
extern float lbl_806D1944;
extern float lbl_806DA42C;
extern float lbl_806DA440;
extern double lbl_806DA458;
extern double lbl_806DA460;
extern float lbl_806DA4B0;
extern float lbl_806DA4B4;
extern float lbl_806DA4B8;
extern float lbl_806DA4BC;
extern float lbl_806DA4C0;
extern double lbl_806DA4C8;
}

#define F32(base, offset) (*(float *)((char *)(base) + (offset)))
#define U8(base, offset) (*(unsigned char *)((char *)(base) + (offset)))
#define S32(base, offset) (*(int *)((char *)(base) + (offset)))

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

#pragma exceptions on
extern "C" void KartPhysics_ApplyCollisionForce(void *self) {
    PhysicsCollisionVec offset;
    volatile Vec3 callVec;
    volatile Vec3 push;
    float len;
    float limit;
    float scale;
    float angleDelta;
    float dz;
    float dy;
    float dx;
    int timer;

    len = vector_length(*(Vec3 *)((char *)self + 0xd8));
    limit = lbl_806D1940;
    if (limit < len) {
        scale = limit / len;
        F32(self, 0xd8) *= scale;
        F32(self, 0xdc) *= scale;
        F32(self, 0xe0) *= scale;
    }

    if (U8(self, 0x64) != 0) {
        F32(self, 0x4c) -= F32(self, 0xd8);
        F32(self, 0x50) -= F32(self, 0xdc);
        F32(self, 0x54) -= F32(self, 0xe0);
    }

    scale = lbl_806DA4B0;
    F32(self, 0xd8) *= scale;
    F32(self, 0xdc) *= scale;
    F32(self, 0xe0) *= scale;

    angleDelta = (float)__fabs(F32(self, 0x7c) - F32(self, 0x84));
    dx = F32(self, 0x4c) - F32(self, 0x58);
    dy = F32(self, 0x50) - F32(self, 0x5c);
    dz = F32(self, 0x54) - F32(self, 0x60);
    offset.set(dx, dy, dz);

    if (lbl_806DA42C < angleDelta) {
        callVec.set(dx, dy, dz);
        scale = lbl_806DA4B4 + angleDelta;
        PSVECScale((Vec3 *)&callVec, (Vec3 *)&callVec, (scale * scale) * lbl_806DA4B8);
        F32(self, 0xcc) += callVec.x;
        F32(self, 0xd0) += callVec.y;
        F32(self, 0xd4) += callVec.z;
    }

    len = vector_length(*(Vec3 *)((char *)self + 0xcc));
    limit = lbl_806D1944;
    if (limit < len) {
        scale = limit / len;
        F32(self, 0xcc) *= scale;
        F32(self, 0xd0) *= scale;
        F32(self, 0xd4) *= scale;
    }

    if (U8(self, 0x64) != 0) {
        dy = F32(self, 0xd0);
        dz = F32(self, 0xd4);
        dx = F32(self, 0xcc);
        push.y = dy;
        push.x = dx;
        push.z = dz;

        if (U8(self, 0xa5) == 0) {
            scale = lbl_806DA440;
            dx *= scale;
            dy *= scale;
            dz *= scale;
            push.set(dx, dy, dz);

            timer = S32(self, 0xc0);
            if (timer > 0) {
                scale = (float)(20 - timer) / lbl_806DA4BC;
                set_scaled(push, dx, dy, dz, scale);
            }
        }

        subtract_vector(*(Vec3 *)((char *)self + 0x4c), push);
    }

    scale = lbl_806DA4C0;
    F32(self, 0xcc) *= scale;
    F32(self, 0xd0) *= scale;
    F32(self, 0xd4) *= scale;
}

#undef F32
#undef U8
#undef S32


#pragma exceptions reset
