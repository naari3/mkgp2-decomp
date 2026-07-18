/* === extracted from auto_VfxSlot_BindResource_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GetSpawnPosition();
extern void cLNormal3DWrap_Mgr_AcquireSlot();
extern void cLNormal3DWrap_Slot_SetAnimSpeed();
extern void cLNormal3DWrap_Slot_SetRenderFlags();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D14A8;
extern unsigned int lbl_806D4FF8;
extern unsigned int lbl_806D5008;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int VfxSlot_RegisterDraw[];

/* --- function index (1 fns, .text 0x800B0378..0x800B0454) ---
 * [  0] 0x800B0378 size:0xDC    global VfxSlot_BindResourceEx
 */

/* --- forward decls --- */
asm void VfxSlot_BindResourceEx(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_BindResourceEx[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_BindResourceEx = {
    (void *)&VfxSlot_BindResourceEx, 0x000000DC, (void *)extab_VfxSlot_BindResourceEx
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_BindResourceEx(void) { /* 0x800B0378 size:0xDC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    li r0, 0x0
    stw r31, 0xc(r1)
    mr. r31, r5
    stw r30, 0x8(r1)
    mr r30, r3
    stb r0, 0x0(r3)
    bne VfxSlot_BindResourceEx_L_800B03AC
    li r0, 0x10
    stb r0, 0x1(r30)
    b VfxSlot_BindResourceEx_L_800B03B4
    VfxSlot_BindResourceEx_L_800B03AC:
    li r0, 0x11
    stb r0, 0x1(r30)
    VfxSlot_BindResourceEx_L_800B03B4:
    stb r4, 0x8(r30)
    clrlwi r4, r4, 24
    li r5, 0x1
    lwz r3, lbl_806D14A8(r13)
    bl cLNormal3DWrap_Mgr_AcquireSlot
    stw r3, 0x4(r30)
    cmpwi r31, 0x0
    lwz r31, 0x4(r30)
    bne VfxSlot_BindResourceEx_L_800B03E4
    mr r3, r31
    li r4, 0x800
    bl cLNormal3DWrap_Slot_SetRenderFlags
    VfxSlot_BindResourceEx_L_800B03E4:
    lfs f1, lbl_806D4FF8(r2)
    mr r3, r31
    bl cLNormal3DWrap_Slot_SetAnimSpeed
    lfs f1, lbl_806D5008(r2)
    li r0, 0x1
    addi r3, r30, 0x1c
    stfs f1, 0x10(r30)
    fmr f2, f1
    fmr f3, f1
    stb r0, 0x14(r30)
    stfs f1, 0x18(r30)
    bl GetSpawnPosition
    lwz r0, 0x4(r30)
    cmplwi r0, 0x0
    beq VfxSlot_BindResourceEx_L_800B0430
    li r0, 0x0
    lfs f0, lbl_806D4FF8(r2)
    stb r0, 0xa(r30)
    stfs f0, 0xc(r30)
    VfxSlot_BindResourceEx_L_800B0430:
    lis r3, VfxSlot_RegisterDraw@ha
    addi r0, r3, VfxSlot_RegisterDraw@l
    stw r0, 0x64(r30)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
