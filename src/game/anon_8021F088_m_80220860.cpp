#include "game/anon_8021F088_private.h"

clGetCoinLine::clGetCoinLine(const char *label, int n, float y, Model *m)
    : value(n), add(0), model(m), rot(lbl_806DB190), spr(new Sprite(0x13E, 1, 0)) {
    timer = 0;
    flashTimer = 0;
    flash = 0;
    tracks[4].Set(y, y, lbl_806DB1E0);
    tracks[3].Set(lbl_806DB23C, lbl_806DB21C, lbl_806DB1EC);
    spr.p->SetPos(lbl_806DB23C, y);
    spr.p->layer = 1;
    TexMgr_SetTexture(&text, label);
    text.visible = 1;
    fn_801F93EC(&text, lbl_806DB240, lbl_806DB244 + y);
    text.spacing = lbl_806DB248;
    Layout(y);
}
