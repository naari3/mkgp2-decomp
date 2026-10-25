typedef struct Vec3 { float x, y, z; } Vec3;

extern void GetSpawnPosition(void *out, float x, float y, float z);
extern float BuildOrientationFromYaw(float a);
extern double cos(double);
extern double sin(double);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Mtx44_TransformVec3(void *out, float *m, Vec3 v);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern const float lbl_806D6C38;
extern const float lbl_806D6C34;
extern float lbl_806D6C48;
extern float lbl_806D6C4C;
extern float lbl_806D6C28;
extern float lbl_806D6C50;

void fn_80119F80(unsigned char *self, unsigned char *ctx)
{
    float m[16];
    Vec3 v;
    float t;

    switch ((signed char)self[0xC9]) {
    case 0:
        GetSpawnPosition(self + 0xB8, lbl_806D6C38, lbl_806D6C38, lbl_806D6C38);
        *(float *)(ctx + 0x14) = lbl_806D6C38;
        *(unsigned int *)(ctx + 0x4) = 600;
        *(unsigned int *)(ctx + 0x8) = 3;
        *(unsigned int *)(ctx + 0xC) = 60;
        self[0xC9]++;
    case 1:
        break;
    }
    if (*(unsigned int *)(ctx + 0x8) == 0) {
        if (*(unsigned long long *)(*(unsigned char **)(*(unsigned char **)(ctx + 0x9C) + 0x304) + 0x10) & 0x10000ULL) {
            *(unsigned int *)(ctx + 0x4) = 0;
        }
    }
    if (*(unsigned int *)(ctx + 0xC) == 0) {
        if (!(*(unsigned long long *)(*(unsigned char **)(*(unsigned char **)(ctx + 0x9C) + 0x304) + 0x10) & 0x20000000000000ULL)) {
            *(unsigned int *)(ctx + 0x4) = 0;
        }
    }
    if (*(unsigned int *)(ctx + 0x4) == 0) {
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D6C34;
        if (*(float *)(self + 0x2C) < lbl_806D6C38) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    *(float *)(ctx + 0x14) = BuildOrientationFromYaw(lbl_806D6C48 + *(float *)(ctx + 0x14));
    v.x = lbl_806D6C4C * (float)cos(*(float *)(ctx + 0x14));
    t = sin(lbl_806D6C28 * *(float *)(ctx + 0x14));
    v.y = lbl_806D6C50 * t + lbl_806D6C50;
    v.z = lbl_806D6C4C * (float)sin(*(float *)(ctx + 0x14));
    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
    Mtx44_TransformVec3(self + 0xA0, m, v);
    Item_DecayVelocityScalar(self, lbl_806D6C28);
}
