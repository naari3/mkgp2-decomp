#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51CC; /* 5.0 */
extern const float lbl_806D5230; /* -1.0 */
extern const float lbl_806D5308; /* 12.0 */

extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);

static inline int VfxSlot_GetDoneFlag(unsigned char *self)
{
    return U8(0x1E);
}

void EffectVfx16_StarItemBurst_Tick(unsigned char *self)
{
    float root[4][4];
    float local[4][4];

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x10);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        U8(0x28) = 1;
        F(0x2C) = lbl_806D51C4;
        F(0xB0) = lbl_806D51C4;
        F(0x120) = Rand_RangeFloat(lbl_806D5230, lbl_806D51C4);
        F(0x124) = lbl_806D51C0;
        F(0x128) = lbl_806D51C0;
        STATE++;
        break;
    case 1:
        break;
    }
    if (VfxSlot_GetDoneFlag(self) == 1) {
        DrawEffect_Free(self);
        return;
    }
    if (P(0x11C) != 0) {
        float x;
        float y;
        float z;

        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
        x = lbl_806D51CC * F(0x120);
        y = F(0x124);
        z = F(0x128) - lbl_806D5308;
        Matrix4_Identity(local);
        Matrix4_PreMultiplyTranslation(local, local, x, y, z);
        Matrix4_Multiply(root, local, root);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, root);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
