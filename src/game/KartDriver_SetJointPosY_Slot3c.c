/* Set the Y translation of the kart joint at 0xf0 (slot 3c). */
typedef struct HSD_JObj {
    unsigned char pad00[0x14];
    unsigned int flags; /* 0x14 */
    unsigned char pad18[0x24];
    float translateY;   /* 0x3C */
} HSD_JObj;

typedef struct KartDriver {
    void *model;  /* 0x00 */
    unsigned char pad04[0x8];
    void *loaded; /* 0x0C */
    unsigned char pad10[0xf0 - 0x10];
    HSD_JObj *joint; /* 0xf0 */
} KartDriver;

extern char lbl_806D2548[7]; /* "jobj.h" */
extern char lbl_806D2550[5]; /* "jobj" */
extern void __assert(const char *file, int line, const char *cond);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);

static inline int HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;
    if (!jobj) {
        __assert(lbl_806D2548, 0x25d, lbl_806D2550);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, float y)
{
    if (!jobj) {
        __assert(lbl_806D2548, 0x3c6, lbl_806D2550);
    }
    jobj->translateY = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

int KartDriver_SetJointPosY_Slot3c(KartDriver *self, float y)
{
    HSD_JObj *jobj;

    if (self->model == 0 || self->loaded == 0) {
        return 0;
    }
    jobj = self->joint;
    if (jobj != 0) {
        HSD_JObjSetTranslateY(jobj, y);
    }
    return 1;
}
