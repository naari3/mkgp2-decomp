#include "game/MathInline.h"

void Mtx44_TransformVec3(Vec3f *out, float m[4][4], const Vec3f *v)
{
    float y = v->y;
    float x = v->x;
    float z = v->z;
    out->x = m[3][0] + (z * m[2][0] + (x * m[0][0] + y * m[1][0]));
    out->y = m[3][1] + (z * m[2][1] + (x * m[0][1] + y * m[1][1]));
    out->z = m[3][2] + (z * m[2][2] + (x * m[0][2] + y * m[1][2]));
}
