#ifndef DNFLASH_PRIVATE_H
#define DNFLASH_PRIVATE_H
/*
 * 0x802280F8..0x80228D64: clDNFlash (Dino Dino Jungle camera flashes).
 * Flash points are read from DNA_cameraF_trans.dat into a 3x3 grid of
 * areas; while the player is near, flashes pop at random points of the
 * player's row and column, and a burst plays when the player drives through
 * one of four trigger boxes in the right direction. The TU owns .rodata
 * 0x803D0390..0x803D08A8, addressed off one hoisted base. The static
 * initializer (fn_80228D64, fills the trigger box bounds) and its min/max
 * helpers stay in asm.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

typedef float Mtx[3][4];

#include "game/types/Vec3f.h"

struct HSD_JObj {
    char pad00[8];
    HSD_JObj *next;
    HSD_JObj *parent;
    HSD_JObj *child;
    unsigned int flags;
    char pad18[0x38 - 0x18];
    Vec3f translate;
};

#include "game/types/clNormal3D.h"

struct KartRender;

#include "game/types/GXChannel.h"

#include "game/types/FlashPoint.h"

struct FlashPart {
    unsigned char active;
    float scale;
    float alpha;
    float dscale;
    int life;
    FlashPoint *owner;
    void Tick();
    void Start(FlashPoint *pt);
};

struct FlashPartObj : FlashPart {
    FlashPartObj();
};

struct TriggerBox {
    Vec3f a;
    Vec3f b;
};

#include "game/types/clMapEffectParts.h"

struct clDNFlash : clMapEffectParts {
    clNormal3D *fx;
    int timer;
    unsigned char inside;
    int burst;
    int counts[9];
    FlashPoint points[9][30];
    FlashPart parts[20];
    FlashPart *free[2];

    virtual void _key();
    clDNFlash();
    virtual void Enable(int on);
    virtual ~clDNFlash();
    virtual void Update();
    virtual void Draw();
    unsigned char Check();
    void Spawn();
};

extern "C" {
extern KartRender *g_playerRenderObj;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern const char lbl_806DB4A4[7];
extern const char lbl_806DB4AC[5];
extern const float lbl_806DB490;
extern const int lbl_806DB494;
extern const float lbl_806DB498;
extern const float lbl_806DB49C;
extern const float lbl_806DB4A0;
extern const Vec3f lbl_804EE008[4];
extern const Vec3f lbl_804EE038[4];
void __assert(const char *file, int line, const char *cond);
HSD_JObj *Archive_GetRootJObj(clNormal3D *m);
void *HSD_JObjGetDObj(HSD_JObj *jobj);
void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
void fn_80182954(HSD_JObj *jobj, int on);
float (*Object_GetJObjLocalMatrix(clNormal3D *m))[4];
void Object_DtorWithGXSync(clNormal3D *m, int flag);
void Object_SetColorAlphaOnly(clNormal3D *m, int idx, float alpha);
void PSMTXScale(Mtx m, float x, float y, float z);
void PSMTXMultVec(float (*m)[4], Vec3f *src, Vec3f *dst);
const float *KartDriver_GetKartRootMtx(KartRender *k);
float *KartMovement_GetVelocityPtr(KartRender *k);
void DebugPrintf(const char *fmt, ...);
int rand(void);
}

extern const unsigned int DNFlash_tail_rodata_803D0390[0x102];
extern const float DNFlash_tail_rodata_803D0798[3];
extern const float lbl_803D07A4[3];
extern const float lbl_803D07B0[3];
extern const TriggerBox DNFlash_tail_rodata_803D07BC[4];
extern const char lbl_803D081C[0xA];
extern const char lbl_803D0828[0x11];
extern const char lbl_803D083C[0x1E];
extern const char lbl_803D085C[0x1E];
extern const char lbl_803D087C[0x10];
extern const char lbl_803D088C[0x16];


template <class T> T Min(const T &a, const T &b) {
    return a < b ? a : b;
}

static inline int AreaIndex(float x, float z) {
    int ix = -1;
    int iz = ix;
    for (int i = 0; i < 3; i++) {
        if (x < lbl_803D07A4[i]) {
            ix = i;
            break;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (z > lbl_803D07B0[i]) {
            iz = i;
            break;
        }
    }
    if (ix < 0 || iz < 0) {
        return -1;
    }
    return ix + iz * 3;
}

static inline int AreaIndexV(const Vec3f &p) {
    int ix = -1;
    int iz = ix;
    for (int i = 0; i < 3; i++) {
        if (p.x < lbl_803D07A4[i]) {
            ix = i;
            break;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (p.z > lbl_803D07B0[i]) {
            iz = i;
            break;
        }
    }
    if (ix < 0 || iz < 0) {
        return -1;
    }
    return ix + iz * 3;
}

static inline void GetTranslation(HSD_JObj *jobj, Vec3f *out) {
    if (jobj == 0) {
        __assert(lbl_806DB4A4, 0x3E4, lbl_806DB4AC);
    }
    *out = jobj->translate;
}

static inline HSD_JObj *JObjNext(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline HSD_JObj *JObjChild(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}


#endif
