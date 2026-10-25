typedef struct Vec3 { float x, y, z; } Vec3;

extern void Effect_KartOrbitSpark_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Mtx44_TransformVec3(void *out, float *m, Vec3 v);
extern float Mtx44_GetYawOfPosZ(float *m);
extern float BuildOrientationFromYaw(float a);
extern const float lbl_806D69A8;
extern const float lbl_806D69AC;
extern const float lbl_806D69B0;
extern float lbl_806CF3F4;
extern float lbl_806CF3F8;
extern const float lbl_806D69B4;
extern float lbl_806CF3FC;
extern const float lbl_806D69B8;

void fn_80112BE4(unsigned char *self, unsigned char *ctx)
{
    float m[16];
    Vec3 v;
    unsigned char *e;

    switch ((signed char)self[0xC9]) {
    case 0:
        *(float *)(ctx + 0x14) = lbl_806D69A8;
        *(float *)(ctx + 0x18) = lbl_806D69A8;
        *(unsigned int *)(ctx + 0x4) = 0;
        self[0xC9]++;
    case 1:
        *(float *)(ctx + 0x18) += lbl_806D69AC;
        if (lbl_806D69B0 < *(float *)(ctx + 0x18)) {
            *(float *)(ctx + 0x18) = lbl_806D69A8;
            *(float *)(ctx + 0x1C) = lbl_806D69A8;
            self[0xC9]++;
        }
        break;
    case 2:
        *(float *)(ctx + 0x1C) += lbl_806CF3F4;
        *(float *)(ctx + 0x14) += *(float *)(ctx + 0x1C);
        if (lbl_806CF3F8 < *(float *)(ctx + 0x18)) {
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D69B4;
            if (*(float *)(self + 0x2C) < lbl_806D69A8) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
        }
        break;
    }
    if (*(unsigned int *)(ctx + 0x4) == 0) {
        e = DrawEffect_SpawnDirect(Effect_KartOrbitSpark_Update);
        if (e) {
            Vec3_Copy(e + 0x8C, self + 0xA0);
            *(void **)(e + 0x11C) = *(void **)(ctx + 0x98);
        }
        *(unsigned int *)(ctx + 0x4) = 5;
    }
    Item_DecayVelocityScalar(self, lbl_806CF3FC);
    if (*(void **)(ctx + 0x98)) {
        Vec3_Copy(&v, ctx + 0x34);
        v.y += *(float *)(ctx + 0x14);
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x98)));
        Mtx44_TransformVec3(self + 0xA0, m, v);
        *(float *)(self + 0xB0) = BuildOrientationFromYaw(*(float *)(ctx + 0x18) + (lbl_806D69B8 + Mtx44_GetYawOfPosZ(m)));
    }
}
