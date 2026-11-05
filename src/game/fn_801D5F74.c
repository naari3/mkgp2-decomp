#include "game/PlayerUnlockTablesPendingPrivate.h"
extern void PlayStats_OnAllItemsUnlocked_Stub(void);
static inline int ExcludePairs(PlayerDataRecord *p, int n) {
    if (p->unlockFlags[0x3D] == 1 && p->unlockFlags[0x3E] == 1) n--;
    if (p->unlockFlags[0x3F] == 1 && p->unlockFlags[0x40] == 1) n--;
    if (p->unlockFlags[0x41] == 1 && p->unlockFlags[0x42] == 1) n--;
    if (p->unlockFlags[0x43] == 1 && p->unlockFlags[0x44] == 1) n--;
    if (p->unlockFlags[0x64] == 1 && p->unlockFlags[0x65] == 1) n--;
    return n;
}
static inline int CountUnlocked(PlayerDataRecord *p) {
    int n = 0, i;
    for (i = 0; i < 0x79; i++) if (p->unlockFlags[i] == 1) n++;
    return ExcludePairs(p, n);
}
static inline int CheckRemap(PlayerDataRecord *p, UnlockRemap *r, int id) {
    if (r->baseId == id && p->extraFlags[r->flagIdx] == 1) return r->resultId;
    return -1;
}
static inline int Resolve(PlayerDataRecord *p, int idx, UnlockTables *tables) {
    int id, i, r;
    UnlockRemap *remap;
    if (idx < 0 || (unsigned int)idx >= 0x79) return 0;
    id = tables->baseIds[idx];
    remap = tables->remaps;
    for (i = 0; i < 3; i++, remap++) {
        r = CheckRemap(p, remap, id);
        if (r >= 0) { id = r; break; }
    }
    return id;
}
void fn_801D5F74(PlayerDataRecord *p, int id, unsigned char select) {
    UnlockTables *tables = &lbl_8039C718;
    int before = CountUnlocked(p);
    int i;
    UnlockGrant *grant = tables->grants;
    for (i = 0; i < 120; i++, grant++) {
        if (id == grant->id) {
            if (grant->flagIdx >= 0) p->unlockFlags[grant->flagIdx] = 1;
            if (grant->extraIdx >= 0) p->extraFlags[grant->extraIdx] = 1;
        }
    }
    if (select == 1) {
        int after;
        for (i = 0; i < 0x79; i++) {
            if (id == Resolve(p, i, tables)) { p->prefix[0xD] = i; break; }
        }
        after = CountUnlocked(p);
        if (before != after && after == ExcludePairs(p, 0x79)) {
            p->pad124[0x1A8-0x124] = 1;
            PlayStats_OnAllItemsUnlocked_Stub();
        }
    }
}
