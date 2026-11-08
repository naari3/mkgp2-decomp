#define FLOWMSGPOPUP_NO_SERVICE_HELPERS
#define SCENELISTIMPL_EXTERNAL_VTABLE
#include "game/FlowScene.h"
#include "game/FlowMsgPopup.h"

/*
 * Message popup service (0x80203EA0..0x80204474): open/close entry points,
 * service init/shutdown, the SceneListImpl task list and the FlowTask
 * base ctor/dtor.
 */

extern "C" {
void DebugPrintf(const char *fmt, ...);
void PreloadResource(int id);
void fn_80120A08(int id);
extern const char lbl_803C250C[];
extern const char lbl_803C2528[];

int fn_80203EA0(void);
int fn_80203F5C(int msg);
void fn_802040B0(void);
void fn_80204130(int layer);
}

static inline ListIter RemoveTask(DoublyLinkedList *entries, ListIter it) {
    ListIter result = entries->Erase(it);
    return result;
}

/* GC/1.3 + opt_propagation off: 13 -> 4 lines. Left: the target copies the
 * Erase result through a memory temp (0x8 -> 0x10 -> it at 0x14) after the
 * call; here RemoveTask's by-value parameter takes slot 0x10 before it. */
#pragma opt_propagation off
#pragma push
#pragma optimization_level 3
void SceneListImpl::Draw() {
    ListNode *end = entries.End();
    ListIter it;
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
            it = RemoveTask(&entries, it);
        } else {
            it.node = it.node->next;
        }
    }
}
#pragma pop

