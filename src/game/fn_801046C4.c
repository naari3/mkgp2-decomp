typedef struct Vec { float x, y, z; } Vec;

extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void VfxLaughInner_Tick(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], float src[4][4]);
extern void Mtx44_TransformVec3(void *out, float m[4][4], Vec v);
extern float Vec3_ToYaw(void *v);
extern float FAbs_FloatAsDouble(float x);
extern float Vec3_HorizontalMagnitude(void *v);
extern void Vec3_ScaleXZ(void *dst, void *src, float s);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void Vec3_Copy(void *dst, void *src);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void DrawEffect_Free(void *e);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double);
extern double cos(double);
extern float Vec3_HorizontalYawTo(void *a, void *b);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern float KartFxParam_GetConst1p5(void *kart);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);

extern Vec lbl_803315D8;

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))

static inline unsigned char Bus_TestFlag(unsigned long long flags, unsigned long long mask)
{
    unsigned char r = 0;

    if (flags & mask) {
        r = 1;
    }
    return r;
}

void fn_801046C4(unsigned char *self, unsigned char *w)
{
    Vec home = lbl_803315D8;
    float m[4][4];
    float inv[4][4];
    Vec root;
    Vec rot;
    Vec fw;
    unsigned long long flags;
    int boost;
    int mode;
    float y0;
    float t;
    float m0;
    float mag;

    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(WP(0x9C)));
    Mtx44_GetTranslation_ColMajor(&root, m);
    boost = 0;
    flags = *(unsigned long long *)(*(unsigned char **)(*(unsigned char **)(w + 0x9C) + 0x304) + 0x10);
    if (Bus_TestFlag(flags, 0x10000)) {
        boost = 1;
    }
    mode = 0;
    if (flags & 0x80000000) {
        mode = 1;
    }
    if (flags & 0x100000000ULL) {
        mode = 2;
    }
    switch (S8(0xC9)) {
    case 0:
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        self[0x3C] = 0;
        WP(0x4C) = DrawEffect_SpawnDirect(VfxLaughInner_Tick);
        WU(0x8) = 10;
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            GetSpawnPosition(self + 0xAC, 0.0f, 0.0f, 0.0f);
            Mtx44_Inverse_GaussJordan(inv, m);
            Mtx44_TransformVec3(w + 0x34, inv, *(Vec *)(self + 0xA0));
            WF(0x14) = 0.0f;
            WF(0x18) = 0.785398f;
            WF(0x1C) = 0.0f;
            y0 = Vec3_ToYaw(w + 0x34);
            WF(0x20) = (1.0f / FAbs_FloatAsDouble(Vec3_ToYaw(&home) - y0)) / 0.17453289f;
            if (0.03f < WF(0x20)) {
                WF(0x20) = 0.03f;
            }
            if (*(signed char *)(w + 0xF0)) {
                WU(0x4) = 660;
            } else {
                WU(0x4) = 480;
            }
            self[0xCA]++;
        case 1:
            t = WF(0x1C);
            WF(0x38) = WF(0x38) * (1.0f - t) + home.y * t;
            m0 = Vec3_HorizontalMagnitude(w + 0x34);
            t = WF(0x1C);
            mag = m0 * (1.0f - t) + t * Vec3_HorizontalMagnitude(&home);
            if (m0) {
                Vec3_ScaleXZ(w + 0x34, w + 0x34, (1.0f / m0) * mag);
            } else {
                GetSpawnPosition(w + 0x34, 0.0f, WF(0x38), mag);
            }
            y0 = Vec3_ToYaw(w + 0x34);
            t = WF(0x1C);
            Vec2_RotateY(w + 0x34, w + 0x34, -y0 + (y0 * (1.0f - t) + t * Vec3_ToYaw(&home)));
            WF(0x1C) += WF(0x20);
            if (1.0f < WF(0x1C)) {
                Vec3_Copy(w + 0x34, &home);
                self[0xCA]++;
            }
            break;
        case 2:
            switch (mode) {
            case 1:
                if (*(char *)(self + 0x1D) != 3) {
                    SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                    SoundMgr_PlaySE_Positional(0xA5, *(Vec *)(self + 0xA0), 0);
                }
                break;
            case 2:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
                SoundMgr_PlaySE_Positional(0xA6, *(Vec *)(self + 0xA0), 0);
                break;
            }
            break;
        }
        if (WU(0x4) == 0) {
            F(0x2C) -= 0.05f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                DrawEffect_Free(WP(0x4C));
                WP(0x4C) = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
        }
        switch (S8(0x1D)) {
        case 4:
            if (0.785398f < WF(0x18)) {
                WF(0x18) = BuildOrientationFromYaw(WF(0x18) - 0.017453289f);
            }
            break;
        case 2:
            if (0.785398f < WF(0x18)) {
                WF(0x18) = BuildOrientationFromYaw(WF(0x18) - 0.017453289f);
            }
            if (*(char *)(self + 0x1E) == 2) {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, 0.0f);
            }
            break;
        case 3:
            if (WF(0x18) < 1.3089967f) {
                WF(0x18) = BuildOrientationFromYaw(0.034906577f + WF(0x18));
            }
            if (*(char *)(self + 0x1E) == 2) {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, 0.0f);
            }
            break;
        }
        switch (S8(0x1D)) {
        case 0:
            WF(0x14) = BuildOrientationFromYaw(0.034906577f + WF(0x14));
            break;
        case 2:
            WF(0x14) = BuildOrientationFromYaw(0.034906577f + WF(0x14));
            break;
        case 3:
            WF(0x14) = BuildOrientationFromYaw(0.07853980f + WF(0x14));
            break;
        }
        Vec2_RotateY(&rot, w + 0x34, WF(0x18) * (float)sin(WF(0x14)));
        rot.y += 4.0f * FAbs_FloatAsDouble((float)cos(WF(0x14))) + -4.0f;
        Mtx44_TransformVec3(self + 0xA0, m, rot);
        GetSpawnPosition(&fw, 0.0f, 0.0f, -10.0f);
        Mtx44_TransformVec3(&fw, m, fw);
        F(0xB0) = Vec3_HorizontalYawTo(self + 0xA0, &fw);
        if (boost && WU(0x8) == 0) {
            Vec3_Subtract_DestFirst(w + 0x34, self + 0xA0, &root);
            self[0xC9]++;
            self[0xCA] = 0;
            return;
        }
        break;
    case 2:
        switch (S8(0xCA)) {
        case 0:
            WU(0x4) = 10;
            GetSpawnPosition(w + 0x40, 0.0f, 2.0f, -1.0f);
            Vec2_RotateY(w + 0x40, w + 0x40, F(0xB0));
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 0.0f);
            self[0xCA]++;
        case 1:
            break;
        }
        if (WU(0x4) == 0) {
            F(0x2C) -= 0.05f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                DrawEffect_Free(WP(0x4C));
                WP(0x4C) = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
        }
        WF(0x44) += -0.1f;
        Vec3_Add_DestFirst(w + 0x34, w + 0x34, w + 0x40);
        Vec3_Add_DestFirst(self + 0xA0, &root, w + 0x34);
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - 0.17453289f);
        break;
    }
    Item_DecayVelocityScalar(self, 0.8f * KartFxParam_GetConst1p5(WP(0x9C)));
    if (FinalLapCoinJump_CheckActiveForObject(WP(0x9C))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}
