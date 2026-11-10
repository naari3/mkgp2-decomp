#ifndef GAME_TYPES_PATHOWNER_H
#define GAME_TYPES_PATHOWNER_H

#include "game/types/PathUserHolder.h"

struct PathOwner {
    void *vt;
    PathUserHolder user;
    int unk8;
    int unkC;

    ~PathOwner() {
        vt = lbl_804E4C18;
        unkC = 0;
        unk8 = 0;
    }
};

#endif /* GAME_TYPES_PATHOWNER_H */
