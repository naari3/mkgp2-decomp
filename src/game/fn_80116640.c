#include "game/types/Vec.h"

extern double sin(double);
extern float BuildOrientationFromYaw(float yaw);
extern int ItemCollision_Check(unsigned char *self);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void Item_BounceOffWall(unsigned char *self, Vec n, int se, int flag, float k1, float k2);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec pos, Vec v);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern float Vec3_ToYaw(void *v);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))

#pragma exceptions on
void fn_80116640(unsigned char *self, unsigned char *w)
{
    Vec n;
    float y;
    int hit;

    switch (S8(0xCA)) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x3C] = 1;
        WU(0x8) = 0;
        WF(0x14) = 0.0f;
        self[0xCA]++;
    case 1:
        break;
    }
    Item_DecayVelocityScalar(self, 2.0f);
    F(0xBC) += -0.1f;
    {
        float s = sin(WF(0x14));
        F(0xC4) = F(0xC4) / (0.2f * s + 1.0f);
    }
    WF(0x14) = BuildOrientationFromYaw(0.34906578f + WF(0x14));
    {
        float s = sin(WF(0x14));
        F(0xC4) = F(0xC4) * (0.1f * s + 1.0f);
    }

    hit = ItemCollision_Check(self);
    switch (hit) {
    case 0:
        break;
    case 1:
    case 2:
        WP(0x9C) = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        if (hit == 1) {
            w[0] = 1;
        } else {
            w[0] = 0;
        }
        self[0xC8] = 2;
        self[0xC9] = 0;
        self[0xCB] = 0;
        return;
    case 3:
        *(int *)(w + 0x7C) = 0;
        Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self),
                                        *(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8));
        F(0xB0) = Vec3_ToYaw(self + 0xB8);
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
    if (Item_CheckWallCollision(self, &n, 0)) {
        Item_BounceOffWall(self, n, 0xCB, 2, 0.05f, 2.0f);
        F(0xB0) = Vec3_ToYaw(self + 0xB8);
    }
    if (ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &y, 0)) {
        if (F(0xA4) < y) {
            F(0xA4) = y;
            F(0xBC) = 1.5f;
            ItemTracker_ReleaseLock(self);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 8;
        }
    } else {
        ItemTracker_ReleaseLock(self);
        self[0xC8] = 2;
        self[0xC9] = 0;
        self[0xCB] = 9;
    }
}
#pragma exceptions reset
