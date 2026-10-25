/*
 * Kart/driver preview model shown on the select screens
 * (0x8013C4A4..0x8013D4B0): model wrapper setters, render, anim, dtor
 * and ctor. The render target singleton lives in RenderTargetSingleton.c.
 *
 * The model setters and the render function test `kart` then `driver` with a
 * `bne; b` branch-over-branch on the second test that no C form tried here
 * reproduces, so they stay asm for now (as does the large ctor).
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
extern char lbl_806D76D0[];
extern char lbl_806D76D8[];
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
extern void fn_802D0B48(HSD_JObj *jobj, int flags);
extern void fn_802D07D4(HSD_JObj *jobj, int flags);
extern void Object_DtorWithGXSync(void *obj, int flag);

extern void fn_8013C334(RenderTargetHolder *h);
extern int fn_8013C34C(RenderTargetHolder *h);
extern RenderTargetHolder *fn_8013C3B8(void);
extern void fn_8013C3C0(void);
extern int fn_8013C428(void);

asm void fn_8013C4A4(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013C4A4[8] = {
    0x08, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013C4A4 = {
    (void *)&fn_8013C4A4, 0x00000090, (void *)extab_fn_8013C4A4
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013C4A4(void) { /* 0x8013C4A4 size:0x90 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x18(r1)
    fmr f31, f1
    stw r31, 0x14(r1)
    mr r31, r3
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq fn_8013C4A4_L_8013C51C
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_8013C4A4_L_8013C4DC
    b fn_8013C4A4_L_8013C51C
    fn_8013C4A4_L_8013C4DC:
    li r4, 0x0
    bl Object_SetColorAlphaOnly
    fmr f1, f31
    lwz r3, 0x8(r31)
    li r4, 0x0
    bl Object_SetColorAlphaOnly
    fmr f1, f31
    lwz r3, 0xc(r31)
    li r4, 0x0
    bl Object_SetColorAlphaOnly
    lwz r3, 0x24(r31)
    cmplwi r3, 0x0
    beq fn_8013C4A4_L_8013C51C
    fmr f1, f31
    li r4, 0x0
    bl Object_SetColorAlphaOnly
    fn_8013C4A4_L_8013C51C:
    lwz r0, 0x24(r1)
    lfd f31, 0x18(r1)
    lwz r31, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


extern void _restfpr_28();
extern void _savefpr_28();
asm void fn_8013C534(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013C534[8] = {
    0x09, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013C534 = {
    (void *)&fn_8013C534, 0x000000C8, (void *)extab_fn_8013C534
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013C534(void) { /* 0x8013C534 size:0xC8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    addi r11, r1, 0x30
    bl _savefpr_28
    stw r31, 0xc(r1)
    mr r31, r3
    fmr f28, f1
    lwz r3, 0x4(r3)
    fmr f29, f2
    fmr f30, f3
    fmr f31, f4
    cmplwi r3, 0x0
    beq fn_8013C534_L_8013C5E0
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_8013C534_L_8013C57C
    b fn_8013C534_L_8013C5E0
    fn_8013C534_L_8013C57C:
    li r4, 0x0
    bl Object_SetColorRGBA
    fmr f1, f28
    lwz r3, 0x8(r31)
    fmr f2, f29
    li r4, 0x0
    fmr f3, f30
    fmr f4, f31
    bl Object_SetColorRGBA
    fmr f1, f28
    lwz r3, 0xc(r31)
    fmr f2, f29
    li r4, 0x0
    fmr f3, f30
    fmr f4, f31
    bl Object_SetColorRGBA
    lwz r3, 0x24(r31)
    cmplwi r3, 0x0
    beq fn_8013C534_L_8013C5E0
    fmr f1, f28
    li r4, 0x0
    fmr f2, f29
    fmr f3, f30
    fmr f4, f31
    bl Object_SetColorRGBA
    fn_8013C534_L_8013C5E0:
    addi r11, r1, 0x30
    bl _restfpr_28
    lwz r0, 0x34(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


asm void fn_8013C5FC(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013C5FC[8] = {
    0x08, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013C5FC = {
    (void *)&fn_8013C5FC, 0x00000078, (void *)extab_fn_8013C5FC
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013C5FC(void) { /* 0x8013C5FC size:0x78 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x18(r1)
    fmr f31, f1
    stw r31, 0x14(r1)
    mr r31, r3
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq fn_8013C5FC_L_8013C65C
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_8013C5FC_L_8013C634
    b fn_8013C5FC_L_8013C65C
    fn_8013C5FC_L_8013C634:
    bl Object_SetJObjRotationY
    fmr f1, f31
    lwz r3, 0x8(r31)
    bl Object_SetJObjRotationY
    fmr f1, f31
    lwz r3, 0xc(r31)
    bl Object_SetJObjRotationY
    fmr f1, f31
    lwz r3, 0x10(r31)
    bl Object_SetJObjRotationY
    fn_8013C5FC_L_8013C65C:
    lwz r0, 0x24(r1)
    lfd f31, 0x18(r1)
    lwz r31, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


asm void fn_8013C674(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013C674[8] = {
    0x08, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013C674 = {
    (void *)&fn_8013C674, 0x00000078, (void *)extab_fn_8013C674
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013C674(void) { /* 0x8013C674 size:0x78 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x18(r1)
    fmr f31, f1
    stw r31, 0x14(r1)
    mr r31, r3
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq fn_8013C674_L_8013C6D4
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_8013C674_L_8013C6AC
    b fn_8013C674_L_8013C6D4
    fn_8013C674_L_8013C6AC:
    bl Object_SetJObjRotationX
    fmr f1, f31
    lwz r3, 0x8(r31)
    bl Object_SetJObjRotationX
    fmr f1, f31
    lwz r3, 0xc(r31)
    bl Object_SetJObjRotationX
    fmr f1, f31
    lwz r3, 0x10(r31)
    bl Object_SetJObjRotationX
    fn_8013C674_L_8013C6D4:
    lwz r0, 0x24(r1)
    lfd f31, 0x18(r1)
    lwz r31, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


asm void fn_8013C6EC(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013C6EC[8] = {
    0x08, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013C6EC = {
    (void *)&fn_8013C6EC, 0x000000C4, (void *)extab_fn_8013C6EC
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013C6EC(void) { /* 0x8013C6EC size:0xC4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x28(r1)
    fmr f31, f3
    stfd f30, 0x20(r1)
    fmr f30, f2
    stfd f29, 0x18(r1)
    fmr f29, f1
    stw r31, 0x14(r1)
    mr r31, r3
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq fn_8013C6EC_L_8013C790
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne fn_8013C6EC_L_8013C734
    b fn_8013C6EC_L_8013C790
    fn_8013C6EC_L_8013C734:
    bl Object_SetJObjScaleXYZ
    fmr f1, f29
    lwz r3, 0x8(r31)
    fmr f2, f30
    fmr f3, f31
    bl Object_SetJObjScaleXYZ
    fmr f1, f29
    lwz r3, 0xc(r31)
    fmr f2, f30
    fmr f3, f31
    bl Object_SetJObjScaleXYZ
    fmr f1, f29
    lwz r3, 0x10(r31)
    fmr f2, f30
    fmr f3, f31
    bl Object_SetJObjScaleXYZ
    lwz r3, 0x24(r31)
    cmplwi r3, 0x0
    beq fn_8013C6EC_L_8013C790
    fmr f1, f29
    fmr f2, f30
    fmr f3, f31
    bl Object_SetJObjScaleXYZ
    fn_8013C6EC_L_8013C790:
    lwz r0, 0x34(r1)
    lfd f31, 0x28(r1)
    lfd f30, 0x20(r1)
    lfd f29, 0x18(r1)
    lwz r31, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


void fn_8013C7B0(KartPreview *p, float x, float y) {
    p->view_x = x;
    p->view_y = y;
}

asm void fn_8013C7BC(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013C7BC[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013C7BC = {
    (void *)&fn_8013C7BC, 0x00000160, (void *)extab_fn_8013C7BC
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013C7BC(void) { /* 0x8013C7BC size:0x160 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq fn_8013C7BC_L_8013C904
    lwz r0, 0xc(r30)
    cmplwi r0, 0x0
    bne fn_8013C7BC_L_8013C7F0
    b fn_8013C7BC_L_8013C904
    fn_8013C7BC_L_8013C7F0:
    bl fn_8013BC98
    cmplwi r3, 0x0
    beq fn_8013C7BC_L_8013C904
    bl fn_8013C3B8
    cmplwi r3, 0x0
    beq fn_8013C7BC_L_8013C904
    bl fn_8013BC98
    lfs f1, 0x88(r30)
    lfs f2, 0x8c(r30)
    bl fn_8013BB1C
    bl fn_8013BC98
    bl fn_8013BC38
    clrlwi. r0, r3, 24
    beq fn_8013C7BC_L_8013C904
    bl fn_8013C3B8
    bl fn_8013C34C
    bl fn_8013BC98
    bl fn_8013BBFC
    lwz r3, 0x4(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0x8(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r3, 0xc(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    lwz r0, 0x24(r30)
    cmplwi r0, 0x0
    beq fn_8013C7BC_L_8013C8F4
    lwz r31, 0x28(r30)
    cmplwi r31, 0x0
    beq fn_8013C7BC_L_8013C8F4
    bne fn_8013C7BC_L_8013C888
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x47c
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
    bl __assert
    fn_8013C7BC_L_8013C888:
    cmplwi r31, 0x0
    beq fn_8013C7BC_L_8013C8D0
    bne fn_8013C7BC_L_8013C8A4
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x25d
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
    bl __assert
    fn_8013C7BC_L_8013C8A4:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne fn_8013C7BC_L_8013C8C0
    rlwinm. r0, r4, 0, 25, 25
    beq fn_8013C7BC_L_8013C8C0
    li r3, 0x1
    fn_8013C7BC_L_8013C8C0:
    clrlwi. r0, r3, 24
    beq fn_8013C7BC_L_8013C8D0
    mr r3, r31
    bl HSD_JObjSetupMatrixSub
    fn_8013C7BC_L_8013C8D0:
    lwz r3, 0x24(r30)
    addi r4, r31, 0x44
    li r5, 0x0
    bl Object_SetAnimBinding
    lwz r3, 0x24(r30)
    bl Object_DriveAnimMatrix
    lwz r3, 0x24(r30)
    li r4, 0x7
    bl Object_RenderJObjTree
    fn_8013C7BC_L_8013C8F4:
    bl fn_8013BC98
    bl fn_8013BB9C
    bl fn_8013C3B8
    bl fn_8013C334
    fn_8013C7BC_L_8013C904:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
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
    fn_802D0B48(p->jobj3C, 0x10);
    fn_802D07D4(p->jobj40, 0x10);
    fn_802D07D4(p->jobj44, 0x10);
}

void fn_8013CA70(KartPreview *p) {
    p->anim_state = 2;
    p->frame = 0.0f;
    p->end_frame = GetCharacterDataEntry(p->chara)->anim1C;
    if (p->chara == 3) {
        fn_802D0B48(p->jobj40, 0x10);
        fn_802D07D4(p->jobj3C, 0x10);
        fn_802D07D4(p->jobj44, 0x10);
    } else {
        fn_802D0B48(p->jobj3C, 0x10);
        fn_802D07D4(p->jobj40, 0x10);
        fn_802D07D4(p->jobj44, 0x10);
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
extern void fn_802D0870();
extern void fn_802D20AC();
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
    bl fn_802D07D4
    lwz r3, 0x44(r28)
    li r4, 0x10
    bl fn_802D07D4
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3e4
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013CF38:
    lwz r26, 0x2c(r28)
    lfs f31, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f29, 0x40(r27)
    bne fn_8013CC24_L_8013CF60
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3a9
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x25d
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    bl fn_802D20AC
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3e4
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D008:
    lwz r26, 0x30(r28)
    lfs f29, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f31, 0x40(r27)
    bne fn_8013CC24_L_8013D030
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3a9
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x25d
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    bl fn_802D20AC
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3e4
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D0D8:
    lwz r26, 0x34(r28)
    lfs f29, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f31, 0x40(r27)
    bne fn_8013CC24_L_8013D100
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3a9
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x25d
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    bl fn_802D20AC
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3e4
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
    bl __assert
    fn_8013CC24_L_8013D1A8:
    lwz r26, 0x38(r28)
    lfs f29, 0x38(r27)
    cmplwi r26, 0x0
    lfs f30, 0x3c(r27)
    lfs f31, 0x40(r27)
    bne fn_8013CC24_L_8013D1D0
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x3a9
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    addi r3, r2, -0x2B90  /* lbl_806D76D0 */
    li r4, 0x25d
    addi r5, r2, -0x2B88  /* lbl_806D76D8 */
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
    bl fn_802D20AC
    fn_8013CC24_L_8013D230:
    lwz r3, 0x8(r28)
    addi r4, r30, 0x180
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x198
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1b0
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1c8
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1e0
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x1f8
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x210
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x228
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x240
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x258
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x270
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x288
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2a0
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2b8
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2d0
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x2e8
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x300
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x318
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x330
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
    lwz r3, 0x8(r28)
    addi r4, r30, 0x348
    bl ResolveJointByName
    li r4, 0x10
    bl fn_802D0870
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

