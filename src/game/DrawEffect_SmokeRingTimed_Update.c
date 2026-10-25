/* DrawEffect_SmokeRingTimed_Update (0x800CB0C8): smoke ring (resource
 * 0x86) that waits 3 frames, then drifts with its velocity while growing;
 * the fade length (10/20/40 frames) and size depend on the tier in +0x190. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5700; /* 2.0 */
extern const float lbl_806D5710; /* 10.0 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5720; /* 0.8 */
extern const float lbl_806D5724; /* 1.2 */
extern const float lbl_806D5728; /* 0.1 */
extern const float lbl_806D572C; /* 20.0 */
extern const float lbl_806D5730; /* 40.0 */
extern void VfxSlot_BindResource(void *slot, int res);

void DrawEffect_SmokeRingTimed_Update(unsigned char *self)
{
    switch (STATE) {
    case 0:
        switch (S8(0xB5)) {
        case 0:
            U32(0x180) = 3;
            S8(0xB5)++;
        case 1:
            if (U32(0x180) == 0) {
                STATE++;
            }
            break;
        }
        break;
    case 1:
        VfxSlot_BindResource(SLOT(self), 0x86);
        F(0x2C) = lbl_806D56F8;
        switch (S8(0x190)) {
        case 1:
            F(0x150) = Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 2:
            F(0x150) = Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 3:
            F(0x150) = lbl_806D5700 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        }
        F(0x154) = lbl_806D56F8;
        switch (S8(0x190)) {
        case 1:
            F(0x158) = lbl_806D5710;
            break;
        case 2:
            F(0x158) = lbl_806D572C;
            break;
        case 3:
            F(0x158) = lbl_806D5730;
            break;
        }
        STATE++;
    case 2:
        if (U32(0x180) == 0) {
            F(0x2C) -= lbl_806D56F8 / F(0x158);
            if (F(0x2C) < lbl_806D571C) {
                S8(0x28) = 0;
                DrawEffect_Free(self);
                return;
            }
        }
        F(0x154) += lbl_806D5728;
        F(0xB0) = F(0x150) * F(0x154);
        Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
        {
            Vec pos = *V(0x8C);
            VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        }
        VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
        break;
    }
    TICK_TIMERS();
}
