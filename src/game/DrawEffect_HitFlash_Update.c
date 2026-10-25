#include "game/DrawEffectAccess.h"

extern const float lbl_806D56F8; /* 1.0 */
extern const float lbl_806D5700; /* 2.0 */
extern const float lbl_806D5708; /* 1.5 */
extern const float lbl_806D571C; /* 0.0 */
extern const float lbl_806D5728; /* 0.1 */
extern const float lbl_806D5734; /* 3.0 */
extern const float lbl_806D573C; /* 4.5 */

void DrawEffect_HitFlash_Update(unsigned char *self)
{
    Vec pos;
    Vec rot;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x1B, 0);
        switch (S8(0x190)) {
        case 1:
            F(0x154) = lbl_806D5708;
            break;
        case 2:
            F(0x154) = lbl_806D5734;
            break;
        case 3:
            F(0x154) = lbl_806D573C;
            break;
        }
        pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        rot = *V(0x98);
        VfxSlot_SetRotationXYZFromVec(SLOT(self), &rot);
        F(0x150) = lbl_806D571C;
        STATE++;
        break;
    case 1:
        break;
    }
    F(0x150) += 0.1f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    F(0x2C) = 1.0f - F(0x150);
    F(0xB0) = lbl_806D5700 * (F(0x150) * F(0x154));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
}
