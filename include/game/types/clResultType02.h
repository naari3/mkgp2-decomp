#ifndef GAME_TYPES_CLRESULTTYPE02_H
#define GAME_TYPES_CLRESULTTYPE02_H
#include "game/types/clResultType01.h"
struct clResultType02 : clResultInterface {
    clResultType02();
    virtual ~clResultType02();
    virtual void Destroy();
    virtual void Enter(unsigned int);
    virtual void Leave(unsigned int);
};
#endif
