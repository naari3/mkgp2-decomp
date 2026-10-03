/* Complete bounded draft (approach 2: 99.27327% text).
 * Disabled: original object remains authoritative; no genuine match claimed.
 * Only the offsets observed in this unit are modeled. */
#if 0
#pragma cplusplus on
struct JObj;
typedef void (*AnimCallback)(void);
struct JObjClass { unsigned char pad[0x50]; AnimCallback animate; };
struct JObj {
    JObjClass *klass;
    unsigned char pad04[0x10];
    unsigned int flags;
    void *dobj;
    unsigned char pad1C[0x60];
    void *aobj;
};
struct AnimRow { void *descriptor; void **joint; void **material; void **shape; };
struct Normal3D {
    unsigned char pad00[2]; unsigned char changed; unsigned char animated;
    unsigned char pad04[4];
    float frame, y, z, x;
    unsigned char pad18[0x14];
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
void fn_802CE078(JObj *, void *, void *, void *);
void HSD_JObjReqAnimByFlags(JObj *, unsigned int, float);
void fn_802C3B54(void);
void fn_802C3B64(void);
void fn_802C3C00(void *, JObj *, AnimCallback);
void fn_802BD0FC(void *);
void fn_802CD2B0(JObj *);
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
    volatile int slot;
};
static inline void *First(void **list) { if (list == 0) return 0; return list[0]; }
static inline void Attach(Normal3D *self, AnimRow *row) {
    void *joint = First(row->joint);
    void *material = First(row->material);
    void *shape = First(row->shape);
    fn_802CE078(self->root, joint, material, shape);
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
static inline unsigned char HasDObj(JObj *node) { return !(node->flags & 0x4020); }
static inline void Animate(JObj **table, int count) {
    if (table != 0) {
        JObj **cursor = table;
        for (int i = 0; i < count; ++i, ++cursor) {
            JObj *node = *cursor;
            if (node != 0) {
                fn_802C3C00(node->aobj, node, node->klass->animate);
                if (HasDObj(node) == 1) fn_802BD0FC(node->dobj);
            }
        }
        fn_802CD2B0(*table);
    }
}
extern "C" int clNormal3D_SetScale(Normal3D *self, Normal3D *source,
    float frame, float x, float y, float z)
{
    if (self->root == 0) return 0;
    self->changed = 1;
    self->x = x;
    self->y = y;
    self->z = z;
    unsigned char updated = 0;
    if (source == 0) {
        if (frame >= lbl_806D2340) self->frame = frame;
        if (First(self->row->joint) || First(self->row->material) || First(self->row->shape)) {
            {
                ScopedTimer timer(8);
                Attach(self, self->row);
            }
            {
                ScopedTimer timer(11);
                Request(self, self);
            }
            self->animated = 1;
            updated = 1;
        }
    } else {
        if (frame >= lbl_806D2340) source->frame = frame;
        if (First(source->row->joint) || First(source->row->material) || First(source->row->shape)) {
            {
                ScopedTimer timer(8);
                Attach(self, source->row);
            }
            {
                ScopedTimer timer(11);
                Request(self, source);
            }
            self->animated = 1;
            updated = 1;
        }
    }
    if (updated == 1) {
        ScopedTimer timer(7);
        JObj **table = self->table;
        int count = self->count;
        if (table != 0) {
            fn_802C3B54();
            Animate(table, count);
            fn_802C3B64();
        }
    }
    return 1;
}
#pragma cplusplus off
#endif
