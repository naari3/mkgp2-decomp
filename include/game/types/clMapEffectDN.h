#ifndef GAME_TYPES_CLMAPEFFECTDN_H
#define GAME_TYPES_CLMAPEFFECTDN_H

#include "game/types/JObj.h"
#include "game/types/PartsList.h"
#include "game/types/clMapEffect.h"

struct clMapEffectDN : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectDN();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectDN(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTDN_H */
