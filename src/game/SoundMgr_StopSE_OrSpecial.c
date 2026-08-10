/* === extracted from auto_SoundMgr_StopSE_OrSp_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8016C394();
extern void fn_8016C444();

/* --- function index (1 fns, .text 0x800DFC9C..0x800DFCE8) ---
 * [  0] 0x800DFC9C size:0x4C    global SoundMgr_StopSE_OrSpecial
 */

/* --- forward decls --- */
asm void SoundMgr_StopSE_OrSpecial(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SoundMgr_StopSE_OrSpecial[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SoundMgr_StopSE_OrSpecial = {
    (void *)&SoundMgr_StopSE_OrSpecial, 0x0000004C, (void *)extab_SoundMgr_StopSE_OrSpecial
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SoundMgr_StopSE_OrSpecial(void) { /* 0x800DFC9C size:0x4C */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmplwi r3, 0x0
    stw r0, 0x14(r1)
    beq SoundMgr_StopSE_OrSpecial_L_800DFCD8
    cmplwi r3, 0xbf
    bne SoundMgr_StopSE_OrSpecial_L_800DFCC4
    li r3, 0x0
    bl fn_8016C444
    b SoundMgr_StopSE_OrSpecial_L_800DFCD8
    SoundMgr_StopSE_OrSpecial_L_800DFCC4:
    cmpwi r4, 0x0
    ble SoundMgr_StopSE_OrSpecial_L_800DFCD4
    clrlslwi r0, r4, 28, 27
    or r3, r3, r0
    SoundMgr_StopSE_OrSpecial_L_800DFCD4:
    bl fn_8016C394
    SoundMgr_StopSE_OrSpecial_L_800DFCD8:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

