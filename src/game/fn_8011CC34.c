typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct F3 { float v[3]; } F3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec3 *pos, int ch);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern int ItemCollision_Check(void *self);
extern void ItemHit_Dispatch(void *self, int a, void *pos, void *b);
extern void SpriteSlot_Container_Free(void *self);
extern float BuildOrientationFromYaw(float yaw);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_TransformVec3(void *out, float m[4][4], Vec3 v);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern F3 lbl_80332518;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void ApplyTransform(unsigned char *self)
{
    Vec3 rot;
    Vec3 pos;
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
}

void fn_8011CC34(unsigned char *self)
{
    Vec3 v;
    F3 tbl;
    Vec3 sePos;
    Vec3 sePos2;
    float m[4][4];

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x84);
        self[0x3C] = 1;
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        *(float *)(self + 0x100) = 0.0f;
        tbl = lbl_80332518;
        *(float *)(self + 0x104) = tbl.v[*(int *)(self + 0x10)];
        *(unsigned int *)(self + 0xF0) = 600;
        *(unsigned int *)(self + 0xF4) = 0;
        *(unsigned int *)(self + 0xF8) = 0;
        *(unsigned int *)(self + 0xFC) = 60;
        *(int *)(self + 0x110) = -1;
        self[0xC8]++;
    case 1:
        break;
    }
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(self + 0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    if (*(int *)(self + 0x10) == 0) {
        if (*(int *)(self + 0x110) < 0) {
            *(int *)(self + 0x110) = SoundMgr_CountActiveSEInstances(0xCC);
            if (*(int *)(self + 0x110) >= 0) {
                sePos = *(Vec3 *)(self + 0xA0);
                SoundMgr_PlaySE_Positional(0xCC, &sePos, *(int *)(self + 0x110));
            }
        } else {
            sePos2 = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_WithChannel(0xCC, &sePos2, *(int *)(self + 0x110));
        }
    }
    if (ItemCollision_Check(self) == 1 && *(void **)(self + 0x184) != ItemTracker_GetTargetKart(self)) {
        ItemHit_Dispatch(self, 0, 0, 0);
        ItemTracker_SetTrackPhase(self, 0);
        *(unsigned int *)(self + 0xF4) = 5;
    }
    if (*(unsigned int *)(self + 0xF4) == 0) {
        ItemTracker_SetTrackPhase(self, 1);
    }
    if (*(unsigned int *)(self + 0xFC) == 0) {
        if ((*(unsigned long long *)(*(unsigned char **)(*(unsigned char **)(self + 0x184) + 0x304) + 0x10) & 0x1000000000000ULL) == 0) {
            *(unsigned int *)(self + 0xF0) = 0;
        }
    }
    if (*(unsigned int *)(self + 0xF0) == 0) {
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
        if (*(float *)(self + 0x2C) < 0.0f) {
            if (*(int *)(self + 0x110) >= 0) {
                SoundMgr_StopSE_OrSpecial(0xCC, *(int *)(self + 0x110));
                *(int *)(self + 0x110) = -1;
            }
            ItemTracker_ReleaseLock(self);
            SpriteSlot_Container_Free(self);
            return;
        }
    }
    *(float *)(self + 0x100) += 0.05f;
    if (1.0f < *(float *)(self + 0x100)) {
        *(float *)(self + 0x100) = 1.0f;
    }
    *(float *)(self + 0x104) = BuildOrientationFromYaw(-0.087266445f + *(float *)(self + 0x104));
    GetSpawnPosition(self + 0xA0, 0.0f, 5.0f, 1e+01f * *(float *)(self + 0x100));
    Vec2_RotateY(self + 0xA0, self + 0xA0, *(float *)(self + 0x104));
    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(self + 0x184)));
    v = *(Vec3 *)(self + 0xA0);
    Mtx44_TransformVec3(self + 0xA0, m, v);
    *(float *)(self + 0xB0) = BuildOrientationFromYaw(-0.17453289f + *(float *)(self + 0xB0));
    *(float *)(self + 0xC4) = 0.8f * *(float *)(self + 0x100);
    ApplyTransform(self);
    ItemObject_TickTimer((unsigned int *)(self + 0xF0));
    ItemObject_TickTimer((unsigned int *)(self + 0xF4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF8));
    ItemObject_TickTimer((unsigned int *)(self + 0xFC));
}
