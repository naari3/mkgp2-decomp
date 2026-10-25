#ifndef GAME_FLOWMSGPOPUP_H
#define GAME_FLOWMSGPOPUP_H

/* Message popup flow tasks (0x80202BCC..0x80203EA0). */

#include "game/FlowScene.h"

extern "C" {
extern const float lbl_806DAA98;
extern const float lbl_806DAA9C;
extern const float lbl_806DAAA0;
extern const float lbl_806DAAA4;
extern const float lbl_806DAAA8;
extern const float lbl_806DAAAC;
extern const float lbl_806DAAB0;
extern const float lbl_806DAAB4;
extern const float lbl_806DAAB8;
extern const float lbl_806DAABC;
extern const float lbl_806DAAC0;
extern const float lbl_806DAAC4;
extern const float lbl_806DAAC8;
extern const float lbl_806DAAD8;
extern const float lbl_806DAADC;
extern const float lbl_806DAAE0;
extern const float lbl_806DAAE4;
extern const float lbl_806DAAE8;
extern const float lbl_806DAAEC;
extern const float lbl_806DAAF0;
const char *fn_80202E78(int msg, int line);
int fn_80202F28(int msg);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
float fn_8020A6CC(FlowFader *fader);
int fn_8020A788(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
}

/* Message popup window (vtable lbl_804EC3E0). */
struct MsgPopup : FlowTask {
    TextManager *texts;
    int msgId;
    int layer;
    int counter;
    VHolder<FlowFaderI> fade;
    VHolder<FlowFaderF> scaleX;
    VHolder<FlowFaderF> scaleY;
    VHolder<FlowFaderF> scale;
    ResCtrl *ctrls;
    int state;
    float x;
    float y;
    int badge;
    MsgPopup(int msg, int layer_, int id);
#ifdef MSGPOPUP_INLINE_DTOR
    ~MsgPopup() {
        delete[] texts;
        delete[] ctrls;
    }
#else
    ~MsgPopup();
#endif
    virtual void _key3();
    void Tick();
    void UpdateBadge();
};

/* Popup variant used for message 0x1C (vtable lbl_804EC3AC). */
struct MsgPopupCoin : MsgPopup {
    MsgPopupCoin(int msg, int layer_, int id) : MsgPopup(msg, layer_, id) {}
    ~MsgPopupCoin();
    virtual void _key4();
};

extern "C" {
struct MsgPopupState {
    int cur;
    int pending;
};
extern MsgPopupState lbl_806D0250;
extern FlowSceneList *lbl_806D19E8;
extern int lbl_806D19EC;
}

static inline int CloseMsgPopup() {
    if (lbl_806D19E8 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19E8, 0);
    if (t) {
        MsgPopup *p = dynamic_cast<MsgPopup *>(t);
        if (p->state < 4) {
            fn_8020A734(p->scaleX.p, 5, lbl_806DAA9C, lbl_806DAA98);
            fn_8020A734(p->scaleY.p, 5, lbl_806DAAA4, lbl_806DAAA0);
            fn_8020A734(p->scale.p, 5, lbl_806DAAAC, lbl_806DAAA8);
            p->state = 4;
        }
        return 1;
    }
    return 0;
}

static inline int OpenMsgPopup(int msg) {
    if (lbl_806D19E8 == 0) {
        return 0;
    }
    bool open = 0;
    if (lbl_806D0250.cur == -1) {
        open = 1;
    } else if (lbl_806D0250.pending == -1) {
        lbl_806D0250.pending = msg;
    }
    if (open) {
        lbl_806D0250.cur = msg;
        if (msg == 0x1C) {
            int layer = lbl_806D19EC;
            fn_801F4DF0(lbl_806D19E8, new MsgPopupCoin(msg, layer, 0), 0);
        } else {
            int layer = lbl_806D19EC;
            fn_801F4DF0(lbl_806D19E8, new MsgPopup(msg, layer, 0), 0);
        }
        FlowTask *t = fn_801F4DC0(lbl_806D19E8, 0);
        if (t) {
            MsgPopup *p = dynamic_cast<MsgPopup *>(t);
            p->x = lbl_806DAAE8;
            p->y = lbl_806DAAF0;
        }
        return 1;
    }
    return 0;
}

#endif
