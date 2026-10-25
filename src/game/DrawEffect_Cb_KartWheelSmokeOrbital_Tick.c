/* DrawEffect_Cb_KartWheelSmokeOrbital_Tick (0x800C968C): smoke puff (one
 * of resources 0x37..0x39) thrown in the kart's local frame toward joint
 * 0xF, with +-15 degree jitter. It grows and fades over 20 frames. */
#include "game/DrawEffectAccess.h"

extern int Rand_RangeIntMax(int max);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], float src[4][4]);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern float Vec3_ToPitch(const Vec *v);
extern float Vec3_ToYaw(const Vec *v);

void DrawEffect_Cb_KartWheelSmokeOrbital_Tick(unsigned char *self)
{
    float inv[4][4];
    float inv2[4][4];
    float root[4][4];
    Vec joint;
    Vec local;
    Vec local2;
    Vec local3;
    Vec pos;
    float pitch;
    float yaw;

    switch (STATE) {
    case 0:
        switch (Rand_RangeIntMax(0xF) % 3) {
        case 0:
            VfxSlot_BindResourceEx(SLOT(self), 0x37, 0);
            break;
        case 1:
            VfxSlot_BindResourceEx(SLOT(self), 0x38, 0);
            break;
        case 2:
            VfxSlot_BindResourceEx(SLOT(self), 0x39, 0);
            break;
        }
        Mtx_TransposeToMtx44(inv, KartDriver_GetKartRootMtx(P(0x11C)));
        Mtx44_Inverse_GaussJordan(inv, inv);
        local = *V(0x8C);
        Mtx44_TransformVec3(V(0x120), inv, &local);
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), 0xF));
        Mtx_TransposeToMtx44(inv2, KartDriver_GetKartRootMtx(P(0x11C)));
        Mtx44_Inverse_GaussJordan(inv2, inv2);
        local2 = joint;
        Mtx44_TransformVec3(&joint, inv2, &local2);
        Vec3_Subtract_DestFirst(V(0xA4), &joint, V(0x120));
        pitch = BuildOrientationFromYaw(Vec3_ToPitch(V(0xA4)) + 0.017453292f * Rand_RangeFloat(-15.0f, 15.0f));
        yaw = BuildOrientationFromYaw(Vec3_ToYaw(V(0xA4)) + 0.017453292f * Rand_RangeFloat(-15.0f, 15.0f));
        GetSpawnPosition(V(0xA4), 0.0f, 0.0f, 1.5f * Rand_RangeFloat(0.7f, 1.3f));
        Vec2_RotateX(V(0xA4), V(0xA4), pitch);
        Vec2_RotateY(V(0xA4), V(0xA4), yaw);
        F(0x150) = 0.0f;
        F(0x154) = Rand_RangeFloat(0.8f, 1.2f);
        STATE++;
        break;
    case 1:
        break;
    }

    F(0x150) += 0.05f;
    if (1.0f < F(0x150)) {
        DrawEffect_Free(self);
        return;
    }
    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
    local3 = *V(0x120);
    Mtx44_TransformVec3(V(0x8C), root, &local3);
    F(0xB0) = F(0x150) * F(0x154);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    F(0x2C) = 2.0f * (1.0f - F(0x150));
    if (1.0f < F(0x2C)) {
        F(0x2C) = 1.0f;
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
