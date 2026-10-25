/* Card cleaning prompt: yes/no cursor, then runs the cleaning sequence. */
struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

struct CardCleanScene {
    char pad0[0x10];
    void *seq;
    void *fader;
    int state;
    int pad1C;
    int timer;
    int cursor;
    int pad28;
    int retries;
};

extern "C" {
extern const int lbl_806DA860;
extern const int lbl_803BFF54[];
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int idx);
unsigned char fn_80207C64(void);
int fn_80203E30(void);
int fn_801FE858(InputPlayer *input);
void fn_80207CC4(int sel);
unsigned char card_cleaning_state_machine(void);
void fn_801FE348(void);
void fn_80207B28(int arg);
int Sci2Card_GetPrintErrorCode(void);
int fn_801FE030(int code, int flag);
void fn_80203EA0(void);
void fn_801F4D3C(void *seq);
void fn_80203E4C(void);
void fn_802078B4(void);
void fn_801FE390(void);
}

extern "C" void fn_801FB418(CardCleanScene *self) {
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char busy = fn_80207C64();
    int prev = self->cursor;
    unsigned char done;
    int retry;

    if (fn_80203E30() == -1) {
        self->cursor += fn_801FE858(input);
    }
    if (self->cursor < 0) {
        self->cursor = 0;
    } else if (self->cursor > 1) {
        self->cursor = 1;
    }
    fn_80207CC4(self->cursor);
    done = card_cleaning_state_machine();
    if (input->Pressed(lbl_806DA860)) {
        if (self->cursor == 1) {
            self->state = 3;
            done = 0;
        } else if (!busy) {
            if (self->retries < 1) {
                self->retries++;
                self->timer = lbl_803BFF54[0] + 1;
            }
            fn_801FE348();
            fn_80207B28(1);
        }
    }
    if (done == 1) {
        retry = 1;
        if (self->timer <= 1) {
            retry = 0;
        }
        switch (fn_801FE030(Sci2Card_GetPrintErrorCode(), retry)) {
        case 0:
            fn_80203EA0();
            fn_80207CC4(0);
            self->cursor = 0;
            fn_801FE348();
            self->state = 7;
            break;
        case 6:
        case 7:
            fn_801F4D3C(self->seq);
            fn_80203E4C();
            fn_802078B4();
            self->state = -1;
            break;
        case 9:
            break;
        }
    }
    if (prev != self->cursor) {
        fn_801FE390();
    }
    if (self->timer <= 0) {
        self->state = 3;
    }
}
