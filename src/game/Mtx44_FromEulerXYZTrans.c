/* Native reconstruction of the target X/Y/Z composition and translation.
 * Keep the LUT assignments in target order; these follow Matrix4RotXY/Z. */
#include "game/C7Mtx44Inline.h"

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
