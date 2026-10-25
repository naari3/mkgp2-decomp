/* EffectVfx134_KartHitBurst_Tick (0x800BEF18): smoke burst (resource 0x86)
 * thrown backward in kart space; it grows by a random rate while it fades
 * and is drawn through an explicit model matrix offset 5 units up. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51C8; /* 0.1 */
extern const float lbl_806D51CC; /* 5.0 */
extern const float lbl_806D5304; /* 1.6 */
extern const float lbl_806D5348; /* pi */
extern const float lbl_806D5368; /* 1.8 */
extern const float lbl_806D536C; /* 0.12 */
extern void VfxSlot_BindResource(void *slot, int res);
extern void VfxSlot_SetMatrixSourceEnabled(void *slot, int on);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec v);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_PreMultiplyTranslation(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float dst[4][4], float a[4][4], float b[4][4]);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);

void EffectVfx134_KartHitBurst_Tick(unsigned char *self)
{
    float m[4][4];
    float t[4][4];
    float kart[4][4];
    Vec origin;

    Mtx_TransposeToMtx44(kart, KartDriver_GetKartRootMtx(P(0x11C)));
    Mtx44_GetTranslation_ColMajor(&origin, kart);
    switch (STATE) {
    case 0:
        VfxSlot_BindResource(SLOT(self), 0x86);
        VfxSlot_SetMatrixSourceEnabled(SLOT(self), 1);
        GetSpawnPosition(V(0xA4), lbl_806D51C0, lbl_806D51C0, lbl_806D51C4);
        Vec2_RotateY(V(0xA4), V(0xA4), lbl_806D5348);
        Mtx44_TransformVec3(V(0xA4), kart, *V(0xA4));
        Vec3_Subtract_DestFirst(V(0xA4), V(0xA4), &origin);
        F(0x2C) = lbl_806D51C4;
        F(0x150) = Rand_RangeFloat(lbl_806D5304, lbl_806D5368);
        F(0x154) = lbl_806D51C4;
        F(0xB0) = F(0x150) * F(0x154);
        F(0x158) = Rand_RangeFloat(lbl_806D51C8, lbl_806D536C);
        GetSpawnPosition(V(0x120), 0.0f, 0.0f, 0.0f);
        STATE++;
    case 1:
        F(0x2C) -= lbl_806D51C8;
        if (F(0x2C) < lbl_806D51C0) {
            S8(0x28) = 0;
            DrawEffect_Free(self);
            return;
        }
        F(0x154) += F(0x158);
        F(0xB0) = F(0x150) * F(0x154);
        Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
        Matrix4_Identity(m);
        Mtx44_Scale_Uniform(m, m, F(0xB0));
        Matrix4_PreMultiplyTranslation(m, m, lbl_806D51C0, lbl_806D51C0, lbl_806D51CC);
        Matrix4_Multiply(m, m, kart);
        Matrix4_Identity(t);
        Mtx44_Translate(t, t, *V(0x120));
        Matrix4_Multiply(m, m, t);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
        Mtx44_GetTranslation_RowMajor(V(0x8C), self + 0x48);
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        S8(0x28) = 0;
    } else {
        S8(0x28) = 1;
    }
}
