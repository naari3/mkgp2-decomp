#ifndef GAME_TYPES_FACEHOLDER_H
#define GAME_TYPES_FACEHOLDER_H

#include "game/types/FaceSprite.h"

struct FaceHolder {
    FaceSprite *p;
    FaceHolder(FaceSprite *q) : p(q) {}
    ~FaceHolder() throw() {
        delete p;
    }
};

#endif /* GAME_TYPES_FACEHOLDER_H */
