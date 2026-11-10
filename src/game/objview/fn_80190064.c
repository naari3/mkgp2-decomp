typedef struct Attr { int attr; int unused; int type; int format; unsigned short unknown,stride; void *data; } Attr;
typedef struct Handle { char pad[8]; Attr *attrs; } Handle;
typedef struct DObj { char pad[0xc]; Handle *handle; } DObj;
#include "game/types/UV.h"
typedef struct Wave { float speedU,speedV,scaleU,scaleV,ampU,ampV,freqU,freqV; DObj *node; Handle *handle; Attr *copy,*original; int attrIndex,count; unsigned short *indices; UV *output,*input; float phaseU,phaseV; } Wave;
extern const float lbl_806D94E0,lbl_806D94E4,lbl_806D94E8,lbl_806D94EC,lbl_806D94DC;
extern DObj *HSD_JObjGetDObj(void *);
extern void *HSD_MemAlloc(unsigned int);
extern void HSD_Free(void *);
extern void *memcpy(void *,const void *,unsigned int);
extern int fn_8018387C(Handle *);
extern unsigned char fn_80183538(Handle *,int,void *,int);
extern unsigned char fn_80182ED0(Handle *,int);
static inline void Reset(Wave *w) {
    w->node=0; w->handle=0; w->copy=0; w->original=0; w->attrIndex=-1;
    w->count=0; w->indices=0; w->output=0; w->input=0;
    w->phaseU=lbl_806D94E0; w->phaseV=lbl_806D94E0;
    w->speedU=lbl_806D94E4; w->speedV=lbl_806D94E4;
    w->scaleU=lbl_806D94E8; w->scaleV=lbl_806D94E8;
    w->ampU=lbl_806D94EC; w->ampV=lbl_806D94EC;
    w->freqU=lbl_806D94DC; w->freqV=lbl_806D94DC;
}
Wave *fn_80190064(Wave *w,void *joint) {
    int i,bytes,attr;
    Reset(w);
    w->node=HSD_JObjGetDObj(joint);
    w->handle=w->node ? w->node->handle : 0;
    if (!w->handle) goto fail;
    w->original=w->handle->attrs;
    for (i=0;(attr=w->original[i].attr)!=255;i++) {
        Attr *a=&w->original[i];
        if (attr==13) {
            if (a->type!=1) goto fail;
            if (a->format!=4) goto fail;
            w->attrIndex=i;
            w->input=w->original[i].data;
        }
    }
    if (i<=0 || w->attrIndex<0) goto fail;
    bytes=(i+1)*24;
    w->copy=HSD_MemAlloc(bytes);
    if (!w->copy) goto fail;
    memcpy(w->copy,w->original,bytes);
    w->count=fn_8018387C(w->handle);
    if (w->count<=0) goto fail;
    w->indices=HSD_MemAlloc(w->count*2);
    if (!w->indices) goto fail;
    w->output=HSD_MemAlloc(w->count*w->original[w->attrIndex].stride);
    if (!w->output) goto fail;
    if (!fn_80183538(w->handle,13,w->indices,w->count)) goto fail;
    if (!fn_80182ED0(w->handle,13)) goto fail;
    w->handle->attrs=w->copy;
    w->copy[w->attrIndex].data=w->output;
    return w;
fail:
    if (w->copy) HSD_Free(w->copy);
    if (w->indices) HSD_Free(w->indices);
    if (w->output) HSD_Free(w->output);
    Reset(w);
    return w;
}
