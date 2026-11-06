#include "game/cxc_buy_card.h"
extern "C" {
extern const int lbl_803BFF54[];
extern const float lbl_806DA81C, lbl_806DA800;
extern RefillSingleton *lbl_806D1A88;
extern unsigned char g_playerData[];
int CreditMgr_GetCoinCount(int, int); int CreditMgr_GetPlayState(int);
int CreditMgr_GetCreditCount(int);
void fn_8024E1DC(void *); void fn_801618CC(void *, int, int);
void fn_80161888(void *); void fn_80232284(RefillSingleton *, float);
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
extern "C" void fn_801FBE14(BuyCardStep *self) {
    InputState *input;
    unsigned char creditOnly;
    input = GetInput();
    int result;
    if (self->panel->state < 2) result = 2;
    else result = self->panel->result;
    bool ready = result == 0;
    int old = self->selection;
    self->selection += input->dir;
    int selection = self->selection;
    if (selection < 0) self->selection = 0;
    if (selection > 1) self->selection = 1;
    int coins = CreditMgr_GetCoinCount(0, -1);
    if (self->coins != coins) self->timeout = lbl_803BFF54[1] + 1;
    self->coins = coins;
    creditOnly = IsCreditOnly();
    if (creditOnly && self->creditOnly != creditOnly && !self->automatic && self->selection > 0) {
        fn_8020A7CC(self->fader, 0, 15, 15);
        self->automatic = 1; self->state = 3; self->next = 2;
    }
    if (input->held == 1) {
        if (self->selection == 0) {
            if (creditOnly) {
                if (CreditMgr_GetCreditCount(2) <= 0) goto purchase;
            } else {
                fn_8024E1DC(self->indicator); self->state = 5;
                if (!creditOnly && !ready) {
                    if (self->retries < 1) {
                        self->retries++; self->timeout = lbl_803BFF54[1] + 1;
                    }
                    fn_801618CC(self->panel, 0, 0);
                }
            }
        } else {
            self->state = 7; fn_80161888(self->panel);
        }
    }
    if (self->timeout > 0) self->timeout--;
    fn_80232284(BuyRefill(), self->timeout / lbl_806DA81C);
    fn_801FE27C(self->timeout);
    if (old != self->selection) fn_801FE390();
    if (self->timeout <= 0) {
        if (self->selection == 0) {
            fn_8020A7CC(self->fader, 0, 15, 15);
            self->state = 4; self->next = 7; fn_80161888(self->panel);
        } else { fn_801FE348(); self->state = 7; fn_80161888(self->panel); }
    }
    self->creditOnly = creditOnly;
    return;
purchase:
    fn_8020AAD4(ItemDisplay_GetOrCreate());
    fn_80232284(BuyRefill(), lbl_806DA800);
    fn_8023CFC8(self->choice); fn_80161888(self->panel); fn_801FE348();
    self->state = 6; self->result = 1;
    card_save_trigger(0);
    if (*self->kart) fn_801D919C(self->kart);
    if (fn_801D5F40(g_playerData) == 1) clFlowKart_SetupTextLayout(self->kart, 1);
    else clFlowKart_SetupTextLayout(self->kart, 0);
}
