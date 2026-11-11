#include "game/types/gx_data.h"
#include "game/DListBoundsPrivate.h"
static inline unsigned char ReadBoundsPosition(unsigned char *p, BoundsVec *out) {
    int i;
    for (i=0;i<22;++i) {
        if (!lbl_80677E18[i].desc || lbl_80677E18[i].desc->attr==255) break;
        if (lbl_80677E18[i].desc->attr==9) {
            VtxAttrEntry *entry=&lbl_80677E18[i];
            VtxDesc *d=entry->desc;
            unsigned int index;
            float *v;
            if (d->type==3) index=GXDATA_U16(p+entry->offset);
            else index=p[entry->offset];
            v=d->array;
            v+=index*(d->stride/4);
            out->x=GXDATA_F32(v);out->y=GXDATA_F32(v + 1);out->z=GXDATA_F32(v + 2);
            return 1;
        }
    }
    return 0;
}
int fn_80184374(HSD_JObj *j, HSD_DObj *d, BoundsVec *lo, BoundsVec *hi) {
    const char *messages=lbl_80376F60;
    BoundsVec v;
    HSD_PObj *pobj;
    unsigned int n;
    unsigned char *p, *end;
    unsigned int size, i;
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
            n=GXDATA_U16(p+1);
            p+=3;
            for (i=0;i<n;++i) {
                if (ReadBoundsPosition(p,&v)) {
                    if (j) {
                        SetupMatrix(j);
                        PSMTXMultVec(&j->_pad_1c[0x28],&v,&v);
                    }
                    Extend(lo,hi,&v);
                }
                p+=lbl_806D1678;
            }
        }
    }
    return 1;
}
