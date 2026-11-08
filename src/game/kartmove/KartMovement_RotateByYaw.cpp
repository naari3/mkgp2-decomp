#include "game/kartmove/carobject_private.h"
#include "game/kartmove/speed_private.h"

extern const float lbl_806D96D0, lbl_806D96D4;
extern const float lbl_806D9704, lbl_806D9708, lbl_806D970C;
extern "C" double sin(double);
extern "C" double cos(double);

static inline void Identity(Matrix44 *a) {
    a->m[3][3] = a->m[2][2] = a->m[1][1] = a->m[0][0] = lbl_806D96D0;
    a->m[1][0] = a->m[0][3] = a->m[0][2] = a->m[0][1] = lbl_806D96D0;
    a->m[2][1] = a->m[2][0] = a->m[1][3] = a->m[1][2] = lbl_806D96D0;
    a->m[3][2] = a->m[3][1] = a->m[3][0] = a->m[2][3] = lbl_806D96D0;
    a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = lbl_806D96D4;
}

static inline float Dot(const float *a, const float *b) {
    float a0 = a[0], b0 = b[0];
    float a1 = a[1], b1 = b[4];
    float a2 = a[2], b2 = b[8];
    float a3 = a[3], b3 = b[12];
    float sum = a0*b0;
    sum += a1*b1;
    sum += a2*b2;
    sum += a3*b3;
    return sum;
}

static inline void Multiply(Matrix44 *a, const Matrix44 *b) {
    Matrix44 result;
    const float *row;
    const float *column;
    float *output = &result.m[0][0];
    const float *right = &b->m[0][0];
    int n = 0;
    for (int i = 0; i < 4; i++) {
        row = &((float *)a)[n];
        column = right;
        for (int j = 0; j < 4; j++, column++) {
            float value = Dot(row, column);
            output[n+j] = value;
        }
        n += 4;
    }
    for (int i = 0; i < 16; i++) ((float *)a)[i] = output[i];
}

extern const double lbl_806D96F0;

static inline void TransformVector(InitVec *v, const Matrix44 *m) {
    float rx = m->m[3][0] + (v->z*m->m[2][0] + (m->m[0][0]*v->x + v->y*m->m[1][0]));
    float ry = m->m[3][1] + (v->z*m->m[2][1] + (m->m[0][1]*v->x + v->y*m->m[1][1]));
    float rz = m->m[3][2] + (v->z*m->m[2][2] + (v->x*m->m[0][2] + v->y*m->m[1][2]));
    v->x = rx; v->y = ry; v->z = rz;
}

static inline void RotateYaw(Matrix44 *transform, float angle) {
    Matrix44 rotation;
    Identity(&rotation);
    double radians = lbl_806D96F0 * angle;
    float c = (float)cos((float)radians);
    float s = (float)sin((float)radians);
    rotation.m[0][0] = c; rotation.m[2][0] = s;
    rotation.m[2][2] = c; rotation.m[0][2] = -s;
    Multiply(&rotation, transform);
    *transform = rotation;
}

extern "C" void KartMovement_RotateByYaw(MovementInit *k, float angle) {
    Matrix44 transform;
    Identity(&transform);
    k->yaw += angle;
    RotateYaw(&transform, angle);
    TransformVector(&k->v17c, &transform);
    TransformVector(&k->v1f8, &transform);
    Multiply(&k->orientation, &transform);
    Multiply(&k->matrixD8, &transform);
}
