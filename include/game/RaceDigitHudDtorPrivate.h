#ifndef GAME_RACE_DIGIT_HUD_DTOR_PRIVATE_H
#define GAME_RACE_DIGIT_HUD_DTOR_PRIVATE_H
#include "game/RaceDigitsPrivate.h"
#include "game/RaceDigitListPrivate.h"

/* The list's three destructor layers are inline in the owning HUD. */
struct RaceHudListBase : RaceDigitList {
    ~RaceHudListBase() {
        RaceDigitEraseRange(this, Begin(), Finish());
    }
};
struct RaceHudListMid : RaceHudListBase { ~RaceHudListMid() {} };
struct RaceHudList : RaceHudListMid { ~RaceHudList() {} };

struct RaceDigitHudDtorBase {
    virtual void Key();
    virtual ~RaceDigitHudDtorBase() {}
    int id;
};
struct RaceDigitHudDtor : RaceDigitHudDtorBase {
    virtual void Key();
    int layer;
    void *sprites[4];
    int state, mode;
    float offset, scale;
    VHolder<FlowFaderF> slide;
    int field30;
    RaceHudList list;
    DigitOwner main, others[5];
    virtual ~RaceDigitHudDtor();
};
#endif
