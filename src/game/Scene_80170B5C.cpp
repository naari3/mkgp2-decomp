/* Native reconstruction of fn_80170B5C; retained as NonMatching. */
#include "game/Scene_80170B5C_private.h"

extern "C" {
extern char lbl_8036E220[];
extern int g_longRoundFlag, g_reverseRoundFlag;
extern char lbl_806D8CD8[7], lbl_806D8CE0[5];
void DebugPrintf(const char *, ...);
int HSD_GetNbBits(unsigned int);
void *FUN_8003b120(unsigned long);
int sprintf(char *, const char *, ...);
GrowJoint *ResolveJointByName(clNormal3D *, const char *);
GrowDObj *HSD_JObjGetDObj(GrowJoint *);
int fn_80184F24(GrowJoint *, void *, GrowFace *, int);
int fn_80183A5C(void *);
int fn_80185630(GrowJoint *, void *, void *, int);
void __assert(char *, int, char *);
}

static inline void *GetPObj(GrowDObj *d) {
    if (d) return d->pobj;
    return 0;
}
static inline void *GetJointPObj(GrowJoint *j) {
    return GetPObj(HSD_JObjGetDObj(j));
}
static inline Vec3Grow *GetPosition(GrowJoint *j) {
    if (!j) __assert(lbl_806D8CD8,0x3E4,lbl_806D8CE0);
    return &j->pos;
}
GrowSet::GrowSet() {
    char *names = lbl_8036E220;
    int bit;
    unsigned int mask;
    int used;
    DebugPrintf(names+0x474);
    model=0; entries=0; count=0;
    model=new clNormal3D(names+0x494,0);
    if (!model) return;
    if (g_longRoundFlag==0) {
        if (g_reverseRoundFlag==0) mask=0x16;
        else mask=0x114;
    } else {
        if (g_reverseRoundFlag==0) mask=0xEA;
        else mask=0x1E8;
    }
    count=HSD_GetNbBits(mask);
    if (count==0) return;
    used=0;
    entries=(GrowEntry *)FUN_8003b120(count*sizeof(GrowEntry));
    for (int i=0;i<count;i++) {
        entries[i].jobj=0;
        entries[i].faces=0;
        entries[i].faceCount=0;
        entries[i].anim=0;
        entries[i].state=0;
        entries[i].t=0.0f;
        entries[i].scale=0.0f;
        entries[i].sub=0;
    }
    for (bit=0;bit<32;bit++) {
        if (mask & (1<<bit)) {
            GrowEntry *e=&entries[used];
            char name[32];
            sprintf(name,names+0x4A4,bit);
            GrowJoint *a=ResolveJointByName(model,name);
            sprintf(name,names+0x4C8,bit);
            GrowJoint *b=ResolveJointByName(model,name);
            sprintf(name,names+0x4E8,bit);
            e->jobj=ResolveJointByName(model,name);
            if (!e->jobj || !a || !b) continue;
            GrowFace face;
            if (fn_80184F24(b,GetJointPObj(b),&face,1)) {
                e->anim=new GrowAnim(&face,1);
            }
            void *pobj=GetJointPObj(a);
            e->faceCount=fn_80183A5C(pobj);
            if (e->faceCount) {
                e->faces=FUN_8003b120(e->faceCount*0x34);
                int n=fn_80185630(a,pobj,e->faces,e->faceCount);
                if (n<e->faceCount) e->faceCount=n;
            }
            Vec3Grow pos=*GetPosition(e->jobj);
            e->sub=new GrowSub;
            e->sub->pos=pos;
            e->sub->scale=1.0f;
            if (++used>=count) break;
        }
    }
}
