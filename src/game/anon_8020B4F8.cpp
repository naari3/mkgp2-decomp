/*
 * 0x8020B4F8..0x8020BD68: battle menu scene (menuFactory state machine that
 * spawns the card / character select sub scenes and fades the screen).
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
};

struct PlayerData {
    char pad000[0x1B8];
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
void fn_8011FAB8(void);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
unsigned char Sci2Card_GetByteFlag1224(void);
int Sci2Card_GetUnpackStatusCode(void);
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

struct BattleMenu : SceneBase {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fade;
    SceneBase *task;
    int state;
    bool bgmStarted;
    BattleMenu();
    ~BattleMenu();
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
            DebugPrintf(lbl_803C3544, id, mode, chara);
            switch (id) {
            case 0:
            case 2:
            case 3:
            case 4:
            case 5:
            case 11:
            case 12:
                break;
            case 1:
                task = fn_801FA024();
                break;
            case 7:
                if (fn_8020A788(fade.p) == 0xFF) {
                    fn_8020A7CC(fade.p, 0, 0, 1);
                    task = fn_801F3914(chara, 1);
                }
                break;
            default:
                task = 0;
                break;
            }
        }
    }
};

void BattleMenu::Draw() {
    list.p->Draw();
    if (task != 0) {
        task->Draw();
    }
    fn_8011FAB8();
}

void BattleMenu::Update() {
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

void BattleMenu::OnTaskDone(int st) {
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

void BattleMenu::Destroy() {
    delete this;
}

extern "C" BattleMenu *fn_8020B994(void) {
    return new BattleMenu;
}

BattleMenu::~BattleMenu() {
    fn_801F4D3C(list.p);
    fn_80202BCC();
}

BattleMenu::BattleMenu() : list(new SceneListImpl), fade(new FlowFaderI), task(0), state(0) {
    FlowSceneList *l;
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
    l = list.p;
    fn_801F4DF0(l, fn_80201A48(0), 2);
    Factory();
}
