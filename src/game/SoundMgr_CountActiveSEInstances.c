/* === extracted from auto_SoundMgr_CountActive_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8016C360();

/* --- function index (1 fns, .text 0x800DFEB8..0x800DFF34) ---
 * [  0] 0x800DFEB8 size:0x7C    global SoundMgr_CountActiveSEInstances
 */

/* --- forward decls --- */
asm void SoundMgr_CountActiveSEInstances(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SoundMgr_CountActiveSEInstances[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SoundMgr_CountActiveSEInstances = {
    (void *)&SoundMgr_CountActiveSEInstances, 0x0000007C, (void *)extab_SoundMgr_CountActiveSEInstances
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SoundMgr_CountActiveSEInstances(void) { /* 0x800DFEB8 size:0x7C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr. r29, r3
    bne SoundMgr_CountActiveSEInstances_L_800DFEE0
    li r3, -0x1
    b SoundMgr_CountActiveSEInstances_L_800DFF18
    SoundMgr_CountActiveSEInstances_L_800DFEE0:
    li r30, 0x0
    li r31, 0x0
    SoundMgr_CountActiveSEInstances_L_800DFEE8:
    rlwinm r0, r31, 0, 1, 4
    or r3, r29, r0
    bl fn_8016C360
    clrlwi. r0, r3, 24
    bne SoundMgr_CountActiveSEInstances_L_800DFF04
    mr r3, r30
    b SoundMgr_CountActiveSEInstances_L_800DFF18
    SoundMgr_CountActiveSEInstances_L_800DFF04:
    addi r30, r30, 0x1
    addis r31, r31, 0x800
    cmpwi r30, 0x8
    blt SoundMgr_CountActiveSEInstances_L_800DFEE8
    li r3, -0x1
    SoundMgr_CountActiveSEInstances_L_800DFF18:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
