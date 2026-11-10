#include "game/DNFlashSpawn_private.h"

#pragma dont_inline on
unsigned char clDNFlash::Check() {
    if (burst > 0) {
        return 0;
    }
    KartRender *k;
    if ((k = g_playerRenderObj) == 0) {
        return 0;
    }
    const float *m = KartDriver_GetKartRootMtx(k);
    int t = 0;
    float x = m[3];
    float z = m[11];
    if (g_longRoundFlag == 1) {
        t = 2;
    }
    if (g_reverseRoundFlag == 1) {
        t++;
    }
    unsigned char prev = inside;
    inside = 0;
    float mnx = lbl_804EE008[t].x;
    if (x < mnx) {
        return 0;
    }
    if (x > lbl_804EE038[t].x) {
        return 0;
    }
    if (z < lbl_804EE008[t].z) {
        return 0;
    }
    if (z > lbl_804EE038[t].z) {
        return 0;
    }
    float nx, nz;
    float dx = DNFlash_tail_rodata_803D07BC[t].b.x - DNFlash_tail_rodata_803D07BC[t].a.x;
    nz = DNFlash_tail_rodata_803D07BC[t].b.z - DNFlash_tail_rodata_803D07BC[t].a.z;
    nx = -dx;
    nx *= KartMovement_GetVelocityPtr(k)[2];
    if (nz * KartMovement_GetVelocityPtr(k)[0] + nx < lbl_806DB490) {
        return 0;
    }
    inside = 1;
    return prev != 1;
}
#pragma dont_inline reset
