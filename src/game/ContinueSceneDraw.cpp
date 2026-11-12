#include "game/types/clRsContinueTask.h"
extern "C" {
void fn_8023CD54(CoinPrompt *);
void fn_8016039C(CoinPopupDetail *);
}
void clRsContinueTask::Draw() {
    list.p->Draw();
    fn_8023CD54(prompt.p);
    if (detail) fn_8016039C(detail);
    if (counter) fn_801D9A2C(counter->window);
}
