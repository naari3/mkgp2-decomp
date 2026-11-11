#ifndef GAME_TYPES_CLRESULTTYPE01_H
#define GAME_TYPES_CLRESULTTYPE01_H
#include "game/types/clSceneInterface.h"
struct HudChild;
/* The secondary list owner is a private base and is absent from public RTTI. */
struct ResultListOwner {
    virtual ~ResultListOwner();
    void *list;
    ResultListOwner();
};
struct clResultInterface : clSceneInterface, private ResultListOwner {
    clResultInterface();
    virtual ~clResultInterface();
    virtual void Destroy() = 0;
    virtual void Update();
    virtual void Draw();
    virtual void Enter(unsigned int) = 0;
    virtual void Leave(unsigned int) = 0;
    int state;
    HudChild *child;
};
struct clResultType01 : clResultInterface {
    clResultType01();
    virtual ~clResultType01();
    virtual void Destroy();
    virtual void Enter(unsigned int);
    virtual void Leave(unsigned int);
};
#endif
