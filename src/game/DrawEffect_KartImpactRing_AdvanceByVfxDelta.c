#include "game/DrawEffectAccess.h"

extern unsigned char lbl_805DF3D0[];

void DrawEffect_KartImpactRing_AdvanceByVfxDelta(unsigned char *self, const Vec *origin, float speed, float alpha)
{
    Vec delta;
    Vec pos;

    if (self != 0) {
        Vec3_Subtract_DestFirst(&delta, origin, (Vec *)(lbl_805DF3D0 + 0x80));
        Vec3_Scale(&delta, &delta, speed * (2.0f * (1.0f / Vec3_Magnitude_Wrapper(&delta))));
        Vec3_Add_DestFirst(V(0x8C), origin, &delta);
        F(0xB0) = 1.5f * speed;
        F(0x150) += 0.02f;
        if (1.0f < F(0x150)) {
            F(0x150) = 1.0f;
        }
        F(0x2C) = alpha * F(0x150);
        pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
        U8(0x28) = 1;
    }
}
