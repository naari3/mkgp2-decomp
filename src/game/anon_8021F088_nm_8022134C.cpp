#include "game/anon_8021F088_private.h"


void clCSSceneCoinMilage::Update() {
    switch (state) {
    case 0:
        if (timer == 30) {
            ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1ADB);
        }
        if (ItemDisplay_GetOrCreate()->state == 2) {
            timer = 0;
            state = 1;
        }
        break;
    case 1:
        StateCoins();
        break;
    case 2:
        StateLines();
        break;
    case 3:
        StateSum();
        break;
    case 4:
        StateItems();
        break;
    case 5:
        StateNext();
        break;
    case 6:
        SetSyncTarget(0x2F);
        if (IsSyncReached() == 1) {
            timer = 0;
            wait = 0;
            state = 7;
        }
        break;
    case 7:
        if (timer == 90) {
            nodes.at(0)->tracks[0].Set(lbl_806DB190, lbl_806DB194, lbl_806DB198);
        }
        if (timer >= 120) {
            timer = 0;
            wait = 0;
            state = 8;
            done = 1;
            ItemDisplay_Stop(ItemDisplay_GetOrCreate());
            fn_8021A0B0(lbl_806D1A60);
        }
        break;
    case 8:
        done = 1;
        break;
    }
    timer++;
    if (state == 4) {
        wnd->Update();
    }
    if (state == 5) {
        next->Update();
    }
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->Tick();
    }
    if (GetInput()->held == 1) {
        SetRumbleMode(0, 1, 1);
    }
    RumbleUpdate();
}
