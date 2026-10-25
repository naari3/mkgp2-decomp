/* DrawEffect_KartDustRing_Update (0x800CAE78): coloured dust puff
 * (resource 0x6D) trailing a tracked item at a random offset. The colour
 * comes from the tier in +0x190; it grows and fades once the item stops
 * homing or its 5..10-frame timer runs out. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5700; /* 2.0 */
extern const float lbl_806D570C; /* -10.0 */
extern const float lbl_806D5710; /* 10.0 */
extern const float lbl_806D5714; /* -5.0 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5720; /* 0.8 */
extern const float lbl_806D5724; /* 1.2 */
extern const float lbl_806D5728; /* 0.1 */
typedef struct DustColors { Vec tier1; Vec tier2; Vec tier3; } DustColors;
extern DustColors lbl_8041A4D0;
extern int Rand_RangeInt(int lo, int hi);
extern int Item_AdvanceTrackedHomingState(void *item, Vec *offset, float k);

void DrawEffect_KartDustRing_Update(unsigned char *self)
{
    DustColors *colors = &lbl_8041A4D0;

    switch (STATE) {
    case 0:
        if (P(0xCC) == 0) {
            DrawEffect_Free(self);
            return;
        }
        VfxSlot_BindResourceEx(SLOT(self), 0x6D, 0);
        switch (S8(0x190)) {
        case 1:
            Vec3_Copy(V(0x30), &colors->tier1);
            break;
        case 2:
            Vec3_Copy(V(0x30), &colors->tier2);
            break;
        case 3:
            Vec3_Copy(V(0x30), &colors->tier3);
            break;
        }
        S8(0x28) = 1;
        F(0x2C) = lbl_806D56F8;
        F(0x150) = lbl_806D5700 * Rand_RangeFloat(lbl_806D5720, lbl_806D5724);
        F(0x154) = lbl_806D56F8;
        F(0x120) = Rand_RangeFloat(lbl_806D570C, lbl_806D5710);
        F(0x124) = lbl_806D5714;
        F(0x128) = Rand_RangeFloat(lbl_806D570C, lbl_806D5710);
        U32(0x180) = Rand_RangeInt(5, 10);
        STATE++;
    case 1:
        break;
    }

    if (Item_AdvanceTrackedHomingState(P(0xCC), V(0x120), lbl_806D56F8) == 1 || U32(0x180) == 0) {
        F(0x154) += lbl_806D5728;
        F(0x2C) -= lbl_806D5728;
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
