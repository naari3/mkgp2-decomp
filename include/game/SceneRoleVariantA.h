#ifndef GAME_SCENEROLEVARIANTA_H
#define GAME_SCENEROLEVARIANTA_H
#include "game/FlowScene.h"

/* Private views of the observed 8-byte root and 24-byte role owner. */
struct VariantAChild {
    virtual ~VariantAChild();
    virtual void Finish();
};
struct VariantARoot {
    virtual void Key();
    unsigned char done;
    unsigned char padding[3];
    VariantARoot() : done(0) {}
    ~VariantARoot() {}
};
extern "C" {
void *ItemDisplay_GetOrCreate();
void fn_8020AAD4(void *);
void fn_80120A08(int);
}
struct VariantABase : VariantARoot {
    VariantAChild *child;
    int route;
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    VariantABase();
    ~VariantABase();
    virtual void Key();
    virtual void Finish(int);
    virtual void Update();
    virtual void Draw();
    virtual void Start(int);
};
struct VariantAOwner : VariantABase {
    VariantAOwner();
    ~VariantAOwner();
    virtual void Key();
    virtual void Start(int);
};
#endif
