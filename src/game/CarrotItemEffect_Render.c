/* === extracted from auto_CarrotItemEffect_Ren_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_ApplyScissor();
extern void CObj_GetProjMatrix_Cached();
extern void CObj_LoadProjMatrix();
extern void DbgGx_BP1009_SetN();
extern void DbgGx_GenModeTail7();
extern void DbgGx_Xfreg100A_Set3();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void GXSetTexCoordGen2();
extern void GX_Begin();
extern void GX_ClearVtxDesc();
extern void GX_LoadPosMtxImm();
extern void GX_SetBlendMode();
extern void GX_SetCullMode();
extern void GX_SetCurrentMtx();
extern void GX_SetNumChans();
extern void GX_SetNumTevStages();
extern void GX_SetTevOrder();
extern void GX_SetTevPreset();
extern void GX_SetVtxAttrFmt();
extern void GX_SetVtxDesc();
extern void GetSpawnPosition();
extern void Matrix4_Identity();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotY();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_TransformVec3();
extern void Mtx44_Translate();
extern void Object_BindMatrixSource();
extern void Object_DriveAnimMatrix();
extern void Object_RenderJObjTree();
extern void Vec3_Copy();
extern void Vec3_HorizontalYawTo();
extern void Vec3_PitchTo();
extern void fn_8011D890();
extern void fn_80231B74();
extern void fn_8025DF40();
extern void fn_8026951C();
extern void fn_802C14B8();
extern void fn_802C7E30();
extern void fn_802C8510();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_courseScene3D;
extern unsigned int lbl_806D5020;
extern unsigned int lbl_806D5024;
extern unsigned int lbl_806D5028;
extern unsigned int lbl_806D509C;
extern unsigned int lbl_806D50A0;
extern unsigned int lbl_806D50D4;
extern unsigned int lbl_806D50D8;
extern unsigned int lbl_806D50DC;
extern unsigned int lbl_806D50E0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80328EB8[];

/* --- function index (1 fns, .text 0x800B23CC..0x800B2A64) ---
 * [  0] 0x800B23CC size:0x698   global CarrotItemEffect_Render
 */

