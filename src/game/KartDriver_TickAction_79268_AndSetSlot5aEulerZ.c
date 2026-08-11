/* === extracted from auto_KartDriver_TickActio_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartTireFX_SetPitch();
extern void __assert();
extern void fn_802D20AC();
extern char lbl_806D2548[7];
extern char lbl_806D2550[5];

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EADBC[];

/* --- function index (1 fns, .text 0x80042120..0x80042238) ---
 * [  0] 0x80042120 size:0x118   global KartDriver_TickAction_79268_AndSetSlot5aEulerZ
 */

/* --- forward decls --- */
asm void KartDriver_TickAction_79268_AndSetSlot5aEulerZ(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_TickAction_79268_AndSetSlot5aEulerZ[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_TickAction_79268_AndSetSlot5aEulerZ = {
    (void *)&KartDriver_TickAction_79268_AndSetSlot5aEulerZ, 0x00000118, (void *)extab_KartDriver_TickAction_79268_AndSetSlot5aEulerZ
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_TickAction_79268_AndSetSlot5aEulerZ(void) { /* 0x80042120 size:0x118 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x18(r1), 0, 0
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    fmr f31, f1
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_8004215C
    lwz r0, 0xc(r30)
    cmplwi r0, 0x0
    bne KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042164
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_8004215C:
    li r3, 0x0
    b KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042218
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042164:
    lwz r3, 0x30c(r30)
    cmplwi r3, 0x0
    beq KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042174
    bl KartTireFX_SetPitch
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042174:
    lwz r31, 0x168(r30)
    cmplwi r31, 0x0
    beq KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042214
    lfs f0, 0x170(r30)
    fadds f31, f0, f31
    bne KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_8004219C
    la r3, lbl_806D2548(r2)
    li r4, 0x2cc
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_8004219C:
    lwz r0, 0x14(r31)
    rlwinm. r0, r0, 0, 14, 14
    beq KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_800421BC
    lis r4, lbl_802EADBC@ha
    la r3, lbl_806D2548(r2)
    addi r5, r4, lbl_802EADBC@l
    li r4, 0x2cd
    bl __assert
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_800421BC:
    stfs f31, 0x24(r31)
    lwz r0, 0x14(r31)
    rlwinm. r0, r0, 0, 6, 6
    bne KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042214
    cmplwi r31, 0x0
    beq KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042214
    bne KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_800421E8
    la r3, lbl_806D2548(r2)
    li r4, 0x25d
    la r5, lbl_806D2550(r2)
    bl __assert
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_800421E8:
    lwz r4, 0x14(r31)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042204
    rlwinm. r0, r4, 0, 25, 25
    beq KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042204
    li r3, 0x1
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042204:
    clrlwi. r0, r3, 24
    bne KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042214
    mr r3, r31
    bl fn_802D20AC
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042214:
    li r3, 0x1
    KartDriver_TickAction_79268_AndSetSlot5aEulerZ_L_80042218:
    psq_l f31, 0x18(r1), 0, 0
    lwz r0, 0x24(r1)
    lfd f31, 0x10(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

