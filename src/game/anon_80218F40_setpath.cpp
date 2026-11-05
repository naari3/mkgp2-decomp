#include "game/anon_80218F40_private.h"

void MinimapHud::SetPath(PathManager *pm) {
    if (pm == 0) {
        return;
    }
    path = pm;
    PathEntry *e;
    int pid;
    int offset;
    int n = 0;
    int i;
    for (i = 0, offset = 0; i < 8; i++) {
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
        *(int *)((char *)order + offset) = i;
        offset += sizeof(int);
        n++;
        if (n >= 8) {
            break;
        }
    }
}
