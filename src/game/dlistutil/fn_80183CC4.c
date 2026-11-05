#include "game/DListBoundsPrivate.h"
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
            n=*(unsigned short *)(p+1);
            p+=3;
            for (i=0;i<n;++i) {
                if (ReadPosition(p,&v)) Extend(&lo,&hi,&v);
                p+=lbl_806D1678;
            }
        }
    }
    center.x=lbl_806D9264*(hi.x+lo.x);
    center.y=lbl_806D9264*(hi.y+lo.y);
    center.z=lbl_806D9264*(hi.z+lo.z);
    if (j) {
        switch (j->flags & 0xe00) {
        case 0x200: center.x=center.y=center.z=lbl_806D927C; break;
        case 0x400: center.x=center.z=lbl_806D927C; break;
        case 0x600: center.y=center.z=lbl_806D927C; break;
        case 0x800: center.x=center.y=lbl_806D927C; break;
        }
        Transform(j,&center); Transform(j,&lo); Transform(j,&hi);
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
