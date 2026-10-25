typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void fn_8011C20C(unsigned char *self, unsigned char *sub);
extern void fn_8011C008(unsigned char *self, unsigned char *sub);
extern void Effect_ExplosionPiece_Update(void *e);
extern unsigned char *DrawEffect_SpawnDirect(void (*cb)(void *));
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern int Item_AdvanceProjectileSimple(unsigned char *self, void *y, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);


static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item_Explode(unsigned char *self)
{
    int i;
    unsigned char *e;
    Vec3 snd;

    for (i = 0; i < 3; i++) {
        e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (e != 0) {
            Vec3_Copy(e + 0x8C, self + 0xA0);
            GetSpawnPosition(e + 0xA4, 0.0f, 0.0f,
                             0.6f * Rand_RangeFloat(0.7f, 1.3f));
            Vec2_RotateX(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-60.0f, 0.0f));
            Vec2_RotateY(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
            e[0x190] = 1;
            e[0x191] = 3;
            e[0x192] = 0;
            GetSpawnPosition(e + 0x120, 0.5f, 1.0f, 1.0f);
            e[0x193] = 1;
        }
    }
    snd = *(Vec3 *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0x87, &snd, 0);
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}

static inline void Item_TickGroundFade(unsigned char *self, unsigned char *sub)
{
    Vec3 g;

    switch ((signed char)self[0xC9]) {
    case 0:
        g = *(Vec3 *)(self + 0xA0);
        ItemObject_GetGroundTypeAt(&g, (float *)(sub + 0x14), 0);
        *(float *)(sub + 0x14) = *(float *)(self + 0xA4) - *(float *)(sub + 0x14);
        self[0xC9]++;
    case 1:
        Item_DecayVelocityScalar(self, 2.0f);
        Item_AdvanceProjectileSimple(self, sub + 0x14, 7.0f, 1.0f);
        *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
        if (*(float *)(self + 0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
        }
        break;
    }
}

void fn_8011C5DC(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Vec3 pos;
    Vec3 rot;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x89);
        self[0x8C] = 3;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            switch ((signed char)self[0xCA]) {
            case 0:
                self[0x28] = 1;
                *(float *)(self + 0x2C) = 0.0f;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
                self[0xCA]++;
            case 1:
                GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 2.0f, 2.9670591f, 1.2f);
                if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98))) {
                    self[0x28] = 0;
                } else {
                    self[0x28] = 1;
                }
                switch (*(signed char *)(sub + 0xA0)) {
                case 1:
                    self[0x28] = 1;
                    SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                    *(float *)(self + 0x2C) = 0.0f;
                    sub[0xA0] = 0;
                    Item_InitLaunchFromKart(self, sub + 0x34, 5.0f, 0.0f);
                    self[0xC9]++;
                    self[0xCA] = 0;
                    break;
                case 2:
                    sub[0xA0] = 0;
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                    break;
                default:
                    Mtx44_GetTranslation_RowMajor(sub + 0x34, KartDriver_GetJointByIdx(*(void **)(sub + 0x98), 0xC));
                    break;
                }
                break;
            }
            break;
        case 1:
            fn_8011C20C(self, sub);
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            fn_8011C008(self, sub);
            break;
        case 4:
            Item_Explode(self);
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
            Item_DecayVelocityScalar(self, 2.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, *(unsigned int *)(sub + 0x4), 0.26179934f, 0.26179934f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            Item_Explode(self);
            break;
        case 5:
            Item_TickGroundFade(self, sub);
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
