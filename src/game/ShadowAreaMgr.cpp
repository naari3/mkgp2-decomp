/* Shadow area manager: up to 0x40 convex shadow volumes (6 planes each)
 * built from an archive; QueryPoint tests a point against all of them. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0

struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3f operator-(const Vec3f &o) const { return Vec3f(x - o.x, y - o.y, z - o.z); }
    float Dot(const Vec3f &o) const {
        float xx = x * o.x;
        float yy = y * o.y;
        float zz = z * o.z;
        return zz + (xx + yy);
    }
    Vec3f Cross(const Vec3f &o) const {
        return Vec3f(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    void Normalize();
};

typedef struct ShadowAreaEdge {
    Vec3f point;
    Vec3f normal;
} ShadowAreaEdge;

typedef struct ShadowAreaEntry {
    u8 valid;
    u8 pad1[3];
    u32 src[0x48];
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
extern void *Alloc(u32 size);
extern void *ShadowAreaMgr_Ctor(void *self, void *archive);
extern void *ShadowAreaEdge_Dtor(void *self, short flag);
extern void MemoryManager_TimedFree(void *);
extern void *__construct_array(void *arr, void *ctor, void *dtor, u32 size, u32 count);
extern void *clNormal3D_Construct(void *self, void *archive, int flag);
extern void *Archive_GetRootJObj(void *);
extern void *fn_802D0758(void *);
extern u8 fn_80184928(void *, void *, void *);
extern void Object_DtorWithGXSync(void *, int);
void fn_800AB130(void);
extern int ShadowAreaEntry_ComputeEdgeNormals(ShadowAreaEntry *self, ShadowAreaSrc *src);


extern char lbl_80411E10[];
#ifdef __cplusplus
}
#endif

struct ShadowAreaMgr {
    ShadowAreaMgr(void *archive);
    virtual ~ShadowAreaMgr();
    ShadowAreaEntry entries[0x40];
    int count;
};
extern "C" ShadowAreaMgr *lbl_806D1060;

typedef struct JObjNode {
    u8 pad0[4];
    struct JObjNode *next;
    struct JObjNode *child;
    struct JObjNode *list;
} JObjNode;

extern "C" int ShadowAreaMgr_BuildFromArchive(ShadowAreaMgr *self, void *archive)
{
    u8 buf[0x120];
    void *model;
    JObjNode *root;
    JObjNode *node;
    JObjNode *it;
    ShadowAreaEntry *entry;
    int count;

    if (archive == 0) {
        return 0;
    }
    model = Alloc(0x5c);
    if (model != 0) {
        clNormal3D_Construct(model, archive, 0);
    }
    entry = self->entries;
    root = (JObjNode *)Archive_GetRootJObj(model);
    count = 0;
    while (root != 0) {
        node = (JObjNode *)fn_802D0758(root);
        while (node != 0) {
            it = node != 0 ? node->list : 0;
            while (it != 0) {
                if (fn_80184928(root, it, buf) == 1) {
                    ShadowAreaEntry_ComputeEdgeNormals(entry, (ShadowAreaSrc *)buf);
                    it = it != 0 ? it->next : 0;
                    count++;
                    entry++;
                    if (count >= 0x40) {
                        Object_DtorWithGXSync(model, 1);
                        return count;
                    }
                }
            }
            node = node != 0 ? node->next : 0;
        }
        root = root == 0 ? 0 : root->child;
    }
    Object_DtorWithGXSync(model, 1);
    return count;
}

static inline BOOL ShadowAreaEntry_Contains(ShadowAreaEntry *self, const Vec3f &p)
{
    int i;

    if (!self->valid) {
        return FALSE;
    }
    for (i = 0; i < 6; i++) {
        Vec3f d = p - self->edges[i].point;
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
        if (ShadowAreaEntry_Contains(&self->entries[i], p) == TRUE) {
            return 1;
        }
    }
    return 0;
}

extern "C" int ShadowAreaMgr_Destroy(void)
{
    delete lbl_806D1060;
    lbl_806D1060 = 0;
    return 1;
}

extern "C" int ShadowAreaMgr_GetOrCreate(void *archive)
{
    if (lbl_806D1060 == 0) {
        lbl_806D1060 = new ShadowAreaMgr(archive);
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

extern "C" int ShadowAreaEntry_ComputeEdgeNormals(ShadowAreaEntry *self, ShadowAreaSrc *src)
{
    int i;
    ShadowAreaSrc *s;
    ShadowAreaEdge *edge;
    Vec3f a;
    Vec3f b;

    if (self->valid == 1) {
        return 0;
    }
    s = src;
    for (i = 0; i < 6; i++) {
        edge = &self->edges[i];
        edge->point = s->origin;
        a = s->a - s->origin;
        a.Normalize();
        b = s->b - s->origin;
        b.Normalize();
        b = a.Cross(b);
        edge->normal = b;
        s = (ShadowAreaSrc *)((u8 *)s + 0x30);
    }
    {
        int j;
        u32 *d = self->src;
        u32 *p = (u32 *)src;
        for (j = 0; j < 0x48; j++) {
            d[j] = p[j];
        }
    }
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
        *(char **)self = lbl_80411E10;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
