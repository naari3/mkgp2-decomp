/* Object JObj binding helpers, 0x80033F10..0x80034508: animation/matrix
 * source binding, JObj display, and the per-frame matrix drive (timed). */
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
extern const float lbl_806D2360;
extern char lbl_806D2348[7]; /* "jobj.h" */
extern char lbl_806D2350[5]; /* "jobj" */
extern char lbl_806D2378[4]; /* "mtx" */
}

struct HSD_JObj {
    unsigned char pad00[0x14];
    unsigned int flags; /* 0x14 */
    unsigned char pad18[0x2C];
    float mtx[3][4]; /* 0x44 */
};

extern "C" {
void __assert(char *file, int line, char *cond);
void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
void HSD_JObjCheckDependAll(HSD_JObj *jobj);
void HSD_JObjDispAll(HSD_JObj *jobj, void *mtx, int mode, int rendermode);
void PSMTXCopy(float (*src)[4], float (*dst)[4]);
}

struct ObjectView {
    unsigned char pad00[3];
    unsigned char noDepend; /* 0x03 */
    unsigned char pad04[0x14];
    float (*mtxA)[4]; /* 0x18 */
    float (*mtxB)[4]; /* 0x1C */
    unsigned char pad20[0xC];
    HSD_JObj *root; /* 0x2C */
    unsigned char pad30[0xC];
    HSD_JObj *bound; /* 0x3C */
};

class ScopedTimer {
public:
    ScopedTimer(int slot) { m_slot = slot; m_startTick = OSGetTick(); }
    ~ScopedTimer() {
        Profiler_RecordFrame(m_slot, (float)(((OSGetTick() - m_startTick) << 3) / ((*(volatile unsigned int *)0x800000F8 >> 2) / 125000)) / lbl_806D2360);
    }
private:
    unsigned int m_startTick;
    int m_slot;
};

static inline unsigned char jobj_mtx_is_dirty(HSD_JObj *jobj)
{
    unsigned char result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void jobj_set_mtx_dirty(HSD_JObj *jobj)
{
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x25D, lbl_806D2350);
        }
        if (!jobj_mtx_is_dirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void jobj_clear_flags(HSD_JObj *jobj, unsigned int flags)
{
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x4AF, lbl_806D2350);
    }
    jobj->flags &= ~flags;
}

static inline void jobj_copy_mtx(HSD_JObj *jobj, float (*mtx)[4])
{
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x495, lbl_806D2350);
    }
    if (mtx == 0) {
        __assert(lbl_806D2348, 0x496, lbl_806D2378);
    }
    PSMTXCopy(mtx, jobj->mtx);
    jobj->flags |= 0x03800000;
    jobj_set_mtx_dirty(jobj);
}

extern "C" int Object_ClearAnimBinding(ObjectView *self)
{
    HSD_JObj *jobj;

    if (self->root == 0) {
        return 0;
    }
    self->mtxA = 0;
    self->mtxB = 0;
    jobj = self->bound;
    if (jobj != 0) {
        jobj_clear_flags(jobj, 0x03800000);
        jobj_set_mtx_dirty(jobj);
    }
    self->bound = 0;
    return 1;
}

extern "C" int Object_SetAnimBinding(ObjectView *self, float (*mtx)[4], HSD_JObj *jobj)
{
    if (self->root == 0) {
        return 0;
    }
    if (self->bound != 0) {
        Object_ClearAnimBinding(self);
    }
    self->mtxA = 0;
    self->mtxB = mtx;
    self->bound = jobj == 0 ? self->root : jobj;
    return 1;
}

extern "C" int Object_BindMatrixSource(ObjectView *self, float (*mtx)[4], HSD_JObj *jobj)
{
    if (self->root == 0) {
        return 0;
    }
    if (self->bound != 0) {
        Object_ClearAnimBinding(self);
    }
    self->mtxA = mtx;
    self->mtxB = 0;
    self->bound = jobj == 0 ? self->root : jobj;
    return 1;
}

extern "C" int Object_RenderJObjEx(ObjectView *self, HSD_JObj *jobj, int mode)
{
    if (jobj == 0) {
        return 0;
    }
    HSD_JObjDispAll(jobj, 0, mode, 0);
    return 1;
}

extern "C" int Object_RenderJObjTree(ObjectView *self, int mode)
{
    if (self->root == 0) {
        return 0;
    }
    HSD_JObjDispAll(self->root, 0, mode, 0);
    return 1;
}

extern "C" int Object_DriveAnimMatrix(ObjectView *self)
{
    ScopedTimer timer(10);

    if (self->root == 0) {
        return 0;
    }
    if (self->mtxA != 0) {
        jobj_copy_mtx(self->bound, self->mtxA);
    } else if (self->mtxB != 0) {
        jobj_copy_mtx(self->bound, self->mtxB);
    } else if (!self->noDepend) {
        HSD_JObjCheckDependAll(self->root);
    }
    return 1;
}
