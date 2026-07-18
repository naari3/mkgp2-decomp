/* === extracted from auto_VfxSlot_RegisterDraw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Vec3_Copy();
extern void cLNormal3DWrap_Slot_GetOrLoadJointTransform();
extern void clDrawMan_AddSorted_DepthRange();
extern void clDrawMan_AddSorted_NoDepthBias();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D4FF8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int VfxSlot_Render[];

/* --- function index (1 fns, .text 0x800AFFE0..0x800B00D8) ---
 * [  0] 0x800AFFE0 size:0xF8    global VfxSlot_RegisterDraw
 */

/* --- forward decls --- */
asm void VfxSlot_RegisterDraw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_RegisterDraw[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_RegisterDraw = {
    (void *)&VfxSlot_RegisterDraw, 0x000000F8, (void *)extab_VfxSlot_RegisterDraw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_RegisterDraw(void) { /* 0x800AFFE0 size:0xF8 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq VfxSlot_RegisterDraw_L_800B00C4
    lbz r0, 0x14(r31)
    extsb. r0, r0
    beq VfxSlot_RegisterDraw_L_800B00C4
    lbz r4, 0x0(r31)
    extsb r4, r4
    rlwinm. r0, r4, 0, 30, 30
    beq VfxSlot_RegisterDraw_L_800B0020
    b VfxSlot_RegisterDraw_L_800B00C4
    VfxSlot_RegisterDraw_L_800B0020:
    lfs f1, 0x18(r31)
    lfs f0, lbl_806D4FF8(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    beq VfxSlot_RegisterDraw_L_800B00C4
    rlwinm. r0, r4, 0, 28, 28
    bne VfxSlot_RegisterDraw_L_800B0048
    addi r4, r1, 0x8
    bl cLNormal3DWrap_Slot_GetOrLoadJointTransform
    b VfxSlot_RegisterDraw_L_800B0054
    VfxSlot_RegisterDraw_L_800B0048:
    addi r3, r1, 0x8
    addi r4, r31, 0x6c
    bl Vec3_Copy
    VfxSlot_RegisterDraw_L_800B0054:
    lbz r0, 0x0(r31)
    clrlwi. r0, r0, 31
    bne VfxSlot_RegisterDraw_L_800B0094
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne VfxSlot_RegisterDraw_L_800B0070
    li r3, 0x0
    VfxSlot_RegisterDraw_L_800B0070:
    lis r4, VfxSlot_Render@ha
    lfs f1, 0x8(r1)
    lfs f2, 0xc(r1)
    addi r4, r4, VfxSlot_Render@l
    lfs f3, 0x10(r1)
    mr r5, r31
    lfs f4, lbl_806D4FF8(r2)
    bl clDrawMan_AddSorted_DepthRange
    b VfxSlot_RegisterDraw_L_800B00C4
    VfxSlot_RegisterDraw_L_800B0094:
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne VfxSlot_RegisterDraw_L_800B00A4
    li r3, 0x0
    VfxSlot_RegisterDraw_L_800B00A4:
    lis r4, VfxSlot_Render@ha
    lfs f1, 0x8(r1)
    lfs f2, 0xc(r1)
    addi r4, r4, VfxSlot_Render@l
    lfs f3, 0x10(r1)
    mr r5, r31
    lfs f4, lbl_806D4FF8(r2)
    bl clDrawMan_AddSorted_NoDepthBias
    VfxSlot_RegisterDraw_L_800B00C4:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
