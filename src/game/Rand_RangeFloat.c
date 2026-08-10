/* === extracted from auto_Rand_RangeFloat_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Rand15();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5950;
extern unsigned int lbl_806D5958;

/* --- function index (1 fns, .text 0x800D6498..0x800D650C) ---
 * [  0] 0x800D6498 size:0x74    global Rand_RangeFloat
 */

/* --- forward decls --- */
asm void Rand_RangeFloat(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Rand_RangeFloat[8] = {
    0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Rand_RangeFloat = {
    (void *)&Rand_RangeFloat, 0x00000074, (void *)extab_Rand_RangeFloat
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Rand_RangeFloat(void) { /* 0x800D6498 size:0x74 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stfd f30, 0x10(r1)
    psq_st f30, 0x18(r1), 0, 0
    fmr f30, f1
    fmr f31, f2
    bl Rand15
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    fsubs f0, f31, f30
    lfd f3, lbl_806D5958(r2)
    stw r0, 0x8(r1)
    lfs f1, lbl_806D5950(r2)
    lfd f2, 0x8(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fmadds f1, f0, f1, f30
    psq_l f31, 0x28(r1), 0, 0
    lfd f31, 0x20(r1)
    psq_l f30, 0x18(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f30, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

