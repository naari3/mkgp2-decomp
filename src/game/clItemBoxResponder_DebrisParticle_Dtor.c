/* === extracted from auto_clItemBoxResponder_D_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D29A8;

/* --- function index (1 fns, .text 0x8005D9D4..0x8005DA18) ---
 * [  0] 0x8005D9D4 size:0x44    global clItemBoxResponder_DebrisParticle_Dtor
 */

/* --- forward decls --- */
asm void clItemBoxResponder_DebrisParticle_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBoxResponder_DebrisParticle_Dtor[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_DebrisParticle_Dtor = {
    (void *)&clItemBoxResponder_DebrisParticle_Dtor, 0x00000044, (void *)extab_clItemBoxResponder_DebrisParticle_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_DebrisParticle_Dtor(void) { /* 0x8005D9D4 size:0x44 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq clItemBoxResponder_DebrisParticle_Dtor_L_8005DA00
    lfs f0, lbl_806D29A8(r2)
    extsh. r0, r4
    stfs f0, 0x1c(r31)
    ble clItemBoxResponder_DebrisParticle_Dtor_L_8005DA00
    bl MemoryManager_TimedFree
    clItemBoxResponder_DebrisParticle_Dtor_L_8005DA00:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

