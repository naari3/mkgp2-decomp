#include "game/types/clMnCardT02.h"
struct CardInput {
    virtual void v0(); virtual void v1(); virtual float v2();
    virtual void v3(); virtual float v4(); virtual float v5();
    virtual unsigned char Pressed(int);
};
struct CardMode { int pad[2]; int light; };
extern "C" {
extern const int lbl_806DA860;
void *GetInputManager();
CardInput *InputMgr_GetPlayer(void *, int);
CardMode *fn_801DAEC0();
void fn_80203EA0();
void fn_8020A7CC(FlowFaderI *, int, int, int);
int fn_80203E30();
}
extern "C" {
extern unsigned char lbl_806D19C0;
extern int lbl_806D19C4;
/* fakematch: natural decl is `extern int lbl_806D19C8[2];` (written by
 * anon_801FD320.cpp). The const view lets the scheduler hoist the fade
 * duration load above the `subState = N` store, as in the target
 * (fn_801FCBCC, fn_801FCD9C). */
extern const int lbl_806D19C8[2];
extern unsigned char g_playerData[];
extern int g_currentSceneState;
void fn_80203F5C(int);
void card_save_trigger(int);
unsigned char CardSave_Tick();
int Sci2Card_GetPrintErrorCode();
int fn_801FDA78(int);
int fn_801FDCA8(int);
void fn_80203E4C();
void fn_802078B4();
int CardRW_GetSubState();
void card_eject_init();
unsigned char card_eject_state_machine();
void fn_801D7610(void *, int);
unsigned char fn_80207C64();
int fn_801FE858(CardInput *);
void fn_80207CC4(int);
int CreditMgr_GetPlayState(int);
int CreditMgr_GetCreditCount(int);
unsigned char CreditMgr_TryConfirmPlay(int);
void fn_801FE348();
void fn_801FE390();
void fn_801FE3BC();
void fn_801FE404();
void fn_801FE27C(int);
void PlayerData_ResetForFlow();
void fn_80207B28(int);
unsigned char Sci2Card_GetReceiptTestFlag();
void fn_80207AD8(int, int);
void fn_802078F8();
unsigned char fn_80207880();
}

static inline unsigned char CardCreditUnavailable(clMnCardT02 *self) {
    if (CreditMgr_GetPlayState(0) == 3) return 1;
    if (CreditMgr_GetCreditCount(self->slot) == 0) return 1;
    return 0;
}

void clMnCardT02::Finish() {
    delete this;
}

clMnCardT02::clMnCardT02(int arg, int base) : clMnCardT0Interface(base) {
    kind = 5;
    arg2C = arg;
    field30 = 0;
    coins = CreditMgr_GetCoinCount(0, -1);
    field38 = 1;
    slot = 3;
    field40 = 0;
    field41 = 0;
    field44 = 0;
    state = 0;
    subState = 0;
    timer = 0x4B1;
    CreditMgr_SetActiveSlot(slot);
}

clMnCardT02::~clMnCardT02() {
    CreditMgr_SetActiveSlot(0);
}

