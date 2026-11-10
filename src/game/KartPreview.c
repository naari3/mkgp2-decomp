/*
 * Kart/driver preview model shown on the select screens
 * (0x8013C4A4..0x8013D4B0): model wrapper setters, render, anim, dtor
 * and ctor. The render target singleton lives in RenderTargetSingleton.c.
 *
 * The model setters and the render function start with
 * `if (kart == 0 || driver == 0) return;`, which is what produces the
 * `beq end; ...; bne body; b end` branch-over-branch on the second test.
 * The ctor (fn_8013CC24) is a real C++ constructor (KPCtor) so that the
 * compiler emits its exception table.
 */

#pragma cplusplus on

extern "C" {

typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned char pad18[0x44 - 0x18];
    unsigned char anim[1];
} HSD_JObj;

#include "game/types/RenderTargetHolder.h"

#include "game/types/CharacterData.h"

#include "game/types/KartPreview.h"

extern unsigned int RenderTargetSingleton_bss_806D1558;
extern RenderTargetHolder *RenderTargetSingleton_bss_806D155C;
extern char RenderTargetSingleton_data_8048EA78[];
extern char lbl_806D76D0[7];
extern char lbl_806D76D8[5];
extern const float lbl_806D76E0;
extern const float lbl_806D76E4;
extern char KartPreview_data_8048EAD8[];
extern char clCSModelInterface_vtable_8048EAE8[];

extern void HSD_LObjDeleteCurrentAll(int);
extern void HSD_LObjAddCurrent(void *rt);
extern void HSD_LObjRemoveAll(void *rt);
extern void *HSD_LObjLoadDesc(void *desc);
extern void *Alloc(unsigned int size);
extern void MemoryManager_TimedFree(void *p);
extern void Object_SetColorAlphaOnly(void *obj, int, float a);
extern void Object_SetColorRGBA(void *obj, int, float r, float g, float b, float a);
extern void Object_SetJObjRotationY(void *obj, float r);
extern void Object_SetJObjRotationX(void *obj, float r);
extern void Object_SetJObjScaleXYZ(void *obj, float x, float y, float z);
extern void *fn_8013BC98(void);
extern void fn_8013BB1C(void *cam, float x, float y);
extern unsigned char fn_8013BC38(void *cam);
extern void fn_8013BBFC(void *cam);
extern void fn_8013BB9C(void *cam);
extern void fn_8013BCA0(void);
extern void Object_RenderJObjTree(void *obj, int flags);
extern void __assert(char *file, int line, char *expr);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
extern void Object_SetAnimBinding(void *obj, void *anim, int);
extern void Object_DriveAnimMatrix(void *obj);
/* fakematch (regalloc_patterns §74): the real prototype is
 * (obj, anim, frame, a, b, c) (Normal3DScale.c). Declaring the first float
 * before the anim pointer keeps the same argument registers but makes the
 * ctor evaluate `1.0f` before `anims14[0]`, as the target does. */
extern void clNormal3D_SetScale(void *obj, float frame, void *anim, float a, float b, float c);
extern void *Archive_GetRootJObj(void *obj);
extern void ObjectTree_BlendOrCopy_Timed(void *obj, void *a, void *b, int, float t);
extern void clNormal3D_Exec(void *obj);
extern CharacterData *GetCharacterDataEntry(int chara);
extern void HSD_JObjClearFlags(HSD_JObj *jobj, int flags);
extern void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
extern void Object_DtorWithGXSync(void *obj, int flag);

extern void fn_8013C334(RenderTargetHolder *h);
extern int fn_8013C34C(RenderTargetHolder *h);
extern RenderTargetHolder *fn_8013C3B8(void);
extern void fn_8013C3C0(void);
extern int fn_8013C428(void);

void fn_8013C4A4(KartPreview *p, float a) {
    if (p->kart == 0 || p->driver == 0) {
        return;
    }
    Object_SetColorAlphaOnly(p->kart, 0, a);
    Object_SetColorAlphaOnly(p->obj8, 0, a);
    Object_SetColorAlphaOnly(p->driver, 0, a);
    if (p->obj24) {
        Object_SetColorAlphaOnly(p->obj24, 0, a);
    }
}


void fn_8013C534(KartPreview *p, float r, float g, float b, float a) {
    if (p->kart == 0 || p->driver == 0) {
        return;
    }
    Object_SetColorRGBA(p->kart, 0, r, g, b, a);
    Object_SetColorRGBA(p->obj8, 0, r, g, b, a);
    Object_SetColorRGBA(p->driver, 0, r, g, b, a);
    if (p->obj24) {
        Object_SetColorRGBA(p->obj24, 0, r, g, b, a);
    }
}


