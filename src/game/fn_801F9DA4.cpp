#include "game/mapobject/mapobject.h"
#include "game/types/ObjEntry.h"
extern "C" {
struct CourseRodata { char pad0[0x708]; char extra[0x10]; char joint[0x1C]; char ready[4]; };
extern const CourseRodata lbl_803BF440;
extern ObjEntry *lbl_804EBD50[3];
extern ObjEntry *lbl_804EBD5C[3];
extern const float lbl_806DA7D8;
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
const void *fn_8023D8F8(int);
void Object_SetColorAlphaOnly(clNormal3D *, int, float);
void JObj_Hide(clNormal3D *, HSD_JObj *, int);
}
struct CourseObjSet {
    clNormal3D *objs[3][30];
    clNormal3D *extra[3];
    CourseObjSet(const CourseRodata *pool) {
        for (int i = 0; i < 3; i++) {
            clNormal3D **o;
            ObjEntry *e;
            if (ServiceEnable_Get() && !ServiceValue_Get()) e = lbl_804EBD50[i];
            else e = lbl_804EBD5C[i];
            o = objs[i];
            for (; e->id != -1; e++, o++) {
                const void *desc = fn_8023D8F8(e->id);
                if (desc) *o = new clNormal3D(desc, 1);
                else *o = 0;
                if (*o) Object_SetColorAlphaOnly(*o, 0, lbl_806DA7D8);
            }
            extra[i] = new clNormal3D(pool->extra, 1);
            JObj_Hide(extra[i], ResolveJointByName(extra[i], pool->joint), 0x10);
        }
        DebugPrintf(pool->ready);
    }
};
extern "C" CourseObjSet *lbl_806D19B0;
extern "C" CourseObjSet *fn_801F9DA4() {
    const CourseRodata *pool = &lbl_803BF440;
    if (!lbl_806D19B0) lbl_806D19B0 = new CourseObjSet(pool);
    return lbl_806D19B0;
}
