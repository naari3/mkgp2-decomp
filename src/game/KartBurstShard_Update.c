/* KartBurstShard_Update (0x800B1DB0): one shard of the kart burst (resource
 * 0x81). It spins, drifts by its velocity, starts falling after a random
 * delay and follows the kart's movement for 20 frames. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5054; /* 10.0 */
extern const float lbl_806D5074; /* -0.1 */
extern const float lbl_806D5080; /* deg->rad */
extern const float lbl_806D508C; /* -180.0 */
extern const float lbl_806D5090; /* 180.0 */
extern const float lbl_806D50AC; /* 0.5 */
extern const float lbl_806D50B0; /* 0.7 */
extern const float lbl_806D50B4; /* 1.3 */
extern const float lbl_806D50B8; /* -10.0 */
extern int Rand_RangeInt(int lo, int hi);

void KartBurstShard_Update(unsigned char *self)
{
    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x81, 0);
        F(0xB0) = lbl_806D50AC * Rand_RangeFloat(lbl_806D50B0, lbl_806D50B4);
        F(0xA0) = lbl_806D5080 * Rand_RangeFloat(lbl_806D508C, lbl_806D5090);
        F(0x150) = lbl_806D5080 * Rand_RangeFloat(lbl_806D50B8, lbl_806D5054);
        U32(0x180) = 0x14;
        U32(0x184) = Rand_RangeInt(5, 0xF);
        if (P(0x11C) != 0) {
            Mtx44_GetTranslation_RowMajor(V(0x120), KartDriver_GetKartRootMtx(P(0x11C)));
        }
        STATE++;
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        DrawEffect_Free(self);
        return;
    }
    if (U32(0x184) == 0) {
        F(0xA8) += lbl_806D5074;
    }
    F(0xA0) = BuildOrientationFromYaw(F(0xA0) + F(0x150));
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
    if (P(0x11C) != 0) {
        Vec now;
        Vec delta;
        Mtx44_GetTranslation_RowMajor(&now, KartDriver_GetKartRootMtx(P(0x11C)));
        Vec3_Subtract_DestFirst(&delta, &now, V(0x120));
        Vec3_Add_DestFirst(V(0x8C), V(0x8C), &delta);
        Vec3_Copy(V(0x120), &now);
    }
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
