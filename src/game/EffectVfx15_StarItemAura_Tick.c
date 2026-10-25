/* EffectVfx15_StarItemAura_Tick (0x800BE3A0): star-item aura (resource 0xF)
 * on the kart root, turned 180 degrees about Y. It fades in while the
 * linked item is in state 6 and plays faster with the item's speed. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51C8; /* 0.1 */
extern const float lbl_806D51D0; /* 3.0 */
extern const float lbl_806D5348; /* pi */
extern void VfxSlot_SetAnimSpeed(void *slot, float speed);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float angle);

void EffectVfx15_StarItemAura_Tick(unsigned char *self)
{
    float root[4][4];
    float rot[4][4];

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0xF);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        U8(0x28) = 0;
        F(0x2C) = 0.0f;
        F(0xB0) = lbl_806D51C4;
        STATE++;
    case 1:
        break;
    }

    if (FINISHED) {
        DrawEffect_Free(self);
        return;
    }

    if (P(0xDC) != 0) {
        float speed;
        if ((int)P(0xDC)[0xD4] == 6 || (int)P(0xDC)[0xD5] == 6) {
            F(0x2C) += lbl_806D51C8;
            if (1.0f < F(0x2C)) {
                F(0x2C) = 1.0f;
            }
            U8(0x28) = 1;
        } else {
            F(0x2C) -= lbl_806D51C8;
            if (F(0x2C) < 0.0f) {
                F(0x2C) = 0.0f;
                U8(0x28) = 0;
            }
        }
        speed = Vec3_Magnitude_Wrapper((Vec *)(P(0xDC) + 0xE4)) / 3.0f;
        if (speed < 0.0f) {
            speed = 0.0f;
        }
        if (3.0f < speed) {
            speed = 3.0f;
        }
        VfxSlot_SetAnimSpeed(SLOT(self), speed);
    }

    if (F(0x2C) < 0.0f) {
        U8(0x28) = 0;
    } else if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }

    if (S8(0x28) && P(0x11C) != 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
        Matrix4_Identity(rot);
        Matrix4_PreMultiplyRotY(rot, rot, lbl_806D5348);
        Matrix4_Multiply(root, rot, root);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, root);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
    }
}
