#include "game/types/size_t.h"

/* clDrawManager: the singleton that collects draw callbacks into depth
 * buckets and runs them back to front. 0x80079B24..0x8007ADC0. */

void *operator new(size_t);
void *operator new[](size_t);
void operator delete(void *);
void operator delete[](void *);

extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int, float);
void DebugPrintf(const char *, ...);
int Clamp_Int(int, int, int);
void *GetCourseScene3D(void);
void CObj_UnprojectPoint(void *, float, float, float, float *, float *, float *);
extern const float lbl_806D2F20, lbl_806D2F24, lbl_806D2F28, lbl_806D2F2C, lbl_806D2F30;
}

typedef void (*DrawCallback)(void *);

struct DrawNode {
    DrawCallback callback;
    void *object;
    float z;
    DrawNode *prev, *next;
    DrawNode();
    ~DrawNode();
    void Reset() {
        callback = 0;
        object = 0;
        z = lbl_806D2F24;
        prev = 0;
        next = 0;
    }
};

struct DrawBucket {
    DrawNode head, tail;
    DrawBucket();
    ~DrawBucket();
    void Dispatch();
    void Reset() {
        head.Reset();
        tail.Reset();
        head.z = lbl_806D2F20;
        tail.z = lbl_806D2F24;
        head.next = &tail;
        tail.prev = &head;
    }
    int Insert(DrawNode *node) {
        float z = node->z;
        if (head.z <= z) {
            head.next->prev = node;
            node->prev = &head;
            node->next = head.next;
            head.next = node;
            return 1;
        }
        DrawNode *cur = head.next;
        DrawNode *end = &tail;
        while (cur != end) {
            if (cur->z <= z) {
                cur->prev->next = node;
                node->prev = cur->prev;
                cur->prev = node;
                node->next = cur;
                return 1;
            }
            cur = cur->next;
        }
        tail.prev->next = node;
        node->prev = tail.prev;
        tail.prev = node;
        node->next = end;
        return 1;
    }
};

class clDrawManager;
typedef clDrawManager DrawManager;
extern "C" DrawManager *lbl_806D10AC;

/* The singleton base of the original (RTTI name "teSingleton<clDrawManager>"). */
template <class T> struct teSingleton {
    teSingleton() { lbl_806D10AC = (T *)this; }
    virtual ~teSingleton();
};
/* fakematch (deferred codegen order): the natural code is the inline
 * `virtual ~teSingleton() {}` in the template; as a specialization it is an
 * ordinary function, which deferred mode emits last, where the original has
 * it (docs/notes/rtti_classes.md). */
template <> teSingleton<clDrawManager>::~teSingleton() {}

class clDrawManager : public teSingleton<clDrawManager> {
public:
    DrawBucket *buckets;
    DrawNode *nodes;
    int bucketCount, nodeCapacity, nodeCount;
    float maxClipZ, minClipZ, depthStep, inverseStep;
    clDrawManager() {
        buckets = 0;
        nodes = 0;
        DebugPrintf("clDrawManager constructor\n");
        bucketCount = 100;
        buckets = new DrawBucket[bucketCount];
        nodeCapacity = 512;
        nodes = new DrawNode[nodeCapacity];
        maxClipZ = lbl_806D2F20;
        minClipZ = lbl_806D2F24;
        depthStep = lbl_806D2F28;
        inverseStep = lbl_806D2F2C / depthStep;
        Reset();
    }
    virtual ~clDrawManager();
    void Reset() {
        int i = bucketCount;
        while (i-- > 0) buckets[i].Reset();
        nodeCount = 0;
    }
    DrawNode *AllocateNode() {
        if (nodeCount >= nodeCapacity) return 0;
        DrawNode *node = &nodes[nodeCount];
        ++nodeCount;
        return node;
    }
    int Insert(DrawCallback callback, void *object, float z) {
        DrawNode *node = AllocateNode();
        if (!node) {
            DebugPrintf("clDrawNode empty\n");
            return 0;
        }
        z -= minClipZ;
        node->callback = callback;
        node->object = object;
        node->z = z;
        int bucket = Clamp_Int((int)(z * inverseStep), 0, bucketCount - 1);
        return buckets[bucket].Insert(node);
    }
};

