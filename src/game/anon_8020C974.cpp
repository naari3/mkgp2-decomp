/* Deferred emission follows reverse target address order. The secondary
 * FlowSceneHost is a private base, so its RTTI is absent from the public
 * base list while MWCC still emits its deleting-destructor adjustment. */
#include "game/singleton.h"
#include "game/types/clMnSystem.h"

extern "C" {
extern const unsigned int CardMenuRoot_RTTI_806D0310[2];
extern const unsigned int SceneBase_RTTI_806D0308[2];
void *fn_80271340(void *object, int offset, const void *toType, const void *fromType, int isReference);
}

static inline int SelectCardMode(CardConfig *cfg) {
    int mode = 1;
    if (cfg->f02) mode = 2;
    return mode;
}

clMnSystem::clMnSystem() : task(0), state(0) {
    CardConfig *cfg;
    fn_801DAEC0();
    DispFlags *d = fn_801DAEC0();
    d->f00 = 1;
    cfg = fn_8024F588(fn_801FE404());
    if (cfg->f0E == 0) {
        lbl_806D1A30 = 0;
        lbl_806D12B0 = 0;
        state = 0;
    } else {
        fn_801FE584(fn_801FE404());
        if (fn_801FE404()->mode == 0) {
            g_ccClass = 2;
        }
        f28 = g_localPcbRole;
        lbl_806D12B0 = 1;
        if (cfg->f0F) {
            state = 1;
        } else {
            state = 3;
            lbl_806D1A30 = SelectCardMode(cfg);
            if (GetInput() == 0) {
                CreateInputState();
            }
            if (!fn_8019083C(1)) {
                ClSound_PlayBgmStream(1, 0);
                clStream_setVolume(1, fn_801932F8());
            }
        }
    }
    StartTask(state);
}

clMnSystem::~clMnSystem() {
    g_cupId = f08;
    g_longRoundFlag = f0C;
    SetReverseRoundFlag(f14);
    g_courseVariantIdx = f10;
    g_roundIndex = f48;
    lbl_806D1264[0] = f30[0];
    lbl_806D1264[1] = f30[1];
    lbl_806D1264[2] = f30[2];
    fn_8011F86C();
    clRom_DumpListOverlay();
    if (fn_8019083C(1)) {
        fn_801909A4(1);
    }
    fn_80121210();
    fn_801DAE54();
    delete (VObject *)g_pInputState;
    g_pInputState = 0;
}

extern "C" clMnSystem *fn_8020CEAC(void) {
    return new clMnSystem;
}

void clMnSystem::Destroy() {
    delete this;
}

void clMnSystem::Update() {
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

void clMnSystem::Draw() {
    if (task != 0) {
        task->Draw();
    }
    DrawScenes();
    fn_8011FAB8();
}

void clMnSystem::StartTask(int st) {
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

void clMnSystem::OnTaskDone(int st) {
    if (task != 0) {
        if (st == 3) {
            clMnSystem01 *menu = static_cast<clMnSystem01 *>(fn_80271340(task, 0, CardMenuRoot_RTTI_806D0310, SceneBase_RTTI_806D0308, 0));
            mode = fn_801FE404()->mode;
            chara = fn_801FE404()->chara;
            f08 = menu->f08;
            f0C = menu->f0C;
            f10 = menu->f10;
            f14 = menu->f14;
            f48 = menu->f48;
        }
        task->Destroy();
        task = 0;
        switch (st) {
        case 0:
            fn_80218F1C();
            ServiceMode_UpdateScheduleGate();
            if (GetInput() == 0) {
                CreateInputState();
            }
            if (fn_801FE404()->f194) {
                f28 = 0;
                SetLocalPcbRole(0);
                {
                    FlowMgrInfo *st = fn_801FE404();
                    st->f168 = 0;
                }
                StrPcb_ForceRun_Neutral(StrPcb_GetInstance());
                StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
                state = 3;
            } else {
                state = 1;
            }
            break;
        case 1:
            f28 = fn_801FE404()->f168;
            if (lbl_806D12B0) {
                if (f28 > 0) {
                    mode = 2;
                    fn_801FE404()->mode = mode;
                }
                state = 3;
            } else {
                state = 0;
            }
            break;
        case 2:
            f28 = fn_801FE404()->f168;
            if (lbl_806D12B0) {
                state = 3;
            } else {
                state = 0;
            }
            break;
        case 3: {
            int i;
            for (i = 0; i < 3; i++) {
                f30[i] = fn_801FE404()->f188[i];
            }
            state = 4;
            break;
        }
        case 4:
            state = -1;
            break;
        }
    }
}
