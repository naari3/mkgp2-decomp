/* DrawEffect_KartSpark_Update (0x800CABEC): spark (resource 0x13/0x14, or
 * 0x84/0x85 for tier 4) trailing a tracked item at a random offset; it
 * fades once the item stops homing or its 10..40-frame timer runs out. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D56FC; /* 0.4 */
extern const float lbl_806D5700; /* 2.0 */
extern const float lbl_806D5704; /* 0.5 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D570C; /* -10.0 */
extern const float lbl_806D5710; /* 10.0 */
extern const float lbl_806D5714; /* -5.0 */
extern const float lbl_806D5718; /* 0.2 */
extern const float lbl_806D571C; /* 0.0 */
extern int Rand_RangeIntMax(int max);
extern int Rand_RangeInt(int lo, int hi);
extern int Item_AdvanceTrackedHomingState(void *item, Vec *offset, float k);

void DrawEffect_KartSpark_Update(unsigned char *self)
{
    switch (STATE) {
    case 0:
        if (P(0xCC) == 0) {
            DrawEffect_Free(self);
            return;
        }
        if ((int)U8(0x190) == 4) {
            if (Rand_RangeIntMax(15) < 10) {
                VfxSlot_BindResourceEx(SLOT(self), 0x84, 0);
            } else {
                VfxSlot_BindResourceEx(SLOT(self), 0x85, 0);
            }
        } else if (Rand_RangeIntMax(16) % 4) {
            VfxSlot_BindResourceEx(SLOT(self), 0x14, 0);
        } else {
            VfxSlot_BindResourceEx(SLOT(self), 0x13, 0);
        }
        S8(0x28) = 1;
        if ((int)U8(0x190) == 4) {
            F(0x2C) = lbl_806D56F8;
        } else {
            F(0x2C) = lbl_806D56FC;
        }
        if ((int)U8(0x190) == 4) {
            F(0x150) = lbl_806D5700 * Rand_RangeFloat(lbl_806D5704, lbl_806D5708);
        } else {
            F(0x150) = Rand_RangeFloat(lbl_806D5704, lbl_806D5708);
        }
        F(0x154) = lbl_806D56F8;
        F(0x120) = Rand_RangeFloat(lbl_806D570C, lbl_806D5710);
        F(0x124) = lbl_806D5714;
        F(0x128) = Rand_RangeFloat(lbl_806D570C, lbl_806D5710);
        U32(0x180) = Rand_RangeInt(10, 40);
        STATE++;
    case 1:
        break;
    }

    if (Item_AdvanceTrackedHomingState(P(0xCC), V(0x120), lbl_806D56F8) == 1 || U32(0x180) == 0) {
        F(0x2C) -= lbl_806D5718;
        if (F(0x2C) < lbl_806D571C) {
            S8(0x28) = 0;
            DrawEffect_Free(self);
            return;
        }
    }
    Vec3_Add_DestFirst(V(0x8C), V_(P(0xCC), 0xA0), V(0x120));
    F(0xB0) = F(0x150) * F(0x154);
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
