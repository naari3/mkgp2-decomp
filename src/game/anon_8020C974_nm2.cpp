#include "game/CardModeRoot_private.h"

CardModeRoot::CardModeRoot() : task(0), state(0) {
    CardConfig *cfg;
    fn_801DAEC0();
    DispFlags *d = fn_801DAEC0();
    d->f00 = 1;
    cfg = fn_8024F588(fn_801FE404());
    if (cfg->f0E == 0) {
        lbl_806D1A30 = 0;
        lbl_806D12B0 = 0;
        state = 0;
    } else {
        fn_801FE584(fn_801FE404());
        if (fn_801FE404()->mode == 0) {
            g_ccClass = 2;
        }
        f28 = g_localPcbRole;
        lbl_806D12B0 = 1;
        if (cfg->f0F) {
            state = 1;
        } else {
            int v;
            state = 3;
            v = 1;
            if (cfg->f02) {
                v = 2;
            }
            lbl_806D1A30 = v;
            if (GetInput() == 0) {
                CreateInputState();
            }
            if (!fn_8019083C(1)) {
                ClSound_PlayBgmStream(1, 0);
                clStream_setVolume(1, fn_801932F8());
            }
        }
    }
    StartTask(state);
}
