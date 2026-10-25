typedef struct Vec {
    float x, y, z;
} Vec;

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int anim, float frame);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void GabyouItem_BuildLocalTransformFromHandJoint(void *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], float src[4][4]);
extern void Mtx44_TransformVec3(void *out, float m[4][4], Vec v);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern void *FindNearestDriverWithinConeAndRadius(Vec pos, void *kart, int flag, float yaw, float cone, float radius);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double);
extern void Vec2_RotateY(Vec *dst, Vec *src, float a);
extern void Vec3_Lerp(void *dst, Vec a, Vec b, float t);
extern float KartFxParam_GetConst1p5(void *kart);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern float KartCharacterParam_GetVfxBindHeightOffset(void *kart);
extern int ItemObject_DispatchVtable18_GetState(void *kart);
extern void ItemHit_Dispatch(void *self, int kind, void *pos, void *kart);
extern void SoundMgr_PlaySE_Positional(int id, Vec pos, int ch);
extern void Vec3_Copy(void *dst, Vec *src);
extern float Vec3_HorizontalYawTo(Vec *a, Vec *b);
extern void ItemObject_DispatchVtable1C_IfBoundedItem(void *kart, int state, int arg);

extern unsigned char lbl_80638300[];
extern Vec lbl_8032FF50;

static inline float LerpF(float a, float b, float t)
{
    return a * (1.0f - t) + b * t;
}

#define F(o) (*(float *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SP(o) (*(void **)(sub + (o)))

