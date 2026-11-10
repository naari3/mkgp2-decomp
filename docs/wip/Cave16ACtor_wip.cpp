#include "../src/game/mapeffect/mapfx16a_private.h"
static inline DObj16A *NextDObj(DObj16A *d) { return d ? d->next : 0; }
Cave16A::Cave16A() {
    const char *pool = Cave16ACtor_rodata_8036CF68;
    DebugPrintf(pool + 0x5a4);
    model = new Obj16A;
    model->flag = 1;
    zone = new Zone16A(pool + 0x3fc, 6);
    hit = 1;
    archive = 0;
    alpha = lbl_806D8A70;
    if (g_longRoundFlag == 1) {
        archive = new clNormal3D(pool + 0x5c4, 1);
        for (DObj16A *d = HSD_JObjGetDObj(Archive_GetRootJObj(archive)); d; d = NextDObj(d)) {
            void *m = d ? d->material : 0;
            if (m) {
                TObj16A *t = HSD_MObjGetTObj(m);
                if (t) { t->s = 2; t->t = 1; }
            }
        }
    }
}
