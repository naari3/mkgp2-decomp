#ifndef GAME_FADELOGO_H
#define GAME_FADELOGO_H

/*
 * Fading logo task (0x8020E2D8..0x8020F220).
 *
 *   PopupRoot (vtable lbl_8048ECF8, inline) -> PopupTask (vtable lbl_8048ED10, inline)
 *     FadeLogoScene (vtable FadeLogoScene_vtable_804ECAA8): owns a task list holding one FadeLogo.
 *     FadeTaskBase (vtable FadeTaskBase_vtable_804ECB1C) -> FadeLogo (vtable FadeLogo_vtable_804ECB04).
 *   TaskListBase (vtable lbl_804ECAC0) -> TaskListImpl (vtable lbl_804ECB44).
 */

#include "game/FlowScene.h"

#include "game/types/PopupRoot.h"

#include "game/types/PopupTask.h"

#include "game/types/TaskNode.h"

#include "game/types/TaskIter.h"

/* count + sentinel node {prev = last, next = first}. */
struct TaskEntriesBase {
    int count;
    TaskNode *last;
    TaskNode *first;
    TaskNode *End() { return (TaskNode *)&last; }
    TaskIter EraseRange(const TaskIter &a, const TaskIter &b);
    ~TaskEntriesBase() { EraseRange(TaskIter(End()->next), TaskIter(End())); }
    void Clear() { EraseRange(TaskIter(first), TaskIter(End())); }
};

#include "game/types/TaskEntriesMid.h"

struct TaskEntries : TaskEntriesMid {
    TaskEntries();
    ~TaskEntries() {}
    TaskIter Insert(const TaskIter &pos, PopupTask *const &task);
    TaskIter Erase(TaskIter it);
};

struct TaskListBase {
    virtual ~TaskListBase() {
        KillAll();
        entries.Clear();
    }
    virtual void Update() = 0;
    virtual void Draw() = 0;
    /* Undefined key stubs (_keyB/_keyL/_key): these vtables live in
     * unowned .data, so no TU may emit them. */
    virtual void _keyB();
    TaskEntries entries;
    TaskListBase() {}
    void KillAll();
    bool Add(PopupTask *task, int delay);
};

struct TaskListImpl : TaskListBase {
    virtual void _keyL();
    TaskListImpl() {}
    ~TaskListImpl();
    virtual void Update();
    virtual void Draw();
    void Sort();
    TaskIter Remove(TaskIter it) { return entries.Erase(it); }
};

struct FadeLogoScene : PopupTask {
    virtual void _key();
    int layer;
    VHolder<TaskListImpl> list;
    FadeLogoScene(int layer_, int id_);
    ~FadeLogoScene();
    void Finish();
    void Update();
    void Draw();
};

#endif
