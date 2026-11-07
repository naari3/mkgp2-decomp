#include "mkgp2_names.h"
#include "jobj_rescue_private.h"

void (HSD_JObjSetMtxDirty)(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return;
    }
    switch (HSD_JObjMtxIsDirty(jobj)) {
    case 0:
        HSD_JObjSetMtxDirtySub(jobj);
        break;
    }
}
