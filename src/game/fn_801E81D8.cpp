/* Native reconstruction of the assigned single-function TU. */
#include "game/AIKartInitPrivate.h"
extern "C" {
extern char lbl_804E4A34[];
void Path_ResetCursorForKart(void *, int);
void dtor_800AA888(void *, int);
void dtor_80060024(void *, int);
void MemoryManager_TimedFree(void *);
void *fn_801E81D8(AIKart *self, short flag) {
    if (self) {
        self->AIResponder::vptr = lbl_804E4A34;
        self->AIWarpResponder::vptr = lbl_804E4A34 + 0x10;
        if (self->path && self->pathId != -1) Path_ResetCursorForKart(self->path, self->pathId);
        self->aux.~AIOwn();
        self->steering.~AIOwn();
        self->item.~AIOwn();
        self->run.~AIOwn();
        self->extra.~AIOwn();
        self->audio.~AIOwn();
        self->tornado.~AIOwn();
        self->driver.~AIOwn();
        dtor_800AA888(&self->AIWarpResponder::vptr, 0);
        dtor_80060024((AIResponder *)self, 0);
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
}
