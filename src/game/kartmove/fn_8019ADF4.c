#include "game/kartmove/speed_private.h"

extern const float lbl_806D9710, lbl_806D9714;

static inline void ForceScale(volatile Vec3 *v, float scale) {
    float x = v->x;
    float y = v->y;
    float z = v->z;
    x *= scale; y *= scale; z *= scale;
    v->x = x; v->y = y; v->z = z;
}

static inline void ApplyHorizontalForce(KartForceState *k, volatile Vec3 *v, const volatile Vec3 *n) {
    float vx, vy, vz;
    float nx, ny, nz;
    nx = n->x; vx = v->x; ny = n->y; vy = v->y; nz = n->z; vz = v->z;
    {
        float xx = nx*vx;
        float yy = ny*vy;
        float zz = nz*vz;
        vz = zz + (xx + yy);
    }
    nx *= vz; nz *= vz;
    vx = v->x; vz = v->z;
    vx += lbl_806D9710 * nx;
    vz += lbl_806D9710 * nz;
    v->x = vx; v->z = vz;
    k->impulse.x += vx;
    k->impulse.y += vy;
    k->impulse.z += vz;
}

/* Keep each Newton result rounded through its own single-precision slot. */
#define FORCE_ROOT(x, y) do { \
    if ((x) > lbl_806D96D0) { \
        double g = __frsqrte(x); \
        g = lbl_806D96E0 * g * (lbl_806D96E8 - (x) * (g * g)); \
        g = lbl_806D96E0 * g * (lbl_806D96E8 - (x) * (g * g)); \
        g = lbl_806D96E0 * g * (lbl_806D96E8 - (x) * (g * g)); \
        y = (float)((x) * g); \
        (x) = y; \
    } \
} while (0)

#pragma exceptions on
void fn_8019ADF4(KartForceState *k, Vec3 *__restrict input) {
    Vec3 v;
    Vec3 n;
    float len;
    volatile float initialRoot, impulseRoot, normalRoot;
    float vx, vy, vz;
    float nx, ny, nz;
    vx = input->x; vy = input->y; vz = input->z;
    v.x = vx; v.y = vy; v.z = vz;
    vy = lbl_806D96D0;
    v.y = vy;
    /* Preserve the separate products used by the vector length operation. */
    {
        float xx = vx*vx;
        float yy = vy*vy;
        float zz = vz*vz;
        len = zz + (xx + yy);
    }
    FORCE_ROOT(len, initialRoot);
    if (len <= lbl_806D96D0) return;
    nx = k->forward.x; ny = lbl_806D96D0; nz = k->forward.z;
    n.x = nx; n.y = ny; n.z = nz;
    {
        float xx = nx*nx;
        float yy = ny*ny;
        float zz = nz*nz;
        len = zz + (xx + yy);
    }
    FORCE_ROOT(len, normalRoot);
    if (len <= lbl_806D96D0) {
        n.z = lbl_806D96D0;
        n.y = lbl_806D96D0;
        n.x = lbl_806D96D0;
    } else {
        float scale = lbl_806D96D4 / len;
        ForceScale(&n, scale);
    }
    ApplyHorizontalForce(k, &v, &n);
    len = k->impulse.z*k->impulse.z + (k->impulse.x*k->impulse.x + k->impulse.y*k->impulse.y);
    FORCE_ROOT(len, impulseRoot);
    if (len > lbl_806D9714) {
        float scale = lbl_806D9714 / len;
        k->impulse.x *= scale;
        k->impulse.y *= scale;
        k->impulse.z *= scale;
    }
}
