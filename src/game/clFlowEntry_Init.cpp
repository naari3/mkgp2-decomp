/* Entry flow constructor: resets per-flow state and drops the input state. */
class InputView {
public:
    virtual ~InputView();
};

struct FlowBase {
    void *vt;
    FlowBase();
    ~FlowBase();
};

struct EntryFlow : FlowBase {
    int timer;
    int next;
    char pad_C[4];
    int unk10;

    EntryFlow();
};

extern "C" {
extern InputView *g_pInputState;
extern void *lbl_8049A234[];
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

static inline InputView *input_state() {
    if (g_pInputState == 0) {
        return 0;
    }
    return g_pInputState;
}

EntryFlow::EntryFlow() {
    vt = lbl_8049A234;
    lbl_806D1193 = 1;
    SetSyncTarget(2);
    unk10 = fn_80124064();
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
    delete g_pInputState;
    g_pInputState = 0;
}
