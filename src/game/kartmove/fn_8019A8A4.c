typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct Kart {
    unsigned char pad0[0x40];
    Vec3 pos;
    unsigned char pad4c[0x68 - 0x4c];
    Vec3 up;
    unsigned char pad74[0x17c - 0x74];
    Vec3 vel;
    unsigned char pad188[0x194 - 0x188];
    Vec3 x194;
    unsigned char pad1a0[0x254 - 0x1a0];
    unsigned char ground[4];
    unsigned char pad258[0x298 - 0x258];
    Vec3 x298;
    unsigned char pad2a4[0x2a8 - 0x2a4];
    float x2a8;
    unsigned char pad2ac[4];
    Vec3 x2b0;
    unsigned char x2bc;
} Kart;

extern const float lbl_806D96D0;
extern const float lbl_806D96D4;
extern const float lbl_806D9700;

static inline void VecSet(Vec3 *d, float x, float y, float z) {
    d->x = x;
    d->y = y;
    d->z = z;
}

static inline void RemoveComponent(Vec3 *v, Vec3 *n) {
    float d = v->x * n->x + v->y * n->y + v->z * n->z;
    v->x -= n->x * d;
    v->y -= n->y * d;
    v->z -= n->z * d;
}

int fn_8019A8A4(Kart *k, float f) {
    int n;
    float zero;

    n = 0;
    if (k->ground[0] == 1) {
        n++;
    }
    if (k->ground[1] == 1) {
        n++;
    }
    if (k->ground[2] == 1) {
        n++;
    }
    if (k->ground[3] == 1) {
        n++;
    }
    if (n <= 1 || k->x2a8 > (zero = lbl_806D96D0)) {
        return 0;
    }
    k->x2a8 = lbl_806D9700 * (lbl_806D96D4 - k->up.y) + lbl_806D9700 * f;
    VecSet(&k->x2b0, k->up.x, k->up.y, k->up.z);
    RemoveComponent(&k->vel, &k->x2b0);
    k->x194.x = zero;
    k->x194.y = zero;
    k->x194.z = zero;
    k->x298.x = k->pos.x;
    k->x298.y = k->pos.y;
    k->x298.z = k->pos.z;
    k->x2bc = 1;
    return 1;
}
