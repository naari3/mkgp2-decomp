#include "game/types/pmf.h"
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

extern "C" const char lbl_80490FE0[];

struct clMapEffectParts {
    // Explicit ABI view keeps derived dispatch data in the shared table pool.
    const void *vtable;
    ~clMapEffectParts();
    void Update();
    void Draw();
    void Enable(int on);
    // No base initializer: the derived ctor stores the base vtable itself, after
    // its locals, so the base-vtable address is numbered after data/strings.
    clMapEffectParts() {}
};

struct clDNBress;
// CodeWarrior's non-virtual member-function dispatch record.
struct MemberFn {
    int thisAdjustment;
    int virtualOffset;
    void (*function)();
};
PMF_TYPE(SpawnFn, clDNBress, void, ());
PMF_TYPE(UpdFn, clDNBress, void, (Particle *p));

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
    void Enable(int on);
    ~clDNBress();
    void Update();
    void Draw();
    void Tick();
    void UpdFire1(Particle *p);
    void SpawnFire1();
    void UpdFire2(Particle *p);
    void SpawnFire2();
    void Breathe();
};

extern "C" {
extern const char DNBress_nm3_rodata_803C6ED0[];
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

// Original writable spawn extents, member dispatch records, RTTI and vtable.
struct DNBressTypeInfo {
    const char *name;
    const void *bases;
    unsigned int flags;
};
struct DNBressDispatch {
    const char *type;
    unsigned int offset;
    void (*slots[5])();
};
extern "C" {
extern const char DNBress_nm3_data_806D058C[];
extern const char DNBress_nm3_data_806D0594[];
void fn_80227AA4();
void fn_80226B20();
void fn_80226954();
void fn_8016A26C();
void fn_80227318();
void fn_802271A4();
void fn_8022760C();
void fn_80227490();
#pragma force_active on
float DNBress_nm3_data_804EDF80[2][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
struct FireRecords { MemberFn spawn; MemberFn upd; } lbl_804EDF98[2] = {
    {{0, -1, fn_80227318}, {0, -1, fn_802271A4}},
    {{0, -1, fn_8022760C}, {0, -1, fn_80227490}}
};
DNBressTypeInfo sdata_806D0540_data_804EDFC8 = {DNBress_nm3_data_806D058C, 0, 0};
DNBressDispatch clDNBress_vtable_804EDFD4 = {
    DNBress_nm3_data_806D0594, 0,
    {fn_80227AA4, fn_80226B20, fn_80226954, fn_8016A26C, 0}
};
#pragma force_active reset
}

static inline const char *DNBressStrings() {
    const char *strings = DNBress_nm3_rodata_803C6ED0 + 0x10000;
    return strings;
}

clDNBress::clDNBress() {
    const char *data = (const char *)DNBress_nm3_data_804EDF80;
    const FireFuncs *fireFuncs = (const FireFuncs *)(data + 0x18);
    // The original unit addresses its shared strings from one retained base.
    const char *strings = DNBressStrings();
    *(const void **)this = lbl_80490FE0;
    vtable = data + 0x54;
    type = 0;
    xc = 0;
    anim = 0;
    x14 = 0;
    fx = 0;
    joint = 0;
    x20 = lbl_806DB400;
    randIdx = 0;
    sePlaying = 0;
    cooldown = 0;
    state = 0;
    x4c = 0;
    timer = 0;
    x54 = lbl_806DB400;
    hidden = 0;
    x68 = 0;
    freeSlot = 0;
    DebugPrintf((strings - 0x6BB0));
    model = 0;
    if (g_longRoundFlag == 0) {
        return;
    }
    if (g_reverseRoundFlag == 1) {
        type++;
    }
    anim = new AnimCtrl;
    if (type == 0) {
        model = new clNormal3D((strings - 0x6D14), 0);
        fn_80240378(anim, (strings - 0x6D14), 0, model, (const char **)(strings - 0x6CF4));
    } else {
        model = new clNormal3D((strings - 0x6D04), 0);
        fn_80240378(anim, (strings - 0x6D04), 0, model, (const char **)(strings - 0x6CF4));
    }
    if (model) {
        clNormal3D_SetScale(model, 0, lbl_806DB400, lbl_806DB404, lbl_806DB400, lbl_806DB400);
    }
    if (model) {
        if (type == 0) {
            joint = ResolveJointByName(model, (strings - 0x6B90));
        } else {
            joint = ResolveJointByName(model, (strings - 0x6B90));
        }
    }
    if (joint == 0) {
        DebugPrintf((strings - 0x6B7C));
        return;
    }
    fx = new clNormal3D((strings - 0x6B54), 1);
    if (fx) {
        JObj_Hide(fx, Archive_GetRootJObj(fx), 4);
        fn_80182954(Archive_GetRootJObj(fx), 1);
        HSD_JObjSetFlags(Archive_GetRootJObj(fx), 0x200);
    }
    for (int i = 0; i < 20; i++) {
        parts[i].active = 0;
        parts[i].c[0] = parts[i].c[1] = parts[i].c[2] = lbl_806DB404;
    }
    for (int i = 0; i < 4; i++) {
        smoke[i].active = 0;
        smoke[i].delay = i * 12 + 45;
        smoke[i].c[0] = lbl_806DB404;
        smoke[i].c[1] = smoke[i].c[2] = lbl_806DB484;
    }
    pos.x = pos.y = pos.z = lbl_806DB400;
    dir.x = dir.y = dir.z = lbl_806DB400;
    x58.x = x58.y = x58.z = lbl_806DB400;
    if (type == 1) {
        spawn = fireFuncs[0].spawn;
        upd = fireFuncs[0].upd;
    } else {
        spawn = fireFuncs[1].spawn;
        upd = fireFuncs[1].upd;
    }
}
