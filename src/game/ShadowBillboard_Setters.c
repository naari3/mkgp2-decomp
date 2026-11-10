/*
 * ShadowBillboard small setters, 0x80061918..0x80061954.
 */

#include "game/MathInline.h"

#include "game/types/ShadowBillboardSrc.h"

#include "game/types/ShadowBillboard.h"

extern const float lbl_806D2B88;
extern const float lbl_806D2B8C;
extern const float lbl_806D2B6C;
extern const float ShadowBillboard_LerpMtx4x4_rodata_802EE4CC[];

float Saturate_Double(float v, float lo, float hi);
void Mtx34_Orthonormalize(float *mtx);
void *GetCourseScene3D(void);
void CObj_LoadProjMatrix(void *scene, Vec3f *out);

void ShadowBillboard_SetField0xA4(ShadowBillboard *sb, float value)
{
    sb->heightA4 = value;
}

int ShadowBillboard_IsRenderReady(ShadowBillboard *sb)
{
    return sb->renderAlpha > 0.0f;
}

void ShadowBillboard_SetVec3At0x70(ShadowBillboard *sb, const Vec3f *v)
{
    sb->vec70.x = v->x;
    sb->vec70.y = v->y;
    sb->vec70.z = v->z;
}
