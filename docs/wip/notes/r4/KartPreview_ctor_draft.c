/*
 * Kart/driver preview model shown on the select screens
 * (0x8013C4A4..0x8013D4B0): model wrapper setters, render, anim, dtor
 * and ctor. The render target singleton lives in RenderTargetSingleton.c.
 *
 * The model setters and the render function start with
 * `if (kart == 0 || driver == 0) return;`, which is what produces the
 * `beq end; ...; bne body; b end` branch-over-branch on the second test.
 * The large ctor (fn_8013CC24) stays asm for now.
 */

typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned char pad18[0x44 - 0x18];
    unsigned char anim[1];
} HSD_JObj;

typedef struct RenderTargetHolder {
    unsigned char active;
    void *rt;
} RenderTargetHolder;

typedef struct CharacterData {
    int pad0;
    void *driver_model;
    void *kart_model;
    int pad0C[4];
    float anim1C;
    float pad20;
    float anim24;
} CharacterData;

typedef struct KartPreview {
    void *vtbl;
    void *kart;
    void *obj8;
    void *driver;
    void *obj10;
    void *anims14[4];
    void *obj24;
    HSD_JObj *jobj28;
    HSD_JObj *jobj2C;
    HSD_JObj *jobj30;
    HSD_JObj *jobj34;
    HSD_JObj *jobj38;
    HSD_JObj *jobj3C;
    HSD_JObj *jobj40;
    HSD_JObj *jobj44;
    int chara;
    int anim_state;
    float frame;
    float end_frame;
    unsigned char pad58[0x88 - 0x58];
    float view_x;
    float view_y;
} KartPreview;

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
extern void clNormal3D_SetScale(void *obj, void *anim, float frame, float a, float b, float c);
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
        clNormal3D_SetScale(p->obj10, anim, p->frame, lbl_806D76E0, lbl_806D76E0, lbl_806D76E0);
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
    int animIdx[4];
    char pad10[0x40 - 0x10];
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
extern KPJObj *ResolveJointByName(void *model, char *name);
extern void clNormal3D_Construct(void *self, char *name, int flags);
extern void clNormal3D_SetFlags(void *model, unsigned int flags, int b);
extern void fn_8013BD7C(void);
extern int sprintf(char *buf, const char *fmt, ...);
extern void HSD_JObjSetFlagsAll(void *jobj, int flags);
extern void HSD_JObjSetMtxDirtySub(KPJObj *jobj);
extern const float lbl_806D76E8;
extern const float lbl_806D76EC;
extern KPStrings KartPreview_rodata_803600E0;
extern char *KartPreview_data_8048EA98[];
extern void dtor_8013DCBC();
KartPreview *fn_8013CC24(KartPreview *p, int chara, int flag);

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



