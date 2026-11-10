/* --- owned .rodata 0x803D0300..0x803D0390 (tools/own_data.py) --- */
#include "game/types/size_t.h"
#pragma force_active on
extern "C" const char DNBress_breath_rodata_803D0300[144] = { 32, 68, 101, 108, 101, 116, 101, 77, 97, 112, 69, 102, 102, 101, 99, 116, 32, 58, 32, 99, 108, 68, 78, 66, 114, 101, 115, 115, 10, 0, 0, 0, 32, 67, 114, 101, 97, 116, 101, 77, 97, 112, 69, 102, 102, 101, 99, 116, 32, 58, 32, 99, 108, 68, 78, 66, 114, 101, 115, 115, 10, 0, 0, 0, 68, 78, 65, 95, 101, 102, 95, 105, 99, 101, 95, 106, 111, 105, 110, 116, 0, 0, 0, 0, 103, 101, 116, 74, 111, 105, 110, 116, 69, 114, 114, 111, 114, 33, 33, 32, 45, 32, 100, 110, 66, 114, 101, 115, 115, 46, 99, 112, 112, 32, 76, 105, 110, 101, 58, 50, 50, 50, 10, 0, 101, 102, 95, 100, 105, 110, 111, 95, 98, 114, 101, 115, 115, 46, 100, 97, 116, 0, 0, 0 };
#pragma force_active reset
/*
 * 0x80226954..0x80227FA4: clDNBress (dnBress.cpp), the ice dinosaur's breath
 * on Dino Dino Jungle. When a kart comes close, the dinosaur animation plays,
 * a breath sound starts and fire/frost particles (two variants, picked by the
 * reverse-course flag) are spawned through pointer-to-member tables. Four
 * smoke puffs rise over the lake. The class data (spawn ranges, member
 * function tables, vtable) lives in DNBress_nm3_data_804EDF80 and is addressed off one
 * base; the static initializer (fn_80227FA4) stays in asm.
 */

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

void clDNBress::Breathe() {
    fn_80240014(anim);
    hidden = 1;
    KartDriver *k;
    if ((k = g_playerRenderObj) != 0) {
        float x = KartDriver_GetKartRootMtx(k)[3];
        float z = KartDriver_GetKartRootMtx(k)[11];
        if (InRect(x, z, DNBress_breath_rodata_803D0278) == 1) {
            hidden = 0;
            if (!sePlaying) {
                if (g_gameMode != 2) {
                    SoundMgr_PlaySE(0x44);
                }
                sePlaying = 1;
            }
        } else if (sePlaying) {
            fn_8016C394(0x44);
            sePlaying = 0;
        }
    }
    if (x68 < 0) {
        fn_8016C394(0x44);
        sePlaying = 0;
    }
    if (sePlaying == 1) {
        dir.x = DNBress_breath_data_806D0580;
        dir.y = DNBress_breath_data_806D0584;
        dir.z = DNBress_breath_data_806D0588;
        HSD_JObj *jobj = joint;
        SetupJointMatrix(jobj);
        float(*m)[4] = jobj->mtx;
        PSMTXMultVecSR(m, &dir, &dir);
        pos.x = m[0][3];
        pos.y = m[1][3];
        pos.z = m[2][3];
        fn_8016C288(0x44, &pos);
    }
    Tick();
    if (cooldown == 0 && sePlaying == 1) {
        (this->*spawn)();
    }
    if (cooldown != 0) {
        cooldown--;
    }
    if (++x68 >= lbl_803D0240[1][type]) {
        fn_8023FE74(anim, 0, lbl_803D0240[0][type]);
        x68 = 0;
    }
    if (++timer >= lbl_803D0240[1][type] * 4) {
        x20 = lbl_806DB400;
        x68 = 0;
        timer = 0;
        sePlaying = 0;
        state = 3;
        fn_8023FE74(anim, 0, lbl_803D0240[1][type] + lbl_803D0240[0][type]);
        fn_8016C394(0x44);
    }
}

clDNBress::~clDNBress() {
    fn_8016C394(0x44);
    if (anim) {
        delete anim;
        anim = 0;
    }
    if (model) {
        delete model;
        model = 0;
    }
    if (x14) {
        delete x14;
        x14 = 0;
    }
    if (fx) {
        delete fx;
        fx = 0;
    }
    DebugPrintf(DNBress_breath_rodata_803D0300);
}
