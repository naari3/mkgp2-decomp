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
static inline void ExtendBounds(BoundsVec *lo, BoundsVec *hi, BoundsVec *v) {
    if (0.0f==lo->x && 0.0f==lo->y && 0.0f==lo->z &&
        0.0f==hi->x && 0.0f==hi->y && 0.0f==hi->z) {
        lo->x=v->x; lo->y=v->y; lo->z=v->z;
        hi->x=v->x; hi->y=v->y; hi->z=v->z;
    } else {
        if (v->x<lo->x) lo->x=v->x;
        if (v->y<lo->y) lo->y=v->y;
        if (v->z<lo->z) lo->z=v->z;
        if (v->x>hi->x) hi->x=v->x;
        if (v->y>hi->y) hi->y=v->y;
        if (v->z>hi->z) hi->z=v->z;
    }
}
int fn_80183CC4(HSD_JObj *j, HSD_DObj *d, BoundsVec *out, float *radius) {
    const char *messages=lbl_80376F60;
    BoundsVec v=*(const BoundsVec *)(messages+0x0c);
    BoundsVec lo=*(const BoundsVec *)(messages+0x18);
    BoundsVec hi=*(const BoundsVec *)(messages+0x24);
    BoundsVec center=*(const BoundsVec *)(messages+0x30);
    HSD_PObj *pobj;
    unsigned char *p, *end;
    unsigned int size,n,i;
    float sq, r;
    pobj=d ? d->pobj : 0;
    if (!pobj) return 0;
    for (;pobj;pobj=pobj->next) {
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
                if (ReadBoundsPosition(p,&v)) ExtendBounds(&lo,&hi,&v);
                p+=lbl_806D1678;
            }
        }
    }
    center.x=lbl_806D9264*(hi.x+lo.x);
    center.y=lbl_806D9264*(hi.y+lo.y);
    center.z=lbl_806D9264*(hi.z+lo.z);
    if (j) {
        if (j->flags & 0xe00) switch (j->flags & 0xe00) {
        case 0x200: center.x=lbl_806D927C; center.y=lbl_806D927C; center.z=lbl_806D927C; break;
        case 0x400: center.x=lbl_806D927C; center.z=lbl_806D927C; break;
        case 0x600: center.y=lbl_806D927C; center.z=lbl_806D927C; break;
        case 0x800: center.x=lbl_806D927C; center.y=lbl_806D927C; break;
        }
        SetupMatrix(j); PSMTXMultVec(&j->_pad_1c[0x28],&center,&center);
        SetupMatrix(j); PSMTXMultVec(&j->_pad_1c[0x28],&lo,&lo);
        SetupMatrix(j); PSMTXMultVec(&j->_pad_1c[0x28],&hi,&hi);
    }
    Vec3_Subtract(&lo,&center,&lo);
    Vec3_Subtract(&hi,&center,&hi);
    sq=PSVECSquareMag(&lo);
    if (PSVECSquareMag(&hi)>sq) r=Vec3_Magnitude(&hi);
    else r=Vec3_Magnitude(&lo);
    if (out) { out->x=center.x;out->y=center.y;out->z=center.z; }
    if (radius) *radius=r;
    return 1;
}
