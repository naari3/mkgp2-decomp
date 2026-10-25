/* ItemObject_ChainShell_BoundOrbit_Sub (0x800E5380): per-frame motion of a
 * chain shell bound to a kart. State 0 picks a hit rebound or captures the
 * launch offset, state 1 slides along the bound direction, state 2 bounces
 * up once and then fades out. The world position is always the kart
 * position plus the stored offset. */
#include "game/DrawEffectAccess.h"

typedef struct ChainShellWork {
    unsigned char hitOnFade;
    unsigned char rebound;
    unsigned char pad2[2];
    unsigned int timer;
    unsigned char pad8[0x34 - 8];
    Vec vel;
    Vec offset;
    unsigned char pad4C[0x9C - 0x4C];
    void *kart;
} ChainShellWork;

extern const float lbl_806D5CD0; /* 0.0 */
extern const float lbl_806D5CD4; /* 1.0 */
extern const float lbl_806D5CE4; /* 2.0 */
extern const float lbl_806D5CE8; /* 0.02 */
extern const float lbl_806D5CEC; /* 0.05 */
extern const float lbl_806D5CF0; /* -0.1 */
extern const float lbl_806D5CF4; /* 3 deg */
extern void Item_PrepareHitRebound(unsigned char *self, Vec *offset, Vec *vel, unsigned int *timer);
extern void Vec3_AddNormalizedXZ(unsigned char *self, Vec *dst, Vec *dir);
extern void ItemHit_Dispatch(unsigned char *self, int kind, Vec *pos, void *kart);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);

void ItemObject_ChainShell_BoundOrbit_Sub(unsigned char *self, ChainShellWork *w)
{
    Vec kartPos;

    Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(w->kart));
    switch (S8(0xC9)) {
    case 0:
        if (w->rebound) {
            Item_PrepareHitRebound(self, &w->offset, &w->vel, &w->timer);
            S8(0xC9) = 1;
            S8(0xCA) = 0;
        } else {
            Vec3_Copy(&w->vel, V(0xB8));
            GetSpawnPosition(V(0xB8), lbl_806D5CD0, lbl_806D5CD0, lbl_806D5CD0);
            Vec3_Subtract_DestFirst(&w->offset, V(0xA0), &kartPos);
            S8(0xC9) = 2;
            S8(0xCA) = 0;
        }
        break;
    case 1: {
        Vec dir = w->vel;
        Vec3_AddNormalizedXZ(self, &w->offset, &dir);
        if (w->timer == 0) {
            S8(0xC9) = 2;
            S8(0xCA) = 0;
        }
        break;
    }
    case 2:
        switch (S8(0xCA)) {
        case 0:
            if (w->hitOnFade) {
                ItemHit_Dispatch(self, 0, V(0xA0), w->kart);
            }
            w->vel.y = lbl_806D5CE4;
            w->vel.x *= lbl_806D5CE8;
            w->vel.z *= lbl_806D5CE8;
            w->timer = 10;
            S8(0xCA)++;
        case 1:
            break;
        }
        if (w->timer == 0) {
            F(0x2C) -= lbl_806D5CEC;
            if (F(0x2C) < lbl_806D5CD0) {
                U8(0x28) = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
                return;
            }
        }
        w->vel.y += lbl_806D5CF0;
        Vec3_Add_DestFirst(&w->offset, &w->offset, &w->vel);
        F(0xAC) = BuildOrientationFromYaw(lbl_806D5CF4 + F(0xAC));
        break;
    }
    Vec3_Add_DestFirst(V(0xA0), &kartPos, &w->offset);
    Item_DecayVelocityScalar(self, lbl_806D5CD4);
    if (FinalLapCoinJump_CheckActiveForObject(w->kart)) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
