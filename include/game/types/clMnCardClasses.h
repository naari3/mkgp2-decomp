#ifndef GAME_TYPES_CLMNCARDCLASSES_H
#define GAME_TYPES_CLMNCARDCLASSES_H
#include "game/FlowScene.h"

struct clYTaskInterface {
    virtual ~clYTaskInterface();
    int id, field08, field0C;
};
struct clMnTaskInterface : clYTaskInterface {
    clMnTaskInterface(int);
    virtual ~clMnTaskInterface();
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};
struct clMnCardT0Interface : clMnTaskInterface {
    virtual ~clMnCardT0Interface();
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    int state, subState, timer, cursor;
    clMnCardT0Interface(int);
};
struct clMnCardErr : clMnTaskInterface {
    virtual ~clMnCardErr();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    TextManager *texts;
    clMnCardErr(int);
};
#endif
