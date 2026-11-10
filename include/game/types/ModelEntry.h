#ifndef GAME_TYPES_MODELENTRY_H
#define GAME_TYPES_MODELENTRY_H

#include "game/types/ModelDef.h"

typedef struct ModelEntry {
    const void *desc;
    ModelDef *defs;
} ModelEntry;

#endif /* GAME_TYPES_MODELENTRY_H */
