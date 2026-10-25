#include "game/MathInline.h"

extern const float lbl_806D5920; /* lbl_806D5920 */
extern const float lbl_806D5924; /* lbl_806D5924 */
extern const float lbl_806D5928; /* lbl_806D5928 */
extern const float lbl_806D592C; /* 0.0f */
extern const float lbl_806D5930; /* 1.0f */

extern float Vec3_Magnitude(const Vec3f *v);
extern void PSVECScale(const Vec3f *src, Vec3f *dst, float scale);
extern void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);

static inline float Vec3_DotInline(Vec3f a, Vec3f b)
{
    return a.z * b.z + (a.x * b.x + a.y * b.y);
}

static inline void Vec3_NormalizeInline(Vec3f *out, Vec3f v)
{
    float mag = Vec3_Magnitude(&v);
    if (lbl_806D5928 < mag) {
        out->x = v.x / mag;
        out->y = v.y / mag;
        out->z = v.z / mag;
    } else {
        out->x = lbl_806D592C;
        out->y = lbl_806D592C;
        out->z = lbl_806D5930;
    }
}

static inline void Vec3_ScaleByDot(Vec3f *out, const Vec3f *n, Vec3f a, Vec3f b)
{
    PSVECScale(n, out, lbl_806D5924);
    PSVECScale(out, out, a.z * b.z + (a.x * b.x + a.y * b.y));
}

void Vec3_OrthoProjectThenScaleByLen(Vec3f *out, const Vec3f *dir, const Vec3f *normal)
{
    float len = Vec3_Magnitude(dir);
    Vec3f r;
    Vec3f neg;

    PSVECScale(dir, &neg, lbl_806D5920);
    Vec3_ScaleByDot(&r, normal, *normal, neg);
    Vec3_Subtract(&r, &neg, &r);
    Vec3_NormalizeInline(&r, r);
    PSVECScale(&r, &r, len);
    out->x = r.x;
    out->y = r.y;
    out->z = r.z;
}
