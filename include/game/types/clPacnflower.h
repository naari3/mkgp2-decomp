#ifndef GAME_TYPES_CLPACNFLOWER_H
#define GAME_TYPES_CLPACNFLOWER_H
#include "game/types/size_t.h"
#include "game/types/Vec.h"
#include "game/types/clMapEffectParts.h"
void *operator new(size_t);
void operator delete(void *);
struct clNormal3D {
    char opaque[0x5C];
    clNormal3D(void *, int);
    ~clNormal3D();
};
struct ObjViewFrame { int active; float time; };
struct clPacnflower : clMapEffectParts {
    virtual ~clPacnflower();
    virtual void Update();
    virtual void Draw();
    clNormal3D *model;
    float radius, yoff;
    Vec *pos;
    float *rot;
    ObjViewFrame *frames;
    int count;
    clPacnflower();
};
#endif