void HandOverItem_HandToHandTick(unsigned char *self, unsigned char *sub)
{
    float m[4][4];
    float inv[4][4];
    Vec pos;
    Vec dir;
    Vec pa;
    Vec pb;
    unsigned char *it;
    int i;
    float s;
    float y;

    switch ((signed char)self[0xC9]) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xCA]) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 1.0f, -0.2617993f, 1.5f);
            if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch ((signed char)sub[0xA0]) {
            case 1:
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                sub[0xA0] = 0;
                F(0x2C) = 1.0f;
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
    case 2:
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(SP(0x98)));
        Mtx44_GetTranslation_ColMajor(&pos, m);
        switch ((signed char)self[0xCA]) {
        case 0:
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            Mtx44_Inverse_GaussJordan(inv, m);
            Mtx44_TransformVec3(sub + 0x34, inv, *(Vec *)(self + 0xA0));
            if (*(signed char *)(sub + 0xF0)) {
                *(unsigned int *)(sub + 0x4) = 780;
            } else {
                *(unsigned int *)(sub + 0x4) = 600;
            }
            SF(0x14) = -1.570796f;
            SF(0x18) = 0.0f;
            for (i = 0; i < 0x100; i++) {
                it = lbl_80638300 + i * 0x1EC;
                if (*(signed char *)it && *(int *)(it + 0xC) == 0 && it != self && *(int *)(it + 0x8) == 0x54) {
                    unsigned char *isub = it + 0xEC;
                    if (SP(0x98) == *(void **)(isub + 0x98) && (char)it[0xC8] == 1 && (char)it[0xC9] == 2 && (char)it[0xCA] == 1) {
                        *(unsigned int *)(isub + 0x4) = 0;
                    }
                }
            }
            self[0xCA]++;
        case 1:
            SP(0x9C) = FindNearestDriverWithinConeAndRadius(pos, SP(0x98), 1, Mtx44_GetYawOfPosZ(m), 0.785398f, 70.0f);
            if (SP(0x9C) != 0) {
                self[0xC9]++;
                self[0xCA] = 0;
            } else if (*(unsigned int *)(sub + 0x4) == 0) {
                self[0xCA]++;
            }
            break;
        case 2:
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
            break;
        }
        if ((char)self[0x1E] == 1) {
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
        }
        SF(0x18) += 0.06666667f;
        if (1.0f < SF(0x18)) {
            SF(0x18) = 1.0f;
        }
        SF(0x14) = BuildOrientationFromYaw(0.034906577f + SF(0x14));
        dir = lbl_8032FF50;
        Vec2_RotateY(&dir, &dir, 0.785398f * (float)sin(SF(0x14)));
        Vec3_Lerp(sub + 0x34, dir, *(Vec *)(sub + 0x34), SF(0x18));
        Mtx44_TransformVec3(self + 0xA0, m, *(Vec *)(sub + 0x34));
        s = (float)sin(SF(0x14));
        y = BuildOrientationFromYaw(3.141592f + (0.785398f * s + Mtx44_GetYawOfPosZ(m)));
        F(0xB0) = BuildOrientationFromYaw(F(0xB0) * (1.0f - SF(0x18)) + y * SF(0x18));
        F(0xC4) = 1.5f * KartFxParam_GetConst1p5(SP(0x98));
        if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        break;
    case 3:
        Mtx44_GetTranslation_RowMajor(&pa, KartDriver_GetJointByIdx(SP(0x9C), 0xC));
        pa.y = pa.y + KartCharacterParam_GetVfxBindHeightOffset(SP(0x9C));
        pa.y += 3.0f;
        Mtx44_GetTranslation_RowMajor(&pb, KartDriver_GetJointByIdx(SP(0x98), 0xC));
        pb.y = pb.y + KartCharacterParam_GetVfxBindHeightOffset(SP(0x98));
        pb.y += 3.0f;
        switch ((signed char)self[0xCA]) {
        case 0:
            self[0x28] = 1;
            SF(0x18) = 0.0f;
            self[0xCA]++;
            self[0xCB] = 0;
        case 1:
            switch ((signed char)self[0xCB]) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                SF(0x14) = 0.0f;
                self[0xCB]++;
            case 1:
                Vec3_Lerp(self + 0xA0, pa, *(Vec *)(self + 0xA0), SF(0x14));
                SF(0x14) += 0.05f;
                if (1.0f < SF(0x14)) {
                    SF(0x14) = 1.0f;
                    *(int *)(sub + 0x24) = ItemObject_DispatchVtable18_GetState(SP(0x9C));
                    ItemHit_Dispatch(self, 0, self + 0xA0, SP(0x9C));
                    SoundMgr_PlaySE_Positional(0xB1, *(Vec *)(self + 0xA0), 0);
                    self[0xCA]++;
                    self[0xCB] = 0;
                }
                break;
            }
            break;
        case 2:
            switch ((signed char)self[0xCB]) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                self[0xCB]++;
            case 1:
                Vec3_Copy(self + 0xA0, &pa);
                if ((char)self[0x1E] == 1) {
                    self[0xCA]++;
                    self[0xCB] = 0;
                }
                break;
            }
            break;
        case 3:
            switch ((signed char)self[0xCB]) {
            case 0:
                SF(0x14) = 0.0f;
                self[0xCB]++;
            case 1:
                Vec3_Lerp(self + 0xA0, pb, *(Vec *)(self + 0xA0), SF(0x14));
                SF(0x14) += 0.05f;
                if (1.0f < SF(0x14)) {
                    ItemObject_DispatchVtable1C_IfBoundedItem(SP(0x98), *(int *)(sub + 0x24), 0);
                    SF(0x14) = 1.0f;
                    self[0xCA]++;
                    self[0xCB] = 0;
                }
                break;
            }
            break;
        case 4:
            if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            Vec3_Copy(self + 0xA0, &pb);
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                return;
            }
            break;
        }
        if ((char)self[0xCA] != 4) {
            SF(0x18) += 0.1f;
            if (1.0f < SF(0x18)) {
                SF(0x18) = 1.0f;
            }
            y = Vec3_HorizontalYawTo(&pa, &pb);
            F(0xB0) = BuildOrientationFromYaw(F(0xB0) * (1.0f - SF(0x18)) + y * SF(0x18));
        }
        F(0xC4) = 1.5f * KartFxParam_GetConst1p5(SP(0x98));
        break;
    }
}
