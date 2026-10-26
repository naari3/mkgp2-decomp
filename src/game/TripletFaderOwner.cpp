#include "game/FlowScene.h"

extern "C" {
extern const float lbl_806DBF60, lbl_806DBF64, lbl_806DBF7C;
void PreloadResource(int);
int SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_SetActiveFlag(int, int);
void SpriteHandle_RecomputeCull(int);
void SpriteHandle_Destroy(int);
}

struct TripletFaderRoot {
    virtual void _key();
    int id;
    TripletFaderRoot() : id(-1) {}
    ~TripletFaderRoot() {}
};

struct TripletFaderOwner : TripletFaderRoot {
    int layer;
    int sprites[2];
    int current, state;
    float value;
    int mode;
    VHolder<FlowFaderF> fade, scale, position;
    VHolder<FlowFaderI> frame;
    TripletFaderOwner(int);
    ~TripletFaderOwner();
    virtual void _key2();
};

extern "C" TripletFaderOwner *fn_802499F4(int layer) {
    return new TripletFaderOwner(layer);
}

TripletFaderOwner::~TripletFaderOwner() {
    for (int i = 0; i < 2; ++i) SpriteHandle_Destroy(sprites[i]);
}

TripletFaderOwner::TripletFaderOwner(int layer_)
    : layer(layer_), current(-1), state(0), value(lbl_806DBF7C), mode(0),
      fade(new FlowFaderF(lbl_806DBF60)), scale(new FlowFaderF(lbl_806DBF60)),
      position(new FlowFaderF(lbl_806DBF60)), frame(new FlowFaderI) {
    PreloadResource(0xB23);
    fade.p->Set(lbl_806DBF7C, lbl_806DBF60, 7);
    scale.p->Set(lbl_806DBF64, lbl_806DBF64, 1);
    position.p->Set(lbl_806DBF60, lbl_806DBF60, 1);
    frame.p->Set(0, 0, 1);
    ResCtrl res;
    res.resId = 0xB23;
    sprites[0] = SpriteHandle_CreateDefault(&res, layer);
    res.mode = 3;
    sprites[1] = SpriteHandle_CreateDefault(&res, layer);
    for (int i = 0; i < 2; ++i) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}
/* Native ownership emits the four holder exception specifications. */
