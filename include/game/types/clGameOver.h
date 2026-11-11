#ifndef GAME_TYPES_CLGAMEOVER_H
#define GAME_TYPES_CLGAMEOVER_H
#include "game/types/clSceneInterface.h"
struct Sprite;
struct clGameOver : clSceneInterface {
    virtual ~clGameOver();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    int state;
    Sprite *sprite;
    int handle, timer;
    clGameOver();
};
#endif
