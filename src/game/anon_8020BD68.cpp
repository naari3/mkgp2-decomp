#include "game/anon_8020BD68_private.h"

void GrandPrixMenu::Draw() {
    list.p->Draw();
    if (task != 0) {
        task->Draw();
    }
    fn_8011FAB8();
}

void GrandPrixMenu::Update() {
    fn_80202A24();
    list.p->Update();
    if (task == 0) {
        if (state == -1 && fn_8020A788(fade.p) == 0xFF) {
            fn_802043B8(list.p, 0);
            done = true;
        } else {
            Factory();
        }
    }
    if (task != 0) {
        if (!task->done) {
            task->Update();
        } else {
            OnTaskDone(state);
        }
    }
    ResCtrl ctrl;
    unsigned char a = fn_8020A788(fade.p);
    ctrl.mode = 2;
    ctrl.SetSize(640.0f, 480.0f);
    ctrl.Show(320.0f, 240.0f, 1.0f);
    ctrl.SetColor(a);
    fn_8011FAFC(&ctrl, 7);
    fade.p->Step();
}

void GrandPrixMenu::OnTaskDone(int st) {
    if (task != 0) {
        PlayerData *pd = &g_playerData;
        switch (st) {
        case 0:
            state = 0xB;
            break;
        case 1:
            if (Sci2Card_GetUnpackStatusCode() == 2 || Sci2Card_GetUnpackStatusCode() == 4) {
                state = 5;
            } else {
                state = 2;
            }
            break;
        case 2:
            pd->chara = fn_801FE404()->chara;
            if (Sci2Card_GetUnpackStatusCode() == 1) {
                state = 3;
            } else if (g_playerData.hasCard == 0) {
                state = 0;
            } else {
                fn_8020A7CC(fade.p, 0, 0xFF, 0xF);
                state = 7;
            }
            break;
        case 3:
            fn_801FE554(fn_801FE404(), pd);
            state = 5;
            card_force_backup_now();
            break;
        case 4:
            if (!Sci2Card_GetByteFlag1224()) {
                if (g_playerData.hasCard == 0) {
                    state = 0;
                } else {
                    fn_8020A7CC(fade.p, 0, 0xFF, 0xF);
                    state = 7;
                }
            } else {
                state = 5;
            }
            break;
        case 5:
            if (pd->hasCard == 0) {
                state = 0;
            } else {
                fn_8020A7CC(fade.p, 0, 0xFF, 0xF);
                state = 7;
            }
            break;
        case 7:
            fn_8020A7CC(fade.p, 0xFF, 0, 0xF);
            state = 0;
            break;
        case 6:
            state = 0xB;
            break;
        case 11:
            state = 0xC;
            break;
        case 12:
            state = -1;
            fn_8020A7CC(fade.p, 0, 0xFF, 0xF);
            break;
        }
        if (task != 0) {
            task->Destroy();
            task = 0;
        }
    }
}

void GrandPrixMenu::Destroy() {
    delete this;
}

extern "C" GrandPrixMenu *fn_8020C254(void) {
    return new GrandPrixMenu;
}

GrandPrixMenu::~GrandPrixMenu() {
    fn_801F4D3C(list.p);
    fn_80202BCC();
}
