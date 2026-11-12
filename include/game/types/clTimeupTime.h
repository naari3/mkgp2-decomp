#ifndef GAME_TYPES_CLTIMEUPTIME_H
#define GAME_TYPES_CLTIMEUPTIME_H

#include "game/types/clTimeup.h"
#include "game/types/FadeKey.h"

struct Tween : FlowFader {
    float from;
    float to;
    float rate;
    float Value();
};

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

struct clTimeupInterface : clCTaskInterface {
    int layer;
    clTimeupInterface(int layer_, int id_) : clCTaskInterface(id_), layer(layer_) {}
    virtual ~clTimeupInterface() {}
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

struct clTimeupTime : clTimeupInterface {
    void Draw();
    VHolder<FadeKey> key1;
    VHolder<FadeSeq> seq1;
    VHolder<FadeKey> key2;
    VHolder<FadeSeq> seq2;
    VHolder<FadeKey> key3;
    VHolder<FadeSeq> seq3;
    clTimeupTime(int layer_, int id_);
    ~clTimeupTime();
    void Finish();
    void Update();
};

#endif
