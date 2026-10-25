typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern int ItemCollision_Check(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern void ItemObject_DispatchVtable18_GetState(void *kart);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx_Copy(void *dst, void *src);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *src);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern const float lbl_806D6998;
extern const float lbl_806D699C;
extern const float lbl_806D69A0;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80112738(unsigned char *self)
{
    Vec3 pos;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x75);
        self[0x28] = 0;
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        self[0xEC] = 0;
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 0);
        self[0xC8] = 1;
    case 1:
        if (self[0xEC]) {
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, lbl_806D6998);
            SpriteSlot_SetScale(self + 0x14, lbl_806D699C);
            self[0x28] = 1;
            self[0xEC] = 0;
        }
        if (*(signed char *)(self + 0x28)) {
            if (lbl_806D69A0 == *(float *)(self + 0x20)) {
                pos = *(Vec3 *)(self + 0xA0);
                SoundMgr_PlaySE_Positional(0xB8, &pos, 0);
            }
            if (*(signed char *)(self + 0x1E) == 2) {
                self[0x28] = 0;
            }
        }
        if (ItemCollision_Check(self) == 1 && *(void **)(self + 0x184) != ItemTracker_GetTargetKart(self)) {
            ItemHit_Dispatch(self, 0, 0, 0);
            ItemObject_DispatchVtable18_GetState(ItemTracker_GetTargetKart(self));
            *(int *)(*(unsigned char **)(self + 0x184) + 0x290) = 1;
        }
        if (*(signed char *)(self + 0x28)) {
            ItemTracker_SetTrackPhase(self, 1);
        } else {
            ItemTracker_SetTrackPhase(self, 0);
        }
        if (*(signed char *)(self + 0x28)) {
            Mtx_Copy(self + 0x48, KartDriver_GetJointByIdx(*(void **)(self + 0x184), 0xF));
            Mtx44_GetTranslation_RowMajor(self + 0xA0, self + 0x48);
            *(float *)(self + 0xC4) = lbl_806D699C;
        }
        if (*(signed char *)(self + 0x18C)) {
            ItemTracker_ReleaseLock(self);
            ItemObject_DecrementCategoryBudget(self);
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
    }
    ItemObject_TickTimer((unsigned int *)(self + 0xF0));
    ItemObject_TickTimer((unsigned int *)(self + 0xF4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF8));
    ItemObject_TickTimer((unsigned int *)(self + 0xFC));
}
