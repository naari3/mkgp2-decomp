#ifndef GAME_ITEMLISTHUDPRIVATE_H
#define GAME_ITEMLISTHUDPRIVATE_H
#include "game/TitleNameHud.h"
extern "C" const float lbl_806DBE64, lbl_806DBE60;

struct ItemListHud : HudPart {
    virtual void _keyItemList();
    void Update(); void Draw(); void SetDelay(int);
    int layer;
    int current;
    unsigned char enabled;
    VHolder<FlowFaderF> fade;
    int count;
    int ids[8];
    int values[8];
    VObject *objects[8];
    ItemListHud(int layer_) : layer(layer_), current(-1), enabled(1),
        fade(new FlowFaderF(lbl_806DBE64)), count(0) {
        for (int i=0; i<8; ++i) {
            ids[i]=i; values[i]=0; objects[i]=0;
        }
        fade.p->Set(lbl_806DBE60, lbl_806DBE60, 1);
    }
    ~ItemListHud();
};
#endif
