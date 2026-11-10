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
