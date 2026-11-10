#ifndef GAME_TYPES_CLMAPEFFECTDK_H
#define GAME_TYPES_CLMAPEFFECTDK_H

#include "game/types/JObj.h"
#include "game/types/PartsList.h"
#include "game/types/clMapEffect.h"

struct clMapEffectDK : clMapEffect {
    PartsList *parts;
    int x08;
    int x0c;
    int x10;
    unsigned char done;

    virtual ~clMapEffectDK();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectDK(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTDK_H */
