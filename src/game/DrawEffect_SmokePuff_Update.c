#include "game/DrawEffectAccess.h"

extern const float lbl_806D5658; /* 1.0 */
extern const float lbl_806D565C; /* 0.0 */
extern const float lbl_806D56B0; /* 0.2 */
extern const float lbl_806D56E0; /* 0.1 */

void DrawEffect_SmokePuff_Update(unsigned char *self)
{
    Vec pos;

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x86);
        F(0x2C) = lbl_806D5658;
        F(0xB0) = lbl_806D56B0;
        U32(0x180) = 0xA;
        STATE++;
    case 1:
        F(0xB0) += lbl_806D56E0;
        if (U32(0x180) == 0) {
            F(0x2C) -= lbl_806D56E0;
            if (F(0x2C) < lbl_806D565C) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
