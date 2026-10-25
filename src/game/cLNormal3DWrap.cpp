/*
 * clNormal3DNodeManager (cLNormal3DWrap): pool of 0x200 render slots over
 * 0x99 shared model handles, 0x80088C84..0x80089834.
 * The base is clNodeManager<char *, clNormal3D *> (an std::map at +4).
 *
 * NonMatching only because of layout: every function is 100%, but the
 * target has virtual dtors with RTTI (vtables lbl_803FE464/lbl_803FE470,
 * type names in .rodata 0x80312810) and emits the base dtor
 * (dtor_800897B8) after ModelHandle_SetInstance. Here the vtable pointers
 * are stored by hand, and CW places the weak base dtor right after the
 * ctor; with real virtuals CW puts the RTTI names in .data instead.
 */

extern "C" {
void *FUN_8003b120(unsigned int size);
void *memset(void *dst, int val, unsigned int n);
void PSMTXIdentity(float m[3][4]);
void AssocTree_FreeAll(void *tree, void *node);

extern const float lbl_806D3280; /* 1.0f */
extern const float lbl_806D3284; /* 0.0f */
extern const float lbl_806D3288; /* -1.0f */
extern int lbl_806D11D8; /* active slot count */
extern int lbl_806D11DC; /* peak active slot count */
extern void *lbl_803FE464[]; /* clNormal3DNodeManager vtable */
extern void *lbl_803FE470[]; /* clNodeManager<char *, clNormal3D *> vtable */

typedef struct ModelEntry {
    void *archive;
    int pad[4];
} ModelEntry;
extern ModelEntry lbl_8041BC00[];

void *ResolveJointByName(void *obj, const char *name);
void fn_802D6948(void *src, float *out);
void Object_BindMatrixSource(void *obj, void *src, int arg);
void Object_DriveAnimMatrix(void *obj);
void Object_ClearAnimBinding(void *obj);
void Object_SetJObjPositionVec(void *obj, float *v);
void Object_SetJObjScaleVec(void *obj, float *v);
void JObj_SetRotationQuat(void *obj, float x, float y, float z);
void Object_SetColorRGBA(void *obj, int arg, float r, float g, float b, float a);
void Object_JObjUpdate_be4(void *obj, int flags);
void Object_JObjUpdate_870(void *obj, int flags);
void fn_802BD6A4(float (*m)[4]);
void clNormal3D_SetScale(void *obj, int arg, float a, float b, float c, float d);
void Object_RenderJObjTree(void *obj, int mask);
void Object_RenderJObjEx(void *obj, void *joint, int mask);
}

class clNormal3D {
public:
    clNormal3D(void *archive, void *arg);
    ~clNormal3D();
    unsigned char m_data[0x5C];
};

class ModelHandle {
public:
    ModelHandle(void *archive, void *instance);
    ~ModelHandle() {}

    void *m_archive;
    void *m_instance;
    int m_refcount;
};

extern "C" {
void *ModelHandle_GetArchive(ModelHandle *h);
void *ModelHandle_GetInstance(ModelHandle *h);
void ModelHandle_IncRefcount(ModelHandle *h);
int ModelHandle_DecRefcountToZero(ModelHandle *h);
void ModelHandle_SetInstance(ModelHandle *h, void *instance);
}

class cLNormal3DWrap_Slot {
public:
    cLNormal3DWrap_Slot();
    ~cLNormal3DWrap_Slot();

    inline void ScrollUV(float du, float dv)
    {
        float u;
        float v;

        if (uvMtxValid == 0) {
            PSMTXIdentity(uvMtx);
            uvMtxValid = 1;
        }
        u = uvMtx[0][3] + du;
        v = uvMtx[1][3] + dv;
        if (u > 0.0f) {
            while (u > 1.0f) {
                u -= 1.0f;
            }
        } else {
            while (u < -1.0f) {
                u += 1.0f;
            }
        }
        if (v > 0.0f) {
            while (v > 1.0f) {
                v -= 1.0f;
            }
        } else {
            while (v < -1.0f) {
                v += 1.0f;
            }
        }
        uvMtx[0][3] = u;
        uvMtx[1][3] = v;
    }

