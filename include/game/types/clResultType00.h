#ifndef GAME_TYPES_CLRESULTTYPE00_H
#define GAME_TYPES_CLRESULTTYPE00_H
#include "game/types/clSceneInterface.h"
#include "game/HudFlowPrivate.h"
/* Private polymorphic host; its original name is not exposed by RTTI.
 * MWCC omits private bases from the public RTTI ancestry. */
struct ResultHost {
    virtual ~ResultHost();
    void *list;
};
struct clResultInterface : clSceneInterface, private ResultHost {
    clResultInterface();
    virtual ~clResultInterface();
    virtual void Update();
    virtual void Draw();
    int state;
    HudChild *child;
    virtual void Enter(unsigned int)=0;
    virtual void Leave(unsigned int)=0;
};
struct clResultType00 : clResultInterface {
    clResultType00();
    virtual ~clResultType00();
    virtual void Destroy();
    virtual void Enter(unsigned int);
    virtual void Leave(unsigned int);
};
#endif
