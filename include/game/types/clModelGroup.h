#ifndef GAME_TYPES_CLMODELGROUP_H
#define GAME_TYPES_CLMODELGROUP_H

#include "game/types/ModelEntry.h"

/* Declare before including (each user already does): clModel, clNormal3D */

struct clModelGroup {
    clModelGroup *next;
    clNormal3D *obj;
    clModel *models;
    clModelGroup(const ModelEntry *entry);
};

#endif /* GAME_TYPES_CLMODELGROUP_H */
