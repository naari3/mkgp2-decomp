#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

#include "mobj_private.h"
void HSD_MObjAnim(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return;
    }
    HSD_AObjInterpretAnim(mobj->aobj, mobj, HSD_MOBJ_METHOD(mobj)->update);
    HSD_TObjAnimAll(mobj->tobj);
}
