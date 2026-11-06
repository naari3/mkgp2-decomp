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
void MObjInfoInit(void)
{
    /* The original material data block also contains the class-name strings. */
    char* base = (char*) &hsdMObj;

    hsdInitClassInfo(HSD_CLASS_INFO(base), HSD_CLASS_INFO(&hsdClass),
                     base + 0x148, base + 0x160,
                     sizeof(HSD_MObjInfo), sizeof(HSD_MObj));

    HSD_CLASS_INFO(base)->release = MObjRelease;
    HSD_CLASS_INFO(base)->amnesia = MObjAmnesia;
    HSD_MOBJ_INFO(base)->setup = HSD_MObjSetup;
    HSD_MOBJ_INFO(base)->unset = HSD_MObjUnset;
    HSD_MOBJ_INFO(base)->load = MObjLoad;
    HSD_MOBJ_INFO(base)->make_texp = MObjMakeTExp;
    HSD_MOBJ_INFO(base)->setup_tev = MObjSetupTev;
    HSD_MOBJ_INFO(base)->update = MObjUpdateFunc;
}
