#include "game/ContinueScene_private.h"
extern "C" {
void fn_8023CD54(CoinPrompt *);
void fn_8016039C(CoinPopupDetail *);
void fn_8024D36C(ContinueScene *self) {
    self->list.p->Draw();
    fn_8023CD54(self->prompt.p);
    if (self->detail) fn_8016039C(self->detail);
    if (self->counter) fn_801D9A2C(self->counter->window);
}
}
