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

extern "C" bool fn_801FD924(FlowController *self) {
    return fn_801F4DC0(self->owner, 100) != 0;
}

FlowSceneHost::~FlowSceneHost() {
    fn_801F4D3C(list.p);
}

FlowSceneHost::FlowSceneHost() : list(new SceneListImpl) {
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

extern "C" int fn_801FDA78(int code) {
    lbl_806D19D0 = 0;
    lbl_806D19D4 = 0;
    if (MapCommonCardError(code)) {
        return lbl_806D19D4;
    }
    switch (code) {
    case 1:
        break;
    case 2:
        lbl_806D19D0 = 1;
        lbl_806D19D4 = 5;
        break;
    default:
        card_save_trigger(1);
        lbl_806D19D4 = 9;
        break;
    }
    return lbl_806D19D4;
}

extern "C" int fn_801FDB90(int code) {
    lbl_806D19D0 = 0;
    lbl_806D19D4 = 0;
    if (MapCommonCardError(code)) {
        return lbl_806D19D4;
    }
    switch (code) {
    case 1:
        break;
    case 2:
        lbl_806D19D0 = 1;
        lbl_806D19D4 = 5;
        break;
    default:
        card_save_trigger(0);
        lbl_806D19D4 = 9;
        break;
    }
    return lbl_806D19D4;
}

extern "C" int fn_801FDCA8(int code) {
    lbl_806D19D0 = 0;
    lbl_806D19D4 = 0;
    if (MapCommonCardError(code)) {
        return lbl_806D19D4;
    }
    switch (code) {
    case 1:
        break;
    case 7:
    default:
        card_eject_init();
        lbl_806D19D4 = 9;
        break;
    }
    return lbl_806D19D4;
}

extern "C" int fn_801FDDA4(int code) {
    lbl_806D19D0 = 0;
    lbl_806D19D4 = 0;
    if (MapCommonCardError(code)) {
        return lbl_806D19D4;
    }
    switch (code) {
    case 1:
        break;
    case 4:
        lbl_806D19D4 = 1;
        break;
    case 3:
        if (Sci2Card_GetUnpackStatusCode() == 6) {
            lbl_806D19D4 = 2;
        }
        break;
    case 103:
        lbl_806D19D4 = 3;
        break;
    case 5:
        lbl_806D19D4 = 4;
        break;
    case 2:
    default:
        DebugPrintf(lbl_806DA840, lbl_803BFEF8, 0xD7);
        card_send_read_cmd_init();
        lbl_806D19D4 = 9;
        break;
    }
    return lbl_806D19D4;
}

extern "C" int fn_801FDF20(void) {
    int code = Sci2Card_GetPrintErrorCode();
    lbl_806D19D0 = 0;
    lbl_806D19D4 = 0;
    if (code == 100) {
        lbl_806D19D0 = 0;
        lbl_806D19D4 = 9;
        return 9;
    }
    if (MapCommonCardError(code)) {
        return lbl_806D19D4;
    }
    if (code != 1) {
        card_send_ping_cmd_init();
        lbl_806D19D4 = 9;
    }
    return lbl_806D19D4;
}

extern "C" int fn_801FE030(int code, unsigned char clean) {
    lbl_806D19D0 = 0;
    lbl_806D19D4 = 0;
    if (MapCommonCardError(code)) {
        return lbl_806D19D4;
    }
    switch (code) {
    case 1:
        break;
    case 6:
    default:
        if (clean == 1) {
            DebugPrintf(lbl_806DA840, lbl_803BFEF8, 0x6D);
            card_send_cleaning_cmd_init();
        }
        lbl_806D19D4 = 9;
        break;
    }
    return lbl_806D19D4;
}
