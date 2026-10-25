class InputPlayer {
public:
    virtual ~InputPlayer();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void *IsPressed(int mask);
};

struct CardReader {
    char pad00[0x10];
    int stage;
    char pad14[4];
    int result;
    int GetResult() {
        if (stage < 2) {
            return 2;
        }
        return result;
    }
};

struct EntryScene {
    void *vt;
    unsigned char done;
    unsigned char cardMode;
    unsigned char cardDone;
    char pad07[9];
    int next;
    char pad14[8];
    CardReader *reader;
};

extern "C" {
extern int g_gameMode;
extern const float lbl_806D9960;
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
int CountPeersWithRole(int role);
int PcbSync_CountJoinedPcbsAdvancedKarts(void);
float PcbSyncTable_GetMyValue(void);
void fn_80161888(void);
void SetTimerModeEnabled(int enable);
void SetLocalPcbRole(int role);
void SetRumbleMode(int a, int b, int c);
void SetPcbScratchFlag_806d11a4(void);
}

extern "C" int fn_801BA1A4(EntryScene *self) {
    InputPlayer *pad;
    int peers;

    if (self->next != -1) {
        return self->next;
    }
    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    peers = CountPeersWithRole(1);
    if (PcbSync_CountJoinedPcbsAdvancedKarts() <= peers) {
        self->done = 1;
    } else if (PcbSyncTable_GetMyValue() <= lbl_806D9960) {
        self->done = 1;
    } else if (self->cardMode && !self->cardDone) {
        if (self->reader->GetResult() == 1) {
            fn_80161888();
            self->cardDone = 1;
        } else if (self->reader->GetResult() == 0) {
            fn_80161888();
            self->cardDone = 1;
            g_gameMode = 0;
            SetTimerModeEnabled(0);
            SetLocalPcbRole(0);
            self->next = 9;
        }
    } else if (pad->IsPressed(0x2000) != 0) {
        SetRumbleMode(0, 1, 1);
        SetPcbScratchFlag_806d11a4();
    }
    return self->next;
}
