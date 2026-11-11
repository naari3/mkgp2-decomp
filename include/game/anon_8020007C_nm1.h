#ifndef GAME_ANON_8020007C_NM1_H
#define GAME_ANON_8020007C_NM1_H

/* Private countdown banner/gauge declarations; shared FlowCountdown.h is unchanged. */

#include "game/FlowScene.h"

struct CcLObjList;

template <> struct VHolder<CcLObjList> {
    CcLObjList *p;
    VHolder() : p(0) {}
    VHolder(CcLObjList *q) : p(q) {}
    ~VHolder() throw();
    void Reset(CcLObjList *q) throw();
};
struct CcScene;

template <> struct VHolder<CcScene> {
    CcScene *p;
    VHolder() : p(0) {}
    VHolder(CcScene *q) : p(q) {}
    ~VHolder() throw();
    void Reset(CcScene *q) throw();
};


struct CountdownPartB;
struct CountdownPartA;
struct CountdownGaugePart;

template <> struct VHolder<CountdownPartB> {
    CountdownPartB *p;
    VHolder() : p(0) {}
    VHolder(CountdownPartB *q) : p(q) {}
    ~VHolder() throw();
};

template <> struct VHolder<CountdownPartA> {
    CountdownPartA *p;
    VHolder() : p(0) {}
    VHolder(CountdownPartA *q) : p(q) {}
    ~VHolder() throw();
};

template <> struct VHolder<CountdownGaugePart> {
    CountdownGaugePart *p;
    VHolder() : p(0) {}
    VHolder(CountdownGaugePart *q) : p(q) {}
    ~VHolder() throw();
};


extern "C" {
extern const float lbl_806DA878;
extern const float lbl_806DA87C;
extern const float lbl_806DA880;
extern const float lbl_806DA88C;
extern const float lbl_806DA890;
extern const float lbl_806DA894;
extern const float lbl_806DA898;
extern const float lbl_806DA884;
extern const float lbl_806DA888;
extern int lbl_803C0200[10];
extern int lbl_803C01C4[15];
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void PreloadResource(int id);
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
float fn_8020A6CC(FlowFader *fader);
int fn_8020A788(FlowFader *fader);
extern float lbl_803C014C[15][2];
extern float lbl_803C0228[2][2];
void fn_80121E10(ResCtrl *ctrl);
int fn_8020A900(int value, int digit);
}

/* Sprite overlay drawn on top of CountdownBanner (types 0..2). */
struct CountdownPartA {
    virtual inline ~CountdownPartA();
    virtual void _key();
    int type;
    int layer;
    int field0C;
    float x;
    float y;
    float mul;
    int counter;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    CountdownPartA(int type_, int layer_)
        : layer(layer_), field0C(0), x(lbl_806DA880), y(lbl_806DA880), counter(0),
          scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI) {
        if (type_ <= -1 || type_ >= 6) {
            type = 0;
        } else {
            type = type_;
        }
        PreloadResource(0x88D);
        PreloadResource(0x88E);
        PreloadResource(0x88F);
        fn_8020A734(scale.p, 0xA, lbl_806DA894, lbl_806DA898);
        fn_8020A7CC(fade.p, 0xCC, 0xCC, 0xA);
    }
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

/* Sprite overlay drawn on top of CountdownBanner (types 3..5). */
struct CountdownPartB {
    virtual inline ~CountdownPartB();
    virtual void _key();
    int type;
    int layer;
    int field0C;
    float x;
    float y;
    float mul;
    int counter;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    CountdownPartB(int type_, int layer_)
        : layer(layer_), field0C(0), x(lbl_806DA880), y(lbl_806DA880), counter(0),
          scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI) {
        if (type_ <= -1 || type_ >= 6) {
            type = 0;
        } else {
            type = type_;
        }
        PreloadResource(0x88C);
        PreloadResource(0x890);
        PreloadResource(0x8A7);
        fn_8020A734(scale.p, 0x46, lbl_806DA894, lbl_806DA894);
        fn_8020A7CC(fade.p, 0xCC, 0xCC, 0x46);
    }
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

#include "game/types/CountdownResStep.h"

extern "C" {
extern CountdownResStep lbl_803C00DC[14];
void fn_80200A48(CountdownPartA *part);
void fn_80200654(CountdownPartB *part);

}

/* Animated countdown banner. */
struct CountdownBanner : FlowTask {
    int type;
    int layer;
    int state;
    float x;
    float y;
    int counter;
    VHolder<CountdownPartA> partA;
    VHolder<CountdownPartB> partB;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    int resId;
    CountdownBanner(int type_, int layer_, int id);
    ~CountdownBanner();
    virtual void _key3();
};

#endif
