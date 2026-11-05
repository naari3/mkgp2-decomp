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
    m->m[0][0] = lbl_806D96D4 - lbl_806D9708*(yy+zz);
    m->m[1][0] = lbl_806D9708*(xy-wz);
    m->m[2][0] = lbl_806D9708*(xz+wy);
    m->m[0][1] = lbl_806D9708*(xy+wz);
    m->m[1][1] = lbl_806D96D4 - lbl_806D9708*(xx+zz);
    m->m[2][1] = lbl_806D9708*(yz-wx);
    m->m[0][2] = lbl_806D9708*(xz-wy);
    m->m[1][2] = lbl_806D9708*(yz+wx);
    m->m[2][2] = lbl_806D96D4 - lbl_806D9708*(xx+yy);
}

static inline void Multiply(Matrix44 *a, const Matrix44 *b) {
    float out[16];
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++, index++) {
            out[index] = ((a->m[i][0]*b->m[0][j] + a->m[i][1]*b->m[1][j])
                        + a->m[i][2]*b->m[2][j]) + a->m[i][3]*b->m[3][j];
        }
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
    float py = k->orientation.m[3][1];
    float pz = k->orientation.m[3][2];
    k->orientation.m[3][0] = lbl_806D96D0;
    k->orientation.m[3][1] = lbl_806D96D0;
    k->orientation.m[3][2] = lbl_806D96D0;
    QuatMatrix(&rotation, &q);
    Multiply(&k->orientation, &rotation);
    k->orientation.m[3][0] = px;
    k->orientation.m[3][1] = lbl_806D970C + py;
    k->orientation.m[3][2] = pz;
}