    inline void Deactivate()
    {
        if (active) {
            lbl_806D11D8--;
            active = 0;
        }
    }

    inline void Activate(ModelHandle *h, int index)
    {
        lbl_806D11D8++;
        if (lbl_806D11D8 > lbl_806D11DC) {
            lbl_806D11DC = lbl_806D11D8;
        }
        active = 1;
        uvMtxValid = 0;
        model = h;
        matrixSource = 0;
        color[0] = lbl_806D3280;
        color[1] = lbl_806D3280;
        color[2] = lbl_806D3280;
        color[3] = lbl_806D3280;
        pos[0] = lbl_806D3284;
        pos[1] = lbl_806D3284;
        pos[2] = lbl_806D3284;
        rot[0] = lbl_806D3284;
        rot[1] = lbl_806D3284;
        rot[2] = lbl_806D3284;
        renderFlags = 0;
        ScrollUV(0.0f, 0.0f);
        animFrame = lbl_806D3284;
        animSpeed = lbl_806D3280;
        joint = 0;
        modelIndex = index;
    }

    void *matrixSource;
    ModelHandle *model;
    float pos[3];
    float rot[3];
    float scale[3];
    float color[4];
    int renderFlags;
    unsigned char uvMtxValid;
    unsigned char pad41[3];
    float uvMtx[3][4];
    float animFrame;
    float animSpeed;
    void *joint;
    int modelIndex;
    unsigned char active;
};

struct clNodeTree {
    ~clNodeTree()
    {
        if (m_root != 0) {
            AssocTree_FreeAll(this, m_root);
        }
    }

    int m_header;
    void *m_root;
};

struct clNodeMap {
    clNodeTree m_tree;
    int m_pad[2];
};

struct clNodeKeyCmp {};
struct clNodeAlloc {};
extern "C" void AssocTree_Init(void *tree, clNodeKeyCmp *cmp, clNodeAlloc *alloc);

template <class K, class V>
class clNodeManager {
public:
    clNodeManager()
    {
        clNodeKeyCmp cmp;
        clNodeAlloc alloc;
        m_vtable = lbl_803FE470;
        AssocTree_Init(m_map, &cmp, &alloc);
    }
    ~clNodeManager()
    {
        m_vtable = lbl_803FE470;
        ((clNodeMap *)m_map)->~clNodeMap();
    }

    void **m_vtable;
    /* std::map<char *, clNormal3D *>; raw storage so that the ctor (an
     * out-of-line map ctor call) registers no member cleanup. */
    unsigned char m_map[0x10];
};

class clNormal3DNodeManager : public clNodeManager<char *, clNormal3D *> {
public:
    clNormal3DNodeManager();
    ~clNormal3DNodeManager();

    inline cLNormal3DWrap_Slot *PopFreeSlot()
    {
        if (m_freeCount <= 0) {
            return 0;
        }
        m_freeCount--;
        return m_freeList[m_freeCount];
    }

    ModelHandle **m_handles;
    cLNormal3DWrap_Slot *m_slots;
    cLNormal3DWrap_Slot **m_freeList;
    int m_freeCount;
};

extern "C" void cLNormal3DWrap_Mgr_ReleaseSlot(clNormal3DNodeManager *mgr, cLNormal3DWrap_Slot *slot)
{
    if (slot != 0) {
        ModelHandle_GetArchive(slot->model);
        slot->Deactivate();
        if (mgr->m_freeCount < 0x200) {
            mgr->m_freeList[mgr->m_freeCount] = slot;
            mgr->m_freeCount++;
        }
    }
}

