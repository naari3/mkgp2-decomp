/* Native draft: 99.56% text (asm-A 11-08: rotation declared first in SaveRotations), 1848-byte primary function.
 * Kept NonMatching: save/request/animation GPR webs remain; restore and conversion match. */
#include "game/ObjectDrivePrivate.h"

static inline void SaveRotations(Normal3D *self) {
    Quat *rotation;
    int i;
    JObj *joint;
    rotation=self->savedRotation;
    if (rotation) {
        for (i=0;i<self->count;i++,rotation++) {
            joint=self->table[i];
            GetRotation(joint,rotation);
        }
    }
}
static inline void RestoreRotations(Normal3D *self) {
    int i=0;
    JObj *joint;
    self->pad00[1]=i;
    Quat *rotation=self->savedRotation;
    for (;i<self->count;rotation++,i++) {
        joint=self->table[i];
        SetRotation(joint,rotation);
    }
}
static inline void PrepareRotations(Normal3D *self) {
    if (!self->savedRotation) {
        self->jointCount=clNormal3D_CountJObjs(self,self->root,0);
        self->savedRotation=(Quat *)FUN_8003b120(self->jointCount * sizeof(Quat));
        SaveRotations(self);
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
static inline void RequestDrive(JObj **cursor, int count, float frame) {
    if (cursor != 0) {
        for (int i=0;i<count;++cursor,++i)
            HSD_JObjReqAnimByFlags(*cursor,0x7FF,frame);
    }
}
static inline void AnimateAllDrive(Normal3D *self) {
        JObj **table=self->table;
        int count=self->count;
        if (table) {
            HSD_AObjInitEndCallBack();
            AnimateDrive(table,count);
            HSD_AObjInvokeCallBacks();
        }
}
extern "C" int Object_DriveAnimAndSkin(Normal3D *self, Normal3D *source, float frame, float speed)
{
    JObj **cursor;
    int count_;
    float frame_;
    if (!self->root) return 0;
    PrepareRotations(self);
    self->changed=1;
    self->x=speed;
    if (!source) {
        if (frame>=lbl_806D2340) self->frame=frame;
        { ScopedTimer timer(8); Attach(self,self->row); }
        { ScopedTimer timer(11);
        cursor = self->table;
        count_ = self->count;
        frame_ = self->frame;
        if (cursor != 0) {
        for (int i=0;i<count_;++cursor,++i)
        HSD_JObjReqAnimByFlags(*cursor,0x7FF,frame_);
        } }
    } else {
        if (frame>=lbl_806D2340) source->frame=frame;
        { ScopedTimer timer(8); Attach(self,source->row); }
        { ScopedTimer timer(11); RequestDrive(self->table,self->count,source->frame); }
    }
    {
        ScopedTimer timer(7);
        AnimateAllDrive(self);
    }
    ConvertRotations(self);
    self->pad00[1]=1;
    return 1;
}
