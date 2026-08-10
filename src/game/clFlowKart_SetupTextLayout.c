/* === extracted from auto_clFlowKart_SetupText_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_801D92D0();
extern void fn_801F93D0();
extern void fn_801F93EC();
extern void isJapanese();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806DA1C8;
extern unsigned int lbl_806DA1CC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8039FC60[];

/* --- function index (1 fns, .text 0x801D9890..0x801D9A2C) ---
 * [  0] 0x801D9890 size:0x19C   global clFlowKart_SetupTextLayout
 */

/* --- forward decls --- */
asm void clFlowKart_SetupTextLayout(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowKart_SetupTextLayout[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowKart_SetupTextLayout = {
    (void *)&clFlowKart_SetupTextLayout, 0x0000019C, (void *)extab_clFlowKart_SetupTextLayout
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowKart_SetupTextLayout(void) { /* 0x801D9890 size:0x19C */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    mr r31, r3
    stw r30, 0x48(r1)
    stw r29, 0x44(r1)
    mr r29, r4
    bl isJapanese
    slwi r4, r3, 2
    addi r3, r13, -0x6E50  /* lbl_806CFED0 */
    mulli r0, r29, 0x1c
    lwzx r4, r3, r4
    mr r3, r31
    add r4, r4, r0
    bl fn_801D92D0
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clFlowKart_SetupTextLayout_L_801D98E4
    stw r29, 0x4(r31)
    b clFlowKart_SetupTextLayout_L_801D98E8
    clFlowKart_SetupTextLayout_L_801D98E4:
    stw r29, 0x40(r31)
    clFlowKart_SetupTextLayout_L_801D98E8:
    bl isJapanese
    cmpwi r3, 0x1
    bne clFlowKart_SetupTextLayout_L_801D9A10
    lwz r0, 0x4(r31)
    cmpwi r0, 0x8
    bne clFlowKart_SetupTextLayout_L_801D9A10
    lis r3, lbl_8039FC60@ha
    lfs f0, lbl_806DA1C8(r2)
    addi r30, r3, lbl_8039FC60@l
    lwz r3, 0x5c(r31)
    lfs f4, 0x0(r30)
    lfs f3, 0x20(r30)
    lfs f2, 0x4(r30)
    fadds f3, f4, f3
    lfs f1, 0x24(r30)
    fadds f1, f2, f1
    stfs f3, 0x18(r1)
    lwz r4, 0x18(r1)
    stfs f1, 0x1c(r1)
    stw r4, 0x30(r1)
    lwz r0, 0x1c(r1)
    lfs f1, 0x30(r1)
    stw r0, 0x34(r1)
    fsubs f1, f1, f0
    lfs f2, 0x34(r1)
    bl fn_801F93EC
    lis r3, lbl_8039FC60@ha
    lfsu f4, lbl_8039FC60@l(r3)
    lfs f2, 0x4(r30)
    lfs f3, 0x28(r3)
    lfs f1, 0x2c(r3)
    fadds f3, f4, f3
    lfs f0, lbl_806DA1C8(r2)
    fadds f1, f2, f1
    lwz r3, 0x60(r31)
    stfs f3, 0x10(r1)
    lwz r0, 0x10(r1)
    stfs f1, 0x14(r1)
    stw r0, 0x28(r1)
    lwz r0, 0x14(r1)
    lfs f1, 0x28(r1)
    stw r0, 0x2c(r1)
    fsubs f1, f1, f0
    lfs f2, 0x2c(r1)
    bl fn_801F93EC
    lis r3, lbl_8039FC60@ha
    lfsu f4, lbl_8039FC60@l(r3)
    lfs f2, 0x4(r30)
    lfs f3, 0x30(r3)
    lfs f1, 0x34(r3)
    fadds f3, f4, f3
    lfs f0, lbl_806DA1C8(r2)
    fadds f1, f2, f1
    lwz r3, 0x64(r31)
    stfs f3, 0x8(r1)
    lwz r0, 0x8(r1)
    stfs f1, 0xc(r1)
    stw r0, 0x20(r1)
    lwz r0, 0xc(r1)
    lfs f1, 0x20(r1)
    stw r0, 0x24(r1)
    fsubs f1, f1, f0
    lfs f2, 0x24(r1)
    bl fn_801F93EC
    li r29, 0x0
    mr r30, r31
    clFlowKart_SetupTextLayout_L_801D99F0:
    lfs f1, lbl_806DA1CC(r2)
    lwz r3, 0x5c(r30)
    fmr f2, f1
    bl fn_801F93D0
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0x3
    blt clFlowKart_SetupTextLayout_L_801D99F0
    clFlowKart_SetupTextLayout_L_801D9A10:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r29, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

