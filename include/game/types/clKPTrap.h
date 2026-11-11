#ifndef GAME_TYPES_CLKPTRAP_H
#define GAME_TYPES_CLKPTRAP_H
#include "game/types/size_t.h"
#include "game/types/clMapEffectParts.h"
#include "game/types/HSD_JObj.h"
#include "game/types/Vec3f.h"
#include "game/types/GrowEntry.h"
#include "game/types/KartDriver.h"
struct DListQuadInfo { Vec3f vertex[4]; int flags; float value1, value2; };
void *operator new(size_t);
void operator delete(void *);
struct clNormal3D { char opaque[0x5C]; clNormal3D(void *, int); };
struct GrowDObj { char pad00[0xC]; void *pobj; };
struct GrowFace { char data[0x34]; };
struct GrowAnim { void *data; GrowAnim(DListQuadInfo *, int); };
struct GrowSub {
    Vec3f pos; float scale;
    unsigned char started, done;
    char rest[0xAA];
    GrowSub();
};
struct clKPTrap : clMapEffectParts {
    virtual ~clKPTrap();
    virtual void Update();
    virtual void Draw();
    clNormal3D *model;
    GrowEntry *entries;
    int count;
    clKPTrap();
};
#endif
