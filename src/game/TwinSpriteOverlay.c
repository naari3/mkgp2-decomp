/* TwinSpriteOverlay 0x800B1670..0x800B1C88: exact asm_fn bundle. */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AnimState_GetTotalScaleX();
extern void AnimState_GetTotalScaleY();
extern void AnimState_GetTotalWeight();
extern void CObj_ApplyScissor();
extern void CObj_GetProjMatrix_Cached();
extern void CObj_LoadProjMatrix();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void Matrix4_Identity();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotY();
extern void Mtx44_Scale_PerAxis();
extern void Mtx44_Translate();
extern void Vec3_Copy();
extern void Vec3_HorizontalYawTo();
extern void Vec3_PitchTo();
extern void cLNormal3DWrap_Slot_Render();
extern void cLNormal3DWrap_Slot_SetMatrixSource();
extern void cLNormal3DWrap_Slot_SetRotationQuat();
extern void fn_8025DF40();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_courseScene3D;
extern unsigned int lbl_806D5018;
extern unsigned int lbl_806D501C;
extern unsigned int lbl_806D5020;
extern unsigned int lbl_806D5024;
extern unsigned int lbl_806D5028;
extern unsigned int lbl_806D5098;
extern unsigned int lbl_806D509C;
extern unsigned int lbl_806D50A0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80329498[];

/* --- function index (1 fns, .text 0x800B1670..0x800B1964) ---
 * [  0] 0x800B1670 size:0x2F4   global TwinSpriteOverlay_Render
 */

