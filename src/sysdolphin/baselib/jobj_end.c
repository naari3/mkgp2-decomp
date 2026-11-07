#include "mkgp2_names.h"
#include "jobj.h"

extern char lbl_804FC9A8[0x3D8];
extern HSD_JObj* lbl_806D21C4;

/* These inline helpers retain the shared assertion pool used by jobj.c. */
static inline void CurrentJObjRef(HSD_JObj* jobj, char* pool)
{
    if (jobj != NULL) {
        HSD_OBJ(jobj)->ref_count++;
        if (HSD_OBJ(jobj)->ref_count == HSD_OBJ_NOREF) {
            __assert(pool + 0x1E0, 93, pool + 0x1EC);
        }
    }
}

static inline void CurrentJObjUnref(HSD_JObj* jobj, char* pool)
{
    if (jobj != NULL && ref_DEC(jobj)) {
        if (iref_CNT(jobj) - 1 < 0) {
            hsdDelete(jobj);
        } else {
            HSD_OBJ(jobj)->ref_count_individual++;
            if (HSD_OBJ(jobj)->ref_count_individual == 0) {
                __assert(pool + 0x1E0, 158, pool + 0x214);
            }
            HSD_JOBJ_METHOD(jobj)->release_child(jobj);
            if (iref_DEC(jobj)) {
                hsdDelete(jobj);
            }
        }
    }
}

void HSD_JObjSetCurrent(HSD_JObj* jobj)
{
    char* pool = lbl_804FC9A8;
    CurrentJObjRef(jobj, pool);
    CurrentJObjUnref(lbl_806D21C4, pool);
    lbl_806D21C4 = jobj;
}

/* Shared assertion strings retained in the original small-data pool. */
char lbl_806D0DB0[7] = "jobj.c";
char lbl_806D0DB8[3] = "jp";
char lbl_806D0DBC[5] = "prev";
char lbl_806D0DC4[4] = "eff";
char lbl_806D0DC8[5] = "robj";
