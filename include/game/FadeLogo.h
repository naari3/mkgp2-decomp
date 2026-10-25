#ifndef GAME_FADELOGO_H
#define GAME_FADELOGO_H

/*
 * Fading logo task (0x8020E2D8..0x8020F220).
 *
 *   PopupRoot (vtable lbl_8048ECF8, inline) -> PopupTask (vtable lbl_8048ED10, inline)
 *     FadeLogoScene (vtable lbl_804ECAA8): owns a task list holding one FadeLogo.
 *     FadeTaskBase (vtable lbl_804ECB1C) -> FadeLogo (vtable lbl_804ECB04).
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
    TaskIter Erase(TaskIter it);
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
    TaskIter Remove(TaskIter it) { return entries.Erase(it); }
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

#endif
