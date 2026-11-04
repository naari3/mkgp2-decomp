#define ANON_8020314C_HELPERS
#include "game/anon_8020314C_private.h"

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
