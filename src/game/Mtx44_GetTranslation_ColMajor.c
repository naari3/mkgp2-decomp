#include "game/MathInline.h"

void Mtx44_GetTranslation_ColMajor(Vec3f *out, float m[4][4])
{
    out->x = m[3][0];
    out->y = m[3][1];
    out->z = m[3][2];
}

void Mtx44_Lerp(float out[4][4], float a[4][4], float b[4][4], float t)
{
    float s = 1.0f - t;
    int i;

    for (i = 0; i < 4; i++) {
        out[i][0] = t * a[i][0] + s * b[i][0];
        out[i][1] = t * a[i][1] + s * b[i][1];
        out[i][2] = t * a[i][2] + s * b[i][2];
        out[i][3] = t * a[i][3] + s * b[i][3];
    }
}
