#define FLOWMSGPOPUP_NO_SERVICE_HELPERS
#include "game/FlowScene.h"
#include "game/FlowMsgPopup.h"

/*
 * Message popup service (0x80203EA0..0x80204474): open/close entry points,
 * service init/shutdown, the SceneListImpl task list and the FlowTask
 * base ctor/dtor.
 */

extern "C" {
void *fn_80271340(void *, int, void *, void *, int);
extern unsigned char MsgPopup_RTTI_806D0268[8];
extern unsigned char FlowTask_RTTI_806D0260[8];

void DebugPrintf(const char *fmt, ...);
void PreloadResource(int id);
void fn_80120A08(int id);
extern const char lbl_803C250C[];
extern const char lbl_803C2528[];

int fn_80203EA0(void);
int fn_80203F5C(int msg);
void fn_802040B0(void);
void fn_80204130(int layer);
}

int fn_80203F5C(int msg) {
    if (lbl_806D19E8 == 0) {
        return 0;
    }
    bool open = 0;
    if (lbl_806D0250.cur == -1) {
        open = 1;
    } else if (lbl_806D0250.pending == -1) {
        lbl_806D0250.pending = msg;
    } else {
        return 0;
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
            MsgPopup *p = (MsgPopup *)fn_80271340(t, 0, MsgPopup_RTTI_806D0268, FlowTask_RTTI_806D0260, 0);
            p->x = lbl_806DAAE8;
            p->y = lbl_806DAAF0;
        }
        return 1;
    }
    return 0;
}
