#include "game/FadeLogo.h"

void TaskListImpl::Update() {
    Sort();
    TaskIter it;
    it.node = entries.End()->next;
    while (it.node != entries.End()) {
        PopupTask *t = it.node->task;
        if (t->CanUpdate()) {
            t->Update();
        }
        it.node = it.node->next;
    }
}
