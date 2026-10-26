#include "CardPrintFlowView.h"
static inline void SetError(CardPrintFlow *self, int error) {
    switch (error) {
    case 102: self->error = 102; self->phase = -1; break;
    case 104: self->error = 104; self->phase = -1; break;
    case 105: self->error = 105; self->phase = -1; break;
    case 100:
    case 106:
    case 255: self->error = 106; self->phase = -1; break;
    case 101: self->error = 101; self->phase = -1; break;
    }
}
extern "C" void fn_8024B924(CardPrintFlow *self) {
    if (fn_8020F278() == 1) {
        if (self->phase != -1) SetError(self, Sci2Card_GetPrintErrorCode());
        if (self->phase != -1) SetError(self, fn_8020F270());
        if (self->phase != -1) SetError(self, fn_8020F268());
        if (self->phase != -1 && card_is_ejected()) self->phase = 8;
    } else if (fn_8020F280() == 1) {
        SetError(self, fn_8020F270());
    }
    switch (card_rw_get_substate()) {
    case 0:
    case 1:
        if (self->kart.p->layout != 5) {
            fn_801D919C(self->kart.p);
            clFlowKart_SetupTextLayout(self->kart.p, 5);
        }
        break;
    case 2:
    case 3:
        if (self->kart.p->layout != 2) {
            fn_801D919C(self->kart.p);
            clFlowKart_SetupTextLayout(self->kart.p, 2);
        }
        break;
    }
}
