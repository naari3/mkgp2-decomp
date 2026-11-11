#include "game/types/clMnCardT01.h"
extern "C" void fn_8020A7CC(void *, int, int, int);

#include "game/singleton.h"
struct PanelText { TextManager *p; };
struct BuyMode { int pad[2]; int light; };
extern "C" {
extern const float lbl_806DA7F0, lbl_806DA7F4, lbl_806DA7F8, lbl_806DA7FC;
extern const int lbl_806DA848;
BuyMode *fn_801DAEC0();
PanelText *fn_80146000(void *, int);

void fn_801618CC(void *, int, int); void fn_80161888(void *);
unsigned char CardSave_Tick(); int Sci2Card_GetPrintErrorCode(); int fn_801FDB90(int);
int CreditMgr_GetPlayState(int); int CreditMgr_GetCreditCount(int); void CreditMgr_TryConfirmPlay(int);
void fn_801D919C(void *); int fn_80203E30();
void fn_8023CFC8(void *); void fn_80232284(ItemMsgWnd *, float);
void *fn_801F8E58(); void fn_801F8A34(void *, void *, int);
void fn_80160588(void *, int, int); void fn_8024E094(void *);
void fn_801D9B70(void *, unsigned char); void fn_8023CDA8(CoinPrompt *);
}
static inline void SetPanelTextPosition(TextManager *tm, float x, float y) {
    *(float *)((char *)tm + 0xC) = x;
    *(float *)((char *)tm + 0x10) = y;
}
static inline void PanelPosition(CardChoicePanel *p, float px, float py, float px2, float py2) {
    p->x = px; p->y = py; p->x2 = px2; p->y2 = py2;
    SetPanelTextPosition(fn_80146000(p->pad + 4, 0)->p, p->x, p->y);
    SetPanelTextPosition(fn_80146000(p->pad + 4, 1)->p, p->x2, p->y2);
    fn_801F93EC(fn_80146000(p->group50, 0)->p, p->x + p->offset[0], p->y + p->offset[1]);
    fn_801F93EC(fn_80146000(p->group50, 1)->p, p->x + p->offset[2], p->y + p->offset[3]);
    fn_801F93EC(fn_80146000(p->group50, 2)->p, p->x2 + p->offset[4], p->y2 + p->offset[5]);
    fn_801F93EC(fn_80146000(p->group50, 3)->p, p->x2 + p->offset[6], p->y2 + p->offset[7]);
    SetPanelTextPosition(p->center,
        p->x + 0.5f * (p->x2 - p->x),
        p->y + 0.5f * (p->y2 - p->y));
}
static inline void BuyFadeTick(FlowFaderI *f) { f->Step(); }
static inline void StepSaveFade(clMnCardT01 *self, InputState *input) {
    FlowFaderI *f = (FlowFaderI *)self->fader.p;
    BuyFadeTick(f);
    if (input->held == 1 || ((FlowFaderI *)self->fader.p)->Done()) {
        fn_801D919C(self->window.p);
        self->subState = 3;
    }
}
static inline void UpdateKart(void *kart) {
    InputState *input = SINGLETON_INSTANCE(g_pInputState);
    fn_801D9B70(kart, input->dir != 0);
}

extern "C" {
extern const int lbl_803BFF54[];
extern const float lbl_806DA81C, lbl_806DA800;

extern unsigned char g_playerData[];
int CreditMgr_GetCoinCount(int, int); int CreditMgr_GetPlayState(int);
int CreditMgr_GetCreditCount(int);
void fn_8024E1DC(void *); void fn_801618CC(void *, int, int);
void fn_80161888(void *); void fn_80232284(ItemMsgWnd *, float);
void fn_801FE27C(int); void fn_801FE390(); void fn_801FE348();
void *ItemDisplay_GetOrCreate(); void fn_8020AAD4(void *);
void fn_8023CFC8(void *); void card_save_trigger(int);
void fn_801D919C(void *); unsigned char fn_801D5F40(void *);
void clFlowKart_SetupTextLayout(void *, int);
}
static inline unsigned char IsCreditOnly() {
    if (CreditMgr_GetPlayState(0) == 3) return 1;
    if (CreditMgr_GetCreditCount(2) == 0) return 1;
    return 0;
}

