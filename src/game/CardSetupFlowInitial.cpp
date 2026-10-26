#include "CardSetupFlowView.h"
extern "C" {
unsigned char Sci2Card_GetByteFlag1224();
unsigned char Sci2Card_GetReceiptTestFlag();
unsigned char ServiceValue_Get();
int Sci2Card_GetUnpackStatusCode();
extern unsigned char g_playerData[0x1DC];
extern int lbl_806D19B8;
FlowTask *fn_801FC1E0(int);
void fn_8024AD8C(CardSetupFlow *self) {
    if (!Sci2Card_GetByteFlag1224()) {
        if (ServiceValue_Get()) {
            self->state = 2;
            self->fader->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
            clFlowKart_SetupTextLayout(self->kart, 6);
        } else if (Sci2Card_GetReceiptTestFlag()) {
            self->state = 2;
            self->fader->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
            clFlowKart_SetupTextLayout(self->kart, 7);
        } else {
            lbl_806D19B8 = 5;
            FlowSceneList *list = self->list;
            fn_801F4DF0(list, fn_801FC1E0(1), 40);
            ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AD5);
            self->state = 3;
        }
    } else if ((int)g_playerData[0x1D9] != 2) self->state = 12;
    else if (Sci2Card_GetUnpackStatusCode() == 5) {
        if (Sci2Card_GetReceiptTestFlag()) {
            FlowSceneList *list = self->list;
            fn_801F4DF0(list, new SetupDialog(1, 2), 40);
            self->fader->Set(0, lbl_806D1AB0, (short)lbl_806D1AB0);
            self->state = 2;
        } else {
            FlowSceneList *list = self->list;
            fn_801F4DF0(list, new SetupDialog(1, 2), 40);
            self->state = 5;
        }
    } else {
        FlowSceneList *list = self->list;
        fn_801F4DF0(list, new SetupPrintTask, 0);
        self->state = 6;
    }
}
}
