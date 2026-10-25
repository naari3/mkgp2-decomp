/* DrawEffect_Cb_KartVfx_Bind4or5_Variant (0x800B5B00): short kart flash
 * (resource 4 or 5 by variant) that fades in/out over 21 frames and sits
 * slightly in front of the kart toward the camera. */
#include "game/DrawEffectAccess.h"

typedef struct CameraView {
    unsigned char pad0[0x80];
    Vec eye;
} CameraView;

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51C8; /* 0.1 */
extern const float lbl_806D51D4; /* 0.2 */
extern const float lbl_806D51E8; /* 0.5 */
extern const float lbl_806D51F4; /* 0.7 */
extern const float lbl_806D51F8; /* 0.3 */
extern const float lbl_806D5204; /* 1/21 */
extern const float lbl_806D5208; /* 0.8 */
extern const float lbl_806D520C; /* 1.6 */
extern const float lbl_806D5210; /* -10.0 */
extern const float lbl_806D5214; /* 4.0 */
extern CameraView lbl_805DF3D0;
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern float KartFxParam_GetConst1p5(void *kart);
extern void VfxSlot_SetScaleVec3(void *slot, float x, float y, float z);

void DrawEffect_Cb_KartVfx_Bind4or5_Variant(unsigned char *self)
{
    switch (STATE) {
    case 0:
        switch (I(0x10)) {
        case 0:
            VfxSlot_BindResourceEx(SLOT(self), 4, 0);
            break;
        case 1:
            VfxSlot_BindResourceEx(SLOT(self), 5, 0);
            break;
        }
        F(0x150) = lbl_806D51C0;
        STATE++;
    case 1:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        S8(0x28) = 0;
    } else {
        S8(0x28) = 1;
    }
    F(0x150) += lbl_806D5204;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    if (F(0x150) < lbl_806D51C8) {
        F(0x2C) = F(0x150) / lbl_806D51C8;
    } else if (lbl_806D51F4 < F(0x150)) {
        F(0x2C) = (1.0f - F(0x150)) / lbl_806D51F8;
    } else {
        F(0x2C) = 1.0f;
    }
    if (I(0x10) == 0) {
        F(0x2C) *= lbl_806D51E8;
    }
    F(0xB0) = lbl_806D5208 * KartFxParam_GetConst1p5(P(0x11C));
    if (I(0x10) == 0) {
        VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    } else {
        VfxSlot_SetScaleVec3(SLOT(self), F(0xB0) * (1.0f - lbl_806D51E8 * F(0x150)),
                             F(0xB0) * (lbl_806D520C * F(0x150) + lbl_806D51D4), F(0xB0));
    }
    Mtx44_GetTranslation_RowMajor(V(0x8C), KartDriver_GetKartRootMtx(P(0x11C)));
    {
        Vec d;
        Vec3_Subtract_DestFirst(&d, V(0x8C), &lbl_805DF3D0.eye);
        Vec3_Scale(&d, &d, lbl_806D5210 * (F(0xB0) * (1.0f / Vec3_Magnitude_Wrapper(&d))));
        Vec3_Add_DestFirst(V(0x8C), V(0x8C), &d);
    }
    F(0x90) -= lbl_806D5214;
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
}
