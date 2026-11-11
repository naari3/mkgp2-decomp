/* clKPTrap: draw, update, destructor and constructor (0x801706C8..0x80170EE0).
 * Deferred code generation emits these definitions in reverse source order. */
#include "game/types/clKPTrap.h"
#include "game/singleton.h"

extern "C" {
extern int g_longRoundFlag, g_reverseRoundFlag;
extern char lbl_806D8CD8[7], lbl_806D8CE0[5];
void DebugPrintf(const char *, ...);
int HSD_GetNbBits(unsigned int);
void *FUN_8003b120(unsigned long);
int sprintf(char *, const char *, ...);
HSD_JObj *ResolveJointByName(clNormal3D *, const char *);
GrowDObj *HSD_JObjGetDObj(HSD_JObj *);
int fn_80184F24(HSD_JObj *, void *, DListQuadInfo *, int);
int fn_80183A5C(void *);
int fn_80185630(HSD_JObj *, void *, void *, int);
void __assert(const char *, int, const char *);
}

/* Original constant pool. Named arrays precede the compiler RTTI strings;
 * the deferred destructor and constructor supply the following literals. */
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
#pragma force_active reset

static inline void *GetPObj(GrowDObj *d) {
    if (d) return d->pobj;
    return 0;
}
static inline void *GetJointPObj(HSD_JObj *j) {
    return GetPObj(HSD_JObjGetDObj(j));
}
static inline Vec3f *GetPosition(HSD_JObj *j) {
    if (!j) __assert(lbl_806D8CD8,0x3E4,lbl_806D8CE0);
    return (Vec3f *)&j->translate;
}

extern "C" {
void HSD_JObjSetMtxDirtySub(HSD_JObj *);
void HSD_JObjDispAll(HSD_JObj *, int, int, int);
void fn_8016F158(void *);
extern int g_totalLaps;
extern void *lbl_806D1138;
KartDriver *GetKartSlotKartVariant(int);
float *KartDriver_GetKartRootMtx(KartDriver *);
unsigned char fn_80123480(void *, Vec3f *);
void fn_8016F584(GrowSub *);
void SpecialFaceMesh_AddFace(void *, GrowFace *);
float LUT_Sin12Bit(float);
void Object_DtorWithGXSync(void *, int);
void fn_80123B48(void *, int);
void *fn_8016F9A0(void *, short);
void MemoryManager_Free(void *);
}
static inline HSD_JObj *HSD_JObjGetChild(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

static inline HSD_JObj *HSD_JObjGetNext(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char clean;

    if (jobj == 0) {
        __assert(lbl_806D8CD8, 0x25D, lbl_806D8CE0);
    }
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        clean = 1;
    }
    if (!clean) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetScaleY(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D8CD8, 0x333, lbl_806D8CE0);
    }
    jobj->scale.y = y;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}


clKPTrap::clKPTrap() {
    int bit;
    unsigned int mask;
    int used;
    DebugPrintf(" CreateMapEffect : clKPTrap\n");
    model=0; entries=0; count=0;
    model=new clNormal3D((char *)"KP_jkabe.dat",0);
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
        entries[bit].trigger=0;
        entries[bit].state=0;
        entries[bit].t=0.0f;
        entries[bit].scale=0.0f;
        entries[bit].sub=0;
    }
    for (bit=0;bit<32;bit++) {
        if (mask & (1<<bit)) {
            GrowEntry *e=&entries[used];
            char name[32];
            sprintf(name,"KP_castle_jkabe_%02d_atari_joint",bit);
            HSD_JObj *a=ResolveJointByName(model,name);
            sprintf(name,"KP_castle_jkabe_%02d_hani_joint",bit);
            HSD_JObj *b=ResolveJointByName(model,name);
            sprintf(name,"KP_castle_jkabe_%02d_joint",bit);
            e->jobj=ResolveJointByName(model,name);
            if (!e->jobj || !a || !b) continue;
            DListQuadInfo face;
            if (fn_80184F24(b,GetJointPObj(b),&face,1)) {
                e->trigger=new GrowAnim(&face,1);
            }
            void *pobj=GetJointPObj(a);
            e->faceCount=fn_80183A5C(pobj);
            if (e->faceCount) {
                e->faces=(GrowFace *)FUN_8003b120(e->faceCount*0x34);
                int n=fn_80185630(a,pobj,e->faces,e->faceCount);
                if (n<e->faceCount) e->faceCount=n;
            }
            /* The target copies the joint position into a stack Vec3 member by
             * member (lfs/stfs) and keeps it in memory across the GrowSub
             * allocation; a plain struct copy uses lwz/stw instead. */
            Vec3f *pp=GetPosition(e->jobj);
            Vec3f pos;
            Vec3f *ppos=&pos;
            ppos->x=pp->x; ppos->y=pp->y; ppos->z=pp->z;
            e->sub=new GrowSub;
            e->sub->pos=*ppos;
            e->sub->scale=1.0f;
            if (++used>=count) break;
        }
    }
}

