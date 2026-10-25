typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Mtx44[4][4];

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enable);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, int flag, float a, float b);
extern void fn_80118858(unsigned char *self, unsigned char *sub);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(Mtx44 dst, void *src);
extern void Mtx44_Inverse_GaussJordan(Mtx44 dst, Mtx44 src);
extern void Mtx44_TransformVec3(void *dst, Mtx44 m, Vec3 *v);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern unsigned char *DrawEffect_SpawnDirect(void *fn);
extern void SpawnRisingTextAndBurst(void);
extern void DebrisArray_Update(void);
extern void Vec3_Copy(void *dst, void *src);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);

extern const char lbl_803324D8[];

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_80118C64(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Mtx44 inv;
    Mtx44 m;
    Vec3 pos;
    Vec3 rot;
    Vec3 se0;
    Vec3 p;
    Vec3 se1;
    Vec3 se4;
    unsigned char *e;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x90);
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
        SpriteSlot_SetScale(self + 0x14, -1.0f);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_803324D8, 0x10, 1);
        self[0x8C] = 2;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            switch ((signed char)self[0xCA]) {
            case 0:
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
                self[0x28] = 1;
                *(float *)(self + 0x2C) = 0.0f;
                self[0xCA]++;
            case 1:
                GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 8.0f, 0.0f, 0.5f);
                if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98))) {
                    self[0x28] = 0;
                } else {
                    self[0x28] = 1;
                }
                switch ((signed char)sub[0xA0]) {
                case 1:
                    self[0x28] = 1;
                    sub[0xA0] = 0;
                    SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                    Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
                    self[0xC9]++;
                    self[0xCA] = 0;
                    break;
                case 2:
                    sub[0xA0] = 0;
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                    break;
                }
                break;
            }
            break;
        case 1:
            fn_80118858(self, sub);
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
            switch ((signed char)self[0xC9]) {
            case 0:
                Mtx44_Inverse_GaussJordan(inv, m);
                p = *(Vec3 *)(self + 0xA0);
                Mtx44_TransformVec3(sub + 0x34, inv, &p);
                *(float *)(sub + 0x14) = 0.0f;
                self[0xC9]++;
            case 1:
                ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(sub + 0x9C));
                if (*(int *)(*(unsigned char **)(sub + 0x9C) + 0x238) != 0) {
                    e = DrawEffect_SpawnDirect(SpawnRisingTextAndBurst);
                    Vec3_Copy(e + 0x8C, self + 0xA0);
                } else {
                    e = DrawEffect_SpawnDirect(DebrisArray_Update);
                    Vec3_Copy(e + 0x8C, self + 0xA0);
                    Vec3_Copy(e + 0xA4, self + 0xB8);
                }
                se0 = *(Vec3 *)(self + 0xA0);
                SoundMgr_PlaySE_Positional(0xCE, &se0, 0);
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            }
            break;
        case 1:
            e = DrawEffect_SpawnDirect(DebrisArray_Update);
            Vec3_Copy(e + 0x8C, self + 0xA0);
            Vec3_Copy(e + 0xA4, self + 0xB8);
            se1 = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xBB, &se1, 0);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 4:
            e = DrawEffect_SpawnDirect(DebrisArray_Update);
            Vec3_Copy(e + 0x8C, self + 0xA0);
            Vec3_Copy(e + 0xA4, self + 0xB8);
            se4 = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xBB, &se4, 0);
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 6:
            switch ((signed char)self[0xC9]) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(sub + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                *(unsigned int *)(sub + 0x4) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 1.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.26179934f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 5:
            Item_DecayVelocityScalar(self, 1.0f);
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
            if (*(float *)(self + 0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
