/* === extracted from auto_TEXBindPaletteEntry_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GXInitTexObjFilter();
extern void fn_80268260();
extern void fn_802685FC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D33A0;

/* --- function index (1 fns, .text 0x8008E3E0..0x8008E4E8) ---
 * [  0] 0x8008E3E0 size:0x108   global TEXBindPaletteEntry_CI
 */

/* --- forward decls --- */
asm void TEXBindPaletteEntry_CI(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TEXBindPaletteEntry_CI[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TEXBindPaletteEntry_CI = {
    (void *)&TEXBindPaletteEntry_CI, 0x00000108, (void *)extab_TEXBindPaletteEntry_CI
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TEXBindPaletteEntry_CI(void) { /* 0x8008E3E0 size:0x108 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    slwi r0, r7, 3
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    mr r29, r6
    stw r28, 0x20(r1)
    mr r28, r4
    lwz r3, 0x8(r3)
    add r31, r3, r0
    lwz r4, 0x0(r31)
    lbz r3, 0x21(r4)
    lbz r0, 0x22(r4)
    cmplw r3, r0
    bne TEXBindPaletteEntry_CI_L_8008E42C
    li r30, 0x0
    b TEXBindPaletteEntry_CI_L_8008E430
    TEXBindPaletteEntry_CI_L_8008E42C:
    li r30, 0x1
    TEXBindPaletteEntry_CI_L_8008E430:
    lwz r6, 0x4(r31)
    mr r3, r5
    lwz r4, 0x8(r6)
    lwz r5, 0x4(r6)
    lhz r6, 0x0(r6)
    bl fn_802685FC
    lwz r9, 0x0(r31)
    mr r3, r28
    mr r10, r30
    stw r29, 0x8(r1)
    lwz r4, 0x8(r9)
    lhz r5, 0x2(r9)
    lhz r6, 0x0(r9)
    lwz r7, 0x4(r9)
    lwz r8, 0xc(r9)
    lwz r9, 0x10(r9)
    bl fn_80268260
    lwz r7, 0x0(r31)
    lis r5, 0x4330
    stw r5, 0x10(r1)
    mr r3, r28
    lbz r4, 0x21(r7)
    li r6, 0x0
    lbz r0, 0x22(r7)
    li r8, 0x0
    stw r4, 0x14(r1)
    lfd f2, lbl_806D33A0(r2)
    lfd f0, 0x10(r1)
    stw r0, 0x1c(r1)
    fsubs f1, f0, f2
    lwz r4, 0x14(r7)
    stw r5, 0x18(r1)
    lwz r5, 0x18(r7)
    lfd f0, 0x18(r1)
    lfs f3, 0x1c(r7)
    fsubs f2, f0, f2
    lbz r7, 0x20(r7)
    bl GXInitTexObjFilter
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

