#ifndef GAME_FLOWPANEL_NATIVE_H
#define GAME_FLOWPANEL_NATIVE_H
#include "game/TitleNameHud.h"
struct PanelSprite {
    int resource, layer;
    char pad08[0x28];
    PanelSprite(int anim, int loop, int arg);
};
struct FlowPanel {
    int state, layout, timer, field0C, alpha, layer;
    float x, y;
    unsigned char showBg, autoClose;
    char pad22[2];
    int field24, field28;
    const char *strings[3];
    int field38, field3C, nextLayout;
    unsigned char queued;
    char pad45[3];
    PanelSprite *labelB, *labelA;
    ResCtrl *icons[3];
    GlyphText *texts[3];
    FlowPanel();
};
extern "C" {
extern const char lbl_806DA1AC[1];
void fn_801F93D0(TextManager *, float, float);
}
#endif
