#include "game/FadeLogoDraw_private.h"

void TaskListImpl::Draw() {
    TaskNode *end = entries.End();
    TaskIter it;
    it.node = entries.first;
    while (it.node != end) {
        if (it->CanDraw()) {
            it->Draw();
        }
        if (it->field0C >= 2) {
            it->Finish();
            it = Remove(it);
        } else {
            ++it;
        }
    }
}

