#ifndef GAME_HUDFLOW24CTORPRIVATE_H
#define GAME_HUDFLOW24CTORPRIVATE_H
#include "game/FlowScene.h"
extern "C" char lbl_804EDB28[];
/* Explicit virtual table view, shared with the original flow hierarchy. */
struct HudFlow24Root {
    void *vtable;
    int next;
    HudFlow24Root() : vtable(lbl_804EDB28), next(-1) {}
    ~HudFlow24Root() {}
};
struct HudFlow24 : HudFlow24Root {
    int arg,sprite,state;
    VHolder<FlowFaderF> x,y;
    TextManager *text;
    int handle;
    HudFlow24(int);
};
#endif
