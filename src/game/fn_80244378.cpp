#include "game/FlowScene.h"
extern "C" void MemoryManager_TimedFree(void *);
extern "C" int RivalMarker_vtable_804EE784[];
struct GaugeOwnerView {
    void *vtable;
    char pad[0x2c];
    VObject *p30, *p34, *p38, *p3c;
};
extern "C" GaugeOwnerView *fn_80244378(GaugeOwnerView *self, short flag) {
    if (self) {
        self->vtable = RivalMarker_vtable_804EE784;
        if (self->p38) { delete self->p38; self->p38 = 0; }
        if (self->p3c) { delete self->p3c; self->p3c = 0; }
        if (self->p34) { delete self->p34; self->p34 = 0; }
        if (self->p30) { delete self->p30; self->p30 = 0; }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
