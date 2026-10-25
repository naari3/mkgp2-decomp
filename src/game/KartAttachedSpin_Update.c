/* KartAttachedSpin_Update (0x800B1444): spinning sprite (id 0x96) launched
 * in a random direction from the kart. It follows the kart's movement,
 * spins, sinks slowly and fades out after 10 frames. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5034; /* 0.0 */
extern const float lbl_806D5040; /* 2.0 */
extern const float lbl_806D5044; /* 0.1 */
extern const float lbl_806D5074; /* -0.1 */
extern const float lbl_806D507C; /* 1.5 */
extern const float lbl_806D5080; /* deg->rad */
extern const float lbl_806D5084; /* -90.0 */
extern const float lbl_806D5088; /* -45.0 */
extern const float lbl_806D508C; /* -180.0 */
extern const float lbl_806D5090; /* 180.0 */
extern const float lbl_806D5094; /* -10 deg */
extern void SpriteSlot_InitNonLoop(void *slot, int id);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
extern void SpriteSlot_Container_Free(unsigned char *self);

void KartAttachedSpin_Update(unsigned char *self)
{
    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(SLOT(self), 0x96);
        GetSpawnPosition(V(0xB8), 0.0f, 0.0f, Rand_RangeFloat(lbl_806D507C, lbl_806D5040));
        Vec2_RotateX(V(0xB8), V(0xB8), lbl_806D5080 * Rand_RangeFloat(lbl_806D5084, lbl_806D5088));
        Vec2_RotateY(V(0xB8), V(0xB8), lbl_806D5080 * Rand_RangeFloat(lbl_806D508C, lbl_806D5090));
        if (P(0x188) != 0) {
            Mtx44_GetTranslation_RowMajor(V(0x120), KartDriver_GetKartRootMtx(P(0x188)));
        }
        U32(0xF0) = 10;
        S8(0xC8)++;
    case 1:
        break;
    }

    if (U32(0xF0) == 0) {
        F(0x2C) -= lbl_806D5044;
        if (F(0x2C) < lbl_806D5034) {
            SpriteSlot_Container_Free(self);
            return;
        }
    }
    F(0xAC) = BuildOrientationFromYaw(lbl_806D5094 + F(0xAC));
    F(0xBC) += lbl_806D5074;
    if (P(0x188) != 0) {
        Vec kartPos;
        Vec delta;
        Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(P(0x188)));
        Vec3_Subtract_DestFirst(&delta, &kartPos, V(0x120));
        Vec3_Add_DestFirst(V(0xA0), V(0xA0), &delta);
        Vec3_Copy(V(0x120), &kartPos);
    }
    Vec3_Add_DestFirst(V(0xA0), V(0xA0), V(0xB8));
    SpriteSlot_SetTransform(SLOT(self), *V(0xA0), *V(0xAC), F(0xC4));
    if (U32(0xF0) != 0) U32(0xF0)--;
    if (U32(0xF4) != 0) U32(0xF4)--;
    if (U32(0xF8) != 0) U32(0xF8)--;
    if (U32(0xFC) != 0) U32(0xFC)--;
}
