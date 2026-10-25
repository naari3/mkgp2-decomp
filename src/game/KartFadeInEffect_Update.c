#include "game/DrawEffectAccess.h"

void KartFadeInEffect_Update(unsigned char *self)
{
    Vec root;
    Vec pos;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x92, 0);
        F(0x150) = 0.0f;
        Mtx44_GetTranslation_RowMajor(V(0x120), KartDriver_GetKartRootMtx(P(0x11C)));
        Vec3_Subtract_DestFirst(V(0x120), V(0x8C), V(0x120));
        STATE++;
        break;
    case 1:
        break;
    }
    F(0x150) += 0.14285715f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    F(0xB0) = 3.0f * F(0x150);
    F(0x2C) = 1.0f - F(0x150);
    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(P(0x11C)));
    Vec3_Add_DestFirst(V(0x8C), &root, V(0x120));
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
}
