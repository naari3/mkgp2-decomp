#include "game/MathInline.h"

void Mtx44_GetTranslation_RowMajor(Vec3f *out, float m[3][4])
{
    out->x = m[0][3];
    out->y = m[1][3];
    out->z = m[2][3];
}

void Mtx_Lerp(float out[3][4], float a[3][4], float b[3][4], float t)
{
    float s = 1.0f - t;
    int i;

    for (i = 0; i < 3; i++) {
        out[i][0] = t * a[i][0] + s * b[i][0];
        out[i][1] = t * a[i][1] + s * b[i][1];
        out[i][2] = t * a[i][2] + s * b[i][2];
        out[i][3] = t * a[i][3] + s * b[i][3];
    }
}