void fn_8013C5FC(KartPreview *p, float r) {
    if (p->kart == 0 || p->driver == 0) {
        return;
    }
    Object_SetJObjRotationY(p->kart, r);
    Object_SetJObjRotationY(p->obj8, r);
    Object_SetJObjRotationY(p->driver, r);
    Object_SetJObjRotationY(p->obj10, r);
}


void fn_8013C674(KartPreview *p, float r) {
    if (p->kart == 0 || p->driver == 0) {
        return;
    }
    Object_SetJObjRotationX(p->kart, r);
    Object_SetJObjRotationX(p->obj8, r);
    Object_SetJObjRotationX(p->driver, r);
    Object_SetJObjRotationX(p->obj10, r);
}


void fn_8013C6EC(KartPreview *p, float x, float y, float z) {
    if (p->kart == 0 || p->driver == 0) {
        return;
    }
    Object_SetJObjScaleXYZ(p->kart, x, y, z);
    Object_SetJObjScaleXYZ(p->obj8, x, y, z);
    Object_SetJObjScaleXYZ(p->driver, x, y, z);
    Object_SetJObjScaleXYZ(p->obj10, x, y, z);
    if (p->obj24) {
        Object_SetJObjScaleXYZ(p->obj24, x, y, z);
    }
}


void fn_8013C7B0(KartPreview *p, float x, float y) {
    p->view_x = x;
    p->view_y = y;
}

/* jobj.h inlines (HSD_JObjMtxIsDirty / SetupMatrix / GetMtxPtr), as in
 * AnimState_UpdateEquipped.c. */
