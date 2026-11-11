#ifndef GAME_TYPES_CLMRPUKUPUKU_H
#define GAME_TYPES_CLMRPUKUPUKU_H
#include "game/types/clMapEffectParts.h"
#include "game/types/clNormal3D.h"
#include "game/types/Vec3.h"

struct PukupukuPlacement {
    Vec3 pos;
    float bob, yaw, roll, t;
    int timer;
};

struct clMRPukupuku : clMapEffectParts {
    virtual ~clMRPukupuku();
    virtual void Update();
    virtual void Draw();
    clNormal3D *model;
    PukupukuPlacement *slots;
    clMRPukupuku();
};
#endif
