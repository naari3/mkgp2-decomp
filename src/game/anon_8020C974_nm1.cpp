#include "game/CardModeRoot_private.h"

CardModeRoot::~CardModeRoot() {
    g_cupId = f08;
    g_longRoundFlag = f0C;
    SetReverseRoundFlag(f14);
    g_courseVariantIdx = f10;
    g_roundIndex = f48;
    lbl_806D1264[0] = f30[0];
    lbl_806D1264[1] = f30[1];
    lbl_806D1264[2] = f30[2];
    fn_8011F86C();
    clRom_DumpListOverlay();
    if (fn_8019083C(1)) {
        fn_801909A4(1);
    }
    fn_80121210();
    fn_801DAE54();
    delete (VObject *)g_pInputState;
    g_pInputState = 0;
}

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
