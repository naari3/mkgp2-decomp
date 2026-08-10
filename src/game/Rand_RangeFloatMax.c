/* === extracted from auto_Rand_RangeFloatMax_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Rand15();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5950;
extern unsigned int lbl_806D5958;

/* --- function index (1 fns, .text 0x800D650C..0x800D6568) ---
 * [  0] 0x800D650C size:0x5C    global Rand_RangeFloatMax
 */

/* --- forward decls --- */
asm void Rand_RangeFloatMax(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Rand_RangeFloatMax[8] = {
    0x00, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Rand_RangeFloatMax = {
    (void *)&Rand_RangeFloatMax, 0x0000005C, (void *)extab_Rand_RangeFloatMax
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Rand_RangeFloatMax(void) { /* 0x800D650C size:0x5C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x18(r1), 0, 0
    fmr f31, f1
    bl Rand15
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f2, lbl_806D5958(r2)
    stw r0, 0x8(r1)
    lfs f0, lbl_806D5950(r2)
    lfd f1, 0x8(r1)
    fsubs f1, f1, f2
    fdivs f0, f1, f0
    fmuls f1, f31, f0
    psq_l f31, 0x18(r1), 0, 0
    lwz r0, 0x24(r1)
    lfd f31, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

