/* Small Object wrappers around the HSD_JObj flag update helpers. */

extern void HSD_JObjClearFlagsAll(void *jobj, unsigned int flags);
extern void HSD_JObjSetFlagsAll(void *jobj, unsigned int flags);

#include "game/types/ObjectJObjView.h"

#pragma exceptions on
void Object_JObjUpdate_be4(ObjectJObjView *object, unsigned int flags) {
    if (object->jobj != 0) {
        HSD_JObjClearFlagsAll(object->jobj, flags);
    }
}

void Object_JObjUpdate_870(ObjectJObjView *object, unsigned int flags) {
    if (object->jobj != 0) {
        HSD_JObjSetFlagsAll(object->jobj, flags);
    }
}
#pragma exceptions reset
