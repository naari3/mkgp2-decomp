#include "CardSetupFlowView.h"
extern "C" {
void fn_8024AD8C(CardSetupFlow *);
void fn_8024AC38(CardSetupFlow *);
void fn_8024AA6C(CardSetupFlow *);
void fn_8024A2F0(CardSetupFlow *);
void fn_8024A06C(CardSetupFlow *);
void fn_801BB6D4(SetupReceipt *);
void fn_80249E78(CardSetupFlow *self) {
    if (!self->done) {
        InputState *input = GetInput();
        switch (self->state) {
        case 0: fn_8024AD8C(self); break;
        case 2:
            self->fader->Step();
            if (self->fader->Done() || input->held == 1) {
                fn_801D919C(self->kart);
                self->state = 13;
            }
            break;
        case 3: fn_8024AC38(self); break;
        case 4: fn_8024AA6C(self); break;
        case 5: fn_8024A2F0(self); break;
        case 6:
            if (!fn_801F4DC0(self->list, 3)) self->state = 13;
            break;
        case 12: fn_8024A06C(self); break;
        case 13: {
            FlowTask *task = fn_801F4DC0(self->list, 6);
            if (task) fn_80201148(fn_80271340(task, 0, lbl_806D0910, lbl_806D08F8, 0));
            task = fn_801F4DC0(self->list, 5);
            if (task) fn_801FFFF4(fn_80271340(task, 0, lbl_806D0908, lbl_806D08F8, 0));
            fn_802043B8(self->list, 4);
            self->state = 14;
            fn_8020AAD4(ItemDisplay_GetOrCreate());
            break;
        }
        case 14:
            if (self->list->entries.count <= 0 && self->kart->busy == 0) {
                self->done = 1;
                self->state = -1;
            }
            break;
        }
        self->list->Update();
        if (self->receipt) fn_801BB6D4(self->receipt);
        fn_801D9B70(self->kart, 0);
    }
}
}
