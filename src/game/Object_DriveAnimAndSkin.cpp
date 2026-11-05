/* Native draft: 99.02597% text, exact 1848-byte primary function.
 * Kept NonMatching: rotation/request/animation GPR webs remain. */
#include "game/ObjectDrivePrivate.h"

static inline void SaveRotations(Normal3D *self, Quat *rotation) {
    if (rotation) {
        for (int i=0;i<self->count;i++,rotation++) GetRotation(self->table[i],rotation);
    }
}
static inline void RestoreRotations(Normal3D *self) {
    int i=0;
    self->pad00[1]=i;
    Quat *rotation=self->savedRotation;
    for (;i<self->count;rotation++,i++) SetRotation(self->table[i],rotation);
}
static inline void PrepareRotations(Normal3D *self) {
    if (!self->savedRotation) {
        self->jointCount=clNormal3D_CountJObjs(self,self->root,0);
        self->savedRotation=(Quat *)FUN_8003b120(self->jointCount * sizeof(Quat));
        SaveRotations(self,self->savedRotation);
    } else {
        for (int i=0;i<self->count;i++) {
            JObj *j=self->table[i];
            if (j) HSD_JObjClearFlags(j,0x20000);
        }
        RestoreRotations(self);
    }
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
static inline int HasDObjDrive(JObj *node) { if (node->flags & 0x4020) return 0; return 1; }
static inline void AnimateDrive(JObj **table, int count) {
    if (table != 0) {
        JObj **cursor = table;
        for (int i = 0; i < count; ++cursor, ++i) {
            JObj *node = *cursor;
            if (node != 0) {
                HSD_AObjInterpretAnim(node->aobj, node, node->klass->animate);
                if (HasDObjDrive(node)) HSD_DObjAnimAll(node->dobj);
            }
        }
        HSD_JObjCheckDepend(*table);
    }
}
extern "C" int Object_DriveAnimAndSkin(Normal3D *self, Normal3D *source, float frame, float speed)
{
    if (!self->root) return 0;
    PrepareRotations(self);
    self->changed=1;
    self->x=speed;
    if (!source) {
        if (frame>=lbl_806D2340) self->frame=frame;
        { ScopedTimer timer(8); Attach(self,self->row); }
        { ScopedTimer timer(11); Request(self,self); }
    } else {
        if (frame>=lbl_806D2340) source->frame=frame;
        { ScopedTimer timer(8); Attach(self,source->row); }
        { ScopedTimer timer(11); Request(self,source); }
    }
    {
        ScopedTimer timer(7);
        JObj **table=self->table;
        int count=self->count;
        if (table) {
            HSD_AObjInitEndCallBack();
            AnimateDrive(table,count);
            HSD_AObjInvokeCallBacks();
        }
    }
    ConvertRotations(self);
    self->pad00[1]=1;
    return 1;
}
