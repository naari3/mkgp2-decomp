#include "game/FlowCardCheckScene.h"
extern "C" void fn_8023CD54(clIndicator *ind);

void clFlowCardCheck::Draw() {
    clFlowCCInterface *p = pages[page];
    if (p != 0 && p->active == 1) {
        p->Draw();
    }
    if (prevPage >= 0) {
        p = pages[prevPage];
        if (p != 0 && p->active == 1) {
            p->Draw();
        }
    }
    fn_8023CD54(indicator);
}
