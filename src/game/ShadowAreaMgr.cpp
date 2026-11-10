#include "game/ShadowAreaMgr_private.h"

#pragma use_lmw_stmw on
extern "C" int ShadowAreaMgr_BuildFromArchive(ShadowAreaMgr *self, void *archive)
{
    u8 buf[0x120];
    HSD_JObj *root;
    int count;
    HSD_DObj *node;
    HSD_PObj *it;

    if (archive == 0) {
        return 0;
    }
    SAArchiveOwner model(new SAArchiveModel(archive, 0));
    root = (HSD_JObj *)Archive_GetRootJObj(model.object);
    count = 0;
    while (root != 0) {
        node = HSD_JObjGetDObj(root);
        while (node != 0) {
            it = DObjGetPObj(node);
            while (it != 0) {
                if (fn_80184928(root, it, buf) == 1) {
                    ShadowAreaEntry_ComputeEdgeNormals(&self->entries[count], (ShadowAreaSrc *)buf);
                    it = PObjNext(it);
                    count++;
                    if (count >= 0x40) {
                        return count;
                    }
                }
            }
            node = DObjNext(node);
        }
        root = root == 0 ? 0 : root->next;
    }
    return count;
}

#pragma use_lmw_stmw reset

static inline const Vec3f &ShadowAreaMgr_GetEdgePoint(ShadowAreaMgr *mgr, int entry, int edge)
{
    return mgr->entries[entry].edges[edge].point;
}

static inline u8 ShadowAreaEntry_Contains(ShadowAreaMgr *mgr, int index, ShadowAreaEntry *self, const Vec3f &p)
{
    int i;

    if (!self->valid) {
        return FALSE;
    }
    for (i = 0; i < 6; i++) {
        Vec3f d;
        d.Sub(p, ShadowAreaMgr_GetEdgePoint(mgr, index, i));
        if (d.Dot(self->edges[i].normal) < 0.0f) {
            return FALSE;
        }
    }
    return TRUE;
}

extern "C" int ShadowAreaMgr_QueryPoint(ShadowAreaMgr *self, float x, float y, float z)
{
    Vec3f p(x, y, z);
    int i;

    i = self->count;
    while (i > 0) {
        i--;
        if (ShadowAreaEntry_Contains(self, i, &self->entries[i], p) == TRUE) {
            return 1;
        }
    }
    return 0;
}

extern "C" int ShadowAreaMgr_Destroy(void)
{
    delete g_shadowAreaMgr;
    g_shadowAreaMgr = 0;
    return 1;
}

extern "C" int ShadowAreaMgr_GetOrCreate(void *archive)
{
    if (g_shadowAreaMgr == 0) {
        g_shadowAreaMgr = new ShadowAreaMgr(archive);
    }
    return 1;
}

static inline float ShadowArea_Sqrt(float x)
{
    volatile float result;

    if (x > 0.0f) {
        double g = __frsqrte(x);
        g = 0.5 * g * (3.0 - x * (g * g));
        g = 0.5 * g * (3.0 - x * (g * g));
        g = 0.5 * g * (3.0 - x * (g * g));
        result = (float)(x * g);
        return result;
    }
    return x;
}

inline void Vec3f::Normalize()
{
    float len = ShadowArea_Sqrt(Dot(*this));
    if (len <= 0.0f) {
        z = 0.0f;
        y = 0.0f;
        x = 0.0f;
    } else {
        float s = 1.0f / len;
        x *= s;
        y *= s;
        z *= s;
    }
}

static inline void CrossInto(Vec3f *o, const Vec3f &a, const Vec3f &b)
{
    float cx, cy, cz;
    cy = a.z * b.x - a.x * b.z;
    cz = a.x * b.y - a.y * b.x;
    cx = a.y * b.z - a.z * b.y;
    o->Set(cx, cy, cz);
}

extern "C" int ShadowAreaEntry_ComputeEdgeNormals(ShadowAreaEntry *self, ShadowAreaSrc *src)
{
    int i;
    ShadowAreaEdge *edge;

    if (self->valid == 1) {
        return 0;
    }
    for (i = 0; i < 6; i++) {
        ShadowAreaSrc *s = &src[i];
        edge = &self->edges[i];
        edge->point.Set(s->origin.x, s->origin.y, s->origin.z);
        Vec3f a(s->a.x - s->origin.x, s->a.y - s->origin.y,
                s->a.z - s->origin.z);
        a.Normalize();
        Vec3f b(s->b.x - s->origin.x, s->b.y - s->origin.y,
                s->b.z - s->origin.z);
        b.Normalize();
        CrossInto(&b, a, b);
        edge->normal.Set(b.x, b.y, b.z);
    }
    self->src = *(ShadowAreaMesh *)src;
    self->valid = 1;
    return 1;
}

extern "C" ShadowAreaEntry *ShadowAreaEntry_Ctor(ShadowAreaEntry *self)
{
    self->valid = 0;
    __construct_array(self->edges, (void *)fn_800AB130, (void *)ShadowAreaEdge_Dtor, 0x18, 6);
    return self;
}

extern "C" void fn_800AB130(void)
{
}

extern "C" void *dtor_800AB134(void *self, short flag)
{
    if (self != 0) {
        *(char **)self = ShadowAreaBase_vtable_80411E10;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
