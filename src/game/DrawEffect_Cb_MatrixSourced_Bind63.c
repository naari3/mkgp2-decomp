#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */


void DrawEffect_Cb_MatrixSourced_Bind63(unsigned char *self)
{
    float root[4][4];

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x63);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        U8(0x28) = 0;
        F(0x2C) = 0.0f;
        F(0xB0) = 1.0f;
        STATE++;
        break;
    case 1:
        break;
    }
    if (FINISHED) {
        DrawEffect_Free(self);
        return;
    }
    if (*(unsigned long long *)(*(unsigned char **)(P(0x11C) + 0x304) + 0x10) & 0x40000000ULL) {
        F(0x2C) += 0.1f;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
    } else {
        F(0x2C) -= 0.1f;
        if (F(0x2C) < 0.0f) {
            F(0x2C) = 0.0f;
        }
    }
    if (F(0x2C) != lbl_806D51C0) {
        S8(0x28) = 1;
    } else {
        S8(0x28) = 0;
    }
    if (S8(0x28)) {
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, root);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
