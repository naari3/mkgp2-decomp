/* === extracted from auto_VfxSlot_SetScaleUnif_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void cLNormal3DWrap_Slot_SetScaleVec3();

/* --- function index (1 fns, .text 0x800AFE70..0x800AFEA4) ---
 * [  0] 0x800AFE70 size:0x34    global VfxSlot_SetScaleUniform
 */

/* --- forward decls --- */
asm void VfxSlot_SetScaleUniform(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_SetScaleUniform[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_SetScaleUniform = {
    (void *)&VfxSlot_SetScaleUniform, 0x00000034, (void *)extab_VfxSlot_SetScaleUniform
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_SetScaleUniform(void) { /* 0x800AFE70 size:0x34 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq VfxSlot_SetScaleUniform_L_800AFE94
    fmr f2, f1
    fmr f3, f1
    bl cLNormal3DWrap_Slot_SetScaleVec3
    VfxSlot_SetScaleUniform_L_800AFE94:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
