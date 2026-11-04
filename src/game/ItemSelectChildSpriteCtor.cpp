#include "game/ItemSelectChildSprite.h"
extern "C" {
extern unsigned char lbl_806D1264[3];
extern int g_gameMode, g_cupId;
int Item_GetDescriptorField0(int, void *);
void PreloadResource(int);
}
inline ItemSelectChildEffect::ItemSelectChildEffect()
    : active(0), x(0.0f), y(0.0f), scale(1.0f), fade(new FlowFaderF(0.0f)) {
    fn_8020A734(fade.p, 1, 1.0f, 1.0f);
    ResCtrl rc;
    fn_80121E10(&rc);
    rc.resId = 0xb4f;
    handles[0] = SpriteHandle_CreateDefault(&rc, 3);
    SpriteHandle_SetActiveFlag(handles[0], 0);
    rc.resId = 0xb50;
    handles[1] = SpriteHandle_CreateDefault(&rc, 3);
    SpriteHandle_SetActiveFlag(handles[1], 0);
}
inline ItemSelectChildOverlay::ItemSelectChildOverlay()
    : active(0), x(0.0f), y(0.0f), scale(1.0f), fade(new FlowFaderF(0.0f)),
      alpha(new FlowFaderI), pulse(new FlowFaderI) {
    PreloadResource(0x13b7);
    fn_8020A734(fade.p, 1, 0.0f, 0.0f);
    fn_8020A7CC(alpha.p, 0, 0, 1);
    fn_8020A7CC(pulse.p, 0, 255, 5);
    ResCtrl rc;
    fn_80121E10(&rc);
    rc.resId = 0x13b7;
    handles[0] = SpriteHandle_CreateDefault(&rc, 3);
    SpriteHandle_SetActiveFlag(handles[0], 0);
    rc.mode = 3;
    handles[1] = SpriteHandle_CreateDefault(&rc, 3);
    SpriteHandle_SetActiveFlag(handles[1], 0);
}
ItemSelectChildSprite::ItemSelectChildSprite(int mode_)
    : item(0), effect(0), overlay(0), slide(new FlowFaderF(0.0f)), timer(new FlowFaderI) {
    state = -1;
    phase = 0;
    y = 220.0f;
    scale = 1.0f;
    color = -1;
    handle = -1;
    x = 0.0f;
    baseY = 0.0f;
    PreloadResource(0xb4e);
    PreloadResource(0xb4f);
    PreloadResource(0xb50);
    for (int i=0; i<3; ++i) PreloadResource(Item_GetDescriptorField0(lbl_806D1264[i], 0));
    fn_8020A734(slide.p, 7, 220.0f, 0.0f);
    mode = mode_;
    countdown = 0;
    fade = new FlowFaderF(0.0f);
    item = new ItemAliasSprite(1, 3);
    effect = new ItemSelectChildEffect;
    ResCtrl rc;
    fn_80121E10(&rc);
    rc.resId = 0xb4e;
    handle = SpriteHandle_CreateDefault(&rc, 3);
    SpriteHandle_SetActiveFlag(handle, 0);
    SpriteHandle_RecomputeCull(handle);
    overlay = new ItemSelectChildOverlay;
    variant = g_gameMode;
    if (g_cupId == 0x10) variant = 3;
}
