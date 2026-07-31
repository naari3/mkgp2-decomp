/* === extracted from auto_clItemBox_StepFn_Pop_text === */
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
extern unsigned int lbl_806D29F0;
extern unsigned int lbl_806D29FC;
extern unsigned int lbl_806D2A00;

/* --- function index (1 fns, .text 0x8005E9D0..0x8005EA74) ---
 * [  0] 0x8005E9D0 size:0xA4    global clItemBox_StepFn_PopOut
 */

/* --- forward decls --- */
asm void clItemBox_StepFn_PopOut(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBox_StepFn_PopOut[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBox_StepFn_PopOut = {
    (void *)&clItemBox_StepFn_PopOut, 0x000000A4, (void *)extab_clItemBox_StepFn_PopOut
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_StepFn_PopOut(void) { /* 0x8005E9D0 size:0xA4 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D29B0(r2)
    stw r0, 0x14(r1)
    lfs f1, lbl_806D29FC(r2)
    stw r31, 0xc(r1)
    mr r31, r3
    lfs f2, 0x2c(r3)
    fadds f0, f2, f0
    lfd f2, lbl_806D29F0(r2)
    stfs f0, 0x2c(r3)
    lfs f0, 0x2c(r3)
    fmuls f0, f1, f0
    fmul f1, f2, f0
    frsp f1, f1
    bl fn_8027E9E8
    frsp f3, f1
    lfs f2, lbl_806D29D8(r2)
    lfs f0, 0x0(r31)
    lfs f1, lbl_806D2A00(r2)
    fmadds f2, f2, f3, f0
    lfs f0, lbl_806D29AC(r2)
    stfs f2, 0xc(r31)
    lfs f2, 0x2c(r31)
    stfs f2, 0x30(r31)
    lfs f2, 0x14(r31)
    fadds f1, f2, f1
    stfs f1, 0x14(r31)
    lfs f1, 0x2c(r31)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne clItemBox_StepFn_PopOut_L_8005EA5C
    stfs f0, 0x30(r31)
    li r3, 0x1
    b clItemBox_StepFn_PopOut_L_8005EA60
    clItemBox_StepFn_PopOut_L_8005EA5C:
    li r3, 0x0
    clItemBox_StepFn_PopOut_L_8005EA60:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

