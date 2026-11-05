#include "game/anon_8020314C_private.h"

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
    } else {
        if (lbl_806D0250.pending != -1) {
            return 0;
        }
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
