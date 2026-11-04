/* Ordered scene insertion, lookup, shutdown and virtual deletion.
 * NonMatching: iterator register allocation differs; owned EH is exact. */
#include "game/FlowScene.h"
extern "C" ListIter DoublyLinkedList_PushBefore(DoublyLinkedList *, const ListIter &, FlowTask *const &);
extern "C" void fn_801F4D3C(FlowSceneList *list) {
    ListNode *end;
    ListNode *n;
    end = list->entries.End();
    for (n = list->entries.first; n != end; n = n->next) n->task->field0C = 1;
    while (list->entries.count > 0) { list->Update(); list->Draw(); }
}
extern "C" FlowTask *fn_801F4DC0(FlowSceneList *list, int id) {
    ListNode *end;
    ListNode *n;
    end = list->entries.End();
    for (n = list->entries.first; n != end; n = n->next) {
        FlowTask *task = n->task;
        if ((unsigned)id == (unsigned)task->id) return task;
    }
    return 0;
}
extern "C" int SceneListInsert(FlowSceneList *list, FlowTask *task, int mode) {
    if (!task) return 0;
    ListNode *end;
    ListNode *n = list->entries.first;
    end = list->entries.End();
    ListIter result;
    ListIter position;
    for (; n != end; n = n->next) {
        FlowTask *other = n->task;
        if (other && (unsigned)task->id < (unsigned)other->id) break;
    }
    task->field08 = mode;
    position.node = n;
    result = DoublyLinkedList_PushBefore(&list->entries, position, task);
    return 1;
}
extern "C" void fn_801F4E78(VObject *p) { delete p; }
