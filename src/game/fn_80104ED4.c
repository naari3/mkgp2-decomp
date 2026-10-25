/* fn_80104ED4 (0x80104ED4): bounce-off/settle motion of a dropped item.
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

extern const float lbl_806D65E0; /* 0.0 */
extern const float lbl_806D65E4; /* 1.0 */
extern const float lbl_806D65F4; /* 10 deg */
extern const float lbl_806D65FC; /* 0.05 */
extern const float lbl_806D6624; /* -0.1 */
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);

void fn_80104ED4(unsigned char *self, DropWork *w)
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
            F(0xBC) = lbl_806D65E0;
        }
        if (w->kart != 0) {
            Vec kartPos;
            Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(w->kart));
            Vec3_Subtract_DestFirst(&w->offset, V(0xA0), &kartPos);
            Vec3_Copy(&w->vel, V(0xB8));
            GetSpawnPosition(V(0xB8), lbl_806D65E0, lbl_806D65E0, lbl_806D65E0);
        }
        SpriteSlot_SetAnimFrameAndApplyScale(SLOT(self), 0, lbl_806D65E0);
        SpriteSlot_SetScale(SLOT(self), lbl_806D65E4);
        S8(0xC9)++;
    case 1:
        break;
    }

    if (w->timer == 0) {
        F(0x2C) -= lbl_806D65FC;
        if (F(0x2C) < lbl_806D65E0) {
            U8(0x28) = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        }
    }
    if (w->kart == 0) {
        float groundY;
        if ((int)U8(0xCB) != 5) {
            F(0xBC) += lbl_806D6624;
        }
        if (ItemObject_GetGroundTypeAt(*V(0xA0), &groundY, 0)) {
            F(0xA4) += groundY - w->groundY;
            w->groundY = groundY;
        }
    } else {
        Vec kartPos;
        w->vel.y += lbl_806D6624;
        Vec3_Add_DestFirst(&w->offset, &w->offset, &w->vel);
        Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(w->kart));
        Vec3_Add_DestFirst(V(0xA0), &kartPos, &w->offset);
    }
    switch (S8(0xCB)) {
    case 1:
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - lbl_806D65F4);
        break;
    case 4:
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - lbl_806D65F4);
        break;
    case 7:
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - lbl_806D65F4);
        break;
    case 9:
        F(0xAC) = BuildOrientationFromYaw(lbl_806D65F4 + F(0xAC));
        break;
    }
}
