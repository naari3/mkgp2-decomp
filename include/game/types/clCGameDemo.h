#ifndef GAME_TYPES_CLCGAMEDEMO_H
#define GAME_TYPES_CLCGAMEDEMO_H
#include "game/types/clJobRunner.h"
struct clCGameDemo : clJobRunner {
    clCGameDemo() {}
    virtual int Update();
    virtual void Draw();
    virtual ~clCGameDemo() {}
};
#endif
