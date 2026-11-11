/* clMnCardT00 card read/print/cleaning task; RTTI and vtable emitted by C++. */
#include "game/types/size_t.h"
#include "game/types/InputPlayer.h"
#include "game/types/PcbMode.h"
void *operator new(size_t);
void operator delete(void *) throw();
struct Fader { int unk0; short duration, time; };
struct CardSeq {
    virtual void v8(); virtual void Tick(); virtual void Draw();
    int count;
};
struct CardInfo { int unk0, printCount; };
struct clYTaskInterface {
    virtual ~clYTaskInterface();
    int id, field08, done;
};
struct clMnTaskInterface : clYTaskInterface {
    virtual ~clMnTaskInterface();
    virtual void Finish(); virtual void Update(); virtual void Draw();
};
struct clMnCardT0Interface : clMnTaskInterface {
    clMnCardT0Interface(int);
    virtual ~clMnCardT0Interface();
    CardSeq *seq; Fader *fader;
    int state, result, timeout, active;
};
extern "C" const int lbl_803BFF40[];
struct clMnCardT00 : clMnCardT0Interface {
    clMnCardT00(int arg) : clMnCardT0Interface(arg), kind(2), retries(0), reading(0), flash(0) {
        state = 0; result = 0; timeout = lbl_803BFF40[0] + 1;
    }
    virtual ~clMnCardT00();
    virtual void Finish(); virtual void Update(); virtual void Draw();
    void PrintCard(); void CleanCard();
    int kind, retries; unsigned char reading; char pad31[3]; int flash;
};
extern "C" {
extern unsigned char lbl_806D14A0;
void fn_80207AD8(int, int);
void fn_80207760(int);
void card_send_cleaning_cmd_init();
unsigned char card_cleaning_state_machine();
int Sci2Card_GetPrintErrorCode();
int fn_801FE030(int, int);
void fn_80207CC4(int);
void fn_801FE348();
void fn_801F4D3C(void *);
void fn_80203E4C();
void fn_802078B4();
void card_send_ping_cmd_init();
unsigned char card_ping_state_machine();
int fn_801FDF20();
void Sci2Card_ResetRetryAndStatus();
unsigned char Sci2Card_GetByteFlag1224();
void card_send_read_cmd_init();
void fn_802078F8();
unsigned char fn_80207880();
int Sci2Card_PollResponseStatusTri();
void fn_801FE27C(int);
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
int fn_801FDDA4(int code);
int fn_801FDCA8(int code);
CardInfo *fn_801FE404(void);
void fn_801FE588(CardInfo *info);
void fn_801FE584(CardInfo *info);
void DebugPrintf(const char *fmt, ...);
void PlayerData_ResetForFlow(void);
void fn_80203F5C(int id);
void fn_8020A7CC(Fader *f, int a, int b, int c);
void card_eject_init(void);
void fn_801D7610(void *data, int arg);
unsigned char card_eject_state_machine(void);
unsigned char fn_80207C64(void);
int fn_801FE858(InputPlayer *input);
void fn_80207B28(int arg);
void fn_801FE390(void);
}
static inline void FaderTick(Fader *f) {
    short d;
    f->time++; d = f->duration;
    if (f->time >= d) f->time = d;
}
static inline bool FaderDone(Fader *f) { return f->time >= f->duration; }
static inline void CardFadeTick(Fader *f) {
    f->time++;
    short d = f->duration;
    if (f->time >= d) f->time = d;
}

clMnCardT00::~clMnCardT00() {}

extern "C" clMnCardT00 *fn_801FB634(int arg) { return new clMnCardT00(arg); }

void clMnCardT00::Finish() { delete this; }

void clMnCardT00::CleanCard() {
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char busy = fn_80207C64();
    int prev = this->active;
    unsigned char done;
    int retry;

    if (fn_80203E30() == -1) {
        this->active += fn_801FE858(input);
    }
    if (this->active < 0) {
        this->active = 0;
    } else if (this->active > 1) {
        this->active = 1;
    }
    fn_80207CC4(this->active);
    done = card_cleaning_state_machine();
    if (input->Pressed(lbl_806DA860)) {
        if (this->active == 1) {
            this->state = 3;
            done = 0;
        } else if (!busy) {
            if (this->retries < 1) {
                this->retries++;
                this->timeout = lbl_803BFF54[0] + 1;
            }
            fn_801FE348();
            fn_80207B28(1);
        }
    }
    if (done == 1) {
        retry = 1;
        if (this->timeout <= 1) {
            retry = 0;
        }
        switch (fn_801FE030(Sci2Card_GetPrintErrorCode(), retry)) {
        case 0:
            fn_80203EA0();
            fn_80207CC4(0);
            this->active = 0;
            fn_801FE348();
            this->state = 7;
            break;
        case 6:
        case 7:
            fn_801F4D3C(this->seq);
            fn_80203E4C();
            fn_802078B4();
            this->state = -1;
            break;
        case 9:
            break;
        }
    }
    if (prev != this->active) {
        fn_801FE390();
    }
    if (this->timeout <= 0) {
        this->state = 3;
    }
}

