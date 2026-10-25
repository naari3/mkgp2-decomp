/* EffectVfx13or14_MushroomDust_Tick (0x800BE5A0): mushroom boost dust puff
 * (resource 0x13 or 0x14) spinning around one of the kart's rear joints. */
#include "game/DrawEffectAccess.h"

/* rear-wheel joint table {2, 3} */
extern const int lbl_806D51AC;
extern const int lbl_806D51B0;
extern int Rand_RangeIntMax(int max);
extern float KartCharacterParam_GetBoostFxSizeFactor(void *driver);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);

void EffectVfx13or14_MushroomDust_Tick(unsigned char *self)
{
    Vec trans;
    Vec joint;
    Vec local;
    Vec pos;
    float root[4][4];

    switch (STATE) {
    case 0:
        if (Rand_RangeIntMax(0x10) % 16 != 0) {
            VfxSlot_BindResourceEx(SLOT(self), 0x14, 0);
        } else {
            VfxSlot_BindResourceEx(SLOT(self), 0x13, 0);
        }
        F(0x2C) = 0.0f;
        F(0x150) = Rand_RangeFloat(0.8f, 1.2f);
        F(0x154) = 0.0f;
        F(0x120) = Rand_RangeFloat(-1.0f, 1.0f);
        F(0x124) = 0.0f;
        F(0x128) = 0.0f;
        U32(0x180) = 5;
        F(0xA0) = 0.017453292f * Rand_RangeFloat(-180.0f, 180.0f);
        F(0x158) = 0.017453292f * Rand_RangeFloat(-10.0f, 10.0f);
        STATE++;
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        F(0x2C) -= 0.06f;
        if (F(0x2C) < 0.0f) {
            DrawEffect_Free(self);
            return;
        }
    } else {
        F(0x2C) += 0.1f;
        if (0.6f < F(0x2C)) {
            F(0x2C) = 0.6f;
        }
    }

    F(0x154) = BuildOrientationFromYaw(0.13962634f + F(0x154));
    GetSpawnPosition(V(0x8C), 0.0f, -2.5f, 0.0f);
    Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0x120));
    Vec3_Scale(V(0x8C), V(0x8C), KartCharacterParam_GetBoostFxSizeFactor(P(0x11C)));
    Vec2_RotateX(V(0x8C), V(0x8C), F(0x154));
    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
    local = *V(0x8C);
    Mtx44_TransformVec3(V(0x8C), root, &local);
    Mtx44_GetTranslation_ColMajor(&trans, root);
    Vec3_Subtract_DestFirst(V(0x8C), V(0x8C), &trans);
    {
        int joints[2];
        joints[0] = lbl_806D51AC;
        joints[1] = lbl_806D51B0;
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), joints[I(0x10)]));
    }
    Vec3_Add_DestFirst(V(0x8C), &joint, V(0x8C));
    F(0x90) += 0.5f;
    F(0xA0) = BuildOrientationFromYaw(F(0xA0) + F(0x158));
    F(0xB0) = 0.4f * F(0x150);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
