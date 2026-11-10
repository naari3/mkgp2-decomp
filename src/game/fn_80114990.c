/* Triple-item throw phase: swing the held item, aim at the nearest kart and release it. */
#include "game/types/Vec.h"

extern void AnimState_SetGlobalScale(void *anim, float s);
extern void AnimState_SetEnabledTimers(void *anim, float t);
extern void AnimState_Step(void *anim);
extern float AnimState_GetTotalScaleX(void *anim);
extern float AnimState_GetTotalScaleY(void *anim);
extern float AnimState_GetTotalScaleZ(void *anim);
extern float BuildOrientationFromYaw(float yaw);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void *FindNearestDriverWithinConeAndRadius(Vec pos, void *kart, int flag, float yaw, float cone, float radius);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern unsigned char *ItemObject_SpawnWithAlias(int id, int alias);
extern void JointByName_GetWorldPosition(void *out, void *slot, char *name);
extern void KartBurstShard_SpawnSet(unsigned char *fx);
extern int KartCharacterParam_GetIdentityIndex(void *kart);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Matrix4_Identity(float m[4][4]);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float dst[4][4]);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern float Mtx44_GetPitchOfPosZ_Padded(void *m);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *m);
extern float Mtx44_GetYawOfPosZ_Padded(void *m);
extern void Mtx44_Lerp(float dst[4][4], float a[4][4], float b[4][4], float t);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Mtx44_TransformVec3(void *out, float m[4][4], Vec v);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec v);
extern void Mtx_TransposeToMtx44(float dst[4][4], void *src);
extern void SoundMgr_PlaySE_Positional(int id, Vec pos, int ch);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int anim, float frame);
extern void SpriteSlot_SetJointScaleByName(void *slot, char *name, float x, float y, float z);
extern void SpriteSlot_TickAnim(void *slot);
extern float fn_800D4174(float m[4][4]);

extern float lbl_806CF410; /* swing speed */
extern float lbl_806CF414; /* swing limit */
extern float lbl_806CF418; /* aim radius */
extern float lbl_806CF41C; /* aim cone */
extern char lbl_80332498[];
extern char lbl_803324AC[];
extern Vec lbl_80421F20[];

#define F(o) (*(float *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(void **)(sub + (o)))
#define KART_FLAGS(k) (*(unsigned long long *)(*(unsigned char **)((unsigned char *)(k) + 0x304) + 0x10))

/* Places an effect's matrix so that its origin sits on the named joint of self. */
static inline void PlaceAtJoint(unsigned char *fx, unsigned char *self, char *name)
{
    float m[4][4];
    Vec jp;
    Vec tr;

    JointByName_GetWorldPosition(&jp, self + 0x14, name);
    Mtx_TransposeToMtx44(m, self + 0x48);
    Mtx44_GetTranslation_ColMajor(&tr, m);
    Matrix4_PreMultiplyTranslation(m, m, -tr.x + jp.x, -tr.y + jp.y, -tr.z + jp.z);
    DbgScene_CopyMatrix3x4Transpose(fx + 0x48, m);
}

/* Steps the two joint-scale animations and applies them to the item's joints. */
static inline void ScaleJointsByAnim(unsigned char *self, void *a, void *b)
{
    AnimState_SetGlobalScale(a, 0.0f);
    AnimState_SetGlobalScale(b, 0.0f);
    AnimState_SetEnabledTimers(a, F(0x20));
    AnimState_SetEnabledTimers(b, F(0x20));
    AnimState_Step(a);
    AnimState_Step(b);
    SpriteSlot_SetJointScaleByName(self + 0x14, lbl_803324AC, AnimState_GetTotalScaleX(a),
                                   AnimState_GetTotalScaleY(a), AnimState_GetTotalScaleZ(a));
    SpriteSlot_SetJointScaleByName(self + 0x14, lbl_80332498, AnimState_GetTotalScaleX(b),
                                   AnimState_GetTotalScaleY(b), AnimState_GetTotalScaleZ(b));
}

