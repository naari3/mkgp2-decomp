#include "game/MathInline.h"

extern void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);
extern double atan2(float y, float x);

static inline void Mtx44_Xform(Vec3f *out, float m[4][4], Vec3f v)
{
    out->x = m[3][0] + (v.z * m[2][0] + (v.x * m[0][0] + v.y * m[1][0]));
    out->y = m[3][1] + (v.z * m[2][1] + (v.x * m[0][1] + v.y * m[1][1]));
    out->z = m[3][2] + (v.z * m[2][2] + (v.x * m[0][2] + v.y * m[1][2]));
}

static inline void GetAngles(const Vec3f *d, float *pitch, float *yaw)
{
    float h = MathInline_sqrtf(d->x * d->x + d->z * d->z);
    float ny = -d->y;
    *yaw = atan2(d->x, d->z);
    *pitch = atan2(ny, h);
}

void Mtx44_GetYawPitchOfPosZ(float m[4][4], float *pitch, float *yaw)
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
    GetAngles(&dir, pitch, yaw);
}
