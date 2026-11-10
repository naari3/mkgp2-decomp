#ifndef GAME_TYPES_CLMAPEFFECTWCC_H
#define GAME_TYPES_CLMAPEFFECTWCC_H

#include "game/types/JObj.h"
#include "game/types/PartsList.h"
#include "game/types/clMapEffect.h"

struct clMapEffectWCC : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectWCC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectWCC(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTWCC_H */
