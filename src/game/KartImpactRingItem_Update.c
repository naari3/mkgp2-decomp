/* KartImpactRingItem_Update (0x800F38F8): impact-ring item that rides on
 * the kart's joint 16. It grows over 20 frames, drives a bound ring effect
 * and pushes hits to drivers within its radius until its timer expires. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D60B0; /* 0.0 */
extern const float lbl_806D60B4; /* 0.05 */
extern const float lbl_806D60B8; /* 1.0 */
extern const float lbl_806D60BC; /* 5.0 */
extern const float lbl_806D60C0; /* 4.0 */
extern const float lbl_806D60C4; /* 9.0 */
extern const float lbl_806D60C8; /* 75.0 */
extern void DrawEffect_Cb_KartVfx4B_StubInit(unsigned char *e);
extern void Matrix4_Copy(void *dst, void *src);
extern void Mtx44_TransformVec3(Vec *out, void *m, Vec v);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, void *m);
extern void DrawEffect_KartImpactRing_SpawnFromVfx(void *e, float m[3][4]);
extern void Item_PropagateHitToDriversInRadius(unsigned char *self, void *kart);
extern void SpriteSlot_Container_Free(unsigned char *self);

void KartImpactRingItem_Update(unsigned char *self)
{
    switch (S8(0xC8)) {
    case 0:
        U8(0x1C) = 0x9B;
        F(0x100) = 0.0f;
        U32(0xF0) = 1800;
        P(0x138) = DrawEffect_SpawnDirect(DrawEffect_Cb_KartVfx4B_StubInit);
        if (P(0x138) != 0) {
            *(void **)(P(0x138) + 0x11C) = P(0x184);
        }
        S8(0xC8) = 1;
        S8(0xC9) = 0;
    case 1: {
        float m[4][4];
        float m34[3][4];

        Mtx_TransposeToMtx44(m, KartDriver_GetJointByIdx(P(0x184), 0x10));
        Matrix4_Copy(self + 0x19C, m);
        {
            float *sc = &F(0x100);
            *sc += lbl_806D60B4;
            if (1.0f < *sc) {
                *sc = 1.0f;
            }
        }
        F(0xC4) = lbl_806D60BC * (lbl_806D60C0 * (lbl_806D60C4 * F(0x100)));
        GetSpawnPosition(V(0xA0), 0.0f, 0.0f, lbl_806D60C8);
        Vec3_Scale(V(0xA0), V(0xA0), F(0x100));
        Mtx44_TransformVec3(V(0xA0), self + 0x19C, *V(0xA0));
        Mtx44_GetTranslation_ColMajor(V(0x120), self + 0x19C);
        DbgScene_CopyMatrix3x4Transpose(m34, (float (*)[4])(self + 0x19C));
        DrawEffect_KartImpactRing_SpawnFromVfx(P(0x138), m34);
        Item_PropagateHitToDriversInRadius(self, P(0x184));
        if (S8(0x18C)) {
            U32(0xF0) = 0;
        }
        if (U32(0xF0) == 0) {
            S8(0xC8) = 3;
            S8(0xC9) = 0;
        }
        break;
    }
    case 3:
        DrawEffect_Free(P(0x138));
        P(0x138) = 0;
        SpriteSlot_Container_Free(self);
        return;
    }
    if (U32(0xF0) != 0) U32(0xF0)--;
    if (U32(0xF4) != 0) U32(0xF4)--;
    if (U32(0xF8) != 0) U32(0xF8)--;
    if (U32(0xFC) != 0) U32(0xFC)--;
}
