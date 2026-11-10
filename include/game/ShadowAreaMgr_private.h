#ifndef GAME_SHADOWAREAMGR_PRIVATE_H
#define GAME_SHADOWAREAMGR_PRIVATE_H

/* Shadow area manager: up to 0x40 convex shadow volumes (6 planes each)
 * built from an archive; QueryPoint tests a point against all of them. */
extern "C" {
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/dobj.h"
}

typedef unsigned char u8;
typedef unsigned int u32;
#define TRUE 1
#define FALSE 0

struct Vec3f {
    float x, y, z;
    Vec3f() {}
    ~Vec3f() {}
    Vec3f(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float Dot(const Vec3f &o) const {
        float xx = x * o.x;
        float yy = y * o.y;
        float zz = z * o.z;
        return zz + (xx + yy);
    }
    void Set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    void Sub(const Vec3f &a, const Vec3f &b) {
        x = a.x - b.x;
        y = a.y - b.y;
        z = a.z - b.z;
    }
    void CrossFrom(const Vec3f &a, const Vec3f &b) {
        float cx, cz, cy;
        cx = a.y * b.z - a.z * b.y;
        cy = a.z * b.x - a.x * b.z;
        cz = a.x * b.y - a.y * b.x;
        Set(cx, cy, cz);
    }
    void Normalize();
};

typedef struct ShadowAreaEdge {
    Vec3f point;
    Vec3f normal;
} ShadowAreaEdge;

struct ShadowAreaMesh { u32 words[0x48]; };

typedef struct ShadowAreaEntry {
    u8 valid;
    u8 pad1[3];
    ShadowAreaMesh src;
    ShadowAreaEdge edges[6];
} ShadowAreaEntry;


typedef struct ShadowAreaSrc {
    Vec3f origin;
    Vec3f a;
    Vec3f b;
    Vec3f pad;
} ShadowAreaSrc;

#ifdef __cplusplus
extern "C" {
#endif
extern void *ShadowAreaMgr_Ctor(void *self, void *archive);
extern void *ShadowAreaEdge_Dtor(void *self, short flag);
extern void MemoryManager_TimedFree(void *);
extern void *__construct_array(void *arr, void *ctor, void *dtor, u32 size, u32 count);
extern void *Archive_GetRootJObj(void *);
extern u8 fn_80184928(void *, void *, void *);
extern void Object_DtorWithGXSync(void *, int);
void fn_800AB130(void);
extern int ShadowAreaEntry_ComputeEdgeNormals(ShadowAreaEntry *self, ShadowAreaSrc *src);


extern char ShadowAreaBase_vtable_80411E10[];
#ifdef __cplusplus
}
#endif

struct ShadowAreaMgr {
    ShadowAreaMgr(void *archive);
    virtual ~ShadowAreaMgr();
    ShadowAreaEntry entries[0x40];
    int count;
};
extern "C" ShadowAreaMgr *g_shadowAreaMgr;

/* PObj has no public layout header yet; only its next link is used here. */
struct HSD_PObj {
    void *class_info;
    HSD_PObj *next;
};

static inline HSD_PObj *DObjGetPObj(HSD_DObj *p) { return p ? p->pobj : 0; }
static inline HSD_DObj *DObjNext(HSD_DObj *p) { return p ? p->next : 0; }
static inline HSD_PObj *PObjNext(HSD_PObj *p) { return p ? p->next : 0; }

struct SAArchiveModel {
    char opaque[0x5c];
    SAArchiveModel(void *archive, int flags);
};
struct SAArchiveOwner {
    SAArchiveModel *object;
    SAArchiveOwner(SAArchiveModel *p) : object(p) {}
    ~SAArchiveOwner() throw() { Object_DtorWithGXSync(object, 1); }
};
extern "C" HSD_DObj *HSD_JObjGetDObj(HSD_JObj *);

#endif