void clMnCardT00::PrintCard() {
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int state = this->result;
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
            this->result = 1;
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
            this->result = 6;
            DebugPrintf("card read ok *************\n");
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
            fn_801F4D3C(this->seq);
            fn_80203E4C();
            fn_802078B4();
            this->state = -1;
            break;
        case 9:
            this->result = 0;
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
        fn_8020A7CC(this->fader, 0, 0x78, 0x78);
        this->result = 2;
        break;
    case 2:
        FaderTick(this->fader);
        if (input->Pressed(lbl_806DA860) || FaderDone(this->fader)) {
            card_eject_init();
            fn_801D7610(g_playerData, 1);
            fn_80203F5C(1);
            this->result = 3;
        }
        break;
    case 3:
        if (!card_eject_state_machine()) {
            break;
        }
        switch (fn_801FDCA8(Sci2Card_GetPrintErrorCode())) {
        case 0:
            fn_8020A7CC(this->fader, 0, 0x78, 0x78);
            this->result = 4;
            break;
        case 6:
        case 7:
            fn_801F4D3C(this->seq);
            fn_80203E4C();
            fn_802078B4();
            this->state = -1;
            this->result = 7;
            break;
        case 9:
            this->result = 3;
            break;
        }
        break;
    case 4:
        FaderTick(this->fader);
        if (input->Pressed(lbl_806DA860) || FaderDone(this->fader)) {
            fn_80203EA0();
            Sci2Card_ResetRetryAndStatus();
            if (fn_801FE404()->printCount < 3 && this->timeout > 1) {
                this->result = 5;
            } else {
                this->result = 6;
            }
        }
        break;
    case 5:
        if (fn_80203E30() == -1) {
            this->timeout = lbl_803BFF54[0] + 1;
            fn_80207760(1);
            card_send_cleaning_cmd_init();
            this->reading = 0;
            this->state = 2;
            this->result = 0;
        }
        break;
    case 6:
        if (fn_80203E30() == -1) {
            this->result = 7;
            fn_80203EA0();
            this->state = 9;
        }
        break;
    }
}

void clMnCardT00::Update() {
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int state = this->state;
    if (state != 7 && state != 8) {
        if (input->Pressed(lbl_806DA860)) this->flash = 10;
        if (this->flash > 0) {
            this->flash--;
            PcbMode *m = fn_801DAEC0(); m->light = 4;
        } else { PcbMode *m = fn_801DAEC0(); m->light = 1; }
    }
    switch (state) {
    case -1: break;
    case 0:
        fn_80207AD8(0, 1);
        if (lbl_806D14A0) fn_80207760(0);
        card_send_cleaning_cmd_init();
        fn_8020A7CC(this->fader, 0, 30, 30);
        this->state = 1;
        break;
    case 1:
        CardFadeTick(this->fader);
        if (this->fader->time >= this->fader->duration) this->state = 2;
        break;
    case 2: CleanCard(); break;
    case 3:
        if (card_cleaning_state_machine() == 1) {
            switch (fn_801FE030(Sci2Card_GetPrintErrorCode(), 0)) {
            case 0:
                fn_80203EA0(); fn_80207CC4(0); this->active = 0;
                fn_801FE348(); this->state = 7;
                break;
            case 6: case 7:
                fn_801F4D3C(this->seq); fn_80203E4C(); fn_802078B4(); this->state = -1;
                break;
            case 9:
                card_send_ping_cmd_init(); this->state = 4;
                break;
            case 8: break;
            }
        }
        break;
    case 4:
        if (card_ping_state_machine()) {
            switch (fn_801FDF20()) {
            default:
                fn_80207CC4(0); this->active = 0; fn_80203EA0();
                Sci2Card_ResetRetryAndStatus(); this->state = 8; this->result = 0;
                break;
            case 0:
                if (!Sci2Card_GetByteFlag1224()) {
                    if (this->active == 0) { fn_80207CC4(1); this->active = 1; }
                    fn_801FE348(); fn_80203EA0(); this->state = 9;
                } else {
                    fn_80207CC4(0); this->active = 0; fn_80203EA0(); this->state = 7;
                }
                break;
            case 6: case 7:
                fn_801F4D3C(this->seq); fn_80203E4C(); fn_802078B4(); this->state = -1;
                break;
            }
        }
        break;
    case 5:
        fn_80207CC4(0);
        CardFadeTick(this->fader);
        if (this->fader->time >= this->fader->duration) {
            this->active = 0; fn_801FE348(); this->state = this->kind;
        }
        break;
    case 6:
        fn_80207CC4(1);
        CardFadeTick(this->fader);
        if (this->fader->time >= this->fader->duration) {
            this->active = 1; fn_801FE348(); this->state = this->kind;
        }
        break;
    case 7:
        if (fn_80203E30() == -1) { PcbMode *m = fn_801DAEC0(); m->light = 4; }
        else { PcbMode *m = fn_801DAEC0(); m->light = 0; }
        this->reading = 1; card_send_read_cmd_init(); this->state = 8; this->result = 0;
        break;
    case 8: PrintCard(); break;
    case 9: fn_802078F8(); this->state = 10; break;
    case 10:
        if (this->seq->count <= 0 && !fn_80207880()) { this->done = 1; this->state = -1; }
        break;
    }
    if (this->state >= 2 && this->timeout > 0 && !this->reading) this->timeout--;
    if (this->timeout <= 0 && Sci2Card_PollResponseStatusTri() == 2) this->timeout = 1;
    fn_801FE27C(this->timeout);
    this->seq->Tick();
}

void clMnCardT00::Draw() { seq->Draw(); }