/* --- forward decls --- */
asm void CarrotItemEffect_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CarrotItemEffect_Render[8] = {
    0x51, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CarrotItemEffect_Render = {
    (void *)&CarrotItemEffect_Render, 0x00000698, (void *)extab_CarrotItemEffect_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CarrotItemEffect_Render(void) { /* 0x800B23CC size:0x698 */
    nofralloc
    stwu r1, -0x410(r1)
    mflr r0
    stw r0, 0x414(r1)
    stfd f31, 0x400(r1)
    psq_st f31, 0x408(r1), 0, 0
    stfd f30, 0x3f0(r1)
    psq_st f30, 0x3f8(r1), 0, 0
    stfd f29, 0x3e0(r1)
    psq_st f29, 0x3e8(r1), 0, 0
    stfd f28, 0x3d0(r1)
    psq_st f28, 0x3d8(r1), 0, 0
    stfd f27, 0x3c0(r1)
    psq_st f27, 0x3c8(r1), 0, 0
    stfd f26, 0x3b0(r1)
    psq_st f26, 0x3b8(r1), 0, 0
    stfd f25, 0x3a0(r1)
    psq_st f25, 0x3a8(r1), 0, 0
    stmw r22, 0x378(r1)
    mr r22, r3
    addi r25, r1, 0x104
    addi r23, r22, 0xec
    addi r26, r1, 0x1c4
    lis r3, lbl_80328EB8@ha
    lfs f27, lbl_806D509C(r2)
    lfs f28, lbl_806D5020(r2)
    mr r29, r23
    lfs f29, lbl_806D50A0(r2)
    mr r28, r25
    lfs f30, lbl_806D5024(r2)
    mr r27, r26
    lfs f31, lbl_806D5028(r2)
    addi r31, r3, lbl_80328EB8@l
    addi r30, r1, 0x78
    li r24, 0x0
    CarrotItemEffect_Render_L_800B2454:
    lwz r5, 0x530(r31)
    addi r3, r1, 0x6c
    lwz r4, 0x534(r31)
    lwz r0, 0x538(r31)
    stw r5, 0x78(r1)
    lfs f1, 0x20(r29)
    stw r4, 0x7c(r1)
    lfs f2, 0x24(r29)
    stw r0, 0x80(r1)
    lfs f3, 0x0(r30)
    bl GetSpawnPosition
    lwz r0, 0x6c(r1)
    lwz r3, 0x70(r1)
    stw r0, 0x50(r1)
    lwz r0, 0x74(r1)
    stw r3, 0x54(r1)
    lfs f1, 0x50(r1)
    lfs f0, 0x54(r1)
    stw r0, 0x58(r1)
    fsubs f2, f1, f28
    fsubs f1, f0, f30
    lwz r3, g_courseScene3D(r13)
    lfs f0, 0x58(r1)
    fmuls f2, f27, f2
    fmuls f1, f29, f1
    fsubs f0, f0, f31
    stfs f2, 0x20(r1)
    stfs f1, 0x24(r1)
    stfs f0, 0x28(r1)
    bl CObj_GetProjMatrix_Cached
    addi r4, r1, 0x20
    mr r5, r4
    bl fn_8025DF40
    addi r3, r1, 0x6c
    addi r4, r1, 0x20
    bl Vec3_Copy
    lwz r3, g_courseScene3D(r13)
    addi r4, r1, 0x8
    bl CObj_LoadProjMatrix
    lwz r3, g_courseScene3D(r13)
    addi r4, r1, 0x14
    bl CObj_ApplyScissor
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    bl Vec3_PitchTo
    fmr f26, f1
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    bl Vec3_HorizontalYawTo
    fmr f25, f1
    mr r3, r28
    bl Matrix4_Identity
    lfs f1, lbl_806D50D4(r2)
    mr r3, r28
    mr r4, r28
    bl Mtx44_Scale_Uniform
    fmr f1, f26
    mr r3, r28
    mr r4, r28
    bl Matrix4_PreMultiplyRotX
    fmr f1, f25
    mr r3, r28
    mr r4, r28
    bl Matrix4_PreMultiplyRotY
    lwz r7, 0x6c(r1)
    mr r3, r28
    lwz r6, 0x70(r1)
    mr r4, r28
    lwz r0, 0x74(r1)
    addi r5, r1, 0x44
    stw r7, 0x44(r1)
    stw r6, 0x48(r1)
    stw r0, 0x4c(r1)
    bl Mtx44_Translate
    mr r3, r27
    mr r4, r28
    bl DbgScene_CopyMatrix3x4Transpose
    addi r24, r24, 0x1
    addi r29, r29, 0x8
    cmpwi r24, 0x3
    addi r28, r28, 0x40
    addi r27, r27, 0x30
    addi r30, r30, 0x4
    blt CarrotItemEffect_Render_L_800B2454
    li r24, 0x0
    CarrotItemEffect_Render_L_800B25A8:
    lwz r3, 0x18(r22)
    mr r4, r26
    li r5, 0x0
    bl Object_BindMatrixSource
    lwz r3, 0x18(r22)
    bl Object_DriveAnimMatrix
    lwz r3, 0x18(r22)
    li r4, 0x7
    bl Object_RenderJObjTree
    addi r24, r24, 0x1
    addi r26, r26, 0x30
    cmpwi r24, 0x3
    blt CarrotItemEffect_Render_L_800B25A8
    bl fn_802C8510
    cmplwi r3, 0x0
    bne CarrotItemEffect_Render_L_800B25F0
    li r0, 0x0
    b CarrotItemEffect_Render_L_800B2730
    CarrotItemEffect_Render_L_800B25F0:
    bl fn_802C7E30
    li r4, 0x0
    bl GX_LoadPosMtxImm
    li r3, 0x0
    bl GX_SetCurrentMtx
    li r3, 0x4
    li r4, 0x0
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl fn_8026951C
    li r3, 0x4
    li r4, 0x0
    li r5, 0x1
    li r6, 0x1
    li r7, 0x0
    li r8, 0x0
    li r9, 0x2
    bl DbgGx_GenModeTail7
    li r3, 0x0
    bl GX_SetCullMode
    li r3, 0x1
    li r4, 0x3
    li r5, 0x1
    bl DbgGx_Xfreg100A_Set3
    li r3, 0x1
    li r4, 0x4
    li r5, 0x5
    li r6, 0xf
    bl GX_SetBlendMode
    li r3, 0x1
    bl GX_SetNumTevStages
    li r3, 0x0
    li r4, 0x1
    li r5, 0x4
    li r6, 0x3c
    li r7, 0x0
    li r8, 0x7d
    bl GXSetTexCoordGen2
    li r3, 0x1
    bl DbgGx_BP1009_SetN
    li r3, 0x1
    bl GX_SetNumChans
    li r3, 0x0
    li r4, 0x0
    li r5, 0x0
    li r6, 0x4
    bl GX_SetTevOrder
    li r3, 0x0
    li r4, 0x0
    bl GX_SetTevPreset
    bl GX_ClearVtxDesc
    li r3, 0x9
    li r4, 0x1
    bl GX_SetVtxDesc
    li r3, 0x0
    li r4, 0x9
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GX_SetVtxAttrFmt
    li r3, 0xb
    li r4, 0x1
    bl GX_SetVtxDesc
    li r3, 0x0
    li r4, 0xb
    li r5, 0x1
    li r6, 0x5
    li r7, 0x0
    bl GX_SetVtxAttrFmt
    li r3, 0xd
    li r4, 0x1
    bl GX_SetVtxDesc
    li r3, 0x0
    li r4, 0xd
    li r5, 0x1
    li r6, 0x4
    li r7, 0x0
    bl GX_SetVtxAttrFmt
    li r0, 0x1
    CarrotItemEffect_Render_L_800B2730:
    clrlwi. r0, r0, 24
    beq CarrotItemEffect_Render_L_800B2A18
    li r0, 0xc
    addi r5, r1, 0xa0
    addi r4, r31, 0x538
    mtctr r0
    CarrotItemEffect_Render_L_800B2748:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz CarrotItemEffect_Render_L_800B2748
    lwz r0, 0xc(r23)
    lwz r9, 0x59c(r31)
    lwz r8, 0x5a0(r31)
    cmpwi r0, -0x1
    lwz r7, 0x5a4(r31)
    lwz r6, 0x5a8(r31)
    lwz r5, 0x5ac(r31)
    lwz r4, 0x5b0(r31)
    lwz r3, 0x5b4(r31)
    lwz r0, 0x5b8(r31)
    stw r9, 0x84(r1)
    stw r8, 0x88(r1)
    stw r7, 0x8c(r1)
    stw r6, 0x90(r1)
    stw r5, 0x94(r1)
    stw r4, 0x98(r1)
    stw r3, 0x9c(r1)
    stw r0, 0xa0(r1)
    beq CarrotItemEffect_Render_L_800B2878
    lwz r3, 0x8(r23)
    bl fn_80231B74
    clrlwi. r0, r3, 24
    bne CarrotItemEffect_Render_L_800B27F0
    lfs f0, 0xa8(r1)
    lfs f4, lbl_806D50D8(r2)
    lfs f2, 0xb4(r1)
    lfs f1, 0xc0(r1)
    fadds f3, f0, f4
    lfs f0, 0xcc(r1)
    fadds f2, f2, f4
    fadds f1, f1, f4
    fadds f0, f0, f4
    stfs f3, 0xa8(r1)
    stfs f2, 0xb4(r1)
    stfs f1, 0xc0(r1)
    stfs f0, 0xcc(r1)
    b CarrotItemEffect_Render_L_800B2878
    CarrotItemEffect_Render_L_800B27F0:
    lfs f12, lbl_806D50DC(r2)
    lfs f0, 0xa8(r1)
    lfs f2, 0xb4(r1)
    lfs f1, 0xc0(r1)
    fmuls f10, f0, f12
    lfs f0, 0xcc(r1)
    fmuls f3, f2, f12
    lfs f9, lbl_806D50E0(r2)
    fmuls f4, f1, f12
    fmuls f1, f0, f12
    lfs f7, 0xa4(r1)
    fsubs f8, f10, f9
    lfs f5, 0xb0(r1)
    fsubs f6, f3, f9
    lfs f2, 0xbc(r1)
    lfs f0, 0xc8(r1)
    fmuls f11, f7, f12
    fmuls f7, f5, f12
    stfs f10, 0xa8(r1)
    fmuls f5, f2, f12
    fmuls f2, f0, f12
    stfs f3, 0xb4(r1)
    fsubs f3, f4, f9
    stfs f4, 0xc0(r1)
    fsubs f0, f1, f9
    stfs f1, 0xcc(r1)
    stfs f11, 0xa4(r1)
    stfs f8, 0xa8(r1)
    stfs f7, 0xb0(r1)
    stfs f6, 0xb4(r1)
    stfs f5, 0xbc(r1)
    stfs f3, 0xc0(r1)
    stfs f2, 0xc8(r1)
    stfs f0, 0xcc(r1)
    CarrotItemEffect_Render_L_800B2878:
    addi r26, r1, 0x254
    li r28, 0x0
    CarrotItemEffect_Render_L_800B2880:
    mr r24, r26
    addi r22, r1, 0xa4
    li r27, 0x0
    CarrotItemEffect_Render_L_800B288C:
    lwz r7, 0x0(r22)
    mr r3, r24
    lwz r6, 0x4(r22)
    mr r4, r25
    lwz r0, 0x8(r22)
    addi r5, r1, 0x38
    stw r7, 0x38(r1)
    stw r6, 0x3c(r1)
    stw r0, 0x40(r1)
    bl Mtx44_TransformVec3
    lwz r7, 0x30(r22)
    mr r4, r25
    lwz r6, 0x34(r22)
    addi r3, r24, 0x90
    lwz r0, 0x38(r22)
    addi r5, r1, 0x2c
    stw r7, 0x2c(r1)
    stw r6, 0x30(r1)
    stw r0, 0x34(r1)
    bl Mtx44_TransformVec3
    addi r27, r27, 0x1
    addi r24, r24, 0xc
    cmpwi r27, 0x4
    addi r22, r22, 0xc
    blt CarrotItemEffect_Render_L_800B288C
    addi r28, r28, 0x1
    addi r25, r25, 0x40
    cmpwi r28, 0x3
    addi r26, r26, 0x30
    blt CarrotItemEffect_Render_L_800B2880
    addi r25, r23, 0x4
    addi r26, r1, 0x2e4
    li r27, 0x1
    CarrotItemEffect_Render_L_800B2910:
    lwz r3, 0x8(r25)
    cmpwi r3, -0x1
    beq CarrotItemEffect_Render_L_800B2A00
    addi r4, r1, 0x5c
    li r5, 0x0
    bl fn_8011D890
    clrlwi. r0, r3, 24
    beq CarrotItemEffect_Render_L_800B2A18
    mr r24, r26
    addi r22, r1, 0x5c
    li r28, 0x0
    lis r23, 0xcc01
    CarrotItemEffect_Render_L_800B2940:
    li r3, 0x80
    li r4, 0x0
    li r5, 0x4
    bl GX_Begin
    li r0, 0x2
    mr r7, r24
    addi r8, r1, 0x84
    li r6, -0x1
    mtctr r0
    CarrotItemEffect_Render_L_800B2964:
    lfs f0, 0x0(r7)
    lwz r5, 0x0(r8)
    stfs f0, -0x8000(r23)
    slwi r4, r5, 3
    lwz r3, 0x4(r8)
    lfs f0, 0x4(r7)
    slwi r3, r3, 3
    lwz r5, 0x8(r8)
    stfs f0, -0x8000(r23)
    addi r0, r3, 0x4
    lwz r3, 0xc(r8)
    addi r8, r8, 0x10
    lfs f0, 0x8(r7)
    slwi r3, r3, 3
    stfs f0, -0x8000(r23)
    stw r6, -0x8000(r23)
    lfsx f0, r22, r4
    slwi r4, r5, 3
    stfs f0, -0x8000(r23)
    lfsx f0, r22, r0
    addi r0, r3, 0x4
    stfs f0, -0x8000(r23)
    lfs f0, 0xc(r7)
    stfs f0, -0x8000(r23)
    lfs f0, 0x10(r7)
    stfs f0, -0x8000(r23)
    lfs f0, 0x14(r7)
    addi r7, r7, 0x18
    stfs f0, -0x8000(r23)
    stw r6, -0x8000(r23)
    lfsx f0, r22, r4
    stfs f0, -0x8000(r23)
    lfsx f0, r22, r0
    stfs f0, -0x8000(r23)
    bdnz CarrotItemEffect_Render_L_800B2964
    addi r28, r28, 0x1
    addi r24, r24, 0x30
    cmpwi r28, 0x3
    blt CarrotItemEffect_Render_L_800B2940
    CarrotItemEffect_Render_L_800B2A00:
    subic. r27, r27, 0x1
    subi r26, r26, 0x90
    subi r25, r25, 0x4
    bge CarrotItemEffect_Render_L_800B2910
    li r3, -0x1
    bl fn_802C14B8
    CarrotItemEffect_Render_L_800B2A18:
    psq_l f31, 0x408(r1), 0, 0
    lfd f31, 0x400(r1)
    psq_l f30, 0x3f8(r1), 0, 0
    lfd f30, 0x3f0(r1)
    psq_l f29, 0x3e8(r1), 0, 0
    lfd f29, 0x3e0(r1)
    psq_l f28, 0x3d8(r1), 0, 0
    lfd f28, 0x3d0(r1)
    psq_l f27, 0x3c8(r1), 0, 0
    lfd f27, 0x3c0(r1)
    psq_l f26, 0x3b8(r1), 0, 0
    lfd f26, 0x3b0(r1)
    psq_l f25, 0x3a8(r1), 0, 0
    lfd f25, 0x3a0(r1)
    lmw r22, 0x378(r1)
    lwz r0, 0x414(r1)
    mtlr r0
    addi r1, r1, 0x410
    blr
}
