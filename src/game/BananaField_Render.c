/* === extracted from auto_BananaField_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void LUT_Sin12Bit();
extern void LookupCos();
extern void LookupSin();
extern void Object_RenderJObjTree();
extern void Object_SetColorAlphaOnly();
extern void Object_SetJObjPositionXYZ();
extern void Object_SetJObjRotationX();
extern void Object_SetJObjRotationZ();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D95B8;
extern unsigned int lbl_806D95BC;
extern unsigned int lbl_806D95C0;
extern unsigned int lbl_806D95C4;
extern unsigned int lbl_806D95C8;
extern unsigned int lbl_806D95CC;
extern unsigned int lbl_806D95D0;
extern unsigned int lbl_806D95D4;

/* --- function index (1 fns, .text 0x80196AA0..0x80196C5C) ---
 * [  0] 0x80196AA0 size:0x1BC   global BananaField_Render
 */

/* --- forward decls --- */
asm void BananaField_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BananaField_Render[8] = {
    0x18, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BananaField_Render = {
    (void *)&BananaField_Render, 0x000001BC, (void *)extab_BananaField_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BananaField_Render(void) { /* 0x80196AA0 size:0x1BC */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r3, 0x0(r3)
    cmplwi r3, 0x0
    beq BananaField_Render_L_80196C38
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    beq BananaField_Render_L_80196C38
    lwz r0, 0x8(r29)
    cmpwi r0, 0x0
    bne BananaField_Render_L_80196AEC
    b BananaField_Render_L_80196C38
    BananaField_Render_L_80196AEC:
    lfs f1, lbl_806D95B8(r2)
    bl Object_SetJObjRotationX
    lwz r3, 0x0(r29)
    lfs f1, lbl_806D95B8(r2)
    bl Object_SetJObjRotationZ
    lwz r3, 0x0(r29)
    li r4, 0x0
    lfs f1, lbl_806D95BC(r2)
    bl Object_SetColorAlphaOnly
    lwz r30, 0x4(r29)
    lfs f31, lbl_806D95C0(r2)
    b BananaField_Render_L_80196B50
    BananaField_Render_L_80196B1C:
    lwz r0, 0x0(r30)
    cmpwi r0, 0x0
    bne BananaField_Render_L_80196B4C
    lfs f0, 0x8(r30)
    lwz r3, 0x0(r29)
    fadds f2, f31, f0
    lfs f1, 0x4(r30)
    lfs f3, 0xc(r30)
    bl Object_SetJObjPositionXYZ
    lwz r3, 0x0(r29)
    li r4, 0x7
    bl Object_RenderJObjTree
    BananaField_Render_L_80196B4C:
    addi r30, r30, 0x18
    BananaField_Render_L_80196B50:
    lwz r0, 0x8(r29)
    lwz r31, 0x4(r29)
    mulli r0, r0, 0x18
    add r0, r31, r0
    cmplw r30, r0
    blt BananaField_Render_L_80196B1C
    b BananaField_Render_L_80196C20
    BananaField_Render_L_80196B6C:
    lwz r0, 0x0(r31)
    cmpwi r0, 0x1
    bne BananaField_Render_L_80196C1C
    lfs f1, lbl_806D95C8(r2)
    lfs f0, 0x14(r31)
    fmuls f1, f1, f0
    bl LUT_Sin12Bit
    lfs f2, lbl_806D95C4(r2)
    lfs f0, 0x8(r31)
    lwz r3, 0x0(r29)
    fmadds f2, f2, f1, f0
    lfs f1, 0x4(r31)
    lfs f3, 0xc(r31)
    bl Object_SetJObjPositionXYZ
    lfs f1, 0x10(r31)
    bl LookupCos
    lfs f2, lbl_806D95D0(r2)
    lfs f0, 0x14(r31)
    lfs f3, lbl_806D95CC(r2)
    fmuls f0, f2, f0
    lwz r3, 0x0(r29)
    fmuls f0, f3, f0
    fmuls f1, f0, f1
    bl Object_SetJObjRotationX
    lfs f1, 0x10(r31)
    bl LookupSin
    lfs f2, lbl_806D95D0(r2)
    lfs f0, 0x14(r31)
    lfs f3, lbl_806D95CC(r2)
    fmuls f0, f2, f0
    lwz r3, 0x0(r29)
    fmuls f0, f3, f0
    fmuls f1, f0, f1
    bl Object_SetJObjRotationZ
    lfs f2, lbl_806D95D4(r2)
    li r4, 0x0
    lfs f1, 0x14(r31)
    lfs f0, lbl_806D95BC(r2)
    lwz r3, 0x0(r29)
    fnmsubs f1, f2, f1, f0
    bl Object_SetColorAlphaOnly
    lwz r3, 0x0(r29)
    li r4, 0x7
    bl Object_RenderJObjTree
    BananaField_Render_L_80196C1C:
    addi r31, r31, 0x18
    BananaField_Render_L_80196C20:
    lwz r0, 0x8(r29)
    lwz r3, 0x4(r29)
    mulli r0, r0, 0x18
    add r0, r3, r0
    cmplw r31, r0
    blt BananaField_Render_L_80196B6C
    BananaField_Render_L_80196C38:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
