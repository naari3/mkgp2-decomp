#ifndef GAME_TYPES_MODEBASE_H
#define GAME_TYPES_MODEBASE_H

#include "game/types/GameModeBase.h"

struct ModeBase : GameModeBase {
    float x4;
    ModeBase() {
        x4 = 0.0f;
    }
    virtual void _key2();
    virtual ~ModeBase();
};

#endif /* GAME_TYPES_MODEBASE_H */
