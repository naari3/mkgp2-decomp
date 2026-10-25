#include "game/MathInline.h"

struct Vec {
    float x, y, z;
    Vec(float px, float py, float pz) : x(px), y(py), z(pz) {}
    ~Vec() {}
};

struct V3 {
    float x, y, z;
};

struct KartMove {
    unsigned char pad0[0x40];
    V3 pos;
    V3 prevPos;
    float mtx[16];
    unsigned char pad98[0x1c8 - 0x98];
    float yaw;
};

extern "C" {
extern double atan2(double y, double x);
}

static inline void SetV3(V3 *d, float x, float y, float z) {
    d->x = x;
    d->y = y;
    d->z = z;
}

extern "C" void fn_8019A4E0(KartMove *k, float *m) {
    int i;
    k->prevPos.x = k->pos.x;
    k->prevPos.y = k->pos.y;
    k->prevPos.z = k->pos.z;
    for (i = 0; i < 16; i++) {
        k->mtx[i] = m[i];
    }
    SetV3(&k->pos, m[12], m[13], m[14]);
    Vec dir(k->mtx[8], 0.0f, k->mtx[10]);
    float len = MathInline_sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (len <= 0.0f) {
        dir.z = 0.0f;
        dir.y = 0.0f;
        dir.x = 0.0f;
    } else {
        float inv = 1.0f / len;
        dir.x *= inv;
        dir.y *= inv;
        dir.z *= inv;
    }
    k->yaw = 57.29577951308232 * (float)atan2(dir.x, dir.z);
}
