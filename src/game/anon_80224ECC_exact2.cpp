#include "game/anon_80224ECC_private.h"

clCSSceneBanner::clCSSceneBanner() {
    obj = 0;
    xc = 0;
    timer = 0;
    state = 0;
    spr = 0;
    obj = new SceneObj(-1, -1, -1, -1, 5);
    bool show = false;
    if (g_gameMode == 0 && fn_8024F588()->flag == 1 && g_roundIndex != 3 && g_roundIndex != 7) {
        show = true;
    }
    if (fn_8024F588()->x10 >= 0) {
        done = 1;
        state = 4;
    }
    CreditMgr_SetActiveSlot(1);
    InitRumbleController(1);
    if (!show) {
        state = 4;
        done = 1;
    }
    fn_8023F5B4(&spr, lbl_806DB340, lbl_806DB344, lbl_806D0508, 1);
    spr->alpha = lbl_806DB330;
    ResCtrl rc;
    rc.mode = 2;
    rc.SetSize(lbl_806DB348, lbl_806DB34C);
    rc.Show(lbl_806DB340, lbl_806DB350, lbl_806DB32C);
    rc.SetColor(0);
    fade = SpriteHandle_CreateDefault(&rc, 3);
}

void clCSSceneBanner::Destroy() {
    delete this;
}


extern "C" clCSSceneBanner *fn_802253B0(void) {
    return new clCSSceneBanner;
}
