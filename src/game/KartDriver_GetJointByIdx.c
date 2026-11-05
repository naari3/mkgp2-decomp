/* KartDriver_GetJointByIdx @ 0x80040E9C: evaluate and return a joint matrix. */
#include "sysdolphin/baselib/jobj.h"
#include "game/KartDriverJointPrivate.h"

extern char lbl_806D2548[7];
extern char lbl_806D2550[5];
extern void __assert(char *file, int line, char *expr);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);

static inline unsigned char HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;

    if (jobj == 0) {
        __assert(lbl_806D2548, 0x25D, lbl_806D2550);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetupMatrix(HSD_JObj *jobj)
{
    if (jobj == 0) {
        return;
    }
    if (HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline float (*HSD_JObjGetMtxPtr(HSD_JObj *jobj))[4]
{
    if (jobj == 0) {
        __assert(lbl_806D2548, 0x47C, lbl_806D2550);
    }
    HSD_JObjSetupMatrix(jobj);
    return (float (*)[4])((char *)jobj + 0x44);
}

static inline float (*JointMatrix(HSD_JObj *jobj))[4]
{
    return jobj == 0 ? 0 : HSD_JObjGetMtxPtr(jobj);
}

#pragma exceptions on
float (*KartDriver_GetJointByIdx(KartDriverJoints *driver, int idx))[4]
{
    if (idx == 0) {
        return JointMatrix(driver->joints[0]);
    }
    if (idx == 1) {
        return JointMatrix(driver->joints[1]);
    }
    if (idx == 2) {
        return JointMatrix(driver->joints[2]);
    }
    if (idx == 3) {
        return JointMatrix(driver->joints[3]);
    }
    if (idx == 4) {
        return JointMatrix(driver->joints[4]);
    }
    if (idx == 5) {
        return JointMatrix(driver->joints[5]);
    }
    if (idx == 6) {
        return JointMatrix(driver->joints[6]);
    }
    if (idx == 7) {
        return JointMatrix(driver->joints[7]);
    }
    if (idx == 8) {
        return JointMatrix(driver->joints[9]);
    }
    if (idx == 9) {
        return JointMatrix(driver->joints[10]);
    }
    if (idx == 12) {
        return JointMatrix(driver->joints[13]);
    }
    if (idx == 13) {
        return JointMatrix(driver->joints[14]);
    }
    if (idx == 14) {
        return JointMatrix(driver->joints[15]);
    }
    if (idx == 15) {
        return JointMatrix(driver->joints[16]);
    }
    if (idx == 16 && driver->joints[17] != 0) {
        return JointMatrix(driver->joints[17]);
    }
    if (idx == 10) {
        return JointMatrix(driver->joints[11]);
    }
    if (idx == 11) {
        return JointMatrix(driver->joints[12]);
    }
    return 0;
}
#pragma exceptions reset
