/* NonMatching (99.09%): GPR webs in the request/animate/restore blocks, as in
 * the sibling Object_DriveAnimAndSkin. */
/* clNormal3D_Exec (0x80032AAC): per-frame update of a Normal3D model.
 * Advances and loops the animation frame, then requests and runs the
 * joint/material/shape animation under the profiler timers. When the
 * rotations were converted to quaternions (see Object_DriveAnimAndSkin),
 * the saved rotations are restored first and converted again afterwards. */
#include "game/ObjectDrivePrivate.h"

static inline void ClearRotationFlags(Normal3D *self) {
    for (int i=0;i<self->count;i++) {
        JObj *j=self->table[i];
        if (j) HSD_JObjClearFlags(j,0x20000);
    }
}
static inline void RestoreRotations(Normal3D *self) {
    int i=0;
    self->pad00[1]=i;
    Quat *rotation=self->savedRotation;
    for (;i<self->count;rotation++,i++) SetRotation(self->table[i],rotation);
}
static inline void ConvertRotations(Normal3D *self) {
    int i;
    for (i=0;i<self->count;i++) {
        JObj *j=self->table[i];
        if (j) {
            Vec3 v;
            Quat q;
            GetRotation(j,&q);
            v.x=q.x; v.y=q.y; v.z=q.z;
            EulerToQuat(&v,&q);
            SetRotation(j,&q);
            HSD_JObjSetFlags(j,0x20000);
        }
    }
}
static inline int HasDObjExec(JObj *node) { if (node->flags & 0x4020) return 0; return 1; }
static inline void AnimateExec(JObj **table, int count) {
    if (table != 0) {
        JObj **cursor = table;
        for (int i = 0; i < count; ++cursor, ++i) {
            JObj *node = *cursor;
            if (node != 0) {
                HSD_AObjInterpretAnim(node->aobj, node, node->klass->animate);
                if (HasDObjExec(node)) HSD_DObjAnimAll(node->dobj);
            }
        }
        HSD_JObjCheckDepend(*table);
    }
}
static inline void RunAnimation(Normal3D *self) {
    ScopedTimer timer(7);
    JObj **table=self->table;
    int count=self->count;
    if (table) {
        HSD_AObjInitEndCallBack();
        AnimateExec(table,count);
        HSD_AObjInvokeCallBacks();
    }
}
extern "C" int clNormal3D_Exec(Normal3D *self)
{
    if (!self->root) return 0;
    if (self->frame < lbl_806D2340) return 0;
    if (self->changed) {
        self->changed=0;
    } else {
        self->frame=self->frame+self->x;
        if (lbl_806D2340 < self->z && self->z < self->frame) self->frame=self->y;
    }
    AnimRow *row=self->row;
    if (!First(row->joint) && !First(row->material) && !First(row->shape)) return 1;
    if (!self->pad00[1]) {
        { ScopedTimer timer(11); Request(self,self); }
        {
            ScopedTimer timer(7);
            JObj **table=self->table;
            int count=self->count;
            if (table) {
                HSD_AObjInitEndCallBack();
                AnimateExec(table,count);
                HSD_AObjInvokeCallBacks();
            }
        }
    } else if (self->savedRotation) {
        ClearRotationFlags(self);
        RestoreRotations(self);
        { ScopedTimer timer(8); Attach(self,self->row); }
        { ScopedTimer timer(11); Request(self,self); }
        {
            ScopedTimer timer(7);
            JObj **table=self->table;
            int count=self->count;
            if (table) {
                HSD_AObjInitEndCallBack();
                AnimateExec(table,count);
                HSD_AObjInvokeCallBacks();
            }
        }
        ConvertRotations(self);
        self->pad00[1]=1;
    }
    return 1;
}
