/* clNormal3D_Exec (0x80032AAC): per-frame update of a Normal3D model.
 * Advances and loops the animation frame, then requests and runs the
 * joint/material/shape animation under the profiler timers. When the
 * rotations were converted to quaternions (see Object_DriveAnimAndSkin),
 * the saved rotations are restored first and converted again afterwards. */
#include "game/types/Quat.h"
#include "game/types/Vec3.h"
struct JObj;
typedef void (*AnimCallback)(void);
struct JObjClass { unsigned char pad[0x50]; AnimCallback animate; };
struct JObj {
    JObjClass *klass;
    unsigned char pad04[0x10];
    unsigned int flags;
    void *dobj;
    Quat rotation;
    unsigned char pad2C[0x50];
    void *aobj;
};
#include "game/types/AnimRow.h"
struct Normal3D {
    unsigned char pad00[2]; unsigned char changed; unsigned char animated;
    int jointCount;
    float frame, y, z, x;
    unsigned char pad18[8];
    Quat *savedRotation;
    unsigned char pad24[8];
    JObj *root;
    void *model;
    AnimRow *row;
    unsigned char pad38[8];
    JObj **table;
    int count;
};
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int, float);
void HSD_JObjAddAnimAll(JObj *, void *, void *, void *);
void HSD_JObjReqAnimByFlags(JObj *, unsigned int, float);
void HSD_AObjInitEndCallBack(void);
void HSD_AObjInvokeCallBacks(void);
void HSD_AObjInterpretAnim(void *, JObj *, AnimCallback);
void HSD_DObjAnimAll(void *);
void HSD_JObjCheckDepend(JObj *);
extern const float lbl_806D2340;
extern const float lbl_806D2360;
}
class ScopedTimer {
public:
    inline ScopedTimer(int id) { slot = id; start = OSGetTick(); }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(slot,
            (float)(((OSGetTick() - start) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D2360);
    }
private:
    unsigned int start;
    int slot;
};
static inline void *First(void **list) { if (list == 0) return 0; return list[0]; }
static inline void Attach(Normal3D *self, AnimRow *row) {
    void *joint = First(row->joint);
    void *material = First(row->material);
    void *shape = First(row->shape);
    HSD_JObjAddAnimAll(self->root, joint, material, shape);
}
static inline void Request(Normal3D *self, Normal3D *source) {
    int count;
    int i;
    JObj **cursor;
    float frame;
    cursor = self->table;
    frame = source->frame;
    count = self->count;
    if (cursor != 0) {
        for (i = 0; i < count; ++cursor, ++i)
            HSD_JObjReqAnimByFlags(*cursor, 0x7FF, frame);
    }
}
static inline void RequestSelf(Normal3D *self) {
    JObj **cursor;
    float frame;
    int i;
    int count;
    cursor = self->table;
    frame = self->frame;
    count = self->count;
    if (cursor != 0) {
        for (i = 0; i < count; ++cursor, ++i)
            HSD_JObjReqAnimByFlags(*cursor, 0x7FF, frame);
    }
}
static inline bool HasDObj(JObj *node) { return !(node->flags & 0x4020); }
static inline void Animate(JObj **table, int count) {
    if (table != 0) {
        JObj **cursor = table;
        for (int i = 0; i < count; ++cursor, ++i) {
            JObj *node = *cursor;
            if (node != 0) {
                HSD_AObjInterpretAnim(node->aobj, node, node->klass->animate);
                if (HasDObj(node) == true) HSD_DObjAnimAll(node->dobj);
            }
        }
        HSD_JObjCheckDepend(*table);
    }
}
extern "C" {
int clNormal3D_CountJObjs(Normal3D *, JObj *, int);
void *FUN_8003b120(unsigned int);
void HSD_JObjClearFlags(JObj *, unsigned int);
void HSD_JObjSetFlags(JObj *, unsigned int);
void HSD_JObjSetMtxDirtySub(JObj *);
void EulerToQuat(Vec3 *, Quat *);
void __assert(char *, int, char *);
extern char lbl_806D2348[7], lbl_806D2350[5], lbl_806D2370[4];
}
static inline unsigned char Dirty(JObj *j) {
    unsigned char result=0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) result=1;
    return result;
}
static inline void SetDirty(JObj *j) {
    if (j) {
        if (!j) __assert(lbl_806D2348,0x25D,lbl_806D2350);
        if (!Dirty(j)) HSD_JObjSetMtxDirtySub(j);
    }
}
static inline void GetRotation(JObj *j, Quat *q) {
    if (!j) __assert(lbl_806D2348,0x2DD,lbl_806D2350);
    if (!q) __assert(lbl_806D2348,0x2DE,lbl_806D2370);
    q->x=j->rotation.x; q->y=j->rotation.y; q->z=j->rotation.z; q->w=j->rotation.w;
}
static inline void SetRotation(JObj *j, Quat *q) {
    if (!j) __assert(lbl_806D2348,0x290,lbl_806D2350);
    if (!q) __assert(lbl_806D2348,0x291,lbl_806D2370);
    j->rotation.x=q->x; j->rotation.y=q->y; j->rotation.z=q->z; j->rotation.w=q->w;
    if (!(j->flags & 0x2000000)) SetDirty(j);
}


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
static inline void RestoreAnimationState(Normal3D *self) {
        int i;
        for (i=0;i<self->count;i++) {
            JObj *j=self->table[i];
            if (j) HSD_JObjClearFlags(j,0x20000);
        }
        i=0;
        self->pad00[1]=i;
        Quat *rotation=self->savedRotation;
        for (;i<self->count;rotation++,i++) SetRotation(self->table[i],rotation);
}
extern "C" int clNormal3D_Exec(Normal3D *self)
{
    JObj **cursor1;
    JObj *node1;
    int i1;
    JObj *node2;
    int i2;
    JObj **cursor2;
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
        { ScopedTimer timer(11); RequestSelf(self); }
        {
            ScopedTimer timer(7);
            JObj **table=self->table;
            int count=self->count;
            if (table) {
                HSD_AObjInitEndCallBack();
                if (table != 0) {
                    cursor1 = table;
                    for (i1 = 0; i1 < count; ++cursor1, ++i1) {
                        node1 = *cursor1;
                        if (node1 != 0) {
                            HSD_AObjInterpretAnim(node1->aobj, node1, node1->klass->animate);
                            if (HasDObjExec(node1)) HSD_DObjAnimAll(node1->dobj);
                        }
                    }
                    HSD_JObjCheckDepend(*table);
                }
                HSD_AObjInvokeCallBacks();
            }
        }
    } else if (self->savedRotation) {
        RestoreAnimationState(self);
        { ScopedTimer timer(8); Attach(self,self->row); }
        { ScopedTimer timer(11); RequestSelf(self); }
        {
            ScopedTimer timer(7);
            JObj **table=self->table;
            int count=self->count;
            if (table) {
                HSD_AObjInitEndCallBack();
                if (table != 0) {
                    cursor2 = table;
                    for (i2 = 0; i2 < count; ++cursor2, ++i2) {
                        node2 = *cursor2;
                        if (node2 != 0) {
                            HSD_AObjInterpretAnim(node2->aobj, node2, node2->klass->animate);
                            if (HasDObjExec(node2)) HSD_DObjAnimAll(node2->dobj);
                        }
                    }
                    HSD_JObjCheckDepend(*table);
                }
                HSD_AObjInvokeCallBacks();
            }
        }
        ConvertRotations(self);
        self->pad00[1]=1;
    }
    return 1;
}
