/* === extracted from auto_ObjectTree_BlendOrCo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ObjectTree_BlendQuatLerp();
extern void Object_CopyFieldsRotPosScale();
extern void fn_802D07BC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2340;

/* --- function index (1 fns, .text 0x800322F8..0x80032540) ---
 * [  0] 0x800322F8 size:0x248   global ObjectTree_BlendOrCopy
 */

/* --- forward decls --- */
asm void ObjectTree_BlendOrCopy(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ObjectTree_BlendOrCopy[8] = {
    0x40, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ObjectTree_BlendOrCopy = {
    (void *)&ObjectTree_BlendOrCopy, 0x00000248, (void *)extab_ObjectTree_BlendOrCopy
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ObjectTree_BlendOrCopy(void) { /* 0x800322F8 size:0x248 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stmw r24, 0x10(r1)
    mr. r26, r4
    fmr f31, f1
    mr r31, r3
    mr r25, r5
    mr r24, r6
    beq ObjectTree_BlendOrCopy_L_80032524
    cmplwi r25, 0x0
    bne ObjectTree_BlendOrCopy_L_80032334
    b ObjectTree_BlendOrCopy_L_80032524
    ObjectTree_BlendOrCopy_L_80032334:
    cmplwi r24, 0x0
    beq ObjectTree_BlendOrCopy_L_80032344
    bl ObjectTree_BlendQuatLerp
    b ObjectTree_BlendOrCopy_L_80032394
    ObjectTree_BlendOrCopy_L_80032344:
    lfs f0, 0x38(r26)
    stfs f0, 0x38(r25)
    lfs f0, 0x3c(r26)
    stfs f0, 0x3c(r25)
    lfs f0, 0x40(r26)
    stfs f0, 0x40(r25)
    lfs f0, 0x1c(r26)
    stfs f0, 0x1c(r25)
    lfs f0, 0x20(r26)
    stfs f0, 0x20(r25)
    lfs f0, 0x24(r26)
    stfs f0, 0x24(r25)
    lfs f0, 0x28(r26)
    stfs f0, 0x28(r25)
    lfs f0, 0x2c(r26)
    stfs f0, 0x2c(r25)
    lfs f0, 0x30(r26)
    stfs f0, 0x30(r25)
    lfs f0, 0x34(r26)
    stfs f0, 0x34(r25)
    ObjectTree_BlendOrCopy_L_80032394:
    mr r3, r26
    bl fn_802D07BC
    rlwinm. r0, r3, 0, 19, 19
    bne ObjectTree_BlendOrCopy_L_80032524
    cmplwi r24, 0x0
    beq ObjectTree_BlendOrCopy_L_800324A4
    lwz r26, 0x10(r26)
    lwz r25, 0x10(r25)
    lwz r24, 0x10(r24)
    b ObjectTree_BlendOrCopy_L_80032498
    ObjectTree_BlendOrCopy_L_800323BC:
    cmplwi r26, 0x0
    beq ObjectTree_BlendOrCopy_L_8003248C
    cmplwi r25, 0x0
    beq ObjectTree_BlendOrCopy_L_8003248C
    cmplwi r24, 0x0
    beq ObjectTree_BlendOrCopy_L_800323F0
    fmr f1, f31
    mr r3, r31
    mr r4, r26
    mr r5, r25
    mr r6, r24
    bl ObjectTree_BlendQuatLerp
    b ObjectTree_BlendOrCopy_L_80032400
    ObjectTree_BlendOrCopy_L_800323F0:
    mr r3, r31
    mr r4, r26
    mr r5, r25
    bl Object_CopyFieldsRotPosScale
    ObjectTree_BlendOrCopy_L_80032400:
    mr r3, r26
    bl fn_802D07BC
    rlwinm. r0, r3, 0, 19, 19
    bne ObjectTree_BlendOrCopy_L_8003248C
    cmplwi r24, 0x0
    beq ObjectTree_BlendOrCopy_L_80032458
    lwz r28, 0x10(r26)
    lwz r29, 0x10(r25)
    lwz r30, 0x10(r24)
    b ObjectTree_BlendOrCopy_L_8003244C
    ObjectTree_BlendOrCopy_L_80032428:
    fmr f1, f31
    mr r3, r31
    mr r4, r28
    mr r5, r29
    mr r6, r30
    bl ObjectTree_BlendOrCopy
    lwz r28, 0x8(r28)
    lwz r29, 0x8(r29)
    lwz r30, 0x8(r30)
    ObjectTree_BlendOrCopy_L_8003244C:
    cmplwi r28, 0x0
    bne ObjectTree_BlendOrCopy_L_80032428
    b ObjectTree_BlendOrCopy_L_8003248C
    ObjectTree_BlendOrCopy_L_80032458:
    lwz r27, 0x10(r26)
    lwz r28, 0x10(r25)
    b ObjectTree_BlendOrCopy_L_80032484
    ObjectTree_BlendOrCopy_L_80032464:
    lfs f1, lbl_806D2340(r2)
    mr r3, r31
    mr r4, r27
    mr r5, r28
    li r6, 0x0
    bl ObjectTree_BlendOrCopy
    lwz r27, 0x8(r27)
    lwz r28, 0x8(r28)
    ObjectTree_BlendOrCopy_L_80032484:
    cmplwi r27, 0x0
    bne ObjectTree_BlendOrCopy_L_80032464
    ObjectTree_BlendOrCopy_L_8003248C:
    lwz r26, 0x8(r26)
    lwz r25, 0x8(r25)
    lwz r24, 0x8(r24)
    ObjectTree_BlendOrCopy_L_80032498:
    cmplwi r26, 0x0
    bne ObjectTree_BlendOrCopy_L_800323BC
    b ObjectTree_BlendOrCopy_L_80032524
    ObjectTree_BlendOrCopy_L_800324A4:
    lwz r30, 0x10(r26)
    lwz r27, 0x10(r25)
    b ObjectTree_BlendOrCopy_L_8003251C
    ObjectTree_BlendOrCopy_L_800324B0:
    cmplwi r30, 0x0
    beq ObjectTree_BlendOrCopy_L_80032514
    cmplwi r27, 0x0
    beq ObjectTree_BlendOrCopy_L_80032514
    mr r3, r31
    mr r4, r30
    mr r5, r27
    bl Object_CopyFieldsRotPosScale
    mr r3, r30
    bl fn_802D07BC
    rlwinm. r0, r3, 0, 19, 19
    bne ObjectTree_BlendOrCopy_L_80032514
    lwz r29, 0x10(r30)
    lwz r28, 0x10(r27)
    b ObjectTree_BlendOrCopy_L_8003250C
    ObjectTree_BlendOrCopy_L_800324EC:
    lfs f1, lbl_806D2340(r2)
    mr r3, r31
    mr r4, r29
    mr r5, r28
    li r6, 0x0
    bl ObjectTree_BlendOrCopy
    lwz r29, 0x8(r29)
    lwz r28, 0x8(r28)
    ObjectTree_BlendOrCopy_L_8003250C:
    cmplwi r29, 0x0
    bne ObjectTree_BlendOrCopy_L_800324EC
    ObjectTree_BlendOrCopy_L_80032514:
    lwz r30, 0x8(r30)
    lwz r27, 0x8(r27)
    ObjectTree_BlendOrCopy_L_8003251C:
    cmplwi r30, 0x0
    bne ObjectTree_BlendOrCopy_L_800324B0
    ObjectTree_BlendOrCopy_L_80032524:
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    lmw r24, 0x10(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

