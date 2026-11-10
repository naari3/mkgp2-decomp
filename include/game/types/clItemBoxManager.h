#ifndef GAME_TYPES_CLITEMBOXMANAGER_H
#define GAME_TYPES_CLITEMBOXMANAGER_H

#include "game/types/BoxList.h"
#include "game/types/ResponderList.h"

/* Declare before including (each user already does): clItemBoxManagerBase */

struct clItemBoxManager : clItemBoxManagerBase {
    ResponderList responders; /* 0x04 */
    BoxList boxes;            /* 0x10 */
    unsigned char active;    /* 0x1C */

    virtual void Key();
    virtual ~clItemBoxManager();
    clItemBoxManager(void *table);
};

#endif /* GAME_TYPES_CLITEMBOXMANAGER_H */
