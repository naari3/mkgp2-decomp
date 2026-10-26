#include "CardSetupFlowView.h"
extern "C" void fn_80249E0C(CardSetupFlow *self) {
    if (!self->done) {
        if (self->state == 4) fn_801BDB60(self->name);
        self->list->Draw();
        fn_801D9A2C(self->kart);
        HSD_StateInvalidate(-1);
    }
}
