/* === extracted from auto_VfxSlot_BindResource_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GetSpawnPosition();
extern void cLNormal3DWrap_Mgr_AcquireSlot();
extern void cLNormal3DWrap_Slot_SetAnimSpeed();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D14A8;
extern unsigned int lbl_806D4FF8;
extern unsigned int lbl_806D5008;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int VfxSlot_RegisterDraw[];

/* --- function index (1 fns, .text 0x800B02CC..0x800B0378) ---
 * [  0] 0x800B02CC size:0xAC    global VfxSlot_BindResource
 */

/* --- forward decls --- */
asm void VfxSlot_BindResource(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_VfxSlot_BindResource[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_VfxSlot_BindResource = {
    (void *)&VfxSlot_BindResource, 0x000000AC, (void *)extab_VfxSlot_BindResource
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_BindResource(void) { /* 0x800B02CC size:0xAC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r5, 0x1
    stw r0, 0x14(r1)
    li r0, 0x0
    stw r31, 0xc(r1)
    mr r31, r3
    stb r0, 0x0(r3)
    li r0, 0x11
    mr r3, r4
    clrlwi r4, r4, 24
    stb r0, 0x1(r31)
    stb r3, 0x8(r31)
    lwz r3, lbl_806D14A8(r13)
    bl cLNormal3DWrap_Mgr_AcquireSlot
    stw r3, 0x4(r31)
    lfs f1, lbl_806D4FF8(r2)
    lwz r3, 0x4(r31)
    bl cLNormal3DWrap_Slot_SetAnimSpeed
    lfs f1, lbl_806D5008(r2)
    li r0, 0x1
    addi r3, r31, 0x1c
    stfs f1, 0x10(r31)
    fmr f2, f1
    fmr f3, f1
    stb r0, 0x14(r31)
    stfs f1, 0x18(r31)
    bl GetSpawnPosition
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    beq VfxSlot_BindResource_L_800B0358
    li r0, 0x0
    lfs f0, lbl_806D4FF8(r2)
    stb r0, 0xa(r31)
    stfs f0, 0xc(r31)
    VfxSlot_BindResource_L_800B0358:
    lis r3, VfxSlot_RegisterDraw@ha
    addi r0, r3, VfxSlot_RegisterDraw@l
    stw r0, 0x64(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
