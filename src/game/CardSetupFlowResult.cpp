#pragma inline_max_size(1000)
#include "CardSetupFlowView.h"
#include "CardSetupFlowPlayerView.h"
extern "C" { extern SetupPlayerSnapshot g_playerData, lbl_805D275C; extern char lbl_806D0928[8]; }
extern "C" void fn_8024A2F0(CardSetupFlow *self) {
    FlowTask *task = fn_801F4DC0(self->list, 2);
    if (task) {
        self->selection = ((SetupChoiceView *)fn_80271340(task, 0, lbl_806D0928, lbl_806D08F8, 0))->selection;
        int result = ((SetupChoiceView *)fn_80271340(task, 0, lbl_806D0928, lbl_806D08F8, 0))->result;
        task = fn_801F4DC0(self->list, 4);
        if (task) fn_801FEF18(fn_80271340(task, 0, lbl_806D0900, lbl_806D08F8, 0), result);
    } else {
        task = fn_801F4DC0(self->list, 6);
        if (task) fn_80201148(fn_80271340(task, 0, lbl_806D0910, lbl_806D08F8, 0));
        fn_802043B8(self->list, 4);
        task = fn_801F4DC0(self->list, 5);
        if (task) fn_801FFFF4(fn_80271340(task, 0, lbl_806D0908, lbl_806D08F8, 0));
        if (self->selection == 0) {
            FlowSceneList *list = self->list;
            fn_801F4DF0(list, new SetupPrintTask, 0);
            self->state = 6;
        } else if ((int)g_playerData.byte1D9 == 2) {
            self->state = 13;
        } else {
            SetupPlayerSnapshot *player = &g_playerData;
            *player = lbl_805D275C;
            FlowSceneList *list = self->list;
            fn_801F4DF0(list, new SetupPrintTask, 0);
            self->state = 6;
        }
    }
}
