#ifndef MKGP2_TOBJ_PRIVATE_H
#define MKGP2_TOBJ_PRIVATE_H
#include "tobj.h"
extern HSD_TObjInfo* tobj_default_class;
extern HSD_TObj* tobj_head;
void TObjInfoInit(void);
void TObjUpdateFunc(void*, enum_t, HSD_ObjData*);
int TObjLoad(HSD_TObj*, HSD_TObjDesc*);
void MakeTextureMtx(HSD_TObj*);
void TObjMakeTExp(HSD_TObj*, u32, u32, HSD_TExp**, HSD_TExp**, HSD_TExp**);
#define default_class tobj_default_class
void HSD_RequestInvalidate(int);
#define fn_802D47F4 HSD_RequestInvalidate
int TObjInit(HSD_Class*);
void TObjRelease(HSD_Class*);
void TObjAmnesia(HSD_ClassInfo*);
void MakeColorGenTExp(u32, HSD_TObj*, HSD_TExp**, HSD_TExp**, HSD_TExp**, int);
#endif
