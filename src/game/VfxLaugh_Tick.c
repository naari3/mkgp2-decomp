#include "game/DrawEffectAccess.h"


void VfxLaugh_Tick(unsigned char *self, const Vec *pos, signed char visible, float scale, float alpha)
{
    if (self != 0 && STATE) {
        S8(0x28) = visible;
        if (S8(0x28)) {
            int frames[3] = { 0, 1, 2 };
            float angles[3] = { -0.523598671f, 0.0f, 0.0f };
            unsigned char shown[3] = { 1, 1, 0 };
            signed char k;
            Vec p;

            S8(0x190)++;
            if (S8(0x190) >= 15) {
                S8(0x190) = 0;
            }
            k = frames[S8(0x190) / 5];
            Vec3_Copy(V(0x8C), pos);
            F(0xA0) = angles[k];
            F(0xB0) = scale;
            F(0x2C) = alpha;
            p = *V(0x8C);
            VfxSlot_SetPositionFromVec(SLOT(self), &p);
            VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
            VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
            U8(0x28) = shown[k];
        } else {
            S8(0x190) = 0;
        }
    }
}
