#ifndef GAME_TYPES_CLFLOWCARDCHECK_H
#define GAME_TYPES_CLFLOWCARDCHECK_H

#include "game/types/clFlowProcess.h"

/* Declare before including (each user already does): clFlowCCInterface, clIndicator */

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

#endif /* GAME_TYPES_CLFLOWCARDCHECK_H */
