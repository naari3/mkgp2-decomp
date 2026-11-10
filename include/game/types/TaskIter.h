#ifndef GAME_TYPES_TASKITER_H
#define GAME_TYPES_TASKITER_H

/* Declare before including (each user already does): TaskNode */

struct TaskIter {
    TaskNode *node;
    TaskIter() {}
    TaskIter(TaskNode *n) : node(n) {}
    TaskIter &operator=(const TaskIter &o) {
        node = o.node;
        return *this;
    }
};

#endif /* GAME_TYPES_TASKITER_H */
