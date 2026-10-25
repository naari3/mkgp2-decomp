typedef struct Vec { float x, y, z; } Vec;

extern void SpriteSlot_InitLoop(void *slot, int id);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void fn_80105EB4(unsigned char *self, unsigned char *w);
extern void fn_80105CC4(unsigned char *self, unsigned char *w, int type, float yaw);
extern void Item_PrepareHitRebound(unsigned char *self, void *a, void *b, void *c);
extern void ItemHit_Dispatch(void *self, int kind, void *pos, void *kart);
extern void Vec3_AddNormalizedXZ(unsigned char *self, void *a, Vec b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *offset, unsigned int timer, float a, float b);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *landed, float *gy, float k);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double);
extern void SpriteSlot_SetPositionFromVec(void *slot, Vec pos);
extern void SpriteSlot_SetRotationQuat(void *slot, float x, float y, float z);
extern void SpriteSlot_SetScaleUniform(void *slot, float s);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_Multiply(float dst[4][4], float a[4][4], float b[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void Vec3_Copy(void *dst, void *src);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define KIND (*(int *)(self + 0x8))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))
#define WB(o) (*(unsigned char **)(w + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void Item8010670C_Finish(unsigned char *self, unsigned char *w)
{
    switch (S8(0xCB)) {
    case 1:
        fn_80105CC4(self, w, 3, 0.0f);
        break;
    case 4:
        fn_80105CC4(self, w, 4, 0.0f);
        break;
    case 7:
        fn_80105CC4(self, w, 5, F(0xB0));
        break;
    }
    self[0x28] = 0;
    self[0xC8] = 3;
    self[0xC9] = 0;
}

static inline void Item8010670C_GroundFade(unsigned char *self, unsigned char *w)
{
    int landed;
    float gy;

    switch (S8(0xC9)) {
    case 0:
        ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), (float *)(w + 0x18), 0);
        if (*(char *)(self + 0xCB) != 5) {
            WU(0x4) = 10;
        } else {
            WU(0x4) = 0;
        }
        self[0xC9]++;
    case 1:
        break;
    }
    if (WU(0x4) == 0) {
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
    }
    F(0xA4) -= F(0xBC);
    if (Item_AdvanceFallingDrop(self, &landed, &gy, 0.6f)) {
        F(0xA4) += F(0xBC);
        F(0xA4) += gy - WF(0x18);
        WF(0x18) = gy;
        if (F(0xA4) < 0.6f * F(0xC4) + gy) {
            F(0xA4) = 0.6f * F(0xC4) + gy;
            F(0xBC) = 4.0f;
        }
    } else {
        F(0xA4) += F(0xBC);
    }
    F(0xBC) += -0.5f;
    Item_DecayVelocityScalar(self, 1.2f);
}

static inline void Item8010670C_Rebound(unsigned char *self, unsigned char *w)
{
    Vec tp;

    switch (S8(0xC9)) {
    case 0:
        Item_PrepareHitRebound(self, w + 0x40, w + 0x34, w + 0x4);
        self[0xC9]++;
    case 1:
        break;
    }
    if (WU(0x4) == 0) {
        if (w[1]) {
            ItemHit_Dispatch(self, 0, 0, WP(0x9C));
        }
        fn_80105CC4(self, w, 3, 0.0f);
        self[0x28] = 0;
        self[0xC8] = 3;
        self[0xC9] = 0;
    }
    Vec3_AddNormalizedXZ(self, w + 0x40, *(Vec *)(w + 0x34));
    Mtx44_GetTranslation_RowMajor(&tp, KartDriver_GetKartRootMtx(WP(0x9C)));
    Vec3_Add_DestFirst(self + 0xA0, &tp, w + 0x40);
    Item_DecayVelocityScalar(self, 1.2f);
}

void fn_8010670C(unsigned char *self)
{
    unsigned char *w = self + 0xEC;
    float mA[4][4];
    float mB[4][4];
    float s;

    switch (S8(0xC8)) {
    case 0:
        if (KIND == 0x5F) {
            SpriteSlot_InitLoop(self + 0x14, 0x5E);
        } else {
            SpriteSlot_InitLoop(self + 0x14, 0x5F);
        }
        w[0] = 0;
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 6, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 0.5f);
        self[0x8C] = 2;
        self[0x8D] = 0;
        WF(0x14) = 0.0f;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_80105EB4(self, w);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            Item8010670C_Rebound(self, w);
            break;
        case 1:
            Item8010670C_Finish(self, w);
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
            Item8010670C_Finish(self, w);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                Vec3_Subtract_DestFirst(w + 0x34, self + 0xA0, *(unsigned char **)(self + 0x9C) + 0xA0);
                WU(0x4) = 30;
                fn_80105CC4(self, w, 6, 0.0f);
                self[0xC9]++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 1.2f);
            if (Item_OrbitAnchorKart(self, w + 0x34, WU(0x4), 0.2617993f, 0.2617993f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 7:
            Item8010670C_Finish(self, w);
            break;
        case 9:
            Item8010670C_GroundFade(self, w);
            break;
        case 5:
            Item8010670C_GroundFade(self, w);
            break;
        }
        break;
    case 3:
        if (WP(0x4C) != 0) {
            WB(0x4C)[0xC9] = 1;
        }
        WP(0x4C) = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    WF(0x14) = BuildOrientationFromYaw(0.10471973f + WF(0x14));
    s = 0.15f * (float)sin(WF(0x14)) + 1.0f;
    if (w[0] == 0) {
        SpriteSlot_SetPositionFromVec(self + 0x14, *(Vec *)(self + 0xA0));
        SpriteSlot_SetRotationQuat(self + 0x14, 0.0f, 0.0f, 0.0f);
        SpriteSlot_SetScaleUniform(self + 0x14, F(0xC4) * s);
    } else {
        Mtx_TransposeToMtx44(mA, self + 0x48);
        Matrix4_Identity(mB);
        Mtx44_Scale_Uniform(mB, mB, s);
        Matrix4_Multiply(mA, mB, mA);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, mA);
    }
    if (WP(0x4C) != 0) {
        Vec3_Copy(WB(0x4C) + 0x8C, self + 0xA0);
        *(float *)(WB(0x4C) + 0xB0) = F(0xC4);
        *(float *)(WB(0x4C) + 0x2C) = F(0x2C);
        WB(0x4C)[0x28] = self[0x28];
        *(float *)(WB(0x4C) + 0x154) = F(0x20) / 15.0f;
    }
    Timer_Tick((unsigned int *)(w + 0x4));
    Timer_Tick((unsigned int *)(w + 0x8));
    Timer_Tick((unsigned int *)(w + 0xC));
    Timer_Tick((unsigned int *)(w + 0x10));
}
