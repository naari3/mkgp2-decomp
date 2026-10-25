/* EffectVfx1C_DriftSparkRing_Tick (0x800C0F80): drift spark (resource
 * 0x1C) thrown out from the kart at a jittered yaw. The sprite faces its
 * screen-space velocity and spins while it flies and fades. */
#include "game/DrawEffectAccess.h"

typedef struct CameraView {
    unsigned char pad0[0x40];
    float view[4][4];
} CameraView;

extern CameraView lbl_805DF3D0;
extern const float lbl_806D52B8; /* pi / 2 */
extern int Rand_RangeInt(int lo, int hi);
extern float LUT_Cosine(float angle);
extern void VfxSlot_SetScaleVec3(void *slot, float x, float y, float z);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern double atan2(float y, float x);

void EffectVfx1C_DriftSparkRing_Tick(unsigned char *self)
{
    float root[4][4];
    Vec trans;
    Vec dir;
    Vec a;
    Vec b;
    Vec d;
    Vec side;
    Vec c1;
    Vec c2;
    Vec c3;
    Vec c4;
    Vec pos;

    Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
    Mtx44_GetTranslation_ColMajor(&trans, root);

    switch (STATE) {
    case 0: {
        float yaw;
        float (*view)[4];

        VfxSlot_BindResourceEx(SLOT(self), 0x1C, 0);
        switch (I(0x10)) {
        case 1:
            GetSpawnPosition(V(0x30), 1.0f, 1.0f, 1.0f);
            break;
        case 2:
            GetSpawnPosition(V(0x30), 1.0f, 1.0f, 0.9f);
            break;
        case 3:
            GetSpawnPosition(V(0x30), 0.7f, 0.6f, 0.3f);
            break;
        }
        yaw = BuildOrientationFromYaw(0.017453292f * Rand_RangeFloat(-5.0f, 5.0f) + F(0x150));
        GetSpawnPosition(&dir, 0.0f, 0.0f, 1.0f);
        Vec2_RotateY(&dir, &dir, yaw);
        c1 = dir;
        Mtx44_TransformVec3(&dir, root, &c1);
        Vec3_Subtract_DestFirst(&dir, &dir, &trans);
        Vec3_Scale(V(0x120), &dir, !S8(0x190) ? Rand_RangeFloat(4.0f, 5.5f) : Rand_RangeFloat(5.5f, 7.5f));
        Vec3_Add_DestFirst(V(0x8C), &trans, V(0x120));
        Vec3_Scale(V(0xA4), &dir, Rand_RangeFloat(0.9f, 1.1f));
        view = lbl_805DF3D0.view;
        c2 = *V(0x8C);
        Mtx44_TransformVec3(&a, view, &c2);
        Vec3_Add_DestFirst(&b, V(0x8C), V(0xA4));
        c3 = b;
        Mtx44_TransformVec3(&b, view, &c3);
        Vec3_Subtract_DestFirst(&d, &b, &a);
        F(0xA0) = BuildOrientationFromYaw(atan2(d.x, d.y));
        if (0.0f < F(0xA0)) {
            F(0xA0) = BuildOrientationFromYaw(F(0xA0) - lbl_806D52B8);
        } else {
            F(0xA0) = BuildOrientationFromYaw(lbl_806D52B8 + F(0xA0));
        }
        F(0xB0) = (float)(unsigned char)!S8(0x190) * (F(0x158) * Rand_RangeFloat(0.7f, 0.9f))
                      ? 0.4f
                      : 0.45f;
        F(0x2C) = 3.0f * F(0x154);
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
        F(0x15C) = Rand_RangeFloat(0.05f, 0.07f);
        GetSpawnPosition(&side, 0.0f, 0.0f, 1.0f);
        c4 = side;
        Mtx44_TransformVec3(&side, root, &c4);
        Vec3_Subtract_DestFirst(&side, &side, &trans);
        F(0x160) = side.x * F(0xAC) - side.z * F(0xA4) > 0.0f ? 0.02f : -0.02f;
        F(0x164) = __fabs(LUT_Cosine(F(0x160)));
        U32(0x184) = Rand_RangeInt(0, 5);
        U32(0x180) = U32(0x184) + 4;
        STATE++;
    }
    case 1:
        break;
    }

    if (U32(0x184) == 0) {
        F(0x2C) -= F(0x15C);
        if (F(0x2C) < 0.0f) {
            DrawEffect_Free(self);
            return;
        }
        if (U32(0x180) == 1) {
            F(0xA4) *= 0.35f;
            F(0xAC) *= 0.35f;
            F(0xA8) *= 2.0f;
        }
        F(0xB0) += 0.1f;
        F(0xA0) = BuildOrientationFromYaw(F(0xA0) + F(0x160));
        F(0xA4) *= 0.9f * (1.0f + F(0x164));
        F(0xAC) *= 0.9f * (1.0f + F(0x164));
        F(0xA8) *= 0.9f * (1.0f - F(0x164));
        Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
        Vec3_Add_DestFirst(V(0x8C), &trans, V(0x120));
        pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
        VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
        VfxSlot_SetScaleVec3(SLOT(self), F(0xB0), F(0xB0), F(0xB0));
        if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
            U8(0x28) = 0;
        } else {
            U8(0x28) = 1;
        }
    } else {
        U8(0x28) = 0;
    }
    TICK_TIMERS();
}
