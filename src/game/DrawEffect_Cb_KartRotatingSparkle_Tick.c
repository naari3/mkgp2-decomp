/* DrawEffect_Cb_KartRotatingSparkle_Tick (0x800CA000): tumbling sparkle
 * (resource 0x87 or 0x88) with random spin rates. It bobs by |f(yaw)|,
 * lives 120 frames and then fades out. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D565C; /* 0.0 */
extern const float lbl_806D5660; /* deg->rad */
extern const float lbl_806D5664; /* -180.0 */
extern const float lbl_806D5668; /* 180.0 */
extern const float lbl_806D5684; /* 0.05 */
extern const float lbl_806D56B0; /* 0.2 */
extern const float lbl_806D56B4; /* -10.0 */
extern const float lbl_806D56B8; /* 10.0 */
extern const float lbl_806D56BC; /* -0.05 */
extern const float lbl_806D56C0; /* -0.2 */
extern double cos(double x);
extern float FAbs_FloatAsDouble(float x);

void DrawEffect_Cb_KartRotatingSparkle_Tick(unsigned char *self)
{
    switch (STATE) {
    case 0:
        if (I(0x10) == 0) {
            VfxSlot_BindResource(SLOT(self), 0x87);
        } else {
            VfxSlot_BindResource(SLOT(self), 0x88);
        }
        F(0xB0) = lbl_806D56B0;
        U32(0x180) = 0x78;
        F(0x98) = lbl_806D5660 * Rand_RangeFloat(lbl_806D5664, lbl_806D5668);
        F(0x9C) = lbl_806D5660 * Rand_RangeFloat(lbl_806D5664, lbl_806D5668);
        F(0x150) = lbl_806D5660 * Rand_RangeFloat(lbl_806D56B4, lbl_806D56B8);
        F(0x154) = lbl_806D5660 * Rand_RangeFloat(lbl_806D56B4, lbl_806D56B8);
        STATE++;
    case 1:
        if (U32(0x180) == 0) {
            F(0x2C) -= lbl_806D5684;
            if (F(0x2C) <= lbl_806D565C) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }

    F(0x98) = BuildOrientationFromYaw(F(0x98) + F(0x150));
    F(0x9C) = BuildOrientationFromYaw(F(0x9C) + F(0x154));
    F(0xA8) = lbl_806D56C0 * FAbs_FloatAsDouble((float)cos(F(0x98))) + lbl_806D56BC;
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    {
        Vec rot = *V(0x98);
        VfxSlot_SetRotationXYZFromVec(SLOT(self), &rot);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    DrawEffect_TickTimer((unsigned int *)(self + 0x180));
}
