#ifndef MKGP2_MOBJ_PRIVATE_H
#define MKGP2_MOBJ_PRIVATE_H
#include "mobj.h"
extern HSD_ClassInfo* default_class;
extern HSD_MObj* current_mobj;
extern HSD_MObj* mobj_override;
extern int mobj_override_enable;
extern void (*tev_stage_callback)(int);
void MObjUpdateFunc(void*, enum_t, HSD_ObjData*);
int MObjLoad(HSD_MObj*, HSD_MObjDesc*);
HSD_TExp* MObjMakeTExp(HSD_MObj*, HSD_TObj*, HSD_TExp**);
void MObjSetupTev(HSD_MObj*, HSD_TObj*, u32);
void MObjRelease(HSD_Class*);
void MObjAmnesia(HSD_ClassInfo*);
#endif
