#include "game/anon_8020314C_private.h"

#pragma peephole off
extern "C" int fn_80203E30(void) {
    if (lbl_806D19E8 == 0) {
        return -1;
    } else {
        return lbl_806D0250.cur;
    }
}
#pragma peephole reset

extern "C" int fn_80203E4C(void) {
    if (lbl_806D19E8 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19E8, 0);
    if (t) {
        t->field0C = 1;
        return 1;
    }
    return 0;
}