static inline unsigned char HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;

    if (jobj == 0) {
        __assert(lbl_806D76D0, 0x25D, lbl_806D76D8);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetupMatrix(HSD_JObj *jobj)
{
    if (jobj == 0) {
        return;
    }
    if (HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline void *HSD_JObjGetMtxPtr(HSD_JObj *jobj)
{
    if (jobj == 0) {
        __assert(lbl_806D76D0, 0x47C, lbl_806D76D8);
    }
    HSD_JObjSetupMatrix(jobj);
    return jobj->anim;
}

void fn_8013C7BC(KartPreview *p) {
    if (p->kart == 0 || p->driver == 0) {
        return;
    }
    if (fn_8013BC98() == 0) {
        return;
    }
    if (fn_8013C3B8() == 0) {
        return;
    }
    fn_8013BB1C(fn_8013BC98(), p->view_x, p->view_y);
    if (!fn_8013BC38(fn_8013BC98())) {
        return;
    }
    fn_8013C34C(fn_8013C3B8());
    fn_8013BBFC(fn_8013BC98());
    Object_RenderJObjTree(p->kart, 7);
    Object_RenderJObjTree(p->obj8, 7);
    Object_RenderJObjTree(p->driver, 7);
    if (p->obj24 != 0 && p->jobj28 != 0) {
        Object_SetAnimBinding(p->obj24, HSD_JObjGetMtxPtr(p->jobj28), 0);
        Object_DriveAnimMatrix(p->obj24);
        Object_RenderJObjTree(p->obj24, 7);
    }
    fn_8013BB9C(fn_8013BC98());
    fn_8013C334(fn_8013C3B8());
}


void fn_8013C91C(KartPreview *p) {
    void *anim;
    float frame;
    if (p->driver) {
        if (p->anim_state == 2) {
            anim = p->anims14[2];
        } else if (p->anim_state == 3) {
            anim = p->anims14[3];
        } else {
            anim = p->anims14[1];
        }
        clNormal3D_SetScale(p->obj10, p->frame, anim, lbl_806D76E0, lbl_806D76E0, lbl_806D76E0);
        ObjectTree_BlendOrCopy_Timed(p->driver, Archive_GetRootJObj(p->obj10), Archive_GetRootJObj(p->driver), 0, lbl_806D76E0);
        Object_DriveAnimMatrix(p->driver);
        if (p->obj24) {
            clNormal3D_Exec(p->obj24);
        }
        frame = p->frame + lbl_806D76E4;
        p->frame = frame;
        if (frame >= p->end_frame) {
            p->frame = lbl_806D76E0;
        }
    }
}

void fn_8013CA04(KartPreview *p) {
    p->anim_state = 3;
    p->frame = 0.0f;
    p->end_frame = GetCharacterDataEntry(p->chara)->anim24;
    HSD_JObjClearFlags(p->jobj3C, 0x10);
    HSD_JObjSetFlags(p->jobj40, 0x10);
    HSD_JObjSetFlags(p->jobj44, 0x10);
}

void fn_8013CA70(KartPreview *p) {
    p->anim_state = 2;
    p->frame = 0.0f;
    p->end_frame = GetCharacterDataEntry(p->chara)->anim1C;
    if (p->chara == 3) {
        HSD_JObjClearFlags(p->jobj40, 0x10);
        HSD_JObjSetFlags(p->jobj3C, 0x10);
        HSD_JObjSetFlags(p->jobj44, 0x10);
    } else {
        HSD_JObjClearFlags(p->jobj3C, 0x10);
        HSD_JObjSetFlags(p->jobj40, 0x10);
        HSD_JObjSetFlags(p->jobj44, 0x10);
    }
}

KartPreview *fn_8013CB10(KartPreview *p, short flag) {
    int i;
    if (p) {
        p->vtbl = KartPreview_data_8048EAD8;
        if (p->kart) {
            Object_DtorWithGXSync(p->kart, 1);
        }
        if (p->obj8) {
            Object_DtorWithGXSync(p->obj8, 1);
        }
        if (p->driver) {
            Object_DtorWithGXSync(p->driver, 1);
        }
        if (p->obj10) {
            Object_DtorWithGXSync(p->obj10, 1);
        }
        for (i = 0; i < 4; i++) {
            if (p->anims14[i]) {
                Object_DtorWithGXSync(p->anims14[i], 1);
            }
        }
        if (p->obj24) {
            Object_DtorWithGXSync(p->obj24, 1);
        }
        fn_8013BCA0();
        fn_8013C3C0();
        if (p) {
            p->vtbl = clCSModelInterface_vtable_8048EAE8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(p);
        }
    }
    return p;
}

typedef struct KPVec3 {
    float x, y, z;
} KPVec3;

typedef struct KPJObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned char pad18[0x38 - 0x18];
    KPVec3 translate;
} KPJObj;

typedef struct KPModelName {
    char *name;
} KPModelName;

typedef struct KPCharData {
    int pad0;
    char *driverModel;  /* 0x04 */
    char *kartModel;    /* 0x08 */
    unsigned char pad0C[0x18 - 0x0C];
    char **anims;       /* 0x18 */
} KPCharData;

/* .rodata 0x803600E0: anim indices and the model/joint name strings */
typedef struct KPStrings {
    char wingJoint[0x1C];      /* 0x40 */
    char wingModel[0x0C];      /* 0x5C */
    char fmtHead[0x18];        /* 0x68 */
    char fmtHandL[0x18];       /* 0x80 */
    char fmtHandR[0x18];       /* 0x98 */
    char kartModel[0x10];      /* 0xB0 */
    char kartJoint[4][0x18];   /* 0xC0 */
    char fmtDriver[4][0x18];   /* 0x120 */
    char hidden[20][0x18];     /* 0x180 */
} KPStrings;

extern KPModelName *GetKartModelNameEntry(int chara, int kind);
extern KPJObj *ResolveJointByName(void *model, const char *name);
extern void clNormal3D_Construct(void *self, const char *name, int flags);
extern void clNormal3D_SetFlags(void *model, unsigned int flags, int b);
extern void fn_8013BD7C(void);
extern int sprintf(char *buf, const char *fmt, ...);
extern void HSD_JObjSetFlagsAll(void *jobj, int flags);
extern void HSD_JObjSetMtxDirtySub(KPJObj *jobj);
extern const float lbl_806D76E8;
extern const float lbl_806D76EC;

/* .rodata 0x803600E0..0x80360440 (TU-owned). The ctor addresses everything
 * from the section start, so the tables it reads are statics. */
extern const int KartPreview_rodata_803600E0[4];
extern const char lbl_803600F0[9];
extern const char lbl_803600FC[0xE];
extern const char lbl_8036010C[0x13];
const int KartPreview_rodata_803600E0[4] = {0, 5, 42, 43};
const char lbl_803600F0[9] = "mspacman";
const char lbl_803600FC[0xE] = "clCSKartModel";
const char lbl_8036010C[0x13] = "clCSModelInterface";
static const char sKPWingJoint[] = "chara_peach_pony_null_joint";
static const char sKPWingModel[] = "pony.dat";
static const char sKPFmtHead[] = "chara_%s_hand_goo_joint";
static const char sKPFmtHandL[] = "chara_%s_hand_pa_joint";
static const char sKPFmtHandR[] = "chara_%s_hand_fin_joint";
static const char sKPKartModel[] = "cart_tire.dat";
static const char sKPKartJoint0[] = "cart_tireset_fl_joint";
static const char sKPKartJoint1[] = "cart_tireset_fr_joint";
static const char sKPKartJoint2[] = "cart_tireset_rl_joint";
static const char sKPKartJoint3[] = "cart_tireset_rr_joint";
static const char sKPFmtDriver0[] = "%s_cart_tire_fl_joint";
static const char sKPFmtDriver1[] = "%s_cart_tire_fr_joint";
static const char sKPFmtDriver2[] = "%s_cart_tire_rl_joint";
static const char sKPFmtDriver3[] = "%s_cart_tire_rr_joint";
static const char sKPHidden0[] = "cart_big_tire_fl_joint";
static const char sKPHidden1[] = "cart_big_tire_fr_joint";
static const char sKPHidden2[] = "cart_big_tire_rl_joint";
static const char sKPHidden3[] = "cart_big_tire_rr_joint";
static const char sKPHidden4[] = "cart_kaku_tire_fl_joint";
static const char sKPHidden5[] = "cart_kaku_tire_fr_joint";
static const char sKPHidden6[] = "cart_kaku_tire_rl_joint";
static const char sKPHidden7[] = "cart_kaku_tire_rr_joint";
static const char sKPHidden8[] = "cart_oil_tire_fl_joint";
static const char sKPHidden9[] = "cart_oil_tire_fr_joint";
static const char sKPHidden10[] = "cart_oil_tire_rl_joint";
static const char sKPHidden11[] = "cart_oil_tire_rr_joint";
static const char sKPHidden12[] = "cart_punk_grid_fl_joint";
static const char sKPHidden13[] = "cart_punk_grid_fr_joint";
static const char sKPHidden14[] = "cart_punk_grid_rl_joint";
static const char sKPHidden15[] = "cart_punk_grid_rr_joint";
static const char sKPHidden16[] = "cart_punk_tire_fl_joint";
static const char sKPHidden17[] = "cart_punk_tire_fr_joint";
static const char sKPHidden18[] = "cart_punk_tire_rl_joint";
static const char sKPHidden19[] = "cart_punk_tire_rr_joint";
extern char *KartPreview_data_8048EA98[];
extern void dtor_8013DCBC();

#define KP_JOBJ(j) ((KPJObj *)(j))

static inline void KP_GetTranslate(KPJObj *j, KPVec3 *v) {
    if (!j) {
        __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
    }
    *v = j->translate;
}

static inline unsigned char KP_MtxIsDirty(KPJObj *j) {
    unsigned char ret;

    if (!j) {
        __assert(lbl_806D76D0, 0x25d, lbl_806D76D8);
    }
    ret = 0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) {
        ret = 1;
    }
    return ret;
}

static inline void KP_SetMtxDirty(KPJObj *j) {
    if (j && !KP_MtxIsDirty(j)) {
        HSD_JObjSetMtxDirtySub(j);
    }
}

static inline void KP_SetTranslate(KPJObj *j, float x, float y, float z) {
    if (!j) {
        __assert(lbl_806D76D0, 0x3a9, lbl_806D76D8);
    }
    j->translate.x = x;
    j->translate.y = y;
    j->translate.z = z;
    if (!(j->flags & 0x2000000)) {
        KP_SetMtxDirty(j);
    }
}



}

