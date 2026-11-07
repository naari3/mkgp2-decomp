#ifndef GAME_FADELOGO_TASKLISTOWNER_H
#define GAME_FADELOGO_TASKLISTOWNER_H

#include "game/FadeLogo.h"

/* Out-of-line ABI view of VHolder<TaskListImpl> for its owned destructor. */
struct TaskListOwner {
    TaskListImpl *p;
    ~TaskListOwner() throw();
};

#endif
