#ifndef GAME_TYPES_FLOWSCENEHOST_H
#define GAME_TYPES_FLOWSCENEHOST_H

/* Declare before including (each user already does): FlowSceneList, VHolder */

struct FlowSceneHost {
    virtual void _key();
    VHolder<FlowSceneList> list;
    FlowSceneHost();
    ~FlowSceneHost();
};

#endif /* GAME_TYPES_FLOWSCENEHOST_H */
