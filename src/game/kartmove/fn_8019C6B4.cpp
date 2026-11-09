#include "game/kartmove/rotation_private.h"
#include "game/kartmove/speed_private.h"

extern const float lbl_806D96D0, lbl_806D96D4;
extern const float lbl_806D9704, lbl_806D9708, lbl_806D970C;
extern "C" double sin(double);
extern "C" double cos(double);



static inline void Identity(Matrix44 *a) {
    a->m[3][3] = a->m[2][2] = a->m[1][1] = a->m[0][0] = 0.0f;
    a->m[1][0] = a->m[0][3] = a->m[0][2] = a->m[0][1] = 0.0f;
    a->m[2][1] = a->m[2][0] = a->m[1][3] = a->m[1][2] = 0.0f;
    a->m[3][2] = a->m[3][1] = a->m[3][0] = a->m[2][3] = 0.0f;
    a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = 1.0f;
}

static inline double QuatX(const MovementQuat *q) { return q->x; }
static inline double QuatY(const MovementQuat *q) { return q->y; }
static inline double QuatZ(const MovementQuat *q) { return q->z; }
static inline double QuatW(const MovementQuat *q) { return q->w; }

static inline void QuatMatrix(Matrix44 *m, MovementQuat *q) {
    float w, z, y, x;
    x = QuatX(q);
    y = QuatY(q);
    z = QuatZ(q);
    w = QuatW(q);
    float xx = x*x;
    float yy = y*y;
    float zz = z*z;
    float xy = x*y;
    float wz = w*z;
    float xz = x*z;
    float wy = w*y;
    float yz = y*z;
    float wx = w*x;
    m->m[0][0] = 1.0f - 2.0f*(yy+zz);
    m->m[1][0] = 2.0f*(xy-wz);
    m->m[2][0] = 2.0f*(xz+wy);
    m->m[0][1] = 2.0f*(xy+wz);
    m->m[1][1] = 1.0f - 2.0f*(xx+zz);
    m->m[2][1] = 2.0f*(yz-wx);
    m->m[0][2] = 2.0f*(xz-wy);
    m->m[1][2] = 2.0f*(yz+wx);
    m->m[2][2] = 1.0f - 2.0f*(xx+yy);
}

static inline void Multiply(Matrix44 *a, const Matrix44 *b) {
    float out[16];
    float sum;
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float a0 = a->m[i][0], b0 = b->m[0][j];
            float a1 = a->m[i][1], b1 = b->m[1][j];
            float a2 = a->m[i][2], b2 = b->m[2][j];
            float a3 = a->m[i][3], b3 = b->m[3][j];
            sum = a0*b0;
            sum = a1*b1 + sum;
            sum = a2*b2 + sum;
            sum = a3*b3 + sum;
            out[index+j] = sum;
        }
        index += 4;
    }
    for (int i = 0; i < 16; i++) ((float *)a)[i] = out[i];
}

extern const double lbl_806D96F0;
extern "C" float LUT_Sine(float);
extern "C" float LUT_Cosine(float);
extern "C" void Mtx34_Orthonormalize(float *);

extern "C" void fn_8019C6B4(MovementInit *k) {
    InitVec direction(k->orientation.m[2][0], lbl_806D96D0, k->orientation.m[2][2]);
    float len = direction.z*direction.z + (direction.x*direction.x + direction.y*direction.y);
    KART_SPEED_ROOT(len);
    if (len <= lbl_806D96D0) {
        direction.z = lbl_806D96D0; direction.y = lbl_806D96D0; direction.x = lbl_806D96D0;
    } else {
        float scale = lbl_806D96D4 / len;
        direction.x *= scale; direction.y *= scale; direction.z *= scale;
    }
    float s = LUT_Sine((float)(lbl_806D96F0 * k->yaw));
    InitVec target(LUT_Cosine((float)(lbl_806D96F0 * k->yaw)), lbl_806D96D0, s);
    MovementQuat q;
    float x = direction.y*target.z - direction.z*target.y;
    float y = direction.z*target.x - direction.x*target.z;
    float z = direction.x*target.y - direction.y*target.x;
    target.x = x; target.y = y; target.z = z;
    float angle = z + (x+y);
    if (lbl_806D96D0 != angle) {
        float half = lbl_806D9704 * angle;
        float scale = LUT_Cosine(half) / angle;
        float w = LUT_Sine(half);
        q.z = target.z*scale; q.y = target.y*scale; q.x = target.x*scale; q.w = w;
        Matrix44 rotation;
        Identity(&rotation);
        QuatMatrix(&rotation, &q);
        Multiply(&k->orientation, &rotation);
        for (int i = 0; i < 12; i++) {}
        Mtx34_Orthonormalize(&k->orientation.m[0][0]);
    }
    k->orientation.m[3][0] = k->pos.x;
    k->orientation.m[3][1] = k->pos.y;
    k->orientation.m[3][2] = k->pos.z;
}
