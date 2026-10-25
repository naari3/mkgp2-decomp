/* Card print flow: reads the card, prints, ejects and handles print errors. */
struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

struct Fader {
    char pad0[4];
    short duration;
    short time;
};

struct PcbMode {
    char pad0[8];
    int light;
};

struct CardInfo {
    int unk0;
    int printCount;
};

extern "C" {
extern const int lbl_806DA860;
extern const char lbl_803BFCB8[];
extern const int lbl_803BFF54[];
extern unsigned char g_playerData[];
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
PcbMode *fn_801DAEC0(void);
unsigned char card_read_tick(void);
void fn_80203EA0(void);
void CardRegister_KickoffArm(void);
int fn_80203E30(void);
int Sci2Card_GetPrintErrorCode(void);
int fn_801FDDA4(int code);
int fn_801FDCA8(int code);
CardInfo *fn_801FE404(void);
void fn_801FE588(CardInfo *info);
void fn_801FE584(CardInfo *info);
void DebugPrintf(const char *fmt, ...);
void fn_801F4D3C(void *seq);
void fn_80203E4C(void);
void fn_802078B4(void);
void PlayerData_ResetForFlow(void);
void fn_80203F5C(int id);
void fn_8020A7CC(Fader *f, int a, int b, int c);
void card_eject_init(void);
void fn_801D7610(void *data, int arg);
unsigned char card_eject_state_machine(void);
void Sci2Card_ResetRetryAndStatus(void);
void fn_80207760(int arg);
void card_send_cleaning_cmd_init(void);
}

struct CardPrintScene {
    char pad0[0x10];
    void *seq;
    Fader *fader;
    int next;
    int state;
    int retry;
    char pad24[0xC];
    unsigned char cleaning;
};

static inline void FaderTick(Fader *f) {
    short d;

    f->time++;
    d = f->duration;
    if (f->time >= d) {
        f->time = d;
    }
}

static inline bool FaderDone(Fader *f) {
    return f->time >= f->duration;
}

extern "C" void fn_801FAFFC(CardPrintScene *self) {
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int state = self->state;
    int voices[8] = { 0x12, 0x13, 0x15, 0x16, 0xC, 0xD, 0xF, 0x10 };
    int voice;
    int sel;

    if (state != 0 && state != 1) {
        PcbMode *m = fn_801DAEC0();
        m->light = 0;
    } else {
        PcbMode *m = fn_801DAEC0();
        m->light = 4;
    }

    switch (state) {
    case 0:
        if (card_read_tick()) {
            fn_80203EA0();
            self->state = 1;
            CardRegister_KickoffArm();
        }
        break;
    case 1:
        if (fn_80203E30() != -1) {
            break;
        }
        sel = -1;
        switch (fn_801FDDA4(Sci2Card_GetPrintErrorCode())) {
        case 0:
            fn_801FE588(fn_801FE404());
            fn_801FE584(fn_801FE404());
            self->state = 6;
            DebugPrintf(lbl_803BFCB8);
            break;
        case 1:
            sel = 0;
            break;
        case 2:
            sel = 1;
            break;
        case 3:
            sel = 2;
            break;
        case 4:
            sel = 3;
            break;
        case 6:
        case 7:
            fn_801F4D3C(self->seq);
            fn_80203E4C();
            fn_802078B4();
            self->next = -1;
            break;
        case 9:
            self->state = 0;
            break;
        }
        if (sel == -1) {
            break;
        }
        fn_801FE588(fn_801FE404());
        voice = voices[sel * 2];
        if (fn_801FE404()->printCount >= 3) {
            voice = voices[sel * 2 + 1];
        }
        PlayerData_ResetForFlow();
        fn_801FE584(fn_801FE404());
        fn_80203F5C(voice);
        fn_8020A7CC(self->fader, 0, 0x78, 0x78);
        self->state = 2;
        break;
    case 2:
        FaderTick(self->fader);
        if (input->Pressed(lbl_806DA860) || FaderDone(self->fader)) {
            card_eject_init();
            fn_801D7610(g_playerData, 1);
            fn_80203F5C(1);
            self->state = 3;
        }
        break;
    case 3:
        if (!card_eject_state_machine()) {
            break;
        }
        switch (fn_801FDCA8(Sci2Card_GetPrintErrorCode())) {
        case 0:
            fn_8020A7CC(self->fader, 0, 0x78, 0x78);
            self->state = 4;
            break;
        case 6:
        case 7:
            fn_801F4D3C(self->seq);
            fn_80203E4C();
            fn_802078B4();
            self->next = -1;
            self->state = 7;
            break;
        case 9:
            self->state = 3;
            break;
        }
        break;
    case 4:
        FaderTick(self->fader);
        if (input->Pressed(lbl_806DA860) || FaderDone(self->fader)) {
            fn_80203EA0();
            Sci2Card_ResetRetryAndStatus();
            if (fn_801FE404()->printCount < 3 && self->retry > 1) {
                self->state = 5;
            } else {
                self->state = 6;
            }
        }
        break;
    case 5:
        if (fn_80203E30() == -1) {
            self->retry = lbl_803BFF54[0] + 1;
            fn_80207760(1);
            card_send_cleaning_cmd_init();
            self->cleaning = 0;
            self->next = 2;
            self->state = 0;
        }
        break;
    case 6:
        if (fn_80203E30() == -1) {
            self->state = 7;
            fn_80203EA0();
            self->next = 9;
        }
        break;
    }
}
