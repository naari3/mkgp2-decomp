#include "game/types/clRsContinueTask.h"
struct ContinueMode { int pad[2]; int mode; };
extern "C" {
ContinueMode *fn_801DAEC0();
void fn_8023CFD4(CoinPrompt *);
void fn_8023CFC8(CoinPrompt *);
void fn_8023CDA8(CoinPrompt *);
void fn_802321D4(ItemMsgWnd *);
void fn_80160588(CoinPopupDetail *, int, int);
static inline void CounterDraw(CoinCounter *c, const char *base) {
    char buf[0x80];
    int idx;
    int credits = CreditMgr_GetCreditCount(c->slot);
    fn_801D9B70(c->window, GetInput()->held == 1);
    if (c->done != 1) {
        idx = lbl_80598A60[0x27] ? 1 : 0;
        if (isJapanese() == 0) {
            sprintf(buf, lbl_806D0970[idx], credits);
            fn_801D8DF8(c->window, buf, 1);
            fn_801D8DF8(c->window, base + 0x984, 2);
        } else {
            sprintf(buf, base + 0x998, credits);
            fn_801D8DF8(c->window, base + 0x768, 1);
            fn_801D8DF8(c->window, buf, 2);
        }
        if (credits <= 0 || c->window->state == 0) {
            fn_801D919C(c->window);
            c->done = 1;
        }
    }
}
}
void clRsContinueTask::Update() {
    const char *strings = lbl_803EFEA0;
    InputState *in = GetInput();
    if (in->held == 1) {
        ContinueMode *mode = fn_801DAEC0();
        mode->mode = 4;
    } else {
        ContinueMode *mode = fn_801DAEC0();
        mode->mode = 1;
    }
    switch (this->state) {
    case -1: break;
    case 0: break;
    case 1:
        this->fader.p->Step();
        if (this->fader.p->Done()) {
            int coins = CreditMgr_GetCoinCount(0, -1);
            if (this->coins != coins) this->timer = lbl_806D1AB8 + 1;
            this->coins = coins;
            this->noCredit = IsNoCredit();
            this->state = 2;
            fn_8023CFD4(this->prompt.p);
        }
        break;
    case 2: Select(); break;
    case 3: Cancel(); break;
    case 4: Confirm(); break;
    case 5:
        if (this->counter->done == 1) this->state = 2;
        break;
    case 7:
        fn_802321D4(ItemMsg_Get());
        fn_8023CFC8(this->prompt.p);
        fn_80161888(this->detail);
        this->state = 8;
        fn_8020AAD4(ItemDisplay_GetOrCreate());
        break;
    case 8:
        if (this->list.p->entries.count <= 0) {
            if ((unsigned char)(this->detail->state == 6) == 1) {
                this->field0C = 1;
                this->state = -1;
            }
        }
        break;
    }
    this->list.p->Update();
    fn_8023CDA8(this->prompt.p);
    if (this->detail) {
        if (this->state == 5) fn_80160588(this->detail, 0, 0);
        else {
            InputState *in = GetInput();
            fn_80160588(this->detail, in->dir, 0);
        }
    }
    CounterDraw(this->counter, strings);
}
