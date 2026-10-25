typedef struct Vec3 { float x, y, z; } Vec3;

extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void Effect_DustBurst4_Update(void);
extern unsigned char *DrawEffect_SpawnDirect(void (*fn)(void));
extern void Vec3_Copy(void *dst, void *src);
extern void SoundMgr_PlaySE_Positional(int id, Vec3 *pos, int a);
extern int ItemCollision_Check(unsigned char *self);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, int b);
extern void SpriteSlot_Container_Free(void *self);
extern float lbl_806D66E0;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80107B00(unsigned char *self)
{
    unsigned char *e;
    Vec3 pos;
    int hit;

    switch ((signed char)self[0xC8]) {
    case 0:
        *(float *)(self + 0xC4) = lbl_806D66E0;
        *(unsigned int *)(self + 0xF0) = 10;
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        e = DrawEffect_SpawnDirect(Effect_DustBurst4_Update);
        if (e) {
            Vec3_Copy(e + 0x8C, self + 0xA0);
        }
        pos = *(Vec3 *)(self + 0xA0);
        SoundMgr_PlaySE_Positional(0xC4, &pos, 0);
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            if (hit == 1) {
                ItemHit_Dispatch(self, 0, self + 0xA0, 0);
            }
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (*(unsigned int *)(self + 0xF0) == 0) {
            ItemTracker_ReleaseLock(self);
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
