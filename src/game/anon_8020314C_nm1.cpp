#include "game/anon_8020314C_private.h"

static inline void LayoutPopupTexts(MsgPopup *popup, float s) {
    int i;
    float ts = s;
    if (popup->msgId == 4) {
        ts = s * lbl_806DAAC0;
    }
    int dy = 0;
    float ox = lbl_806DAAC4 * s;
    float base = -40.0f;
    for (i = 0; i < 4; i++, dy += 30) {
        float yy = s * (base + (float)dy);
        fn_801F93EC(&popup->texts[i], popup->x + ox, popup->y + yy);
        fn_801F93D0(&popup->texts[i], ts, ts);
    }
}

void MsgPopup::Tick() {
    switch (state) {
    case 0:
        state = 1;
        break;
    case 1:
        if (fade.p->Done()) {
            state = 2;
        }
        break;
    case 2:
        if (scaleX.p->Done()) {
            if (lbl_806DAA98 == fn_8020A6CC(scaleX.p)) {
                fn_8020A734(scaleX.p, 5, lbl_806DAA98, lbl_806DAA9C);
                fn_8020A734(scaleY.p, 5, lbl_806DAAA0, lbl_806DAAA4);
                fn_8020A734(scale.p, 5, lbl_806DAAA8, lbl_806DAAAC);
            } else {
                state = 3;
            }
        }
        break;
    case 3:
        break;
    case 4:
        if (scaleX.p->Done()) {
            if (lbl_806DAA98 == fn_8020A6CC(scaleX.p)) {
                fn_8020A734(scaleX.p, 0xA, lbl_806DAA98, lbl_806DAAB0);
                fn_8020A734(scaleY.p, 0xA, lbl_806DAAA0, lbl_806DAAB4);
                fn_8020A734(scale.p, 0xA, lbl_806DAAA8, lbl_806DAAB8);
            } else {
                fn_8020A7CC(fade.p, 0x7F, 0, 0xA);
                state = 5;
            }
        }
        break;
    case 5:
        if (fade.p->Done()) {
            state = 6;
        }
        break;
    case 6:
        field0C = 1;
        state = -1;
        break;
    }
    float s;
    float sx = fn_8020A6CC(scaleX.p);
    float sy = fn_8020A6CC(scaleY.p);
    s = fn_8020A6CC(scale.p);
    ResCtrl unused;
    ctrls[0].SetColor(fn_8020A788(fade.p));
    float off = lbl_806DAABC * s;
    ctrls[1].SetScaleXY(sx, sy);
    {
        float px = x + off;
        float py = y + off;
        ctrls[1].Show(px, py, lbl_806DAAAC);
    }
    ctrls[2].SetScale(s);
    {
        float px = x;
        float py = y;
        ctrls[2].Show(px, py, lbl_806DAAAC);
    }
    UpdateBadge();
    LayoutPopupTexts(this, s);
    fade.p->Step();
    scaleX.p->Step();
    scaleY.p->Step();
    scale.p->Step();
}
