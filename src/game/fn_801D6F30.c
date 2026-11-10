#include "game/types/UnlockRemap.h"
extern int kItemBaseIdTable[];
extern UnlockRemap kItemUnlockRemap[3];

static inline int CheckRemap(unsigned char *self, UnlockRemap *r, int id) {
    if (r->baseId == id && self[r->flagIdx + 0x121] == 1) {
        return r->resultId;
    }
    return -1;
}

static inline int Resolve(unsigned char *self, int idx) {
    int id;
    int i;
    int r;
    UnlockRemap *remap;

    if (idx < 0 || (unsigned int)idx >= 0x79) {
        return 0;
    }
    id = kItemBaseIdTable[idx];
    remap = kItemUnlockRemap;
    for (i = 0; i < 3; i++, remap++) {
        r = CheckRemap(self, remap, id);
        if (r >= 0) {
            id = r;
            break;
        }
    }
    return id;
}

extern int ItemAlias_DestToSource(int, signed char *);
unsigned char fn_801D6F30(unsigned char *self, int id, unsigned char aliases) {
    signed char idAlias = 0;
    int source = ItemAlias_DestToSource((unsigned char)id, &idAlias);
    int i;
    for (i = 0; i < 0x79; i++) {
        if (self[i + 0xA8] == 1) {
            int item = Resolve(self, i);
            unsigned char found = 0;
            if (aliases == 0) {
                if (id == item) found = 1;
            } else {
                signed char itemAlias = 0;
                int itemSource = ItemAlias_DestToSource((unsigned char)item, &itemAlias);
                if (itemSource == source) {
                    if (itemAlias == 1 && idAlias == 0) found = 1;
                    else if (itemAlias == 0 && idAlias == 0) found = 1;
                    else if (itemAlias == 1 && idAlias == 1) found = 1;
                }
                if (id == 0x3F && itemSource == 0x3D) found = 1;
                if (id == 0x3A && itemSource == 0x39) found = 1;
                if (id == 0x33 && itemSource == 0x32) found = 1;
            }
            if (found == 1) return 1;
        }
    }
    return 0;
}