void clMnCardT02::Select() {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char promptActive = fn_80207C64();
    int previous = this->cursor;
    this->cursor += fn_801FE858(input);
    int selected = this->cursor;
    if (selected < 0) this->cursor = 0;
    if (selected > 1) this->cursor = 1;
    fn_80207CC4(this->cursor);
    int coins = CreditMgr_GetCoinCount(0, -1);
    if (this->coins != coins) this->timer = 1201;
    this->coins = coins;
    unsigned char unavailable = CardCreditUnavailable(this);
    if (unavailable && this->field41 != unavailable && !this->field40 && this->cursor > 0) {
        fn_8020A7CC(this->fader.p, 0, 15, 15);
        this->field40 = 1;
        this->state = 6;
        this->kind = 5;
    }
    if (input->Pressed(lbl_806DA860)) {
        if (this->cursor == 0) {
            fn_801FE348();
            if (CreditMgr_TryConfirmPlay(this->slot)) {
                this->state = 9;
                this->subState = 4;
            } else {
                if (this->field38) {
                    this->field38 = 0;
                    this->timer = 1201;
                }
                if (!promptActive) fn_80207B28(1);
            }
        } else {
            fn_801FE348();
            PlayerData_ResetForFlow();
            fn_801FE3BC();
            fn_801FE404();
            lbl_806D19C0 = 0;
            this->state = 8;
            this->subState = 0;
        }
    }
    if (this->timer > 0) --this->timer;
    fn_801FE27C(this->timer);
    if (previous != this->cursor) fn_801FE390();
    if (this->timer <= 0) {
        PlayerData_ResetForFlow();
        fn_801FE3BC();
        fn_801FE404();
        if (this->cursor == 0) {
            fn_8020A7CC(this->fader.p, 0, 15, 15);
            this->state = 7;
            this->kind = 8;
            this->subState = 0;
        } else {
            fn_801FE348();
            this->state = 8;
            this->subState = 0;
        }
        lbl_806D19C0 = 0;
    }
    this->field41 = unavailable;
}

