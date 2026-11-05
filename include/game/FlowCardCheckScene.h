#ifndef GAME_FLOW_CARD_CHECK_SCENE_H
#define GAME_FLOW_CARD_CHECK_SCENE_H
#include "game/FlowCardCheckInterface.h"
class clIndicator;
class clFlowProcess {
public:
    clFlowProcess();
    virtual ~clFlowProcess();
    virtual int Update();
    virtual void Draw();
};

class clFlowCardCheck : public clFlowProcess {
public:
    unsigned char stickLatch;
    int page;
    int prevPage;
    int timer;
    int state;
    float bright;
    int result;
    clIndicator *indicator;
    clFlowCCInterface *pages[8];

    clFlowCardCheck();
    virtual ~clFlowCardCheck();
    virtual int Update();
    virtual void Draw();
};

#endif
