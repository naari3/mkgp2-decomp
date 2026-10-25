/* DrawEffect_Cb_KartVfx_Bind6_YawZ (0x800B5930): one-shot kart ring
 * (resource 6) that grows, spins around the kart yaw and rises over 45
 * frames, fading in over the first 10% and out over the last 30%. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51C8; /* 0.1 */
extern const float lbl_806D51CC; /* 5.0 */
extern const float lbl_806D51E8; /* 0.5 */
extern const float lbl_806D51EC; /* 0.6 */
extern const float lbl_806D51F0; /* 1/45 */
extern const float lbl_806D51F4; /* 0.7 */
extern const float lbl_806D51F8; /* 0.3 */
extern const float lbl_806D51FC; /* 16.755157 */
extern const float lbl_806D5200; /* 10.0 */
extern float KartFxParam_GetConst1p5(void *driver);
extern void VfxSlot_SetScaleVec3(void *slot, float x, float y, float z);
extern float Mtx44_GetYawOfPosZ_Padded(void *mtx);

void DrawEffect_Cb_KartVfx_Bind6_YawZ(unsigned char *self)
{
    float s;

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 6);
        F(0x150) = 0.0f;
        STATE++;
    case 1:
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }

    F(0x150) += 0.022222223f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    if (F(0x150) < 0.1f) {
        F(0x2C) = F(0x150) / 0.1f;
    } else if (0.7f < F(0x150)) {
        F(0x2C) = (1.0f - F(0x150)) / 0.3f;
    } else {
        F(0x2C) = 1.0f;
    }

    F(0xB0) = 0.6f * KartFxParam_GetConst1p5(P(0x11C));
    s = F(0xB0) * (0.5f * F(0x150) + 1.0f);
    VfxSlot_SetScaleVec3(SLOT(self), s, F(0xB0), s);

    F(0x9C) = BuildOrientationFromYaw(
        lbl_806D51FC * F(0x150) + Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(P(0x11C))));
    {
        Vec rot = *V(0x98);
        VfxSlot_SetRotationXYZFromVec(SLOT(self), &rot);
    }

    Mtx44_GetTranslation_RowMajor(V(0x8C), KartDriver_GetKartRootMtx(P(0x11C)));
    F(0x90) = (10.0f * (1.0f - F(0x150)) + 5.0f) * F(0xB0) + F(0x90);
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
}
