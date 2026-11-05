#include "game/objview/emitter_private.h"
struct GroupBase { GroupBase() {} virtual ~GroupBase(); };
struct GroupJoint { ViewJoint *joint; unsigned char active, flags, pad[2]; };
struct GroupParticle { unsigned char type; unsigned char rest[0x2b]; };
struct GroupCtor : GroupBase {
    virtual void key();
    GroupJoint *joints; int count; clNormal3D **models;
    GroupParticle *particles; void *field14; int field18;
    GroupCtor(clNormal3D *);
};
extern "C" {
extern char lbl_80378058[];
extern const char *lbl_806CFC18;
extern const void *lbl_80495E50[3];
void *FUN_8003b120(unsigned long);
}
static inline ViewJoint *child(ViewJoint *p) { if (p == 0) return 0; return p->child; }
static inline ViewJoint *next(ViewJoint *p) { if (p == 0) return 0; return p->next; }
GroupCtor::GroupCtor(clNormal3D *root) {
    DebugPrintf(lbl_80378058);
    joints = 0; count = 0; models = 0; particles = 0; field14 = 0; field18 = 0;
    if (root == 0) return;
    ViewJoint *joint = (ViewJoint *)ResolveJointByName(root, lbl_806CFC18);
    if (joint == 0) return;
    ViewJoint *j;
    for (j = child(joint); j; j = next(j)) count++;
    if (count == 0) return;
    joints = (GroupJoint *)FUN_8003b120(count * sizeof(GroupJoint));
    int i;
    for (i = 0, j = child(joint); j && i < count; j = next(j), i++) {
        joints[i].joint = j; joints[i].active = 0; joints[i].flags = 0;
    }
    models = (clNormal3D **)FUN_8003b120(3 * sizeof(clNormal3D *));
    for (i = 0; i < 3; i++) models[i] = new clNormal3D(lbl_80495E50[i], 1);
    particles = (GroupParticle *)FUN_8003b120(60 * sizeof(GroupParticle));
    for (i = 0; i < 60; i++) particles[i].type = 3;
}
