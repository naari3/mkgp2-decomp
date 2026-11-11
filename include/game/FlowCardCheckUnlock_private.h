#ifndef GAME_FLOW_CARD_CHECK_UNLOCK_PRIVATE_H
#define GAME_FLOW_CARD_CHECK_UNLOCK_PRIVATE_H

class clFlowCCInterface {
public:
    clFlowCCInterface() : dir(0), inTimer(0), outTimer(0), active(0) {
        slide = -1000.0f;
        f8 = 0.0f;
    }
    virtual ~clFlowCCInterface();
    virtual int Update() = 0;
    virtual void Draw() = 0;
    virtual void Unk14() = 0;
    virtual void SlideIn();
    virtual void SlideOut();
    virtual void OnShown();
    virtual void OnHidden();

    float slide;
    float f8;
    int dir;
    int inTimer;
    int outTimer;
    unsigned char active;
    unsigned char pad19[3]; /* tail padding, named so a derived class cannot use it */

    void Open(int t) {
        inTimer = t;
        active = 1;
        dir = 1;
        SlideIn();
    }
    void Close(int t) {
        outTimer = t;
        dir = 0;
        SlideOut();
    }
    unsigned char IsIdle() {
        unsigned char r = 0;
        if (inTimer == 0 && outTimer == 0) {
            r = 1;
        }
        return r;
    }
    void UpdateSlide() {
        if (IsIdle() != 1) {
            int t = 0;
            if (inTimer > 0) {
                if (--inTimer == 0) {
                    OnShown();
                }
            } else if (outTimer > 0) {
                if (--outTimer == 0) {
                    active = 0;
                    OnHidden();
                }
                t = 18 - outTimer;
            }
            float d = 1000.0f;
            if (dir == 0) {
                d = -1000.0f;
            }
            slide = d * (t / 18.0f);
        }
    }
};

class clIndicator;
#include "game/types/clFlowProcess.h"

#include "game/types/clFlowCardCheck.h"


#endif
