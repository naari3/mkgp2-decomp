/*
 * HUD manager: result overlay tasks @ 0x80253BE4..0x80253DF0.
 *
 * Each entry point adds one overlay task to the manager's list unless a
 * task with that id is already there, then starts hiding the race parts.
 */

#include "game/HudManager.h"

struct OverlayA {
    char body[0xA0];
    OverlayA(int layer, int a, int b, int id);
};

struct OverlayB {
    char body[0x7C];
    OverlayB(int layer, int id);
};

struct OverlayC {
    char body[0x78];
    OverlayC(int layer, int id);
};

extern "C" {
extern int g_gameMode;
unsigned char fn_80254360(FlowSceneList *list, int id);
void fn_8020EDB4(FlowSceneList *list, void *task, int mode);
void *fn_8020E3D0(int layer, int id);
void fn_80251288(void);
void fn_8025189C(void);
void fn_802156C4(void);
void fn_8020E388(void);
}

extern "C" void fn_80253BE4(HudManager *self) {
    if (!fn_80254360(self->list.p, 0x13)) {
        FlowSceneList *list = self->list.p;
        fn_8020EDB4(list, fn_8020E3D0(4, 0x13), 0);
    }
}

extern "C" bool fn_80253C40(HudManager *self) {
    return !fn_80254360(self->list.p, 0x10);
}

extern "C" void fn_80253C74(HudManager *self, int a, int unused, int b) {
    if (!fn_80254360(self->list.p, 0x10)) {
        FlowSceneList *list = self->list.p;
        fn_8020EDB4(list, new OverlayA(5, a, b, 0x10), 0);
        self->style = 2;
        self->HideAll();
    }
}

extern "C" void fn_80253D00(HudManager *self) {
    if (!fn_80254360(self->list.p, 0x10)) {
        if (g_gameMode != 2) {
            fn_80251288();
            fn_8025189C();
            fn_802156C4();
            fn_8020E388();
        }
        if (g_gameMode == 1) {
            FlowSceneList *list = self->list.p;
            fn_8020EDB4(list, new OverlayB(5, 0x10), 0);
            self->style = 1;
        } else {
            FlowSceneList *list = self->list.p;
            fn_8020EDB4(list, new OverlayC(5, 0x10), 0);
            self->style = 0;
        }
        self->HideAll();
    }
}
