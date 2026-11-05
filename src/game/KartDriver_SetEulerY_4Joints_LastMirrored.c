/* Set the Y rotation of the four wheel/steering joints (0xe8, 0xec, 0x164,
 * 0x16c); the last one is mirrored (negated angle). */
typedef struct HSD_JObj {
    unsigned char pad00[0x14];
    unsigned int flags; /* 0x14 */
    unsigned char pad18[0x20 - 0x18];
    float rotY;         /* 0x20 */
} HSD_JObj;

typedef struct KartDriver {
    void *model;  /* 0x000 */
    unsigned char pad004[0x8];
    void *loaded; /* 0x00C */
    unsigned char pad010[0xe8 - 0x10];
    HSD_JObj *joint0E8; /* 0x0E8 */
    HSD_JObj *joint0EC; /* 0x0EC */
    unsigned char pad0f0[0x164 - 0xf0];
    HSD_JObj *joint164; /* 0x164 */
    unsigned char pad168[0x16c - 0x168];
    HSD_JObj *joint16C; /* 0x16C */
} KartDriver;

extern char lbl_806D2548[7]; /* "jobj.h" */
extern char lbl_806D2550[5]; /* "jobj" */
extern char lbl_802EADBC[];  /* "!(jobj->flags & JOBJ_USE_QUATERNION)" */
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

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, float y)
{
    if (!jobj) {
        __assert(lbl_806D2548, 0x2b8, lbl_806D2550);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D2548, 0x2b9, lbl_802EADBC);
    }
    jobj->rotY = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

#pragma exceptions on
int KartDriver_SetEulerY_4Joints_LastMirrored(KartDriver *self, float y)
{
    if (self->model == 0 || self->loaded == 0) {
        return 0;
    }
    if (self->joint0E8 != 0) {
        HSD_JObjSetRotationY(self->joint0E8, y);
    }
    if (self->joint0EC != 0) {
        HSD_JObjSetRotationY(self->joint0EC, y);
    }
    if (self->joint164 != 0) {
        HSD_JObjSetRotationY(self->joint164, y);
    }
    if (self->joint16C != 0) {
        HSD_JObjSetRotationY(self->joint16C, -y);
    }
    return 1;
}
#pragma exceptions reset
