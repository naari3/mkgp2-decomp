#define COIN_EXTERNAL_VTABLE_KEY
#include "game/anon_8021F088_private.h"

clCSSceneCoinMilage::~clCSSceneCoinMilage() {
    delete wnd;
    delete next;
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        delete *it;
    }
    delete model;
    SetInput(0);
    ItemDisplay_Destroy();
    fn_8021A0B0(lbl_806D1A60);
    fn_801699D8(0, 0);
    fn_80169C44();
}
