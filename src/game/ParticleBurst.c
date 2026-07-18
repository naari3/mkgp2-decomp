/*
 * ParticleBurst unit: all three claimed members are preserved as byte-identical
 * inline PowerPC asm. Generated from the three dtk reversed-extab groups;
 * do not reorder functions or extab declarations.
 */

asm void ParticleBurst_Draw(void);
asm void ParticleBurst_DrawCb(void);
asm void ParticleBurst_Update(void);

/* === extracted from auto_ParticleBurst_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DbgGx_Xfreg100A_Set3();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void GX_Begin();
extern void GX_LoadPosMtxImm();
extern void GX_SetCullMode();
extern void GX_SetCurrentMtx();
extern void Matrix4_Identity();
extern void Matrix4_PreMultiplyRotZ();
extern void Matrix4_PreMultiplyTranslation();
extern void fn_802D2B00();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5020;
extern unsigned int lbl_806D5024;
extern unsigned int lbl_806D5028;
extern unsigned int lbl_806D5034;
extern unsigned int lbl_806D506C;
extern unsigned int lbl_806D509C;
extern unsigned int lbl_806D50A0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803292B4[];

/* --- function index (1 fns, .text 0x800B4164..0x800B4388) ---
 * [  0] 0x800B4164 size:0x224   global ParticleBurst_Draw
 */

