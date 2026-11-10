#ifndef GAME_TYPES_JOBTASK15_H
#define GAME_TYPES_JOBTASK15_H

#include "game/types/JobTask.h"

struct JobTask15 : JobTask {
    char pad[0x18 - 0x8];
    JobTask15();
};

#endif /* GAME_TYPES_JOBTASK15_H */
