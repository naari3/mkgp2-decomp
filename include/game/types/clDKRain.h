#ifndef GAME_TYPES_CLDKRAIN_H
#define GAME_TYPES_CLDKRAIN_H
#include "game/types/clMapEffectParts.h"
struct Obj16A;
struct Zone16A;
class clNormal3D;
struct clDKRain : clMapEffectParts {
    Obj16A *model;
    Zone16A *zone;
    unsigned char hit;
    unsigned char align[3];
    clNormal3D *archive;
    float alpha;
    clDKRain();
    virtual ~clDKRain();
    virtual void Update();
    virtual void Draw();
};
#endif
