#define SCENELISTIMPL_EXTERNAL_VTABLE
#include "game/SceneListDraw_private.h"

void SceneListImpl::Draw() {
    ListNode *end = entries.End();
    SceneDrawIter it;
    it.node = entries.first;
    while (it.node != end) {
        FlowTask *t = it.node->task;
        bool run;
        if (t->field08 > 0) {
            run = 0;
            t->field08--;
        } else {
            if (t->field0C == 1) {
                t->field0C = 2;
            }
            run = t->field0C <= 0;
        }
        if (run) {
            t->Draw();
        }
        if (t->field0C >= 2) {
            t->Finish();
            it = entries.Erase(it);
        } else {
            it.node = it.node->next;
        }
    }
}