/* --- forward decls --- */
asm void ParticleBurst_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ParticleBurst_Draw[8] = {
    0x31, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ParticleBurst_Draw = {
    (void *)&ParticleBurst_Draw, 0x00000224, (void *)extab_ParticleBurst_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ParticleBurst_Draw(void) { /* 0x800B4164 size:0x224 */
    nofralloc
    stwu r1, -0xd0(r1)
    mflr r0
    stw r0, 0xd4(r1)
    stfd f31, 0xc0(r1)
    psq_st f31, 0xc8(r1), 0, 0
    stfd f30, 0xb0(r1)
    psq_st f30, 0xb8(r1), 0, 0
    stfd f29, 0xa0(r1)
    psq_st f29, 0xa8(r1), 0, 0
    stfd f28, 0x90(r1)
    psq_st f28, 0x98(r1), 0, 0
    stmw r26, 0x78(r1)
    mr r29, r3
    li r3, 0x0
    bl GX_SetCullMode
    lis r4, 0x4000
    li r3, 0x0
    addi r4, r4, 0x2
    bl fn_802D2B00
    li r3, 0x1
    li r4, 0x3
    li r5, 0x1
    bl DbgGx_Xfreg100A_Set3
    lfs f0, lbl_806D506C(r2)
    li r30, 0x0
    li r31, 0x0
    fneg f28, f0
    ParticleBurst_Draw_L_800B41D0:
    lwz r0, 0xcc(r29)
    add r5, r0, r31
    lbz r0, 0x1d(r5)
    extsb. r0, r0
    bne ParticleBurst_Draw_L_800B4344
    lbz r0, 0x1c(r5)
    extsb. r0, r0
    bne ParticleBurst_Draw_L_800B4344
    lis r4, 0x2aab
    lis r3, lbl_803292B4@ha
    subi r0, r4, 0x5555
    lfs f3, 0x0(r5)
    mulhw r4, r0, r30
    lfs f2, lbl_806D5020(r2)
    lfs f1, 0x4(r5)
    addi r0, r3, lbl_803292B4@l
    lfs f0, lbl_806D5024(r2)
    fsubs f4, f3, f2
    srwi r3, r4, 31
    lfs f5, lbl_806D509C(r2)
    add r3, r4, r3
    fsubs f2, f1, f0
    mulli r3, r3, 0x6
    lfs f3, lbl_806D50A0(r2)
    lfs f1, 0x8(r5)
    fmuls f31, f5, f4
    lfs f0, lbl_806D5028(r2)
    subf r3, r3, r30
    mulli r4, r3, 0x3
    fmuls f30, f3, f2
    fsubs f29, f1, f0
    addi r3, r1, 0x38
    add r4, r0, r4
    lbz r28, 0x0(r4)
    lbz r27, 0x1(r4)
    lbz r26, 0x2(r4)
    bl Matrix4_Identity
    lwz r4, 0xcc(r29)
    addi r0, r31, 0xc
    addi r3, r1, 0x38
    lfsx f1, r4, r0
    mr r4, r3
    bl Matrix4_PreMultiplyRotZ
    fmr f1, f31
    addi r3, r1, 0x38
    fmr f2, f30
    mr r4, r3
    fmr f3, f29
    bl Matrix4_PreMultiplyTranslation
    addi r3, r1, 0x8
    addi r4, r1, 0x38
    bl DbgScene_CopyMatrix3x4Transpose
    addi r3, r1, 0x8
    li r4, 0x0
    bl GX_LoadPosMtxImm
    li r3, 0x0
    bl GX_SetCurrentMtx
    li r3, 0x80
    li r4, 0x0
    li r5, 0x4
    bl GX_Begin
    lis r3, 0xcc01
    lfs f1, lbl_806D5034(r2)
    stfs f28, -0x8000(r3)
    li r0, 0xff
    lfs f0, lbl_806D506C(r2)
    stfs f28, -0x8000(r3)
    stfs f1, -0x8000(r3)
    stb r28, -0x8000(r3)
    stb r27, -0x8000(r3)
    stb r26, -0x8000(r3)
    stb r0, -0x8000(r3)
    stfs f0, -0x8000(r3)
    stfs f28, -0x8000(r3)
    stfs f1, -0x8000(r3)
    stb r28, -0x8000(r3)
    stb r27, -0x8000(r3)
    stb r26, -0x8000(r3)
    stb r0, -0x8000(r3)
    stfs f0, -0x8000(r3)
    stfs f0, -0x8000(r3)
    stfs f1, -0x8000(r3)
    stb r28, -0x8000(r3)
    stb r27, -0x8000(r3)
    stb r26, -0x8000(r3)
    stb r0, -0x8000(r3)
    stfs f28, -0x8000(r3)
    stfs f0, -0x8000(r3)
    stfs f1, -0x8000(r3)
    stb r28, -0x8000(r3)
    stb r27, -0x8000(r3)
    stb r26, -0x8000(r3)
    stb r0, -0x8000(r3)
    ParticleBurst_Draw_L_800B4344:
    addi r30, r30, 0x1
    addi r31, r31, 0x20
    cmpwi r30, 0x24
    blt ParticleBurst_Draw_L_800B41D0
    psq_l f31, 0xc8(r1), 0, 0
    lfd f31, 0xc0(r1)
    psq_l f30, 0xb8(r1), 0, 0
    lfd f30, 0xb0(r1)
    psq_l f29, 0xa8(r1), 0, 0
    lfd f29, 0xa0(r1)
    psq_l f28, 0x98(r1), 0, 0
    lfd f28, 0x90(r1)
    lmw r26, 0x78(r1)
    lwz r0, 0xd4(r1)
    mtlr r0
    addi r1, r1, 0xd0
    blr
}


/* === extracted from auto_ParticleBurst_DrawCb_text === */
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
extern unsigned int lbl_803292C8[];
extern unsigned int lbl_805DF3D0[];

/* --- function index (1 fns, .text 0x800B4388..0x800B441C) ---
 * [  0] 0x800B4388 size:0x94    global ParticleBurst_DrawCb
 */

/* --- forward decls --- */
asm void ParticleBurst_DrawCb(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ParticleBurst_DrawCb[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ParticleBurst_DrawCb = {
    (void *)&ParticleBurst_DrawCb, 0x00000094, (void *)extab_ParticleBurst_DrawCb
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ParticleBurst_DrawCb(void) { /* 0x800B4388 size:0x94 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r4, lbl_805DF3D0@ha
    lis r5, lbl_803292C8@ha
    stw r0, 0x34(r1)
    addi r4, r4, lbl_805DF3D0@l
    stw r31, 0x2c(r1)
    mr r31, r3
    addi r3, r1, 0x14
    lwzu r7, lbl_803292C8@l(r5)
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
    bne ParticleBurst_DrawCb_L_800B43E8
    li r3, 0x0
    ParticleBurst_DrawCb_L_800B43E8:
    lis r4, ParticleBurst_Draw@ha
    lfs f1, 0x14(r1)
    lfs f2, 0x18(r1)
    addi r4, r4, ParticleBurst_Draw@l
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


/* === extracted from auto_ParticleBurst_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void DrawEffect_Free();
extern void FUN_8003b120();
extern void MemoryManager_Free();
extern void Rand_RangeFloat();
extern void Rand_RangeFloatMax();
extern void fn_8027E480();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5020;
extern unsigned int lbl_806D5024;
extern unsigned int lbl_806D5034;
extern unsigned int lbl_806D5044;
extern unsigned int lbl_806D5070;
extern unsigned int lbl_806D5074;
extern unsigned int lbl_806D5080;
extern unsigned int lbl_806D5084;
extern unsigned int lbl_806D5090;
extern unsigned int lbl_806D50E4;
extern unsigned int lbl_806D5134;
extern unsigned int lbl_806D5140;
extern unsigned int lbl_806D5144;
extern unsigned int lbl_806D5148;
extern unsigned int lbl_806D514C;
extern unsigned int lbl_806D5150;
extern unsigned int lbl_806D5154;
extern unsigned int lbl_806D5158;
extern unsigned int lbl_806D515C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */

/* --- function index (1 fns, .text 0x800B441C..0x800B4804) ---
 * [  0] 0x800B441C size:0x3E8   global ParticleBurst_Update
 */

/* --- forward decls --- */
asm void ParticleBurst_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ParticleBurst_Update[8] = {
    0x29, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ParticleBurst_Update = {
    (void *)&ParticleBurst_Update, 0x000003E8, (void *)extab_ParticleBurst_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ParticleBurst_Update(void) { /* 0x800B441C size:0x3E8 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stfd f30, 0x70(r1)
    psq_st f30, 0x78(r1), 0, 0
    stfd f29, 0x60(r1)
    psq_st f29, 0x68(r1), 0, 0
    stfd f28, 0x50(r1)
    psq_st f28, 0x58(r1), 0, 0
    stfd f27, 0x40(r1)
    psq_st f27, 0x48(r1), 0, 0
    stfd f26, 0x30(r1)
    psq_st f26, 0x38(r1), 0, 0
    stfd f25, 0x20(r1)
    psq_st f25, 0x28(r1), 0, 0
    stmw r27, 0xc(r1)
    mr r27, r3
    li r29, 0x1
    lbz r0, 0xb4(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ParticleBurst_Update_L_800B4660
    bge ParticleBurst_Update_L_800B47B8
    cmpwi r0, 0x0
    bge ParticleBurst_Update_L_800B448C
    b ParticleBurst_Update_L_800B47B8
    ParticleBurst_Update_L_800B448C:
    li r0, 0x1
    li r3, 0x480
    stb r0, 0x14(r27)
    bl FUN_8003b120
    stw r3, 0xcc(r27)
    li r30, 0x0
    lfs f26, lbl_806D5020(r2)
    li r31, 0x0
    lfs f27, lbl_806D5024(r2)
    lfs f29, lbl_806D5090(r2)
    lfs f30, lbl_806D5080(r2)
    lfs f31, lbl_806D5034(r2)
    ParticleBurst_Update_L_800B44BC:
    lwz r3, 0xcc(r27)
    li r6, 0x12
    srawi r5, r30, 31
    addi r0, r31, 0x4
    stfsx f26, r3, r31
    subfc r3, r6, r30
    srwi r4, r6, 31
    lwz r3, 0xcc(r27)
    adde. r28, r5, r4
    stfsx f27, r3, r0
    bne ParticleBurst_Update_L_800B44FC
    lfs f0, lbl_806D5044(r2)
    addi r0, r31, 0x8
    lwz r3, 0xcc(r27)
    stfsx f0, r3, r0
    b ParticleBurst_Update_L_800B450C
    ParticleBurst_Update_L_800B44FC:
    lfs f0, lbl_806D5074(r2)
    addi r0, r31, 0x8
    lwz r3, 0xcc(r27)
    stfsx f0, r3, r0
    ParticleBurst_Update_L_800B450C:
    cmpwi r28, 0x0
    beq ParticleBurst_Update_L_800B4528
    lfs f1, lbl_806D5140(r2)
    lfs f2, lbl_806D5144(r2)
    bl Rand_RangeFloat
    fmr f28, f1
    b ParticleBurst_Update_L_800B4538
    ParticleBurst_Update_L_800B4528:
    lfs f1, lbl_806D5140(r2)
    lfs f2, lbl_806D5148(r2)
    bl Rand_RangeFloat
    fmr f28, f1
    ParticleBurst_Update_L_800B4538:
    lfs f1, lbl_806D5084(r2)
    lfs f2, lbl_806D5134(r2)
    bl Rand_RangeFloat
    fadds f0, f29, f1
    fmuls f25, f30, f0
    fmr f1, f25
    bl fn_8027E9E8
    frsp f0, f1
    lwz r3, 0xcc(r27)
    fmr f1, f25
    addi r0, r31, 0x10
    fmuls f0, f28, f0
    stfsx f0, r3, r0
    bl fn_8027E480
    frsp f0, f1
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x14
    lfs f1, lbl_806D514C(r2)
    fmuls f0, f28, f0
    stfsx f0, r3, r0
    bl Rand_RangeFloatMax
    fmuls f1, f30, f1
    bl BuildOrientationFromYaw
    lwz r3, 0xcc(r27)
    addi r0, r31, 0xc
    lfs f2, lbl_806D5154(r2)
    stfsx f1, r3, r0
    lfs f1, lbl_806D5150(r2)
    bl Rand_RangeFloat
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x18
    stfsx f1, r3, r0
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f0, 0x10(r3)
    fcmpo cr0, f31, f0
    bge ParticleBurst_Update_L_800B45DC
    lfs f1, 0x18(r3)
    lfs f0, lbl_806D5070(r2)
    fmuls f0, f1, f0
    stfs f0, 0x18(r3)
    ParticleBurst_Update_L_800B45DC:
    cmpwi r28, 0x0
    bne ParticleBurst_Update_L_800B45F8
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x1c
    li r4, 0x0
    stbx r4, r3, r0
    b ParticleBurst_Update_L_800B4624
    ParticleBurst_Update_L_800B45F8:
    lis r4, 0x6666
    lwz r3, 0xcc(r27)
    addi r4, r4, 0x6667
    addi r0, r31, 0x1c
    mulhw r4, r4, r30
    srawi r4, r4, 2
    srwi r5, r4, 31
    add r4, r4, r5
    mulli r4, r4, 0xa
    subf r4, r4, r30
    stbx r4, r3, r0
    ParticleBurst_Update_L_800B4624:
    addi r30, r30, 0x1
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x1d
    li r4, 0x0
    cmpwi r30, 0x24
    stbx r4, r3, r0
    addi r31, r31, 0x20
    blt ParticleBurst_Update_L_800B44BC
    lis r3, ParticleBurst_DrawCb@ha
    addi r0, r3, ParticleBurst_DrawCb@l
    stw r0, 0x78(r27)
    stw r27, 0x7c(r27)
    lbz r3, 0xb4(r27)
    addi r0, r3, 0x1
    stb r0, 0xb4(r27)
    ParticleBurst_Update_L_800B4660:
    lfs f0, lbl_806D50E4(r2)
    li r30, 0x0
    mr r31, r30
    fneg f26, f0
    ParticleBurst_Update_L_800B4670:
    lwz r0, 0xcc(r27)
    add r4, r0, r31
    lbz r0, 0x1d(r4)
    extsb. r0, r0
    bne ParticleBurst_Update_L_800B4778
    lbz r3, 0x1c(r4)
    extsb. r0, r3
    beq ParticleBurst_Update_L_800B469C
    subi r0, r3, 0x1
    stb r0, 0x1c(r4)
    b ParticleBurst_Update_L_800B4778
    ParticleBurst_Update_L_800B469C:
    lfs f1, 0x14(r4)
    lfs f0, lbl_806D5044(r2)
    fadds f0, f1, f0
    stfs f0, 0x14(r4)
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f1, 0x0(r3)
    lfs f0, 0x10(r3)
    fadds f0, f1, f0
    stfs f0, 0x0(r3)
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f1, 0x4(r3)
    lfs f0, 0x14(r3)
    fadds f0, f1, f0
    stfs f0, 0x4(r3)
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f1, 0xc(r3)
    lfs f0, 0x18(r3)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    lwz r3, 0xcc(r27)
    addi r0, r31, 0xc
    stfsx f1, r3, r0
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f0, 0x0(r3)
    fcmpo cr0, f0, f26
    bge ParticleBurst_Update_L_800B471C
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B471C:
    lwz r0, 0xcc(r27)
    lfs f1, lbl_806D5158(r2)
    add r3, r0, r31
    lfs f0, 0x0(r3)
    fcmpo cr0, f1, f0
    bge ParticleBurst_Update_L_800B473C
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B473C:
    lwz r0, 0xcc(r27)
    add r3, r0, r31
    lfs f0, 0x4(r3)
    fcmpo cr0, f0, f26
    bge ParticleBurst_Update_L_800B4758
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B4758:
    lwz r0, 0xcc(r27)
    lfs f1, lbl_806D515C(r2)
    add r3, r0, r31
    lfs f0, 0x4(r3)
    fcmpo cr0, f1, f0
    bge ParticleBurst_Update_L_800B4778
    li r0, 0x1
    stb r0, 0x1d(r3)
    ParticleBurst_Update_L_800B4778:
    lwz r3, 0xcc(r27)
    addi r0, r31, 0x1d
    lbzx r0, r3, r0
    extsb. r0, r0
    bne ParticleBurst_Update_L_800B4790
    li r29, 0x0
    ParticleBurst_Update_L_800B4790:
    addi r30, r30, 0x1
    addi r31, r31, 0x20
    cmpwi r30, 0x24
    blt ParticleBurst_Update_L_800B4670
    cmpwi r29, 0x0
    beq ParticleBurst_Update_L_800B47B8
    lwz r3, 0xcc(r27)
    bl MemoryManager_Free
    mr r3, r27
    bl DrawEffect_Free
    ParticleBurst_Update_L_800B47B8:
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    psq_l f30, 0x78(r1), 0, 0
    lfd f30, 0x70(r1)
    psq_l f29, 0x68(r1), 0, 0
    lfd f29, 0x60(r1)
    psq_l f28, 0x58(r1), 0, 0
    lfd f28, 0x50(r1)
    psq_l f27, 0x48(r1), 0, 0
    lfd f27, 0x40(r1)
    psq_l f26, 0x38(r1), 0, 0
    lfd f26, 0x30(r1)
    psq_l f25, 0x28(r1), 0, 0
    lfd f25, 0x20(r1)
    lmw r27, 0xc(r1)
    lwz r0, 0x94(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

