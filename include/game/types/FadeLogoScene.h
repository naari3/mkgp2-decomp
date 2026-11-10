#ifndef GAME_TYPES_FADELOGOSCENE_H
#define GAME_TYPES_FADELOGOSCENE_H

#include "game/types/PopupTask.h"
#include "game/types/TaskListImpl.h"

/* Declare before including (each user already does): VHolder */

struct FadeLogoScene : PopupTask {
    int layer;
    VHolder<TaskListImpl> list;
    FadeLogoScene(int layer_, int id_);
    ~FadeLogoScene();
    void Finish();
    void Update();
    void Draw();
    virtual void _key();
};

#endif /* GAME_TYPES_FADELOGOSCENE_H */
