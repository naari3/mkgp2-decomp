/* === extracted from auto_KartDriver_SetUnifor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802D20AC();
extern unsigned int lbl_806D2548;
extern unsigned int lbl_806D2550;

/* --- function index (1 fns, .text 0x80041D80..0x80041FE0) ---
 * [  0] 0x80041D80 size:0x260   global KartDriver_SetUniformScale_4Wheels
 */

/* --- forward decls --- */
asm void KartDriver_SetUniformScale_4Wheels(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_SetUniformScale_4Wheels[8] = {
    0x10, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_SetUniformScale_4Wheels = {
    (void *)&KartDriver_SetUniformScale_4Wheels, 0x00000260, (void *)extab_KartDriver_SetUniformScale_4Wheels
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_SetUniformScale_4Wheels(void) { /* 0x80041D80 size:0x260 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x18(r1)
    fmr f31, f1
    stw r31, 0x14(r1)
    mr r31, r3
    stw r30, 0x10(r1)
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041DB8
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne KartDriver_SetUniformScale_4Wheels_L_80041DC0
    KartDriver_SetUniformScale_4Wheels_L_80041DB8:
    li r3, 0x0
    b KartDriver_SetUniformScale_4Wheels_L_80041FC4
    KartDriver_SetUniformScale_4Wheels_L_80041DC0:
    lwz r30, 0xe8(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041E40
    bne KartDriver_SetUniformScale_4Wheels_L_80041DE0
    la r3, lbl_806D2548(r2)
    li r4, 0x316
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041DE0:
    stfs f31, 0x2c(r30)
    stfs f31, 0x30(r30)
    stfs f31, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetUniformScale_4Wheels_L_80041E40
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041E40
    bne KartDriver_SetUniformScale_4Wheels_L_80041E14
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041E14:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetUniformScale_4Wheels_L_80041E30
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetUniformScale_4Wheels_L_80041E30
    li r3, 0x1
    KartDriver_SetUniformScale_4Wheels_L_80041E30:
    clrlwi. r0, r3, 24
    bne KartDriver_SetUniformScale_4Wheels_L_80041E40
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetUniformScale_4Wheels_L_80041E40:
    lwz r30, 0xec(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041EC0
    bne KartDriver_SetUniformScale_4Wheels_L_80041E60
    la r3, lbl_806D2548(r2)
    li r4, 0x316
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041E60:
    stfs f31, 0x2c(r30)
    stfs f31, 0x30(r30)
    stfs f31, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetUniformScale_4Wheels_L_80041EC0
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041EC0
    bne KartDriver_SetUniformScale_4Wheels_L_80041E94
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041E94:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetUniformScale_4Wheels_L_80041EB0
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetUniformScale_4Wheels_L_80041EB0
    li r3, 0x1
    KartDriver_SetUniformScale_4Wheels_L_80041EB0:
    clrlwi. r0, r3, 24
    bne KartDriver_SetUniformScale_4Wheels_L_80041EC0
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetUniformScale_4Wheels_L_80041EC0:
    lwz r30, 0xf0(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041F40
    bne KartDriver_SetUniformScale_4Wheels_L_80041EE0
    la r3, lbl_806D2548(r2)
    li r4, 0x316
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041EE0:
    stfs f31, 0x2c(r30)
    stfs f31, 0x30(r30)
    stfs f31, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetUniformScale_4Wheels_L_80041F40
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041F40
    bne KartDriver_SetUniformScale_4Wheels_L_80041F14
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041F14:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetUniformScale_4Wheels_L_80041F30
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetUniformScale_4Wheels_L_80041F30
    li r3, 0x1
    KartDriver_SetUniformScale_4Wheels_L_80041F30:
    clrlwi. r0, r3, 24
    bne KartDriver_SetUniformScale_4Wheels_L_80041F40
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetUniformScale_4Wheels_L_80041F40:
    lwz r30, 0xf4(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041FC0
    bne KartDriver_SetUniformScale_4Wheels_L_80041F60
    la r3, lbl_806D2548(r2)
    li r4, 0x316
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041F60:
    stfs f31, 0x2c(r30)
    stfs f31, 0x30(r30)
    stfs f31, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetUniformScale_4Wheels_L_80041FC0
    cmplwi r30, 0x0
    beq KartDriver_SetUniformScale_4Wheels_L_80041FC0
    bne KartDriver_SetUniformScale_4Wheels_L_80041F94
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetUniformScale_4Wheels_L_80041F94:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetUniformScale_4Wheels_L_80041FB0
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetUniformScale_4Wheels_L_80041FB0
    li r3, 0x1
    KartDriver_SetUniformScale_4Wheels_L_80041FB0:
    clrlwi. r0, r3, 24
    bne KartDriver_SetUniformScale_4Wheels_L_80041FC0
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetUniformScale_4Wheels_L_80041FC0:
    li r3, 0x1
    KartDriver_SetUniformScale_4Wheels_L_80041FC4:
    lwz r0, 0x24(r1)
    lfd f31, 0x18(r1)
    lwz r31, 0x14(r1)
    lwz r30, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

