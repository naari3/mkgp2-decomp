#include "game/FlowScene.h"
#include "game/anon_80216568_fader.h"

extern "C" const unsigned char lbl_80419DC8[];
extern "C" const unsigned char lbl_804E5284[];

static inline void InitBase(FlowFaderBaseLayout *p) {
    p->vtable = lbl_80419DC8;
    p->a = 0;
    p->b = 0;
}

extern "C" FlowFaderI *fn_80218B28(FlowFaderI *p) {
    FlowFaderBaseLayout *base = (FlowFaderBaseLayout *)p;
    InitBase(base);
    base->vtable = lbl_804E5284;
    p->x = 0;
    p->y = 0;
    p->z = 0;
    return p;
}
