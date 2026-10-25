/* DrawEffect_Cb_KartFlatBurst_Tick (0x800CA2C4): flat burst plane
 * (resource 0x12) with a random roll. It fades in over 15 frames, then
 * keeps growing and fades out once its timer runs down. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5658; /* 1.0 */
extern const float lbl_806D565C; /* 0.0 */
extern const float lbl_806D5660; /* deg->rad */
extern const float lbl_806D5664; /* -180.0 */
extern const float lbl_806D5668; /* 180.0 */
extern const float lbl_806D5674; /* 1.5 */
extern const float lbl_806D56A0; /* 0.01 */
extern const float lbl_806D56A4; /* 0.5 */
extern const float lbl_806D56C4; /* 1/15 */
extern const float lbl_806D56C8; /* 8.0 */
extern const float lbl_806D56CC; /* 2.0 */
extern const float lbl_806D56D0; /* 3.0 */
extern void VfxSlot_SetScaleVec3(void *slot, float x, float y, float z);

void DrawEffect_Cb_KartFlatBurst_Tick(unsigned char *self)
{
    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x12, 0);
        GetSpawnPosition(V(0x30), lbl_806D5658, lbl_806D5658, lbl_806D5658);
        F(0x150) = Rand_RangeFloat(lbl_806D56A4, lbl_806D5674);
        F(0x154) = lbl_806D5658;
        F(0x2C) = lbl_806D565C;
        F(0xA0) = lbl_806D5660 * Rand_RangeFloat(lbl_806D5664, lbl_806D5668);
        STATE++;
    case 1:
        F(0x2C) += lbl_806D56C4;
        if (lbl_806D5658 <= F(0x2C)) {
            U32(0x180) = 0;
            STATE++;
        }
        break;
    case 2:
        F(0x154) += lbl_806D56A0;
        if (U32(0x180) == 0) {
            F(0x2C) -= lbl_806D56C4;
            if (F(0x2C) <= lbl_806D565C) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }

    F(0xB0) = lbl_806D56C8 * (lbl_806D56CC * (F(0x150) * F(0x154)));
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    {
        float w = lbl_806D56D0 * F(0xB0);
        VfxSlot_SetScaleVec3(SLOT(self), w, F(0xB0), w);
    }
    TICK_TIMERS();
}
