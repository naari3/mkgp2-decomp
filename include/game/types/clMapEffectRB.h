#ifndef GAME_TYPES_CLMAPEFFECTRB_H
#define GAME_TYPES_CLMAPEFFECTRB_H

#include "game/types/JObj.h"
#include "game/types/PartsCtx.h"
#include "game/types/PartsList.h"
#include "game/types/clMapEffect.h"

struct clMapEffectRB : clMapEffect {
    PartsList *parts;
    PartsCtx *ctx;
    unsigned char done;

    virtual ~clMapEffectRB();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectRB(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTRB_H */
