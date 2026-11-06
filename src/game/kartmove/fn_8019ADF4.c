#include "game/kartmove/speed_private.h"



extern const float lbl_806D9710, lbl_806D9714;

#pragma exceptions on
void fn_8019ADF4(KartForceState *__restrict k, Vec3 *__restrict input) {
    volatile Vec3 v;
    volatile Vec3 n;
    float len;
    float dot;
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
    KART_SPEED_ROOT(len);
    if (len <= lbl_806D96D0) return;
    nx = k->forward.x; ny = lbl_806D96D0; nz = k->forward.z;
    n.x = nx; n.y = ny; n.z = nz;
    {
        float xx = nx*nx;
        float yy = ny*ny;
        float zz = nz*nz;
        len = zz + (xx + yy);
    }
    KART_SPEED_ROOT(len);
    if (len <= lbl_806D96D0) {
        n.z = lbl_806D96D0;
        n.y = lbl_806D96D0;
        n.x = lbl_806D96D0;
    } else {
        float scale = lbl_806D96D4 / len;
        nx = n.x; ny = n.y; nz = n.z;
        nx *= scale; ny *= scale; nz *= scale;
        n.x = nx; n.y = ny; n.z = nz;
    }
    nx = n.x; vx = v.x; ny = n.y; vy = v.y; nz = n.z; vz = v.z;
    {
        float xx = nx*vx;
        float yy = ny*vy;
        float zz = nz*vz;
        dot = zz + (xx + yy);
    }
    vx = v.x; vz = v.z;
    vx += lbl_806D9710 * (nx * dot);
    vz += lbl_806D9710 * (nz * dot);
    v.x = vx; v.z = vz;
    k->impulse.x += vx;
    k->impulse.y += vy;
    k->impulse.z += vz;
    len = k->impulse.z*k->impulse.z + (k->impulse.x*k->impulse.x + k->impulse.y*k->impulse.y);
    KART_SPEED_ROOT(len);
    if (len > lbl_806D9714) {
        float scale = lbl_806D9714 / len;
        k->impulse.x *= scale;
        k->impulse.y *= scale;
        k->impulse.z *= scale;
    }
}
