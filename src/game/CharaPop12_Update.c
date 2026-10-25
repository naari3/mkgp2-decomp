/* CharaPop12_Update (0x800B1014): one part (joint +0x10 of 14) of the
 * character "pop" model (sprite 0x9A) flying off: the other joints are
 * hidden, the part keeps its offset from the model origin and is flung
 * outward with a spin for 55 frames. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5028; /* 1.0 */
extern const float lbl_806D5034; /* 0.0 */
extern const float lbl_806D5038; /* 0.05 */
extern const float lbl_806D5044; /* 0.1 */
extern const float lbl_806D5068; /* -0.01 */
extern const float lbl_806D506C; /* 0.02 */
extern const float lbl_806D5070; /* -1.0 */
extern const float lbl_806D5074; /* -0.1 */
extern const char *lbl_8041A17C[14];
extern void SpriteSlot_InitNonLoop(void *slot, int id);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int on);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int flag, int hide);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern void SpriteSlot_Container_Free(unsigned char *self);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
extern void Matrix4_PreMultiplyRotX(float dst[4][4], float src[4][4], float a);
extern void Matrix4_PreMultiplyRotY(float dst[4][4], float src[4][4], float a);

void CharaPop12_Update(unsigned char *self)
{
    switch (S8(0xC8)) {
    case 0: {
        int i;

        SpriteSlot_InitNonLoop(SLOT(self), 0x9A);
        F(0xC4) = lbl_806D5028;
        SpriteSlot_SetTransform(SLOT(self), *V(0xA0), *V(0xAC), F(0xC4));
        SpriteSlot_TickAnim(SLOT(self));
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(SLOT(self), 1);
        for (i = 0; i < 14; i++) {
            if (I(0x10) != i) {
                SpriteSlot_SetJointVisibilityByName(SLOT(self), lbl_8041A17C[i], 0x10, 1);
            }
        }
        JointByName_GetWorldPosition(V(0xA0), SLOT(self), lbl_8041A17C[I(0x10)]);
        F(0xB8) = lbl_806D5044 * F(0xA0);
        F(0xBC) = lbl_806D5038 * F(0xA4);
        F(0xC0) = lbl_806D5044;
        if (F(0xBC) < 0.0f) {
            F(0xBC) = 0.0f;
        }
        F(0x12C) = lbl_806D5068 * F(0xA4);
        F(0x130) = lbl_806D506C * F(0xA0);
        F(0x134) = 0.0f;
        Vec3_Scale(V(0x120), V(0xA0), lbl_806D5070);
        U32(0xF0) = 55;
        S8(0xC8)++;
    }
    case 1:
        break;
    }

    if (U32(0xF0) == 0) {
        SpriteSlot_Container_Free(self);
        return;
    }
    F(0xBC) += lbl_806D5074;
    Vec3_Add_DestFirst(V(0xA0), V(0xA0), V(0xB8));
    F(0xAC) = BuildOrientationFromYaw(F(0xAC) + F(0x12C));
    F(0xB0) = BuildOrientationFromYaw(F(0xB0) + F(0x130));
    F(0xB4) = BuildOrientationFromYaw(F(0xB4) + F(0x134));
    {
        float m[4][4];
        Matrix4_Identity(m);
        Mtx44_Translate(m, m, *V(0x120));
        Matrix4_PreMultiplyRotX(m, m, F(0xAC));
        Matrix4_PreMultiplyRotY(m, m, F(0xB0));
        Mtx44_Translate(m, m, *V(0xA0));
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
    }
    if (U32(0xF0) != 0) U32(0xF0)--;
    if (U32(0xF4) != 0) U32(0xF4)--;
    if (U32(0xF8) != 0) U32(0xF8)--;
    if (U32(0xFC) != 0) U32(0xFC)--;
}
