#include "game/types/c_region.h"
C_REGION_BEGIN
/* fn_80117E08: state tick of a floating item that bobs up and down on a
 * sine wave, spins slowly, and leaves the tracking state on a kart hit, a
 * kart-held drop or when its hit-registry lifetime expires.
 * Compiled as C++: the hit call's last parameter is a bool, and the int
 * ternary argument is normalised (neg/or/srwi) at the call. */
C_REGION_END
#pragma cplusplus on

extern "C" {

#include "game/types/Vec.h"

extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, unsigned int id, int flag);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void fn_801B1D5C(void *kart, void *target, int alias, bool flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void ItemHit_Dispatch(void *self, int kind, void *pos, void *kart);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec *normal, Vec *pos);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *landed, float *groundY, float f);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(unsigned char *self);
extern double sin(double);

}

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))

static inline float Bob(unsigned char *w)
{
    float s = (float)sin(0.017453289f * (720.0f * WF(0x14)));
    return 5.0f + 5.0f * s;
}

#pragma use_lmw_stmw on

extern "C" void fn_80117E08(unsigned char *self, unsigned char *w)
{
    float groundY;
    Vec normal;
    Vec pos;
    int hit;

    switch (S8(0xCA)) {
    case 0:
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x8D] = 1;
        self[0x3C] = 1;
        WU(0x4) = 900;
        WU(0x8) = 0;
        WU(0xC) = 10;
        WF(0x14) = 0.0f;
        self[0xCA]++;
        ItemHitRegistry_AddEntry(self);
    case 1:
        if (WU(0xC) == 0) {
            F(0xB8) = 0.0f;
            F(0xC0) = 0.0f;
            self[0xCA]++;
        }
        break;
    case 2:
        break;
    }
    F(0xBC) = -1.0f;
    Item_DecayVelocityScalar(self, 0.8f);
    hit = ItemCollision_Check(self);
    switch (hit) {
    case 1:
        fn_801B1D5C(WP(0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(8)),
                    S8(0xCA) == 2 ? 1 : 0);
    case 2:
        if (hit == 2) {
            fn_801B1660(WP(0x98), ItemTracker_GetTargetKart(self));
        }
        if (hit == 1) {
            ItemHit_Dispatch(self, 0, self + 0xA0, 0);
        }
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        self[0xC8] = 2;
        self[0xC9] = 0;
        self[0xCB] = 0;
        return;
    case 3:
        fn_801B158C(WP(0x98), ItemTracker_GetTargetKart(self));
        ItemTracker_SetTrackPhase(self, 0);
        WU(0x8) = 5;
        break;
    case 5:
        ItemTracker_SetTrackPhase(self, 1);
        break;
    }
    if (WU(0x8) == 0) {
        ItemTracker_SetTrackPhase(self, 1);
    }
    if (*(char *)(self + 0x8D) == 2) {
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        if (*(char *)(self + 0x8E) == 1) {
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 4;
            return;
        }
        self[0xC8] = 2;
        self[0xC9] = 0;
        self[0xCB] = 6;
        return;
    }
    if (Item_CheckWallCollision(self, &normal, &pos)) {
        F(0xA0) = pos.x;
        F(0xA8) = pos.z;
    }
    Item_AdvanceFallingDrop(self, 0, &groundY, 0.0f);
    F(0xA4) -= Bob(w);
    if (F(0xA4) + F(0xBC) < 8.0f + groundY) {
        F(0xA4) = 8.0f + groundY;
        F(0xBC) = 0.0f;
    }
    WF(0x14) += 0.004166667f;
    if (1.0f <= WF(0x14)) {
        WF(0x14) = 0.0f;
    }
    F(0xA4) += Bob(w);
    F(0xB0) += 0.2f * (float)sin(0.017453289f * (360.0f * WF(0x14)));
    if (F(0xB0) < 6.283184f) {
        F(0xB0) += 6.283184f;
    }
    if (6.283184f <= F(0xB0)) {
        F(0xB0) -= 6.283184f;
    }
    if (ItemHitRegistry_RemoveEntry(self, WU(0x4), 0)) {
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
    }
}

#pragma use_lmw_stmw reset
