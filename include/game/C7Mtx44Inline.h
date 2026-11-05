#ifndef GAME_C7_MTX44_INLINE_H
#define GAME_C7_MTX44_INLINE_H

/* Private native matrix helpers for the 0x800D3278 and 0x800D4174 TUs. */
#include "game/MathInline.h"

extern const float lbl_806D5920;
extern const float lbl_806D592C;
extern const float lbl_806D5930;

static inline void C7_Mtx44Identity(float m[4][4])
{
    m[0][0] = lbl_806D5930; m[0][1] = lbl_806D592C; m[0][2] = lbl_806D592C; m[0][3] = lbl_806D592C;
    m[1][0] = lbl_806D592C; m[1][1] = lbl_806D5930; m[1][2] = lbl_806D592C; m[1][3] = lbl_806D592C;
    m[2][0] = lbl_806D592C; m[2][1] = lbl_806D592C; m[2][2] = lbl_806D5930; m[2][3] = lbl_806D592C;
    m[3][0] = lbl_806D592C; m[3][1] = lbl_806D592C; m[3][2] = lbl_806D592C; m[3][3] = lbl_806D5930;
}

static inline void C7_Mtx44Mul(float out[4][4], float a[4][4], float b[4][4])
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

static inline void C7_Mtx44Copy(float out[4][4], const float in[4][4])
{
    out[0][0] = in[0][0];
    out[0][1] = in[0][1];
    out[0][2] = in[0][2];
    out[0][3] = in[0][3];
    out[1][0] = in[1][0];
    out[1][1] = in[1][1];
    out[1][2] = in[1][2];
    out[1][3] = in[1][3];
    out[2][0] = in[2][0];
    out[2][1] = in[2][1];
    out[2][2] = in[2][2];
    out[2][3] = in[2][3];
    out[3][0] = in[3][0];
    out[3][1] = in[3][1];
    out[3][2] = in[3][2];
    out[3][3] = in[3][3];
}

static inline void C7_Mtx44Translate(float dst[4][4], float src[4][4], Vec3f t)
{
    float tr[4][4];
    C7_Mtx44Identity(tr);
    tr[3][0] = t.x;
    tr[3][1] = t.y;
    tr[3][2] = t.z;
    C7_Mtx44Mul(dst, src, tr);
}

static inline void C7_Mtx44Xform(Vec3f *out, float m[4][4], Vec3f v)
{
    out->x = m[3][0] + (v.z * m[2][0] + (v.x * m[0][0] + v.y * m[1][0]));
    out->y = m[3][1] + (v.z * m[2][1] + (v.x * m[0][1] + v.y * m[1][1]));
    out->z = m[3][2] + (v.z * m[2][2] + (v.x * m[0][2] + v.y * m[1][2]));
}

#endif
