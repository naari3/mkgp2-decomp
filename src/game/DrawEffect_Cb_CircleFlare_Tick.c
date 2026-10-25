#include "game/DrawEffectAccess.h"

extern const float lbl_806D555C; /* 0.0 */
extern const float lbl_806D5588; /* pi/2 */
extern const float lbl_806D55A0; /* 0.05 */
extern const float lbl_806D55AC; /* 2.0 */
extern const float lbl_806D5630; /* 1.5 */

void DrawEffect_Cb_CircleFlare_Tick(unsigned char *self)
{
    Vec rot;
    Vec pos;

    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x8E);
        GetSpawnPosition(V(0xA4), lbl_806D555C, lbl_806D555C, lbl_806D5630);
        Vec2_RotateY(V(0xA4), V(0xA4), F(0x9C));
        F(0x9C) = BuildOrientationFromYaw(F(0x9C) - lbl_806D5588);
        rot = *V(0x98);
        VfxSlot_SetRotationXYZFromVec(SLOT(self), &rot);
        F(0xB0) = lbl_806D55AC;
        VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
        U32(0x180) = 5;
        STATE++;
        break;
    case 1:
        break;
    }
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    if (U32(0x180) == 0) {
        F(0x2C) -= lbl_806D55A0;
        if (F(0x2C) < lbl_806D555C) {
            U8(0x28) = 0;
            DrawEffect_Free(self);
            return;
        }
    }
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    TICK_TIMERS();
}
