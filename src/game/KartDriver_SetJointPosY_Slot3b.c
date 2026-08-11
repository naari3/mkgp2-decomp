/* === extracted from auto_KartDriver_SetJointP_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802D20AC();
extern unsigned int lbl_806D2548;
extern unsigned int lbl_806D2550;

/* --- function index (1 fns, .text 0x80041924..0x800419F0) ---
 * [  0] 0x80041924 size:0xCC    global KartDriver_SetJointPosY_Slot3b
 */

/* --- forward decls --- */
asm void KartDriver_SetJointPosY_Slot3b(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_SetJointPosY_Slot3b[8] = {
    0x08, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_SetJointPosY_Slot3b = {
    (void *)&KartDriver_SetJointPosY_Slot3b, 0x000000CC, (void *)extab_KartDriver_SetJointPosY_Slot3b
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_SetJointPosY_Slot3b(void) { /* 0x80041924 size:0xCC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x18(r1)
    fmr f31, f1
    stw r31, 0x14(r1)
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq KartDriver_SetJointPosY_Slot3b_L_80041954
    lwz r0, 0xc(r3)
    cmplwi r0, 0x0
    bne KartDriver_SetJointPosY_Slot3b_L_8004195C
    KartDriver_SetJointPosY_Slot3b_L_80041954:
    li r3, 0x0
    b KartDriver_SetJointPosY_Slot3b_L_800419D8
    KartDriver_SetJointPosY_Slot3b_L_8004195C:
    lwz r31, 0xec(r3)
    cmplwi r31, 0x0
    beq KartDriver_SetJointPosY_Slot3b_L_800419D4
    bne KartDriver_SetJointPosY_Slot3b_L_8004197C
    la r3, lbl_806D2548(r2)
    li r4, 0x3c6
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetJointPosY_Slot3b_L_8004197C:
    stfs f31, 0x3c(r31)
    lwz r0, 0x14(r31)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_SetJointPosY_Slot3b_L_800419D4
    cmplwi r31, 0x0
    beq KartDriver_SetJointPosY_Slot3b_L_800419D4
    bne KartDriver_SetJointPosY_Slot3b_L_800419A8
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_SetJointPosY_Slot3b_L_800419A8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_SetJointPosY_Slot3b_L_800419C4
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_SetJointPosY_Slot3b_L_800419C4
    li r3, 0x1
    KartDriver_SetJointPosY_Slot3b_L_800419C4:
    clrlwi. r0, r3, 24
    bne KartDriver_SetJointPosY_Slot3b_L_800419D4
    mr r3, r31
    bl fn_802D20AC
    KartDriver_SetJointPosY_Slot3b_L_800419D4:
    li r3, 0x1
    KartDriver_SetJointPosY_Slot3b_L_800419D8:
    lwz r0, 0x24(r1)
    lfd f31, 0x18(r1)
    lwz r31, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

