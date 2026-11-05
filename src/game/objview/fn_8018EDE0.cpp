#include "game/objview/emitter_private.h"
struct EmitterBase { EmitterBase() {} virtual ~EmitterBase(); };
struct EmitterCtor : EmitterBase {
    virtual void key();
    clNormal3D *model, *billboard; int count;
    ViewMatrixParticle *matrices; ViewBillboardParticle *particles;
    int delay, randomIndex, variationIndex;
    EmitterCtor(clNormal3D *);
};
extern "C" {
extern char lbl_803781CC[], lbl_803781F4[];
extern const void *lbl_806CFC40, *lbl_806CFC44;
void *FUN_8003b120(unsigned long);
}
static inline ViewJoint *child(ViewJoint *p) { if (p == 0) return 0; return p->child; }
static inline ViewJoint *next(ViewJoint *p) { if (p == 0) return 0; return p->next; }
EmitterCtor::EmitterCtor(clNormal3D *root) {
    DebugPrintf(lbl_803781CC);
    model = 0; billboard = 0; count = 0; matrices = 0; particles = 0;
    delay = 0; randomIndex = 0; variationIndex = 0;
    ViewJoint *joint = (ViewJoint *)ResolveJointByName(root, lbl_803781F4);
    count = 0;
    ViewJoint *j;
    for (j = child(joint); j; j = next(j)) count++;
    if (count == 0) return;
    model = new clNormal3D(lbl_806CFC40, 0);
    clNormal3D_SetScale(model, 0, lbl_806D9440, lbl_806D9460, lbl_806D9440, lbl_806D9440);
    billboard = new clNormal3D(lbl_806CFC44, 1);
    matrices = (ViewMatrixParticle *)FUN_8003b120(count * sizeof(ViewMatrixParticle));
    int i;
    for (i = 0, j = child(joint); i < count && j; i++, j = next(j)) {
        matrices[i].age = lbl_806D944C;
        matrices[i].joint = j;
    }
    for (i = 0; i < count; i++) matrices[i].age = lbl_806D944C;
    particles = (ViewBillboardParticle *)FUN_8003b120(60 * sizeof(ViewBillboardParticle));
    for (i = 0; i < 60; i++) particles[i].age = lbl_806D944C;
}
