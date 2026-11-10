#ifndef GAME_TYPES_HUDRESHOLDER_H
#define GAME_TYPES_HUDRESHOLDER_H

#include "game/types/HudResSet.h"

struct HudResHolder {
    HudResSet *p;
    HudResHolder(HudResSet *q) : p(q) {}
    ~HudResHolder() throw();
};

#endif /* GAME_TYPES_HUDRESHOLDER_H */
