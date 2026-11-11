#ifndef GAME_TYPES_CLKPTHUNDER_H
#define GAME_TYPES_CLKPTHUNDER_H
#include "game/types/clMapEffectParts.h"
struct RenderJoint {
    char pad00[8]; RenderJoint *next;
    char pad0C[4]; RenderJoint *child;
    unsigned int flags; char pad18[4];
    float rx, ry, rz;
    char pad28[0x10]; float x, y, z;
};
struct clNormal3D {
    char opaque[0x5C];
    clNormal3D(void *, int);
    ~clNormal3D();
};
struct CourseSpark {
    unsigned char active;
    unsigned char pad[3];
    int timer;
    int index;
};
struct clKPThunder : clMapEffectParts {
    RenderJoint *root;
    int count;
    clNormal3D *modelA, *modelB;
    RenderJoint *joints[4];
    CourseSpark sparks[5];
    int cooldown, randomIndex;
    virtual ~clKPThunder();
    virtual void Update();
    virtual void Draw();
    clKPThunder(RenderJoint *);
};
#endif