void clMnCardT02::Eject() {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (this->subState) {
    case 0:
        if (fn_80203E30() == -1) {
            this->subState = 1;
            fn_8020A7CC(this->fader.p, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
            if (lbl_806D19C0 == 1) fn_80203F5C(20);
            else fn_80203F5C(1);
            card_eject_init();
            fn_801D7610(g_playerData, 1);
        }
        break;
    case 1:
        if (card_eject_state_machine()) {
            switch (fn_801FDCA8(Sci2Card_GetPrintErrorCode())) {
            case 0:
                fn_8020A7CC(this->fader.p, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
                this->subState = 2;
                break;
            case 6: case 7:
                fn_80203E4C();
                fn_802078B4();
                this->state = -1;
                break;
            }
        }
        break;
    case 2:
        this->fader.p->Step();
        if (input->Pressed(lbl_806DA860) || this->fader.p->b >= this->fader.p->a) {
            fn_80203EA0();
            this->subState = 3;
        }
        break;
    case 3:
        if (fn_80203E30() == -1) this->subState = 7;
        break;
    case 7:
        this->state = 10;
        this->subState = 8;
        break;
    }
}

void clMnCardT02::Save() {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (this->subState) {
    case 4:
        if (fn_80203E30() == -1) {
            card_save_trigger(1);
            fn_80203F5C(8);
            this->subState = 5;
            lbl_806D19C0 = 1;
            lbl_806D19C4 = 0;
        }
        break;
    case 5:
        if (CardSave_Tick()) {
            switch (fn_801FDA78(Sci2Card_GetPrintErrorCode())) {
            case 0:
                this->subState = 6;
                fn_8020A7CC(this->fader.p, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
                break;
            case 6: case 7:
                fn_80203E4C();
                fn_802078B4();
                this->state = -1;
                break;
            }
        } else {
            if (lbl_806D19C4 == 0) {
                if (CardRW_GetSubState() == 1) {
                    fn_80203F5C(1);
                    lbl_806D19C4 = 1;
                }
            } else if (lbl_806D19C4 == 1) {
                if (CardRW_GetSubState() == 2) {
                    fn_80203E4C();
                    lbl_806D19C4 = 2;
                }
            }
        }
        break;
    case 6:
        this->fader.p->Step();
        if (input->Pressed(lbl_806DA860) || this->fader.p->b >= this->fader.p->a) {
            fn_80203EA0();
            this->subState = 7;
        }
        break;
    case 7:
        if (fn_80203E30() == -1) {
            this->state = 10;
            this->subState = 8;
        }
        break;
    }
}

void clMnCardT02::Update() {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int state = this->state;
    if (state != 1 && state != 8) {
        if (input->Pressed(lbl_806DA860)) this->field44 = 10;
        if (this->field44 > 0) {
            --this->field44;
            { CardMode *mode = fn_801DAEC0(); mode->light = 4; }
        } else {
            { CardMode *mode = fn_801DAEC0(); mode->light = 1; }
        }
    }
    switch (state) {
    case 0:
        if (this->arg2C == 1) {
            if (!g_playerData[0x1A0]) {
                this->slot = 3;
                fn_80203F5C(6);
            } else {
                this->slot = 4;
                fn_80203F5C(27);
            }
        } else {
            if (!g_playerData[0x1A0]) {
                this->slot = 3;
                fn_80203F5C(7);
            } else {
                this->slot = 4;
                fn_80203F5C(26);
            }
        }
        CreditMgr_SetActiveSlot(this->slot);
        fn_8020A7CC(this->fader.p, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
        this->state = 1;
        break;
    case 1:
        if (input->Pressed(lbl_806DA860)) { CardMode *mode = fn_801DAEC0(); mode->light = 0; }
        else { CardMode *mode = fn_801DAEC0(); mode->light = 1; }
        this->fader.p->Step();
        if (this->fader.p->b >= this->fader.p->a || input->Pressed(lbl_806DA860)) {
            if (Sci2Card_GetReceiptTestFlag()) {
                fn_80203F5C(10);
                fn_8020A7CC(this->fader.p, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
                this->field30 = 180;
                this->state = 2;
            } else {
                fn_80203EA0();
                this->state = 3;
            }
        }
        break;
    case 2:
        if (input->Pressed(lbl_806DA860)) { CardMode *mode = fn_801DAEC0(); mode->light = 0; }
        else { CardMode *mode = fn_801DAEC0(); mode->light = 1; }
        this->fader.p->Step();
        if (this->field30 != 0) --this->field30;
        else if (this->fader.p->b >= this->fader.p->a || input->Pressed(lbl_806DA860)) {
            fn_80203EA0();
            PlayerData_ResetForFlow();
            fn_801FE3BC();
            fn_801FE404();
            lbl_806D19C0 = 0;
            this->state = 8;
            this->subState = 0;
        }
        break;
    case 3:
        if (fn_80203E30() == -1) {
            if (g_currentSceneState < 44) {
                if (this->slot == 3) fn_80207AD8(10, 1);
                else fn_80207AD8(12, 1);
            } else {
                if (this->slot == 3) fn_80207AD8(2, 1);
                else fn_80207AD8(11, 1);
            }
            fn_8020A7CC(this->fader.p, 0, 30, 30);
            this->state = 4;
        }
        break;
    case 4:
        this->fader.p->Step();
        if (this->fader.p->b >= this->fader.p->a) {
            int coins = CreditMgr_GetCoinCount(0, -1);
            if (this->coins != coins) this->timer = 1201;
            this->coins = coins;
            this->field41 = CardCreditUnavailable(this);
            this->state = 5;
        }
        break;
    case 5:
        Select();
        break;
    case 6:
        fn_80207CC4(0);
        this->fader.p->Step();
        if (this->fader.p->b >= this->fader.p->a) {
            this->cursor = 0;
            fn_801FE348();
            this->state = this->kind;
        }
        break;
    case 7:
        fn_80207CC4(1);
        this->fader.p->Step();
        if (this->fader.p->b >= this->fader.p->a) {
            this->cursor = 1;
            fn_801FE348();
            this->state = this->kind;
        }
        break;
    case 8:
        { CardMode *mode = fn_801DAEC0(); mode->light = 0; }
        Eject();
        break;
    case 9:
        Save();
        break;
    case 10:
        fn_802078F8();
        this->state = 11;
        break;
    case 11:
        if (list.p->entries.count <= 0 && !fn_80207880()) {
            this->field0C = 1;
            this->state = -1;
        }
        break;
    }
    list.p->Update();
}

void clMnCardT02::Draw() {
    list.p->Draw();
}
