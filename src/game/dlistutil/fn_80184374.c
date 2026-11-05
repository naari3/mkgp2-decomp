#include "game/DListBoundsPrivate.h"
int fn_80184374(HSD_JObj *j, HSD_DObj *d, BoundsVec *lo, BoundsVec *hi) {
    const char *messages=lbl_80376F60;
    BoundsVec v;
    HSD_PObj *pobj;
    unsigned char *p, *end;
    unsigned int size, n, i;
    if (!d || !lo || !hi) return 0;
    v=*(const BoundsVec *)messages;
    pobj=d ? d->pobj : 0;
    if (!pobj) return 0;
    for (; pobj; pobj=pobj->next) {
        p=pobj->display;
        end=p+pobj->n_display*32;
        fn_801866DC(pobj->verts);
        if (!lbl_806D1678) return 0;
        while (p<end) {
            size=CmdSize(p,messages);
            if (size) { p+=size; continue; }
            n=*(unsigned short *)(p+1);
            p+=3;
            for (i=0;i<n;++i) {
                if (ReadPosition(p,&v)) {
                    if (j) Transform(j,&v);
                    Extend(lo,hi,&v);
                }
                p+=lbl_806D1678;
            }
        }
    }
    return 1;
}
