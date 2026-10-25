typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Mtx44 { float m[4][4]; } Mtx44;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern unsigned char *DrawEffect_SpawnDirect(void (*cb)(void *));
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern int Rand_RangeIntMax(int max);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void fn_8011B244(unsigned char *self, unsigned char *sub);
extern void fn_8011AD98(unsigned char *self, unsigned char *sub);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern int Item_AdvanceProjectileSimple(unsigned char *self, void *y, float a, float b);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern float Vec3_PitchTo(void *a, void *b);
extern float Vec3_HorizontalYawTo(void *from, void *to);
extern void Matrix4_Identity(Mtx44 *m);
extern void Mtx44_Scale_Uniform(Mtx44 *dst, Mtx44 *src, float s);
extern void Matrix4_PreMultiplyRotZ(Mtx44 *dst, Mtx44 *src, float a);
extern void Matrix4_PreMultiplyRotX(Mtx44 *dst, Mtx44 *src, float a);
extern void Matrix4_PreMultiplyRotY(Mtx44 *dst, Mtx44 *src, float a);
extern void Mtx44_Translate(Mtx44 *dst, Mtx44 *src, Vec3 *v);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, Mtx44 *src);

extern unsigned char lbl_805DF3D0[];
extern int g_gameMode;

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item_TickSpinFall(unsigned char *self, unsigned char *sub)
{
    switch ((signed char)self[0xC9]) {
    case 0:
        *(float *)(self + 0xB4) = 0.785398f;
        *(unsigned int *)(sub + 0x4) = 10;
        self[0xC9]++;
    case 1:
        *(float *)(self + 0xBC) += -0.1f;
        Item_DecayVelocityScalar(self, 2.0f);
        if (*(unsigned int *)(sub + 0x4) == 0) {
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
            if (*(float *)(self + 0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
        }
        break;
    }
}

void fn_8011B748(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Mtx44 m;
    Vec3 tp;
    Vec3 g;
    unsigned char *cam;
    float pitch;
    float yaw;

    switch ((signed char)self[0xC8]) {
    case 0:
        if (g_gameMode == 2) {
            *(int *)(self + 0x10) = 0;
        } else {
            *(int *)(self + 0x10) = Rand_RangeIntMax(2);
        }
        switch (*(int *)(self + 0x10)) {
        case 0:
            SpriteSlot_InitNonLoop(self + 0x14, 0x8A);
            break;
        case 1:
            SpriteSlot_InitNonLoop(self + 0x14, 0x8B);
            break;
        case 2:
            SpriteSlot_InitNonLoop(self + 0x14, 0x8C);
            break;
        }
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
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
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
                self[0x28] = 1;
                *(float *)(self + 0x2C) = 0.0f;
                self[0xCA]++;
            case 1:
                GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 3.0f, 0.0f, 1.2f);
                if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98))) {
                    self[0x28] = 0;
                } else {
                    self[0x28] = 1;
                }
                switch (*(signed char *)(sub + 0xA0)) {
                case 1:
                    self[0x28] = 1;
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
            fn_8011B244(self, sub);
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            fn_8011AD98(self, sub);
            break;
        case 1:
            Item_TickSpinFall(self, sub);
            break;
        case 4:
            Item_TickSpinFall(self, sub);
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
            Item_TickSpinFall(self, sub);
            break;
        case 5:
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
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    cam = lbl_805DF3D0 + 0x80;
    pitch = Vec3_PitchTo(self + 0xA0, cam);
    yaw = Vec3_HorizontalYawTo(self + 0xA0, cam);
    Matrix4_Identity(&m);
    Mtx44_Scale_Uniform(&m, &m, *(float *)(self + 0xC4));
    Matrix4_PreMultiplyRotZ(&m, &m, *(float *)(self + 0xB4));
    Matrix4_PreMultiplyRotX(&m, &m, pitch);
    Matrix4_PreMultiplyRotY(&m, &m, yaw);
    tp = *(Vec3 *)(self + 0xA0);
    Mtx44_Translate(&m, &m, &tp);
    DbgScene_CopyMatrix3x4Transpose(self + 0x48, &m);
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
