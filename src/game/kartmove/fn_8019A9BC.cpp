#include "game/kartmove/rotation_private.h"

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
    float wz = q->w*q->z;
    float xz = q->x*q->z;
    float wy = q->w*q->y;
    float yz = q->y*q->z;
    float wx = q->w*q->x;
    SetRotation(m, lbl_806D96D4 - lbl_806D9708*(yy+zz),
                lbl_806D9708*(xy-wz), lbl_806D9708*(xz+wy),
                lbl_806D9708*(xy+wz), lbl_806D96D4 - lbl_806D9708*(xx+zz),
                lbl_806D9708*(yz-wx), lbl_806D9708*(xz-wy),
                lbl_806D9708*(yz+wx), lbl_806D96D4 - lbl_806D9708*(xx+yy));
}

static inline void Multiply(Matrix44 *a, const Matrix44 *b) {
    float out[16];
    float value;
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            value = a->m[i][0]*b->m[0][j];
            value += a->m[i][1]*b->m[1][j];
            value += a->m[i][2]*b->m[2][j];
            value += a->m[i][3]*b->m[3][j];
            out[index+j] = value;
        }
        index += 4;
    }
    for (int i = 0; i < 16; i++) ((float *)a)[i] = out[i];
}

extern "C" void fn_8019A9BC(MovementInit *k) {
    Matrix44 rotation;
    MovementQuat q;
    Identity(&rotation);
    float x = k->orientation.m[0][0];
    float y = k->orientation.m[0][1];
    float z = k->orientation.m[0][2];
    float s = (float)sin(lbl_806D9704);
    q.x = x*s; q.y = y*s; q.z = z*s;
    q.w = (float)cos(lbl_806D9704);
    float px = k->orientation.m[3][0];
    float py = lbl_806D970C + k->orientation.m[3][1];
    float pz = k->orientation.m[3][2];
    k->orientation.m[3][0] = lbl_806D96D0;
    k->orientation.m[3][1] = lbl_806D96D0;
    k->orientation.m[3][2] = lbl_806D96D0;
    QuatMatrix(&rotation, &q);
    Multiply(&k->orientation, &rotation);
    k->orientation.m[3][0] = px;
    k->orientation.m[3][1] = py;
    k->orientation.m[3][2] = pz;
}
