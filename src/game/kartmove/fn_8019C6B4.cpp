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
static inline void QSet(MovementQuat *q, float x, float y, float z, float w) { q->x = x; q->y = y; q->z = z; q->w = w; }
extern "C" float LUT_Sine(float);
extern "C" float LUT_Cosine(float);
extern "C" void Mtx34_Orthonormalize(float *);

/* The angle test, the quaternion and the matrix build are ONE inline in the
 * original: `angle` and the q products are coloured among the matrix
 * temporaries (regalloc_patterns 88). Inline locals are created in reverse
 * declaration order. */
/* fakematch (inline limit): the original presumably built with a larger
 * inline size limit; without this pragma Turn is not inlined. */
#pragma inline_max_size(100000)
static inline void Turn(MovementInit *k, InitVec &target, MovementQuat &q, float a) {
    float half, scale, sw; float w, z, angle, y, x;
    float xx, yy, zz, xy, xz, yz, wx, wy, wz;
    float qz, qy, qx;
    angle = a;
    if (lbl_806D96D0 != angle) {
        half = lbl_806D9704 * angle;
        scale = LUT_Cosine(half) / angle;
        sw = LUT_Sine(half);
        qz = target.z*scale;
        qy = target.y*scale;
        qx = target.x*scale;
        QSet(&q, qx, qy, qz, sw);
        Matrix44 rotation;
        Identity(&rotation);
        x = QuatX(&q);
        y = QuatY(&q);
        z = QuatZ(&q);
        w = QuatW(&q);
        xx = x*x;
        yy = y*y;
        zz = z*z;
        xy = x*y;
        xz = x*z;
        yz = y*z;
        wx = w*x;
        wy = w*y;
        wz = w*z;
        rotation.m[0][0] = 1.0f - 2.0f*(yy+zz);
        rotation.m[1][0] = 2.0f*(xy-wz);
        rotation.m[2][0] = 2.0f*(xz+wy);
        rotation.m[0][1] = 2.0f*(xy+wz);
        rotation.m[1][1] = 1.0f - 2.0f*(xx+zz);
        rotation.m[2][1] = 2.0f*(yz-wx);
        rotation.m[0][2] = 2.0f*(xz-wy);
        rotation.m[1][2] = 2.0f*(yz+wx);
        rotation.m[2][2] = 1.0f - 2.0f*(xx+yy);
        Multiply(&k->orientation, &rotation);
        for (int i = 12; i > 0; i--) {}
        Mtx34_Orthonormalize(&k->orientation.m[0][0]);
    }
}

extern "C" void fn_8019C6B4(MovementInit *k) {
    float dz = k->orientation.m[2][2];
    float dx = k->orientation.m[2][0];
    InitVec direction(dx, lbl_806D96D0, dz);
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
    float y, x, z;
    x = direction.y*target.z - direction.z*target.y;
    y = direction.z*target.x - direction.x*target.z;
    z = direction.x*target.y - direction.y*target.x;
    target.x = x; target.y = y; target.z = z;
    Turn(k, target, q, z + (x+y));
    k->orientation.m[3][0] = k->pos.x;
    k->orientation.m[3][1] = k->pos.y;
    k->orientation.m[3][2] = k->pos.z;
}
