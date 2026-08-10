/* === extracted from auto_clItemBoxResponder_D_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void clItemBoxResponder_DrawDebrisParticle();

/* --- function index (1 fns, .text 0x8005DB3C..0x8005DBA0) ---
 * [  0] 0x8005DB3C size:0x64    global clItemBoxResponder_DrawDebris
 */

/* --- forward decls --- */
asm void clItemBoxResponder_DrawDebris(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBoxResponder_DrawDebris[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_DrawDebris = {
    (void *)&clItemBoxResponder_DrawDebris, 0x00000064, (void *)extab_clItemBoxResponder_DrawDebris
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_DrawDebris(void) { /* 0x8005DB3C size:0x64 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    lbz r0, 0x0(r3)
    cmplwi r0, 0x0
    bne clItemBoxResponder_DrawDebris_L_8005DB64
    li r3, 0x0
    b clItemBoxResponder_DrawDebris_L_8005DB88
    clItemBoxResponder_DrawDebris_L_8005DB64:
    li r30, 0x0
    mr r31, r3
    clItemBoxResponder_DrawDebris_L_8005DB6C:
    addi r3, r31, 0x4
    bl clItemBoxResponder_DrawDebrisParticle
    addi r30, r30, 0x1
    addi r31, r31, 0x2c
    cmplwi r30, 0xf
    blt clItemBoxResponder_DrawDebris_L_8005DB6C
    li r3, 0x1
    clItemBoxResponder_DrawDebris_L_8005DB88:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
