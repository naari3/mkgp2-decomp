/*
 * clCSAnim (csAnim.cpp): keyframed sprite animation node list.
 * .text 0x8013AB74..0x8013BA90
 *
 * fn_8013BA78 (Reset) is inlined into its callers here; the weak
 * out-of-line copy CW emits is superseded by the strong definition in
 * csAnim_Reset.c, which sits at the address following this TU.
 *
 * fn_8013AE20 (fp register count) and fn_8013B87C (member dtor only on the
 * innermost inlined level) do not match from C yet; they stay as asm with
 * manual extab, ordered via tools/extab_order.json.
 */

typedef struct CSAnimKey {
    int type;
    int count;
    float x;
    float y;
    float u10;
    float u14;
    float u18;
    float r;
    float g;
    float b;
    float a;
} CSAnimKey;

typedef struct CSAnim {
    int id;
    struct CSAnim *next;
    int flags;
    int frame;
    int index;
    CSAnimKey *keys;
    /* 0x18: ResCtrl-like sprite resource */
    int res;
    int pad1C;
    int res20;
    int pad24;
    unsigned char visible;
    float x;
    float y;
    float z;
    int pad38;
    int pad3C;
    float u40;
    float u44;
    float u48;
    unsigned int color[4];
    int pad5C;
    int u60;
    int u64;
    int u68;
} CSAnim;

extern const int lbl_806D7480;
extern const int lbl_806D7498;
extern char lbl_8035C678[];
extern char lbl_8035C684[];
extern const int lbl_806D7484;
extern const int lbl_806D7488;
extern const int lbl_806D7490;

extern void fn_8011FAFC(void *res, void *arg);
extern void OSPanic(const char *file, int line, const char *msg, ...);
extern void ResCtrl_Init(void *res);
extern void dtor_80082960();
extern void MemoryManager_TimedFree();

asm void fn_8013B87C(void);
asm void fn_8013AE20(void);

inline void fn_8013BA78(CSAnim *n) {
    n->flags = 2;
    n->frame = 0;
    n->index = 0;
}

