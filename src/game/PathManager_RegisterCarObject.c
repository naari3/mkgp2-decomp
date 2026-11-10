/* PathManager_RegisterCarObject @ 0x8003CF44: claim a path participant slot
 * (first free one when slot == -1) for a car and reset its progress.
 * The free-slot search is a plain loop; mwcc fully unrolls it. */

#include "game/types/PathEntry.h"

typedef struct PathMgr {
    unsigned char pad0[0x10];
    PathEntry entries[8];
    int field4D0;
} PathMgr;

extern const float lbl_806D24E8;
int PathManager_HasPathLoaded(PathMgr *mgr);
int Path_GetTotalCount(PathMgr *mgr);
int Waypoint_FindBestAhead(PathMgr *path, float x, float y, float z,
                           int start, int from, int to, float *outDist);
void KartItem_SetField2ac(void *kart, int slot);

#pragma exceptions on

int PathManager_RegisterCarObject(PathMgr *self, float *px, float *py, float *pz, void *obj,
                                  void *kart, int slot)
{
    PathEntry *e;

    if (PathManager_HasPathLoaded(self) == 0) {
        return -1;
    }
    if (slot == -1) {
        int i;
        for (i = 0; i < 8; i++) {
            if (self->entries[i].node < 0) {
                slot = i;
                break;
            }
        }
    }
    if (slot == -1) {
        return -1;
    }
    e = &self->entries[slot];
    self->field4D0 = 0;
    e->node = Waypoint_FindBestAhead(self, *px, *py, *pz, 0, 0, 3, &e->dist);
    e->field8 = 0;
    e->px = px;
    e->py = py;
    e->pz = pz;
    e->pos[0] = *px;
    e->pos[1] = *py;
    e->pos[2] = *pz;
    e->segment = 0;
    e->field74 = 0;
    e->field94 = 0;
    e->field44 = 0;
    e->field46 = 1;
    e->field48 = 0;
    e->total = Path_GetTotalCount(self);
    e->field50 = -1;
    e->field58 = -1;
    e->field5C = -1;
    e->field60 = 1;
    e->field40 = lbl_806D24E8;
    e->field45 = 0;
    e->field4C = lbl_806D24E8;
    e->field78 = 0;
    e->field7C = 0;
    e->field8C = obj;
    e->kart = kart;
    e->hist[0] = lbl_806D24E8;
    e->hist[1] = lbl_806D24E8;
    e->hist[2] = lbl_806D24E8;
    e->hist[3] = lbl_806D24E8;
    e->hist[4] = lbl_806D24E8;
    e->hist[5] = lbl_806D24E8;
    e->hist[6] = lbl_806D24E8;
    e->hist[7] = lbl_806D24E8;
    e->hist[8] = lbl_806D24E8;
    e->hist[9] = lbl_806D24E8;
    if (kart != 0) {
        KartItem_SetField2ac(kart, slot);
    }
    return slot;
}

#pragma exceptions reset
