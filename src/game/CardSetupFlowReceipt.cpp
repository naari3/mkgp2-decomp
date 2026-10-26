#include "CardSetupFlowView.h"
extern "C" {
void fn_801BBAF0(SetupReceipt *);
void fn_801BB940(SetupReceipt *, int);
int Sci2Card_GetUnpackStatusCode();
unsigned char Sci2Card_GetReceiptTestFlag();
void fn_8024A06C(CardSetupFlow *self) {
    if (!self->receipt) self->receipt = new SetupReceipt(1);
    fn_801BBAF0(self->receipt);
    if (self->receipt->Done() == 1) {
        if (self->receipt->accepted == 1) {
            if (Sci2Card_GetUnpackStatusCode() == 5) {
                FlowSceneList *list = self->list;
                fn_801F4DF0(list, new SetupDialog(1, 2), 40);
                if (Sci2Card_GetReceiptTestFlag()) {
                    self->fader->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
                    self->state = 2;
                } else self->state = 5;
            } else {
                FlowSceneList *list = self->list;
                fn_801F4DF0(list, new SetupPrintTask, 0);
                self->state = 6;
            }
        } else self->state = 13;
        fn_801BB940(self->receipt, 1);
        self->receipt = 0;
    }
}
}