void fn_8013AB74(CSAnim *n, void *arg, int id) {
    if ((id < 0 || n->id == id) && n->keys && (n->flags & 4)) {
        fn_8011FAFC(&n->res, arg);
    }
    if (n->next) {
        fn_8013AB74(n->next, arg, id);
    }
}

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013AE20[8] = {
    0x31, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013AE20 = {
    (void *)&fn_8013AE20, 0x000004E0, (void *)extab_fn_8013AE20
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013AE20(void) { /* 0x8013AE20 size:0x4E0 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stfd f29, 0x90(r1)
    psq_st f29, 0x98(r1), 0, 0
    stfd f28, 0x80(r1)
    psq_st f28, 0x88(r1), 0, 0
    stfd f27, 0x70(r1)
    psq_st f27, 0x78(r1), 0, 0
    stfd f26, 0x60(r1)
    psq_st f26, 0x68(r1), 0, 0
    stfd f25, 0x50(r1)
    psq_st f25, 0x58(r1), 0, 0
    stmw r26, 0x38(r1)
    mr r30, r3
    fmr f29, f1
    lwz r3, 0x4(r3)
    fmr f30, f2
    fmr f31, f3
    cmplwi r3, 0x0
    beq fn_8013AE20_L_8013AE88
    bl fn_8013AE20
    fn_8013AE20_L_8013AE88:
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq fn_8013AE20_L_8013B2B4
    lwz r0, 0x8(r30)
    clrlwi. r0, r0, 31
    beq fn_8013AE20_L_8013B2B4
    lwz r0, 0x10(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    fn_8013AE20_L_8013AEAC:
    lwz r0, 0x0(r31)
    cmpwi r0, 0x0
    bne fn_8013AE20_L_8013AEE0
    lwz r3, 0x10(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x10(r30)
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013AEE0:
    cmpwi r0, 0x1
    bne fn_8013AE20_L_8013AF54
    lwz r3, 0xc(r30)
    lwz r0, 0x4(r31)
    cmpw r3, r0
    bge fn_8013AE20_L_8013AF2C
    lwz r0, 0x8(r30)
    rlwinm r0, r0, 0, 30, 28
    stw r0, 0x8(r30)
    lwz r3, 0x8(r30)
    rlwinm. r0, r3, 0, 30, 30
    beq fn_8013AE20_L_8013AF1C
    rlwinm r0, r3, 0, 31, 29
    stw r0, 0x8(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013AF1C:
    lwz r3, 0xc(r30)
    addi r0, r3, 0x1
    stw r0, 0xc(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013AF2C:
    lwz r3, 0x10(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x10(r30)
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013AF54:
    cmpwi r0, 0x2
    bne fn_8013AE20_L_8013AFB8
    lwz r4, 0xc(r30)
    lwz r0, 0x4(r31)
    cmpw r4, r0
    bge fn_8013AE20_L_8013AF90
    lwz r3, 0x8(r30)
    rlwinm. r0, r3, 0, 30, 30
    beq fn_8013AE20_L_8013AF84
    rlwinm r0, r3, 0, 31, 29
    stw r0, 0x8(r30)
    b fn_8013AE20_L_8013B130
    fn_8013AE20_L_8013AF84:
    addi r0, r4, 0x1
    stw r0, 0xc(r30)
    b fn_8013AE20_L_8013B130
    fn_8013AE20_L_8013AF90:
    lwz r3, 0x10(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x10(r30)
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013AFB8:
    cmpwi r0, 0x3
    bne fn_8013AE20_L_8013B04C
    lis r4, lbl_8035C678@ha
    lis r3, lbl_8035C684@ha
    addi r28, r4, lbl_8035C678@l
    li r26, 0x0
    addi r29, r3, lbl_8035C684@l
    li r27, 0x0
    fn_8013AE20_L_8013AFD8:
    lwz r3, 0x14(r30)
    lwzx r0, r3, r27
    cmpwi r0, 0x5
    bne fn_8013AE20_L_8013AFFC
    mr r3, r28
    mr r5, r29
    li r4, 0x86
    crxor 6, 6, 6
    bl OSPanic
    fn_8013AE20_L_8013AFFC:
    lwz r0, 0x14(r30)
    add r4, r0, r27
    lwz r0, 0x0(r4)
    cmpwi r0, 0x0
    bne fn_8013AE20_L_8013B040
    lwz r3, 0x4(r31)
    lwz r0, 0x4(r4)
    cmpw r3, r0
    bne fn_8013AE20_L_8013B040
    stw r26, 0x10(r30)
    li r0, 0x0
    stw r0, 0xc(r30)
    lwz r0, 0x10(r30)
    lwz r3, 0x14(r30)
    mulli r0, r0, 0x2c
    add r31, r3, r0
    b fn_8013AE20_L_8013AEAC
    fn_8013AE20_L_8013B040:
    addi r27, r27, 0x2c
    addi r26, r26, 0x1
    b fn_8013AE20_L_8013AFD8
    fn_8013AE20_L_8013B04C:
    cmpwi r0, 0x4
    bne fn_8013AE20_L_8013B118
    lwz r4, 0x8(r30)
    li r0, 0x1
    lwz r3, lbl_806D7480(r2)
    lfs f0, lbl_806D7484(r2)
    or r3, r4, r3
    lfs f4, lbl_806D7488(r2)
    stw r3, 0x8(r30)
    lfs f1, 0x8(r31)
    lfs f2, 0xc(r31)
    fadds f1, f1, f29
    stb r0, 0x28(r30)
    fadds f2, f2, f30
    stfs f1, 0x2c(r30)
    stfs f2, 0x30(r30)
    stfs f0, 0x34(r30)
    lfs f1, 0x14(r31)
    lfs f0, 0x10(r31)
    stfs f0, 0x44(r30)
    stfs f1, 0x48(r30)
    lfs f0, 0x20(r31)
    lfs f2, 0x28(r31)
    lfs f1, 0x1c(r31)
    fmuls f0, f4, f0
    fmuls f3, f4, f2
    lfs f2, 0x24(r31)
    fmuls f1, f4, f1
    fctiwz f0, f0
    fmuls f2, f4, f2
    fctiwz f1, f1
    stfd f0, 0x20(r1)
    fmuls f3, f3, f31
    fctiwz f2, f2
    lwz r0, 0x24(r1)
    fctiwz f0, f3
    stfd f1, 0x18(r1)
    clrlslwi r3, r0, 24, 16
    lwz r0, 0x1c(r1)
    stfd f2, 0x10(r1)
    rlwimi r3, r0, 24, 0, 7
    lwz r0, 0x14(r1)
    stfd f0, 0x8(r1)
    rlwimi r3, r0, 8, 16, 23
    lwz r0, 0xc(r1)
    rlwimi r3, r0, 0, 24, 31
    stw r3, 0x4c(r30)
    stw r3, 0x50(r30)
    stw r3, 0x54(r30)
    stw r3, 0x58(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013B118:
    li r3, 0x2
    li r0, 0x0
    stw r3, 0x8(r30)
    stw r0, 0xc(r30)
    stw r0, 0x10(r30)
    b fn_8013AE20_L_8013B2B4
    fn_8013AE20_L_8013B130:
    lwz r5, 0x8(r30)
    lis r4, 0x4330
    lwz r3, lbl_806D7480(r2)
    li r0, 0x1
    stw r4, 0x20(r1)
    or r3, r5, r3
    lfd f2, lbl_806D7490(r2)
    stw r3, 0x8(r30)
    lfs f9, lbl_806D7488(r2)
    lwz r5, 0xc(r30)
    lwz r3, 0x4(r31)
    xoris r5, r5, 0x8000
    stw r4, 0x18(r1)
    xoris r3, r3, 0x8000
    lwz r4, 0x10(r30)
    stw r5, 0x24(r1)
    addi r4, r4, 0x1
    lwz r5, 0x14(r30)
    stw r3, 0x1c(r1)
    mulli r3, r4, 0x2c
    lfd f1, 0x20(r1)
    lfd f0, 0x18(r1)
    fsubs f1, f1, f2
    add r3, r5, r3
    fsubs f0, f0, f2
    lfs f10, 0x8(r31)
    lfs f3, 0x8(r3)
    lfs f11, 0xc(r31)
    fdivs f2, f1, f0
    lfs f6, 0xc(r3)
    lfs f13, 0x1c(r31)
    lfs f4, 0x1c(r3)
    lfs f27, 0x24(r31)
    lfs f28, 0x20(r31)
    fsubs f8, f3, f10
    lfs f1, 0x20(r3)
    fsubs f7, f6, f11
    lfs f3, 0x24(r3)
    fsubs f6, f4, f13
    lfs f26, 0x28(r31)
    fsubs f4, f3, f27
    lfs f0, 0x28(r3)
    fsubs f5, f1, f28
    lfs f12, 0x10(r3)
    fsubs f1, f0, f26
    lfs f0, 0x10(r31)
    fmadds f25, f2, f8, f10
    lfs f10, 0x18(r3)
    fmadds f6, f2, f6, f13
    lfs f13, 0x18(r31)
    fmadds f3, f2, f1, f26
    lfs f1, 0x14(r31)
    fmadds f26, f2, f7, f11
    lfs f11, 0x14(r3)
    fmadds f5, f2, f5, f28
    fmuls f8, f9, f6
    stb r0, 0x28(r30)
    fmadds f4, f2, f4, f27
    fmuls f7, f9, f5
    fmuls f5, f9, f3
    lfs f3, lbl_806D7484(r2)
    fmuls f6, f9, f4
    fadds f4, f25, f29
    fsubs f12, f12, f0
    fctiwz f7, f7
    stfs f4, 0x2c(r30)
    fadds f4, f26, f30
    fctiwz f8, f8
    stfd f7, 0x8(r1)
    fsubs f9, f11, f1
    fctiwz f6, f6
    stfs f4, 0x30(r30)
    fmuls f5, f31, f5
    lwz r0, 0xc(r1)
    fmadds f0, f2, f12, f0
    stfd f8, 0x10(r1)
    fctiwz f4, f5
    clrlslwi r0, r0, 24, 16
    stfs f3, 0x34(r30)
    fsubs f7, f10, f13
    fmadds f1, f2, f9, f1
    lwz r3, 0x14(r1)
    stfs f0, 0x44(r30)
    fmadds f2, f2, f7, f13
    rlwimi r0, r3, 24, 0, 7
    stfd f6, 0x28(r1)
    lwz r3, 0x2c(r1)
    stfs f1, 0x48(r30)
    rlwimi r0, r3, 8, 16, 23
    stfd f4, 0x30(r1)
    lwz r3, 0x34(r1)
    stfs f2, 0x40(r30)
    rlwimi r0, r3, 0, 24, 31
    stw r0, 0x4c(r30)
    stw r0, 0x50(r30)
    stw r0, 0x54(r30)
    stw r0, 0x58(r30)
    fn_8013AE20_L_8013B2B4:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    psq_l f29, 0x98(r1), 0, 0
    lfd f29, 0x90(r1)
    psq_l f28, 0x88(r1), 0, 0
    lfd f28, 0x80(r1)
    psq_l f27, 0x78(r1), 0, 0
    lfd f27, 0x70(r1)
    psq_l f26, 0x68(r1), 0, 0
    lfd f26, 0x60(r1)
    psq_l f25, 0x58(r1), 0, 0
    lfd f25, 0x50(r1)
    lmw r26, 0x38(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

void fn_8013B300(CSAnim *n, int id) {
    if (id < 0 || n->id == id) {
        fn_8013BA78(n);
    }
    if (n->next) {
        fn_8013B300(n->next, id);
    }
}

void fn_8013B4FC(CSAnim *n, int id) {
    if ((id < 0 || n->id == id) && n->keys && !(n->flags & 1)) {
        fn_8013BA78(n);
        n->flags |= lbl_806D7498;
    }
    if (n->next) {
        fn_8013B4FC(n->next, id);
    }
}

void fn_8013B7A8(CSAnim *n, CSAnim *add) {
    if (n->next) {
        fn_8013B7A8(n->next, add);
        return;
    }
    n->next = add;
}

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8013B87C[8] = {
    0x50, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013B87C = {
    (void *)&fn_8013B87C, 0x00000124, (void *)extab_fn_8013B87C
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void fn_8013B87C(void) { /* 0x8013B87C size:0x124 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r22, 0x8(r1)
    mr. r22, r3
    mr r23, r4
    beq fn_8013B87C_L_8013B988
    lwz r31, 0x4(r22)
    cmplwi r31, 0x0
    beq fn_8013B87C_L_8013B978
    beq fn_8013B87C_L_8013B978
    lwz r30, 0x4(r31)
    cmplwi r30, 0x0
    beq fn_8013B87C_L_8013B970
    beq fn_8013B87C_L_8013B970
    lwz r29, 0x4(r30)
    cmplwi r29, 0x0
    beq fn_8013B87C_L_8013B968
    beq fn_8013B87C_L_8013B968
    lwz r28, 0x4(r29)
    cmplwi r28, 0x0
    beq fn_8013B87C_L_8013B960
    beq fn_8013B87C_L_8013B960
    lwz r27, 0x4(r28)
    cmplwi r27, 0x0
    beq fn_8013B87C_L_8013B958
    beq fn_8013B87C_L_8013B958
    lwz r26, 0x4(r27)
    cmplwi r26, 0x0
    beq fn_8013B87C_L_8013B950
    beq fn_8013B87C_L_8013B950
    lwz r25, 0x4(r26)
    cmplwi r25, 0x0
    beq fn_8013B87C_L_8013B948
    beq fn_8013B87C_L_8013B948
    lwz r24, 0x4(r25)
    cmplwi r24, 0x0
    beq fn_8013B87C_L_8013B940
    beq fn_8013B87C_L_8013B940
    lwz r3, 0x4(r24)
    cmplwi r3, 0x0
    beq fn_8013B87C_L_8013B92C
    li r4, 0x1
    bl fn_8013B87C
    fn_8013B87C_L_8013B92C:
    addi r3, r24, 0x18
    li r4, -0x1
    bl dtor_80082960
    mr r3, r24
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B940:
    mr r3, r25
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B948:
    mr r3, r26
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B950:
    mr r3, r27
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B958:
    mr r3, r28
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B960:
    mr r3, r29
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B968:
    mr r3, r30
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B970:
    mr r3, r31
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B978:
    extsh. r0, r23
    ble fn_8013B87C_L_8013B988
    mr r3, r22
    bl MemoryManager_TimedFree
    fn_8013B87C_L_8013B988:
    mr r3, r22
    lmw r22, 0x8(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

CSAnim *fn_8013B9A0(CSAnim *n, int res, int res20, int mode, CSAnimKey *keys, int id) {
    n->id = id;
    n->keys = 0;
    ResCtrl_Init(&n->res);
    fn_8013BA78(n);
    n->next = 0;
    if (keys == 0) {
        return n;
    }
    n->keys = keys;
    n->res = res;
    n->res20 = res20;
    if (res20 <= -1 || res20 >= 5) {
        n->res20 = 0;
    }
    switch (mode) {
    case 1:
        n->u60 = 1;
        n->u64 = 4;
        n->u68 = 1;
        break;
    default:
        n->u60 = 1;
        n->u64 = 4;
        n->u68 = 5;
        break;
    }
    return n;
}
