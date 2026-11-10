/*
 * 0x80226954..0x80227FA4: clDNBress (dnBress.cpp), the ice dinosaur's breath
 * on Dino Dino Jungle. When a kart comes close, the dinosaur animation plays,
 * a breath sound starts and fire/frost particles (two variants, picked by the
 * reverse-course flag) are spawned through pointer-to-member tables. Four
 * smoke puffs rise over the lake. The class data (spawn ranges, member
 * function tables, vtable) lives in DNBress_nm3_data_804EDF80 and is addressed off one
 * base; the static initializer (fn_80227FA4) stays in asm.
 */

#include "game/types/size_t.h"
void *operator new(size_t size);
void operator delete(void *p) throw();

typedef float Mtx[3][4];

#include "game/types/Vec3f.h"

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x38 - 0x18];
    Vec3f translate;
    Mtx mtx;
};

#include "game/types/clNormal3D.h"

#include "game/types/AnimCtrl.h"

#include "game/types/KartDriver.h"

#include "game/types/GXChannel.h"

#include "game/types/Particle.h"

#include "game/types/clMapEffectParts.h"

struct clDNBress;
typedef void (clDNBress::*SpawnFn)();
typedef void (clDNBress::*UpdFn)(Particle *p);

struct FireFuncs {
    SpawnFn spawn;
    UpdFn upd;
};

struct clDNBress : clMapEffectParts {
    clNormal3D *model;
    int type;
    unsigned char xc;
    AnimCtrl *anim;
    clNormal3D *x14;
    clNormal3D *fx;
    HSD_JObj *joint;
    float x20;
    Vec3f pos;
    Vec3f dir;
    int randIdx;
    unsigned char sePlaying;
    int cooldown;
    int state;
    int x4c;
    int timer;
    float x54;
    Vec3f x58;
    unsigned char hidden;
    int x68;
    Particle parts[20];
    Particle smoke[4];
    Particle *freeSlot;
    SpawnFn spawn;
    UpdFn upd;

    clDNBress();
    virtual void Enable(int on);
    virtual ~clDNBress();
    virtual void Update();
    virtual void Draw();
    void Tick();
    void UpdFire1(Particle *p);
    void SpawnFire1();
    void UpdFire2(Particle *p);
    void SpawnFire2();
    void Breathe();
};

