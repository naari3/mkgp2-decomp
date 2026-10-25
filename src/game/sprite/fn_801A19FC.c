typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct KartInfo {
    unsigned char pad0[0x10];
    unsigned long long flags;
} KartInfo;

typedef struct KartDrv {
    unsigned char pad0[0x304];
    KartInfo *info;
} KartDrv;

extern float *KartDriver_GetKartRootMtx(KartDrv *k);
extern void KartDriver_GetJointPosition(KartDrv *k, int joint, Vec3 *out);
extern float Vec3_Magnitude(Vec3 *v);
extern void Vec3_Normalize(Vec3 *src, Vec3 *dst);
extern float Vec3_Dot(Vec3 *a, Vec3 *b);
extern const float lbl_806D97F0;
extern const float lbl_806D97F4;
extern const float lbl_806D9800;
extern const float lbl_806D97FC;

static inline unsigned char HasFlag(KartInfo *info, unsigned long long mask) {
    unsigned char r;
    if ((info->flags & mask) == 0) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

float fn_801A19FC(KartDrv *self, KartDrv *k) {
    float *m;
    float dist;
    float d;
    Vec3 a;
    Vec3 b;
    Vec3 v;

    if (self == k) {
        return lbl_806D97F0;
    }
    if (HasFlag(k->info, 0x80)) {
        return lbl_806D97F0;
    }
    if ((k->info->flags & 0x8000000000ULL) != 0) {
        return lbl_806D97F0;
    }
    m = KartDriver_GetKartRootMtx(self);
    KartDriver_GetJointPosition(k, -1, &v);
    v.x -= m[3];
    v.y = lbl_806D97F4;
    v.z -= m[11];
    dist = Vec3_Magnitude(&v);
    if (Vec3_Magnitude(&v) > lbl_806D9800) {
        return lbl_806D97F0;
    }
    a.x = m[0];
    a.y = lbl_806D97F4;
    a.z = m[8];
    b.x = m[2];
    b.y = lbl_806D97F4;
    b.z = m[10];
    Vec3_Normalize(&v, &v);
    Vec3_Normalize(&a, &a);
    Vec3_Normalize(&b, &b);
    d = Vec3_Dot(&a, &v);
    if (Vec3_Dot(&b, &v) > lbl_806D97F4) {
        return lbl_806D97F0;
    }
    if ((float)__fabs(d) > lbl_806D97FC) {
        return lbl_806D97F0;
    }
    return dist;
}
