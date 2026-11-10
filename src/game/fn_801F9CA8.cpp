/* --- owned .rodata 0x803BFB30..0x803BFB90 (tools/own_data.py) --- */
#pragma force_active on
extern "C" const char lbl_803BFB30[96] = { 68, 101, 115, 116, 114, 111, 121, 32, 105, 116, 101, 109, 32, 109, 111, 100, 101, 108, 46, 46, 46, 10, 0, 0, 46, 47, 105, 116, 101, 109, 95, 98, 111, 120, 46, 100, 97, 116, 0, 0, 105, 116, 101, 109, 95, 98, 111, 120, 95, 104, 97, 104, 101, 110, 95, 110, 117, 108, 108, 49, 95, 106, 111, 105, 110, 116, 0, 0, 67, 114, 101, 97, 116, 101, 32, 105, 116, 101, 109, 32, 109, 111, 100, 101, 108, 46, 46, 46, 10, 0, 0, 0, 0, 0, 0, 0 };
#pragma force_active reset
extern "C" /* Course object set owned by lbl_806D19B0; deleted through its inline dtor. */
struct HSD_Obj;
#include "game/types/ObjEntry.h"
extern "C" {
extern ObjEntry *lbl_804EBD50[3];
extern ObjEntry *lbl_804EBD5C[3];
void Object_DtorWithGXSync(HSD_Obj *obj, int del);
unsigned char ServiceEnable_Get(void);
unsigned char ServiceValue_Get(void);
void DebugPrintf(const char *fmt, ...);
}

struct CourseObjSet {
    HSD_Obj *objs[3][30];
    HSD_Obj *extra[3];
    ~CourseObjSet();
};

inline CourseObjSet::~CourseObjSet()
{
    ObjEntry *e;
    HSD_Obj **o;
    int i;
    for (i = 0; i < 3; i++) {
        Object_DtorWithGXSync(extra[i], 1);
        extra[i] = 0;
        if (ServiceEnable_Get() && !ServiceValue_Get()) {
            e = lbl_804EBD50[i];
        } else {
            e = lbl_804EBD5C[i];
        }
        for (o = objs[i]; e->id != -1; o++, e++) {
            if (*o != 0) {
                Object_DtorWithGXSync(*o, 1);
                *o = 0;
            }
        }
    }
    DebugPrintf(lbl_803BFB30);
}

extern "C" {
extern CourseObjSet *lbl_806D19B0;
}

void operator delete(void *p);

extern "C" void fn_801F9CA8(void)
{
    if (lbl_806D19B0 != 0) {
        delete lbl_806D19B0;
        lbl_806D19B0 = 0;
    }
}
