#include "game/objview/morph18f_private.h"
extern int lbl_806D9488,lbl_806D948C;
extern MorphHandle *lbl_806DCF58,*lbl_806DCF5C;
MorphNode *fn_8018F8A8(MorphNode *n,void *a,void *b) {
    MorphNode *cur;
    MorphHandle **h;
    int *sz;
    int i,j,attr,bytes;
    n->next=0;
    MorphClear(n);
    {
        int sizes[2];
        MorphHandle *handles[2];
        sizes[0]=lbl_806D9488; sizes[1]=lbl_806D948C;
        handles[0]=lbl_806DCF58; handles[1]=lbl_806DCF5C;
        n->obj[0]=HSD_JObjGetDObj(a);
        n->obj[1]=HSD_JObjGetDObj(b);
        handles[0]=n->obj[0] ? n->obj[0]->handle : 0;
        handles[1]=n->obj[1] ? n->obj[1]->handle : 0;
        if (!handles[0] || !handles[1]) goto fail;
        n->count=fn_8018387C(handles[0]);
        if (n->count<=0) goto fail;
        if (n->count!=fn_8018387C(handles[1])) goto fail;
        h=handles; sz=sizes; cur=n;
        for (i=0;i<2;i++,h++,cur=(MorphNode *)((char *)cur+4),sz++) {
            cur->original[0]=(*h)->attrs;
            for (j=0;(attr=cur->original[0][j].attr)!=255;j++) {
                MorphAttr *d=&cur->original[0][j];
                if (attr==9) {
                    if (d->type!=1) goto fail;
                    if (d->format!=4) goto fail;
                    *sz=j;
                    cur->input[0]=cur->original[0][j].data;
                }
            }
            if (j<=0 || *sz<0) goto fail;
            bytes=(j+1)*24;
            cur->copy[0]=HSD_MemAlloc(bytes);
            if (!cur->copy[0]) goto fail;
            memcpy(cur->copy[0],cur->original[0],bytes);
            cur->indices[0]=HSD_MemAlloc(n->count*2);
            if (!cur->indices[0]) goto fail;
            if (!fn_80183538(*h,9,cur->indices[0],n->count)) goto fail;
            cur->output[0]=HSD_MemAlloc(n->count*12);
            if (!cur->output[0]) goto fail;
            if (!fn_80183538(*h,9,cur->indices[0],n->count)) goto fail;
        }
        if (!fn_80182ED0(handles[0],9)) goto fail;
        if (!fn_80182ED0(handles[1],9)) goto fail;
        handles[0]->attrs=n->copy[0];
        n->copy[0][sizes[0]].data=n->output[0];
        handles[1]->attrs=n->copy[1];
        n->copy[1][sizes[1]].data=n->output[1];
        return n;
    fail:
        for (i=0;i<2;i++) {
            if (n->copy[i]) HSD_Free(n->copy[i]);
            if (n->indices[i]) HSD_Free(n->indices[i]);
            if (n->output[i]) HSD_Free(n->output[i]);
        }
        MorphClear(n);
        return n;
    }
}
