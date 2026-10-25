/* PathManager_RegisterCarObject @ 0x8003CF44: claim a path participant slot
 * (first free one when slot == -1) for a car and reset its progress.
 *
 * NonMatching: register numbering only. The target gives the entry pointer
 * r31 and the parameters r24..r30; here the entry lands in r24. */

typedef struct PathEntry {
    int field0;
    int node;
    int field8;
    float *px;
    float *py;
    float *pz;
    float hist[10];
    float field40;
    unsigned char field44;
    unsigned char field45;
    unsigned char field46;
    unsigned char pad47;
    short field48;
    short total;
    float field4C;
    int field50;
    float dist;
    int field58;
    int field5C;
    int field60;
    unsigned char pad64[0x70 - 0x64];
    int field70;
    int field74;
    int field78;
    int field7C;
    float pos[3];
    void *field8C;
    void *kart;
    int field94;
} PathEntry;

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

int PathManager_RegisterCarObject(PathMgr *self, float *px, float *py, float *pz, void *obj,
                                  void *kart, int slot)
{
    PathEntry *e;

    if (PathManager_HasPathLoaded(self) == 0) {
        return -1;
    }
    if (slot == -1) {
        if (self->entries[0].node < 0) {
            slot = 0;
        } else if (self->entries[1].node < 0) {
            slot = 1;
        } else if (self->entries[2].node < 0) {
            slot = 2;
        } else if (self->entries[3].node < 0) {
            slot = 3;
        } else if (self->entries[4].node < 0) {
            slot = 4;
        } else if (self->entries[5].node < 0) {
            slot = 5;
        } else if (self->entries[6].node < 0) {
            slot = 6;
        } else if (self->entries[7].node < 0) {
            slot = 7;
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
    e->field70 = 0;
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
