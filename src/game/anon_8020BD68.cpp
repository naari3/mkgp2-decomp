/*
 * 0x8020BD68..0x8020C650: grand prix menu scene (same menuFactory state
 * machine as the battle menu, plus the class / cup preselect).
 */

#include "game/FlowScene.h"

/* Scene object with a done flag (base vtable lbl_803FE0C8). */
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
    int pad168;
    int mode;
    char pad170[0x197 - 0x170];
    unsigned char ccSelected;
};

struct PlayerData {
    char pad000[0x19D];
    unsigned char hasCard;
    char pad19E[0x1B8 - 0x19E];
    unsigned char chara;
};

struct SyncSlot {
    unsigned char kind : 5;
    unsigned char rest : 3;
};

struct InputImpl {
    void *vt;
    unsigned char enabled;
    unsigned char flag5;
    unsigned char flag6;
    int fields[8];
};

extern "C" {
extern PlayerData g_playerData;
extern int g_ccClass;
extern int g_gameMode;
extern int g_cupId;
extern int lbl_806D1A30;
void card_force_backup_now(void);
unsigned char fn_801D5C88(PlayerData *pd, int ccClass);
void fn_801FE3B4(FlowMgrInfo *mgr, int cup);
int fn_80202A5C(int sel);
extern const char lbl_803C3544[];
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
void *Alloc(unsigned long size);
void DebugPrintf(const char *fmt, ...);
SyncSlot *SyncSlot_GetRecv(void);
SyncSlot *SyncSlot_GetHostSend(void);
void ClSound_PlayBgmStream(int slot, int id);
int fn_801932F8(void);
void clStream_setVolume(int slot, int vol);
void fn_80202A24(void);
void fn_80202BCC(void);
void fn_80202C34(int arg);
int fn_80202B48(int cur);
FlowTask *fn_80201A48(int arg);
void fn_802043B8(FlowSceneList *list, int id);
int fn_8020A788(FlowFaderI *t);
void fn_8020A7CC(FlowFaderI *t, int from, int to, short dur);
FlowMgrInfo *fn_801FE404(void);
void fn_801FE554(FlowMgrInfo *mgr, PlayerData *pd);
SceneBase *fn_801FA024(void);
SceneBase *fn_801F3914(int chara, int arg);
SceneBase *fn_8015B6D0(void);
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
unsigned char Sci2Card_GetByteFlag1224(void);
int Sci2Card_GetUnpackStatusCode(void);
}

static inline void SetCC(bool on) {
    FlowMgrInfo *m = fn_801FE404();
    m->ccSelected = on;
}

static inline void SetMode(int mode) {
    fn_801FE404()->mode = mode;
}

static inline void SetCup(int cup) {
    if (cup < 1) {
        cup = 1;
    }
    while (cup >= 9) {
        cup -= 8;
    }
    fn_801FE3B4(fn_801FE404(), cup);
}

struct GrandPrixMenu : SceneBase {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fade;
    SceneBase *task;
    int state;
    int unk18;
    GrandPrixMenu();
    ~GrandPrixMenu();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
    void OnTaskDone(int st);
    void Factory() {
        int chara;
        int mode;
        int id = state;
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
};

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

GrandPrixMenu::GrandPrixMenu() : list(new SceneListImpl), fade(new FlowFaderI), task(0), state(0) {
    FlowSceneList *l;
    fn_80202C34(0);
    fn_80202B48(0);
    switch (lbl_806D1A30) {
    case 1:
        state = 0xB;
        SetMode(g_gameMode);
        break;
    case 2: {
        state = 0xB;
        int cup = g_gameMode;
        fn_801FE404()->mode = cup;
        cup = g_cupId;
        if (cup < 1) {
            cup = 1;
        }
        while (cup >= 9) {
            cup -= 8;
        }
        fn_801FE3B4(fn_801FE404(), cup);
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
    l = list.p;
    fn_801F4DF0(l, fn_80201A48(0), 2);
    Factory();
}
