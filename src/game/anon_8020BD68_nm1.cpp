#include "game/anon_8020BD68_private.h"

static inline void AddInitialTask(FlowSceneList *l) {
    fn_801F4DF0(l, fn_80201A48(0), 2);
}

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
    AddInitialTask(list.p);
    {
        /* Keep the initial dispatch in this constructor: its locals share
         * registers with the earlier mode and cup selections. */
        int id;
        int mode;
        int chara;
        id = state;
        if (task == 0) {
            mode = fn_801FE404()->mode;
            chara = fn_801FE404()->chara;
            switch (id) {
            case 0:
            case 2:
            case 3:
            case 4:
            case 6:
            case 12:
                break;
            case 1:
                task = fn_801FA024();
                break;
            case 5:
                fn_80202A5C(0xF);
                task = fn_8015B6D0();
                break;
            case 7:
                if (fn_8020A788(fade.p) == 0xFF) {
                    fn_8020A7CC(fade.p, 0, 0, 1);
                    task = fn_801F3914(chara, 0);
                }
                break;
            case 11:
                if (fn_801D5C88(&g_playerData, g_ccClass) == 1) {
                    SetCC(true);
                } else {
                    SetCC(false);
                }
                break;
            default:
                task = 0;
                break;
            }
        }
    }
}
