#ifndef GAME_HUDFLOW24PRIVATE_H
#define GAME_HUDFLOW24PRIVATE_H
#include "game/HudFlow20Private.h"
/* The target pools both language tables in one data object. */
struct HudFlowLabels { const char *international[13]; const char *japanese[13]; };
struct HudFlow24 : HudFlowRoot {
    int arg,sprite,state;
    VHolder<FlowFaderF> x,y;
    TextManager *text;
    int handle;
    virtual void Key();
    HudFlow24(int);
};
#endif
