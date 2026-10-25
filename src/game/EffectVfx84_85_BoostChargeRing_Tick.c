/* EffectVfx84_85_BoostChargeRing_Tick (0x800C0C7C): boost-charge spark
 * (resource 0x84/0x85) placed behind the kart around yaw +0x150, thrown
 * upward/backward in kart space; it rides with the kart, sinks and fades
 * after 10 frames. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51BC; /* 2.0 */
extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51CC; /* 5.0 */
extern const float lbl_806D51D4; /* 0.2 */
extern const float lbl_806D51E4; /* -20.0 */
extern const float lbl_806D51EC; /* 0.6 */
extern const float lbl_806D521C; /* deg->rad */
extern const float lbl_806D5248; /* 1.5 */
extern const float lbl_806D5250; /* -45.0 */
extern const float lbl_806D5280; /* 0.4 */
extern const float lbl_806D5338; /* 7.0 */
extern const float lbl_806D5388; /* -5.0 */
extern const float lbl_806D538C; /* 9.0 */
extern const float lbl_806D5390; /* 0.09 */
extern int Rand_RangeIntMax(int max);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec v);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);

void EffectVfx84_85_BoostChargeRing_Tick(unsigned char *self)
{
    float kart[4][4];
    Vec origin;
    float yaw;
    Vec pos;

    Mtx_TransposeToMtx44(kart, KartDriver_GetKartRootMtx(P(0x11C)));
    Mtx44_GetTranslation_ColMajor(&origin, kart);
    switch (STATE) {
    case 0:
        if (Rand_RangeIntMax(16) % 2) {
            VfxSlot_BindResourceEx(SLOT(self), 0x84, 0);
        } else {
            VfxSlot_BindResourceEx(SLOT(self), 0x85, 0);
        }
        yaw = BuildOrientationFromYaw(lbl_806D521C * Rand_RangeFloat(lbl_806D5388, lbl_806D51CC) + F(0x150));
        GetSpawnPosition(V(0x120), lbl_806D51C0, lbl_806D51BC, Rand_RangeFloat(lbl_806D5338, lbl_806D538C));
        Vec2_RotateY(V(0x120), V(0x120), yaw);
        Mtx44_TransformVec3(V(0x120), kart, *V(0x120));
        Vec3_Subtract_DestFirst(V(0x120), V(0x120), &origin);
        GetSpawnPosition(V(0xA4), 0.0f, 0.0f, Rand_RangeFloat(lbl_806D51C4, lbl_806D5248));
        Vec2_RotateX(V(0xA4), V(0xA4), lbl_806D521C * Rand_RangeFloat(lbl_806D5250, lbl_806D51E4));
        Vec2_RotateY(V(0xA4), V(0xA4), yaw);
        Mtx44_TransformVec3(V(0xA4), kart, *V(0xA4));
        Vec3_Subtract_DestFirst(V(0xA4), V(0xA4), &origin);
        F(0xB0) = Rand_RangeFloat(lbl_806D5280, lbl_806D51EC);
        F(0x2C) = lbl_806D51C4;
        U32(0x180) = 10;
        STATE++;
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        F(0x2C) -= lbl_806D51D4;
        if (F(0x2C) < lbl_806D51C0) {
            DrawEffect_Free(self);
            return;
        }
    }
    F(0xA8) -= lbl_806D5390;
    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    Vec3_Add_DestFirst(V(0x8C), &origin, V(0x120));
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        S8(0x28) = 0;
    } else {
        S8(0x28) = 1;
    }
}
