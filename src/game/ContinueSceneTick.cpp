#include "game/ContinueScene_private.h"
struct ContinueMode { int pad[2]; int mode; };
extern "C" {
ContinueMode *fn_801DAEC0();
void fn_8023CFD4(CoinPrompt *);
void fn_8023CFC8(CoinPrompt *);
void fn_8023CDA8(CoinPrompt *);
void fn_802321D4(ItemMsgWnd *);
void fn_80160588(CoinPopupDetail *, int, int);
void fn_8024D874(ContinueScene *);
void fn_8024D7F4(ContinueScene *);
void fn_8024D764(ContinueScene *);
void fn_8024D3D4(ContinueScene *self) {
    const char *strings = lbl_803EFEA0;
    InputState *in = GetInput();
    if (in->held == 1) {
        ContinueMode *mode = fn_801DAEC0();
        mode->mode = 4;
    } else {
        ContinueMode *mode = fn_801DAEC0();
        mode->mode = 1;
    }
    switch (self->state) {
    case -1: break;
    case 0: break;
    case 1:
        self->fader.p->Step();
        if (self->fader.p->Done()) {
            int coins = CreditMgr_GetCoinCount(0, -1);
            if (self->coins != coins) self->timer = lbl_806D1AB8 + 1;
            self->coins = coins;
            self->noCredit = IsNoCredit();
            self->state = 2;
            fn_8023CFD4(self->prompt.p);
        }
        break;
    case 2: fn_8024D874(self); break;
    case 3: fn_8024D7F4(self); break;
    case 4: fn_8024D764(self); break;
    case 5:
        if (self->counter->done == 1) self->state = 2;
        break;
    case 7:
        fn_802321D4(ItemMsg_Get());
        fn_8023CFC8(self->prompt.p);
        fn_80161888(self->detail);
        self->state = 8;
        fn_8020AAD4(ItemDisplay_GetOrCreate());
        break;
    case 8:
        if (self->list.p->entries.count <= 0) {
            if ((unsigned char)(self->detail->state == 6) == 1) {
                self->field0C = 1;
                self->state = -1;
            }
        }
        break;
    }
    self->list.p->Update();
    fn_8023CDA8(self->prompt.p);
    if (self->detail) {
        if (self->state == 5) fn_80160588(self->detail, 0, 0);
        else {
            InputState *in = GetInput();
            fn_80160588(self->detail, in->dir, 0);
        }
    }
    CoinCounter *counter = self->counter;
    int alternate;
    int credits = CreditMgr_GetCreditCount(counter->slot);
    in = GetInput();
    fn_801D9B70(counter->window, in->held == 1);
    if (counter->done == 1) return;
    alternate = lbl_80598A60[0x27] != 0;
    char text[0x80];
    if (!isJapanese()) {
        sprintf(text, lbl_806D0970[alternate], credits);
        fn_801D8DF8(counter->window, text, 1);
        fn_801D8DF8(counter->window, strings + 0x984, 2);
    } else {
        sprintf(text, strings + 0x998, credits);
        fn_801D8DF8(counter->window, strings + 0x768, 1);
        fn_801D8DF8(counter->window, text, 2);
    }
    if (credits <= 0 || counter->window->state == 0) {
        fn_801D919C(counter->window);
        counter->done = 1;
    }
}
}
