typedef struct UnlockRemap { int baseId; int flagIdx; int resultId; } UnlockRemap;
extern int kItemBaseIdTable[];
extern UnlockRemap kItemUnlockRemap[3];

static inline int CheckRemap(unsigned char *self, UnlockRemap *r, int id) {
    if (r->baseId == id && self[r->flagIdx + 0x121] == 1) {
        return r->resultId;
    }
    return -1;
}

int PlayerData_ResolveUnlockedIdByIndex(unsigned char *self, int idx) {
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
