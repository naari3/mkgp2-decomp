#ifndef GAME_TYPES_CLMNCARDT02_H
#define GAME_TYPES_CLMNCARDT02_H
#include "game/types/clMnCardClasses.h"
struct clMnCardT02 : clMnCardT0Interface {
    virtual ~clMnCardT02();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    void Save();
    void Eject();
    void Select();
    int kind, arg2C, field30, coins;
    unsigned char field38;
    char pad39[3];
    int slot;
    unsigned char field40, field41;
    char pad42[2];
    int field44;
    clMnCardT02(int arg, int base);
};
#endif
