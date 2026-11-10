#ifndef GAME_TYPES_JOBRUNNERMODE_H
#define GAME_TYPES_JOBRUNNERMODE_H

#include "game/types/JobTask.h"

/* Declare before including (each user already does): GameModeBase */

struct JobRunnerMode : GameModeBase {
    JobTask *task;
    unsigned int updateStart;
    unsigned int updateEnd;
    unsigned int drawStart;
    unsigned int drawEnd;
    int sel;
    JobRunnerMode() : task(0), sel(3) {}
    virtual int Update();
    virtual void Draw();
    virtual ~JobRunnerMode();
};

#endif /* GAME_TYPES_JOBRUNNERMODE_H */
