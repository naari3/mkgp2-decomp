#include "game/DrawEffectAccess.h"

extern const float lbl_806D5658; /* 1.0 */
extern const float lbl_806D565C; /* 0.0 */
extern const float lbl_806D5674; /* 1.5 */
extern const float lbl_806D56A4; /* 0.5 */
extern const float lbl_806D56B0; /* 0.2 */
extern const float lbl_806D56E4; /* 0.09 */

extern int Rand_RangeIntMax(int max);

void DrawEffect_SparkDescend_Update(unsigned char *self)
{
    Vec pos;

    switch (STATE) {
    case 0:
        if (Rand_RangeIntMax(0x10) % 2) {
            VfxSlot_BindResourceEx(SLOT(self), 0x84, 0);
        } else {
            VfxSlot_BindResourceEx(SLOT(self), 0x85, 0);
        }
        F(0x2C) = lbl_806D5658;
        F(0x150) = Rand_RangeFloat(lbl_806D56A4, lbl_806D5674);
        F(0x154) = lbl_806D5658;
        U32(0x180) = 0xA;
        STATE++;
    case 1:
        F(0xA8) -= lbl_806D56E4;
        if (U32(0x180) == 0) {
            F(0x2C) -= lbl_806D56B0;
            if (F(0x2C) < lbl_806D565C) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    F(0xB0) = F(0x150) * F(0x154);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
