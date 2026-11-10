#ifndef GAME_TYPES_TASKLISTIMPL_H
#define GAME_TYPES_TASKLISTIMPL_H

/* Declare before including (each user already does): TaskIter, TaskListBase */

struct TaskListImpl : TaskListBase {
    TaskListImpl() {}
    ~TaskListImpl();
    virtual void Update();
    virtual void Draw();
    void Sort();
    TaskIter Remove(TaskIter it) { return entries.Erase(it); }
};

#endif /* GAME_TYPES_TASKLISTIMPL_H */
