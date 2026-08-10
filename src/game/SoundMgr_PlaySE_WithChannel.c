/* === extracted from auto_SoundMgr_PlaySE_With_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8016C288();

/* --- function index (1 fns, .text 0x800DFCE8..0x800DFD28) ---
 * [  0] 0x800DFCE8 size:0x40    global SoundMgr_PlaySE_WithChannel
 */

/* --- forward decls --- */
asm void SoundMgr_PlaySE_WithChannel(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SoundMgr_PlaySE_WithChannel[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SoundMgr_PlaySE_WithChannel = {
    (void *)&SoundMgr_PlaySE_WithChannel, 0x00000040, (void *)extab_SoundMgr_PlaySE_WithChannel
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SoundMgr_PlaySE_WithChannel(void) { /* 0x800DFCE8 size:0x40 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmplwi r3, 0x0
    stw r0, 0x14(r1)
    beq SoundMgr_PlaySE_WithChannel_L_800DFD18
    cmplwi r3, 0xbf
    beq SoundMgr_PlaySE_WithChannel_L_800DFD18
    cmpwi r5, 0x0
    ble SoundMgr_PlaySE_WithChannel_L_800DFD14
    clrlslwi r0, r5, 28, 27
    or r3, r3, r0
    SoundMgr_PlaySE_WithChannel_L_800DFD14:
    bl fn_8016C288
    SoundMgr_PlaySE_WithChannel_L_800DFD18:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


