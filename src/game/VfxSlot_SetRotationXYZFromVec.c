/* === extracted from auto_VfxSlot_SetRotationX_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void cLNormal3DWrap_Slot_SetRotationXYZ();

/* --- function index (1 fns, .text 0x800AFED0..0x800AFF08) ---
 * [  0] 0x800AFED0 size:0x38    global VfxSlot_SetRotationXYZFromVec
 */

/* --- forward decls --- */
asm void VfxSlot_SetRotationXYZFromVec(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_SetRotationXYZFromVec[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_SetRotationXYZFromVec = {
    (void *)&VfxSlot_SetRotationXYZFromVec, 0x00000038, (void *)extab_VfxSlot_SetRotationXYZFromVec
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_SetRotationXYZFromVec(void) { /* 0x800AFED0 size:0x38 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq VfxSlot_SetRotationXYZFromVec_L_800AFEF8
    lfs f1, 0x0(r4)
    lfs f2, 0x4(r4)
    lfs f3, 0x8(r4)
    bl cLNormal3DWrap_Slot_SetRotationXYZ
    VfxSlot_SetRotationXYZFromVec_L_800AFEF8:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
