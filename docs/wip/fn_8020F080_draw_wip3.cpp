/* WIP3 2026-11-07 (R2): Remove(TaskIter it){ return it = entries.erase(it); } gives the target post-call stores 0x8->0x10->0x14 exactly; only diff left is the dead pre-call store of the Remove param to 0x10 (kept by opt_dead_assignments off). */
/* WIP2 2026-11-07 (thread B): 2 diff lines left. Erase(const TaskIter&) + inline erase(TaskIter){r=Erase(it);return r;} + Remove(TaskIter){r=entries.erase(it);return r;} + opt_dead_assignments off. Left: target has no dead store of the Remove param to 0x10 before the call, but stores the result 0x8 -> 0x10 -> it(0x14). ~300 forms swept (Remove/erase/Erase by val/cref, Draw-side temps, op= by value). Erase by cref needs a rename Erase__11TaskEntriesFRC8TaskIter -> fn_8012215C. */

/*
 * Fading logo task (0x8020E2D8..0x8020F220).
 *
 *   PopupRoot (vtable lbl_8048ECF8, inline) -> PopupTask (vtable lbl_8048ED10, inline)
 *     FadeLogoScene (vtable FadeLogoScene_vtable_804ECAA8): owns a task list holding one FadeLogo.
 *     FadeTaskBase (vtable FadeTaskBase_vtable_804ECB1C) -> FadeLogo (vtable FadeLogo_vtable_804ECB04).
 *   TaskListBase (vtable lbl_804ECAC0) -> TaskListImpl (vtable lbl_804ECB44).
 */

#include "game/FlowScene.h"

struct PopupRoot {
    virtual ~PopupRoot() {}
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void _keyR();
    unsigned int id;
    int field08;
    int field0C;
    PopupRoot(int id_) : id(id_), field08(0), field0C(0) {}
    bool CanDraw() {
        if (field08 > 0) {
            field08--;
            return 0;
        }
        if (field0C == 1) {
            field0C = 2;
        }
        return field0C <= 0;
    }
    bool CanUpdate() {
        if (field08 > 0) {
            return 0;
        }
        return field0C <= 0;
    }
};

struct PopupTask : PopupRoot {
    PopupTask(int id_) : PopupRoot(id_) {}
    virtual ~PopupTask() {}
    virtual void _keyT();
};

struct TaskNode {
    TaskNode *prev;
    TaskNode *next;
    PopupTask *task;
};

struct TaskIter {
    TaskNode *node;
    TaskIter() {}
    TaskIter(TaskNode *n) : node(n) {}
    bool operator!=(TaskNode *n) const { return node != n; }
    PopupTask *operator*() const { return node->task; }
    TaskIter &operator++() { node = node->next; return *this; }
    TaskIter &operator=(const TaskIter &o) {
        node = o.node;
        return *this;
    }
};

/* count + sentinel node {prev = last, next = first}. */
struct TaskEntriesBase {
    int count;
    TaskNode *last;
    TaskNode *first;
    TaskNode *End() { return (TaskNode *)&last; }
    TaskIter EraseRange(const TaskIter &a, const TaskIter &b);
    ~TaskEntriesBase() { EraseRange(TaskIter(End()->next), TaskIter(End())); }
};

struct TaskEntriesMid : TaskEntriesBase {
    ~TaskEntriesMid() {}
};

struct TaskEntries : TaskEntriesMid {
    TaskEntries();
    ~TaskEntries() {}
    TaskIter Insert(TaskIter pos, PopupTask *const &task);
    TaskIter Erase(const TaskIter &it);
    TaskIter erase(TaskIter it) { return Erase(it); }
};

struct TaskListBase {
    virtual ~TaskListBase() {
        KillAll();
        entries.EraseRange(TaskIter(entries.first), TaskIter(entries.End()));
    }
    virtual void Update() = 0;
    virtual void Draw() = 0;
    TaskEntries entries;
    TaskListBase() {}
    void KillAll();
    bool Add(PopupTask *task, int delay);
};

struct TaskListImpl : TaskListBase {
    TaskListImpl() {}
    ~TaskListImpl();
    virtual void Update();
    virtual void Draw();
    void Sort();
    TaskIter Remove(TaskIter it) { return it = entries.erase(it); }
};

struct FadeLogoScene : PopupTask {
    int layer;
    VHolder<TaskListImpl> list;
    FadeLogoScene(int layer_, int id_);
    ~FadeLogoScene();
    void Finish();
    void Update();
    void Draw();
    virtual void _key();
};


#pragma opt_dead_assignments off
void TaskListImpl::Draw() {
    TaskNode *end = entries.End();
    TaskIter it;
    it.node = entries.first;
    while (it.node != end) {
        if ((*it)->CanDraw()) {
            (*it)->Draw();
        }
        if ((*it)->field0C >= 2) {
            (*it)->Finish();
            it = Remove(it);
        } else {
            it.node = it.node->next;
        }
    }
}

