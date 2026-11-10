#ifndef GAME_TYPES_TASKENTRIESBASE_H
#define GAME_TYPES_TASKENTRIESBASE_H

/* Declare before including (each user already does): TaskIter, TaskNode */

struct TaskEntriesBase {
    int count;
    TaskNode *last;
    TaskNode *first;
    TaskNode *End() { return (TaskNode *)&last; }
    TaskIter EraseRange(const TaskIter &a, const TaskIter &b);
    ~TaskEntriesBase() { EraseRange(TaskIter(End()->next), TaskIter(End())); }
};

#endif /* GAME_TYPES_TASKENTRIESBASE_H */
