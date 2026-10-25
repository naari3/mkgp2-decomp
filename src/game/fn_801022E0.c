/* fn_801022E0 (0x801022E0): bounce-off/settle motion of a dropped item.
 * Bound to a kart it keeps its offset and falls; free it settles on the
 * ground. It fades out after 10 frames (immediately for kind 5) and spins
 * by kind. */
#include "game/DrawEffectAccess.h"

typedef struct DropWork {
    unsigned char pad0[4];
    unsigned int timer;
    unsigned char pad8[0x14 - 8];
    float groundY;
    unsigned char pad18[0x34 - 0x18];
    Vec offset;
    Vec vel;
    unsigned char pad4C[0x9C - 0x4C];
    void *kart;
} DropWork;

extern const float lbl_806D64E8; /* 0.0 */
extern const float lbl_806D64EC; /* 1.0 */
extern const float lbl_806D64F0; /* 2.0 */
extern const float lbl_806D64F4; /* 1.5 */
extern const float lbl_806D6500; /* 3 deg */
extern const float lbl_806D6548; /* 0.05 */
extern const float lbl_806D6544; /* -0.2 */
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);

void fn_801022E0(unsigned char *self, DropWork *w)
{
    switch (S8(0xC9)) {
    case 0:
        ItemObject_GetGroundTypeAt(*V(0xA0), &w->groundY, 0);
        if ((int)U8(0xCB) != 5) {
            w->timer = 10;
        } else {
            w->timer = 0;
        }
        if ((int)U8(0xCB) == 5) {
            F(0xBC) = lbl_806D64E8;
        }
        if (w->kart != 0) {
            Vec kartPos;
            Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(w->kart));
            Vec3_Subtract_DestFirst(&w->offset, V(0xA0), &kartPos);
            Vec3_Copy(&w->vel, V(0xB8));
            GetSpawnPosition(V(0xB8), lbl_806D64E8, lbl_806D64E8, lbl_806D64E8);
        }
        if ((int)U8(0x1D) == 1) {
            SpriteSlot_SetAnimFrameAndApplyScale(SLOT(self), 2, lbl_806D64E8);
            SpriteSlot_SetScale(SLOT(self), lbl_806D64EC);
        }
        S8(0xC9)++;
    case 1:
        break;
    }

    if (w->timer == 0) {
        F(0x2C) -= lbl_806D6548;
        if (F(0x2C) < lbl_806D64E8) {
            U8(0x28) = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        }
    }
    if (w->kart == 0) {
        float groundY;
        if ((int)U8(0xCB) != 5) {
            F(0xBC) += lbl_806D6544;
        }
        if (ItemObject_GetGroundTypeAt(*V(0xA0), &groundY, 0)) {
            F(0xA4) += groundY - w->groundY;
            w->groundY = groundY;
        }
    } else {
        Vec kartPos;
        w->vel.y += lbl_806D6544;
        Vec3_Add_DestFirst(&w->offset, &w->offset, &w->vel);
        Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(w->kart));
        Vec3_Add_DestFirst(V(0xA0), &kartPos, &w->offset);
    }
    switch (S8(0xCB)) {
    case 1:
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - lbl_806D6500);
        break;
    case 4:
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - lbl_806D6500);
        break;
    case 7:
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - lbl_806D6500);
        break;
    case 9:
        F(0xAC) = BuildOrientationFromYaw(lbl_806D6500 + F(0xAC));
        break;
    }
    if (I(0x8) == 0x59) {
        Item_DecayVelocityScalar(self, lbl_806D64F0);
    } else {
        Item_DecayVelocityScalar(self, lbl_806D64F4);
    }
}
