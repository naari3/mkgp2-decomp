#include "game/Collision.h"

/* Sphere/box overlap tests (0x80207E3C..0x80208E30). */

extern "C" {

float CollisionTest_CalcPenetration(void *self, CollisionObject *a, CollisionObject *b);
float fn_802083C4(void *self, CollisionObject *a, CollisionObject *b);
void fn_802086AC(void *self, CollisionObject *a, CollisionObject *b);
void fn_80208E2C(void);
}

static inline float Col_sqrtf(float x) {
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

static inline void Col_Normalize(Vec *v) {
    float len = v->x * v->x + v->y * v->y + v->z * v->z;
    if (len > 0.0f) {
        volatile float y;
        double guess = __frsqrte(len);
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        y = (float)(len * guess);
        len = y;
    }
    if (0.0f != len) {
        float inv = 1.0f / len;
        v->x *= inv;
        v->y *= inv;
        v->z *= inv;
    }
}

/* Box support offset along dir, with ext added to the half extents. */
static inline void Col_BoxSupport(CollisionObject *o, Vec *ext, Vec *dir, Vec *out, Vec &row) {
    Mtx s;
    Mtx r;
    Mtx t;
    PSVECAdd(ext, &o->half, ext);
    PSMTXIdentity(s);
    s[0][0] = ext->x;
    s[1][1] = ext->y;
    s[2][2] = ext->z;
    PSMTXIdentity(r);
    PSMTXRotRad(t, 'z', -o->rot.z);
    PSMTXConcat(r, t, r);
    PSMTXRotRad(t, 'x', -o->rot.x);
    PSMTXConcat(r, t, r);
    PSMTXRotRad(t, 'y', -o->rot.y);
    PSMTXConcat(r, t, r);
    PSMTXConcat(s, r, s);
    row.x = s[0][0];
    row.y = s[0][1];
    row.z = s[0][2];
    out->x = Vec3_Dot(&row, dir);
    row.x = s[1][0];
    row.y = s[1][1];
    row.z = s[1][2];
    out->y = Vec3_Dot(&row, dir);
    row.x = s[2][0];
    row.y = s[2][1];
    row.z = s[2][2];
    out->z = Vec3_Dot(&row, dir);
}

static inline void Col_Support(CollisionObject *o, Vec *dir, Vec *out) {
    Vec ext;
    Vec row;
    if (o->type != 1) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
    } else {
        ext.x = 0.0f;
        ext.y = 0.0f;
        ext.z = 0.0f;
        Col_BoxSupport(o, &ext, dir, out, row);
    }
}

float CollisionTest_CalcPenetration(void *self, CollisionObject *a, CollisionObject *b) {
    float dist = Col_sqrtf(PSVECSquareDistance(&a->pos, &b->pos));
    Vec dir;
    Vec sup;
    Vec3_Subtract(&b->pos, &a->pos, &dir);
    Col_Normalize(&dir);
    Col_Support(a, &dir, &sup);
    float ra = Vec3_Magnitude(&sup);
    Vec3_Subtract(&a->pos, &b->pos, &dir);
    Col_Normalize(&dir);
    Col_Support(b, &dir, &sup);
    float sum = ra + Vec3_Magnitude(&sup);
    sum = sum * sum;
    float d = Col_sqrtf(sum) - dist;
    if (d < 0.0f) {
        d = -1.0f;
    }
    return d;
}

float fn_802083C4(void *self, CollisionObject *a, CollisionObject *b) {
    float dist = Col_sqrtf(PSVECSquareDistance(&a->pos, &b->pos));
    Vec dir;
    Vec sup;
    Vec3_Subtract(&a->pos, &b->pos, &dir);
    Col_Normalize(&dir);
    float r = a->radius;
    if (b->type != 1) {
        sup.x = 0.0f;
        sup.y = 0.0f;
        sup.z = 0.0f;
    } else {
        Vec row;
        Vec ext;
        ext.x = r;
        ext.y = r;
        ext.z = r;
        Col_BoxSupport(b, &ext, &dir, &sup, row);
    }
    float d = Vec3_Magnitude(&sup) - dist;
    if (d < 0.0f) {
        d = -1.0f;
    }
    return d;
}

static inline void Col_GetSupport(CollisionObject *o, Vec *dir, Vec *out) {
    switch (o->type) {
    case 0:
        PSVECScale(dir, out, o->radius);
        break;
    case 1:
        Col_Support(o, dir, out);
        break;
    default:
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        break;
    }
}

/* Writes o's contact against other, pushing out from `from` toward `to`. */
static inline float Col_SphereSphere(CollisionObject *a, CollisionObject *b) {
    float dsq = PSVECSquareDistance(&a->pos, &b->pos);
    float rs = a->radius + b->radius;
    float d = Col_sqrtf(rs * rs) - Col_sqrtf(dsq);
    if (d < 0.0f) {
        return -1.0f;
    }
    return d;
}

#define COL_RESOLVE(o, oth, from, to, dep)              \
    do {                                                \
        Vec3_Subtract(from, to, &dir);                  \
        Col_Normalize(&dir);                            \
        Col_GetSupport(o, &dir, &sup);                  \
        PSVECAdd(&sup, &(o)->pos, &sup);                \
        (o)->hit = 1;                                   \
        (o)->depth = dep;                               \
        (o)->normal = dir;                              \
        (o)->contact = sup;                             \
        (o)->other = oth;                               \
    } while (0)

void fn_802086AC(void *self, CollisionObject *a, CollisionObject *b) {
    if (a == 0 || b == 0) {
        return;
    }
    if (a == b) {
        return;
    }
    if (a->hit && b->hit) {
        return;
    }
    float depth = 0.0f;
    switch (a->type) {
    case 0:
        if (b->type == 0) {
            depth = Col_SphereSphere(a, b);
        } else if (b->type == 1) {
            depth = fn_802083C4(self, a, b);
        }
        break;
    case 1:
        if (b->type == 0) {
            depth = fn_802083C4(self, b, a);
        } else if (b->type == 1) {
            depth = CollisionTest_CalcPenetration(self, a, b);
        }
        break;
    }
    if (depth >= 0.0f) {
        Vec dir;
        Vec sup;
        Vec *pa = &a->pos;
        Vec *pb = &b->pos;
        if (!a->hit) {
            COL_RESOLVE(a, b, pa, pb, depth);
        }
        if (!b->hit) {
            COL_RESOLVE(b, a, pb, pa, depth);
        }
    }
}

void fn_80208E2C(void) {}
