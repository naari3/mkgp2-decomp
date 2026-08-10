/* === extracted from auto_ItemObjectManager_Re_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DbgScene_CopyMatrix3x4Transpose();
extern void Item_ProbeForwardGroundPitch();
extern void Item_ProbeLateralGroundPitch();
extern void Matrix4_Identity();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotZ();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_Translate();
extern void Object_BindMatrixSource();
extern void Object_DriveAnimMatrix();
extern void Object_RenderJObjTree();
extern void Object_SetColorRGBA();
extern void SpriteSlot_RegisterDraw();
extern void Terrain_ApplyCup2FlagPatch();
extern void Terrain_FlagsToTypeId();
extern void Terrain_GetGroundHeightWithPenetration();
extern void fn_801375D8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5A84;
extern unsigned int lbl_806D5A8C;
extern unsigned int lbl_806D5A90;
extern unsigned int lbl_806D5AA0;
extern unsigned int lbl_806D5AA4;
extern unsigned int lbl_806D5AA8;
extern unsigned int lbl_806D5AAC;
extern unsigned int lbl_806D5AB0;

/* --- function index (1 fns, .text 0x800D8288..0x800D85B8) ---
 * [  0] 0x800D8288 size:0x330   global ItemObjectManager_RenderImpl
 */

/* --- forward decls --- */
asm void ItemObjectManager_RenderImpl(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemObjectManager_RenderImpl[8] = {
    0x19, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemObjectManager_RenderImpl = {
    (void *)&ItemObjectManager_RenderImpl, 0x00000330, (void *)extab_ItemObjectManager_RenderImpl
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemObjectManager_RenderImpl(void) { /* 0x800D8288 size:0x330 */
    nofralloc
    stwu r1, -0x100(r1)
    mflr r0
    stw r0, 0x104(r1)
    stfd f31, 0xf0(r1)
    psq_st f31, 0xf8(r1), 0, 0
    stfd f30, 0xe0(r1)
    psq_st f30, 0xe8(r1), 0, 0
    stfd f29, 0xd0(r1)
    psq_st f29, 0xd8(r1), 0, 0
    stfd f28, 0xc0(r1)
    psq_st f28, 0xc8(r1), 0, 0
    stw r31, 0xbc(r1)
    stw r30, 0xb8(r1)
    stw r29, 0xb4(r1)
    mr r29, r3
    li r30, 0x0
    mr r31, r29
    ItemObjectManager_RenderImpl_L_800D82CC:
    lbz r0, 0x0(r31)
    extsb. r0, r0
    beq ItemObjectManager_RenderImpl_L_800D856C
    lbz r0, 0x14(r31)
    clrlwi. r0, r0, 31
    beq ItemObjectManager_RenderImpl_L_800D82F0
    li r0, 0x1
    stb r0, 0xdc(r31)
    b ItemObjectManager_RenderImpl_L_800D8300
    ItemObjectManager_RenderImpl_L_800D82F0:
    lfs f1, 0xd8(r31)
    addi r3, r31, 0xcc
    bl fn_801375D8
    stb r3, 0xdc(r31)
    ItemObjectManager_RenderImpl_L_800D8300:
    lbz r0, 0xdc(r31)
    extsb. r0, r0
    beq ItemObjectManager_RenderImpl_L_800D8348
    lwz r12, 0x78(r31)
    cmplwi r12, 0x0
    beq ItemObjectManager_RenderImpl_L_800D8340
    lwz r3, 0x7c(r31)
    cmplwi r3, 0x0
    beq ItemObjectManager_RenderImpl_L_800D8330
    mtctr r12
    bctrl
    b ItemObjectManager_RenderImpl_L_800D8348
    ItemObjectManager_RenderImpl_L_800D8330:
    addi r3, r31, 0x14
    mtctr r12
    bctrl
    b ItemObjectManager_RenderImpl_L_800D8348
    ItemObjectManager_RenderImpl_L_800D8340:
    addi r3, r31, 0x14
    bl SpriteSlot_RegisterDraw
    ItemObjectManager_RenderImpl_L_800D8348:
    addis r3, r29, 0x2
    lwz r0, -0x1400(r3)
    cmplwi r0, 0x0
    beq ItemObjectManager_RenderImpl_L_800D856C
    lbz r0, 0xdc(r31)
    extsb. r0, r0
    beq ItemObjectManager_RenderImpl_L_800D856C
    lbz r0, 0x28(r31)
    extsb. r0, r0
    beq ItemObjectManager_RenderImpl_L_800D856C
    lbz r0, 0x3c(r31)
    extsb. r0, r0
    beq ItemObjectManager_RenderImpl_L_800D856C
    lfs f28, 0xd0(r31)
    li r0, 0x0
    lwz r6, 0xcc(r31)
    addi r3, r1, 0x34
    lwz r7, 0xd0(r31)
    addi r4, r31, 0xd0
    lfs f1, lbl_806D5A84(r2)
    addi r5, r1, 0x8
    stw r6, 0x34(r1)
    addi r6, r1, 0xc
    stw r7, 0x38(r1)
    lwz r7, 0xd4(r31)
    stw r7, 0x3c(r1)
    stw r0, 0x8(r1)
    bl Terrain_GetGroundHeightWithPenetration
    clrlwi. r0, r3, 24
    bne ItemObjectManager_RenderImpl_L_800D83C8
    li r0, 0x0
    b ItemObjectManager_RenderImpl_L_800D83DC
    ItemObjectManager_RenderImpl_L_800D83C8:
    lwz r3, 0xc(r1)
    bl Terrain_ApplyCup2FlagPatch
    stw r3, 0xc(r1)
    bl Terrain_FlagsToTypeId
    extsb r0, r3
    ItemObjectManager_RenderImpl_L_800D83DC:
    extsb. r0, r0
    beq ItemObjectManager_RenderImpl_L_800D856C
    lfs f0, 0xd0(r31)
    lfs f2, lbl_806D5AA4(r2)
    fsubs f5, f28, f0
    lfs f4, lbl_806D5AA0(r2)
    lfs f3, 0xd8(r31)
    lfs f1, lbl_806D5A8C(r2)
    fsubs f0, f2, f5
    fmuls f3, f4, f3
    fdivs f0, f0, f2
    fmuls f29, f3, f0
    fcmpo cr0, f1, f29
    bge ItemObjectManager_RenderImpl_L_800D856C
    lfs f2, lbl_806D5AA8(r2)
    lfs f0, lbl_806D5A90(r2)
    fnmsubs f28, f2, f5, f0
    fcmpo cr0, f1, f28
    bge ItemObjectManager_RenderImpl_L_800D856C
    lwz r4, 0xcc(r31)
    fmr f3, f1
    lwz r0, 0xd0(r31)
    addi r3, r1, 0x28
    lfs f2, lbl_806D5AAC(r2)
    stw r4, 0x28(r1)
    stw r0, 0x2c(r1)
    lwz r0, 0xd4(r31)
    stw r0, 0x30(r1)
    bl Item_ProbeForwardGroundPitch
    lwz r4, 0xcc(r31)
    fmr f31, f1
    lwz r0, 0xd0(r31)
    addi r3, r1, 0x1c
    lfs f1, lbl_806D5A8C(r2)
    stw r4, 0x1c(r1)
    fmr f3, f1
    lfs f2, lbl_806D5AAC(r2)
    stw r0, 0x20(r1)
    lwz r0, 0xd4(r31)
    stw r0, 0x24(r1)
    bl Item_ProbeLateralGroundPitch
    lfs f2, 0xd0(r31)
    addis r3, r29, 0x2
    lfs f0, lbl_806D5A90(r2)
    fmr f30, f1
    addi r4, r1, 0x80
    li r5, 0x0
    fadds f0, f2, f0
    stfs f0, 0xd0(r31)
    lwz r3, -0x1400(r3)
    bl Object_BindMatrixSource
    addi r3, r1, 0x40
    bl Matrix4_Identity
    addi r3, r1, 0x40
    lfs f1, lbl_806D5AB0(r2)
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    fmr f1, f29
    addi r3, r1, 0x40
    mr r4, r3
    bl Mtx44_Scale_Uniform
    fmr f1, f30
    addi r3, r1, 0x40
    mr r4, r3
    bl Matrix4_PreMultiplyRotZ
    fmr f1, f31
    addi r3, r1, 0x40
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    lwz r6, 0xcc(r31)
    addi r3, r1, 0x40
    lwz r0, 0xd0(r31)
    mr r4, r3
    addi r5, r1, 0x10
    stw r6, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xd4(r31)
    stw r0, 0x18(r1)
    bl Mtx44_Translate
    addi r3, r1, 0x80
    addi r4, r1, 0x40
    bl DbgScene_CopyMatrix3x4Transpose
    addis r3, r29, 0x2
    lwz r3, -0x1400(r3)
    bl Object_DriveAnimMatrix
    lfs f2, lbl_806D5AA0(r2)
    addis r3, r29, 0x2
    lfs f0, 0x2c(r31)
    li r4, 0x0
    lfs f1, lbl_806D5A8C(r2)
    fmuls f0, f2, f0
    lwz r3, -0x1400(r3)
    fmr f2, f1
    fmr f3, f1
    fmuls f4, f28, f0
    bl Object_SetColorRGBA
    addis r3, r29, 0x2
    li r4, 0x7
    lwz r3, -0x1400(r3)
    bl Object_RenderJObjTree
    ItemObjectManager_RenderImpl_L_800D856C:
    addi r30, r30, 0x1
    addi r31, r31, 0x1ec
    cmpwi r30, 0x100
    blt ItemObjectManager_RenderImpl_L_800D82CC
    psq_l f31, 0xf8(r1), 0, 0
    lfd f31, 0xf0(r1)
    psq_l f30, 0xe8(r1), 0, 0
    lfd f30, 0xe0(r1)
    psq_l f29, 0xd8(r1), 0, 0
    lfd f29, 0xd0(r1)
    psq_l f28, 0xc8(r1), 0, 0
    lfd f28, 0xc0(r1)
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    lwz r0, 0x104(r1)
    lwz r29, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0x100
    blr
}

