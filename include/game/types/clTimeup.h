#ifndef GAME_TYPES_CLTIMEUP_H
#define GAME_TYPES_CLTIMEUP_H

#include "game/FlowScene.h"
#include "game/types/clRaceCountNum.h"

/* Keep the existing task-container declarations with the real task type. */
#ifndef GAME_TYPES_POPUPROOT_H
#define GAME_TYPES_POPUPROOT_H
typedef clYTaskInterface PopupRoot;
#endif
#ifndef GAME_TYPES_POPUPTASK_H
#define GAME_TYPES_POPUPTASK_H
typedef clCTaskInterface PopupTask;
#endif

struct TaskListImpl;

struct clTimeupDisp : clCTaskInterface {
    void Draw();
    int layer;
    VHolder<TaskListImpl> list;
    clTimeupDisp(int layer_, int id_);
    ~clTimeupDisp();
    void Finish();
    void Update();
};

#endif
