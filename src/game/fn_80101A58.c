typedef struct Vec { float x, y, z; } Vec;

extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void Mtx44_TransformVec3(void *out, float m[4][4], Vec v);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void Vec3_Lerp(void *dst, Vec a, Vec b, float t);
extern float Vec3_HorizontalYawTo(void *a, void *b);
extern float Vec3_PitchTo(void *a, void *b);
extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern void Vec2_RotateX(void *dst, void *src, float a);
extern void Vec2_RotateY(void *dst, void *src, float a);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void Vec3_Copy(void *dst, void *src);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern float fn_800D3184(void *a, void *b);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void DrawEffect_ItemHitOriented_Spawn(Vec pos, Vec vel, int mode);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyRotZ(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern void SpriteSlot_TickAnim(void *slot);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);
extern float KartFxParam_GetConst1p5(void *kart);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);

extern void ItemEffectBus_ClearMask(void *bus, unsigned long long mask);

extern Vec lbl_80330C14;
extern char lbl_80330D00[];

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WI(o) (*(int *)(w + (o)))

void fn_80101A58(unsigned char *self, unsigned char *w)
{
    float m[4][4];
    Vec rootPos;
    Vec target;
    Vec probe;
    Vec fwd;
    Vec tmpv;
    float gy;
    float dist;
    float yaw;
    float d;
    float p0;
    unsigned char *bus;

    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(*(void **)(w + 0x9C)));
    Mtx44_GetTranslation_ColMajor(&rootPos, m);
    Mtx44_TransformVec3(&target, m, lbl_80330C14);
    switch (S8(0xC9)) {
    case 0:
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        self[0xC9]++;
        self[0xCA]++;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            WF(0x14) = 0.0f;
            self[0xCA]++;
        case 1:
            break;
        }
        Vec3_Lerp(self + 0xA0, target, *(Vec *)(self + 0xA0), WF(0x14));
        F(0xB0) = AngleStepTowards_Shortest(F(0xB0), Vec3_HorizontalYawTo(self + 0xA0, &target), 0.05235986f);
        F(0xAC) = AngleStepTowards_Shortest(F(0xAC), Vec3_PitchTo(self + 0xA0, &target), 0.05235986f);
        WF(0x14) += 0.3f;
        if (1.0f <= WF(0x14)) {
            self[0xC9]++;
            self[0xCA] = 0;
        }
        break;
    case 2:
        if (FinalLapCoinJump_CheckActiveForObject(*(void **)(w + 0x9C))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        GetSpawnPosition(&probe, 0.0f, -3.0f, -10.0f);
        Vec2_RotateX(&probe, &probe, F(0xAC));
        Vec2_RotateY(&probe, &probe, F(0xB0));
        Vec3_Add_DestFirst(&probe, self + 0xA0, &probe);
        GetSpawnPosition(&fwd, 0.0f, 0.0f, -1.0f);
        Vec2_RotateX(&fwd, &fwd, F(0xAC));
        Vec2_RotateY(&fwd, &fwd, F(0xB0));
        Vec3_Add_DestFirst(&fwd, self + 0xA0, &fwd);
        Vec3_Copy(self + 0xA0, &target);
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80330D00, 0x10, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            WU(0x4) = 1200;
            WU(0x8) = 0;
            WU(0xC) = 10;
            WF(0x14) = 0.0f;
            Vec3_Copy(w + 0x34, self + 0xA0);
            Vec3_Copy(w + 0x40, &fwd);
            WI(0x30) = -1;
            self[0xCA]++;
        case 1:
            dist = fn_800D3184(w + 0x34, self + 0xA0);
            if (2.0f < dist) {
                dist = 2.0f;
            }
            Vec3_Copy(w + 0x34, self + 0xA0);
            SpriteSlot_SetScale(self + 0x14, dist / 2.0f);
            if (0.1f < dist) {
                F(0xB0) = AngleStepTowards_Shortest(F(0xB0), Vec3_HorizontalYawTo(w + 0x40, self + 0xA0), 0.017453289f);
                Vec3_Copy(w + 0x40, &fwd);
            }
            yaw = Mtx44_GetYawOfPosZ(m);
            d = BuildOrientationFromYaw(yaw - F(0xB0));
            if (1.0471973f < FAbs_FloatAsDouble(d)) {
                if (0.0f < d) {
                    F(0xB0) = BuildOrientationFromYaw(yaw - 1.0471973f);
                } else {
                    F(0xB0) = BuildOrientationFromYaw(1.0471973f + yaw);
                }
            }
            if (ItemObject_GetGroundTypeAt(probe, &gy, 0) && probe.y < gy) {
                if (WF(0x14) < 0.0f) {
                    WF(0x14) = -1.0f * WF(0x14);
                }
                Vec3_Copy(&tmpv, &probe);
                tmpv.y = gy;
                p0 = Vec3_PitchTo(self + 0xA0, &tmpv);
                F(0xAC) += Vec3_PitchTo(self + 0xA0, &probe) - p0;
                if (0.1f < dist && WU(0x8) == 0) {
                    DrawEffect_ItemHitOriented_Spawn(tmpv, *(Vec *)(self + 0xB8), 2);
                    WU(0x8) = 3;
                }
            }
            if (FAbs_FloatAsDouble(F(0xAC)) < 1.5707959793508053) {
                WF(0x14) -= 0.008726644f;
            } else {
                WF(0x14) += 0.008726644f;
            }
            if (WF(0x14) < -0.08726645f) {
                WF(0x14) = -0.08726645f;
            }
            if (0.08726645f < WF(0x14)) {
                WF(0x14) = 0.08726645f;
            }
            F(0xAC) = BuildOrientationFromYaw(F(0xAC) + WF(0x14));
            if (1.0471973f < F(0xAC)) {
                F(0xAC) = 1.0471973f;
                WF(0x14) = 0.0f;
            }
            if (F(0xAC) < -2.6179934f) {
                F(0xAC) = -2.6179934f;
                WF(0x14) = 0.0f;
            }
            break;
        }
        if (WU(0xC) == 0) {
            bus = *(unsigned char **)(*(unsigned char **)(w + 0x9C) + 0x304);
            if (*(unsigned long long *)(bus + 0x10) & 0x10000) {
                ItemEffectBus_ClearMask(bus, 0x800000);
                WU(0x4) = 0;
            }
            if (!(*(unsigned long long *)(bus + 0x10) & 0x800000)) {
                WU(0x4) = 0;
            }
        }
        if (WU(0x4) == 0) {
            if (WI(0x30) >= 0) {
                SoundMgr_StopSE_OrSpecial(0x9D, WI(0x30));
                WI(0x30) = -1;
            }
            self[0xC9]++;
            self[0xCA] = 0;
            return;
        }
        if (WI(0x30) < 0) {
            WI(0x30) = SoundMgr_CountActiveSEInstances(0x9D);
            if (WI(0x30) >= 0) {
                SoundMgr_PlaySE_Positional(0x9D, *(Vec *)(self + 0xA0), WI(0x30));
            }
        } else {
            SoundMgr_PlaySE_WithChannel(0x9D, *(Vec *)(self + 0xA0), WI(0x30));
        }
        break;
    case 3:
        switch (S8(0xCA)) {
        case 0:
            self[0x28] = 1;
            GetSpawnPosition(self + 0xB8, 0.0f, 3.5f, 0.2f);
            Vec2_RotateY(self + 0xB8, self + 0xB8, F(0xB0));
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_80330D00, 0x10, 0);
            WU(0x4) = 10;
            Vec3_Subtract_DestFirst(w + 0x34, self + 0xA0, &rootPos);
            Vec3_Copy(w + 0x40, self + 0xB8);
            GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
            self[0xCA]++;
        case 1:
            WF(0x44) += -0.2f;
            Vec3_Add_DestFirst(w + 0x34, w + 0x34, w + 0x40);
            Vec3_Add_DestFirst(self + 0xA0, &rootPos, w + 0x34);
            F(0xAC) = BuildOrientationFromYaw(-0.08726645f + F(0xAC));
            if (WU(0x4) == 0) {
                F(0x2C) -= 0.05f;
                if (F(0x2C) < 0.0f) {
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                    return;
                }
            }
            break;
        }
        break;
    }
    Item_DecayVelocityScalar(self, 2.0f * KartFxParam_GetConst1p5(*(void **)(w + 0x9C)));
}
