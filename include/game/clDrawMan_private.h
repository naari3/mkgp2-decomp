#ifndef CLDRAWMAN_PRIVATE_H
#define CLDRAWMAN_PRIVATE_H
#include "game/types/size_t.h"

/* Private complete layout of the draw-manager singleton and its sorted lists.
 * Existing callers use an opaque DrawMan view. Array constructors/destructors
 * are supplied by the adjacent NodeList/Free TUs through the symbol bridge. */

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
extern const char lbl_80311B74[], lbl_80311B90[];
extern void *lbl_803FE05C[], *clDrawMan_vtable_803FE068[];
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

struct DrawManager;
extern "C" DrawManager *lbl_806D10AC;

struct DrawManagerBase {
    void **vtable;
    DrawManagerBase() {
        vtable = clDrawMan_vtable_803FE068;
        lbl_806D10AC = (DrawManager *)this;
    }
    ~DrawManagerBase();
};

struct DrawManager : DrawManagerBase {
    DrawBucket *buckets;
    DrawNode *nodes;
    int bucketCount, nodeCapacity, nodeCount;
    float maxClipZ, minClipZ, depthStep, inverseStep;
    DrawManager() {
        vtable = lbl_803FE05C;
        buckets = 0;
        nodes = 0;
        DebugPrintf(lbl_80311B74);
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
            DebugPrintf(lbl_80311B90);
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

#endif
