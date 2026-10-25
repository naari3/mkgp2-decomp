typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern void ItemHitRegistry_AddEntry(void *self);
extern unsigned char ItemHitRegistry_RemoveEntry(void *self, int t, int a);
extern void Item_DecayVelocityScalar(void *self, float k);
extern int ItemCollision_Check(void *self);
extern short ItemAlias_HitRemapLookup(int itemId);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void GetSpawnPosition(float *out, float x, float y, float z);
extern int Item_CheckWallCollision(void *self, void *out, void *out2);
extern int Item_AdvanceFallingDrop(void *self, void *a, float *out, float f);
extern void ItemObject_DecrementCategoryBudget(void *self);
extern void SpriteSlot_Container_Free(void *self);
extern double sin(double);
extern const double lbl_806D6BD8;

void fn_80118858(char *self, char *sub)
{
    float groundY;
    Vec3 wallN;
    Vec3 wallPos;
    int collision;
    int alias;
    int lastHit;
    float s;
    float g;

    switch (*(signed char *)(self + 0xca)) {
    case 0:
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x8d] = 1;
        self[0x3c] = 1;
        *(int *)(sub + 4) = 900;
        *(int *)(sub + 8) = 0;
        *(int *)(sub + 0xc) = 10;
        *(float *)(sub + 0x14) = 0.0f;
        self[0xca]++;
        ItemHitRegistry_AddEntry(self);
    case 1:
        if (*(unsigned int *)(sub + 0xc) == 0) {
            *(float *)(self + 0xb8) = 0.0f;
            *(float *)(self + 0xc0) = 0.0f;
            self[0xca]++;
        }
        break;
    case 2:
        break;
    }
    *(float *)(self + 0xbc) = -1.0f;
    Item_DecayVelocityScalar(self, 1.0f);
    collision = ItemCollision_Check(self);
    switch (collision) {
    case 1:
        lastHit = *(signed char *)(self + 0xca) == 2;
        alias = ItemAlias_HitRemapLookup(*(int *)(self + 8));
        fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self), alias, !!lastHit);
        *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 0;
        return;
    case 2:
        fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 1;
        return;
    case 3:
        fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        ItemTracker_SetTrackPhase(self, 0);
        *(int *)(sub + 8) = 5;
        break;
    case 5:
        ItemTracker_SetTrackPhase(self, 1);
        break;
    }
    if (*(unsigned int *)(sub + 8) == 0) {
        ItemTracker_SetTrackPhase(self, 1);
    }
    if ((int)*(unsigned char *)(self + 0x8d) == 2) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
        if ((int)*(unsigned char *)(self + 0x8e) == 1) {
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 4;
            return;
        }
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 6;
        return;
    }
    if (Item_CheckWallCollision(self, &wallN, &wallPos) != 0) {
        *(float *)(self + 0xa0) = wallPos.x;
        *(float *)(self + 0xa8) = wallPos.z;
    }
    Item_AdvanceFallingDrop(self, 0, &groundY, 0.0f);
    s = sin(0.017453289f * (3.6e+02f * *(float *)(sub + 0x14)));
    *(float *)(self + 0xa4) = *(float *)(self + 0xa4) - (lbl_806D6BD8 * s + lbl_806D6BD8);
    if (*(float *)(self + 0xa4) + *(float *)(self + 0xbc) < 8.0f + groundY) {
        *(float *)(self + 0xa4) = 8.0f + groundY;
        *(float *)(self + 0xbc) = 0.0f;
    }
    *(float *)(sub + 0x14) += 0.01f;
    if (1.0f <= *(float *)(sub + 0x14)) {
        *(float *)(sub + 0x14) = 0.0f;
    }
    s = sin(0.017453289f * (3.6e+02f * *(float *)(sub + 0x14)));
    *(float *)(self + 0xa4) = *(float *)(self + 0xa4) + (lbl_806D6BD8 * s + lbl_806D6BD8);
    if (ItemHitRegistry_RemoveEntry(self, *(int *)(sub + 4), 0)) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
    }
}
