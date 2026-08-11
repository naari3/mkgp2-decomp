/* === extracted from auto_KartDriver_SetEulerY_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802D20AC();
extern char lbl_806D2548[7];
extern char lbl_806D2550[5];

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EADBC[];

/* --- function index (1 fns, .text 0x80041ABC..0x80041D80) ---
 * [  0] 0x80041ABC size:0x2C4   global KartDriver_SetEulerY_4Joints_LastMirrored
 */

/* --- forward decls --- */
asm void KartDriver_SetEulerY_4Joints_LastMirrored(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_SetEulerY_4Joints_LastMirrored[8] = {
    0x10, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_SetEulerY_4Joints_LastMirrored = {
    (void *)&KartDriver_SetEulerY_4Joints_LastMirrored, 0x000002C4, (void *)extab_KartDriver_SetEulerY_4Joints_LastMirrored
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_SetEulerY_4Joints_LastMirrored(void) { /* 0x80041ABC size:0x2C4 */
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
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041AF4
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041AFC
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041AF4:
    li r3, 0x0
    b KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D64
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041AFC:
    lwz r30, 0xe8(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B94
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B1C
    la r3, lbl_806D2548(r2)
    li r4, 0x2b8
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B1C:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B3C
    lis r4, lbl_802EADBC@ha
    la r3, lbl_806D2548(r2)
    addi r5, r4, lbl_802EADBC@l
    li r4, 0x2b9
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B3C:
    stfs f31, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B94
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B94
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B68
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B68:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B84
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B84
    li r3, 0x1
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B84:
    clrlwi. r0, r3, 24
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B94
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041B94:
    lwz r30, 0xec(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C2C
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041BB4
    la r3, lbl_806D2548(r2)
    li r4, 0x2b8
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041BB4:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041BD4
    lis r4, lbl_802EADBC@ha
    la r3, lbl_806D2548(r2)
    addi r5, r4, lbl_802EADBC@l
    li r4, 0x2b9
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041BD4:
    stfs f31, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C2C
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C2C
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C00
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C00:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C1C
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C1C
    li r3, 0x1
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C1C:
    clrlwi. r0, r3, 24
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C2C
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C2C:
    lwz r30, 0x164(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CC4
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C4C
    la r3, lbl_806D2548(r2)
    li r4, 0x2b8
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C4C:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C6C
    lis r4, lbl_802EADBC@ha
    la r3, lbl_806D2548(r2)
    addi r5, r4, lbl_802EADBC@l
    li r4, 0x2b9
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C6C:
    stfs f31, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CC4
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CC4
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C98
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041C98:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CB4
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CB4
    li r3, 0x1
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CB4:
    clrlwi. r0, r3, 24
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CC4
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CC4:
    lwz r30, 0x16c(r31)
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D60
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CE4
    la r3, lbl_806D2548(r2)
    li r4, 0x2b8
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041CE4:
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 14, 14
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D04
    lis r4, lbl_802EADBC@ha
    la r3, lbl_806D2548(r2)
    addi r5, r4, lbl_802EADBC@l
    li r4, 0x2b9
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D04:
    fneg f0, f31
    stfs f0, 0x20(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D60
    cmplwi r30, 0x0
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D60
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D34
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D34:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D50
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D50
    li r3, 0x1
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D50:
    clrlwi. r0, r3, 24
    bne KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D60
    mr r3, r30
    bl fn_802D20AC
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D60:
    li r3, 0x1
    KartDriver_SetEulerY_4Joints_LastMirrored_L_80041D64:
    lwz r0, 0x24(r1)
    lfd f31, 0x18(r1)
    lwz r31, 0x14(r1)
    lwz r30, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

