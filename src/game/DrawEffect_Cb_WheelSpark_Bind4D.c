/* DrawEffect_Cb_WheelSpark_Bind4D (0x800B75B8): wheel spark (resource 0x4D)
 * shot out behind a rear wheel joint (2 or 3 by variant) in kart space,
 * with a little random drift; it sinks and fades out after 10 frames. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D51BC; /* 2.0 */
extern const float lbl_806D51C0; /* 0.0 */
extern const float lbl_806D51C4; /* 1.0 */
extern const float lbl_806D51D4; /* 0.2 */
extern const float lbl_806D51E8; /* 0.5 */
extern const float lbl_806D51EC; /* 0.6 */
extern const float lbl_806D5200; /* 10.0 */
extern const float lbl_806D5208; /* 0.8 */
extern const float lbl_806D5210; /* -10.0 */
extern const float lbl_806D521C; /* deg->rad */
extern const float lbl_806D5224; /* 180.0 */
extern const float lbl_806D5228; /* 1.2 */
extern const float lbl_806D5244; /* 0.25 */
extern const float lbl_806D5248; /* 1.5 */
extern const float lbl_806D524C; /* -50.0 */
extern const float lbl_806D5250; /* -45.0 */
extern const float lbl_806D5254; /* -2.0 */
extern const float lbl_806D5258; /* 0.07 */
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec v);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);

void DrawEffect_Cb_WheelSpark_Bind4D(unsigned char *self)
{
    float m[4][4];
    Vec origin;
    Vec wheel;
    Vec dir;

    switch (STATE) {
    case 0: {

        VfxSlot_BindResourceEx(SLOT(self), 0x4D, 0);
        F(0x150) = lbl_806D51C4;
        F(0x154) = lbl_806D5244 * Rand_RangeFloat(lbl_806D51E8, lbl_806D5248);
        GetSpawnPosition(V(0xA4), 0.0f, 0.0f, lbl_806D51EC * Rand_RangeFloat(lbl_806D5208, lbl_806D5228));
        Vec2_RotateX(V(0xA4), V(0xA4), lbl_806D521C * Rand_RangeFloat(lbl_806D524C, lbl_806D5250));
        Vec2_RotateY(V(0xA4), V(0xA4), lbl_806D521C * (lbl_806D5224 + Rand_RangeFloat(lbl_806D5210, lbl_806D5200)));
        Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(P(0x11C)));
        dir = *V(0xA4);
        Mtx44_TransformVec3(V(0xA4), m, dir);
        Mtx44_GetTranslation_ColMajor(&origin, m);
        Vec3_Subtract_DestFirst(V(0xA4), V(0xA4), &origin);
        F(0x120) = Rand_RangeFloat(lbl_806D5254, lbl_806D51BC);
        F(0x124) = Rand_RangeFloat(lbl_806D5254, lbl_806D51BC);
        F(0x128) = Rand_RangeFloat(lbl_806D5254, lbl_806D51BC);
        U32(0x180) = 10;
        STATE++;
    }
    case 1:
        break;
    }

    if (U32(0x180) == 0) {
        F(0x150) -= lbl_806D51D4;
        if (F(0x150) < lbl_806D51C0) {
            DrawEffect_Free(self);
            return;
        }
    }
    F(0xA8) -= lbl_806D5258;
    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    {
        int joints[2] = {2, 3};
        Mtx44_GetTranslation_RowMajor(&wheel, KartDriver_GetJointByIdx(P(0x11C), joints[I(0x10)]));
        Vec3_Add_DestFirst(V(0x8C), &wheel, V(0x120));
    }
    F(0xB0) = F(0x150) * F(0x154);
    {
        Vec pos = *V(0x8C);
        VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    }
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
