/* EffectVfx82_FieldItemDropPuff_Tick (0x800C2F48): resource 0x82 puff left
 * where a field item drops. Grows to 2x while drifting down, holds for 120
 * frames, then fades out. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5400; /* 0.0 */
extern const float lbl_806D5414; /* 0.05 */
extern const float lbl_806D5418; /* -0.05 */
extern const float lbl_806D5424; /* 1.0 */
extern const float lbl_806D5444; /* 0.99 */
extern const float lbl_806D5448; /* 0.2 */

void EffectVfx82_FieldItemDropPuff_Tick(unsigned char *self)
{
    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x82);
        U8(0x28) = 1;
        F(0x2C) = lbl_806D5424;
        F(0xB0) = lbl_806D5400;
        STATE++;
    case 1:
        F(0xA8) += lbl_806D5418;
        F(0xA4) *= lbl_806D5444;
        F(0xAC) *= lbl_806D5444;
        F(0xB0) += lbl_806D5448;
        if (2.0f < F(0xB0)) {
            F(0xB0) = 2.0f;
            U32(0x180) = 0x78;
            STATE++;
        }
        break;
    case 2:
        if (U32(0x180) == 0) {
            STATE++;
        }
        break;
    case 3:
        F(0x2C) -= lbl_806D5414;
        if (F(0x2C) < lbl_806D5400) {
            U8(0x28) = 0;
            DrawEffect_Free(self);
            return;
        }
        break;
    }

    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    {
        Vec rot = *V(0x98);
        VfxSlot_SetRotationXYZFromVec(SLOT(self), &rot);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
