#include "game/types/clFlowProcess.h"
#include "game/singleton.h"

struct InputView {
    void *vt;
    unsigned char enabled;
    unsigned char flag5;
    unsigned char flag6;
    char pad_7;
    int fields[8];
};

class SceneChild {
public:
    virtual void v8();
    virtual void vC();
    virtual ~SceneChild();
};

class InputOwner { public: virtual ~InputOwner(); };

extern "C" {
extern InputView *g_pInputState;
extern void *lbl_803FDF28[];
extern void *lbl_803FDF40[];
extern unsigned char lbl_806D1193;
void *Alloc(unsigned long size);
void MemoryManager_TimedFree(void *p);
void RaceFlow_ResetState_FullColdInit(void);
void RaceSlot_ResetAll(void);
void *StrPcb_GetInstance(void);
void StrPcb_ForceRun_Neutral(void *pcb);
void StrPcb_ResetCommands_Neutral(void *pcb, int arg);
void fn_80121210(void);
}

static inline InputView *input_state() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline void CreateInputState() {
    InputView *p = (InputView *)Alloc(0x28);
    if (p != 0) {
        p->vt = lbl_803FDF28;
        g_pInputState = p;
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

extern "C" {
extern unsigned char lbl_806D117C;
extern unsigned char lbl_806D1193;
extern unsigned char lbl_806D12B0;
extern unsigned char lbl_806D17F0;
extern unsigned char lbl_806D17F1;
extern unsigned char lbl_806D17F2;
int CreditMgr_GetCreditCount(int arg);
void PlayerData_ResetForFlow(void);
void SetCardVolumeFlagByte(int arg);
void SetLocalPcbRole(int role);
void SetSyncTarget(int target);
void *StrPcb_GetInstance(void);
void StrPcb_ResetCommands_NeutralDefault(void *pcb);
void StrPcb_ResetCommands_Zero(void *pcb, int arg);
int fn_80124064(void);
}

class clFlowTitle : public clFlowProcess {
public:
    clFlowTitle();
    virtual ~clFlowTitle();
    virtual int Update();
    virtual void Draw();
    int timer;
    int next;
    char pad_C[4];
    SceneChild *child;
};

clFlowTitle::clFlowTitle() {
    lbl_806D1193 = 1;
    SetSyncTarget(2);
    child = (SceneChild *)fn_80124064();
    next = -1;
    timer = 0xF;
    SetLocalPcbRole(0);
    lbl_806D12B0 = 0;
    PlayerData_ResetForFlow();
    SetCardVolumeFlagByte(0);
    lbl_806D17F0 = 0;
    lbl_806D17F1 = 0;
    lbl_806D17F2 = 0;
    lbl_806D117C = CreditMgr_GetCreditCount(0) <= 0;
    if (input_state()) {
        StrPcb_ResetCommands_Zero(StrPcb_GetInstance(), 1);
        StrPcb_ResetCommands_NeutralDefault(StrPcb_GetInstance());
    }
    delete (InputOwner *)g_pInputState;
    g_pInputState = 0;
}

clFlowTitle::~clFlowTitle() {
    if (child != 0) {
        delete child;
    }
    RaceFlow_ResetState_FullColdInit();
    RaceSlot_ResetAll();
    if (input_state() == 0) {
        CreateInputState();
    }
    StrPcb_ForceRun_Neutral(StrPcb_GetInstance());
    StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
    fn_80121210();
    lbl_806D1193 = 0;
}

extern "C" int fn_801B76C8(void *self);

int clFlowTitle::Update() {
    if (child != 0) {
        child->v8();
    }
    return fn_801B76C8(this);
}

void clFlowTitle::Draw() {
    if (child != 0) {
        child->vC();
    }
}
