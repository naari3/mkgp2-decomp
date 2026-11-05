/* Native reconstruction of the target X/Y/Z composition and translation.
 * Keep the LUT assignments in target order; these follow Matrix4RotXY/Z. */
#include "game/MathInline.h"

static inline void C7_Mtx44Identity(float m[4][4])
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
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



extern float LUT_Sine(float angle);
extern float LUT_Cosine(float angle);

static inline void C7_FillX(float rotation[4][4], float angle)
{
    float sine, cosine;
    C7_Mtx44Identity(rotation);
    sine = LUT_Sine(angle);
    cosine = LUT_Cosine(angle);
    rotation[1][1] = sine;
    rotation[2][1] = -cosine;
    rotation[1][2] = cosine;
    rotation[2][2] = sine;
}

static inline void C7_FillY(float rotation[4][4], float angle)
{
    float sine, cosine;
    C7_Mtx44Identity(rotation);
    sine = LUT_Sine(angle);
    cosine = LUT_Cosine(angle);
    rotation[2][2] = sine;
    rotation[2][0] = cosine;
    rotation[0][2] = -cosine;
    rotation[0][0] = sine;
}

static inline void C7_FillZ(float rotation[4][4], float angle)
{
    float sine, cosine;
    C7_Mtx44Identity(rotation);
    sine = LUT_Sine(angle);
    cosine = LUT_Cosine(angle);
    rotation[0][0] = sine;
    rotation[0][1] = cosine;
    rotation[1][0] = -cosine;
    rotation[1][1] = sine;
}

void Mtx44_FromEulerXYZTrans(float dst[4][4], const Vec3f *translation, const Vec3f *angles)
{
    float rotationX[4][4];
    float rotationY[4][4];
    float rotationZ[4][4];
    float tr[4][4];
    Vec3f t;

    C7_Mtx44Identity(dst);
    C7_FillX(rotationX, angles->x);
    C7_Mtx44Mul(dst, dst, rotationX);
    C7_FillY(rotationY, angles->y);
    C7_Mtx44Mul(dst, dst, rotationY);
    C7_FillZ(rotationZ, angles->z);
    C7_Mtx44Mul(dst, dst, rotationZ);
    t = *translation;
    C7_Mtx44Identity(tr);
    tr[3][0] = t.x;
    tr[3][1] = t.y;
    tr[3][2] = t.z;
    C7_Mtx44Mul(dst, dst, tr);
}
