#define lbl_806D8EA8 lbl_806D92AC
#define lbl_806D8EB0 lbl_806D92B4
#define lbl_803761AC lbl_8037722C
#define lbl_803761A0 lbl_80377254
#include "game/objview/path186_private.h"
extern "C" {
float LUT_Sin12Bit(float);
unsigned char fn_801379F0(Vec3f *, float);
static inline void SwingPath186(Path186 *p, float swing, float turn) {
    HSD_JObj *joint = p->joint[1];
    if (joint) {
        HSD_JObjSetRotationX(joint, swing);
        HSD_JObjSetRotationY((HSD_JObj *)p->joint[1], turn);
    }
}
void fn_801869F8(View186 *self) {
    unsigned char visible[2];
    Path186 *p;
    const Path186 *renderPath;
    int i;
    HSD_JObj *joint;
    Vec3f probe;
    float swing, turn;
    if (self->object == 0 || self->paths == 0) return;
    swing = 1.0471975803375244f * LUT_Sin12Bit(360.0f * self->phase);
    turn = 6.2831854820251465f * self->phase2;
    for (i = 0; i < 2; i++) {
        p = &self->paths[i];
        probe.x = p->position.x;
        probe.y = 150.0f + p->position.y;
        probe.z = p->position.z;
        if (fn_801379F0(&probe, 400.0f)) {
            SwingPath186(p, swing, turn);
            joint = p->joint[2];
            if (joint) HSD_JObjSetRotationZ(joint, self->rotation);
            joint = p->joint[3];
            if (joint) HSD_JObjSetRotationZ(joint, self->rotation);
            visible[i] = 1;
        } else visible[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        if (visible[i]) {
            p = &self->paths[i];
            joint = p->joint[0];
            if (joint) {
                HSD_JObjSetTranslate(joint, &p->position);
                HSD_JObjSetRotationY((HSD_JObj *)p->joint[0], p->yaw);
                HSD_JObjDispAll((HSD_JObj *)p->joint[0], 0, 1, 0);
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (visible[i]) {
            renderPath = &self->paths[i];
            joint = renderPath->joint[0];
            if (joint) {
                HSD_JObjSetTranslate(joint, &renderPath->position);
                HSD_JObjSetRotationY((HSD_JObj *)renderPath->joint[0], renderPath->yaw);
                HSD_JObjDispAll((HSD_JObj *)renderPath->joint[0], 0, 6, 0);
            }
        }
    }
}
}
