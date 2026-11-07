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

static inline void MultiplyRow(const float *a, const Matrix44 *b, float *out, int &index) {
    for (int j = 0; j < 4; j++, index++) {
        float a0 = a[0];
        float b0 = b->m[0][j];
        float a1 = a[1];
        float b1 = b->m[1][j];
        float a2 = a[2];
        float b2 = b->m[2][j];
        float a3 = a[3];
        float b3 = b->m[3][j];
        float sum = a0*b0;
        sum += a1*b1;
        sum += a2*b2;
        sum += a3*b3;
        out[index] = sum;
    }
}

static inline void Multiply(Matrix44 *a, const Matrix44 *b) {
    float out[16];
    int index = 0;
    for (int i = 0; i < 4; i++) {
        MultiplyRow(a->m[i], b, out, index);
    }
    for (int i = 0; i < 16; i++) ((float *)a)[i] = out[i];
}

extern const double lbl_806D96F0;

static inline void TransformVector(InitVec *v, const Matrix44 *m) {
    float x = v->x, y = v->y, z = v->z;
    float rx = m->m[3][0] + (z*m->m[2][0] + (m->m[0][0]*x + y*m->m[1][0]));
    float ry = m->m[3][1] + (z*m->m[2][1] + (m->m[0][1]*x + y*m->m[1][1]));
    float rz = m->m[3][2] + (z*m->m[2][2] + (x*m->m[0][2] + y*m->m[1][2]));
    v->x = rx; v->y = ry; v->z = rz;
}

extern "C" void KartMovement_RotateByYaw(MovementInit *k, float angle) {
    Matrix44 transform;
    Matrix44 rotation;
    Identity(&transform);
    Identity(&rotation);
    k->yaw += angle;
    double radians = lbl_806D96F0 * angle;
    float c = (float)cos((float)radians);
    float s = (float)sin((float)radians);
    rotation.m[0][0] = c; rotation.m[2][0] = s;
    rotation.m[2][2] = c; rotation.m[0][2] = -s;
    Multiply(&rotation, &transform);
    transform = rotation;
    TransformVector(&k->v17c, &transform);
    TransformVector(&k->v1f8, &transform);
    Multiply(&k->orientation, &transform);
    Multiply(&k->matrixD8, &transform);
}