/* --- forward decls --- */
asm void TwinSpriteOverlay_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TwinSpriteOverlay_Render[8] = {
    0x22, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TwinSpriteOverlay_Render = {
    (void *)&TwinSpriteOverlay_Render, 0x000002F4, (void *)extab_TwinSpriteOverlay_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TwinSpriteOverlay_Render(void) { /* 0x800B1670 size:0x2F4 */
    nofralloc
    stwu r1, -0x190(r1)
    mflr r0
    stw r0, 0x194(r1)
    stfd f31, 0x180(r1)
    psq_st f31, 0x188(r1), 0, 0
    stfd f30, 0x170(r1)
    psq_st f30, 0x178(r1), 0, 0
    stfd f29, 0x160(r1)
    psq_st f29, 0x168(r1), 0, 0
    stfd f28, 0x150(r1)
    psq_st f28, 0x158(r1), 0, 0
    stfd f27, 0x140(r1)
    psq_st f27, 0x148(r1), 0, 0
    stfd f26, 0x130(r1)
    psq_st f26, 0x138(r1), 0, 0
    stfd f25, 0x120(r1)
    psq_st f25, 0x128(r1), 0, 0
    stfd f24, 0x110(r1)
    psq_st f24, 0x118(r1), 0, 0
    stfd f23, 0x100(r1)
    psq_st f23, 0x108(r1), 0, 0
    stw r31, 0xfc(r1)
    stw r30, 0xf8(r1)
    stw r29, 0xf4(r1)
    stw r28, 0xf0(r1)
    mr r28, r3
    lwz r30, 0xe0(r3)
    cmplwi r30, 0x0
    beq TwinSpriteOverlay_Render_L_800B18FC
    lwz r3, 0xd0(r28)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Render_L_800B18FC
    lis r5, lbl_80329498@ha
    lwzu r31, lbl_80329498@l(r5)
    lwz r4, lbl_806D5018(r2)
    lwz r0, lbl_806D501C(r2)
    lwz r12, 0x4(r5)
    lwz r11, 0x8(r5)
    lwz r10, 0xc(r5)
    lwz r9, 0x10(r5)
    lwz r8, 0x14(r5)
    lwz r7, 0x18(r5)
    lwz r6, 0x1c(r5)
    lwz r5, 0x20(r5)
    stw r31, 0xc8(r1)
    lwz r31, 0x18(r30)
    stw r12, 0xcc(r1)
    stw r11, 0xd0(r1)
    stw r10, 0xd4(r1)
    stw r9, 0xd8(r1)
    stw r8, 0xdc(r1)
    stw r7, 0xe0(r1)
    stw r6, 0xe4(r1)
    stw r5, 0xe8(r1)
    stw r4, 0x8(r1)
    stw r0, 0xc(r1)
    bl AnimState_GetTotalScaleX
    fmr f27, f1
    lwz r3, 0xd0(r28)
    bl AnimState_GetTotalScaleY
    fmr f26, f1
    lwz r3, 0xd0(r28)
    bl AnimState_GetTotalWeight
    lfs f0, 0x150(r28)
    mr r3, r31
    lfs f5, lbl_806D5098(r2)
    fmuls f4, f1, f0
    lfs f1, lbl_806D5028(r2)
    fmuls f31, f27, f5
    fmr f2, f1
    fmr f3, f1
    fmuls f25, f26, f5
    bl cLNormal3DWrap_Slot_SetRotationQuat
    lfs f26, lbl_806D509C(r2)
    addi r30, r1, 0xc8
    lfs f27, lbl_806D5020(r2)
    addi r29, r1, 0x8
    lfs f28, lbl_806D50A0(r2)
    li r28, 0x0
    lfs f29, lbl_806D5024(r2)
    lfs f30, lbl_806D5028(r2)
    TwinSpriteOverlay_Render_L_800B17B4:
    lwz r0, 0x0(r30)
    lwz r3, 0x4(r30)
    stw r0, 0x40(r1)
    lwz r0, 0x8(r30)
    stw r3, 0x44(r1)
    lfs f1, 0x40(r1)
    lfs f0, 0x44(r1)
    stw r0, 0x48(r1)
    fsubs f2, f1, f27
    fsubs f1, f0, f29
    lwz r3, g_courseScene3D(r13)
    lfs f0, 0x48(r1)
    fmuls f2, f26, f2
    fmuls f1, f28, f1
    fsubs f0, f0, f30
    stfs f2, 0x28(r1)
    stfs f1, 0x2c(r1)
    stfs f0, 0x30(r1)
    bl CObj_GetProjMatrix_Cached
    addi r4, r1, 0x28
    mr r5, r4
    bl fn_8025DF40
    addi r3, r1, 0x4c
    addi r4, r1, 0x28
    bl Vec3_Copy
    lwz r3, g_courseScene3D(r13)
    addi r4, r1, 0x10
    bl CObj_LoadProjMatrix
    lwz r3, g_courseScene3D(r13)
    addi r4, r1, 0x1c
    bl CObj_ApplyScissor
    addi r3, r1, 0x1c
    addi r4, r1, 0x10
    bl Vec3_PitchTo
    fmr f24, f1
    addi r3, r1, 0x1c
    addi r4, r1, 0x10
    bl Vec3_HorizontalYawTo
    fmr f23, f1
    addi r3, r1, 0x88
    bl Matrix4_Identity
    addi r3, r1, 0x88
    lfs f1, 0x0(r29)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    fmr f1, f31
    addi r3, r1, 0x88
    fmr f2, f25
    lfs f3, lbl_806D5028(r2)
    mr r4, r3
    bl Mtx44_Scale_PerAxis
    fmr f1, f24
    addi r3, r1, 0x88
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    fmr f1, f23
    addi r3, r1, 0x88
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    lwz r7, 0x4c(r1)
    addi r3, r1, 0x88
    lwz r6, 0x50(r1)
    mr r4, r3
    lwz r0, 0x54(r1)
    addi r5, r1, 0x34
    stw r7, 0x34(r1)
    stw r6, 0x38(r1)
    stw r0, 0x3c(r1)
    bl Mtx44_Translate
    addi r3, r1, 0x58
    addi r4, r1, 0x88
    bl DbgScene_CopyMatrix3x4Transpose
    mr r3, r31
    addi r4, r1, 0x58
    bl cLNormal3DWrap_Slot_SetMatrixSource
    mr r3, r31
    bl cLNormal3DWrap_Slot_Render
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x2
    addi r30, r30, 0xc
    blt TwinSpriteOverlay_Render_L_800B17B4
    TwinSpriteOverlay_Render_L_800B18FC:
    psq_l f31, 0x188(r1), 0, 0
    lfd f31, 0x180(r1)
    psq_l f30, 0x178(r1), 0, 0
    lfd f30, 0x170(r1)
    psq_l f29, 0x168(r1), 0, 0
    lfd f29, 0x160(r1)
    psq_l f28, 0x158(r1), 0, 0
    lfd f28, 0x150(r1)
    psq_l f27, 0x148(r1), 0, 0
    lfd f27, 0x140(r1)
    psq_l f26, 0x138(r1), 0, 0
    lfd f26, 0x130(r1)
    psq_l f25, 0x128(r1), 0, 0
    lfd f25, 0x120(r1)
    psq_l f24, 0x118(r1), 0, 0
    lfd f24, 0x110(r1)
    psq_l f23, 0x108(r1), 0, 0
    lfd f23, 0x100(r1)
    lwz r31, 0xfc(r1)
    lwz r30, 0xf8(r1)
    lwz r29, 0xf4(r1)
    lwz r0, 0x194(r1)
    lwz r28, 0xf0(r1)
    mtlr r0
    addi r1, r1, 0x190
    blr
}

/* === extracted from auto_TwinSpriteOverlay_Ad_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Mtx44_TransformVec3();
extern void clDrawMan_AddSorted_NoDepthBias();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D5034;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern void TwinSpriteOverlay_Render();
extern unsigned int lbl_8032948C[];
extern unsigned int lbl_805DF3D0[];

/* --- function index (1 fns, .text 0x800B1964..0x800B19F8) ---
 * [  0] 0x800B1964 size:0x94    global TwinSpriteOverlay_AddDraw
 */

/* --- forward decls --- */
asm void TwinSpriteOverlay_AddDraw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TwinSpriteOverlay_AddDraw[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TwinSpriteOverlay_AddDraw = {
    (void *)&TwinSpriteOverlay_AddDraw, 0x00000094, (void *)extab_TwinSpriteOverlay_AddDraw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TwinSpriteOverlay_AddDraw(void) { /* 0x800B1964 size:0x94 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r4, lbl_805DF3D0@ha
    lis r5, lbl_8032948C@ha
    stw r0, 0x34(r1)
    addi r4, r4, lbl_805DF3D0@l
    stw r31, 0x2c(r1)
    mr r31, r3
    addi r3, r1, 0x14
    lwzu r7, lbl_8032948C@l(r5)
    lwz r6, 0x4(r5)
    lwz r0, 0x8(r5)
    addi r5, r1, 0x8
    stw r7, 0x14(r1)
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne TwinSpriteOverlay_AddDraw_L_800B19C4
    li r3, 0x0
    TwinSpriteOverlay_AddDraw_L_800B19C4:
    lis r4, TwinSpriteOverlay_Render@ha
    lfs f1, 0x14(r1)
    lfs f2, 0x18(r1)
    addi r4, r4, TwinSpriteOverlay_Render@l
    lfs f3, 0x1c(r1)
    mr r5, r31
    lfs f4, lbl_806D5034(r2)
    bl clDrawMan_AddSorted_NoDepthBias
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

/* === extracted from auto_TwinSpriteOverlay_Up_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AnimStatePool_Alloc();
extern void AnimStatePool_Free();
extern void AnimState_Step();
extern void DrawEffect_Free();
extern void DrawEffect_SpawnDirect();
extern void VfxSlot_BindResource();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5028;
extern unsigned int lbl_806D5034;
extern unsigned int lbl_806D5044;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern void TwinSpriteOverlay_AddDraw();
extern unsigned int fn_800AF4F8[];
extern unsigned int lbl_8041A0E0[];
extern unsigned int lbl_8041A14C[];

/* --- function index (1 fns, .text 0x800B19F8..0x800B1C88) ---
 * [  0] 0x800B19F8 size:0x290   global TwinSpriteOverlay_Update
 */

/* --- forward decls --- */
asm void TwinSpriteOverlay_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TwinSpriteOverlay_Update[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TwinSpriteOverlay_Update = {
    (void *)&TwinSpriteOverlay_Update, 0x00000290, (void *)extab_TwinSpriteOverlay_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TwinSpriteOverlay_Update(void) { /* 0x800B19F8 size:0x290 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    lbz r0, 0xb4(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TwinSpriteOverlay_Update_L_800B1AD8
    bge TwinSpriteOverlay_Update_L_800B1AD8
    cmpwi r0, 0x0
    bge TwinSpriteOverlay_Update_L_800B1A30
    b TwinSpriteOverlay_Update_L_800B1AD8
    TwinSpriteOverlay_Update_L_800B1A30:
    li r0, 0x1
    lis r3, fn_800AF4F8@ha
    stb r0, 0x14(r31)
    addi r3, r3, fn_800AF4F8@l
    bl DrawEffect_SpawnDirect
    lis r4, fn_800AF4F8@ha
    stw r3, 0xdc(r31)
    addi r3, r4, fn_800AF4F8@l
    bl DrawEffect_SpawnDirect
    stw r3, 0xe0(r31)
    li r4, 0x94
    lwz r3, 0xe0(r31)
    addi r3, r3, 0x14
    bl VfxSlot_BindResource
    lwz r4, 0xdc(r31)
    li r0, 0x0
    lis r3, lbl_8041A0E0@ha
    stb r0, 0x28(r4)
    addi r3, r3, lbl_8041A0E0@l
    lwz r4, 0xe0(r31)
    stb r0, 0x28(r4)
    bl AnimStatePool_Alloc
    lis r4, lbl_8041A14C@ha
    stw r3, 0xcc(r31)
    addi r3, r4, lbl_8041A14C@l
    bl AnimStatePool_Alloc
    lis r4, TwinSpriteOverlay_AddDraw@ha
    stw r3, 0xd0(r31)
    addi r0, r4, TwinSpriteOverlay_AddDraw@l
    li r4, 0x0
    stw r0, 0x78(r31)
    li r3, 0x3
    lfs f0, lbl_806D5028(r2)
    li r0, 0x3c
    stw r31, 0x7c(r31)
    stb r4, 0x190(r31)
    stfs f0, 0x150(r31)
    stw r3, 0x180(r31)
    stw r0, 0x184(r31)
    lbz r3, 0xb4(r31)
    addi r0, r3, 0x1
    stb r0, 0xb4(r31)
    TwinSpriteOverlay_Update_L_800B1AD8:
    lwz r0, 0x180(r31)
    cmplwi r0, 0x0
    bne TwinSpriteOverlay_Update_L_800B1B1C
    lwz r5, 0x11c(r31)
    lis r3, 0x1
    li r4, 0x0
    lwz r5, 0x304(r5)
    lwz r0, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r0, r4
    and r3, r5, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    beq TwinSpriteOverlay_Update_L_800B1B1C
    li r0, 0x1
    stb r0, 0x190(r31)
    TwinSpriteOverlay_Update_L_800B1B1C:
    lwz r0, 0x184(r31)
    cmplwi r0, 0x0
    bne TwinSpriteOverlay_Update_L_800B1B60
    lwz r3, 0x11c(r31)
    li r4, 0x0
    li r0, 0x800
    lwz r5, 0x304(r3)
    lwz r3, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne TwinSpriteOverlay_Update_L_800B1B60
    li r0, 0x1
    stb r0, 0x190(r31)
    TwinSpriteOverlay_Update_L_800B1B60:
    lbz r0, 0x190(r31)
    extsb. r0, r0
    beq TwinSpriteOverlay_Update_L_800B1B7C
    lfs f1, 0x150(r31)
    lfs f0, lbl_806D5044(r2)
    fsubs f0, f1, f0
    stfs f0, 0x150(r31)
    TwinSpriteOverlay_Update_L_800B1B7C:
    lwz r3, 0xcc(r31)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Update_L_800B1BC0
    lwz r0, 0xd0(r31)
    cmplwi r0, 0x0
    beq TwinSpriteOverlay_Update_L_800B1BC0
    bl AnimState_Step
    mr r30, r3
    lwz r3, 0xd0(r31)
    bl AnimState_Step
    clrlwi. r0, r30, 24
    bne TwinSpriteOverlay_Update_L_800B1BB4
    clrlwi. r0, r3, 24
    beq TwinSpriteOverlay_Update_L_800B1BC8
    TwinSpriteOverlay_Update_L_800B1BB4:
    li r0, 0x1
    stb r0, 0xc9(r31)
    b TwinSpriteOverlay_Update_L_800B1BC8
    TwinSpriteOverlay_Update_L_800B1BC0:
    li r0, 0x1
    stb r0, 0xc9(r31)
    TwinSpriteOverlay_Update_L_800B1BC8:
    lbz r0, 0xc9(r31)
    extsb. r0, r0
    bne TwinSpriteOverlay_Update_L_800B1BE4
    lfs f1, 0x150(r31)
    lfs f0, lbl_806D5034(r2)
    fcmpo cr0, f1, f0
    bge TwinSpriteOverlay_Update_L_800B1C20
    TwinSpriteOverlay_Update_L_800B1BE4:
    lwz r3, 0xcc(r31)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Update_L_800B1BF4
    bl AnimStatePool_Free
    TwinSpriteOverlay_Update_L_800B1BF4:
    lwz r3, 0xd0(r31)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Update_L_800B1C04
    bl AnimStatePool_Free
    TwinSpriteOverlay_Update_L_800B1C04:
    lwz r3, 0xdc(r31)
    bl DrawEffect_Free
    lwz r3, 0xe0(r31)
    bl DrawEffect_Free
    mr r3, r31
    bl DrawEffect_Free
    b TwinSpriteOverlay_Update_L_800B1C70
    TwinSpriteOverlay_Update_L_800B1C20:
    lwz r3, 0x180(r31)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Update_L_800B1C34
    subi r0, r3, 0x1
    stw r0, 0x180(r31)
    TwinSpriteOverlay_Update_L_800B1C34:
    lwz r3, 0x184(r31)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Update_L_800B1C48
    subi r0, r3, 0x1
    stw r0, 0x184(r31)
    TwinSpriteOverlay_Update_L_800B1C48:
    lwz r3, 0x188(r31)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Update_L_800B1C5C
    subi r0, r3, 0x1
    stw r0, 0x188(r31)
    TwinSpriteOverlay_Update_L_800B1C5C:
    lwz r3, 0x18c(r31)
    cmplwi r3, 0x0
    beq TwinSpriteOverlay_Update_L_800B1C70
    subi r0, r3, 0x1
    stw r0, 0x18c(r31)
    TwinSpriteOverlay_Update_L_800B1C70:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

