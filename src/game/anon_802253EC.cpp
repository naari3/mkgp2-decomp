#include "game/NetJoin_private.h"

void clCSSceneNextRaceBT::Draw() {
    waiter->Draw();
    fn_801D9A2C(panel);
    fn_801F8A34(fn_801F8E58(), text->tm(), 1);
    prompt->Draw();
    list->Draw();
    if (popup) {
        popup->Draw();
    }
}

void clCSSceneNextRaceBT::Update() {
    if (done == 1) {
        return;
    }
    if (state == 4) {
        done = 1;
        return;
    }
    if (count < 30) {
        if (++count == 30) {
            SetSyncTarget(0x32);
        }
    }
    bool pressed;
    InputState *in;
    float t = PcbSyncTable_LookupValueByState(g_localPcbRole);
    in = GetInput();
    pressed = in->held == 1;
    if (state >= 1) {
        if (pressed == 1) {
            SetPcbMode(4);
        } else {
            SetPcbMode(1);
        }
    }
    switch (state) {
    case 0:
        if (time >= lbl_806DB358) {
            time = lbl_806DB35C;
            state = 1;
            SetPcbSub(1);
        }
        break;
    case 1:
        if (pressed) {
            SetPcbMode(4);
            SetPcbScratchFlag_806d11a4();
        }
        if (in->held == 3 && t >= lbl_806DB360 && timing == 0) {
            SetPcbSub(4);
            state = 2;
            joined = 1;
            if (popup == 0) {
                popup = new NetJoinPopup;
            }
            break;
        }
        if (fn_8021B568(waiter) == 0 && timing == 0) {
            timing = 1;
            t0 = OSGetTime();
            fn_8021B5D4(waiter);
        }
        if (timing == 1 && (float)OSTicksToMilliseconds(OSGetTime() - t0) / lbl_806DB364 >= lbl_806DB368 && PCBComm_ConfirmHostBattle() == 1) {
            t0 = OSGetTime();
            time = lbl_806DB35C;
            state = 3;
            fn_801D919C(panel);
            if (g_localPcbRole != 0) {
                lbl_806D17F1 = 1;
            } else {
                lbl_806D17F1 = 0;
            }
        }
        break;
    case 2:
        if (fn_8021B568(waiter) == 0 && timing == 0) {
            timing = 1;
            t0 = OSGetTime();
            time = lbl_806DB35C;
            state = 1;
            joined = 0;
            if (popup) {
                delete popup;
                popup = 0;
            }
            break;
        }
        if (popup->state == 4) {
            joined = 0;
            if (popup->ok == 1) {
                joined = 1;
                state = 3;
                time = lbl_806DB35C;
                t0 = 0;
                fn_801D919C(panel);
            } else {
                SetInput(1);
                state = 1;
                time = lbl_806DB35C;
                SetPcbSub(1);
            }
            if (popup) {
                delete popup;
                popup = 0;
            }
            break;
        }
        if (t <= lbl_806DB360) {
            time = lbl_806DB35C;
            state = 1;
            joined = 0;
            if (popup) {
                delete popup;
                popup = 0;
            }
        }
        break;
    case 3:
        if (panel->state == 0 && (float)OSTicksToMilliseconds(OSGetTime() - t0) / lbl_806DB364 >= lbl_806DB36C) {
            lbl_806D17F0 = 1;
            fn_801FE348();
            if (joined == 1) {
                SetSyncTarget(0xD);
                SetLocalPcbRole(0);
                lbl_806D17F1 = 0;
            }
            fn_8021B5D4(waiter);
            RankLog *log = GetRankLog();
            if (log) {
                RankLog_OnRoundComplete(log);
                TitleStats_ResetRaceStagingState(log);
            }
            time = lbl_806DB35C;
            state = 4;
            SetPcbMode(0);
            SetPcbSub(0);
        }
        break;
    }
    if (popup == 0) {
        scroll -= lbl_806DB370;
        if (scroll <= -scrollMin) {
            scroll = scrollMin;
        }
        fn_801F93EC(text->tm(), scroll, lbl_806DB374);
        waiter->Update();
        fn_801D9B70(panel, 0);
        box->Cull();
        prompt->Update();
        list->Update();
    } else {
        popup->Update();
    }
    if (state >= 3) {
        t = lbl_806DB378;
    } else {
        fn_801FE27C((int)t);
    }
    fn_80232284(ItemMsg_Get(), t);
    time += lbl_806DB37C;
}

clCSSceneNextRaceBT::~clCSSceneNextRaceBT() {
    SetInput(0);
    if (popup) {
        delete popup;
        popup = 0;
    }
    if (prompt) {
        delete prompt;
        prompt = 0;
    }
    if (text) {
        delete text;
        text = 0;
    }
    if (panel) {
        fn_801D9F88(panel, 1);
        panel = 0;
    }
    if (box) {
        delete box;
        box = 0;
    }
    if (waiter) {
        delete waiter;
        waiter = 0;
    }
    if (list) {
        delete list;
        list = 0;
    }
}
