#ifndef GAME_TYPES_TASKNODE_H
#define GAME_TYPES_TASKNODE_H

#include "game/types/PopupTask.h"

typedef struct TaskNode {
    TaskNode *prev;
    TaskNode *next;
    PopupTask *task;
} TaskNode;

#endif /* GAME_TYPES_TASKNODE_H */
