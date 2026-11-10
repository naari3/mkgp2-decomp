/* fn_80117494: state tick of an item that circles a fixed anchor point on
 * the ground: it orbits with a wobbling yaw, is pulled back onto a 100-unit
 * radius around the anchor, and leaves the tracking state on a kart hit, a
 * kart-held drop or when its hit-registry lifetime expires. A two-child
 * effect follows it and is released together with it.
 * Compiled as C++: the hit call's last parameter is a bool, and the int
 * ternary argument is normalised (neg/or/srwi) at the call. */
#pragma cplusplus on

extern "C" {

#include "game/types/Vec.h"

extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, unsigned int id, int flag);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_TwoChild_Res8F_Update(unsigned char *self);
extern float BuildOrientationFromYaw(float yaw);
extern float Vec3_HorizontalDistance(void *a, void *b);
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
extern double cos(double);

}

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(unsigned char **)(w + (o)))

static inline void PullToRadius(Vec *p, Vec *c, float d, float r)
{
    float dx = p->x - c->x;
    float dz = p->z - c->z;
    dx = r * (dx / d);
    dz = r * (dz / d);
    p->x = c->x + dx;
    p->z = c->z + dz;
}

#pragma use_lmw_stmw on

extern "C" void fn_80117494(unsigned char *self, unsigned char *w)
{
    int landed;
    Vec normal;
    Vec pos;
    float dist;
    int hit;

    switch (S8(0xCA)) {
    case 0:
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x8D] = 1;
        self[0x3C] = 1;
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
        WP(0x4C) = DrawEffect_SpawnDirect(Effect_TwoChild_Res8F_Update);
        WU(0x4) = 900;
        WU(0x8) = 0;
        WU(0xC) = 10;
        self[0xCA]++;
        ItemHitRegistry_AddEntry(self);
    case 1:
        if (WU(0xC) == 0) {
            WF(0x14) = 0.0f;
            WF(0x18) = 0.0f;
            WF(0x34) = F(0xA0);
            WF(0x3C) = F(0xA8);
            self[0xCA]++;
        }
        break;
    case 2:
        WF(0x14) = BuildOrientationFromYaw(0.10471973f + WF(0x14));
        WF(0x18) = BuildOrientationFromYaw(0.052359864f + WF(0x18));
        F(0xB0) = 0.34906578f * (float)sin(WF(0x18)) + WF(0x14);
        F(0xB8) = 3.0f * (float)sin(F(0xB0));
        F(0xC0) = 3.0f * (float)cos(F(0xB0));
        dist = Vec3_HorizontalDistance(self + 0xA0, w + 0x34);
        if (100.0f < dist) {
            PullToRadius((Vec *)(self + 0xA0), (Vec *)(w + 0x34), dist, 100.0f);
            WF(0x14) = BuildOrientationFromYaw(1.570796f + WF(0x14));
        }
        break;
    }
    F(0xBC) += -0.1f;
    Item_DecayVelocityScalar(self, 3.0f);
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
        WF(0x14) = BuildOrientationFromYaw(3.141592f + WF(0x14));
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
        WF(0x14) = BuildOrientationFromYaw(0.17453289f + WF(0x14));
        F(0xA0) = pos.x;
        F(0xA8) = pos.z;
    }
    if (Item_AdvanceFallingDrop(self, &landed, 0, 0.0f) && landed != 0) {
        F(0xBC) = 0.0f;
    }
    if (ItemHitRegistry_RemoveEntry(self, WU(0x4), 0)) {
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        if (WP(0x4C) != 0) {
            WP(0x4C)[0xC9] = 1;
        }
        WP(0x4C) = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
    }
}

#pragma use_lmw_stmw reset
