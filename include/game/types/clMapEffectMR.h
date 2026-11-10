#ifndef GAME_TYPES_CLMAPEFFECTMR_H
#define GAME_TYPES_CLMAPEFFECTMR_H

#include "game/types/JObj.h"
#include "game/types/PartsList.h"
#include "game/types/clMapEffect.h"

struct clMapEffectMR : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectMR();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectMR(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTMR_H */
