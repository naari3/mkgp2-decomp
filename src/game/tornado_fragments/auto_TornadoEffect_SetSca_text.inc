/* === extracted from auto_TornadoEffect_SetSca_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Saturate_Double();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28C8;
extern unsigned int lbl_806D28CC;

/* --- function index (1 fns, .text 0x800577FC..0x8005785C) ---
 * [  0] 0x800577FC size:0x60    global TornadoEffect_SetScalePairB0BC
 */

/* --- forward decls --- */
asm void TornadoEffect_SetScalePairB0BC(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_SetScalePairB0BC[8] = {
    0x08, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_SetScalePairB0BC = {
    (void *)&TornadoEffect_SetScalePairB0BC, 0x00000060, (void *)extab_TornadoEffect_SetScalePairB0BC
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_SetScalePairB0BC(void) { /* 0x800577FC size:0x60 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stfd f31, 0x10(r1)
    psq_st f31, 0x18(r1), 0, 0
    stw r31, 0xc(r1)
    fmr f31, f2
    lfs f2, lbl_806D28C8(r2)
    lfs f3, lbl_806D28CC(r2)
    mr r31, r3
    bl Saturate_Double
    stfs f1, 0xb0(r31)
    fmr f1, f31
    lfs f2, lbl_806D28C8(r2)
    lfs f3, lbl_806D28CC(r2)
    bl Saturate_Double
    stfs f1, 0xbc(r31)
    psq_l f31, 0x18(r1), 0, 0
    lwz r0, 0x24(r1)
    lfd f31, 0x10(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

