#ifndef GAME_SCENE_LIST_DRAW_PRIVATE_H
#define GAME_SCENE_LIST_DRAW_PRIVATE_H
#include "game/FlowScene.h"

/* Writable adapter: assignment consumes the list's iterator by value. */
struct SceneDrawIter : ListIter {
    SceneDrawIter &operator=(ListIter other) {
        node = other.node;
        return *this;
    }
};
#endif
