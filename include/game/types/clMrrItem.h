#ifndef GAME_TYPES_CLMRRITEM_H
#define GAME_TYPES_CLMRRITEM_H
#include "game/FlowScene.h"

/* The item-use gauge and its transient marker. Both own their tween objects. */
struct ItemUseStats;
struct ItemUseOwner { char pad[0x344]; ItemUseStats *stats; };
extern "C" {
int fn_8023DBEC(int);
int ItemUseStats_GetItemIdIfFlag14(ItemUseStats *);
int ItemUseStats_GetCountCat5_6_8(ItemUseStats *);
int ItemUseStats_GetCountCat7_9(ItemUseStats *);
int ItemUseStats_GetCountBanana(ItemUseStats *);
int ItemUseStats_GetCountShell(ItemUseStats *);
extern const float lbl_806DBE64, lbl_806DBE90, lbl_806DBEC4;
extern const float lbl_806DBEC0;
extern const float lbl_806DBEC8, lbl_806DBECC, lbl_806DBED0, lbl_806DBED4;
}
struct clMrrItemEffect {
    virtual ~clMrrItemEffect();
    void *context;
    float x,y,scale;
    bool Draw(unsigned char);
    void SetPosition(float px, float py) { x=px; y=py; }
    VHolder<FlowFaderF> fade, size;
    VHolder<FlowFaderI> alpha;
    clMrrItemEffect(void *c) : context(c), x(0.0f), y(0.0f), scale(1.0f),
        fade(new FlowFaderF(0.0f)), size(new FlowFaderF(0.0f)), alpha(new FlowFaderI) {
        fade.p->Set(0.0f, 1.0f, 10);
        size.p->Set(0.0f, lbl_806DBED4, 20);
        alpha.p->Set(0,255,10);
    }
};
struct clMrrItem {
    virtual ~clMrrItem();
    ItemUseOwner *owner;
    void *context;
    int state, item, cat568, cat79, bananas, shells, category;
    float x,y,scale;
    VHolder<FlowFaderF> fade;
    VHolder<FlowFaderI> alpha;
    VHolder<FlowFaderF> size;
    VHolder<FlowFaderI> color, flash;
    VHolder<FlowFaderF> offset;
    clMrrItemEffect *burst;
    clMrrItem(ItemUseOwner *, int, void *);
    void Draw(unsigned char);
    void Update();
    void Trigger();
};
#endif
