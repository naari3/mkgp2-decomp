#ifndef GAME_TYPES_CLFRNKDISP_H
#define GAME_TYPES_CLFRNKDISP_H
#include "game/KartChoiceOwnerPrivate.h"
#include "game/types/clCDispInterface.h"

/* Face-rank display. Legacy callers still use KartChoiceOwner's layout view. */
struct clFRnkDisp : clCDispInterface {
    virtual ~clFRnkDisp();
    virtual void Update();
    virtual void Draw();
    virtual void Request();
    int layer, phase, choice;
    ChoiceChild *child;
    ChoiceOther *other;
    VHolder<FlowFaderF> fade, scale;
    ChoiceRender *render;
    int state, selected;
    float x, y, vx, vy;
    clFRnkDisp(int);
};
#endif
