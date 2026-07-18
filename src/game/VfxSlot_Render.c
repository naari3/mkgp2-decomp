/* === extracted from auto_VfxSlot_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void cLNormal3DWrap_Slot_AdvanceUVScrollWrapped();
extern void cLNormal3DWrap_Slot_Render();
extern void cLNormal3DWrap_Slot_SetRotationQuat();

/* --- function index (1 fns, .text 0x800B00D8..0x800B013C) ---
 * [  0] 0x800B00D8 size:0x64    global VfxSlot_Render
 */

/* --- forward decls --- */
asm void VfxSlot_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_Render[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_Render = {
    (void *)&VfxSlot_Render, 0x00000064, (void *)extab_VfxSlot_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_Render(void) { /* 0x800B00D8 size:0x64 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r31, 0x4(r3)
    lfs f1, 0x1c(r3)
    lfs f2, 0x20(r3)
    mr r3, r31
    lfs f3, 0x24(r30)
    lfs f4, 0x18(r30)
    bl cLNormal3DWrap_Slot_SetRotationQuat
    lfs f1, 0x2c(r30)
    mr r3, r31
    lfs f2, 0x30(r30)
    bl cLNormal3DWrap_Slot_AdvanceUVScrollWrapped
    mr r3, r31
    bl cLNormal3DWrap_Slot_Render
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
