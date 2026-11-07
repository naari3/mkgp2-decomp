#include "game/cxc_buy_card.h"
#include "game/singleton.h"
struct PanelText { TextManager *p; };
struct BuyMode { int pad[2]; int light; };
extern "C" {
extern const float lbl_806DA7F0, lbl_806DA7F4, lbl_806DA7F8, lbl_806DA7FC;
extern const int lbl_806DA848;
BuyMode *fn_801DAEC0();
PanelText *fn_80146000(void *, int);
void fn_801FBE14(BuyCardStep *); void fn_801FBD94(BuyCardStep *); void fn_801FBD14(BuyCardStep *);
void fn_801618CC(void *, int, int); void fn_80161888(void *);
unsigned char CardSave_Tick(); int Sci2Card_GetPrintErrorCode(); int fn_801FDB90(int);
int CreditMgr_GetPlayState(int); int CreditMgr_GetCreditCount(int); void CreditMgr_TryConfirmPlay(int);
void fn_801D919C(void *); int fn_80203E30();
void fn_8023CFC8(void *); void fn_80232284(RefillSingleton *, float);
void *fn_801F8E58(); void fn_801F8A34(void *, void *, int);
void fn_80160588(void *, int, int); void fn_8024E094(void *);
void fn_801D9B70(void *, int); void fn_8023CDA8(void *);
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
static inline void StepSaveFade(BuyCardStep *self, InputState *input) {
    FlowFaderI *f = (FlowFaderI *)self->fader;
    BuyFadeTick(f);
    if (input->held == 1 || ((FlowFaderI *)self->fader)->Done()) {
        fn_801D919C(self->kart);
        self->result = 3;
    }
}
extern "C" void fn_801FB778(BuyCardStep *self) {
    InputState *input = SINGLETON_INSTANCE(g_pInputState);
    if (input->held == 1) self->flash = 10;
    if (self->flash > 0) {
        self->flash--; BuyMode *m = fn_801DAEC0(); m->light = 4;
    } else { BuyMode *m = fn_801DAEC0(); m->light = 1; }
    switch (self->state) {
    case -1: break;
    case 0:
        self->panel = new CardChoicePanel(0, 0, 4);
        PanelPosition(self->panel, lbl_806DA7F0, lbl_806DA7F4, lbl_806DA7F8, lbl_806DA7F4);
        fn_8020A7CC(self->fader, 0, 30, 30); self->state = 1;
        break;
    case 1: {
        FlowFaderI *f = (FlowFaderI *)self->fader;
        BuyFadeTick(f);
        if (((FlowFaderI *)self->fader)->Done()) {
            int coins = CreditMgr_GetCoinCount(0, -1);
            if (self->coins != coins) self->timeout = lbl_803BFF54[1] + 1;
            self->coins = coins;
            unsigned char credit;
            if (CreditMgr_GetPlayState(0) == 3) credit = 1;
            else if (CreditMgr_GetCreditCount(2) == 0) credit = 1;
            else credit = 0;
            self->creditOnly = credit;
            self->state = 2;
        }
        break;
    }
    case 2: fn_801FBE14(self); break;
    case 3: fn_801FBD94(self); break;
    case 4: fn_801FBD14(self); break;
    case 6: {
        InputState *input = SINGLETON_INSTANCE(g_pInputState);
        switch (self->result) {
        case 1:
            if (CardSave_Tick()) {
                switch (fn_801FDB90(Sci2Card_GetPrintErrorCode())) {
                case 0:
                    self->result = 2;
                    fn_8020A7CC(self->fader, 0, lbl_806DA848, (short)lbl_806DA848);
                    CreditMgr_TryConfirmPlay(2);
                    break;
                case 6: case 7: fn_801D919C(self->kart); self->state = -1; break;
                }
            }
            break;
        case 2: {
            StepSaveFade(self, input);
            break;
        }
        case 3:
            if (fn_80203E30() == -1) { fn_801D919C(self->kart); self->state = 7; }
            break;
        }
        break;
    }
    case 5:
        if (*((unsigned char *)self->indicator + 8) == 1) self->state = 2;
        break;
    case 7:
        fn_8023CFC8(self->choice); fn_80232284(BuyRefill(), lbl_806DA800);
        if (self->panel->state == 6) self->state = 8;
        break;
    case 8: self->done = 1; self->state = -1; break;
    }
    if (self->state >= 1 && self->state < 6) {
        fn_801F8A34(fn_801F8E58(), self->text, 4);
        fn_801F8A34(fn_801F8E58(), (char *)self->text + 0x230, 4);
        fn_801F8A34(fn_801F8E58(), (char *)self->text + 0x460, 4);
    }
    if (self->panel) {
        if (self->state == 5) fn_80160588(self->panel, 0, 0);
        else fn_80160588(self->panel, SINGLETON_INSTANCE(g_pInputState)->dir, 0);
    }
    fn_8024E094(self->indicator);
    input = SINGLETON_INSTANCE(g_pInputState);
    fn_801D9B70(self->kart, input->dir != 0);
    fn_8023CDA8(self->choice);
}
