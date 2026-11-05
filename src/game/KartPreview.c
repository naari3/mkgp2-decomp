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

extern unsigned int lbl_806D1558;
extern RenderTargetHolder *lbl_806D155C;
extern char lbl_8048EA78[];
extern char lbl_806D76D0[7];
extern char lbl_806D76D8[5];
extern float lbl_806D76E0;
extern float lbl_806D76E4;
extern char lbl_8048EAD8[];
extern char lbl_8048EAE8[];

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
        p->vtbl = lbl_8048EAD8;
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
            p->vtbl = lbl_8048EAE8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(p);
        }
    }
    return p;
}

extern void GetKartModelNameEntry();
extern void ResolveJointByName();
extern void clNormal3D_Construct();
extern void clNormal3D_SetFlags();
extern void fn_8013BD7C();
extern void sprintf();
extern void HSD_JObjSetFlagsAll();
extern void HSD_JObjSetMtxDirtySub();
extern unsigned int lbl_806D76E8;
extern unsigned int lbl_806D76EC;
extern unsigned int lbl_803600E0[];
extern unsigned int lbl_8048EA98[];
extern void dtor_8013DCBC();
asm void fn_8013CC24(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; unsigned int f31; void *f32; unsigned int f33; void *f34; unsigned int f35; unsigned int f36; void *f37; unsigned int f38; void *f39; unsigned int f40; unsigned int f41; void *f42; unsigned int f43; void *f44; unsigned int f45; unsigned int f46; void *f47; unsigned int f48; void *f49; unsigned int f50; unsigned int f51; void *f52; unsigned int f53; void *f54; unsigned int f55; unsigned int f56; void *f57; } extab_fn_8013CC24 = { 0x38CA0000, 0x00000058, 0x00240078, 0x000000FC, 0x00000070, 0x00000108, 0x00000078, 0x0000011C, 0x00000084, 0x00000128, 0x00000078, 0x0000013C, 0x00000098, 0x0000015C, 0x000A0078, 0x00000198, 0x000000AC, 0x000001B8, 0x002F0078, 0x00000288, 0x000000C0, 0x00000298, 0x01460078, 0x000007D0, 0x000000D4, 0x00000808, 0x00150078, 0x00000000, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001C, 0x00000000, (void *)&dtor_8013DCBC };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013CC24 = {
    (void *)&fn_8013CC24, 0x0000088C, (void *)&extab_fn_8013CC24
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013CC24(void) { /* 0x8013CC24 size:0x88C */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stfd f30, 0x60(r1)
    psq_st f30, 0x68(r1), 0, 0
    stfd f29, 0x50(r1)
    psq_st f29, 0x58(r1), 0, 0
    stmw r25, 0x34(r1)
    lis r7, lbl_8048EAE8@ha
    lis r6, lbl_8048EAD8@ha
    mr r28, r3
    lis r8, lbl_803600E0@ha
    addi r3, r7, lbl_8048EAE8@l
    addi r0, r6, lbl_8048EAD8@l
    stw r3, 0x0(r28)
    mr r26, r4
    mr r29, r5
    addi r30, r8, lbl_803600E0@l
    stw r0, 0x0(r28)
    bl fn_8013BD7C
    bl fn_8013C428
    lfs f1, lbl_806D76E0(r2)
    li r0, 0x0
    lfs f0, lbl_806D76E8(r2)
    mr r3, r28
    stfs f1, 0x88(r28)
    stfs f1, 0x8c(r28)
    stw r26, 0x48(r28)
    stw r0, 0x4c(r28)
    stfs f1, 0x50(r28)
    stfs f0, 0x54(r28)
    stw r0, 0x4(r28)
    stw r0, 0x8(r28)
    stw r0, 0xc(r28)
    stw r0, 0x10(r28)
    stw r0, 0x14(r28)
    stw r0, 0x18(r28)
    stw r0, 0x1c(r28)
    stw r0, 0x20(r28)
    stw r0, 0x24(r28)
    stw r0, 0x28(r28)
    lwz r0, 0x48(r28)
    cmpwi r0, 0x0
    blt fn_8013CC24_L_8013D484
    cmpwi r0, 0xd
    blt fn_8013CC24_L_8013CCE8
    b fn_8013CC24_L_8013D484
    fn_8013CC24_L_8013CCE8:
    mr r3, r0
    li r4, -0x1
    bl GetKartModelNameEntry
    mr r27, r3
    lwz r3, 0x48(r28)
    bl GetCharacterDataEntry
    mr r31, r3
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8013CC24_L_8013CD20
    lwz r4, 0x0(r27)
    mr r5, r29
    bl clNormal3D_Construct
    fn_8013CC24_L_8013CD20:
    stw r26, 0x4(r28)
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8013CC24_L_8013CD40
    lwz r4, 0x4(r31)
    mr r5, r29
    bl clNormal3D_Construct
    fn_8013CC24_L_8013CD40:
    stw r26, 0xc(r28)
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8013CC24_L_8013CD60
    lwz r4, 0x8(r31)
    li r5, 0x0
    bl clNormal3D_Construct
    fn_8013CC24_L_8013CD60:
    lfs f1, lbl_806D76E0(r2)
    li r4, 0x0
    stw r26, 0x10(r28)
    fmr f3, f1
    lfs f2, lbl_806D76E4(r2)
    fmr f4, f1
    lwz r3, 0xc(r28)
    bl clNormal3D_SetScale
    lwz r0, 0x48(r28)
    cmpwi r0, 0x3
    beq fn_8013CC24_L_8013CD90
    b fn_8013CC24_L_8013CDDC
    fn_8013CC24_L_8013CD90:
    lwz r3, 0xc(r28)
    addi r4, r30, 0x40
    bl ResolveJointByName
    stw r3, 0x28(r28)
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8013CC24_L_8013CDBC
    mr r5, r29
    addi r4, r30, 0x5c
    bl clNormal3D_Construct
    fn_8013CC24_L_8013CDBC:
    lfs f1, lbl_806D76E0(r2)
    li r4, 0x0
    stw r26, 0x24(r28)
    fmr f3, f1
    lfs f2, lbl_806D76E4(r2)
    lwz r3, 0x24(r28)
    lfs f4, lbl_806D76EC(r2)
    bl clNormal3D_SetScale
    fn_8013CC24_L_8013CDDC:
    lwz r0, 0x48(r28)
    lis r3, lbl_8048EA98@ha
    addi r5, r3, lbl_8048EA98@l
    addi r3, r1, 0x8
    slwi r0, r0, 2
    addi r4, r30, 0x68
    lwzx r5, r5, r0
    crxor 6, 6, 6
    bl sprintf
    lwz r3, 0xc(r28)
    addi r4, r1, 0x8
    bl ResolveJointByName
    stw r3, 0x3c(r28)
    lis r3, lbl_8048EA98@ha
    addi r5, r3, lbl_8048EA98@l
    addi r3, r1, 0x8
    lwz r0, 0x48(r28)
    addi r4, r30, 0x80
    slwi r0, r0, 2
    lwzx r5, r5, r0
    crxor 6, 6, 6
    bl sprintf
    lwz r3, 0xc(r28)
    addi r4, r1, 0x8
    bl ResolveJointByName
    stw r3, 0x40(r28)
    lis r3, lbl_8048EA98@ha
    addi r5, r3, lbl_8048EA98@l
    addi r3, r1, 0x8
    lwz r0, 0x48(r28)
    addi r4, r30, 0x98
    slwi r0, r0, 2
    lwzx r5, r5, r0
    crxor 6, 6, 6
    bl sprintf
    lwz r3, 0xc(r28)
    addi r4, r1, 0x8
    bl ResolveJointByName
    stw r3, 0x44(r28)
    li r4, 0x10
    lwz r3, 0x40(r28)
    bl HSD_JObjSetFlags
    lwz r3, 0x44(r28)
    li r4, 0x10
    bl HSD_JObjSetFlags
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq fn_8013CC24_L_8013CEAC
    mr r5, r29
    addi r4, r30, 0xb0
    bl clNormal3D_Construct
    fn_8013CC24_L_8013CEAC:
    stw r26, 0x8(r28)
    addi r4, r30, 0xc0
    lwz r3, 0x8(r28)
    bl ResolveJointByName
    stw r3, 0x2c(r28)
    addi r4, r30, 0xd8
    lwz r3, 0x8(r28)
    bl ResolveJointByName
    stw r3, 0x30(r28)
    addi r4, r30, 0xf0
    lwz r3, 0x8(r28)
    bl ResolveJointByName
    stw r3, 0x34(r28)
    addi r4, r30, 0x108
    lwz r3, 0x8(r28)
    bl ResolveJointByName
    stw r3, 0x38(r28)
    lis r3, lbl_8048EA98@ha
    addi r5, r3, lbl_8048EA98@l
    addi r3, r1, 0x8
    lwz r0, 0x48(r28)
    addi r4, r30, 0x120
    slwi r0, r0, 2
    lwzx r5, r5, r0
    crxor 6, 6, 6
    bl sprintf
    lwz r3, 0x4(r28)
    addi r4, r1, 0x8
    bl ResolveJointByName
    mr. r27, r3
    bne fn_8013CC24_L_8013CF38
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3e4
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013CF38:
    lwz r26, 0x2c(r28)
    lfs f31, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f29, 0x40(r27)
    bne fn_8013CC24_L_8013CF60
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3a9
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013CF60:
    stfs f31, 0x38(r26)
    stfs f30, 0x3c(r26)
    stfs f29, 0x40(r26)
    lwz r0, 0x14(r26)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_8013CC24_L_8013CFC0
    cmplwi r26, 0x0
    beq fn_8013CC24_L_8013CFC0
    bne fn_8013CC24_L_8013CF94
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x25d
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013CF94:
    lwz r4, 0x14(r26)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8013CC24_L_8013CFB0
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8013CC24_L_8013CFB0
    li r3, 0x1
    fn_8013CC24_L_8013CFB0:
    clrlwi. r0, r3, 24
    bne fn_8013CC24_L_8013CFC0
    mr r3, r26
    bl HSD_JObjSetMtxDirtySub
    fn_8013CC24_L_8013CFC0:
    lwz r0, 0x48(r28)
    lis r3, lbl_8048EA98@ha
    addi r5, r3, lbl_8048EA98@l
    addi r3, r1, 0x8
    slwi r0, r0, 2
    addi r4, r30, 0x138
    lwzx r5, r5, r0
    crxor 6, 6, 6
    bl sprintf
    lwz r3, 0x4(r28)
    addi r4, r1, 0x8
    bl ResolveJointByName
    mr. r27, r3
    bne fn_8013CC24_L_8013D008
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3e4
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D008:
    lwz r26, 0x30(r28)
    lfs f29, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f31, 0x40(r27)
    bne fn_8013CC24_L_8013D030
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3a9
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D030:
    stfs f29, 0x38(r26)
    stfs f30, 0x3c(r26)
    stfs f31, 0x40(r26)
    lwz r0, 0x14(r26)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_8013CC24_L_8013D090
    cmplwi r26, 0x0
    beq fn_8013CC24_L_8013D090
    bne fn_8013CC24_L_8013D064
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x25d
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D064:
    lwz r4, 0x14(r26)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8013CC24_L_8013D080
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8013CC24_L_8013D080
    li r3, 0x1
    fn_8013CC24_L_8013D080:
    clrlwi. r0, r3, 24
    bne fn_8013CC24_L_8013D090
    mr r3, r26
    bl HSD_JObjSetMtxDirtySub
    fn_8013CC24_L_8013D090:
    lwz r0, 0x48(r28)
    lis r3, lbl_8048EA98@ha
    addi r5, r3, lbl_8048EA98@l
    addi r3, r1, 0x8
    slwi r0, r0, 2
    addi r4, r30, 0x150
    lwzx r5, r5, r0
    crxor 6, 6, 6
    bl sprintf
    lwz r3, 0x4(r28)
    addi r4, r1, 0x8
    bl ResolveJointByName
    mr. r27, r3
    bne fn_8013CC24_L_8013D0D8
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3e4
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D0D8:
    lwz r26, 0x34(r28)
    lfs f29, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f31, 0x40(r27)
    bne fn_8013CC24_L_8013D100
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3a9
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D100:
    stfs f29, 0x38(r26)
    stfs f30, 0x3c(r26)
    stfs f31, 0x40(r26)
    lwz r0, 0x14(r26)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_8013CC24_L_8013D160
    cmplwi r26, 0x0
    beq fn_8013CC24_L_8013D160
    bne fn_8013CC24_L_8013D134
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x25d
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D134:
    lwz r4, 0x14(r26)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8013CC24_L_8013D150
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8013CC24_L_8013D150
    li r3, 0x1
    fn_8013CC24_L_8013D150:
    clrlwi. r0, r3, 24
    bne fn_8013CC24_L_8013D160
    mr r3, r26
    bl HSD_JObjSetMtxDirtySub
    fn_8013CC24_L_8013D160:
    lwz r0, 0x48(r28)
    lis r3, lbl_8048EA98@ha
    addi r5, r3, lbl_8048EA98@l
    addi r3, r1, 0x8
    slwi r0, r0, 2
    addi r4, r30, 0x168
    lwzx r5, r5, r0
    crxor 6, 6, 6
    bl sprintf
    lwz r3, 0x4(r28)
    addi r4, r1, 0x8
    bl ResolveJointByName
    mr. r27, r3
    bne fn_8013CC24_L_8013D1A8
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3e4
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D1A8:
    lwz r26, 0x38(r28)
    lfs f29, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f31, 0x40(r27)
    bne fn_8013CC24_L_8013D1D0
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x3a9
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D1D0:
    stfs f29, 0x38(r26)
    stfs f30, 0x3c(r26)
    stfs f31, 0x40(r26)
    lwz r0, 0x14(r26)
    rlwinm. r0, r0, 0, 6, 6
    bne fn_8013CC24_L_8013D230
    cmplwi r26, 0x0
    beq fn_8013CC24_L_8013D230
    bne fn_8013CC24_L_8013D204
    la r3, lbl_806D76D0(r2)  /* lbl_806D76D0 */
    li r4, 0x25d
    la r5, lbl_806D76D8(r2)  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D204:
    lwz r4, 0x14(r26)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8013CC24_L_8013D220
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8013CC24_L_8013D220
    li r3, 0x1
    fn_8013CC24_L_8013D220:
    clrlwi. r0, r3, 24
    bne fn_8013CC24_L_8013D230
    mr r3, r26
    bl HSD_JObjSetMtxDirtySub
    fn_8013CC24_L_8013D230:
    lwz r3, 0x8(r28)
    addi r4, r30, 0x180
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x198
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1b0
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1c8
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1e0
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1f8
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x210
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x228
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x240
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x258
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x270
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x288
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2a0
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2b8
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2d0
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2e8
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x300
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x318
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x330
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    lwz r3, 0x8(r28)
    addi r4, r30, 0x348
    bl ResolveJointByName
    li r4, 0x10
    bl HSD_JObjSetFlagsAll
    addi r26, r30, 0x0
    li r30, 0x0
    li r27, 0x0
    fn_8013CC24_L_8013D3CC:
    li r3, 0x5c
    bl Alloc
    mr. r25, r3
    beq fn_8013CC24_L_8013D3F4
    lwz r0, 0x0(r26)
    li r5, 0x0
    lwz r4, 0x18(r31)
    slwi r0, r0, 2
    lwzx r4, r4, r0
    bl clNormal3D_Construct
    fn_8013CC24_L_8013D3F4:
    addi r30, r30, 0x1
    addi r0, r27, 0x14
    cmpwi r30, 0x4
    stwx r25, r28, r0
    addi r26, r26, 0x4
    addi r27, r27, 0x4
    blt fn_8013CC24_L_8013D3CC
    lfs f2, lbl_806D76E0(r2)
    lwz r3, 0x10(r28)
    fmr f3, f2
    lfs f1, lbl_806D76EC(r2)
    fmr f4, f2
    lwz r4, 0x14(r28)
    bl clNormal3D_SetScale
    lwz r3, 0xc(r28)
    bl Archive_GetRootJObj
    mr r30, r3
    lwz r3, 0x10(r28)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0xc(r28)
    lfs f1, lbl_806D76E0(r2)
    mr r5, r30
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    clrlwi. r0, r29, 24
    beq fn_8013CC24_L_8013D480
    lwz r3, 0x4(r28)
    lis r4, 0x4000
    li r5, 0x0
    bl clNormal3D_SetFlags
    lwz r3, 0xc(r28)
    lis r4, 0x4000
    li r5, 0x0
    bl clNormal3D_SetFlags
    fn_8013CC24_L_8013D480:
    mr r3, r28
    fn_8013CC24_L_8013D484:
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    lmw r25, 0x34(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

