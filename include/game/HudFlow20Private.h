#ifndef GAME_HUDFLOW20PRIVATE_H
#define GAME_HUDFLOW20PRIVATE_H
#include "game/FlowScene.h"
struct HudFlowRoot {
    virtual void Key();
    int next;
    HudFlowRoot() : next(-1) {}
    ~HudFlowRoot() {}
};
struct HudFlow20 : HudFlowRoot {
    int arg;
    void *sprite;
    int state;
    int index;
    VHolder<FlowFaderF> x;
    VHolder<FlowFaderF> y;
    HudFlow20(int);
    ~HudFlow20();
    virtual void Key();
};
#endif
