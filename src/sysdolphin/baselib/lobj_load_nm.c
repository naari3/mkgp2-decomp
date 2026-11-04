#include "lobj_private.h"

#undef __FILE__
#define __FILE__ "lobj.c"
extern int LObjLoad(HSD_LObj*, HSD_LightDesc*);
extern void LObjRelease(HSD_Class*);
extern void LObjAmnesia(HSD_ClassInfo*);
void LObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdLObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_lobj",
                     sizeof(HSD_LObjInfo), sizeof(HSD_LObj));
    HSD_CLASS_INFO(&hsdLObj)->release = LObjRelease;
    HSD_CLASS_INFO(&hsdLObj)->amnesia = LObjAmnesia;
    HSD_LOBJ_INFO(&hsdLObj)->load = LObjLoad;
    HSD_LOBJ_INFO(&hsdLObj)->update = LObjUpdateFunc;
}