#pragma exceptions on
void fn_80114990(unsigned char *self, unsigned char *sub)
{
    float joint[4][4];
    float m[4][4];
    float prev[4][4];
    float r[4][4];
    Vec pos;
    float yaw;
    unsigned char *it;

    switch ((signed char)self[0xCA]) {
    case 0:
        SU(0x4) = 600;
        SF(0x14) = 0.0f;
        sub[0] = 0;
        SF(0x18) = 0.0f;
        SF(0x1C) = 0.0f;
        sub[1] = 0;
        SU(0xC) = 60;
        self[0xCA]++;
    case 1:
        SF(0x18) += 0.1f;
        if (1.0f < SF(0x18)) {
            SF(0x18) = 1.0f;
            self[0xCA]++;
        }
        break;
    case 2:
        SU(0x8) = 10;
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
        self[0xCA]++;
    case 3:
        if (sub[0]) {
            SF(0x14) += lbl_806CF410;
            if (lbl_806CF414 < SF(0x14)) {
                SF(0x14) = lbl_806CF414;
                sub[0] = 0;
            }
        } else {
            SF(0x14) -= lbl_806CF410;
            if (SF(0x14) < -lbl_806CF414) {
                SF(0x14) = -lbl_806CF414;
                sub[0] = 1;
            }
        }
        if (SU(0x8) == 0) {
            yaw = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(SP(0x98)));
            yaw = BuildOrientationFromYaw(yaw + SF(0x14));
            Mtx44_GetTranslation_RowMajor(&pos, KartDriver_GetKartRootMtx(SP(0x98)));
            SP(0x9C) = FindNearestDriverWithinConeAndRadius(pos, SP(0x98), 1, yaw, lbl_806CF41C, lbl_806CF418);
            if (SP(0x9C) != 0 && (KART_FLAGS(SP(0x9C)) & 0x0080000000000000ULL) != 0) {
                SP(0x9C) = 0;
            }
            sub[1] = 1;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
            self[0xCA]++;
        } else if (SU(0x4) == 0) {
            self[0xCA] = 5;
        }
        break;
    case 4:
        if ((int)self[0x1E] == 1) {
            self[0xCA] = 2;
        }
        break;
    case 5:
        F(0x2C) -= 0.1f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    if (SU(0xC) == 0 && (KART_FLAGS(SP(0x98)) & 0x0000040000000000ULL) == 0) {
        SU(0x4) = 0;
    }

    Mtx_TransposeToMtx44(joint, KartDriver_GetJointByIdx(SP(0x98), 15));
    Matrix4_Identity(m);
    Matrix4_PreMultiplyRotY(m, m, 1.570796f);
    Mtx44_Translate(m, m, lbl_80421F20[KartCharacterParam_GetIdentityIndex(SP(0x98))]);
    Matrix4_Multiply(m, m, joint);
    if ((int)self[0xCA] == 1) {
        if (SP(0x5C) != 0) {
            Mtx_TransposeToMtx44(prev, (unsigned char *)SP(0x5C) + 0x48);
        } else {
            Mtx_TransposeToMtx44(prev, self + 0x48);
        }
        Mtx44_Lerp(m, m, prev, SF(0x18));
    }
    if (SP(0x5C) != 0) {
        DbgScene_CopyMatrix3x4Transpose((unsigned char *)SP(0x5C) + 0x48, m);
        it = (unsigned char *)SP(0x5C);
        Mtx44_GetTranslation_RowMajor(it + 0xA0, it + 0x48);
        ((unsigned char *)SP(0x5C))[0x28] = self[0x28];
        *(float *)((unsigned char *)SP(0x5C) + 0x2C) = F(0x2C);
    }

    F(0xC4) = fn_800D4174(m);
    GetSpawnPosition(self + 0xA0, 0.0f, 1.0f, 0.0f);
    Mtx44_TransformVec3(self + 0xA0, m, *(Vec *)(self + 0xA0));
    F(0xAC) = Mtx44_GetPitchOfPosZ_Padded(KartDriver_GetKartRootMtx(SP(0x98)));
    F(0xB0) = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(SP(0x98)));
    Matrix4_Identity(r);
    Matrix4_PreMultiplyTranslation(r, r, 0.0f, -1.0f, 0.0f);
    Matrix4_PreMultiplyRotY(r, r, 1.570796f);
    Matrix4_PreMultiplyRotY(r, r, SF(0x14));
    Mtx44_Scale_Uniform(r, r, F(0xC4));
    Matrix4_PreMultiplyRotX(r, r, F(0xAC));
    Matrix4_PreMultiplyRotY(r, r, F(0xB0));
    Mtx44_Translate(r, r, *(Vec *)(self + 0xA0));
    DbgScene_CopyMatrix3x4Transpose(self + 0x48, r);

    if ((int)self[0x1D] == 1 && SU(0x6C) != 0 && SU(0x70) != 0) {
        void *a = SP(0x6C);
        void *b = SP(0x70);

        ScaleJointsByAnim(self, a, b);
    }

    {
        int visible = *(signed char *)(self + 0x28);
        self[0x28] = 1;
        SpriteSlot_TickAnim(self + 0x14);
        self[0x28] = visible;
    }

    if (sub[1]) {
        it = ItemObject_SpawnWithAlias(0x9E, 0xFF);
        if (it != 0) {
            JointByName_GetWorldPosition(it + 0xA0, self + 0x14, lbl_80332498);
            *(float *)(it + 0xB0) = Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(SP(0x98)));
            *(float *)(it + 0xB0) = BuildOrientationFromYaw(*(float *)(it + 0xB0) + SF(0x14));
            *(void **)(it + 0x180) = SP(0x94);
            *(void **)(it + 0x184) = SP(0x98);
            *(void **)(it + 0x168) = SP(0x9C);
        }
        if (*(signed char *)(self + 0x28)) {
            it = DrawEffect_SpawnDirect(KartBurstShard_SpawnSet);
            PlaceAtJoint(it, self, lbl_80332498);
            *(void **)(it + 0x11C) = SP(0x98);
            KartBurstShard_SpawnSet(it);
        }
        SoundMgr_PlaySE_Positional(0xD0, *(Vec *)(self + 0xA0), 0);
        sub[1] = 0;
    }
}
#pragma exceptions reset
