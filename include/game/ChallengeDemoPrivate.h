#ifndef GAME_CHALLENGEDEMO_PRIVATE_H
#define GAME_CHALLENGEDEMO_PRIVATE_H

#include "game/DemoKartScene.h"

/* Deleting dispatch slot shared by scene and draw-manager objects. */
struct DemoDeleteView {
    virtual void Destroy(int);
};
struct DemoMode {
    void *vtable;
    unsigned char first;
    unsigned char pad[3];
    float frame;
    DemoScene *camera;
    int owner;
    DemoNormal *world, *extra, *effect;
    HSD_JObj *joint;
    HSD_JObj *joints[5];
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *anchor;
    void *vfx;
};
#endif
