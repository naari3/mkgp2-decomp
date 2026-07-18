/* === extracted from auto_VfxSlot_Release_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void cLNormal3DWrap_Mgr_ReleaseSlot();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D14A8;

/* --- function index (1 fns, .text 0x800AFF9C..0x800AFFE0) ---
 * [  0] 0x800AFF9C size:0x44    global VfxSlot_Release
 */

/* --- forward decls --- */
asm void VfxSlot_Release(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_Release[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_Release = {
    (void *)&VfxSlot_Release, 0x00000044, (void *)extab_VfxSlot_Release
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_Release(void) { /* 0x800AFF9C size:0x44 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r4, 0x4(r3)
    cmplwi r4, 0x0
    beq VfxSlot_Release_L_800AFFCC
    lwz r3, lbl_806D14A8(r13)
    bl cLNormal3DWrap_Mgr_ReleaseSlot
    li r0, 0x0
    stw r0, 0x4(r31)
    VfxSlot_Release_L_800AFFCC:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
