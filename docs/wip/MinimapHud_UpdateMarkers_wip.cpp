#include "game/anon_80218F40_private.h"

static inline void WorldToMap(MinimapHud *h, float *ppx, float *ppz) {
    const MapInfo *mi = &lbl_803C4C10[CupIndex()][h->variant];
    float &px = *ppx;
    float &pz = *ppz;
    float ang = lbl_806DAF54 * mi->rot;
    ang += h->scale;
    float rx;
    float rz;
    if (lbl_806DAF44 != ang) {
        float s = sin(ang);
        float c = cos(ang);
        rx = px * c - pz * s;
        rz = px * s + pz * c;
    } else {
        rx = px;
        rz = pz;
    }
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

void MinimapHud::UpdateMarkers() {
    float px = lbl_806DAF44;
    float pz = lbl_806DAF44;
    int me = GetDisplayBufferIndex();
    int cup7 = g_cupId == 7 ? 1 : 0;
    int myTeam = self->team;
    for (int i = 7; i >= 0; i--) {
        if (order[i] == -1) {
            continue;
        }
        PathEntry *e = PathManager_GetEntrySubStruct(path, i);
        int pid = e->kart->playerId;
        int slot = i + 3;
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
        bool sameTeam = e->kart->team == myTeam;
        int vis = 0;
        if (cup7 || sameTeam) {
            vis = 1;
        }
        SpriteHandle_SetActiveFlag(sprites[slot], vis);
        if (pid == me) {
            SpriteHandle_SetCornerAlpha(sprites[1], blink.p->Value());
            fn_8011F804(sprites[1], px, pz);
            SpriteHandle_SetActiveFlag(sprites[1], 1);
        }
    }
}

