#include "game/types/clMapEffectParts.h"
#include "game/ObjViewS22_private.h"
#include "game/types/HSD_JObj.h"
struct clPCGrass : clMapEffectParts {
    virtual ~clPCGrass();
    virtual void Update();
    virtual void Draw();
    clNormal3D **models;
    int count;
    float angle;
    clPCGrass();
};
extern "C" {
extern int g_courseVariantIdx, g_longRoundFlag;
extern const float lbl_806D93E0;
void *FUN_8003b120(unsigned long);
void Object_RenderJObjTree(void *, int);
void Object_DtorWithGXSync(void *, int);
void MemoryManager_Free(void *);
}
static const char grassA[] = "PCA_grass_a.dat";
static const char grassB[] = "PCA_grass_b.dat";
static const char grassC[] = "PCA_grass_c.dat";
static const char grassD[] = "PCA_grass_d.dat";
static const char grassE[] = "PCA_grass_e.dat";
static const char *grassFiles[5] = {grassA,grassB,grassC,grassD,grassE};
clPCGrass::clPCGrass() {
    int mask=0;
    int i, n;
    models=0;
    count=0;
    angle=lbl_806D93E0;
    switch (g_courseVariantIdx) {
    case 0: if (!g_longRoundFlag) mask=0; else mask=0; break;
    case 1: if (!g_longRoundFlag) mask=5; else mask=8; break;
    case 2: if (!g_longRoundFlag) mask=9; else mask=8; break;
    case 3: if (!g_longRoundFlag) mask=18; else mask=16; break;
    }
    for (i=0;i<5;i++) if (mask & (1<<i)) count++;
    if (count==0) return;
    models=(clNormal3D **)FUN_8003b120(count*4);
    if (!models) { count=0; return; }
    for (i=0;i<count;i++) models[i]=0;
    n=0;
    for (i=0;i<5;i++) {
        if (n>=count) break;
        if (mask & (1<<i)) {
            models[n]=new clNormal3D(grassFiles[i],0);
            n++;
        }
    }
}
clPCGrass::~clPCGrass() {
    int i;
    if (count > 0) {
        for (i=0; i<count; i++) Object_DtorWithGXSync(models[i],1);
        MemoryManager_Free(models);
    }
}
extern "C" char lbl_806D93D0[7], lbl_806D93D8[5];
extern "C" float LUT_Sin12Bit(float);
extern "C" float fn_80186960(float);
extern "C" float fn_8018D638(float);
extern "C" HSD_JObj *Archive_GetRootJObj(void *);
extern "C" void __assert(char *, int, char *);
extern "C" void HSD_JObjSetMtxDirtySub(HSD_JObj *);
static inline unsigned char IsDirty(HSD_JObj *j) {
    unsigned int flags;
    unsigned char dirty;
    if (!j) __assert(lbl_806D93D0, 0x25d, lbl_806D93D8);
    flags = j->flags;
    dirty = 0;
    if (!(flags & 0x800000) && (flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void SetScaleY(HSD_JObj *j, float y) {
    if (!j) __assert(lbl_806D93D0, 0x333, lbl_806D93D8);
    j->scale.y = y;
    if (!(j->flags & 0x2000000)) {
        if (j && !IsDirty(j)) HSD_JObjSetMtxDirtySub(j);
    }
}
static inline HSD_JObj *Child(HSD_JObj *j) { if (j == 0) return 0; return j->child; }
static inline HSD_JObj *Next(HSD_JObj *j) { if (j == 0) return 0; return j->next; }
void clPCGrass::Update() {
    float a, odd, even;
    int i, n;
    HSD_JObj *j, *root;
    if (models == 0 || count == 0) return;
    angle += 1.0f;
    a=angle;
    if (a >= 60.0f) angle = a - 60.0f;
    odd = 0.3f * fn_8018D638(LUT_Sin12Bit(3.0f * angle)) + 1.0f;
    even = 0.3f * fn_8018D638(fn_80186960(3.0f * angle)) + 1.0f;
    for (i=0; i<count; i++) {
        if (models[i]) {
            n=0;
            root=Archive_GetRootJObj(models[i]);
            for (j=Child(root); j; j=Next(j)) {
                if (n & 1) SetScaleY(j, odd);
                else SetScaleY(j, even);
                n++;
            }
        }
    }
}
void clPCGrass::Draw() {
    int i;

    if (models == 0 || count == 0) {
        return;
    }
    for (i = 0; i < count; i++) {
        if (models[i] != 0) {
            Object_RenderJObjTree(models[i], 7);
        }
    }
}
