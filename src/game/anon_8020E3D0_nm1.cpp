#include "game/FadeLogoDraw_private.h"

void TaskListImpl::Draw() {
    TaskNode *end = entries.End();
    TaskIter it;
    it.node = entries.first;
    while (it.node != end) {
        if (it.node->task->CanDraw()) {
            it.node->task->Draw();
        }
        if (it.node->task->field0C >= 2) {
            it.node->task->Finish();
            it = Remove(it);
        } else {
            it.node = it.node->next;
        }
    }
}

