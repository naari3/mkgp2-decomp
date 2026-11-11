#ifndef GAME_TYPES_CSCSPARTSMSGWINDOW_H
#define GAME_TYPES_CSCSPARTSMSGWINDOW_H
#include "game/CSParts.h"
struct SpriteAnim {
    void *data;
    int f4;
    int f8;
    SpriteAnim(int a);
};


struct clCSPartsMsgWindow : clCSPartsInerface {
    int state;
    float t;
    float px, py;
    float sx, sy;
    float px2, py2;
    float sx2, sy2;
    float fade;
    SpriteAnim *anim;

    clCSPartsMsgWindow();
    virtual ~clCSPartsMsgWindow();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
    virtual void m20();
    void Print(float x, float y, float w, float h, float r, float g, float b, float a, const char *fmt, ...);
    void Put(int id, int flag, float x, float y, float w, float h, float r, float g, float b, float a);
};



#endif
