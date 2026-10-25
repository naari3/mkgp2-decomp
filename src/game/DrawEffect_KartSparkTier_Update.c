/* DrawEffect_KartSparkTier_Update (0x800CB344): free-flying spark
 * (resource 0x13/0x14, or 0x84/0x85 for kind 4) that sinks and drifts with
 * its velocity; size and lifetime (5/15/35 frames) follow the tier in
 * +0x190, kind 5 is half size. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D56FC; /* 0.4 */
extern const float lbl_806D5704; /* 0.5 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D5718; /* 0.2 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5720; /* 0.8 */
extern const float lbl_806D5724; /* 1.2 */
extern const float lbl_806D5734; /* 3.0 */
extern const float lbl_806D5738; /* 0.09 */
extern int Rand_RangeIntMax(int max);

void DrawEffect_KartSparkTier_Update(unsigned char *self)
{
    switch (STATE) {
    case 0:
        if ((int)U8(0x191) == 4) {
            if (Rand_RangeIntMax(16) % 2) {
                VfxSlot_BindResourceEx(SLOT(self), 0x84, 0);
            } else {
                VfxSlot_BindResourceEx(SLOT(self), 0x85, 0);
            }
        } else if (Rand_RangeIntMax(16) % 4) {
            VfxSlot_BindResourceEx(SLOT(self), 0x14, 0);
        } else {
            VfxSlot_BindResourceEx(SLOT(self), 0x13, 0);
        }
        if ((int)U8(0x191) == 4) {
            F(0x2C) = lbl_806D56F8;
        } else {
            F(0x2C) = lbl_806D56FC;
        }
        switch (S8(0x190)) {
        case 1:
            F(0x150) = lbl_806D5708 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 2:
            F(0x150) = lbl_806D5708 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        case 3:
            F(0x150) = lbl_806D5734 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
            break;
        }
        if ((int)U8(0x191) == 5) {
            F(0x150) *= lbl_806D5704;
        }
        F(0x154) = lbl_806D56F8;
        switch (S8(0x190)) {
        case 1:
            U32(0x180) = 5;
            break;
        case 2:
            U32(0x180) = 15;
            break;
        case 3:
            U32(0x180) = 35;
            break;
        }
        STATE++;
    case 1:
        break;
    }

    F(0xA8) -= lbl_806D5738;
    if (U32(0x180) == 0) {
        F(0x154) -= lbl_806D5718;
        if (F(0x154) < lbl_806D571C) {
            DrawEffect_Free(self);
            return;
        }
    }
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    F(0xB0) = F(0x150) * F(0x154);
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
