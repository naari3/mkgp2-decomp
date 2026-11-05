#include "game/RivalMarkerPrivate.h"

extern "C" void fn_80242E80(RivalMarkerHud *self) {
    switch (self->state) {
    case -1:
        if (g_countdownPhase < 4) {
            self->state = 0;
            fn_8020A734(self->fade, 7, lbl_806DBE60, lbl_806DBE64);
        }
        break;
    case 0:
        if (self->fade->Done()) self->state = 1;
        break;
    case 1:
        break;
    case 2:
        self->state = 3;
        break;
    case 3:
        fn_80120A08(0xc2e);
        fn_80120A08(0xc2d);
        fn_80120A08(0x1cd3);
        fn_80120A08(0x1cd4);
        fn_80120A08(0x1cd6);
        if (g_gameMode != 1) {
            for (int i = 0; i < 5; ++i) {
                int round = g_roundIndex;
                int cup = g_cupId;
                int mode = g_gameMode;
                int *p = AI_GetItemList(GetEnemyParam(), mode, cup, round, i);
                while (*p != -1) {
                    fn_80120A08(fn_8023DBEC(*p));
                    ++p;
                }
            }
        }
        return;
    default:
        return;
    }
    if (self->countdown >= 0) {
        --self->countdown;
        if (self->countdown == 0) {
            self->state = 2;
            fn_8020A734(self->fade, 7, lbl_806DBE64, lbl_806DBE60);
        }
    }
    fn_80243464(self);
    for (int i = 0; i < 8; ++i) {
        RivalMarker *p = self->markers[self->order[i]];
        if (p) fn_80243C70(p);
    }
    self->fade->Step();
}
