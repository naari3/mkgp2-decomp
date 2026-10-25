#include "game/MathInline.h"

static inline void Mtx44_Identity(float m[4][4])
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

static inline void Mtx44_Mul(float out[4][4], float a[4][4], float b[4][4])
{
    float tmp[4][4];
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tmp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
        }
    }
    out[0][0] = tmp[0][0]; out[0][1] = tmp[0][1]; out[0][2] = tmp[0][2]; out[0][3] = tmp[0][3];
    out[1][0] = tmp[1][0]; out[1][1] = tmp[1][1]; out[1][2] = tmp[1][2]; out[1][3] = tmp[1][3];
    out[2][0] = tmp[2][0]; out[2][1] = tmp[2][1]; out[2][2] = tmp[2][2]; out[2][3] = tmp[2][3];
    out[3][0] = tmp[3][0]; out[3][1] = tmp[3][1]; out[3][2] = tmp[3][2]; out[3][3] = tmp[3][3];
}

void Mtx44_Translate(float dst[4][4], float src[4][4], const Vec3f *t)
{
    float tr[4][4];

    Mtx44_Identity(tr);
    tr[3][0] = t->x;
    tr[3][1] = t->y;
    tr[3][2] = t->z;
    Mtx44_Mul(dst, src, tr);
}
