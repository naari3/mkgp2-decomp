#ifndef GAME_TYPES_CARDMENUROOT_H
#define GAME_TYPES_CARDMENUROOT_H

#include "game/types/SceneBase.h"

/* Declare before including (each user already does): MenuModeBase */

struct CardMenuRoot : MenuModeBase {
    SceneBase *task;
    CardMenuRoot();
    ~CardMenuRoot();
    virtual void Destroy();
    virtual void Update();
    virtual void Draw();
};

#endif /* GAME_TYPES_CARDMENUROOT_H */
