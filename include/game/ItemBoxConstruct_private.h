#include "game/types/size_t.h"
struct BoxVec { float x,y,z; };
struct BoxJoint { char pad[8]; BoxJoint *next; BoxJoint *parent; BoxJoint *child; char pad14[0x24]; BoxVec pos; };
struct BoxDObj { void *vptr; BoxDObj *next; };
struct BoxModel { char opaque[0x5c]; BoxModel(const char *, int); };
struct BoxSlot {
    BoxVec points[3]; BoxVec pos; float rx, ry, unknown, t; int delay;
    unsigned char visible; char pad[3];
    struct Shadow { BoxVec pos; float scale; } shadows[10];
    int cooldown, randIdx;
};
struct BoxBase {
    BoxBase() {}
    virtual ~BoxBase();
};
struct BoxConstruct : BoxBase {
    virtual void key();
    void *sound;
    BoxModel *modelA, *modelB, *archive;
    BoxDObj *nodes;
    int selected;
    BoxSlot *slots;
    int count;
    BoxConstruct(BoxJoint *);
};
extern "C" {
extern char lbl_806D8B34[7], lbl_806D8B3C[5];
extern const float lbl_806D8B30, lbl_806D8B0C;
void DebugPrintf(const char *, ...);
void *FUN_8003b120(int);
void Object_SetJObjScaleXYZ(void *,float,float,float);
BoxJoint *Archive_GetRootJObj(void *);
void HSD_JObjSetFlags(BoxJoint *,unsigned int);
BoxDObj *HSD_JObjGetDObj(BoxJoint *);
void HSD_DObjSetFlags(BoxDObj *,unsigned int);
void __assert(char *,int,char *);
}
void *operator new(size_t);
void operator delete(void *);