extern "C" cLNormal3DWrap_Slot *cLNormal3DWrap_Mgr_AcquireSlot(clNormal3DNodeManager *mgr, int index, void *arg)
{
    void *archive;
    cLNormal3DWrap_Slot *slot;

    if (index < 0 || index >= 0x98) {
        return 0;
    }
    archive = lbl_8041BC00[index].archive;
    if (ModelHandle_GetInstance(mgr->m_handles[index]) != 0) {
        slot = mgr->PopFreeSlot();
        if (slot == 0) {
            return 0;
        }
        ModelHandle_IncRefcount(mgr->m_handles[index]);
        slot->Activate(mgr->m_handles[index], index);
        return slot;
    }
    ModelHandle_SetInstance(mgr->m_handles[index], new clNormal3D(archive, arg));
    ModelHandle_IncRefcount(mgr->m_handles[index]);
    slot = mgr->PopFreeSlot();
    slot->Activate(mgr->m_handles[index], index);
    return slot;
}

clNormal3DNodeManager::~clNormal3DNodeManager()
{
    int i;
    clNormal3D *obj;

    m_vtable = lbl_803FE464;
    lbl_806D11D8 = 0;
    for (i = 0; i < 0x99; i++) {
        if (m_handles[i] != 0) {
            obj = (clNormal3D *)ModelHandle_GetInstance(m_handles[i]);
            if (obj != 0) {
                delete obj;
            }
            ModelHandle_SetInstance(m_handles[i], 0);
            delete m_handles[i];
            m_handles[i] = 0;
        }
    }
    delete[] m_freeList;
    delete[] m_slots;
    delete[] m_handles;
}

clNormal3DNodeManager::clNormal3DNodeManager()
{
    int i;
    int j;

    m_vtable = lbl_803FE464;
    m_handles = new ModelHandle *[0x99];
    memset(m_handles, 0, 0x99 * sizeof(ModelHandle *));
    m_slots = new cLNormal3DWrap_Slot[0x200];
    m_freeList = new cLNormal3DWrap_Slot *[0x200];
    for (i = 0; i < 0x200; i++) {
        m_freeList[i] = &m_slots[i];
    }
    m_freeCount = 0x200;
    for (j = 0; j < 0x99; j++) {
        m_handles[j] = new ModelHandle(lbl_8041BC00[j].archive, 0);
        if (m_handles[j] != 0) {
            ModelHandle_DecRefcountToZero(m_handles[j]);
        }
    }
}

cLNormal3DWrap_Slot::~cLNormal3DWrap_Slot()
{
    Deactivate();
}

cLNormal3DWrap_Slot::cLNormal3DWrap_Slot()
{
    active = 0;
}

extern "C" void cLNormal3DWrap_Slot_ResolveJoint(cLNormal3DWrap_Slot *slot, const char *name)
{
    slot->joint = ResolveJointByName(ModelHandle_GetInstance(slot->model), name);
}

extern "C" void cLNormal3DWrap_Slot_SetAnimSpeed(cLNormal3DWrap_Slot *slot, float speed)
{
    slot->animSpeed = speed;
}

extern "C" void cLNormal3DWrap_Slot_SetAnimFrame(cLNormal3DWrap_Slot *slot, float frame)
{
    slot->animFrame = frame;
}

extern "C" void cLNormal3DWrap_Slot_ClearMatrixSource(cLNormal3DWrap_Slot *slot)
{
    slot->matrixSource = 0;
}

extern "C" void cLNormal3DWrap_Slot_SetMatrixSource(cLNormal3DWrap_Slot *slot, void *src)
{
    slot->matrixSource = src;
}

extern "C" void cLNormal3DWrap_Slot_SetRotationQuat(cLNormal3DWrap_Slot *slot, float r, float g, float b, float a)
{
    slot->color[0] = r;
    slot->color[1] = g;
    slot->color[2] = b;
    slot->color[3] = a;
}

extern "C" void cLNormal3DWrap_Slot_AdvanceUVScrollWrapped(cLNormal3DWrap_Slot *slot, float du, float dv)
{
    float u;
    float v;

    if (slot->uvMtxValid == 0) {
        PSMTXIdentity(slot->uvMtx);
        slot->uvMtxValid = 1;
    }
    u = slot->uvMtx[0][3] + du;
    v = slot->uvMtx[1][3] + dv;
    if (u > 0.0f) {
        while (u > 1.0f) {
            u -= 1.0f;
        }
    } else {
        while (u < -1.0f) {
            u += 1.0f;
        }
    }
    if (v > 0.0f) {
        while (v > 1.0f) {
            v -= 1.0f;
        }
    } else {
        while (v < -1.0f) {
            v += 1.0f;
        }
    }
    slot->uvMtx[0][3] = u;
    slot->uvMtx[1][3] = v;
}

