#include "CardSetupFlowView.h"
extern "C" void fn_8024AC38(CardSetupFlow *self) {
    FlowTask *task = fn_801F4DC0(self->list, 1);
    if (task) {
        self->selection = ((SetupChoiceView *)fn_80271340(task, 0, lbl_806D0920, lbl_806D08F8, 0))->selection;
        int result = ((SetupChoiceView *)fn_80271340(task, 0, lbl_806D0920, lbl_806D08F8, 0))->result;
        task = fn_801F4DC0(self->list, 4);
        if (task) fn_801FEF18(fn_80271340(task, 0, lbl_806D0900, lbl_806D08F8, 0), result);
    } else {
        task = fn_801F4DC0(self->list, 6);
        if (task) fn_80201148(fn_80271340(task, 0, lbl_806D0910, lbl_806D08F8, 0));
        fn_802043B8(self->list, 4);
        task = fn_801F4DC0(self->list, 5);
        if (task) fn_801FFFF4(fn_80271340(task, 0, lbl_806D0908, lbl_806D08F8, 0));
        fn_802043B8(self->list, 1);
        PlayStats_AccumulatePlayTime(1);
        if (self->selection == 0) {
            self->state = 4;
            ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AD8);
        } else self->state = 13;
    }
}
