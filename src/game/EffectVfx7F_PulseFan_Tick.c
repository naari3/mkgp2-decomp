/* EffectVfx7F_PulseFan_Tick (0x800C34F8): pulsing fan sprite (resource
 * 0x7F). It waits a random 0..119 frames hidden, then plays one 36-frame
 * pulse (scale 1 + sin over a full turn) while spinning in a random
 * direction, and goes back to waiting. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D53E8; /* 0.8 */
extern const float lbl_806D53EC; /* deg->rad */
extern const float lbl_806D53F0; /* -180.0 */
extern const float lbl_806D53F4; /* 180.0 */
extern const float lbl_806D5400; /* 0.0 */
extern const float lbl_806D5408; /* 1.2 */
extern const float lbl_806D540C; /* 0.5 */
extern const float lbl_806D5424; /* 1.0 */
extern const float lbl_806D5434; /* -1.0 */
extern const float lbl_806D543C; /* 270.0 */
extern const float lbl_806D544C; /* 2.0 */
extern const float lbl_806D5458; /* 90.0 */
extern const float lbl_806D5468; /* 1/36 */
extern int Rand_RangeIntMax(int max);
extern double sin(double x);

void EffectVfx7F_PulseFan_Tick(unsigned char *self)
{
    float s;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x7F, 0);
        STATE++;
        S8(0xB5) = 0;
    case 1:
        switch (S8(0xB5)) {
        case 0:
            U8(0x28) = 0;
            U32(0x180) = Rand_RangeIntMax(120);
            S8(0xB5)++;
        case 1:
            break;
        }
        if (U32(0x180) == 0) {
            STATE++;
            S8(0xB5) = 0;
        }
        break;
    case 2:
        switch (S8(0xB5)) {
        case 0:
            U8(0x28) = 1;
            F(0x150) = lbl_806D5400;
            F(0xA0) = lbl_806D53EC * Rand_RangeFloat(lbl_806D53F0, lbl_806D53F4);
            if (Rand_RangeIntMax(15) % 2) {
                F(0x154) = lbl_806D5424;
            } else {
                F(0x154) = lbl_806D5434;
            }
            F(0x158) = lbl_806D544C * Rand_RangeFloat(lbl_806D53E8, lbl_806D5408);
            S8(0xB5)++;
        case 1:
            break;
        }
        {
            Vec pos = *V(0x8C);
            VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        }
        F(0xA0) = BuildOrientationFromYaw(lbl_806D53EC * (lbl_806D544C * F(0x154)) + F(0xA0));
        VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
        if (F(0x150) < lbl_806D540C) {
            s = lbl_806D5424 + (float)sin(lbl_806D53EC * (lbl_806D5458 * (lbl_806D544C * F(0x150)) + lbl_806D543C));
        } else {
            s = lbl_806D5424 + (float)sin(lbl_806D53EC * (lbl_806D5458 * (lbl_806D544C * (F(0x150) - lbl_806D540C)) + lbl_806D53F4));
        }
        VfxSlot_SetScaleUniform(SLOT(self), s * (F(0xB0) * F(0x158)));
        F(0x150) += lbl_806D5468;
        if (lbl_806D5424 < F(0x150)) {
            STATE = 1;
            S8(0xB5) = 0;
        }
        break;
    }
    TICK_TIMERS();
}
