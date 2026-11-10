#ifndef GAME_TYPES_PATHUSERHOLDER_H
#define GAME_TYPES_PATHUSERHOLDER_H

#include "game/types/PathUser.h"

struct PathUserHolder {
    PathUser *p;
    ~PathUserHolder() throw() {
        delete p;
    }
};

#endif /* GAME_TYPES_PATHUSERHOLDER_H */
