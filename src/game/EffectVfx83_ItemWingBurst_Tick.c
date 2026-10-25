/* EffectVfx83_ItemWingBurst_Tick (0x800C1BAC): feather burst (resource
 * 0x83) from a kart hand joint. Normal feathers fly out in a random cone
 * and fall; the 0x190 variant flies toward the camera. The sprite is
 * rotated to face its screen-space velocity. */
#include "game/DrawEffectAccess.h"

typedef struct CameraView {
    unsigned char pad0[0x80];
    Vec eye;
} CameraView;

extern CameraView lbl_805DF3D0;
extern const float lbl_806D51BC; /* 2.0 */
extern int Rand_RangeInt(int lo, int hi);
extern float Vec3_HorizontalYawTo(const Vec *from, const Vec *to);
extern float Vec3_PitchTo(const Vec *from, const Vec *to);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], void *src);
extern void VfxSlot_SetScaleVec3(void *slot, float x, float y, float z);
extern void EffectVfx_KartChildAttached_RenderHook(unsigned char *self);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern double atan2(float y, float x);

void EffectVfx83_ItemWingBurst_Tick(unsigned char *self)
{
    float root[4][4];
    float inv[4][4];
    Vec trans;
    Vec a;
    Vec b;
    Vec local;
    Vec c1;
    Vec c2;
    Vec pos;

    if (I(0x10) == 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetJointByIdx(P(0x11C), 0xA));
    } else {
        Mtx_TransposeToMtx44(root, KartDriver_GetJointByIdx(P(0x11C), 0xB));
    }
    Mtx44_GetTranslation_ColMajor(&trans, root);

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x83, 0);
        *(void (**)(unsigned char *))(self + 0x78) = EffectVfx_KartChildAttached_RenderHook;
        GetSpawnPosition(V(0x30), 1.0f, 0.5f, 0.0f);
        F(0x2C) = 1.0f;
        Vec3_Copy(V(0x8C), &trans);
        GetSpawnPosition(V(0x120), 0.0f, 0.0f, 0.0f);
        F(0xB0) = 0.7f * Rand_RangeFloat(0.5f, 1.5f);
        if (!S8(0x190)) {
            GetSpawnPosition(V(0xA4), 0.0f, Rand_RangeFloat(0.6f, 1.0f), 1.3f);
            Vec2_RotateX(V(0xA4), V(0xA4), 0.017453292f * Rand_RangeFloat(-25.0f, 15.0f));
            Vec2_RotateY(V(0xA4), V(0xA4), 0.017453292f * (180.0f + Rand_RangeFloat(-15.0f, 15.0f)));
            Vec3_Scale(V(0xA4), V(0xA4), Rand_RangeFloat(1.8f, 3.0f));
            local = *V(0xA4);
            Mtx44_TransformVec3(V(0xA4), root, &local);
            Vec3_Subtract_DestFirst(V(0xA4), V(0xA4), &trans);
        } else {
            Vec *eye = &lbl_805DF3D0.eye;
            float yaw = Vec3_HorizontalYawTo(V(0x8C), eye);
            float pitch = Vec3_PitchTo(V(0x8C), eye);
            yaw = BuildOrientationFromYaw(0.017453292f * Rand_RangeFloat(-15.0f, 15.0f) + yaw);
            pitch = BuildOrientationFromYaw(0.017453292f * Rand_RangeFloat(-15.0f, 15.0f) + pitch);
            GetSpawnPosition(V(0xA4), 0.0f, 0.0f, Rand_RangeFloat(1.5f, 3.0f));
            Vec2_RotateX(V(0xA4), V(0xA4), pitch);
            Vec2_RotateY(V(0xA4), V(0xA4), yaw);
        }
        U32(0x180) = (signed char)Rand_RangeInt(5, 15);
        Vec3_Scale(V(0xA4), V(0xA4), 0.2f);
        if (!S8(0x190)) {
            F(0x150) = 3.0f;
        } else {
            F(0x150) = 1.0f;
        }
        STATE++;
    case 1:
        if (U32(0x180) == 0) {
            Vec3_Scale(V(0xA4), V(0xA4), 5.0f);
            if (!S8(0x190)) {
                U32(0x180) = 0;
            } else {
                U32(0x180) = (signed char)Rand_RangeInt(15, 30);
            }
            STATE++;
        }
        break;
    case 2:
        F(0x150) -= 0.5f;
        if (F(0x150) < 1.0f) {
            F(0x150) = 1.0f;
        }
        if (!S8(0x190)) {
            F(0xA8) -= 0.07f;
        }
        if (U32(0x180) == 0) {
            F(0x2C) -= 0.1f;
            if (F(0x2C) < 0.0f) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }

    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    F(0xA8) -= 0.015f;
    Vec3_Add_DestFirst(V(0x8C), &trans, V(0x120));
    Mtx44_Inverse_GaussJordan(inv, &lbl_805DF3D0);
    c1 = *V(0x8C);
    Mtx44_TransformVec3(&a, inv, &c1);
    Vec3_Add_DestFirst(&b, V(0x8C), V(0xA4));
    c2 = b;
    Mtx44_TransformVec3(&b, inv, &c2);
    Vec3_Subtract_DestFirst(&a, &b, &a);
    F(0xA0) = atan2(a.x, a.y);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetRotationZ(SLOT(self), lbl_806D51BC * F(0xA0));
    VfxSlot_SetScaleVec3(SLOT(self), F(0xB0), F(0xB0), F(0xB0));
    if (S8(0x190)) {
        if (*(int *)(P(0x11C) + 0x238) == 0) {
            U8(0x28) = 0;
        } else {
            U8(0x28) = 1;
        }
    }
    TICK_TIMERS();
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
