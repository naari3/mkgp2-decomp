#include "game/anon_8020BD68_private.h"

GrandPrixMenu::GrandPrixMenu() : list(new SceneListImpl), fade(new FlowFaderI), task(0), state(0) {
    fn_80202C34(0);
    fn_80202B48(0);
    switch (lbl_806D1A30) {
    case 1:
        state = 0xB;
        SetMode(g_gameMode);
        break;
    case 2: {
        state = 0xB;
        SetMode(g_gameMode);
        SetCup(g_cupId);
        break;
    }
    default:
        if (ServiceEnable_Get() && !ServiceValue_Get()) {
            state = 1;
        } else {
            state = 2;
        }
        break;
    }
    fn_8020A7CC(fade.p, 0xFF, 0, 0xF);
    ClSound_PlayBgmStream(1, 0);
    clStream_setVolume(1, fn_801932F8());
    {
        FlowSceneList *l = list.p;
        fn_801F4DF0(l, fn_80201A48(0), 2);
    }
    Factory();
}