extern "C" void cLNormal3DWrap_Slot_SetRenderFlags(cLNormal3DWrap_Slot *slot, int flags)
{
    slot->renderFlags = flags;
}

extern "C" void cLNormal3DWrap_Slot_SetRotationZ(cLNormal3DWrap_Slot *slot, float z)
{
    slot->rot[2] = z;
}

extern "C" void cLNormal3DWrap_Slot_SetRotationXYZ(cLNormal3DWrap_Slot *slot, float x, float y, float z)
{
    slot->rot[0] = x;
    slot->rot[1] = y;
    slot->rot[2] = z;
}

extern "C" void cLNormal3DWrap_Slot_SetScaleVec3(cLNormal3DWrap_Slot *slot, float x, float y, float z)
{
    slot->scale[0] = x;
    slot->scale[1] = y;
    slot->scale[2] = z;
}

extern "C" void cLNormal3DWrap_Slot_SetPositionXYZ(cLNormal3DWrap_Slot *slot, float x, float y, float z)
{
    slot->pos[0] = x;
    slot->pos[1] = y;
    slot->pos[2] = z;
}

extern "C" void cLNormal3DWrap_Slot_GetOrLoadJointTransform(cLNormal3DWrap_Slot *slot, float *out)
{
    if (slot->matrixSource == 0) {
        out[0] = slot->pos[0];
        out[1] = slot->pos[1];
        out[2] = slot->pos[2];
    } else {
        fn_802D6948(slot->matrixSource, out);
    }
}

extern "C" void cLNormal3DWrap_Slot_AdvanceAnimFrame(cLNormal3DWrap_Slot *slot)
{
    slot->animFrame += slot->animSpeed;
}

extern "C" void cLNormal3DWrap_Slot_Render(cLNormal3DWrap_Slot *slot)
{
    void *obj = ModelHandle_GetInstance(slot->model);

    if (slot->matrixSource != 0) {
        Object_BindMatrixSource(obj, slot->matrixSource, 0);
        Object_DriveAnimMatrix(obj);
    } else {
        Object_ClearAnimBinding(obj);
        Object_SetJObjPositionVec(obj, slot->pos);
        Object_SetJObjScaleVec(obj, slot->scale);
        JObj_SetRotationQuat(obj, slot->rot[0], slot->rot[1], slot->rot[2]);
    }
    Object_SetColorRGBA(obj, 0, slot->color[0], slot->color[1], slot->color[2], slot->color[3]);
    Object_JObjUpdate_be4(obj, 0x800);
    Object_JObjUpdate_870(obj, slot->renderFlags);
    if (slot->uvMtxValid == 1) {
        fn_802BD6A4(slot->uvMtx);
    }
    clNormal3D_SetScale(obj, 0, slot->animFrame, lbl_806D3280, lbl_806D3284, lbl_806D3284);
    obj = ModelHandle_GetInstance(slot->model);
    if (slot->joint == 0) {
        Object_RenderJObjTree(obj, 7);
    } else {
        Object_RenderJObjEx(obj, slot->joint, 7);
    }
    fn_802BD6A4(0);
}

void *ModelHandle_GetArchive(ModelHandle *h)
{
    return h->m_archive;
}

void *ModelHandle_GetInstance(ModelHandle *h)
{
    return h->m_instance;
}

extern "C" void ModelHandle_IncRefcount(ModelHandle *h)
{
    h->m_refcount++;
}

extern "C" int ModelHandle_DecRefcountToZero(ModelHandle *h)
{
    return --h->m_refcount <= 0 ? 1 : 0;
}

ModelHandle::ModelHandle(void *archive, void *instance)
{
    m_archive = archive;
    m_instance = instance;
    m_refcount = 1;
}

extern "C" void ModelHandle_SetInstance(ModelHandle *h, void *instance)
{
    h->m_instance = instance;
}
