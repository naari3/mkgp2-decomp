#include "game/RivalMarkerPrivate.h"
extern "C" void fn_802437AC(RivalMarkerHud *self, RivalPath *path) {
    if (path) {
        self->path = path;
        RivalRender *kart;
        for (int i = 0; i < 8; ++i) {
            RivalPathEntry *entry = PathManager_GetEntrySubStruct(path, i);
            if (!entry || entry->id == -1) continue;
            kart = entry->kart;
            if (!kart) continue;
            int slot = kart->slot;
            if (slot == GetDisplayBufferIndex()) continue;
            self->karts[i] = kart;
            if (kart->character > -1 && kart->character < 13) {
                self->markers[i] = new RivalMarker(kart, self->layer);
            }
        }
    }
}
