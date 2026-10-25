/* Effect_KartGlow_Update (0x800C3CC8): glow (resource 0x49) orbiting the
 * kart at radius 8. It fades in while its timer runs and fades out after. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5400; /* 0.0 */
extern const float lbl_806D5410; /* 1.5 */
extern const float lbl_806D5414; /* 0.05 */
extern const float lbl_806D5424; /* 1.0 */
extern const float lbl_806D5448; /* 0.2 */
extern const float lbl_806D547C; /* 6 deg */
extern const float lbl_806D5480; /* 8.0 */
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], const Vec *in);

/* Only referenced through a hard-coded address in HeartCompoundItem.c, so
 * keep the linker from dead-stripping it. */
#pragma force_active on
void Effect_KartGlow_Update(unsigned char *self)
{
    float m[4][4];
    Vec tmp;
    Vec pos;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x49, 0);
        F(0x2C) = lbl_806D5400;
        F(0xB0) = lbl_806D5410;
        STATE++;
    case 1:
        break;
    }

    F(0x150) = BuildOrientationFromYaw(lbl_806D547C + F(0x150));
    if (U32(0x180) != 0) {
        F(0x2C) += lbl_806D5448;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
    } else {
        F(0x2C) -= lbl_806D5414;
        if (F(0x2C) < lbl_806D5400) {
            DrawEffect_Free(self);
            return;
        }
    }

    if (P(0x11C) != 0) {
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(P(0x11C)));
        GetSpawnPosition(V(0x8C), lbl_806D5400, lbl_806D5480, lbl_806D5480);
        Vec2_RotateY(V(0x8C), V(0x8C), F(0x150));
        tmp = *V(0x8C);
        Mtx44_TransformVec3(V(0x8C), m, &tmp);
    }
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
    TICK_TIMERS();
}
#pragma force_active reset
