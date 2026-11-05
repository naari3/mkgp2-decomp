/*
 * Card-system result tasks and Sci2Card error mapping @ 0x801FD924..0x801FE150.
 */

#include "game/FlowScene.h"

struct FlowController {
    void *vt;
    FlowSceneList *owner;
};

/* Holds the scene list at +4 (vtable lbl_804EC190). */
struct FlowSceneHost {
    virtual void _key();
    VHolder<FlowSceneList> list;
    FlowSceneHost();
    ~FlowSceneHost();
};

extern "C" {
extern int lbl_806D19D0;
extern int lbl_806D19D4;
extern const char lbl_806DA840[7];
extern const char lbl_803BFEF8[];
void DebugPrintf(const char *fmt, ...);
void card_save_trigger(int mode);
void card_eject_init(void);
void card_send_read_cmd_init(void);
void card_send_ping_cmd_init(void);
void card_send_cleaning_cmd_init(void);
int Sci2Card_GetUnpackStatusCode(void);
int Sci2Card_GetPrintErrorCode(void);
}

static inline int MapCommonCardError(int code) {
    int handled;
    switch (code) {
    case 101:
        lbl_806D19D0 = 0x33;
        handled = 1;
        lbl_806D19D4 = 6;
        break;
    case 102:
        lbl_806D19D0 = 0x34;
        handled = 1;
        lbl_806D19D4 = 7;
        break;
    case 100:
    case 104:
        lbl_806D19D0 = 0x35;
        handled = 1;
        lbl_806D19D4 = 6;
        break;
    case 105:
        lbl_806D19D0 = 0x36;
        handled = 1;
        lbl_806D19D4 = 7;
        break;
    case 106:
        lbl_806D19D0 = 0x37;
        handled = 1;
        lbl_806D19D4 = 7;
        break;
    default:
        handled = 0;
        break;
    }
    return handled;
}

extern "C" int fn_801FDDA4(int code) {
    lbl_806D19D0 = 0;
    lbl_806D19D4 = 0;
    if (MapCommonCardError(code)) {
        return lbl_806D19D4;
    }
    if (code == 5) goto status4;
    if (code >= 5) {
        if (code == 103) goto status3;
        if (code >= 103) goto error;
        goto error;
    }
    if (code == 2) goto error;
    if (code >= 2) {
        if (code >= 4) goto status1;
        goto unpack;
    }
    if (code >= 1) goto done;
    goto error;
status1:
    lbl_806D19D4 = 1;
    goto done;
unpack:
    if (Sci2Card_GetUnpackStatusCode() == 6) lbl_806D19D4 = 2;
    goto done;
status3:
    lbl_806D19D4 = 3;
    goto done;
status4:
    lbl_806D19D4 = 4;
    goto done;
error:
    DebugPrintf(lbl_806DA840, lbl_803BFEF8, 0xD7);
    card_send_read_cmd_init();
    lbl_806D19D4 = 9;
done:
    return lbl_806D19D4;
}
