/* === extracted from auto_VfxEffect_InitVarian_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GetSpawnPosition();

/* --- function index (1 fns, .text 0x800C6040..0x800C6074) ---
 * [  0] 0x800C6040 size:0x34    global VfxEffect_InitVariantAndResetPos
 */

/* --- forward decls --- */
asm void VfxEffect_InitVariantAndResetPos(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxEffect_InitVariantAndResetPos[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxEffect_InitVariantAndResetPos = {
    (void *)&VfxEffect_InitVariantAndResetPos, 0x00000034, (void *)extab_VfxEffect_InitVariantAndResetPos
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxEffect_InitVariantAndResetPos(void) { /* 0x800C6040 size:0x34 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    mr. r5, r3
    stw r0, 0x14(r1)
    beq VfxEffect_InitVariantAndResetPos_L_800C6064
    clrlwi r0, r4, 24
    addi r3, r5, 0x30
    stw r0, 0x10(r5)
    bl GetSpawnPosition
    VfxEffect_InitVariantAndResetPos_L_800C6064:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