/* --- asm function bodies (.text order = fn address order) --- */
void *operator new(unsigned long size);
void operator delete(void *p);

struct KPNormal3D {
    unsigned char opaque[0x5C];
    KPNormal3D(const void *name, unsigned char flags);
};

struct KPBase {
    void *vptr;
    KPBase() { vptr = clCSModelInterface_vtable_8048EAE8; }
    ~KPBase();
};

struct KPCtor : KPBase {
    KPNormal3D *kart;
    KPNormal3D *obj8;
    KPNormal3D *driver;
    KPNormal3D *obj10;
    KPNormal3D *anims14[4];
    KPNormal3D *obj24;
    KPJObj *jobj28;
    KPJObj *jobj2C;
    KPJObj *jobj30;
    KPJObj *jobj34;
    KPJObj *jobj38;
    KPJObj *jobj3C;
    KPJObj *jobj40;
    KPJObj *jobj44;
    int chara;
    int anim_state;
    float frame;
    float end_frame;
    unsigned char pad58[0x88 - 0x58];
    float view_x;
    float view_y;
    KPCtor(int chara, unsigned char flag);
};

#pragma push
#pragma use_lmw_stmw on
KPCtor::KPCtor(int ch, unsigned char flag) {
    char buf[0x28];
    CharacterData *cd;
    KPModelName *km;
    KPJObj *src;
    int i;

    vptr = KartPreview_data_8048EAD8;
    fn_8013BD7C();
    fn_8013C428();
    view_x = lbl_806D76E0;
    view_y = lbl_806D76E0;
    chara = ch;
    anim_state = 0;
    frame = lbl_806D76E0;
    end_frame = lbl_806D76E8;
    kart = 0;
    obj8 = 0;
    driver = 0;
    obj10 = 0;
    anims14[0] = 0;
    anims14[1] = 0;
    anims14[2] = 0;
    anims14[3] = 0;
    obj24 = 0;
    jobj28 = 0;
    if (chara < 0 || chara >= 13) {
        return;
    }
    {
        km = GetKartModelNameEntry(chara, -1);
        cd = GetCharacterDataEntry(chara);
        kart = new KPNormal3D(km->name, flag);
        driver = new KPNormal3D(cd->driver_model, flag);
        obj10 = new KPNormal3D(cd->kart_model, 0);
        clNormal3D_SetScale(driver, lbl_806D76E0, 0, lbl_806D76E4, lbl_806D76E0, lbl_806D76E0);
        switch (chara) {
        case 3:
            jobj28 = ResolveJointByName(driver, sKPWingJoint);
            obj24 = new KPNormal3D(sKPWingModel, flag);
            clNormal3D_SetScale(obj24, lbl_806D76E0, 0, lbl_806D76E4, lbl_806D76E0, lbl_806D76EC);
            break;
        }
        sprintf(buf, sKPFmtHead, KartPreview_data_8048EA98[chara]);
        jobj3C = ResolveJointByName(driver, buf);
        sprintf(buf, sKPFmtHandL, KartPreview_data_8048EA98[chara]);
        jobj40 = ResolveJointByName(driver, buf);
        sprintf(buf, sKPFmtHandR, KartPreview_data_8048EA98[chara]);
        jobj44 = ResolveJointByName(driver, buf);
        HSD_JObjSetFlags((HSD_JObj *)jobj40, 0x10);
        HSD_JObjSetFlags((HSD_JObj *)jobj44, 0x10);
        obj8 = new KPNormal3D(sKPKartModel, flag);
        jobj2C = ResolveJointByName(obj8, sKPKartJoint0);
        jobj30 = ResolveJointByName(obj8, sKPKartJoint1);
        jobj34 = ResolveJointByName(obj8, sKPKartJoint2);
        jobj38 = ResolveJointByName(obj8, sKPKartJoint3);

        {
            float x;
            float y;
            float z;
            sprintf(buf, sKPFmtDriver0, KartPreview_data_8048EA98[chara]);
            src = ResolveJointByName(kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate((jobj2C), x, y, z);
        }
        {
            float x;
            float y;
            float z;
            sprintf(buf, sKPFmtDriver1, KartPreview_data_8048EA98[chara]);
            src = ResolveJointByName(kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate((jobj30), x, y, z);
        }
        {
            float x;
            float y;
            float z;
            sprintf(buf, sKPFmtDriver2, KartPreview_data_8048EA98[chara]);
            src = ResolveJointByName(kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate((jobj34), x, y, z);
        }
        {
            float x;
            float y;
            float z;
            sprintf(buf, sKPFmtDriver3, KartPreview_data_8048EA98[chara]);
            src = ResolveJointByName(kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate((jobj38), x, y, z);
        }

        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden0), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden1), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden2), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden3), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden4), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden5), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden6), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden7), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden8), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden9), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden10), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden11), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden12), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden13), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden14), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden15), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden16), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden17), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden18), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(obj8, sKPHidden19), 0x10);

        for (i = 0; i < 4; i++) {
            anims14[i] = new KPNormal3D(((KPCharData *)cd)->anims[KartPreview_rodata_803600E0[i]], 0);
        }
        clNormal3D_SetScale(obj10, lbl_806D76EC, anims14[0], lbl_806D76E0, lbl_806D76E0, lbl_806D76E0);
        ObjectTree_BlendOrCopy_Timed(driver, Archive_GetRootJObj(obj10), Archive_GetRootJObj(driver), 0, lbl_806D76E0);
        if (flag) {
            clNormal3D_SetFlags(kart, 0x40000000, 0);
            clNormal3D_SetFlags(driver, 0x40000000, 0);
        }
    }
    return;
}
#pragma pop