clMnCardT01::clMnCardT01(int arg)
    : clMnCardT0Interface(arg), kind(2), field2C(0), field30(0), coins(CreditMgr_GetCoinCount(0, -1)),
      field3C(0), field40(0), counter(0), window(new CoinWindow),
      prompt(new CoinPrompt(0x74, 0x4A, 0x1874, 0x1875, 4)) {
    InputState *in;
    int jp;
    in = GetInput();
    in->enabled = 1;
    in->held = 0;
    int initialTimer = lbl_803BFF40[1];
    in->edge = 0;
    subState = 1;
    timer = initialTimer + 1;
    cursor = 0;
    state = 0;
    texts = new TextManager[3];
    texts[0].visible = 1;
    texts[1].visible = 1;
    texts[2].visible = 1;
    fn_801F93EC(&texts[0], lbl_806DA820, lbl_806DA824);
    fn_801F93EC(&texts[1], lbl_806DA820, lbl_806DA820);
    fn_801F93EC(&texts[2], lbl_806DA820, lbl_806DA828);
    jp = isJapanese() != 0;
    TexMgr_SetTexture(&texts[0], lbl_804EBF58[jp][0]);
    TexMgr_SetTexture(&texts[1], lbl_804EBF58[jp][1]);
    TexMgr_SetTexture(&texts[2], lbl_804EBF58[jp][2]);
    if (jp == 1) {
        texts[0].scale = lbl_806DA82C;
        texts[1].scale = lbl_806DA82C;
        texts[2].scale = lbl_806DA82C;
    }
    CreditMgr_SetActiveSlot(2);
    fn_80218D90(2);
    counter = new CoinCounter(2);
    fn_8023CEB4(prompt.p);
    fn_8023CD3C(prompt.p, lbl_806DA814, lbl_806DA818);
    fn_8023CCF8(prompt.p, lbl_806DA7EC, lbl_806DA7E8);
    fn_8023CD24(prompt.p, lbl_806DA810, lbl_806DA7E8);
    fn_8023CCCC(prompt.p, lbl_806DA7E4, lbl_806DA7E8);
    fn_8023CDA8(prompt.p);
    fn_8023CFD4(prompt.p);
    *((unsigned char *)window.p + 0x20) = 1;
}

clMnCardT01::~clMnCardT01() {
    fn_80232284(ItemMsg_Get(), lbl_806DA800);
    if (detail) {
        fn_80161F28(detail, 1);
    }
    fn_8024E244(counter, 1);
    delete[] texts;
    CreditMgr_SetActiveSlot(0);
    fn_80218D90(0);
    {
        BuyMode *mgr = fn_801DAEC0();
        mgr->light = 0;
    }
}


extern "C" clMnCardT01 *fn_801FC1E0(int arg) {
    return new clMnCardT01(arg);
}


void clMnCardT01::Finish() { delete this; }
void clMnCardT01::Select() {
    clMnCardT01 *self = this;
    InputState *input;
    unsigned char creditOnly;
    input = GetInput();
    int result;
    if (self->detail->state < 2) result = 2;
    else result = self->detail->result;
    bool ready = result == 0;
    int old = self->cursor;
    self->cursor += input->dir;
    int selection = self->cursor;
    if (selection < 0) self->cursor = 0;
    if (selection > 1) self->cursor = 1;
    int coins = CreditMgr_GetCoinCount(0, -1);
    if (self->coins != coins) self->timer = lbl_803BFF54[1] + 1;
    self->coins = coins;
    creditOnly = IsCreditOnly();
    if (creditOnly && self->field2C != creditOnly && !self->field3C && self->cursor > 0) {
        fn_8020A7CC(self->fader.p, 0, 15, 15);
        self->field3C = 1; self->state = 3; self->kind = 2;
    }
    if (input->held == 1) {
        if (self->cursor == 0) {
            if (creditOnly) {
                if (CreditMgr_GetCreditCount(2) <= 0) goto purchase;
            } else {
                fn_8024E1DC(self->counter); self->state = 5;
                if (!creditOnly && !ready) {
                    if (self->field30 < 1) {
                        self->field30++; self->timer = lbl_803BFF54[1] + 1;
                    }
                    fn_801618CC(self->detail, 0, 0);
                }
            }
        } else {
            self->state = 7; fn_80161888(self->detail);
        }
    }
    if (self->timer > 0) self->timer--;
    fn_80232284(ItemMsg_Get(), self->timer / lbl_806DA81C);
    fn_801FE27C(self->timer);
    if (old != self->cursor) fn_801FE390();
    if (self->timer <= 0) {
        if (self->cursor == 0) {
            fn_8020A7CC(self->fader.p, 0, 15, 15);
            self->state = 4; self->kind = 7; fn_80161888(self->detail);
        } else { fn_801FE348(); self->state = 7; fn_80161888(self->detail); }
    }
    self->field2C = creditOnly;
    return;
purchase:
    fn_8020AAD4(ItemDisplay_GetOrCreate());
    fn_80232284(ItemMsg_Get(), lbl_806DA800);
    fn_8023CFC8(self->prompt.p); fn_80161888(self->detail); fn_801FE348();
    self->state = 6; self->subState = 1;
    card_save_trigger(0);
    if (*(int *)self->window.p) fn_801D919C(self->window.p);
    if (fn_801D5F40(g_playerData) == 1) clFlowKart_SetupTextLayout(self->window.p, 1);
    else clFlowKart_SetupTextLayout(self->window.p, 0);
}

