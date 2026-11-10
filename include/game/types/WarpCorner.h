#ifndef GAME_TYPES_WARPCORNER_H
#define GAME_TYPES_WARPCORNER_H

#include "game/types/WarpPlainVector.h"

struct WarpCorner : WarpPlainVector {
    WarpCorner(const WarpCorner &v) : WarpPlainVector(v) {}
    ~WarpCorner();
};

#endif /* GAME_TYPES_WARPCORNER_H */
