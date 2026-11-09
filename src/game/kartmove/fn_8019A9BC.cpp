#include "game/kartmove/carobject_private.h"
struct MovementQuat {
    float x, y, z, w;
    MovementQuat() { x = y = z = w = 0.0f; }
    ~MovementQuat() {}
};

extern const float lbl_806D9704;
extern "C" double sin(double);
extern "C" double cos(double);



static inline void Identity(Matrix44 *a) {
    a->m[3][3] = a->m[2][2] = a->m[1][1] = a->m[0][0] = 0.0f;
    a->m[1][0] = a->m[0][3] = a->m[0][2] = a->m[0][1] = 0.0f;
    a->m[2][1] = a->m[2][0] = a->m[1][3] = a->m[1][2] = 0.0f;
    a->m[3][2] = a->m[3][1] = a->m[3][0] = a->m[2][3] = 0.0f;
    a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = 1.0f;
}

static inline void SetRotation(Matrix44 *m, float m00, float m10, float m20,
                               float m01, float m11, float m21,
                               float m02, float m12, float m22) {
    m->m[0][0] = m00; m->m[1][0] = m10; m->m[2][0] = m20;
    m->m[0][1] = m01; m->m[1][1] = m11; m->m[2][1] = m21;
    m->m[0][2] = m02; m->m[1][2] = m12; m->m[2][2] = m22;
}

static inline void QuatMatrix(Matrix44 *m, MovementQuat *q) {
    float xx = q->x*q->x;
    float yy = q->y*q->y;
    float zz = q->z*q->z;
    float xy = q->x*q->y;
    float xz = q->x*q->z;
    float yz = q->y*q->z;
    float wx = q->w*q->x;
    float wy = q->w*q->y;
    float wz = q->w*q->z;
    SetRotation(m, 1.0f - 2.0f*(yy+zz),
                2.0f*(xy-wz), 2.0f*(xz+wy),
                2.0f*(xy+wz), 1.0f - 2.0f*(xx+zz),
                2.0f*(yz-wx), 2.0f*(xz-wy),
                2.0f*(yz+wx), 1.0f - 2.0f*(xx+yy));
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

static inline void SetAxisAngle(MovementQuat *q, const float *axis) {
    float z = axis[2];
    float y = axis[1];
    float x = axis[0];
    float s = (float)sin(lbl_806D9704);
    q->x = x*s; q->y = y*s; q->z = z*s;
}

extern "C" void fn_8019A9BC(MovementInit *k) {
    Matrix44 rotation;
    MovementQuat q;
    Identity(&rotation);
    SetAxisAngle(&q, k->orientation.m[0]);
    float c = (float)cos(lbl_806D9704);
    q.w = c;
    QuatMatrix(&rotation, &q);
    Vec3 position;
    position.x = k->orientation.m[3][0];
    position.y = 50.0f + k->orientation.m[3][1];
    position.z = k->orientation.m[3][2];
    k->orientation.m[3][0] = 0.0f;
    k->orientation.m[3][1] = 0.0f;
    k->orientation.m[3][2] = 0.0f;
    Multiply(&k->orientation, &rotation);
    k->orientation.m[3][0] = position.x;
    k->orientation.m[3][1] = position.y;
    k->orientation.m[3][2] = position.z;
}
