/* EffectVfx88_DustHelix_Tick (0x800C27D4): tumbling dust chunk (resource
 * 0x88) thrown out in a random direction; its horizontal speed decays,
 * it falls with a tumble-dependent rate and follows the kart's motion.
 * It fades after 10 frames, or 120 when spawned without a kart. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D53E8; /* 0.8 */
extern const float lbl_806D53EC; /* deg->rad */
extern const float lbl_806D53F0; /* -180.0 */
extern const float lbl_806D53F4; /* 180.0 */
extern const float lbl_806D53F8; /* -10.0 */
extern const float lbl_806D53FC; /* 10.0 */
extern const float lbl_806D5400; /* 0.0 */
extern const float lbl_806D5404; /* 4.0 */
extern const float lbl_806D5408; /* 1.2 */
extern const float lbl_806D540C; /* 0.5 */
extern const float lbl_806D5410; /* 1.5 */
extern const float lbl_806D5414; /* 0.05 */
extern const float lbl_806D5418; /* -0.05 */
extern const float lbl_806D541C; /* -0.2 */
extern void VfxSlot_BindResource(void *slot, int res);
extern float FAbs_FloatAsDouble(float x);
extern double cos(double x);
extern void Vec3_ScaleXZ(Vec *out, const Vec *in, float s);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);

void EffectVfx88_DustHelix_Tick(unsigned char *self)
{
    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x88);
        F(0xB0) = lbl_806D53E8;
        if (P(0x11C) == 0) {
            U32(0x180) = 120;
        } else {
            U32(0x180) = 10;
        }
        F(0x98) = lbl_806D53EC * Rand_RangeFloat(lbl_806D53F0, lbl_806D53F4);
        F(0x9C) = lbl_806D53EC * Rand_RangeFloat(lbl_806D53F0, lbl_806D53F4);
        F(0x150) = lbl_806D53EC * Rand_RangeFloat(lbl_806D53F8, lbl_806D53FC);
        F(0x154) = lbl_806D53EC * Rand_RangeFloat(lbl_806D53F8, lbl_806D53FC);
        GetSpawnPosition(V(0xA4), 0.0f, 0.0f, lbl_806D5404 * Rand_RangeFloat(lbl_806D53E8, lbl_806D5408));
        Vec2_RotateY(V(0xA4), V(0xA4), lbl_806D53EC * Rand_RangeFloat(lbl_806D53F0, lbl_806D53F4));
        if (P(0x11C) != 0) {
            Mtx44_GetTranslation_RowMajor(V(0x120), KartDriver_GetKartRootMtx(P(0x11C)));
        }
        F(0x158) = Rand_RangeFloat(lbl_806D540C, lbl_806D5410);
        STATE++;
    case 1:
        if (U32(0x180) == 0) {
            F(0x2C) -= lbl_806D5414;
            if (F(0x2C) <= lbl_806D5400) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }

    F(0x98) = BuildOrientationFromYaw(F(0x98) + F(0x150));
    F(0x9C) = BuildOrientationFromYaw(F(0x9C) + F(0x154));
    F(0xA8) = F(0x158) * (lbl_806D541C * FAbs_FloatAsDouble((float)cos(F(0x98))) + lbl_806D5418);
    Vec3_ScaleXZ(V(0xA4), V(0xA4), lbl_806D53E8);
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    if (P(0x11C) != 0) {
        Vec kartPos;
        Vec delta;
        Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(P(0x11C)));
        Vec3_Subtract_DestFirst(&delta, &kartPos, V(0x120));
        Vec3_Add_DestFirst(V(0x8C), V(0x8C), &delta);
        Vec3_Copy(V(0x120), &kartPos);
    }
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    {
        Vec rot = *V(0x98);
        VfxSlot_SetRotationXYZFromVec(SLOT(self), &rot);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    if (U32(0x180) != 0) {
        U32(0x180)--;
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        S8(0x28) = 0;
    } else {
        S8(0x28) = 1;
    }
}
