#include "game/kartmove/carobject_private.h"
#include "game/kartmove/speed_private.h"

extern const float lbl_806D96D0, lbl_806D96D4;
extern const float lbl_806D9704, lbl_806D9708, lbl_806D970C;
extern "C" double sin(double);
extern "C" double cos(double);

static inline void Identity(Matrix44 *a) {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) a->m[i][j] = 0.0f;
    a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = 1.0f;
}

static inline void AccumulateProduct(float &value, float right, float left) {
    value += left * right;
}

static inline void Multiply(Matrix44 *a, const Matrix44 *b) {
    Matrix44 product;
    float *out = (float *)product.m;
    int j;
    int index;
    int i;
    float value;
    index = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            value = a->m[i][0]*b->m[0][j];
            AccumulateProduct(value, b->m[1][j], a->m[i][1]);
            AccumulateProduct(value, b->m[2][j], a->m[i][2]);
            AccumulateProduct(value, b->m[3][j], a->m[i][3]);
            out[index+j] = value;
        }
        index += 4;
    }
    for (int i = 0; i < 16; i++) ((float *)a)[i] = out[i];
}

extern const double lbl_806D96F0;

static inline void TransformVector(InitVec *v, const Matrix44 *m) {
    float x = v->x, y = v->y, z = v->z;
    v->x = m->m[3][0] + (z*m->m[2][0] + (m->m[0][0]*x + y*m->m[1][0]));
    v->y = m->m[3][1] + (z*m->m[2][1] + (m->m[0][1]*x + y*m->m[1][1]));
    v->z = m->m[3][2] + (z*m->m[2][2] + (x*m->m[0][2] + y*m->m[1][2]));
}

static inline void RotateYaw(Matrix44 *transform, float angle) {
    Matrix44 rotation;
    Identity(&rotation);
    float c, s;
    double radians = lbl_806D96F0 * angle;
    c = (float)cos((float)radians);
    s = (float)sin((float)radians);
    rotation.m[0][0] = c; rotation.m[2][0] = s;
    rotation.m[2][2] = c; rotation.m[0][2] = -s;
    Multiply(&rotation, transform);
    *transform = rotation;
}

extern "C" void KartMovement_RotateByYaw(MovementInit *k, float angle) {
    Matrix44 transform;
    k->yaw += angle;
    Identity(&transform);
    RotateYaw(&transform, angle);
    TransformVector(&k->v17c, &transform);
    TransformVector(&k->v1f8, &transform);
    Multiply(&k->orientation, &transform);
    Multiply(&k->matrixD8, &transform);
}
