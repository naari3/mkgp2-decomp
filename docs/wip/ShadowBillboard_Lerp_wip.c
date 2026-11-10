/*
 * ShadowBillboard matrix blend toward a target, 0x8006181C..0x80061918.
 */

#include "game/MathInline.h"

typedef struct ShadowBillboard {
    unsigned char pad00[0x5C];
    float *mtx; /* 4x4 */
} ShadowBillboard;

extern const float lbl_806D2B88;
extern const float lbl_806D2B8C;
extern const float lbl_806D2B6C;
extern const float ShadowBillboard_LerpMtx4x4_rodata_802EE4CC[];

float Saturate_Double(float v, float lo, float hi);
void Mtx34_Orthonormalize(float *mtx);

static inline void CopyPosition(Vec3f *dst, const Vec3f *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

static inline void LerpRow(ShadowBillboard *sb, const float *target, float t, float scale, int row)
{
    int j;
    for (j = 0; j < 3; j++) {
        sb->mtx[row + j] += t * (scale * (target[row + j] - sb->mtx[row + j]));
    }
}

#pragma exceptions on

void ShadowBillboard_LerpMtx4x4(ShadowBillboard *sb, const float *target, float t)
{
    unsigned int i;

    t = Saturate_Double(lbl_806D2B88 * t, lbl_806D2B8C, lbl_806D2B6C);
    for (i = 0; i < 3; i++) {
        LerpRow(sb, target, t, ShadowBillboard_LerpMtx4x4_rodata_802EE4CC[i], i * 4);
    }
    Mtx34_Orthonormalize(sb->mtx);
    CopyPosition((Vec3f *)(sb->mtx + 12), (const Vec3f *)(target + 12));
}

#pragma exceptions reset
