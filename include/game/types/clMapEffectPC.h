#ifndef GAME_TYPES_CLMAPEFFECTPC_H
#define GAME_TYPES_CLMAPEFFECTPC_H

#include "game/types/JObj.h"
#include "game/types/PartsCtx.h"
#include "game/types/PartsList.h"
#include "game/types/clMapEffect.h"

struct clMapEffectPC : clMapEffect {
    PartsList *parts;
    PartsCtx *ctx;
    unsigned char done;

    virtual ~clMapEffectPC();
    virtual void Update();
    virtual void Draw(int mask);

    clMapEffectPC(JObj *root, int arg);
};

#endif /* GAME_TYPES_CLMAPEFFECTPC_H */
