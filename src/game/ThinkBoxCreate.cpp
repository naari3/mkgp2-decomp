#include "game/ThinkBoxCreatePrivate.h"
extern "C" ThinkBoxBase *ThinkBox_Create() {
    if (g_gameMode == 0) return new ThinkBoxRace;
    if (g_isCommHost) {
        if (g_gameMode == 2) return new ThinkBoxHost;
        return new ThinkBoxRace;
    }
    return new ThinkBoxClient;
}
struct ThinkBoxStorage { void *storage; };
extern "C" ThinkBoxStorage *dtor_801EC388(ThinkBoxStorage *self, short deleting) {
    if (self) {
        MemoryManager_TimedFree(self->storage);
        if (deleting > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
