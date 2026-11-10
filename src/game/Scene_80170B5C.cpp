/* Native reconstruction of the clKPTrap (GrowSet) constructor. */
#include "game/Scene_80170B5C_private.h"

extern "C" {
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
void __assert(const char *, int, const char *);
}

/* .rodata 0x8036E220..0x8036E728 is this file's (clKPTrap). The ctor
 * addresses its strings from the section start (`addi r31, ...rodata.0`), so
 * they are separate objects defined here. Names other files use stay global:
 * lbl_8036E654/lbl_8036E660 (class names in .sdata), lbl_8036E674 (the
 * DeleteMapEffect message in Scene_801709FC). */
#pragma force_active on
extern "C" {
extern const unsigned int Scene_80170B5C_rodata_8036E220[0xFF];
const unsigned int Scene_80170B5C_rodata_8036E220[0xFF] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
}
static const char sKPJointA[] = "_jkabe_A_joint";
static const char sKPAtariA[] = "_kabe_atari_A_joint";
static const char sKPHaniA[] = "_kabe_hani_A_joint";
extern "C" {
extern const char lbl_8036E654[9], lbl_8036E660[0x11], lbl_8036E674[0x1D];
const char lbl_8036E654[9] = "clKPTrap";
const char lbl_8036E660[0x11] = "clMapEffectParts";
const char lbl_8036E674[0x1D] = " DeleteMapEffect : clKPTrap\n";
}
static const char sKPCreate[] = " CreateMapEffect : clKPTrap\n";
static const char sKPModel[] = "KP_jkabe.dat";
static const char sKPFmtAtari[] = "KP_castle_jkabe_%02d_atari_joint";
static const char sKPFmtHani[] = "KP_castle_jkabe_%02d_hani_joint";
static const char sKPFmtJoint[] = "KP_castle_jkabe_%02d_joint";
#pragma force_active reset

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
    int bit;
    unsigned int mask;
    int used;
    DebugPrintf(sKPCreate);
    model=0; entries=0; count=0;
    model=new clNormal3D((char *)sKPModel,0);
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
    /* The clear loop shares `bit` with the bit loop below: only a multi-def
     * counter keeps `li r29,0; mr r30,r29` for the entry offset
     * (regalloc_patterns 73). */
    for (bit=0;bit<count;bit++) {
        entries[bit].jobj=0;
        entries[bit].faces=0;
        entries[bit].faceCount=0;
        entries[bit].anim=0;
        entries[bit].state=0;
        entries[bit].t=0.0f;
        entries[bit].scale=0.0f;
        entries[bit].sub=0;
    }
    for (bit=0;bit<32;bit++) {
        if (mask & (1<<bit)) {
            GrowEntry *e=&entries[used];
            char name[32];
            sprintf(name,sKPFmtAtari,bit);
            GrowJoint *a=ResolveJointByName(model,name);
            sprintf(name,sKPFmtHani,bit);
            GrowJoint *b=ResolveJointByName(model,name);
            sprintf(name,sKPFmtJoint,bit);
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
            /* The target copies the joint position into a stack Vec3 member by
             * member (lfs/stfs) and keeps it in memory across the GrowSub
             * allocation; a plain struct copy uses lwz/stw instead. */
            Vec3Grow *pp=GetPosition(e->jobj);
            Vec3Grow pos;
            Vec3Grow *ppos=&pos;
            ppos->x=pp->x; ppos->y=pp->y; ppos->z=pp->z;
            e->sub=new GrowSub;
            e->sub->pos=*ppos;
            e->sub->scale=1.0f;
            if (++used>=count) break;
        }
    }
}
