typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct ItemBendParam { float a, b, c; } ItemBendParam;

extern float KartFxParam_GetConst1p5(void *kart);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void KartDriver_TransformWorldToLocalY0(void *dst, Vec3 *src, void *kart);
extern float Vec3_ToYaw(void *v);
extern void Item_BendVelocityByGroundProbe(void *vel, Vec3 *pos, float yaw, float speed, float pitch);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B14B8(void *kart, void *target);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec3 *pos, Vec3 *v);
extern void ItemHit_Dispatch(unsigned char *self, int a, int b, int c);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void Item_ComputeBiasedTargetPos(void *dst, Vec3 *pos, void *target);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec3 *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec3 *n, int a, int b, float k1, float k2);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, Vec3 *n);
extern float Item_ProbeForwardGroundPitch(Vec3 *pos, float yaw, float a, float b);
extern void Vec3_OrthoProjectThenScaleByLen(void *dst, Vec3 *v, Vec3 *n);
extern void Vec3_Scale(void *dst, void *src, float k);
extern float Vec3_Magnitude_Wrapper(void *v);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, int id, int flag);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);

extern ItemBendParam lbl_80421B30[7];

void fn_80108484(unsigned char *self, unsigned char *sub)
{
    Vec3 n;
    Vec3 local;
    Vec3 bend;
    Vec3 apPos;
    Vec3 apVel;
    Vec3 bias;
    Vec3 wall;
    Vec3 gpos;
    Vec3 ppos;
    Vec3 vel;
    Vec3 nrm2;
    float gy;
    int hit;
    float pitch;

    switch ((signed char)self[0xC9]) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:

    switch ((signed char)self[0xCA]) {
    case 0:
        self[0x28] = 1;
        *(float *)(self + 0x2C) = 1.0f;
        *(float *)(self + 0xC4) = 0.8f * KartFxParam_GetConst1p5(*(void **)(sub + 0x98));
        Mtx44_GetTranslation_RowMajor(self + 0xA0, KartDriver_GetJointByIdx(*(void **)(sub + 0x98), 0xC));
        local = *(Vec3 *)(self + 0xA0);
        KartDriver_TransformWorldToLocalY0(self + 0xA0, &local, *(void **)(sub + 0x98));
        bend = *(Vec3 *)(self + 0xA0);
        Item_BendVelocityByGroundProbe(self + 0xB8, &bend, Vec3_ToYaw(sub + 0xA4), 5.0f,
                                       lbl_80421B30[*(int *)(self + 0x10)].a);
        Vec2_RotateY(self + 0xB8, self + 0xB8, lbl_80421B30[*(int *)(self + 0x10)].b);
        *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x8D] = 1;
        self[0x3C] = 1;
        *(int *)(sub + 0x4) = 900;
        ItemHitRegistry_AddEntry(self);
        *(int *)(sub + 0x8) = 0;
        self[0xCA]++;
    case 1:
        *(float *)(self + 0xBC) += -0.1f;
        Item_HomingScanAndSteer(self, self + 0xB0, 1);
        break;
    case 2:
        break;
    }

    Item_DecayVelocityScalar(self, 2.0f);
    hit = ItemCollision_Check(self);
    switch (hit) {
    case 1:
        fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(*(int *)(self + 0x8)), 0);
    case 2:
        if (hit == 2) {
            fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        }
    case 3:
        if (hit == 3) {
            fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        }
        if (*(char *)(self + 0xCA) == 1 && hit == 3) {
            *(int *)(sub + 0x7C) = 0;
            apVel = *(Vec3 *)(self + 0xB8);
            apPos = *(Vec3 *)(self + 0xA0);
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), &apPos, &apVel);
            ItemTracker_SetTrackPhase(self, 0);
            *(int *)(sub + 0x8) = 5;
            break;
        }
        if (hit == 1) {
            ItemHit_Dispatch(self, 0, 0, 0);
        }
        *(void **)(sub + 0x9C) = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        bias = *(Vec3 *)(self + 0xA0);
        Item_ComputeBiasedTargetPos(self + 0xA0, &bias, *(void **)(sub + 0x9C));
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        self[0xC8] = 2;
        self[0xC9] = 0;
        self[0xCB] = 0;
        return;
    case 4:
        fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        *(void **)(sub + 0x9C) = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        self[0xC8] = 2;
        self[0xC9] = 0;
        self[0xCB] = 3;
        return;
    case 5:
        ItemTracker_SetTrackPhase(self, 1);
        break;
    }

    if (*(unsigned int *)(sub + 0x8) == 0) {
        ItemTracker_SetTrackPhase(self, 1);
    }
    if (*(char *)(self + 0x8D) == 2) {
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        if (*(char *)(self + 0x8E) == 1) {
            GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
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
    if (*(char *)(self + 0xCA) == 1) {
        if (Item_CheckWallCollision(self, &n, 0)) {
            wall = n;
            Item_BounceOffWall(self, &wall, 0, 0, 0.2f, 0.0f);
            *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
        }
        gpos = *(Vec3 *)(self + 0xA0);
        if (ItemObject_GetGroundTypeAt(&gpos, &gy, &n)) {
            if (*(float *)(self + 0xA4) < 1.5f * *(float *)(self + 0xC4) + gy) {
                *(float *)(self + 0xA4) = 1.5f * *(float *)(self + 0xC4) + gy;
                ppos = *(Vec3 *)(self + 0xA0);
                pitch = Item_ProbeForwardGroundPitch(&ppos, *(float *)(self + 0xB0), 1.0f,
                                                     1.5f * *(float *)(self + 0xC4));
                GetSpawnPosition(&n, 0.0f, 1.0f, 0.0f);
                Vec2_RotateX(&n, &n, pitch);
                Vec2_RotateY(&n, &n, *(float *)(self + 0xB0));
                nrm2 = n;
                vel = *(Vec3 *)(self + 0xB8);
                Vec3_OrthoProjectThenScaleByLen(self + 0xB8, &vel, &nrm2);
                Vec3_Scale(self + 0xB8, self + 0xB8, 0.5f);
                if (Vec3_Magnitude_Wrapper(self + 0xB8) < 1.0f) {
                    GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                    self[0xCA] = 2;
                }
            }
        } else {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 9;
            return;
        }
    }
    if (ItemHitRegistry_RemoveEntry(self, *(int *)(sub + 0x4), 0)) {
        ItemTracker_ReleaseLock(self);
        self[0x8D] = 0;
        if (*(int *)(self + 0x10) == 0) {
            ItemObject_DecrementCategoryBudget(self);
        }
        SpriteSlot_Container_Free(self);
    }
    }
}
