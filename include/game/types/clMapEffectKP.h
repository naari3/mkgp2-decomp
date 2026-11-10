#ifndef GAME_TYPES_CLMAPEFFECTKP_H
#define GAME_TYPES_CLMAPEFFECTKP_H

#include "game/types/JObj.h"
#include "game/types/PartsList.h"
#include "game/types/ZoneVolume.h"
#include "game/types/clMapEffect.h"

struct clMapEffectKP : clMapEffect {
    PartsList *parts;
    ZoneVolume *zone;
    float x0c;
    JObj *x10;
    float x14;
    unsigned char x18;
    JObj *x1c;
    JObj *x20;
    float x24;
    float x28;
    unsigned char x2c;

    virtual ~clMapEffectKP();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectKP(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTKP_H */
