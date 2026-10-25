#include "game/MathInline.h"

extern void PSMTX44Identity(float dst[4][4]);
extern void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);
extern double atan2(float y, float x);

static inline void Mtx_TransposeToMtx44_Inline(float dst[4][4], float src[3][4])
{
    PSMTX44Identity(dst);
    dst[0][0] = src[0][0];
    dst[0][1] = src[1][0];
    dst[0][2] = src[2][0];
    dst[1][0] = src[0][1];
    dst[1][1] = src[1][1];
    dst[1][2] = src[2][1];
    dst[2][0] = src[0][2];
    dst[2][1] = src[1][2];
    dst[2][2] = src[2][2];
    dst[3][0] = src[0][3];
    dst[3][1] = src[1][3];
    dst[3][2] = src[2][3];
}

static inline void Mtx44_Xform(Vec3f *out, float m[4][4], Vec3f v)
{
    out->x = m[3][0] + (v.z * m[2][0] + (v.x * m[0][0] + v.y * m[1][0]));
    out->y = m[3][1] + (v.z * m[2][1] + (v.x * m[0][1] + v.y * m[1][1]));
    out->z = m[3][2] + (v.z * m[2][2] + (v.x * m[0][2] + v.y * m[1][2]));
}

static inline float GetAngle(float m[4][4])
{
    Vec3f pos;
    Vec3f dir;

    pos.x = m[3][0];
    pos.y = m[3][1];
    pos.z = m[3][2];
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 1.0f;
    Mtx44_Xform(&dir, m, dir);
    Vec3_Subtract(&dir, &pos, &dir);
    return atan2(-dir.y, MathInline_sqrtf(dir.x * dir.x + dir.z * dir.z));
}

float Mtx44_GetPitchOfPosZ_Padded(float src[3][4])
{
    float m[4][4];

    Mtx_TransposeToMtx44_Inline(m, src);
    return GetAngle(m);
}
