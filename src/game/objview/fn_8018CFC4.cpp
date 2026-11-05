#include "game/ObjViewS22_private.h"
struct HSD_JObj;
extern "C" {
extern const char lbl_80377E60[];
void DebugPrintf(const char *, ...);
HSD_JObj *ResolveJointByName(clNormal3D *, const char *);
}
struct S22Single : S22Base {
    clNormal3D *model;
    HSD_JObj *joint;
    S22Single();
    virtual ~S22Single();
};
S22Single::S22Single() {
    const char *data = lbl_80377E60;
    DebugPrintf(data + 0x40);
    model = 0;
    joint = 0;
    model = new clNormal3D(data + 0x60, 0);
    joint = ResolveJointByName(model, data + 0x74);
}
