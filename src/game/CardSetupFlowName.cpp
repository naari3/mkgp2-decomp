#include "CardSetupFlowView.h"
extern "C" void fn_8024AA6C(CardSetupFlow *self) {
    fn_801BE170(self->name);
    if (self->name->Done() == 1) {
        FlowSceneList *list = self->list;
        fn_801F4DF0(list, new SetupPrintTask, 0);
        self->state = 6;
        card_force_backup_now();
        fn_8020AAD4(ItemDisplay_GetOrCreate());
        fn_8020F3F0();
    }
}
