#include "game/FadeLogo.h"

void TaskListImpl::Sort() {
    TaskIter a;
    a.node = entries.first;
    TaskIter last;
    last.node = entries.last;
    while (a.node != last.node) {
        TaskIter b;
        b.node = a.node->next;
        while (b.node != entries.End()) {
            PopupTask *ta;
            PopupTask *tb;
            tb = b.node->task;
            ta = a.node->task;
            if (ta->id > tb->id) {
                a.node->task = tb;
                b.node->task = ta;
            }
            b.node = b.node->next;
        }
        a.node = a.node->next;
    }
}

