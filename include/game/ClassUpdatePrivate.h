#ifndef CLASS_UPDATE_PRIVATE_H
#define CLASS_UPDATE_PRIVATE_H
#include "game/types/size_t.h"
void *operator new(size_t);
void operator delete(void *);
struct ClassSprite {
    char pad0[12]; float x,y,sx,sy; char pad1C[20];
    ClassSprite(int,int,int);
    ClassSprite(int,unsigned char,float,float);
    void pos(float a,float b) { x=a; y=b; }
    void scale(float a,float b) { sx=a; sy=b; }
};
struct ClassUpdate {
    void *vptr;
    unsigned char advance, mode, fading, pad7;
    int count, selection, unknown10, state, selectedSpecial, indicatorStarted;
    float brightness, elapsed;
    int result;
    ClassSprite *indicator, *sprites[3], *extra;
    int unknown40;
    ClassSprite *left, *right;
    int ticks; float startX,startY;
};
struct ClassInputState { char pad[0x14]; int delta; };
struct ClassPlayer {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8();
    virtual unsigned int Check(int);
};
struct ClassAnims { int ids[3]; };
#endif
