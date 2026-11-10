#ifndef GAME_TYPES_FXBASE_H
#define GAME_TYPES_FXBASE_H

#include "game/types/FxData.h"

struct FxBase : FxData {
    FxBase() {
        obj = 0;
        active = 0;
        x = 0.0f;
        y = 0.0f;
        alpha = 1.0f;
    }
    virtual ~FxBase() {}
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
};

#endif /* GAME_TYPES_FXBASE_H */
