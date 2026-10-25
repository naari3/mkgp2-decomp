/*
 * 0x8020C974..0x8020D1C0: card mode root scene. Runs the card attract /
 * entry / menu tasks in turn and writes the chosen race settings back to the
 * globals when it goes away.
 */

#include "game/FlowScene.h"

#pragma auto_inline off

struct SceneBase {
    virtual ~SceneBase() {}
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    bool done;
    SceneBase() : done(false) {}
};

struct FlowMgrInfo {
    char pad000[0x164];
    int chara;
    int f168;
    int mode;
    int f170;
    int f174;
    int f178;
    int f17C;
    int f180;
    int pad184;
    int f188[3];
    unsigned char f194;
};

struct CardConfig {
    char pad00[2];
    unsigned char f02;
    char pad03[0xE - 3];
    unsigned char f0E;
    unsigned char f0F;
};

struct DispFlags {
    unsigned char f00;
};

/* Menu mode base (vtable lbl_804E549C, ctor fn_801F5B54). */
struct MenuModeBase : SceneBase {
    int f08;
    int f0C;
    int f10;
    int f14;
    char pad18[0x28 - 0x18];
    int f28;
    int pad2C;
    int f30[3];
    int chara;
    int pad40;
    int mode;
    int f48;
    char pad4C[0x5C - 0x4C];
    MenuModeBase();
    ~MenuModeBase() {}
};

/* Holds the scene list at +4 (vtable lbl_804EC190). */
struct FlowSceneHost {
    virtual ~FlowSceneHost();
    VHolder<FlowSceneList> list;
    FlowSceneHost();
    void DrawScenes();
    bool HasEjectTask();
    void UpdateScenes();
};

struct CardMenuRoot : MenuModeBase {
    SceneBase *task;
    CardMenuRoot();
    ~CardMenuRoot();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
};

struct InputImpl {
    void *vt;
    unsigned char enabled;
    unsigned char flag5;
    unsigned char flag6;
    int fields[8];
};

extern "C" {
extern int g_localPcbRole;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_roundIndex;
extern int g_ccClass;
extern unsigned char lbl_806D12B0;
extern unsigned char lbl_806D1264[3];
extern int lbl_806D1A30;
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
void *Alloc(unsigned long size);
FlowMgrInfo *fn_801FE404(void);
void fn_801FE584(FlowMgrInfo *mgr);
CardConfig *fn_8024F588(FlowMgrInfo *mgr);
DispFlags *fn_801DAEC0(void);
void fn_801DABFC(void);
void fn_801DAE54(void);
void fn_8011FAB8(void);
void fn_8011F86C(void);
void fn_80121210(void);
void fn_80218F1C(void);
void ServiceMode_UpdateScheduleGate(void);
void SetLocalPcbRole(int role);
void *StrPcb_GetInstance(void);
void StrPcb_ForceRun_Neutral(void *pcb);
void StrPcb_ResetCommands_Neutral(void *pcb, int mode);
void Frame_PostDrawOverlay(void);
void Frame_UpdatePerFrameState(void);
void DemoFlow_ResetTwoFlags(void);
void OperationClock_Commit(void);
void RaceFlow_ResetState_FullColdInit(void);
SceneBase *fn_8014F6A4(void);
CardMenuRoot *fn_8020C7F4(void);
void CGameCoin_ProcessInput(InputState *in);
void SetReverseRoundFlag(int flag);
void clRom_DumpListOverlay(void);
unsigned char fn_8019083C(int slot);
void fn_801909A4(int slot);
void ClSound_PlayBgmStream(int slot, int id);
int fn_801932F8(void);
void clStream_setVolume(int slot, int vol);
}

static inline void CreateInputState() {
    InputImpl *p = (InputImpl *)Alloc(0x28);
    if (p != 0) {
        p->vt = lbl_803FDF28;
        g_pInputState = (InputState *)p;
        p->vt = lbl_803FDF40;
        p->enabled = 0;
        p->flag5 = 1;
        p->flag6 = 1;
        p->fields[0] = 0;
        p->fields[1] = 0;
        p->fields[2] = 0;
        p->fields[3] = 0;
        p->fields[4] = 0;
        p->fields[5] = 0;
        p->fields[6] = 0;
        p->fields[7] = 0;
    }
}

struct CardModeRoot : MenuModeBase, FlowSceneHost {
    SceneBase *task;
    int state;
    CardModeRoot();
    ~CardModeRoot();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    void OnTaskDone(int st);
    void StartTask(int st);
};

void CardModeRoot::OnTaskDone(int st) {
    if (task != 0) {
        if (st == 3) {
            CardMenuRoot *menu = dynamic_cast<CardMenuRoot *>(task);
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
        CGameCoin_ProcessInput(in == 0 ? (InputState *)0 : in);
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
    fn_801DAEC0();
    fn_801DABFC();
}

void CardModeRoot::Destroy() {
    delete this;
}

extern "C" CardModeRoot *fn_8020CEAC(void) {
    return new CardModeRoot;
}

CardModeRoot::~CardModeRoot() {
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

CardModeRoot::CardModeRoot() : task(0), state(0) {
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
            int v;
            state = 3;
            v = 1;
            if (cfg->f02) {
                v = 2;
            }
            lbl_806D1A30 = v;
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
