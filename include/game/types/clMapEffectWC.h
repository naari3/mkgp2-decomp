#ifndef GAME_TYPES_CLMAPEFFECTWC_H
#define GAME_TYPES_CLMAPEFFECTWC_H

#include "game/types/JObj.h"
#include "game/types/PartsList.h"
#include "game/types/clMapEffect.h"

struct clMapEffectWC : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual ~clMapEffectWC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectWC(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTWC_H */
