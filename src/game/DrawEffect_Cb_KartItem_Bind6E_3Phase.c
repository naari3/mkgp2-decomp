/* DrawEffect_Cb_KartItem_Bind6E_3Phase (0x800B7864): puff (resource 0x6E)
 * thrown off one rear wheel (I(0x10) picks the side), drifting in the
 * kart's local frame. Phase 1 fades it in, phase 2 fades it out. */
#include "game/DrawEffectAccess.h"

extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], float src[4][4]);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);

void DrawEffect_Cb_KartItem_Bind6E_3Phase(unsigned char *self)
{
    float root[4][4];
    float inv[4][4];
    float m[4][4];
    Vec trans;
    Vec local;
    Vec cur;
    Vec pos;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x6E, 0);
        if (I(0x10) == 0) {
            Mtx44_GetTranslation_RowMajor(V(0x8C), KartDriver_GetJointByIdx(P(0x11C), 2));
        } else {
            Mtx44_GetTranslation_RowMajor(V(0x8C), KartDriver_GetJointByIdx(P(0x11C), 3));
        }
        F(0x150) = 1.0f;
        F(0x154) = 0.2f * Rand_RangeFloat(0.5f, 1.5f);
        F(0x158) = 0.0f;
        F(0xA0) = 0.017453292f * Rand_RangeFloat(-180.0f, 180.0f);
        F(0x15C) = 0.017453292f * Rand_RangeFloat(-2.0f, 2.0f);
        GetSpawnPosition(V(0xA4), 0.0f, 0.0f, 0.2f * Rand_RangeFloat(0.5f, 1.5f));
        Vec2_RotateX(V(0xA4), V(0xA4), 0.017453292f * Rand_RangeFloat(-90.0f, 0.0f));
        Vec2_RotateY(V(0xA4), V(0xA4), 0.017453292f * Rand_RangeFloat(90.0f, 180.0f));
        if (I(0x10) != 0) {
            V(0xA4)->x *= -1.0f;
        }
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
        Mtx44_GetTranslation_ColMajor(&trans, root);
        Mtx_TransposeToMtx44(inv, KartDriver_GetKartRootMtx(P(0x11C)));
        Mtx44_Inverse_GaussJordan(inv, inv);
        local = *V(0x8C);
        Mtx44_TransformVec3(V(0x120), inv, &local);
        F(0x128) = F(0x128) - 3.0f;
        STATE++;
        break;
    case 1:
        F(0x150) += 0.3f;
        if (1.0f <= F(0x150)) {
            F(0x150) = 1.0f;
        }
        F(0x158) += 0.3f;
        if (1.0f <= F(0x158)) {
            F(0x158) = 1.0f;
        }
        if (1.0f <= F(0x150) && 1.0f <= F(0x158)) {
            STATE++;
        }
        break;
    case 2:
        F(0x150) += 0.005f;
        F(0x158) -= 0.05f;
        if (F(0x158) < 0.0f) {
            DrawEffect_Free(self);
            return;
        }
        break;
    }

    Vec3_Scale(V(0xA4), V(0xA4), 0.95f);
    F(0xA8) += 0.003f;
    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(P(0x11C)));
    cur = *V(0x120);
    Mtx44_TransformVec3(V(0x8C), m, &cur);
    F(0xA0) = BuildOrientationFromYaw(F(0xA0) + F(0x15C));
    F(0xB0) = 3.0f * (F(0x150) * F(0x154));
    F(0x2C) = F(0x158);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
