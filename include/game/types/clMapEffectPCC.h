#ifndef GAME_TYPES_CLMAPEFFECTPCC_H
#define GAME_TYPES_CLMAPEFFECTPCC_H

#include "game/types/clMapEffect.h"

struct clMapEffectPCC : clMapEffect {
    unsigned char done;

    virtual ~clMapEffectPCC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectPCC() {
        done = 0;
    }
};

#endif /* GAME_TYPES_CLMAPEFFECTPCC_H */
