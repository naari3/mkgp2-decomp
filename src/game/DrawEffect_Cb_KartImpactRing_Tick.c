/* DrawEffect_Cb_KartImpactRing_Tick (0x800C8F3C): impact ring (resource
 * 0x4A) that follows the kart at a fixed offset, spins, grows and fades out
 * once its 20-frame timer runs down. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D555C; /* 0.0 */
extern const float lbl_806D5560; /* 0.2 */
extern const float lbl_806D5574; /* deg->rad */
extern const float lbl_806D5584; /* 1.0 */
extern const float lbl_806D5594; /* -180.0 */
extern const float lbl_806D5598; /* 180.0 */
extern const float lbl_806D55A0; /* 0.05 */
extern const float lbl_806D55A8; /* 10.0 */
extern const float lbl_806D55B4; /* 0.1 */
extern const float lbl_806D55DC; /* 0.7 */
extern const float lbl_806D55F8; /* 0.8 */
extern const float lbl_806D5608; /* 1.3 */
extern const float lbl_806D560C; /* -10.0 */
extern const float lbl_806D5628; /* 0.6 */

void DrawEffect_Cb_KartImpactRing_Tick(unsigned char *self)
{
    Vec kartPos;

    Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(P(0x11C)));
    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x4A, 0);
        Vec3_Subtract_DestFirst(V(0x120), V(0x8C), &kartPos);
        F(0x150) = lbl_806D5560;
        F(0x154) = lbl_806D55F8 * Rand_RangeFloat(lbl_806D55DC, lbl_806D5608);
        F(0x158) = lbl_806D5584;
        F(0x15C) = lbl_806D5628 * Rand_RangeFloat(lbl_806D5628, lbl_806D5584);
        F(0xA0) = lbl_806D5574 * Rand_RangeFloat(lbl_806D5594, lbl_806D5598);
        F(0x160) = lbl_806D5574 * Rand_RangeFloat(lbl_806D560C, lbl_806D55A8);
        U32(0x180) = 20;
        STATE++;
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        F(0x158) -= lbl_806D55B4;
        if (F(0x158) < lbl_806D555C) {
            DrawEffect_Free(self);
            return;
        }
    }
    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    Vec3_Add_DestFirst(V(0x8C), &kartPos, V(0x120));
    F(0x150) += lbl_806D55A0;
    F(0xB0) = F(0x150) * F(0x154);
    F(0x2C) = F(0x158) * F(0x15C);
    F(0xA0) = BuildOrientationFromYaw(F(0xA0) + F(0x160));
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
