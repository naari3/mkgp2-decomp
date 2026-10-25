typedef struct Vec { float x, y, z; } Vec;

extern void SpriteSlot_InitLoop(void *slot, int id);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, unsigned int timer, int flag);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B14B8(void *kart, void *target);
extern void ItemHit_Dispatch(void *self, int kind, void *pos, void *kart);
extern void SpriteSlot_Container_Free(void *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void DrawEffect_Cb_RalySmokeSpawner_4Wheel(unsigned char *e);
extern void Vec3_Copy(void *dst, void *src);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *offset, unsigned int timer, float a, float b);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define U32(o) (*(unsigned int *)(self + (o)))
#define P(o) (*(void **)(self + (o)))
#define KIND (*(int *)(self + 0x8))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item80107040_Smoke(unsigned char *self)
{
    unsigned char *e;

    switch (S8(0xC9)) {
    case 0:
        e = DrawEffect_SpawnDirect(DrawEffect_Cb_RalySmokeSpawner_4Wheel);
        if (e != 0) {
            *(int *)(e + 0x10) = 0;
            Vec3_Copy(e + 0x8C, self + 0xA0);
            *(float *)(e + 0xB0) = F(0xC4);
            *(void **)(e + 0x11C) = P(0x188);
        }
        SoundMgr_PlaySE_Positional(0x87, *(Vec *)(self + 0xA0), 0);
        self[0xC9]++;
    case 1:
        F(0xC4) -= 0.4f;
        if (F(0xC4) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
        }
        break;
    }
}

void fn_80107040(unsigned char *self)
{
    int hit;

    switch (S8(0xC8)) {
    case 0:
        KIND = 0x62;
        SpriteSlot_InitLoop(self + 0x14, 0x61);
        self[0x17C] = 1;
        self[0x8C] = 1;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
        ItemHitRegistry_AddEntry(self);
    case 1:
        switch (S8(0xC9)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8D] = 1;
            F(0xC4) = 0.0f;
            U32(0xF0) = 900;
            self[0x3C] = 1;
            SoundMgr_PlaySE_Positional(0xC1, *(Vec *)(self + 0xA0), 0);
            self[0xC9]++;
        case 1:
            break;
        }
        Item_DecayVelocityScalar(self, 2.0f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(P(0x184), ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(KIND), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(P(0x184), ItemTracker_GetTargetKart(self));
            }
        case 3:
            if (hit == 3) {
                fn_801B158C(P(0x184), ItemTracker_GetTargetKart(self));
            }
            if (hit == 1) {
                ItemHit_Dispatch(self, 0, 0, 0);
            }
            P(0x188) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 0;
            break;
        case 4:
            fn_801B14B8(P(0x184), ItemTracker_GetTargetKart(self));
            P(0x188) = ItemTracker_GetTargetKart(self);
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
        if (*(char *)(self + 0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (*(char *)(self + 0x8E) == 1) {
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 4;
            } else {
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 6;
            }
        } else if (ItemHitRegistry_RemoveEntry(self, U32(0xF0), 0)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            SoundMgr_PlaySE_Positional(0x87, *(Vec *)(self + 0xA0), 0);
            SpriteSlot_Container_Free(self);
        }
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            Item80107040_Smoke(self);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                F(0x100) = 0.0f;
                F(0x104) = F(0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, (float *)(self + 0x100), F(0x104), 0.0f, 0.0f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            Item80107040_Smoke(self);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(self + 0x120, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                U32(0xF0) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 2.0f);
            if (Item_OrbitAnchorKart(self, self + 0x120, U32(0xF0), 0.0f, 0.0f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 5:
            Item80107040_Smoke(self);
            break;
        }
        break;
    case 3:
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    Timer_Tick((unsigned int *)(self + 0xF0));
    Timer_Tick((unsigned int *)(self + 0xF4));
    Timer_Tick((unsigned int *)(self + 0xF8));
    Timer_Tick((unsigned int *)(self + 0xFC));
}
