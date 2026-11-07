#include "game/FlowPanelNative.h"
extern "C" {
extern const float lbl_806DA1B0, lbl_806DA1B4, lbl_806DA1B8, lbl_806DA1BC;
}
static inline void InitIcons(FlowPanel *panel) {
    FlowPanel *cursor = panel;
    panel->state = 0;
    panel->layout = 0;
    panel->timer = 0;
    panel->alpha = 0;
    panel->layer = 5;
    panel->showBg = 0;
    panel->autoClose = 1;
    panel->labelB = 0;
    panel->labelA = 0;
    for (int i = 0; i < 3; i++) {
        cursor->icons[0] = new ResCtrl;
        cursor = (FlowPanel *)((char *)cursor + sizeof(ResCtrl *));
    }
}

FlowPanel::FlowPanel() {
    InitIcons(this);
    float scale;
    float spacing;
    spacing = lbl_806DA1B0;
    scale = lbl_806DA1B4;
    if (isJapanese()) {
        scale = lbl_806DA1B8;
        spacing = lbl_806DA1BC;
    }
    for (int i = 0; i < 3; i++) {
        texts[i] = new GlyphText;
        TexMgr_SetTexture(texts[i]->tm(), lbl_806DA1AC);
        texts[i]->tm()->scale = scale;
        texts[i]->tm()->visible = 1;
        fn_801F93D0(texts[i]->tm(), spacing, spacing);
    }
    nextLayout = -1;
    queued = 0;
    field24 = 0;
    field28 = 0;
    strings[0] = lbl_806DA1AC;
    strings[1] = lbl_806DA1AC;
    strings[2] = lbl_806DA1AC;
    field38 = 0;
    field3C = -1;
}
