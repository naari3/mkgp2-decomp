/* WIP 2026-11-07 (thread B): fn_8019ADF4, 28 diff lines left (orig source 86). Gains: named volatile sqrt results declared r1,r3,r2 (stack 16/8/12), normalize as nx = n.x * scale, v.x/v.z update as vx = v.x + c*(nx*dot), dot loads in program order with nx/vy/nz kept. Left: entry block schedules stwu + the v.y store differently (target stores x,y,z in order); dot sum regalloc (zz in f3 vs f9). Decl-order sweep (3500), GC 1.2.5n..2.7, load/store/product permutations: no further gain. */
#include "game/kartmove/speed_private.h"



extern const float lbl_806D9710, lbl_806D9714;

#define ROOT(x, y) do { \
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
void fn_8019ADF4(KartForceState *__restrict k, Vec3 *__restrict input) {
    volatile Vec3 v;
    volatile Vec3 n;
    float len;
    float dot;
    float vx, vy, vz;
    float nx, ny, nz;
    volatile float r1, r3, r2;
    vx = input->x; vz = input->z; vy = input->y;
    v.y = vy; v.x = vx; v.z = vz;
    vy = lbl_806D96D0;
    v.y = vy;
    /* Preserve the separate products used by the vector length operation. */
    {
        float xx = vx*vx;
        float yy = vy*vy;
        float zz = vz*vz;
        len = zz + (xx + yy);
    }
    ROOT(len, r1);
    if (len <= lbl_806D96D0) return;
    nx = k->forward.x; ny = lbl_806D96D0; nz = k->forward.z;
    n.x = nx; n.y = ny; n.z = nz;
    {
        float xx = nx*nx;
        float yy = ny*ny;
        float zz = nz*nz;
        len = zz + (xx + yy);
    }
    ROOT(len, r2);
    if (len <= lbl_806D96D0) {
        n.z = lbl_806D96D0;
        n.y = lbl_806D96D0;
        n.x = lbl_806D96D0;
    } else {
        float scale = lbl_806D96D4 / len;
        nx = n.x * scale; ny = n.y * scale; nz = n.z * scale;
        n.x = nx; n.y = ny; n.z = nz;
    }
    {
        float xx = (nx = n.x) * v.x;
        float yy = n.y * (vy = v.y);
        float zz = (nz = n.z) * v.z;
        dot = zz + (xx + yy);
    }
    vx = v.x + lbl_806D9710 * (nx * dot);
    vz = v.z + lbl_806D9710 * (nz * dot);
    v.x = vx; v.z = vz;
    k->impulse.x += vx;
    k->impulse.y += vy;
    k->impulse.z += vz;
    len = k->impulse.z*k->impulse.z + (k->impulse.x*k->impulse.x + k->impulse.y*k->impulse.y);
    ROOT(len, r3);
    if (len > lbl_806D9714) {
        float scale = lbl_806D9714 / len;
        k->impulse.x *= scale;
        k->impulse.y *= scale;
        k->impulse.z *= scale;
    }
}
