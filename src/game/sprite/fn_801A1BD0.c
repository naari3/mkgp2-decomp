typedef struct Seg {
    float x1;
    float z1;
    float x2;
    float z2;
} Seg;

typedef struct KartRef {
    unsigned char pad0[0x44];
    void *render;
    float prevX;
    float prevZ;
} KartRef;

extern float *KartDriver_GetKartRootMtx(void *r);

#define IN_RANGE(v, den) (((den) > 0.0f && 0.0f <= (v) && (v) <= (den)) || ((den) < 0.0f && (den) <= (v) && (v) <= 0.0f))

int fn_801A1BD0(Seg *s, KartRef *k) {
    float *m = KartDriver_GetKartRootMtx(k->render);
    float px = m[3];
    float pz = m[11];
    float qx = k->prevX;
    float qz = k->prevZ;
    float sx, dx, sz, dz, den, ox, oz, t, u;

    if (s->x1 == s->x2 && s->z1 == s->z2) {
        return 0;
    }
    if (px == qx && pz == qz) {
        return 0;
    }
    dx = qx - px;
    sx = s->x2 - s->x1;
    dz = qz - pz;
    sz = s->z2 - s->z1;
    den = sx * dz - dx * sz;
    if (0.0f == den) {
        return 0;
    }
    ox = s->x1 - px;
    oz = s->z1 - pz;
    t = sx * oz - sz * ox;
    u = dx * oz - dz * ox;
    if (IN_RANGE(u, den)) {
        if (IN_RANGE(t, den)) {
            return 1;
        }
    }
    return 0;
}
