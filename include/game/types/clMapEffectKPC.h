#ifndef GAME_TYPES_CLMAPEFFECTKPC_H
#define GAME_TYPES_CLMAPEFFECTKPC_H

#include "game/types/clMapEffect.h"

struct clMapEffectKPC : clMapEffect {
    unsigned char done;

    virtual ~clMapEffectKPC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectKPC() {
        done = 0;
    }
};

#endif /* GAME_TYPES_CLMAPEFFECTKPC_H */
