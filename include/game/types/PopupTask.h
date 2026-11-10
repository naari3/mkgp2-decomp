#ifndef GAME_TYPES_POPUPTASK_H
#define GAME_TYPES_POPUPTASK_H

/* Declare before including (each user already does): PopupRoot */

struct PopupTask : PopupRoot {
    PopupTask(int id_) : PopupRoot(id_) {}
    virtual ~PopupTask() {}
    virtual void _keyT();
};

#endif /* GAME_TYPES_POPUPTASK_H */
