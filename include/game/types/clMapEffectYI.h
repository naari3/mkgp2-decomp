#ifndef GAME_TYPES_CLMAPEFFECTYI_H
#define GAME_TYPES_CLMAPEFFECTYI_H

#include "game/types/JObj.h"
#include "game/types/PartsList.h"
#include "game/types/YIState.h"
#include "game/types/clMapEffect.h"

struct clMapEffectYI : clMapEffect {
    PartsList *parts;
    YIState *state;

    virtual ~clMapEffectYI();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectYI(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTYI_H */
