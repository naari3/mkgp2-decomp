class InputPlayer {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual unsigned char IsHeld(int mask);
    virtual unsigned char IsPressed(int mask);
};

extern "C" unsigned char CreditMgr_TryConfirmPlay(int);
extern "C" void *GetInputManager(void);
extern "C" InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
extern "C" float PcbSyncTable_GetMyValue(void);
extern "C" unsigned char PcbSync_AnyJoinedPcbHasReadyFlagBit1(void);
extern "C" int PcbSync_AnyPeerAtState5(void);
extern "C" int PcbSync_CountJoinedPcbsAdvancedKarts(void);
extern "C" void SetLocalPcbRole(int);
extern "C" void SetSyncTarget(int);
extern "C" void SetTimerModeEnabled(int);
extern int g_gameMode;
extern unsigned char lbl_806D117C;
extern signed char lbl_806D12B0;
extern const float lbl_806D9878;

struct EntryWait {
    char pad_0[4];
    int timer;
    int next;
};

extern "C" int fn_801B76C8(EntryWait *self) {
    unsigned char ready;
    InputPlayer *player;
    unsigned char confirmed;

    if (self->next != -1) {
        return self->next;
    }
    ready = 0;
    if (PcbSync_AnyJoinedPcbHasReadyFlagBit1() && PcbSyncTable_GetMyValue() > lbl_806D9878) {
        ready = 1;
    }
    player = InputMgr_GetPlayer(GetInputManager(), 0);
    confirmed = 0;
    if (lbl_806D117C == 1) {
        if (player->IsHeld(0x2100) && CreditMgr_TryConfirmPlay(0)) {
            confirmed = 1;
        }
    } else if (CreditMgr_TryConfirmPlay(0)) {
        confirmed = 1;
    }
    if (confirmed) {
        lbl_806D12B0 = 1;
        if (player->IsPressed(0x400) || PcbSync_CountJoinedPcbsAdvancedKarts() == 1) {
            g_gameMode = 0;
            SetTimerModeEnabled(0);
            self->next = 9;
        } else {
            SetSyncTarget(7);
            SetLocalPcbRole(1);
            self->next = 7;
        }
    } else if (self->timer == 0) {
        if (ready) {
            self->next = 6;
        } else if (PcbSync_AnyPeerAtState5()) {
            self->next = 0x30;
        }
    } else {
        self->timer--;
    }
    return self->next;
}
