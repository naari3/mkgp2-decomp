#ifndef GAME_TYPES_CLRSCONTINUE_H
#define GAME_TYPES_CLRSCONTINUE_H
#include "game/FlowScene.h"
#include "game/types/clSceneInterface.h"
struct clRsContinue : clSceneInterface {
    clSceneInterface *child;
    int route;
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    clRsContinue();
    virtual ~clRsContinue();
    virtual void Destroy() = 0;
    virtual void Update();
    virtual void Draw();
    virtual void Start(int) = 0;
    virtual void Finish(int) = 0;
};
struct clRsContinueBT : clRsContinue {
    clRsContinueBT();
    virtual ~clRsContinueBT();
    virtual void Destroy();
    virtual void Start(int);
    virtual void Finish(int);
};
struct clRsContinueTA : clRsContinue {
    clRsContinueTA();
    virtual ~clRsContinueTA();
    virtual void Destroy();
    virtual void Start(int);
    virtual void Finish(int);
};
struct clRsContinueGP : clRsContinue {
    clRsContinueGP();
    virtual ~clRsContinueGP();
    virtual void Destroy();
    virtual void Start(int);
    virtual void Finish(int);
};
#endif