void clMnCardT01::FadeOut() {
    fn_801618CC(detail, 0, 0);
    fader.p->Step();
    if (fader.p->Done()) { cursor = 0; state = kind; }
}
void clMnCardT01::FadeIn() {
    fn_801618CC(detail, 1, 0);
    fader.p->Step();
    if (fader.p->Done()) { cursor = 1; state = kind; }
}

void clMnCardT01::Update() {
    clMnCardT01 *self = this;
    InputState *input = SINGLETON_INSTANCE(g_pInputState);
    if (input->held == 1) self->field40 = 10;
    if (self->field40 > 0) {
        self->field40--; BuyMode *m = fn_801DAEC0(); m->light = 4;
    } else { BuyMode *m = fn_801DAEC0(); m->light = 1; }
    switch (self->state) {
    case -1: break;
    case 0:
        self->detail = new CardChoicePanel(0, 0, 4);
        PanelPosition(self->detail, lbl_806DA7F0, lbl_806DA7F4, lbl_806DA7F8, lbl_806DA7F4);
        fn_8020A7CC(self->fader.p, 0, 30, 30); self->state = 1;
        break;
    case 1: {
        FlowFaderI *f = (FlowFaderI *)self->fader.p;
        BuyFadeTick(f);
        if (((FlowFaderI *)self->fader.p)->Done()) {
            int coins = CreditMgr_GetCoinCount(0, -1);
            if (self->coins != coins) self->timer = lbl_803BFF54[1] + 1;
            self->coins = coins;
            unsigned char credit;
            if (CreditMgr_GetPlayState(0) == 3) credit = 1;
            else if (CreditMgr_GetCreditCount(2) == 0) credit = 1;
            else credit = 0;
            self->field2C = credit;
            self->state = 2;
        }
        break;
    }
    case 2: Select(); break;
    case 3: FadeOut(); break;
    case 4: FadeIn(); break;
    case 6: {
        InputState *input = SINGLETON_INSTANCE(g_pInputState);
        switch (self->subState) {
        case 1:
            if (CardSave_Tick()) {
                switch (fn_801FDB90(Sci2Card_GetPrintErrorCode())) {
                case 0:
                    self->subState = 2;
                    fn_8020A7CC(self->fader.p, 0, lbl_806DA848, (short)lbl_806DA848);
                    CreditMgr_TryConfirmPlay(2);
                    break;
                case 6: case 7: fn_801D919C(self->window.p); self->state = -1; break;
                }
            }
            break;
        case 2: {
            StepSaveFade(self, input);
            break;
        }
        case 3:
            if (fn_80203E30() == -1) { fn_801D919C(self->window.p); self->state = 7; }
            break;
        }
        break;
    }
    case 5:
        if (*((unsigned char *)self->counter + 8) == 1) self->state = 2;
        break;
    case 7:
        fn_8023CFC8(self->prompt.p); fn_80232284(ItemMsg_Get(), lbl_806DA800);
        if (self->detail->state == 6) self->state = 8;
        break;
    case 8: self->field0C = 1; self->state = -1; break;
    }
    if (self->state >= 1 && self->state < 6) {
        fn_801F8A34(fn_801F8E58(), self->texts, 4);
        fn_801F8A34(fn_801F8E58(), (char *)self->texts + 0x230, 4);
        fn_801F8A34(fn_801F8E58(), (char *)self->texts + 0x460, 4);
    }
    if (self->detail) {
        if (self->state == 5) fn_80160588(self->detail, 0, 0);
        else fn_80160588(self->detail, SINGLETON_INSTANCE(g_pInputState)->dir, 0);
    }
    fn_8024E094(self->counter);
    UpdateKart(self->window.p);
    fn_8023CDA8(self->prompt.p);
}

extern "C" { void fn_8016039C(void *); void fn_8024E05C(void *); void fn_801D9A2C(void *); void fn_8023CD54(void *); }
void clMnCardT01::Draw() {
    if (detail) fn_8016039C(detail);
    if (counter) fn_8024E05C(counter);
    fn_801D9A2C(window.p);
    fn_8023CD54(prompt.p);
}

extern "C" {
/* 8-aligned in the original: probably the first object of a TU */
extern const char lbl_803BFCD8[36] = "\215\354\202\347\202\310\202\242\217\352\215\207\201A\215\241\211\361\203\214\201[\203X\202\305\212l\223\276\202\265\202\275";
extern const char lbl_803BFCFC[36] = "\203}\203\212\203I\203R\203C\203\223\202\315\202\267\202\327\202\304\202\310\202\255\202\310\202\350\202\334\202\267\201B";
extern const char lbl_803BFD20[] = "If you do not have a card,";
extern const char lbl_803BFD3C[] = "you will lose all MARIO COIN";
extern const char lbl_803BFD5C[] = "received in this race.";
extern const char lbl_806DA7E0[];
const char *lbl_804EBF58[2][3] = {
    lbl_803BFCD8, lbl_803BFCFC, lbl_806DA7E0,
    lbl_803BFD20, lbl_803BFD3C, lbl_803BFD5C
};
}
