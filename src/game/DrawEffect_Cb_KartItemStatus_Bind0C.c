/* DrawEffect_Cb_KartItemStatus_Bind0C (0x800B6FA0): per-character item
 * status overlay (resource 0xC) on the kart's root matrix. It scrolls its
 * UVs in bursts with random pauses and fades in while the driver's 0x400000
 * status flag is set. */
#include "game/DrawEffectAccess.h"

extern Vec lbl_8041A2B0[11];
extern int Rand_RangeInt(int lo, int hi);
extern void VfxSlot_SetUVScroll(void *slot, float u, float v);
extern void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float x, float y, float z);
extern double sin(double x);

void DrawEffect_Cb_KartItemStatus_Bind0C(unsigned char *self)
{
    float root[4][4];
    float scale[4][4];

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0xC);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        F(0x2C) = 0.0f;
        switch (*(unsigned int *)(P(0x11C) + 0x1F8)) {
        case 0: I(0x10) = 0; break;
        case 1: I(0x10) = 1; break;
        case 5: I(0x10) = 2; break;
        case 4: I(0x10) = 3; break;
        case 2: I(0x10) = 4; break;
        case 3: I(0x10) = 5; break;
        case 7: I(0x10) = 6; break;
        case 6: I(0x10) = 7; break;
        case 8: I(0x10) = 8; break;
        case 9: I(0x10) = 9; break;
        case 10: I(0x10) = 10; break;
        }
        F(0x150) = 0.0f;
        U32(0x180) = 0;
        S8(0x190) = -1;
        S8(0x191) = -1;
        STATE++;
    case 1:
        break;
    }

    if (FINISHED) {
        DrawEffect_Free(self);
        return;
    }
    if (U32(0x180) == 0) {
        if (1.0f <= F(0x150)) {
            VfxSlot_SetUVScroll(SLOT(self), 0.0f, 0.0f);
            F(0x150) = 0.0f;
            U32(0x180) = Rand_RangeInt(1, 5) * 60;
        } else {
            F(0x150) += 0.06666667f;
            VfxSlot_SetUVScroll(SLOT(self), -0.06666667f, -0.06666667f);
        }
        {
            float s = sin(0.017453292f * (180.0f * F(0x150)));
            float k = 0.6f * s + 1.0f;
            GetSpawnPosition(V(0x30), k, k, k);
        }
    }
    if (*(unsigned long long *)(*(unsigned char **)(P(0x11C) + 0x304) + 0x10) & 0x400000ULL) {
        F(0x2C) += 0.05f;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
    } else {
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            F(0x2C) = 0.0f;
        }
    }
    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
    Matrix4_Identity(scale);
    Mtx44_Scale_PerAxis(scale, scale, lbl_8041A2B0[I(0x10)].x, lbl_8041A2B0[I(0x10)].y,
                        lbl_8041A2B0[I(0x10)].z);
    Matrix4_Multiply(root, scale, root);
    DbgScene_CopyMatrix3x4Transpose(self + 0x48, root);
    Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    F(0xB0) = 1.0f;
    TICK_TIMERS();
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
