#ifndef GAME_TYPES_AISYSTEM_H
#define GAME_TYPES_AISYSTEM_H

#include "game/types/ObjCollChecker.h"
#include "game/types/PathManager.h"

struct AISystem {
    unsigned char data[0x4];
    AISystem(PathManager *path, ObjCollChecker *coll, int flag);
};

#endif /* GAME_TYPES_AISYSTEM_H */
