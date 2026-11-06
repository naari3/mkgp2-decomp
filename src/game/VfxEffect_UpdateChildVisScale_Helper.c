/* Update the child effect fade, position, scale and visibility. */
#include "game/DrawEffectAccess.h"

extern void VfxSlot_SetScaleVec3(void *slot, float x, float y, float z);

void VfxEffect_UpdateChildVisScale_Helper(unsigned char *self, const Vec *position,
                                        float scale, float alpha)
{
    if (self != 0) {
        if (S8(0x190) != 0) {
            F(0x150) += 0.05f;
            if (1.0f < F(0x150)) {
                F(0x150) = 1.0f;
            }
        } else {
            F(0x150) -= 0.1f;
            if (F(0x150) < 0.0f) {
                F(0x150) = 0.0f;
            }
        }
        Vec3_Copy(V(0x8C), position);
        {
            Vec pos = *V(0x8C);
            VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        }
        F(0xB0) = scale;
        VfxSlot_SetScaleVec3(SLOT(self), 2.0f * F(0xB0),
                            2.2f * F(0xB0), F(0xB0));
        F(0x2C) = F(0x150) * alpha;
        U8(0x28) = 1;
    }
}
