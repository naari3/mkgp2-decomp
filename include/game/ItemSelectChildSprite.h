#ifndef GAME_ITEMSELECTCHILDSPRITE_H
#define GAME_ITEMSELECTCHILDSPRITE_H
#include "game/ItemAliasSprite.h"

/* Private observed layouts for the item-selection child at 0x8023DCEC. */
struct ItemSelectChildEffect {
    unsigned char active;
    float x, y, scale;
    int handles[2];
    VHolder<FlowFaderF> fade;
    ItemSelectChildEffect();
    ~ItemSelectChildEffect() {
        for (int i=0; i<2; ++i) SpriteHandle_Destroy(handles[i]);
    }
};
struct ItemSelectChildOverlay {
    unsigned char active;
    float x, y, scale;
    int handles[2];
    VHolder<FlowFaderF> fade;
    VHolder<FlowFaderI> alpha, pulse;
    ItemSelectChildOverlay();
    ~ItemSelectChildOverlay();
};
struct ItemSelectChildSprite {
    ItemAliasSprite *item;
    ItemSelectChildEffect *effect;
    ItemSelectChildOverlay *overlay;
    VHolder<FlowFaderF> slide;
    VHolder<FlowFaderI> timer;
    int state, phase;
    float y, scale;
    int color;
    unsigned char mode;
    int handle, variant;
    FlowFaderF *fade;
    int countdown;
    float x, baseY;
    ItemSelectChildSprite(int mode);
    ~ItemSelectChildSprite();
};
extern "C" {
extern const float lbl_806DBDA8, lbl_806DBDB0, lbl_806DBDB4;
float fn_8020A6CC(FlowFader *);
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFader *, int, float, float);
void fn_8020A7CC(FlowFader *, int, int, int);
void fn_8023D458(ItemAliasSprite *, int);
void fn_8023D2B4(ItemAliasSprite *);
void fn_8011F994(int);
}
#endif
