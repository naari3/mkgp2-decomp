#ifndef GAME_CLCGAMEDEMOWC_TICK_PRIVATE_H
#define GAME_CLCGAMEDEMOWC_TICK_PRIVATE_H

#include "game/DemoKartScene.h"

/* Tick-only owner view; offsets agree with the existing DemoWC constructor. */
struct DemoWCTickAux {
    virtual void v0();
    virtual void Tick();
};
struct DemoWCTick {
    void *vtable;
    unsigned char first, pad5[3];
    float frame;
    DemoScene *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *joint;
    int event;
    DemoWCTickAux *aux;
};
#endif
