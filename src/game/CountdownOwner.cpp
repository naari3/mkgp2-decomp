#include "game/FlowScene.h"

extern "C" {
extern const float lbl_806DBDD0, lbl_806DBDD4, lbl_806DBDC8, lbl_806DBDCC;
extern int g_longRoundFlag;
void PreloadResource(int);
void fn_80121E10(ResCtrl *);
int SpriteHandle_CreateDefault(ResCtrl *, int);
void SpriteHandle_SetActiveFlag(int, int);
void SpriteHandle_RecomputeCull(int);
void SpriteLayer_SetResource(int, int);
void SpriteHandle_Destroy(int);
}

struct CountdownRoot {
    virtual void _key();
    int id;
    CountdownRoot() : id(-1) {}
    ~CountdownRoot() {}
};

struct CountdownOwner : CountdownRoot {
    int layer;
    int sprites[3];
    int current;
    int mode;
    VHolder<FlowFaderF> fade;
    VHolder<FlowFaderF> scale;
    int state, duration, enabled;
    CountdownOwner(int, int);
    ~CountdownOwner();
    virtual void _key2();
};

extern "C" CountdownOwner *fn_8023FB4C(int mode, int layer) {
    return new CountdownOwner(mode, layer);
}

CountdownOwner::~CountdownOwner() {
    for (int i = 0; i < 3; ++i) SpriteHandle_Destroy(sprites[i]);
}

CountdownOwner::CountdownOwner(int mode_, int layer_)
    : layer(layer_), current(-1), mode(mode_),
      fade(new FlowFaderF(lbl_806DBDD0)), scale(new FlowFaderF(lbl_806DBDD0)),
      state(0), enabled(1) {
    PreloadResource(0xB3B);
    PreloadResource(0xB3C);
    if (g_longRoundFlag == 1) duration = 6;
    else duration = 9;
    fade.p->Set(lbl_806DBDD4, lbl_806DBDD0, 7);
    scale.p->Set(lbl_806DBDC8, lbl_806DBDCC, 4);
    ResCtrl res;
    fn_80121E10(&res);
    res.resId = 0xB3B;
    for (int i = 0; i < 3; ++i) {
        sprites[i] = SpriteHandle_CreateDefault(&res, layer);
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    SpriteLayer_SetResource(sprites[0], 0xB3B);
}
/* Native ownership supplies automatic cleanup records for both faders. */
