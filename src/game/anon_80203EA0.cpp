#define FLOWMSGPOPUP_NO_SERVICE_HELPERS
#define SCENELISTIMPL_EXTERNAL_VTABLE
#include "game/FlowScene.h"
#include "game/FlowMsgPopup.h"

/*
 * Message popup service (0x80203EA0..0x80204474): open/close entry points,
 * service init/shutdown, the SceneListImpl task list and the FlowTask
 * base ctor/dtor.
 */

extern "C" {
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

extern "C" {
extern const unsigned long MsgPopup_RTTI_806D0268[2];
extern const unsigned long FlowTask_RTTI_806D0260[2];
void *fn_80271340(void *, int, const void *, const void *, int);
}

static inline int CloseMsgPopup() {
    if (lbl_806D19E8 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19E8, 0);
    if (t) {
        MsgPopup *p = (MsgPopup *)fn_80271340(t, 0, MsgPopup_RTTI_806D0268, FlowTask_RTTI_806D0260, 0);
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

int fn_80203EA0(void) {
    return CloseMsgPopup();
}
