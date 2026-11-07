#include "mobj.h"

/* Shared material globals and data remain in the original fallback pool. */
HSD_TObj* tobj_toon;
HSD_TObj* tobj_shadows;
HSD_MObj* mobj_override;
int mobj_override_enable;
void (*tev_stage_callback)(int);
