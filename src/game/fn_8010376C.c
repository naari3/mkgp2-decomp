typedef struct Vec { float x, y, z; } Vec;

typedef struct BurstIdx {
    unsigned char v[3][6];
} BurstIdx;

typedef struct BurstPos {
    Vec v[6];
} BurstPos;

typedef struct ScaleKey {
    float t[12];
    float v[12];
} ScaleKey;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void DrawEffect_KartWheel_TripleChildSpawn(unsigned char *self);
extern void Effect_ExplosionPiece_Update(unsigned char *e);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void fn_80103144(unsigned char *self, unsigned char *w);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec b);
extern void ItemHit_Dispatch(void *self, int kind, void *pos, void *kart);
extern void Vec3_Copy(void *dst, void *src);
extern float Rand_RangeFloat(float lo, float hi);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void Vec3_Scale(void *dst, void *src, float s);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *offset, unsigned int timer, float a, float b);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float dst[4][4], float a[4][4], float b[4][4]);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern void DrawEffect_KartWheel_TripleChildUpdate(void *child, Vec pos, float scale, float alpha);
extern void DrawEffect_ApplyScaleAndIntensity(void *e, Vec pos, float scale, float alpha);

extern unsigned char lbl_80330D10[];
extern ScaleKey lbl_804218E0[3];

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define KIND (*(int *)(self + 0x8))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))
#define WB(o) (*(unsigned char **)(w + (o)))

