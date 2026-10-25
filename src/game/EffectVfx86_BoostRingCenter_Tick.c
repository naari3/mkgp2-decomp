#include "game/DrawEffectAccess.h"

extern const float lbl_806D51BC; /* 2.0 */
extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51C8; /* 0.1 */
extern const float lbl_806D5304; /* 1.6 */
extern const float lbl_806D5368; /* 1.8 */
extern const float lbl_806D536C; /* 0.12 */

extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);

void EffectVfx86_BoostRingCenter_Tick(unsigned char *self)
{
    float root[4][4];
    float local[4][4];

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x86);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        F(0x2C) = lbl_806D51C4;
        F(0x150) = Rand_RangeFloat(lbl_806D5304, lbl_806D5368);
        F(0x154) = lbl_806D51C4;
        F(0x158) = Rand_RangeFloat(lbl_806D51C8, lbl_806D536C);
        STATE++;
        break;
    case 1:
        break;
    }
    F(0x2C) -= lbl_806D51C8;
    if (F(0x2C) < lbl_806D51C0) {
        DrawEffect_Free(self);
        return;
    }
    F(0x154) += F(0x158);
    F(0xB0) = F(0x150) * F(0x154);
    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
    Matrix4_Identity(local);
    Mtx44_Scale_Uniform(local, local, F(0xB0));
    Matrix4_PreMultiplyTranslation(local, local, lbl_806D51C0, lbl_806D51BC, lbl_806D51C0);
    Matrix4_Multiply(root, local, root);
    DbgScene_CopyMatrix3x4Transpose(self + 0x48, root);
    Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
