#ifndef GAME_CLMRRCAUTION_H
#define GAME_CLMRRCAUTION_H
#include "game/FlowScene.h"
extern "C" const float lbl_806DBE64, lbl_806DBE90;
struct clMrrCaution {
    virtual ~clMrrCaution();
    int field04, layer;
    float x, y, scale;
    VHolder<FlowFaderI> fade;
    clMrrCaution(int a, int b) : field04(a), layer(b), x(0.0f), y(0.0f), scale(1.0f), fade(new FlowFaderI) {
        fade.p->Set(0, 255, 5);
    }
    void SetPosition(float px,float py) { x=px; y=py; }
    static void ShowYX(ResCtrl &r,float py,float px,float pz) {
        r.flag=1; r.x=px; r.y=py; r.z=pz;
    }
    void Draw(unsigned char visible) {
        ResCtrl r;
        int l = layer;

        float s = scale;
        r.resId = 0x1cd4;
        ShowYX(r,y,x,1.0f);
        r.SetScale(s);
        if (visible) fn_8011FAFC(&r,l);
        fade.p->Step();
        if (fade.p->Done()) {
            if (fade.p->Value() == 255) fade.p->Set(255,0,5);
            else fade.p->Set(0,255,5);
        }
    }
};
#endif
