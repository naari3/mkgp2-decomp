#include "game/types/Quat.h"

#include "game/types/HSD_JObj.h"

#include "game/types/ObjectJObjView.h"

extern const Quat JObj_SetRotationQuat_rodata_802E9780;
extern char lbl_806D2348[7];
extern char lbl_806D2350[5];
extern void __assert(char *, int, char *);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *);

static inline void update_matrix(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char skip;

    flags = jobj->flags;
    skip = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        skip = 1;
    }
    if (!skip) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

void JObj_SetRotationQuat(ObjectJObjView *object, float x, float y, float z) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        Quat quat = JObj_SetRotationQuat_rodata_802E9780;

        quat.x = x;
        quat.y = y;
        quat.z = z;
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x290, lbl_806D2350);
        }
        jobj->rotate.x = quat.x;
        jobj->rotate.y = quat.y;
        jobj->rotate.z = quat.z;
        jobj->rotate.w = quat.w;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}
