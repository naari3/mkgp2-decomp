#include "game/objview/emitter_private.h"
extern "C" void fn_8018E538(ViewEmitter *o) {
    int i;
    ViewMatrixParticle *p;
    ViewBillboardParticle *q;
    Mtx *view;
    Vec3f pos;
    if (o->count == 0) return;
    view = CObj_GetProjMatrix_Cached(GetCourseScene3D());
    for (i = 0; i < o->count; i++) {
        p = &o->matrices[i];
        if (!(p->age < lbl_806D9440)) {
            pos.x = p->matrix[0][3];
            pos.y = p->matrix[1][3];
            pos.z = p->matrix[2][3];
            if (fn_801379F0(&pos, lbl_806D9444)) {
                Object_SetField8_AndDirty(o->model, p->age);
                Object_SetAnimBinding(o->model, p->matrix, 0);
                clNormal3D_Exec(o->model);
                Object_DriveAnimMatrix(o->model);
                Object_RenderJObjTree(o->model, 7);
            }
        }
    }
    GXChannel ch(Archive_GetRootJObj(o->billboard), HSD_JObjGetDObj(Archive_GetRootJObj(o->billboard)), 0x40000000, 1);
    Mtx m;
    for (i = 0; i < 60; i++) {
        q = &o->particles[i];
        /* regalloc_patterns 73: the age test spells the element out again, so
         * the address becomes a CSE temp that is coloured before the split
         * temp of the shared counter (q r30, i r29). */
        if (!(o->particles[i].age < lbl_806D9440) && fn_801379F0(&q->pos, lbl_806D9448)) {
            PSMTXScale(m, q->scale, q->scale, q->scale);
            PSMTXConcat(m, *view, m);
            m[0][3] = q->pos.x;
            m[1][3] = q->pos.y;
            m[2][3] = q->pos.z;
            Object_SetColorAlphaOnly(o->billboard, 0, q->alpha);
            GXChannel_PushTransform(&ch, m);
        }
    }
}


