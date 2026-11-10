#ifndef GAME_DNSTARTCAMERA_PRIVATE_H
#define GAME_DNSTARTCAMERA_PRIVATE_H
/*
 * 0x8022929C..0x80229998: clDNStartCamera (Dino Dino Jungle start-line
 * cameramen). Ten cameramen turn to face the player while the player is in
 * the start area, and six of them fire flashes (the clDNFlash FlashPart
 * helpers) at random intervals. The TU owns .rodata 0x803D08F0..0x803D0DB0,
 * addressed off one hoisted base.
 */

typedef float Mtx[3][4];

#include "game/types/Vec3f.h"

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x1C - 0x18];
    Vec3f rotate;
    char pad28[0x38 - 0x28];
    Vec3f translate;
    Mtx mtx;
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
    void Init();
};

struct CamFlash {
    FlashPoint pt;
    FlashPart fp;
    int timer;
};

#include "game/types/clMapEffectParts.h"

struct clDNStartCamera : clMapEffectParts {
    clNormal3D *flash;
    clNormal3D *cam;
    HSD_JObj *men[10];
    HSD_JObj *flashJoints[6];
    unsigned char hidden;
    CamFlash flashes[6];

    clDNStartCamera(HSD_JObj *at);
    virtual void Enable(int on);
    virtual ~clDNStartCamera();
    virtual void Update();
    virtual void Draw();
};

extern "C" {
extern KartRender *g_playerRenderObj;
extern const char lbl_806DB4E0[7];
extern const char lbl_806DB4E8[5];
extern const float lbl_806DB4F0;
extern const float lbl_806DB4F4;
extern const float lbl_806DB4F8;
void __assert(const char *file, int line, const char *cond);
HSD_JObj *Archive_GetRootJObj(clNormal3D *m);
void *HSD_JObjGetDObj(HSD_JObj *jobj);
void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void fn_80182954(HSD_JObj *jobj, int on);
void Object_DtorWithGXSync(clNormal3D *m, int flag);
void Object_SetColorAlphaOnly(clNormal3D *m, int idx, float alpha);
void Object_RenderJObjTree(clNormal3D *m, int flags);
void Object_SetJObjPositionX(clNormal3D *m, float v);
void Object_SetJObjPositionY(clNormal3D *m, float v);
void Object_SetJObjField40(clNormal3D *m, float v);
void clNormal3D_SetScale(clNormal3D *m, int anim, float t, float a, float b, float c);
void clNormal3D_Exec(clNormal3D *m);
void Object_DriveAnimMatrix(clNormal3D *m);
HSD_JObj *ResolveJointByName(clNormal3D *m, const char *name);
void PSMTXScale(Mtx m, float x, float y, float z);
const float *KartDriver_GetKartRootMtx(KartRender *k);
double atan2(double y, double x);
int sprintf(char *buf, const char *fmt, ...);
int rand(void);
}

extern const unsigned int DNStartCamera_m2_rodata_803D08F0[0x102];
extern const float DNStartCamera_nm1_rodata_803D0CF8[4];
extern const char lbl_803D0D08[0x10];
extern const char lbl_803D0D18[0x11];
extern const char lbl_803D0D2C[0x25];
extern const char lbl_803D0D54[0x14];
extern const char lbl_803D0D68[0x10];
extern const char lbl_803D0D78[0xB];
extern const char lbl_803D0D84[0x17];
extern const char lbl_803D0D9C[0x13];

static inline float JObjGetTranslationX(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x3F1, lbl_806DB4E8);
    }
    return jobj->translate.x;
}

static inline float JObjGetTranslationY(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x3FD, lbl_806DB4E8);
    }
    return jobj->translate.y;
}

static inline float JObjGetTranslationZ(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x409, lbl_806DB4E8);
    }
    return jobj->translate.z;
}

static inline unsigned char JObjMtxIsDirty(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x25D, lbl_806DB4E8);
    }
    unsigned int flags = jobj->flags;
    unsigned char dirty = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        dirty = 1;
    }
    return dirty;
}

static inline void JObjSetupMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x47C, lbl_806DB4E8);
    }
    if (jobj != 0) {
        if (JObjMtxIsDirty(jobj)) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

static inline void JObjSetRotationY(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806DB4E0, 0x2B8, lbl_806DB4E8);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806DB4E0, 0x2B9, lbl_803D0D2C);
    }
    jobj->rotate.y = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}


#endif
