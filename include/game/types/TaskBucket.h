#ifndef GAME_TYPES_TASKBUCKET_H
#define GAME_TYPES_TASKBUCKET_H

#include "game/types/BucketTask.h"

struct TaskBucket {
    void *allocation;
    unsigned int count;
    BucketTask **start;
    BucketTask **End() { return start + count; }
};

#endif /* GAME_TYPES_TASKBUCKET_H */
