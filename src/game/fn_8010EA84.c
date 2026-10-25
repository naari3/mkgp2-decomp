typedef struct Vec3 { float x, y, z; } Vec3;

extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Mtx44_Inverse_GaussJordan(float *dst, float *src);
extern void Mtx44_TransformVec3(void *out, float *m, Vec3 v);
extern float Vec3_HorizontalMagnitude(void *v);
extern void Vec3_ScaleXZ(void *dst, void *src, float s);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern const float lbl_806D68C4;
extern const float lbl_806D68C8;
extern const float lbl_806D68C0;
extern const float lbl_806D68CC;
extern const float lbl_806D68D0;

void fn_8010EA84(unsigned char *self, unsigned char *ctx)
{
    float m1[16];
    float inv[16];
    float m[16];
    Vec3 pos;

    switch ((signed char)self[0xC9]) {
    case 0:
        *(unsigned int *)(ctx + 0x4) = 10;
        if (*(void **)(ctx + 0x9C)) {
            Vec3_Subtract_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
            Mtx_TransposeToMtx44(m1, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
            Mtx44_Inverse_GaussJordan(inv, m1);
            Mtx44_TransformVec3(ctx + 0x34, inv, *(Vec3 *)(self + 0xA0));
            Vec3_ScaleXZ(ctx + 0x34, ctx + 0x34, lbl_806D68C8 * (lbl_806D68C4 / Vec3_HorizontalMagnitude(ctx + 0x34)));
            GetSpawnPosition(self + 0xB8, lbl_806D68C0, lbl_806D68C0, lbl_806D68C0);
        }
        self[0xC9]++;
    case 1:
        break;
    }
    if (*(unsigned int *)(ctx + 0x4) == 0) {
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - lbl_806D68CC;
        if (*(float *)(self + 0x2C) < lbl_806D68C0) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    if (*(void **)(ctx + 0x9C) == 0) {
        if ((signed char)self[0xCB] == 4 || (signed char)self[0xCB] == 9) {
            *(float *)(self + 0xBC) += lbl_806D68D0;
        }
    } else {
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(ctx + 0x9C))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(ctx + 0x9C)));
        Mtx44_TransformVec3(self + 0xA0, m, *(Vec3 *)(ctx + 0x34));
    }
    Item_DecayVelocityScalar(self, lbl_806D68C4);
}
