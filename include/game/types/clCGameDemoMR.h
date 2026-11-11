#ifndef GAME_TYPES_CLCGAMEDEMOMR_H
#define GAME_TYPES_CLCGAMEDEMOMR_H

#include "game/DemoKartScene.h"
#include "game/types/clJobRunner.h"

struct clCGameDemo : clJobRunner {
    clCGameDemo() {}
    virtual int Update();
    virtual void Draw();
    virtual ~clCGameDemo() {}
};

struct clCGameDemoMR : clCGameDemo {
    unsigned char first;
    float time;
    DemoScene *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoNormal *obj;
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *joint;
    clCGameDemoMR();
    virtual int Update();
    virtual void Draw();
    virtual ~clCGameDemoMR();
};

#endif
