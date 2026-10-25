/*
 * Message popup window task @ 0x8020314C..0x80203EA0.
 */

#include "game/FlowMsgPopup.h"


extern "C" void fn_8020314C(MsgPopup *self) {
    if (self->state < 6) {
        int msg = self->msgId;
        if (msg != 0 && msg != 1) {
            fn_8011FAFC(&self->ctrls[0], self->layer);
        }
        if (self->state < 5) {
            int i;
            fn_8011FAFC(&self->ctrls[1], self->layer);
            fn_8011FAFC(&self->ctrls[2], self->layer);
            if (self->badge != 0) {
                fn_8011FAFC(&self->ctrls[3], self->layer);
            }
            for (i = 0; i < 4; i++) {
                fn_801F8A34(fn_801F8E58(), &self->texts[i], self->layer);
            }
        }
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
    ctrls[1].Show(x + off, y + off, lbl_806DAAAC);
    ctrls[2].SetScale(s);
    ctrls[2].Show(x, y, lbl_806DAAAC);
    UpdateBadge();
    {
        int i;
        float ts = s;
        if (msgId == 4) {
            ts = s * lbl_806DAAC0;
        }
        int dy = 0;
        float base = lbl_806DAAC8;
        float ox = lbl_806DAAC4 * s;
        for (i = 0; i < 4; i++, dy += 30) {
            fn_801F93EC(&texts[i], x + ox, y + s * (base + (float)dy));
            fn_801F93D0(&texts[i], ts, ts);
        }
    }
    fade.p->Step();
    scaleX.p->Step();
    scaleY.p->Step();
    scale.p->Step();
}

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

extern "C" void fn_80203C24(void) {
    FlowTask *t = fn_801F4DC0(lbl_806D19E8, 0);
    if (t == 0) {
        lbl_806D0250.cur = -1;
    }
    if (lbl_806D0250.pending != -1) {
        if (t) {
            CloseMsgPopup();
        } else {
            int req = lbl_806D0250.pending;
            lbl_806D0250.pending = -1;
            OpenMsgPopup(req);
        }
    }
    if (lbl_806D19E8) {
        lbl_806D19E8->Update();
    }
}

extern "C" int fn_80203E30(void) {
    if (lbl_806D19E8 == 0) {
        return -1;
    } else {
        return lbl_806D0250.cur;
    }
}

extern "C" int fn_80203E4C(void) {
    if (lbl_806D19E8 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19E8, 0);
    if (t) {
        t->field0C = 1;
        return 1;
    }
    return 0;
}