static inline void Item8010376C_Burst(unsigned char *self, unsigned char *w, unsigned char *base)
{
    BurstIdx idx;
    BurstPos pos;
    unsigned char *e;
    int i;
    unsigned char k;

    self[0x28] = 0;
    idx = *(BurstIdx *)(base + 0x408);
    pos = *(BurstPos *)(base + 0x41C);
    for (i = 0; i < 6; i++) {
        e = DrawEffect_SpawnDirect(Effect_ExplosionPiece_Update);
        if (e != 0) {
            Vec3_Copy(e + 0x8C, self + 0xA0);
            GetSpawnPosition(e + 0xA4, 0.0f, 0.0f, 0.6f * Rand_RangeFloat(0.7f, 1.3f));
            Vec2_RotateX(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
            Vec2_RotateY(e + 0xA4, e + 0xA4, 0.017453289f * Rand_RangeFloat(-180.0f, 180.0f));
            e[0x190] = 1;
            e[0x191] = 2;
            *(void **)(e + 0x11C) = WP(0x9C);
            switch (KIND) {
            case 0x5B:
                k = idx.v[0][i];
                break;
            case 0x5C:
                k = idx.v[1][i];
                break;
            case 0x5D:
                k = idx.v[2][i];
                break;
            }
            if (k == 0) {
                e[0x192] = 2;
            } else {
                e[0x192] = 0;
            }
            Vec3_Copy(e + 0x120, &pos.v[k]);
            e[0x193] = 1;
        }
    }
    SoundMgr_PlaySE_Positional(0x87, *(Vec *)(self + 0xA0), 0);
    self[0xC8] = 3;
    self[0xC9] = 0;
}

static inline void Item8010376C_Rebound(unsigned char *self, unsigned char *w, unsigned char *base)
{
    Vec p;

    switch (S8(0xC9)) {
    case 0:
        Item_PrepareHitRebound(self, w + 0x40, w + 0x34, w + 0x4);
        self[0xC9]++;
    case 1:
        Vec3_AddNormalizedXZ(self, w + 0x40, *(Vec *)(w + 0x34));
        if (WU(0x4) == 0) {
            if (w[1]) {
                ItemHit_Dispatch(self, 0, self + 0xA0, WP(0x9C));
            }
            if (w[1]) {
                self[0xC9]++;
            } else {
                Item8010376C_Burst(self, w, base);
                return;
            }
        }
        break;
    case 2:
        Vec3_Scale(w + 0x40, w + 0x40, 0.9f);
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    }
    Mtx44_GetTranslation_RowMajor(&p, KartDriver_GetKartRootMtx(WP(0x9C)));
    Vec3_Add_DestFirst(self + 0xA0, &p, w + 0x40);
    Item_DecayVelocityScalar(self, 2.0f);
}

static inline void Item8010376C_Explode(unsigned char *self, unsigned char *w, unsigned char *base)
{
    Item8010376C_Burst(self, w, base);
}

static inline void Item8010376C_GroundFade(unsigned char *self, unsigned char *w)
{
    float gy;

    switch (S8(0xC9)) {
    case 0:
        ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), (float *)(w + 0x18), 0);
        if (*(char *)(self + 0xCB) != 5) {
            WU(0x4) = 10;
        } else {
            WU(0x4) = 0;
        }
        if (*(char *)(self + 0xCB) == 5) {
            F(0xBC) = 0.0f;
        }
        self[0xC9]++;
    case 1:
        break;
    }
    if (WU(0x4) == 0) {
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            F(0x2C) = 0.0f;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    if (*(char *)(self + 0xCB) != 5) {
        F(0xBC) += -0.1f;
    }
    if (ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &gy, 0)) {
        F(0xA4) = F(0xA4) + (gy - WF(0x18));
        WF(0x18) = gy;
    }
    Item_DecayVelocityScalar(self, 2.0f);
}

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_8010376C(unsigned char *self)
{
    unsigned char *base = lbl_80330D10;
    unsigned char *w = self + 0xEC;
    float m[4][4];
    float mA[4][4];
    float mB[4][4];
    Vec scale;
    Vec jp;
    ScaleKey *key;
    float *out;
    int j;
    int k;

    switch (S8(0xC8)) {
    case 0:
        switch (KIND) {
        case 0x5B:
            SpriteSlot_InitNonLoop(self + 0x14, 0x5A);
            break;
        case 0x5C:
            SpriteSlot_InitNonLoop(self + 0x14, 0x5B);
            break;
        case 0x5D:
            SpriteSlot_InitNonLoop(self + 0x14, 0x5C);
            break;
        }
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        w[0] = 1;
        self[0x14] = 4;
        self[0x8C] = 2;
        self[0x8D] = 0;
        WF(0x14) = 0.0f;
        WP(0x4C) = DrawEffect_SpawnDirect(DrawEffect_KartWheel_TripleChildSpawn);
        if (WP(0x4C) != 0) {
            *(int *)(WB(0x4C) + 0x10) = KIND;
        }
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_80103144(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            Item8010376C_Rebound(self, w, base);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                WF(0x18) = 0.0f;
                WF(0x1C) = F(0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, (float *)(w + 0x18), WF(0x1C), 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            Item8010376C_Explode(self, w, base);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(w + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                WU(0x4) = 30;
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 2.0f);
            if (Item_OrbitAnchorKart(self, w + 0x34, WU(0x4), 0.2617993f, 0.2617993f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            Item8010376C_Explode(self, w, base);
            break;
        case 9:
            Item8010376C_GroundFade(self, w);
            break;
        case 5:
            Item8010376C_GroundFade(self, w);
            break;
        }
        break;
    case 3:
        if (WP(0x4C) != 0) {
            WB(0x4C)[0xC9] = 1;
        }
        WP(0x4C) = 0;
        if (WP(0x50) != 0) {
            WB(0x50)[0xC9] = 1;
        }
        WP(0x50) = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    if (w[0]) {
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, F(0xC4));
        Matrix4_PreMultiplyRotZ(m, m, F(0xB4));
        Matrix4_PreMultiplyRotX(m, m, F(0xAC));
        Matrix4_PreMultiplyRotY(m, m, F(0xB0));
        Mtx44_Translate(m, m, *(Vec *)(self + 0xA0));
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
    }
    if (KIND == 0x5C) {
        if (*(char *)(self + 0x1D) != 1) {
            WF(0x14) += 2.0f;
            if (140.0f <= WF(0x14)) {
                WF(0x14) -= 140.0f;
            }
        } else {
            WF(0x14) = 0.0f;
        }
        scale = *(Vec *)(base + 0x3FC);
        for (j = 0; j < 3; j++) {
            key = &lbl_804218E0[j];
            out = &(&scale.x)[j];
            for (k = 0; k < 11; k++) {
                if (key->t[k] <= WF(0x14) && WF(0x14) <= key->t[k + 1]) {
                    *out = (WF(0x14) - key->t[k]) * ((key->v[k + 1] - key->v[k]) / (key->t[k + 1] - key->t[k])) + key->v[k];
                    *out *= 0.7f;
                }
            }
        }
        Mtx_TransposeToMtx44(mA, self + 0x48);
        Matrix4_Identity(mB);
        Mtx44_Scale_PerAxis(mB, mB, scale.x, scale.y, scale.z);
        Matrix4_Multiply(mA, mB, mA);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, mA);
    }
    SpriteSlot_TickAnim(self + 0x14);
    switch (KIND) {
    case 0x5B:
        JointByName_GetWorldPosition(&jp, self + 0x14, (char *)(base + 0x464));
        break;
    case 0x5C:
        JointByName_GetWorldPosition(&jp, self + 0x14, (char *)(base + 0x484));
        break;
    case 0x5D:
        JointByName_GetWorldPosition(&jp, self + 0x14, (char *)(base + 0x49C));
        break;
    }
    if (WP(0x4C) != 0) {
        if (KIND == 0x5C) {
            *(float *)(WB(0x4C) + 0x150) = WF(0x14) / 140.0f;
        } else {
            *(float *)(WB(0x4C) + 0x150) += 0.007142857f;
            if (1.0f < *(float *)(WB(0x4C) + 0x150)) {
                *(float *)(WB(0x4C) + 0x150) -= 1.0f;
            }
        }
        if (*(signed char *)(self + 0x28)) {
            DrawEffect_KartWheel_TripleChildUpdate(WP(0x4C), jp, F(0xC4), F(0x2C));
        } else {
            DrawEffect_KartWheel_TripleChildUpdate(WP(0x4C), jp, F(0xC4), 0.0f);
        }
    }
    DrawEffect_ApplyScaleAndIntensity(WP(0x50), jp, F(0xC4), F(0x2C));
    Timer_Tick((unsigned int *)(w + 0x4));
    Timer_Tick((unsigned int *)(w + 0x8));
    Timer_Tick((unsigned int *)(w + 0xC));
    Timer_Tick((unsigned int *)(w + 0x10));
}
