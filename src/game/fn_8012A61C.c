/* fn_8012A61C: draws the preview kart, its driver model and the optional
 * attachment bound to a joint of the driver. */
typedef struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x44 - 0x18];
    float mtx[3][4];
} HSD_JObj;

typedef struct KartPreviewDraw {
    void *kart;
    void *tires;
    void *driver;
    char pad0C[0x124 - 0xC];
    void *attach;
    HSD_JObj *attachJoint;
} KartPreviewDraw;

extern char lbl_806D70C8[7];
extern char lbl_806D70D0[5];
extern void __assert(char *file, int line, char *expr);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
extern void Object_RenderJObjTree(void *obj, int mask);
extern void KartTireFX_ApplyAndRender(void *fx);
extern void Object_SetAnimBinding(void *obj, float (*mtx)[4], int flag);
extern void Object_DriveAnimMatrix(void *obj);

static inline void SetupJointMatrix(HSD_JObj *jobj)
{
    if (jobj == 0) {
        __assert(lbl_806D70C8, 0x47C, lbl_806D70D0);
    }
    if (jobj != 0) {
        unsigned int flags;
        unsigned char dirty;
        if (jobj == 0) {
            __assert(lbl_806D70C8, 0x25D, lbl_806D70D0);
        }
        flags = jobj->flags;
        dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (dirty) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

void fn_8012A61C(KartPreviewDraw *self)
{
    HSD_JObj *j;

    if (self->kart == 0 || self->driver == 0) {
        return;
    }
    Object_RenderJObjTree(self->kart, 7);
    KartTireFX_ApplyAndRender(self->tires);
    Object_RenderJObjTree(self->driver, 7);
    if (self->attach != 0 && (j = self->attachJoint) != 0) {
        SetupJointMatrix(j);
        Object_SetAnimBinding(self->attach, j->mtx, 0);
        Object_DriveAnimMatrix(self->attach);
        Object_RenderJObjTree(self->attach, 7);
    }
}
