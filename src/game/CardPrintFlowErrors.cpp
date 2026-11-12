#include "CardPrintFlowView.h"
static inline void SetError(clRsCardT1 *self, int error) {
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
void clRsCardT1::CheckErrors() {
    if (fn_8020F278() == 1) {
        if (this->phase != -1) SetError(this, Sci2Card_GetPrintErrorCode());
        if (this->phase != -1) SetError(this, fn_8020F270());
        if (this->phase != -1) SetError(this, fn_8020F268());
        if (this->phase != -1 && card_is_ejected()) this->phase = 8;
    } else if (fn_8020F280() == 1) {
        SetError(this, fn_8020F270());
    }
    switch (card_rw_get_substate()) {
    case 0:
    case 1:
        if (this->kart.p->layout != 5) {
            fn_801D919C(this->kart.p);
            clFlowKart_SetupTextLayout(this->kart.p, 5);
        }
        break;
    case 2:
    case 3:
        if (this->kart.p->layout != 2) {
            fn_801D919C(this->kart.p);
            clFlowKart_SetupTextLayout(this->kart.p, 2);
        }
        break;
    }
}