/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; unsigned int f31; void *f32; unsigned int f33; void *f34; unsigned int f35; unsigned int f36; void *f37; unsigned int f38; void *f39; unsigned int f40; unsigned int f41; void *f42; unsigned int f43; void *f44; unsigned int f45; unsigned int f46; void *f47; unsigned int f48; void *f49; unsigned int f50; unsigned int f51; void *f52; unsigned int f53; void *f54; unsigned int f55; unsigned int f56; void *f57; } extab_fn_8013CC24 = { 0x38CA0000, 0x00000058, 0x00240078, 0x000000FC, 0x00000070, 0x00000108, 0x00000078, 0x0000011C, 0x00000084, 0x00000128, 0x00000078, 0x0000013C, 0x00000098, 0x0000015C, 0x000A0078, 0x00000198, 0x000000AC, 0x000001B8, 0x002F0078, 0x00000288, 0x000000C0, 0x00000298, 0x01460078, 0x000007D0, 0x000000D4, 0x00000808, 0x00150078, 0x00000000, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013CC24 = {
    (void *)&fn_8013CC24, 0x0000088C, (void *)&extab_fn_8013CC24
};

/* --- asm function bodies (.text order = fn address order) --- */
#define KP_NEW_MODEL(dst, name, flags) \
    do { \
        void *o_ = Alloc(0x5C); \
        if (o_) { \
            clNormal3D_Construct(o_, name, flags); \
        } \
        dst = o_; \
    } while (0)

#pragma push
#pragma use_lmw_stmw on
KartPreview *fn_8013CC24(KartPreview *p, int chara, int flag) {
    char buf[0x28];
    KPStrings *str;
    CharacterData *cd;
    KPModelName *km;
    KPJObj *src;
    int i;

    str = &KartPreview_rodata_803600E0;
    p->vtbl = clCSModelInterface_vtable_8048EAE8;
    p->vtbl = KartPreview_data_8048EAD8;
    fn_8013BD7C();
    fn_8013C428();
    p->view_x = lbl_806D76E0;
    p->view_y = lbl_806D76E0;
    p->chara = chara;
    p->anim_state = 0;
    p->frame = lbl_806D76E0;
    p->end_frame = lbl_806D76E8;
    p->kart = 0;
    p->obj8 = 0;
    p->driver = 0;
    p->obj10 = 0;
    p->anims14[0] = 0;
    p->anims14[1] = 0;
    p->anims14[2] = 0;
    p->anims14[3] = 0;
    p->obj24 = 0;
    p->jobj28 = 0;
    if (p->chara < 0 || p->chara >= 13) {
        return p;
    }
    {
        km = GetKartModelNameEntry(p->chara, -1);
        cd = GetCharacterDataEntry(p->chara);
        KP_NEW_MODEL(p->kart, km->name, flag);
        KP_NEW_MODEL(p->driver, cd->driver_model, flag);
        KP_NEW_MODEL(p->obj10, cd->kart_model, 0);
        clNormal3D_SetScale(p->driver, 0, lbl_806D76E0, lbl_806D76E4, lbl_806D76E0, lbl_806D76E0);
        switch (p->chara) {
        case 3:
            p->jobj28 = (HSD_JObj *)ResolveJointByName(p->driver, str->wingJoint);
            KP_NEW_MODEL(p->obj24, str->wingModel, flag);
            clNormal3D_SetScale(p->obj24, 0, lbl_806D76E0, lbl_806D76E4, lbl_806D76E0, lbl_806D76EC);
            break;
        }
        sprintf(buf, str->fmtHead, KartPreview_data_8048EA98[p->chara]);
        p->jobj3C = (HSD_JObj *)ResolveJointByName(p->driver, buf);
        sprintf(buf, str->fmtHandL, KartPreview_data_8048EA98[p->chara]);
        p->jobj40 = (HSD_JObj *)ResolveJointByName(p->driver, buf);
        sprintf(buf, str->fmtHandR, KartPreview_data_8048EA98[p->chara]);
        p->jobj44 = (HSD_JObj *)ResolveJointByName(p->driver, buf);
        HSD_JObjSetFlags(p->jobj40, 0x10);
        HSD_JObjSetFlags(p->jobj44, 0x10);
        KP_NEW_MODEL(p->obj8, str->kartModel, flag);
        p->jobj2C = (HSD_JObj *)ResolveJointByName(p->obj8, str->kartJoint[0]);
        p->jobj30 = (HSD_JObj *)ResolveJointByName(p->obj8, str->kartJoint[1]);
        p->jobj34 = (HSD_JObj *)ResolveJointByName(p->obj8, str->kartJoint[2]);
        p->jobj38 = (HSD_JObj *)ResolveJointByName(p->obj8, str->kartJoint[3]);

        {
            float x;
            float y;
            float z;
            sprintf(buf, str->fmtDriver[0], KartPreview_data_8048EA98[p->chara]);
            src = ResolveJointByName(p->kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate(KP_JOBJ(p->jobj2C), x, y, z);
        }
        {
            float x;
            float y;
            float z;
            sprintf(buf, str->fmtDriver[1], KartPreview_data_8048EA98[p->chara]);
            src = ResolveJointByName(p->kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate(KP_JOBJ(p->jobj30), x, y, z);
        }
        {
            float x;
            float y;
            float z;
            sprintf(buf, str->fmtDriver[2], KartPreview_data_8048EA98[p->chara]);
            src = ResolveJointByName(p->kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate(KP_JOBJ(p->jobj34), x, y, z);
        }
        {
            float x;
            float y;
            float z;
            sprintf(buf, str->fmtDriver[3], KartPreview_data_8048EA98[p->chara]);
            src = ResolveJointByName(p->kart, buf);
            if (!src) {
                __assert(lbl_806D76D0, 0x3e4, lbl_806D76D8);
            }
            x = src->translate.x;
            y = src->translate.y;
            z = src->translate.z;
            KP_SetTranslate(KP_JOBJ(p->jobj38), x, y, z);
        }

        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[0]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[1]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[2]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[3]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[4]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[5]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[6]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[7]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[8]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[9]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[10]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[11]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[12]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[13]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[14]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[15]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[16]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[17]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[18]), 0x10);
        HSD_JObjSetFlagsAll(ResolveJointByName(p->obj8, str->hidden[19]), 0x10);

        for (i = 0; i < 4; i++) {
            KP_NEW_MODEL(p->anims14[i], ((KPCharData *)cd)->anims[str->animIdx[i]], 0);
        }
        clNormal3D_SetScale(p->obj10, p->anims14[0], lbl_806D76EC, lbl_806D76E0, lbl_806D76E0, lbl_806D76E0);
        ObjectTree_BlendOrCopy_Timed(p->driver, Archive_GetRootJObj(p->obj10), Archive_GetRootJObj(p->driver), 0, lbl_806D76E0);
        if ((unsigned char)flag) {
            clNormal3D_SetFlags(p->kart, 0x40000000, 0);
            clNormal3D_SetFlags(p->driver, 0x40000000, 0);
        }
    }
    return p;
}
#pragma pop