extern "C" {
extern int g_gameMode;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern KartDriver *g_playerRenderObj;
extern const char lbl_806DB3F0[7];
extern const char lbl_806DB3F8[5];
extern const int lbl_806DB3E8[2];
extern float lbl_806D0548[2];
extern float DNBress_breath_data_806D0580;
extern float DNBress_breath_data_806D0584;
extern float DNBress_breath_data_806D0588;
extern const int lbl_803D0240[4][2];
extern const float DNBress_tick_rodata_803D0260[3];
extern const float lbl_803D026C[3];
extern const float DNBress_breath_rodata_803D0278[4];
extern const Vec3f lbl_803D02A0[2];
extern float DNBress_nm3_data_804EDF80[2][3];
extern FireFuncs lbl_804EDF98[2];
extern float lbl_80495A94[48];
extern const char lbl_803D01BC[];
extern const char lbl_803D01CC[];
extern const char *lbl_803D01DC[];
extern const char DNBress_breath_rodata_803D0300[];
extern const char lbl_803D0320[];
extern const char lbl_803D0340[];
extern const char lbl_803D0354[];
extern const char lbl_803D037C[];
extern const float lbl_806DB400;
extern const float lbl_806DB404;
extern const float lbl_806DB408;
extern const float lbl_806DB40C;
extern const float lbl_806DB410;
extern const float lbl_806DB414;
extern const float lbl_806DB418;
extern const float lbl_806DB41C;
extern const float lbl_806DB420;
extern const float lbl_806DB424;
extern const float lbl_806DB428;
extern const float lbl_806DB42C;
extern const float lbl_806DB430;
extern const float lbl_806DB434;
extern const float lbl_806DB438;
extern const float lbl_806DB43C;
extern const float lbl_806DB440;
extern const float lbl_806DB444;
extern const float lbl_806DB448;
extern const float lbl_806DB44C;
extern const float lbl_806DB450;
extern const float lbl_806DB454;
extern const float lbl_806DB458;
extern const float lbl_806DB45C;
extern const float lbl_806DB460;
extern const float lbl_806DB464;
extern const float lbl_806DB468;
extern const float lbl_806DB46C;
extern const float lbl_806DB470;
extern const float lbl_806DB474;
extern const float lbl_806DB478;
extern const float lbl_806DB47C;
extern const float lbl_806DB480;
extern const float lbl_806DB484;
void __assert(const char *file, int line, const char *cond);
HSD_JObj *LinkedNode_GetField10_OrFallback(clNormal3D *m, int idx);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void Object_RenderJObjTree(clNormal3D *m, int mask);
HSD_JObj *Archive_GetRootJObj(clNormal3D *m);
void *HSD_JObjGetDObj(HSD_JObj *jobj);
void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
void PSMTXScale(Mtx m, float x, float y, float z);
void PSMTXMultVecSR(Mtx m, Vec3f *src, Vec3f *dst);
float PSVECSquareMag(Vec3f *v);
void Object_SetColorRGBA(clNormal3D *m, int idx, float r, float g, float b, float a);
void Object_DriveAnimMatrix(clNormal3D *m);
void clNormal3D_SetScale(clNormal3D *m, int idx, float x, float y, float z, float w);
KartDriver *GetKartSlotKartVariant(int slot);
void *GetPlayerCarObject(void);
KartDriver *CarObject_GetRenderObj(void *car);
const float *KartDriver_GetKartRootMtx(KartDriver *k);
void fn_80240014(AnimCtrl *a);
void fn_8023FE74(AnimCtrl *a, int b, int frame);
void fn_80240378(AnimCtrl *a, const char *file, int b, clNormal3D *m, const char **names);
void SoundMgr_PlaySE(int id);
void fn_8016C288(int id, Vec3f *pos);
void fn_8016C1F8(int id, float vol);
void fn_8016C394(int id);
float LUT_Cosine(float a);
float LUT_Sine(float a);
void DebugPrintf(const char *fmt, ...);
HSD_JObj *ResolveJointByName(clNormal3D *m, const char *name);
void JObj_Hide(clNormal3D *m, HSD_JObj *jobj, int flags);
void fn_80182954(HSD_JObj *jobj, int on);
}

static inline HSD_JObj *GetJObj(clNormal3D *m) {
    HSD_JObj *jobj = LinkedNode_GetField10_OrFallback(m, 0);
    if (jobj == 0) {
        __assert(lbl_806DB3F0, 0x3E4, lbl_806DB3F8);
    }
    return jobj;
}

static inline void SetupJointMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB3F0, 0x47C, lbl_806DB3F8);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806DB3F0, 0x25D, lbl_806DB3F8);
        }
        unsigned int flags = jobj->flags;
        unsigned char dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (dirty) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline bool InRect(float x, float z, const float *r) {
    if (x < r[0]) {
        return 0;
    }
    if (x > r[2]) {
        return 0;
    }
    if (z < r[1]) {
        return 0;
    }
    if (z > r[3]) {
        return 0;
    }
    return 1;
}

void clDNBress::SpawnFire2() {
    Particle *p = freeSlot;
    if (p == 0) {
        return;
    }
    p->v.x = dir.x;
    freeSlot->v.y = 3.0f * dir.y;
    freeSlot->v.z = dir.z;
    freeSlot->pos.x = pos.x;
    freeSlot->pos.y = pos.y;
    freeSlot->pos.z = pos.z;
    freeSlot->scale = 3.0f;
    freeSlot->alpha = 1.0f;
    freeSlot->speed = 0.4f * lbl_80495A94[randIdx] + 1.2f;
    freeSlot->grow = 0.1f * lbl_80495A94[randIdx] + 0.1f;
    freeSlot->active = 1;
    *(Vec3f*)freeSlot->c = *(const Vec3f*)lbl_803D026C;
    float a = 3.141592025756836f * lbl_80495A94[randIdx] - 1.570796012878418f;
    freeSlot->dvx = dir.x * LUT_Cosine(a);
    freeSlot->dvz = dir.z * LUT_Sine(a);
    freeSlot->dvy = -0.015f;
    if (++randIdx >= 48) {
        randIdx = 0;
    }
    cooldown = 4;
    freeSlot = 0;
}
