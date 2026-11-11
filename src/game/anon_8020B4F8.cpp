/* Deferred definitions follow reverse target order. The canonical scene base
 * uses its existing shared RTTI/name through the per-TU bridges. */
#include "game/types/clMnSystem01Battle.h"

static inline void AddInitialTask(FlowSceneList *l) {
    fn_801F4DF0(l, fn_80201A48(0), 2);
}

clMnSystem01Battle::clMnSystem01Battle() : list(new SceneListImpl), fade(new FlowFaderI), task(0), state(0) {
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

clMnSystem01Battle::~clMnSystem01Battle() {
    fn_801F4D3C(list.p);
    fn_80202BCC();
}

extern "C" clMnSystem01Battle *fn_8020B994(void) {
    return new clMnSystem01Battle;
}

void clMnSystem01Battle::Destroy() {
    delete this;
}

void clMnSystem01Battle::OnTaskDone(int st) {
    if (task != 0) {
        PlayerData *pd = &g_playerData;
        switch (st) {
        case 0:
            if (ServiceEnable_Get() && !ServiceValue_Get()) {
                if (Sci2Card_GetByteFlag1224()) {
                    state = 4;
                } else {
                    state = 1;
                }
            } else {
                state = 4;
            }
            break;
        case 1:
            if (Sci2Card_GetUnpackStatusCode() == 2 || Sci2Card_GetUnpackStatusCode() == 4 ||
                Sci2Card_GetUnpackStatusCode() == 5) {
                state = 4;
            } else {
                state = 2;
            }
            break;
        case 2:
            pd->chara = fn_801FE404()->chara;
            if (Sci2Card_GetUnpackStatusCode() == 1) {
                state = 3;
            } else {
                state = 4;
            }
            break;
        case 3:
            fn_801FE554(fn_801FE404(), pd);
            state = 4;
            break;
        case 4:
        case 5:
            fn_8020A7CC(fade.p, 0, 0xFF, 0xF);
            state = 7;
            break;
        case 7:
            fn_8020A7CC(fade.p, 0xFF, 0, 0xF);
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

void clMnSystem01Battle::Update() {
    if (!bgmStarted) {
        if (SyncSlot_GetRecv()->kind == 1) {
            ClSound_PlayBgmStream(1, 0);
            clStream_setVolume(1, fn_801932F8());
            bgmStarted = true;
        }
    }
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

void clMnSystem01Battle::Draw() {
    list.p->Draw();
    if (task != 0) {
        task->Draw();
    }
    fn_8011FAB8();
}
