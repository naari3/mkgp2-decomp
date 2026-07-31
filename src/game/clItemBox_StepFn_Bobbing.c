/* === extracted from auto_clItemBox_StepFn_Bob_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D29AC;
extern unsigned int lbl_806D29B0;
extern unsigned int lbl_806D29D8;
extern unsigned int lbl_806D29E0;
extern unsigned int lbl_806D29EC;
extern unsigned int lbl_806D29F0;
extern unsigned int lbl_806D29F8;

/* --- function index (1 fns, .text 0x8005E924..0x8005E9D0) ---
 * [  0] 0x8005E924 size:0xAC    global clItemBox_StepFn_Bobbing
 */

/* --- forward decls --- */
asm void clItemBox_StepFn_Bobbing(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBox_StepFn_Bobbing[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBox_StepFn_Bobbing = {
    (void *)&clItemBox_StepFn_Bobbing, 0x000000AC, (void *)extab_clItemBox_StepFn_Bobbing
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_StepFn_Bobbing(void) { /* 0x8005E924 size:0xAC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D29EC(r2)
    stw r0, 0x14(r1)
    lfs f1, lbl_806D29E0(r2)
    stw r31, 0xc(r1)
    mr r31, r3
    lfs f2, 0x28(r3)
    fadds f0, f2, f0
    lfd f2, lbl_806D29F0(r2)
    stfs f0, 0x28(r3)
    lfs f0, 0x28(r3)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl fn_8027E9E8
    lfs f2, lbl_806D29D8(r2)
    frsp f4, f1
    lfs f0, 0x0(r31)
    lfs f3, lbl_806D29F8(r2)
    fadds f1, f2, f0
    lfs f0, lbl_806D29AC(r2)
    fmuls f2, f2, f4
    stfs f1, 0xc(r31)
    lfs f1, 0xc(r31)
    fmadds f1, f3, f2, f1
    stfs f1, 0xc(r31)
    lfs f1, 0x28(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne clItemBox_StepFn_Bobbing_L_8005E9A8
    fsubs f0, f1, f0
    stfs f0, 0x28(r31)
    clItemBox_StepFn_Bobbing_L_8005E9A8:
    lfs f1, 0x14(r31)
    li r3, 0x1
    lfs f0, lbl_806D29B0(r2)
    fadds f0, f1, f0
    stfs f0, 0x14(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

