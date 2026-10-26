#include "CardPrintFlowView.h"
extern "C" {
extern const char lbl_803EFDE8[], lbl_803EFE0C[];
struct PrintPlayerData { char pad[0x198]; signed char remaining; };
extern PrintPlayerData g_playerData;
void fn_8024B568(CardPrintFlow *self) {
    InputState *input = GetInput();
    switch (self->phase) {
    case 0:
        if (!fn_8020F288()) DebugPrintf(lbl_803EFDE8);
        else { DebugPrintf(lbl_803EFE0C); self->phase = 7; }
        break;
    case 7: fn_8024B924(self); break;
    case 8:
        if (card_rw_get_substate() == 5) {
            fn_801D919C(self->kart.p);
            self->fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
            self->phase = 9;
        }
        break;
    case 9:
        self->fader.p->Step();
        if (self->fader.p->Done()) {
            fn_801D919C(self->kart.p);
            self->phase = 10;
        }
        break;
    case 10:
        if (self->kart.p->busy == 0) {
            if (g_playerData.remaining <= 0) {
                clFlowKart_SetupTextLayout(self->kart.p, 8);
                self->fader.p->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
                self->phase = 11;
            } else { fn_801D919C(self->kart.p); self->phase = 14; }
        }
        break;
    case 11:
        self->fader.p->Step();
        if (self->fader.p->Done() || input->held == 1) {
            fn_801D919C(self->kart.p);
            self->phase = 14;
        }
        break;
    case 14:
        if (self->kart.p->busy == 0) { self->field0C = 1; self->phase = -1; }
        break;
    case -1: fn_8024B77C(self); break;
    }
    fn_801D9B70(self->kart.p, 0);
}
}
