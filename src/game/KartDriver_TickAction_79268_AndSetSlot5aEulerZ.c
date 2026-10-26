/* Forward the pitch to the tire FX, then roll joint 0x168 to its base
 * angle plus the same amount. */
typedef struct HSD_JObj {
    unsigned char pad00[0x14];
    unsigned int flags; /* 0x14 */
    unsigned char pad18[0xc];
    float rotZ;         /* 0x24 */
} HSD_JObj;

typedef struct KartDriver {
    void *model;  /* 0x000 */
    unsigned char pad004[0x8];
    void *loaded; /* 0x00C */
    unsigned char pad010[0x158];
    HSD_JObj *joint; /* 0x168 */
    unsigned char pad16c[0x4];
    float baseRotZ;  /* 0x170 */
    unsigned char pad174[0x198];
    void *tireFX;    /* 0x30C */
} KartDriver;

extern char lbl_806D2548[7]; /* "jobj.h" */
extern char lbl_806D2550[5]; /* "jobj" */
extern char lbl_802EADBC[];  /* "!(jobj->flags & JOBJ_USE_QUATERNION)" */
extern void __assert(const char *file, int line, const char *cond);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
extern void KartTireFX_SetPitch(void *fx, float pitch);

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

static inline void HSD_JObjSetRotationZ(HSD_JObj *jobj, float z)
{
    if (!jobj) {
        __assert(lbl_806D2548, 0x2cc, lbl_806D2550);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D2548, 0x2cd, lbl_802EADBC);
    }
    jobj->rotZ = z;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

int KartDriver_TickAction_79268_AndSetSlot5aEulerZ(KartDriver *self, float pitch)
{
    HSD_JObj *jobj;

    if (self->model == 0 || self->loaded == 0) {
        return 0;
    }
    if (self->tireFX != 0) {
        KartTireFX_SetPitch(self->tireFX, pitch);
    }
    jobj = self->joint;
    if (jobj != 0) {
        HSD_JObjSetRotationZ(jobj, self->baseRotZ + pitch);
    }
    return 1;
}
