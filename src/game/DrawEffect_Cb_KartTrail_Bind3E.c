/* DrawEffect_Cb_KartTrail_Bind3E (0x800B6C24): scrolling trail (resource
 * 0x3E) on kart joint 15. It fades in while the driver's item-effect flag
 * 0x02000000 is set and fades out otherwise. It is pulled 10 units towards
 * the camera. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51BC; /* 2.0 */
extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51D8; /* 0.05 */
extern const float lbl_806D5200; /* 10.0 */
extern const float lbl_806D5238; /* -1/30 */
extern unsigned char lbl_805DF3D0[];
extern void VfxSlot_SetUVScroll(void *slot, float u, float v);
extern float KartCharacterParam_GetFxSizeFactor(void *driver);

void DrawEffect_Cb_KartTrail_Bind3E(unsigned char *self)
{
    Vec d;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x3E, 0);
        VfxSlot_SetUVScroll(SLOT(self), lbl_806D51C0, lbl_806D5238);
        F(0xB0) = lbl_806D51C4;
        F(0x2C) = lbl_806D51C0;
        STATE++;
    case 1:
        break;
    }

    if (FINISHED) {
        DrawEffect_Free(self);
        return;
    }

    if (*(unsigned long long *)(*(unsigned char **)(P(0x11C) + 0x304) + 0x10) & 0x02000000ULL) {
        F(0x2C) += lbl_806D51D8;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
    } else {
        F(0x2C) -= lbl_806D51D8;
        if (F(0x2C) < 0.0f) {
            F(0x2C) = 0.0f;
        }
    }

    F(0xB0) = lbl_806D51BC * KartCharacterParam_GetFxSizeFactor(P(0x11C));
    Mtx44_GetTranslation_RowMajor(V(0x8C), KartDriver_GetJointByIdx(P(0x11C), 0xF));
    Vec3_Subtract_DestFirst(&d, (Vec *)(lbl_805DF3D0 + 0x80), V(0x8C));
    Vec3_Scale(&d, &d, lbl_806D5200 * (lbl_806D51C4 / Vec3_Magnitude_Wrapper(&d)));
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), &d);

    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
}
