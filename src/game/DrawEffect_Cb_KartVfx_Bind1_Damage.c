/* DrawEffect_Cb_KartVfx_Bind1_Damage (0x800B6534): kart-attached damage
 * billboard (resource 1) floated 5 units above the kart root and pulled
 * 2.5*scale towards the camera. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51CC; /* 5.0 */
extern const float lbl_806D5214; /* 4.0 */
extern const float lbl_806D5234; /* -2.5 */
extern unsigned char lbl_805DF3D0[];
extern float KartFxParam_GetConst1p5(void *driver);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], const Vec *in);

void DrawEffect_Cb_KartVfx_Bind1_Damage(unsigned char *self)
{
    float m[4][4];
    Vec off;
    Vec world;
    Vec tmp;
    Vec pos;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 1, 0);
        U8(0x28) = 1;
        F(0x2C) = lbl_806D51C4;
        STATE++;
    case 1:
        break;
    }

    if ((int)U8(0x1E) == 1) {
        U8(0x28) = 0;
        DrawEffect_Free(self);
        return;
    }

    F(0xB0) = lbl_806D5214 * KartFxParam_GetConst1p5(P(0x11C));
    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(P(0x11C)));
    GetSpawnPosition(&off, lbl_806D51C0, lbl_806D51CC, lbl_806D51C0);
    tmp = off;
    Mtx44_TransformVec3(&world, m, &tmp);
    Vec3_Subtract_DestFirst(&off, &world, (Vec *)(lbl_805DF3D0 + 0x80));
    Vec3_Scale(&off, &off, F(0xB0) * (lbl_806D5234 * (lbl_806D51C4 / Vec3_Magnitude_Wrapper(&off))));
    Vec3_Add_DestFirst(V(0x8C), &world, &off);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
