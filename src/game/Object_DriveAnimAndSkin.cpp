/* Native draft: 98.521645% text. Kept NonMatching: GPR webs and a
 * four-byte size difference remain after three bounded approaches. */
#include "game/ObjectDrivePrivate.h"

static inline void PrepareRotations(Normal3D *self) {
    int i;
    if (!self->savedRotation) {
        self->jointCount=clNormal3D_CountJObjs(self,self->root,0);
        self->savedRotation=(Quat *)FUN_8003b120(self->jointCount * sizeof(Quat));
        Quat *rotation=self->savedRotation;
        if (rotation) {
            for (i=0;i<self->count;i++,rotation++) GetRotation(self->table[i],rotation);
        }
    } else {
        for (i=0;i<self->count;i++) {
            JObj *j=self->table[i];
            if (j) HSD_JObjClearFlags(j,0x20000);
        }
        i=0;
        self->pad00[1]=i;
        Quat *rotation=self->savedRotation;
        for (;i<self->count;rotation++,i++) SetRotation(self->table[i],rotation);
    }
}
static inline void ConvertRotations(Normal3D *self) {
    int i;
    for (i=0;i<self->count;i++) {
        JObj *j=self->table[i];
        if (j) {
            Quat q;
            Vec3 v;
            GetRotation(j,&q);
            v.x=q.x; v.y=q.y; v.z=q.z;
            EulerToQuat(&v,&q);
            SetRotation(j,&q);
            HSD_JObjSetFlags(j,0x20000);
        }
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
            Animate(table,count);
            HSD_AObjInvokeCallBacks();
        }
    }
    ConvertRotations(self);
    self->pad00[1]=1;
    return 1;
}
