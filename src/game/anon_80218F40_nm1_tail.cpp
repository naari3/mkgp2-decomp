#include "game/anon_80218F40_private.h"

static inline void RotateMapPoint(float angle, float *px, float *pz, float *rx, float *rz) {
    if (lbl_806DAF44 != angle) {
        float s = sin(angle);
        float c = cos(angle);
        *rx = *px * c - *pz * s;
        *rz = *px * s + *pz * c;
    } else {
        *rx = *px;
        *rz = *pz;
    }
}

static inline void WorldToMap(MinimapHud *h, float *ppx, float *ppz) {
    float &px = *ppx;
    float &pz = *ppz;
    const MapInfo *mi = &lbl_803C4C10[CupIndex()][h->variant];
    float ang = mi->rot * lbl_806DAF54;
    ang += h->scale;
    float rx;
    float rz;
    RotateMapPoint(ang, ppx, ppz, &rx, &rz);
    rx *= mi->sx;
    rz *= mi->sy;
    if (rx < -500.0f) {
        rx = -500.0f;
    } else if (rx > 500.0f) {
        rx = 500.0f;
    }
    if (rz < -500.0f) {
        rz = -500.0f;
    } else if (rz > 500.0f) {
        rz = 500.0f;
    }
    rx += mi->ox;
    rz += mi->oy;
    rx -= h->slideX;
    px = h->x + rx;
    pz = h->y + rz;
}

static inline void SetMarkerVisible(int sprite, int battleCup, bool sameTeam) {
    int visible = 0;
    if (battleCup || sameTeam) {
        visible = 1;
    }
    SpriteHandle_SetActiveFlag(sprite, visible);
}

void MinimapHud::UpdateMarkers() {
    float px = lbl_806DAF44;
    float pz = lbl_806DAF44;
    PathEntry *e;
    int me;
    int myTeam;
    int cup7;
    int pid;
    int orderOffset;
    int i;
    int slot;
    me = GetDisplayBufferIndex();
    if (g_cupId == 7) {
        cup7 = 1;
    } else {
        cup7 = 0;
    }
    myTeam = self->team;
    for (i = 7, orderOffset = 7 * sizeof(int); i >= 0; i--, orderOffset -= sizeof(int)) {
        if (*(int *)((char *)order + orderOffset) == -1) {
            continue;
        }
        e = PathManager_GetEntrySubStruct(path, i);
        slot = i + 3;
        pid = e->kart->playerId;
        if (pid >= 0 && pid <= 3) {
            if (pid == me) {
                slot = 2;
                int res = 0xBCC;
                if (g_gameMode == 2) {
                    res = pid + 0xBCD;
                }
                SpriteLayer_SetResource(sprites[2], res);
            } else {
                SpriteLayer_SetResource(sprites[slot], pid + 0xBCD);
                others[i] = 1;
            }
        } else if (pid == 4 && e->kart->hidden == 1) {
            SpriteHandle_SetActiveFlag(sprites[slot], 0);
            continue;
        } else {
            SpriteLayer_SetResource(sprites[slot], 0xBD1);
            fn_8011F744(sprites[slot], lbl_806DAF48, lbl_806DAF48);
            others[i] = 0;
        }
        float *m = KartDriver_GetKartRootMtx(e->kart);
        px = m[3];
        pz = m[11];
        WorldToMap(this, &px, &pz);
        fn_8011F804(sprites[slot], px, pz);
        SetMarkerVisible(sprites[slot], cup7, myTeam == e->kart->team);
        if (pid == me) {
            SpriteHandle_SetCornerAlpha(sprites[1], blink.p->Value());
            fn_8011F804(sprites[1], px, pz);
            SpriteHandle_SetActiveFlag(sprites[1], 1);
        }
    }
}

