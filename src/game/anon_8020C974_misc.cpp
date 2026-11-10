#include "game/singleton.h"
#include "game/CardModeRoot_private.h"

void CardModeRoot::StartTask(int st) {
    if (task == 0) {
        Frame_PostDrawOverlay();
        Frame_UpdatePerFrameState();
        switch (st) {
        case 0:
            DemoFlow_ResetTwoFlags();
            if (g_localPcbRole != 0) {
                f28 = 0;
                SetLocalPcbRole(0);
            }
            OperationClock_Commit();
            RaceFlow_ResetState_FullColdInit();
            fn_801FE584(fn_801FE404());
            task = fn_8014F6A4();
            break;
        case 1:
            DemoFlow_ResetTwoFlags();
            break;
        case 2:
            DemoFlow_ResetTwoFlags();
            break;
        case 3:
            if (GetInput()) {
                InputState *in = GetInput();
                in->enabled = 1;
                in->held = 0;
                in->edge = 0;
            }
            task = fn_8020C7F4();
            break;
        case 4:
            break;
        default:
            task = 0;
            break;
        }
    }
}

void CardModeRoot::Draw() {
    if (task != 0) {
        task->Draw();
    }
    DrawScenes();
    fn_8011FAB8();
}

void CardModeRoot::Update() {
    if (GetInput()) {
        InputState *in = g_pInputState;
        CGameCoin_ProcessInput(SINGLETON_INSTANCE(in));
    }
    if (task == 0) {
        int st = state;
        if (st == -1) {
            done = true;
        } else if (st != 5) {
            StartTask(st);
        }
    }
    if (task != 0) {
        if (!task->done) {
            task->Update();
        } else {
            OnTaskDone(state);
        }
    }
    if (HasEjectTask()) {
        if (task != 0) {
            OnTaskDone(state);
        }
        state = 5;
    }
    UpdateScenes();
    fn_801DABFC(fn_801DAEC0());
}

void CardModeRoot::Destroy() {
    delete this;
}

extern "C" CardModeRoot *fn_8020CEAC(void) {
    return new CardModeRoot;
}
