#include "game/anon_80218F40_private.h"

static inline void WorldToMap(MinimapHud *h, float &px, float &pz) {
    const MapInfo *mi = &lbl_803C4C10[CupIndex()][h->variant];
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
    if (rx < lbl_806DAF58) {
        rx = lbl_806DAF58;
    } else if (rx > lbl_806DAF5C) {
        rx = lbl_806DAF5C;
    }
    if (rz < lbl_806DAF58) {
        rz = lbl_806DAF58;
    } else if (rz > lbl_806DAF5C) {
        rz = lbl_806DAF5C;
    }
    rx += mi->ox;
    rz += mi->oy;
    rx -= h->slideX;
    pz = h->y + rz;
    px = h->x + rx;
}

void MinimapHud::UpdateMarkers() {
    float px = lbl_806DAF44;
    float pz = lbl_806DAF44;
    int me = GetDisplayBufferIndex();
    int cup7 = g_cupId == 7;
    int myTeam = self->team;
    for (int i = 7; i >= 0; i--) {
        if (order[i] == -1) {
            continue;
        }
        PathEntry *e = PathManager_GetEntrySubStruct(path, i);
        int slot = i + 3;
        int pid = e->kart->playerId;
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
        WorldToMap(this, px, pz);
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

void MinimapHud::SetPath(PathManager *pm) {
    if (pm == 0) {
        return;
    }
    path = pm;
    PathEntry *e;
    int pid;
    int n = 0;
    int i;
    for (i = 0; i < 8; i++) {
        e = PathManager_GetEntrySubStruct(pm, i);
        if (e == 0 || e->id == -1) {
            continue;
        }
        int c = e->kart->character;
        if (c <= -1 || c >= 13) {
            continue;
        }
        pid = e->kart->playerId;
        if (pid == GetDisplayBufferIndex()) {
            self = e->kart;
        }
        order[n] = i;
        n++;
        if (n >= 8) {
            break;
        }
    }
}
