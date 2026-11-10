#ifndef GAME_TYPES_TASKENTRIES_H
#define GAME_TYPES_TASKENTRIES_H

#include "game/types/PopupTask.h"
#include "game/types/TaskEntriesMid.h"

/* Declare before including (each user already does): TaskIter */

struct TaskEntries : TaskEntriesMid {
    TaskEntries();
    ~TaskEntries() {}
    TaskIter Insert(TaskIter pos, PopupTask *const &task);
    TaskIter Erase(TaskIter it);
};

#endif /* GAME_TYPES_TASKENTRIES_H */