class ScopedTimer {
    unsigned int startTick;
    volatile int slot;
public:
    ScopedTimer(int s) { slot = s; startTick = OSGetTick(); }
    ~ScopedTimer() {
        Profiler_RecordFrame(slot,
            (float)(((OSGetTick() - startTick) * 8) /
            ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D2F30);
    }
};

inline void DrawBucket::Dispatch()
{
    ScopedTimer total(20);
    ScopedTimer draw(42);
    DrawNode *node = head.next;
    DrawNode *end = &tail;
    while (node != end) {
        if (node->callback) node->callback(node->object);
        node = node->next;
    }
}


/* Deferred code generation: the functions below are in reverse address order. */

/* The two no-bias variants test clipping before applying the depth bias. */

extern "C" int clDrawMan_AddSorted_DepthRange(DrawManager *self, DrawCallback callback, void *object,
                                             float x, float y, float z, float bias)
{
    ScopedTimer total(20);
    ScopedTimer sort(41);
    if (!GetCourseScene3D()) return 0;
    float xx, yy, zz;
    CObj_UnprojectPoint(GetCourseScene3D(), x, y, z, &xx, &yy, &zz);
    zz = -zz;
    if (zz < self->minClipZ || zz > self->maxClipZ) return 0;
    return self->Insert(callback, object, zz + bias);
}

extern "C" int clDrawMan_AddSorted_NoDepthBias(DrawManager *self, DrawCallback callback, void *object,
                                              float x, float y, float z, float bias)
{
    ScopedTimer total(20);
    ScopedTimer sort(41);
    if (!GetCourseScene3D()) return 0;
    float xx, yy, zz;
    CObj_UnprojectPoint(GetCourseScene3D(), x, y, z, &xx, &yy, &zz);
    zz = -zz;
    if (zz < self->minClipZ) return 0;
    return self->Insert(callback, object, zz + bias);
}

extern "C" int clDrawMan_AddSorted(DrawManager *self, DrawCallback callback, void *object,
                                  float x, float y, float z, float bias)
{
    ScopedTimer total(20);
    ScopedTimer sort(41);
    if (!GetCourseScene3D()) return 0;
    float xx, yy, zz;
    CObj_UnprojectPoint(GetCourseScene3D(), x, y, z, &xx, &yy, &zz);
    zz = -zz;
    zz += bias;
    if (zz < self->minClipZ) return 0;
    return self->Insert(callback, object, zz);
}

extern "C" void clDrawMan_SetMaxClipZ(DrawManager *self, float z)
{
    self->maxClipZ = z;
}

static inline DrawManager *CurrentDrawManager()
{
    DrawManager *manager = lbl_806D10AC;
    if (!manager) manager = 0;
    return manager;
}

#pragma use_lmw_stmw on
extern "C" void clDrawMan_Buckets_Dispatch(DrawManager *self)
{
    int i = self->bucketCount;
    while (i-- > 0) {
        DrawBucket *bucket = &self->buckets[i];
        bucket->Dispatch();
    }
}

extern "C" void clDrawMan_Buckets_Reset(DrawManager *self)
{
    self->Reset();
}

extern "C" void clDrawMan_EndFrame_NoOp(DrawManager *) {}

extern "C" DrawManager *DrawManager_GetOrCreate()
{
    if (!CurrentDrawManager()) new DrawManager;
    return CurrentDrawManager();
}
#pragma use_lmw_stmw off

DrawBucket::DrawBucket() { Reset(); }
DrawNode::DrawNode() { Reset(); }
DrawBucket::~DrawBucket() {}
DrawNode::~DrawNode() {}

clDrawManager::~clDrawManager()
{
    DebugPrintf("clDrawMan destructor\n");
    delete[] buckets;
    buckets = 0;
    delete[] nodes;
    nodes = 0;
}
