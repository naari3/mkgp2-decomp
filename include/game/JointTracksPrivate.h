#ifndef GAME_JOINT_TRACKS_PRIVATE_H
#define GAME_JOINT_TRACKS_PRIVATE_H

extern "C" {
#include "sysdolphin/baselib/jobj.h"
void *Alloc(unsigned long);
void MemoryManager_TimedFree(void *);
HSD_JObj *ResolveJointByName(void *, const char *);
HSD_JObj *HSD_JObjAlloc();
void HSD_JObjSetFlags(HSD_JObj *, unsigned int);
void HSD_JObjSetFlagsAll(HSD_JObj *, unsigned int);
void HSD_JObjClearFlagsAll(HSD_JObj *, unsigned int);
void HSD_JObjSetupMatrixSub(HSD_JObj *);
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
void HSD_JObjReqAnim(HSD_JObj *, float);
void HSD_JObjDispAll(HSD_JObj *, int, int, int);
void fn_802D0EC0(HSD_JObj *);
void PSMTXCopy(const float (*)[4], float (*)[4]);
void __assert(const char *, int, const char *);
void DebugPrintf(const char *, ...);
int strcmp(const char *, const char *);
extern const char lbl_806DBDE4[7], lbl_806DBDEC[5], lbl_806DBDF4[4];
extern const float lbl_806DBDE0, lbl_806DBE00;
extern const unsigned char lbl_804EE6C0[], JointTracks_data_804EE68C[], lbl_804EE6AC[];
extern int g_cupId;
}

void *operator new(unsigned long);
void operator delete(void *);

// The canonical JObj header leaves the transform portion opaque.
struct JointTransform {
    float rotation[4];
    float scale[3];
    float translation[3];
    float matrix[3][4];
};
static inline JointTransform *Transform(HSD_JObj *j) {
    return (JointTransform *)j->_pad_1c;
}
static inline unsigned char NeedsMatrix(HSD_JObj *j) {
    if (!j) __assert(lbl_806DBDE4, 0x25D, lbl_806DBDEC);
    unsigned int flags = j->flags;
    unsigned char result = 0;
    if (!(flags & 0x800000) && (flags & 0x40)) result = 1;
    return result;
}
static inline void DirtyMatrix(HSD_JObj *j) {
    if (j && !NeedsMatrix(j)) HSD_JObjSetMtxDirtySub(j);
}
static inline float (*Matrix(HSD_JObj *j))[4] {
    if (!j) __assert(lbl_806DBDE4, 0x47C, lbl_806DBDEC);
    if (j && NeedsMatrix(j)) HSD_JObjSetupMatrixSub(j);
    return Transform(j)->matrix;
}
static inline void SetMatrix(HSD_JObj *j, float (*m)[4]) {
    if (!j) __assert(lbl_806DBDE4, 0x495, lbl_806DBDEC);
    if (!m) __assert(lbl_806DBDE4, 0x496, lbl_806DBDF4);
    PSMTXCopy(m, Transform(j)->matrix);
    j->flags |= 0x03800000;
    DirtyMatrix(j);
}

struct TrackKey { short frame; short reserved; float value; };
struct TrackSet { const TrackKey *channels[9]; };
struct TrackState { int key, frame; };
struct JointTask {
    const unsigned char *vtable;
    HSD_JObj *joint;
    JointTask(HSD_JObj *j) { vtable = lbl_804EE6C0; joint = j; }
    ~JointTask();
};
struct MatrixChild {
    HSD_JObj *joint;
    float matrix[3][4];
    MatrixChild(HSD_JObj *parent, HSD_JObj *source) : joint(0) {
        joint = HSD_JObjAlloc();
        HSD_JObjSetFlags(joint, 0x1000);
        joint->child = parent;
        PSMTXCopy(Matrix(source), matrix);
        SetMatrix(joint, matrix);
    }
    ~MatrixChild() { fn_802D0EC0(joint); }
};
struct ChildVector {
    void *allocation;
    unsigned int count;
    MatrixChild **start;
    MatrixChild **End() { return start + count; }
};
struct TrackTask : JointTask {
    const TrackSet *tracks;
    TrackState state[9];
    ChildVector children;
    TrackTask(HSD_JObj *j, const TrackSet *t) : JointTask(j) {
        vtable = JointTracks_data_804EE68C;
        tracks = t;
        children.allocation = 0; children.count = 0; children.start = 0;
        state[0].frame = 0; state[0].key = 0;
        state[1].frame = 0; state[1].key = 0;
        state[2].frame = 0; state[2].key = 0;
        state[3].frame = 0; state[3].key = 0;
        state[4].frame = 0; state[4].key = 0;
        state[5].frame = 0; state[5].key = 0;
        state[6].frame = 0; state[6].key = 0;
        state[7].frame = 0; state[7].key = 0;
        state[8].frame = 0; state[8].key = 0;
    }
};
struct AnimTask : JointTask {
    AnimTask(HSD_JObj *j) : JointTask(j) {
        vtable = lbl_804EE6AC;
        HSD_JObjReqAnim(joint, lbl_806DBDE0);
    }
};
struct DispatchTask { virtual ~DispatchTask(); };
struct TaskBucket {
    void *allocation;
    unsigned int count;
    DispatchTask **start;
    DispatchTask **End() { return start + count; }
};
struct TrackBinding { const char *name; const TrackSet *tracks; };
struct ChildBinding { const char *name; const char **children; };
struct TrackGroup {
    const char *name;
    const TrackBinding *tracks;
    const ChildBinding *children;
    const char **animated;
};
extern "C" {
void PtrVec_InsertFill(void *, void *, unsigned int, const void *);
void __destroy_arr(void *, void *, unsigned int, unsigned int);
void __construct_array(void *, void *, void *, unsigned int, unsigned int);
void *fn_80240764(TaskBucket *, short);
void *fn_80241C08(TaskBucket *);
void fn_802400A4(TaskBucket *, const ChildBinding *, int, void *);
int fn_80240378(TaskBucket *, const char *, int, void *, const TrackGroup *);
}
static inline void Append(TaskBucket *b, TrackTask *&p) {
    PtrVec_InsertFill(b, b->End(), 1, &p);
}
static inline void Append(TaskBucket *b, AnimTask *&p) {
    PtrVec_InsertFill(b, b->End(), 1, &p);
}
static inline void AppendChild(ChildVector *b, MatrixChild *p) {
    PtrVec_InsertFill(b, b->End(), 1, &p);
}
#endif
