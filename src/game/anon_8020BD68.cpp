#include "game/types/clMnSystem01Single.h"

void clMnSystem01Single::Draw() {
    list.p->Draw();
    if (task != 0) {
        task->Draw();
    }
    fn_8011FAB8();
}

void clMnSystem01Single::Update() {
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

void clMnSystem01Single::OnTaskDone(int st) {
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

void clMnSystem01Single::Destroy() {
    delete this;
}

extern "C" clMnSystem01Single *fn_8020C254(void) {
    return new clMnSystem01Single;
}

clMnSystem01Single::~clMnSystem01Single() {
    fn_801F4D3C(list.p);
    fn_80202BCC();
}


static inline void AddInitialTask(FlowSceneList *l) {
    fn_801F4DF0(l, fn_80201A48(0), 2);
}

clMnSystem01Single::clMnSystem01Single() : list(new SceneListImpl), fade(new FlowFaderI), task(0), state(0) {
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
