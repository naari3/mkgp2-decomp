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
    float dx = lbl_803D07BC[t].b.x - lbl_803D07BC[t].a.x;
    nz = lbl_803D07BC[t].b.z - lbl_803D07BC[t].a.z;
    nx = -dx;
    nx *= KartMovement_GetVelocityPtr(k)[2];
    if (nz * KartMovement_GetVelocityPtr(k)[0] + nx < lbl_806DB490) {
        return 0;
    }
    inside = 1;
    return prev != 1;
}
#pragma dont_inline reset

static inline int SpawnArea(const float *xLimits, const float *zLimits, float x, float z) {
    int ix = -1;
    int iz = ix;
    for (int i = 0; i < 3; i++) {
        if (x < xLimits[i]) { ix = i; break; }
    }
    for (int i = 0; i < 3; i++) {
        if (z > zLimits[i]) { iz = i; break; }
    }
    if (ix < 0 || iz < 0) return -1;
    return ix + iz * 3;
}

void clDNFlash::Spawn() {
    const DNFlashSpawnTables &tables = *(const DNFlashSpawnTables *)lbl_803D0390;
    int list[5];

    if (g_playerRenderObj == 0) {
        return;
    }
    const float *m = KartDriver_GetKartRootMtx(g_playerRenderObj);
    int area = SpawnArea(tables.xLimits, tables.zLimits, m[3], m[11]);
    if (area < 0) {
        return;
    }
    int col = area % 3;
    int n = 0;
    list[n++] = area - col;
    list[n++] = list[0] + 1;
    list[n++] = list[1] + 1;
    if (area != col) {
        list[n++] = col;
    }
    if (area != col + 3) {
        list[n++] = col + 3;
    }
    if (area != col + 6) {
        list[n++] = col + 6;
    }
    FlashPoint *pt = 0;
    int start = rand() % 5;
    for (int tries = 0; tries < 5; tries++) {
        int k = rand() % counts[list[start]];
        for (int j = Min(counts[list[start]], lbl_806DB494); j > 0; j--) {
            if (k >= counts[list[start]]) {
                k = 0;
            }
            if (points[list[start]][k].used != 1) {
                pt = &points[list[start]][k];
                break;
            }
            k++;
        }
        if (pt) {
            break;
        }
        if (++start >= 5) {
            start = 0;
        }
    }
    if (pt == 0) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        if (free[i]) {
            FlashPart *p = free[i];
            pt->used = 1;
            p->owner = pt;
            p->active = 1;
            p->life = 8;
            p->scale = tables.scales[rand() % 3];
            p->dscale = lbl_806DB498;
            p->alpha = lbl_806DB49C;
            free[i] = 0;
            return;
        }
    }
}
