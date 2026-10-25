typedef struct Vec3 { float x, y, z; } Vec3;

extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void *fn);
extern void DrawEffect_Cb_KartItemTrail_SpawnerSwarm(void);
extern void Vec3_Copy(void *dst, void *src);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, int id, int flag);
extern void Vec3_Scale(void *dst, void *src, float k);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern double sin(double);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern void SpriteSlot_Container_Free(void *self);


static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

#define EFFECT (*(unsigned char **)(self + 0x138))

void fn_80107C74(unsigned char *self)
{
    Vec3 t;
    Vec3 d;
    Vec3 se;
    Vec3 g;
    float gy;
    int hit;

    switch ((signed char)self[0xC8]) {
    case 0:
        self[0x1C] = 0x9B;
        self[0x17C] = 1;
        self[0x28] = 1;
        *(float *)(self + 0x2C) = 1.0f;
        self[0x3C] = 1;
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x8C] = 1;
        self[0x8D] = 1;
        *(float *)(self + 0xC4) = 40.0f;
        EFFECT = DrawEffect_SpawnDirect(DrawEffect_Cb_KartItemTrail_SpawnerSwarm);
        if (EFFECT) {
            *(int *)(EFFECT + 0x10) = *(int *)(self + 0x8);
            Vec3_Copy(EFFECT + 0x8C, self + 0xA0);
        }
        *(unsigned int *)(self + 0xF0) = 900;
        ItemHitRegistry_AddEntry(self);
        Vec3_Scale(self + 0xB8, self + 0xB8, 0.2f);
        if (*(int *)(self + 0x8) == 0x67 && *(void **)(self + 0x184)) {
            *(float *)(self + 0x100) = 0.0f;
            Mtx44_GetTranslation_RowMajor(self + 0x120, KartDriver_GetKartRootMtx(*(void **)(self + 0x184)));
        }
        se = *(Vec3 *)(self + 0xA0);
        SoundMgr_PlaySE_Positional(0xBC, &se, 0);
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        if (*(int *)(self + 0x8) == 0x67 && *(void **)(self + 0x184)) {
            *(float *)(self + 0x100) += 0.02f;
            if (1.0f < *(float *)(self + 0x100)) {
                *(float *)(self + 0x100) = 1.0f;
            }
            if (*(float *)(self + 0x100) < 1.0f) {
                Mtx44_GetTranslation_RowMajor(&t, KartDriver_GetKartRootMtx(*(void **)(self + 0x184)));
                Vec3_Subtract_DestFirst(&d, &t, self + 0x120);
                Vec3_Scale(&d, &d, 1.0f - (float)sin(1.570796f * *(float *)(self + 0x100)));
                Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, &d);
                Vec3_Copy(self + 0x120, &t);
            }
        }
        Vec3_Scale(self + 0xB8, self + 0xB8, 0.8f);
        g = *(Vec3 *)(self + 0xA0);
        if (ItemObject_GetGroundTypeAt(&g, &gy, 0)) {
            if (*(float *)(self + 0xA4) - gy < 10.0f) {
                *(float *)(self + 0xBC) += 0.05f;
            } else {
                *(float *)(self + 0xBC) -= 0.05f;
            }
        }
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(*(void **)(self + 0x184), ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(*(int *)(self + 0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(*(void **)(self + 0x184), ItemTracker_GetTargetKart(self));
            }
        case 3:
            if (hit == 3) {
                fn_801B158C(*(void **)(self + 0x184), ItemTracker_GetTargetKart(self));
            }
        case 4:
            if (hit == 1) {
                ItemHit_Dispatch(self, 0, 0, 0);
            }
            *(void **)(self + 0x188) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
            Vec3_Scale(self + 0xB8, self + 0xB8, 0.2f);
            if (hit != 4) {
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 0;
            } else {
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 3;
            }
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (*(char *)(self + 0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (*(char *)(self + 0x8E) == 1) {
                Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
                Vec3_Scale(self + 0xB8, self + 0xB8, 0.2f);
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
        if (ItemHitRegistry_RemoveEntry(self, *(int *)(self + 0xF0), 0)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            EFFECT[0xC9] = 1;
            EFFECT = 0;
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
    case 2:
        switch ((signed char)self[0xC9]) {
        case 0:
            switch ((signed char)self[0xCB]) {
            case 0:
            case 4:
            case 5:
                Vec3_Copy(EFFECT + 0xA4, self + 0xB8);
                *(void **)(EFFECT + 0x11C) = *(void **)(self + 0x188);
                EFFECT[0xC9] = 1;
                EFFECT = 0;
                break;
            case 3:
                *(void **)(EFFECT + 0x11C) = *(void **)(self + 0x188);
                EFFECT[0xC9] = 2;
                EFFECT = 0;
                *(float *)(self + 0x2C) = 0.0f;
                break;
            case 6:
                *(void **)(EFFECT + 0xCC) = *(void **)(self + 0x9C);
                EFFECT[0xC9] = 3;
                EFFECT = 0;
                *(float *)(self + 0x2C) = 0.0f;
                break;
            }
            self[0xC9]++;
        case 1:
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
            if (*(float *)(self + 0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                return;
            }
            break;
        }
        break;
    case 3:
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    if (EFFECT) {
        Vec3_Copy(EFFECT + 0x8C, self + 0xA0);
    }
    ItemObject_TickTimer((unsigned int *)(self + 0xF0));
    ItemObject_TickTimer((unsigned int *)(self + 0xF4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF8));
    ItemObject_TickTimer((unsigned int *)(self + 0xFC));
}
