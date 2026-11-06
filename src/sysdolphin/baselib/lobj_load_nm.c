#include "lobj_private.h"

#undef __FILE__
#define __FILE__ "lobj.c"
extern int LObjLoad(HSD_LObj*, HSD_LightDesc*);
extern void LObjRelease(HSD_Class*);
extern void LObjAmnesia(HSD_ClassInfo*);
/* Shared strings used by the light position, load and class routines. */
char lbl_804FC43C[0x44] =
    "lobj->position\0\0"
    "lobj->interest\0\0"
    "hsdIsDescendantOf(info, &hsdLObj)";
char lbl_804FC480[0x48] =
    "unexpected lightdesc flags (%x)\n\0\0\0\0"
    "sysdolphin_base_library\0"
    "hsd_lobj";

void LObjInfoInit(void)
{
    char* base = (char*) &hsdLObj;

    hsdInitClassInfo(HSD_CLASS_INFO(base), HSD_CLASS_INFO(&hsdObj),
                     base + 0x13C, base + 0x154,
                     sizeof(HSD_LObjInfo), sizeof(HSD_LObj));
    HSD_CLASS_INFO(base)->release = LObjRelease;
    HSD_CLASS_INFO(base)->amnesia = LObjAmnesia;
    HSD_LOBJ_INFO(base)->load = LObjLoad;
    HSD_LOBJ_INFO(base)->update = LObjUpdateFunc;
}
