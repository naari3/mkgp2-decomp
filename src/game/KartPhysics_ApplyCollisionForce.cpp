/*
 * NonMatching C++ reconstruction of KartPhysics_ApplyCollisionForce.
 *
 * Current best probe (CW1.3.2, game lib):
 * - Text size and instruction count reach the target shape (0x380 / 224 insns).
 * - Manual extab/extabindex match 100%; cleanup metadata still points at
 *   dtor_80036E40 for the stack local at 0x28(SP).
 * - Stack locals can be made to line up with the target:
 *     push    = 0x10(SP)
 *     callVec = 0x1C(SP)
 *     offset  = 0x28(SP)  (the cleanup local)
 *     int-to-double cookie = 0x38(SP)
 * - The int-to-double conversion can be made to resolve through lbl_806DA4C8
 *   instead of a fresh local .sdata2 constant.
 *
 * Remaining mismatch is mostly register allocation and scheduling, not control
 * flow:
 * - fast_sqrtf receives the squared magnitude in f2 in the current output,
 *   while the target keeps it in f4; forcing locals/register hints caused f31
 *   saves or frame changes, so that path was worse.
 * - The angle/offset block still differs in f3/f4/f5/f6 allocation and in the
 *   order around lfs lbl_806DA4B8 / stfs callVec.
 * - The push block is close, but x/y live values still tend to occupy f4/f5 in
 *   the opposite order from the target; declaration-order experiments did not
 *   move CW's allocator enough.
 *
 * Useful failed probes:
 * - A plain C version matched behavior and extab but only reached ~81.25% and
 *   either shrank the frame or over-constrained stack traffic with volatile.
 * - Making the Vec3 dtor non-trivial emitted extra weak destructor text.
 * - Hoisting a reusable zero/sum local for fast_sqrtf caused f31 save/restore
 *   and a 0x60-byte frame.
 *
 * Next promising route: use this file as a decomp.me scratch and tune the
 * angle/offset and push blocks independently. Keep avoiding inline asm; the
 * remaining problem is small enough to search with source-level lifetime and
 * declaration-order changes.
 */

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
extern void fn_8025E2AC(Vec3 *dst, Vec3 *src, float scale);
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

static inline float fast_sqrtf(float value) {
    volatile float result;

    if (value > lbl_806DA42C) {
        double estimate = __frsqrte(value);
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - value * (estimate * estimate));
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - value * (estimate * estimate));
        estimate = lbl_806DA458 * estimate * (lbl_806DA460 - value * (estimate * estimate));
        result = value * estimate;
        return result;
    }

    return value;
}

extern "C" void KartPhysics_ApplyCollisionForce(void *self) {
    volatile Vec3 offset;
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

    len = fast_sqrtf(F32(self, 0xd8) * F32(self, 0xd8) + F32(self, 0xdc) * F32(self, 0xdc) +
                     F32(self, 0xe0) * F32(self, 0xe0));
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
        fn_8025E2AC((Vec3 *)&callVec, (Vec3 *)&callVec, (scale * scale) * lbl_806DA4B8);
        F32(self, 0xcc) += callVec.x;
        F32(self, 0xd0) += callVec.y;
        F32(self, 0xd4) += callVec.z;
    }

    len = fast_sqrtf(F32(self, 0xcc) * F32(self, 0xcc) + F32(self, 0xd0) * F32(self, 0xd0) +
                     F32(self, 0xd4) * F32(self, 0xd4));
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
            push.x = dx;
            push.y = dy;
            push.z = dz;

            timer = S32(self, 0xc0);
            if (timer > 0) {
                scale = (float)(20 - timer) / lbl_806DA4BC;
                dx *= scale;
                dy *= scale;
                dz *= scale;
                push.x = dx;
                push.y = dy;
                push.z = dz;
            }
        }

        F32(self, 0x4c) -= push.x;
        F32(self, 0x50) -= push.y;
        F32(self, 0x54) -= push.z;
    }

    scale = lbl_806DA4C0;
    F32(self, 0xcc) *= scale;
    F32(self, 0xd0) *= scale;
    F32(self, 0xd4) *= scale;
}

#undef F32
#undef U8
#undef S32

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_KartPhysics_ApplyCollisionForce = {
    0x080A0000, 0x000001A0, 0x00000010, 0x00000000, 0x82000028, (void *)&dtor_80036E40
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_KartPhysics_ApplyCollisionForce = {
    (void *)&KartPhysics_ApplyCollisionForce, 0x00000380, (void *)&extab_KartPhysics_ApplyCollisionForce
};
