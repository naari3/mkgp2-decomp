/*
 * 0x8020E3D0..0x8020F220: fading logo task (resource 0x2AFA) and the task
 * list that runs it.
 */

#include "game/FadeLogoFactory.h"

#pragma auto_inline off

struct Tween : FlowFader {
    float from;
    float to;
    float rate;
    float Value();
};

#include "game/types/FadeKeyBase.h"

#include "game/types/FadeKey.h"

struct FadeSeq {
    virtual ~FadeSeq();
    virtual bool Done();
    virtual void Update();
    bool loop;
    FadeKey *head;
    FadeKey *cur;
    Tween *tween;
    FadeSeq(FadeKey *h, bool l);
};

struct FadeTaskBase : PopupTask {
    int layer;
    FadeTaskBase(int layer_, int id_) : PopupTask(id_), layer(layer_) {}
    virtual ~FadeTaskBase() {}
};

struct FadeLogo : FadeTaskBase {
    VHolder<FadeKey> key1;
    VHolder<FadeSeq> seq1;
    VHolder<FadeKey> key2;
    VHolder<FadeSeq> seq2;
    VHolder<FadeKey> key3;
    VHolder<FadeSeq> seq3;
    FadeLogo(int layer_, int id_);
    ~FadeLogo();
    void Finish();
    void Update();
    void Draw();
};

extern "C" {
extern const float lbl_806DACD8;
extern const float lbl_806DACDC;
extern const float lbl_806DACE0;
extern const float lbl_806DACE4;
extern const float lbl_806DACE8;
extern const float lbl_806DACEC;
extern const float lbl_806DACF0;
extern const float lbl_806DACF4;
extern const float lbl_806DACF8;
void fn_8011FAFC(ResCtrl *ctrl, int layer);
}

inline FadeLogoScene::FadeLogoScene(int layer_, int id_) : PopupTask(id_), layer(layer_), list(new TaskListImpl) {
    TaskListImpl *l = list.p;
    l->Add(new FadeLogo(layer_, 0), 0);
}

extern "C" FadeLogoScene *fn_8020E3D0(int layer, int id) {
    return new FadeLogoScene(layer, id);
}
