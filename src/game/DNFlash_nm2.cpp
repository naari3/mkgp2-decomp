#include "game/DNFlashSpawn_private.h"

static inline int SpawnArea(const float *xLimits, const float *zLimits, float x, float z) {
    int ix = -1;
    int iz = ix;
    for (int i = 0; i < 3; i++, xLimits++) {
        if (x < *xLimits) { ix = i; break; }
    }
    for (int i = 0; i < 3; i++, zLimits++) {
        if (z > *zLimits) { iz = i; break; }
    }
    if (ix < 0 || iz < 0) return -1;
    return ix + iz * 3;
}

static inline FlashPoint *FindSpawnPoint(clDNFlash *self, int *list) {
    FlashPoint *pt = 0;
    int start = rand() % 5;
    for (int tries = 0; tries < 5; tries++) {
        int k = rand() % self->counts[list[start]];
        int count = Min(self->counts[list[start]], lbl_806DB494);
        for (int j = 0; j < count; j++) {
            if (k >= self->counts[list[start]]) {
                k = 0;
            }
            if (self->points[list[start]][k].used != 1) {
                pt = &self->points[list[start]][k];
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
    return pt;
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
    FlashPoint *pt = FindSpawnPoint(this, list);
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