clKPTrap::~clKPTrap() {
    int i;

    if (model) {
        Object_DtorWithGXSync(model, 1);
    }
    if (entries) {
        for (i = 0; i < count; i++) {
            if (entries[i].faces) {
                MemoryManager_Free(entries[i].faces);
                entries[i].faces = 0;
                entries[i].faceCount = 0;
            }
            if (entries[i].trigger) {
                fn_80123B48(entries[i].trigger, 1);
                entries[i].trigger = 0;
            }
            if (entries[i].sub) {
                fn_8016F9A0(entries[i].sub, 1);
                entries[i].sub = 0;
            }
        }
        MemoryManager_Free(entries);
    }
    DebugPrintf(" DeleteMapEffect : clKPTrap\n");
}

void clKPTrap::Update() {
    int i;
    GrowEntry *e;

    for (i = 0; i < count; i++) {
        e = &entries[i];
        if (e->state == 0 && e->trigger) {
            int k;
            for (k = 0; k < 8; k++) {
                KartDriver *kart = GetKartSlotKartVariant(k);
                if (kart && kart->lap < g_totalLaps) {
                    Vec3f p;
                    p.x = KartDriver_GetKartRootMtx(kart)[3];
                    p.y = KartDriver_GetKartRootMtx(kart)[7];
                    p.z = KartDriver_GetKartRootMtx(kart)[11];
                    if (fn_80123480(e->trigger, &p)) {
                        e->state = 1;
                        e->sub->started = 1;
                        break;
                    }
                }
            }
        }
        fn_8016F584(e->sub);
        switch (e->state) {
        case 1: {
            unsigned char done = e->sub->done;
            e->sub->done = 0;
            if (done) {
                void *mesh;
                int f;
                e->state = 2;
                mesh = SINGLETON_INSTANCE(lbl_806D1138);
                for (f = 0; f < e->faceCount; f++) {
                    SpecialFaceMesh_AddFace(mesh, &e->faces[f]);
                }
            }
            break;
        }
        case 2:
            e->t += 0.05f;
            if (e->t < 1.0f) {
                if (e->t <= 0.75f) {
                    e->scale = 1.5f * LUT_Sin12Bit(120.0f * e->t);
                } else {
                    e->scale = 0.5f * LUT_Sin12Bit(360.0f * (e->t - 0.75f) + 90.0f) + 1.0f;
                }
            } else {
                e->state = 3;
                e->t = 0.0f;
                e->scale = 1.0f;
            }
            break;
        }
    }
}

void clKPTrap::Draw() {
    int i;
    GrowEntry *e;
    HSD_JObj *jobj;

    for (i = 0; i < count; i++) {
        e = &entries[i];

        if (e->state >= 2) {
            for (jobj = HSD_JObjGetChild(e->jobj); jobj != 0; jobj = HSD_JObjGetNext(jobj)) {
                HSD_JObjSetScaleY(jobj, e->scale);
            }
            HSD_JObjDispAll(e->jobj, 0, 7, 0);
        }
        fn_8016F158(e->sub);
    }
}

#pragma readonly_strings on
