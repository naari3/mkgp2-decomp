/* === extracted from auto_VfxSlot_SetMatrixSou_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void cLNormal3DWrap_Slot_ClearMatrixSource();
extern void cLNormal3DWrap_Slot_SetMatrixSource();

/* --- function index (1 fns, .text 0x800AFE00..0x800AFE44) ---
 * [  0] 0x800AFE00 size:0x44    global VfxSlot_SetMatrixSourceEnabled
 */

/* --- forward decls --- */
asm void VfxSlot_SetMatrixSourceEnabled(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_SetMatrixSourceEnabled[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_SetMatrixSourceEnabled = {
    (void *)&VfxSlot_SetMatrixSourceEnabled, 0x00000044, (void *)extab_VfxSlot_SetMatrixSourceEnabled
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_SetMatrixSourceEnabled(void) { /* 0x800AFE00 size:0x44 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    mr r5, r3
    stw r0, 0x14(r1)
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq VfxSlot_SetMatrixSourceEnabled_L_800AFE34
    extsb. r0, r4
    beq VfxSlot_SetMatrixSourceEnabled_L_800AFE30
    addi r4, r5, 0x34
    bl cLNormal3DWrap_Slot_SetMatrixSource
    b VfxSlot_SetMatrixSourceEnabled_L_800AFE34
    VfxSlot_SetMatrixSourceEnabled_L_800AFE30:
    bl cLNormal3DWrap_Slot_ClearMatrixSource
    VfxSlot_SetMatrixSourceEnabled_L_800AFE34:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
