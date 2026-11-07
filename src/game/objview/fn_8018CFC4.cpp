#include "game/ObjViewS22_private.h"
struct HSD_JObj;
extern "C" {
void DebugPrintf(const char *, ...);
HSD_JObj *ResolveJointByName(clNormal3D *, const char *);

/* This TU owns the clPCFruit string pool (.rodata 0x80377E60..0x80377EF0). */
extern const char lbl_80377E60[] = "clPCFruit";
extern const char lbl_80377E6C[] = "clMapEffectParts";
extern const char lbl_80377E80[0x20] = " DeleteMapEffect : clPCFruit\n";
static const char createMsg[0x20] = " CreateMapEffect : clPCFruit\n";
static const char modelFile[0x14] = "PCA_anim_fruits.dat";
static const char jointName[] = "PC_land_anim_fruits_joint";
}
struct S22Single : S22Base {
    clNormal3D *model;
    HSD_JObj *joint;
    S22Single();
    virtual ~S22Single();
};
S22Single::S22Single() {
    DebugPrintf(createMsg);
    model = 0;
    joint = 0;
    model = new clNormal3D(modelFile, 0);
    joint = ResolveJointByName(model, jointName);
}
