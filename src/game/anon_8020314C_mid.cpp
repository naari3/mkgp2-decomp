#include "game/anon_8020314C_private.h"

void MsgPopup::UpdateBadge() {
    ResCtrl unused;
    float s = fn_8020A6CC(scale.p);
    int b = badge;
    if (msgId != 0x18) {
        if (b != 0) {
            ctrls[3].resId = b;
            ctrls[3].SetScale(s);
            ctrls[3].Show(lbl_806DAAD8 * s + x, y, lbl_806DAAAC);
        }
    } else {
        int res;
        int c = counter;
        if (c >= 0 && c < 12) {
            res = 0x748;
        } else if (c >= 12 && c < 24) {
            res = 0x749;
        } else if (c >= 24 && c < 36) {
            res = 0x74A;
        } else if (c >= 36 && c < 48) {
            res = 0x74B;
        } else {
            res = 0x749;
        }
        ctrls[3].resId = res;
        ctrls[3].SetScale(s);
        ctrls[3].Show(lbl_806DAAD8 * s + x, y, lbl_806DAAAC);
        counter++;
        if (counter >= 60) {
            counter = 0;
        }
    }
}

extern "C" void fn_8020374C(VObject *obj) {
    delete obj;
}

MsgPopup::~MsgPopup() {
    delete[] texts;
    delete[] ctrls;
}

MsgPopup::MsgPopup(int msg, int layer_, int id)
    : FlowTask(id), msgId(msg), layer(layer_), counter(0), fade(new FlowFaderI),
      scaleX(new FlowFaderF(lbl_806DAADC)), scaleY(new FlowFaderF(lbl_806DAADC)),
      scale(new FlowFaderF(lbl_806DAADC)), state(0), x(lbl_806DAADC), y(lbl_806DAADC),
      badge(fn_80202F28(msg)) {
    int i;
    fn_8020A7CC(fade.p, 0, 0x7F, 0xA);
    fn_8020A734(scaleX.p, 0xA, lbl_806DAAA8, lbl_806DAA98);
    fn_8020A734(scaleY.p, 0xA, lbl_806DAAB4, lbl_806DAAA0);
    fn_8020A734(scale.p, 0xA, lbl_806DAAB8, lbl_806DAAA8);
    ctrls = new ResCtrl[4];
    ctrls[0].mode = 2;
    ctrls[0].SetSize(lbl_806DAAE0, lbl_806DAAE4);
    ctrls[0].Show(lbl_806DAAE8, lbl_806DAAEC, lbl_806DAAAC);
    ctrls[1].resId = 0x72F;
    ctrls[2].resId = 0x731;
    texts = new TextManager[4];
    for (i = 0; i < 4; i++) {
        texts[i].visible = 1;
        TexMgr_SetTexture(&texts[i], fn_80202E78(msg, i));
    }
}

extern "C" void fn_80203BEC(void) {
    if (lbl_806D19E8) {
        lbl_806D19E8->Draw();
    }
}
