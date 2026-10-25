/* DrawEffect_Cb_KartSparkleSpray_Tick (0x800C9BE8): sparkle spray puff
 * (resource 0x6D) with a random roll that drifts backward. Variant 0 is a
 * small long-lived puff; other variants are large, grow slowly and fade
 * in to half opacity. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5658; /* 1.0 */
extern const float lbl_806D565C; /* 0.0 */
extern const float lbl_806D5660; /* deg->rad */
extern const float lbl_806D5664; /* -180.0 */
extern const float lbl_806D5668; /* 180.0 */
extern const float lbl_806D566C; /* 0.6 */
extern const float lbl_806D5670; /* 0.7 */
extern const float lbl_806D5674; /* 1.5 */
extern const float lbl_806D5678; /* 2.5 */
extern const float lbl_806D567C; /* 0.15 */
extern const float lbl_806D5680; /* 0.25 */
extern const float lbl_806D5684; /* 0.05 */
extern const float lbl_806D5688; /* pi */
extern const float lbl_806D568C; /* 0.02 */
extern const float lbl_806D5690; /* 0.3 */
extern const float lbl_806D5694; /* 0.9 */
extern const float lbl_806D5698; /* 30.0 */
extern const float lbl_806D569C; /* 45.0 */
extern const float lbl_806D56A0; /* 0.01 */
extern const float lbl_806D56A4; /* 0.5 */
extern const float lbl_806D56A8; /* 0.002 */
extern const float lbl_806D56AC; /* 20.0 */

void DrawEffect_Cb_KartSparkleSpray_Tick(unsigned char *self)
{
    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x6D, 0);
        F(0x15C) = lbl_806D5658;
        F(0x2C) = lbl_806D565C;
        F(0xA0) = lbl_806D5660 * Rand_RangeFloat(lbl_806D5664, lbl_806D5668);
        if (I(0x10) == 0) {
            GetSpawnPosition(V(0x30), lbl_806D566C, lbl_806D566C, lbl_806D5670);
            F(0x150) = Rand_RangeFloat(lbl_806D5674, lbl_806D5678);
            GetSpawnPosition(V(0xA4), 0.0f, Rand_RangeFloat(lbl_806D567C, lbl_806D5680), Rand_RangeFloat(lbl_806D5684, lbl_806D567C));
            Vec2_RotateY(V(0xA4), V(0xA4), lbl_806D5688);
            U32(0x180) = 600;
            F(0x154) = lbl_806D568C;
            F(0x158) = lbl_806D5690;
        } else {
            GetSpawnPosition(V(0x30), lbl_806D5694, lbl_806D5694, lbl_806D5658);
            F(0x150) = Rand_RangeFloat(lbl_806D5698, lbl_806D569C);
            GetSpawnPosition(V(0xA4), lbl_806D565C, lbl_806D5658, Rand_RangeFloat(lbl_806D5694, lbl_806D5658));
            Vec2_RotateY(V(0xA4), V(0xA4), lbl_806D5688);
            U32(0x180) = 500;
            F(0x154) = lbl_806D56A0;
            F(0x158) = lbl_806D56A4;
            U8(0x14) = 1;
        }
        STATE++;
    case 1:
        if (I(0x10) != 0) {
            F(0x15C) += lbl_806D56A8;
        }
        if (U32(0x180) != 0) {
            F(0x2C) += F(0x158) / lbl_806D56AC;
            if (F(0x158) < F(0x2C)) {
                F(0x2C) = F(0x158);
            }
        } else {
            F(0x2C) -= F(0x154);
            if (F(0x2C) <= lbl_806D565C) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }

    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    F(0xB0) = F(0x150) * F(0x15C);
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
