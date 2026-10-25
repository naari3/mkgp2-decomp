typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Mtx44 { float m[4][4]; } Mtx44;
typedef struct Mtx34 { float m[3][4]; } Mtx34;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_80113500(unsigned char *self, unsigned char *sub);
extern void fn_80113114(unsigned char *self, unsigned char *sub);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec3 *b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *kart);
extern void Effect_ExplosionPiece_Update(void *e);
extern unsigned char *DrawEffect_SpawnDirect(void (*cb)(void *));
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern void DrawEffect_Free(void *e);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern void Matrix4_Identity(Mtx44 *m);
extern void Matrix4_PreMultiplyTranslation(Mtx44 *dst, Mtx44 *src, float x, float y, float z);
extern void Mtx44_Scale_PerAxis(Mtx44 *dst, Mtx44 *src, float x, float y, float z);
extern void Matrix4_PreMultiplyRotY(Mtx44 *dst, Mtx44 *src, float a);
extern void Mtx44_Translate(Mtx44 *dst, Mtx44 *src, Vec3 *v);
extern void DbgScene_CopyMatrix3x4Transpose(Mtx34 *dst, Mtx44 *src);
extern void VfxEffect_UpdateChildSpinMatrix_Helper(void *e, Mtx34 *m);


static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item_Explode(unsigned char *self, unsigned char *sub)
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
            *(void **)(e + 0x11C) = *(void **)(sub + 0x9C);
            GetSpawnPosition(e + 0x120, 0.7f, 0.7f, 0.7f);
            e[0x193] = 1;
        }
    }
    snd = *(Vec3 *)(self + 0xA0);
    SoundMgr_PlaySE_Positional(0x87, &snd, 0);
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}

static inline void Item_TickFall(unsigned char *self, unsigned char *sub, Vec3 *g1, Vec3 *g2)
{
    float gy;

    switch ((signed char)self[0xC9]) {
    case 0:
        *g1 = *(Vec3 *)(self + 0xA0);
        ItemObject_GetGroundTypeAt(g1, (float *)(sub + 0x14), 0);
        *(float *)(self + 0xBC) = 0.0f;
        self[0xC9]++;
    case 1:
        break;
    }
    *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.1f;
    if (*(float *)(self + 0x2C) < 0.0f) {
        self[0x28] = 0;
        self[0xC8] = 3;
        self[0xC9] = 0;
        return;
    }
    *g2 = *(Vec3 *)(self + 0xA0);
    if (ItemObject_GetGroundTypeAt(g2, &gy, 0)) {
        *(float *)(self + 0xA4) = *(float *)(self + 0xA4) + (gy - *(float *)(sub + 0x14));
        *(float *)(sub + 0x14) = gy;
    }
    Item_DecayVelocityScalar(self, 2.0f);
}

void fn_80113728(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    Mtx44 m;
    Mtx34 m34;
    Vec3 pos;
    Vec3 rot;
    Vec3 tp;
    Vec3 c;
    Vec3 t;
    Vec3 f5b;
    Vec3 f5a;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x80);
        self[0x8C] = 3;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xC9]) {
        case 0:
            fn_80113500(self, sub);
            break;
        case 1:
            fn_80113114(self, sub);
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            switch ((signed char)self[0xC9]) {
            case 0:
                Vec3_Subtract_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
                Item_PrepareHitRebound(self, sub + 0x40, sub + 0x34, sub + 0x4);
                self[0xC9]++;
            case 1:
                break;
            }
            c = *(Vec3 *)(sub + 0x34);
            Vec3_AddNormalizedXZ(self, sub + 0x40, &c);
            Mtx44_GetTranslation_RowMajor(&t, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
            Vec3_Add_DestFirst(self + 0xA0, &t, sub + 0x40);
            if (*(unsigned int *)(sub + 0x4) == 0) {
                if (sub[0] != 0) {
                    ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(sub + 0x9C));
                }
                Item_Explode(self, sub);
            }
            break;
        case 4:
            Item_Explode(self, sub);
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
            Item_Explode(self, sub);
            break;
        case 5:
            Item_TickFall(self, sub, &f5a, &f5b);
            break;
        }
        break;
    case 3:
        if (*(void **)(sub + 0x4C) != 0) {
            DrawEffect_Free(*(void **)(sub + 0x4C));
        }
        *(void **)(sub + 0x4C) = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    if (*(void **)(sub + 0x4C) != 0) {
        Matrix4_Identity(&m);
        Matrix4_PreMultiplyTranslation(&m, &m, 0.0f, 0.0f, 0.5f);
        Mtx44_Scale_PerAxis(&m, &m, *(float *)(self + 0xC4), *(float *)(self + 0xC4), *(float *)(self + 0xC4));
        Matrix4_PreMultiplyRotY(&m, &m, *(float *)(self + 0xB0));
        tp = *(Vec3 *)(self + 0xA0);
        Mtx44_Translate(&m, &m, &tp);
        DbgScene_CopyMatrix3x4Transpose(&m34, &m);
        VfxEffect_UpdateChildSpinMatrix_Helper(*(void **)(sub + 0x4C), &m34);
    }
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
