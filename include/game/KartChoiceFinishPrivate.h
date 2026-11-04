#ifndef GAME_KARTCHOICEFINISHPRIVATE_H
#define GAME_KARTCHOICEFINISHPRIVATE_H
#include "game/SpritePairOwner.h"
struct ChoiceFinishBase {
    virtual void _key();
    unsigned char done;
    ChoiceFinishBase() : done(0) {}
    ~ChoiceFinishBase() {}
};
struct ChoiceFinish : ChoiceFinishBase {
    int state;
    Sprite *sprite;
    int handle, timer;
    virtual void _key2();
    ChoiceFinish();
    ~ChoiceFinish();
};
#endif
