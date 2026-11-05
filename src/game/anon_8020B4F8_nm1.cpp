#include "game/anon_8020B4F8_private.h"

static inline void AddInitialTask(FlowSceneList *l) {
    fn_801F4DF0(l, fn_80201A48(0), 2);
}

BattleMenu::BattleMenu() : list(new SceneListImpl), fade(new FlowFaderI), task(0), state(0) {
    fn_80202C34(0);
    fn_80202B48(0);
    if (GetInput() == 0) {
        CreateInputState();
    }
    if (ServiceEnable_Get() && !ServiceValue_Get()) {
        state = 1;
    } else {
        state = 2;
    }
    fn_8020A7CC(fade.p, 0xFF, 0, 0xF);
    if (SyncSlot_GetHostSend() != 0) {
        SyncSlot_GetHostSend()->kind = 1;
    }
    bgmStarted = false;
    AddInitialTask(list.p);
    Factory();
}
