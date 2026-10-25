/*
 * ShadowBillboard small setters, 0x80061918..0x80061954.
 */

#include "game/MathInline.h"

typedef struct ShadowBillboardSrc {
    unsigned char pad000[0xF8];
    float axisX;
    float padFC;
    float axisZ;
} ShadowBillboardSrc;

typedef struct ShadowBillboard {
    unsigned char pad00[0x14];
    ShadowBillboardSrc *src;
    unsigned char pad18[0x5C - 0x18];
    float *mtx; /* 4x4 */
    unsigned char pad60[0x6C - 0x60];
    int field6C;
    Vec3f vec70;
    Vec3f camPos;
    Vec3f axis;
    float field94;
    unsigned char pad98[0xA0 - 0x98];
    float renderAlpha;
    float fieldA4;
} ShadowBillboard;

extern const float lbl_806D2B88;
extern const float lbl_806D2B8C;
extern const float lbl_806D2B6C;
extern const float lbl_802EE4CC[];

float Saturate_Double(float v, float lo, float hi);
void Mtx34_Orthonormalize(float *mtx);
void *GetCourseScene3D(void);
void CObj_LoadProjMatrix(void *scene, Vec3f *out);

void ShadowBillboard_SetField0xA4(ShadowBillboard *sb, float value)
{
    sb->fieldA4 = value;
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
