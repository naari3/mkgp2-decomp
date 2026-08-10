/* === extracted from auto_BombItem_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BombExplosion_InitOrDestroy();
extern void BombExplosion_UpdateShockwaveVfx();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern void ItemObject_AllocFromPool();
extern void ItemObject_DecrementCategoryBudget();
extern void KartDriver_GetKartRootMtx();
extern void KartFxParam_GetConst1p5();
extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyTranslation();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_Scale_Uniform();
extern void Mtx_Lerp();
extern void Mtx_TransposeToMtx44();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D6348;
extern unsigned int lbl_806D6350;
extern unsigned int lbl_806D6354;
extern unsigned int lbl_806D6360;
extern unsigned int lbl_806D6370;
extern unsigned int lbl_806D637C;
extern unsigned int lbl_806D63A8;
extern unsigned int lbl_806D63B0;
extern unsigned int lbl_806D63B4;
extern unsigned int lbl_806D63B8;

/* --- function index (1 fns, .text 0x800FC854..0x800FCCAC) ---
 * [  0] 0x800FC854 size:0x458   global BombItem_Tick
 */

/* --- forward decls --- */
asm void BombItem_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BombItem_Tick[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BombItem_Tick = {
    (void *)&BombItem_Tick, 0x00000458, (void *)extab_BombItem_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BombItem_Tick(void) { /* 0x800FC854 size:0x458 */
    nofralloc
    stwu r1, -0x110(r1)
    mflr r0
    stw r0, 0x114(r1)
    stw r31, 0x10c(r1)
    mr r31, r3
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BombItem_Tick_L_800FCC48
    bge BombItem_Tick_L_800FC88C
    cmpwi r0, 0x0
    beq BombItem_Tick_L_800FC898
    bge BombItem_Tick_L_800FC8C0
    b BombItem_Tick_L_800FCC48
    BombItem_Tick_L_800FC88C:
    cmpwi r0, 0x4
    bge BombItem_Tick_L_800FCC48
    b BombItem_Tick_L_800FCC38
    BombItem_Tick_L_800FC898:
    addi r3, r31, 0x14
    li r4, 0x52
    bl SpriteSlot_InitNonLoop
    addi r3, r31, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r3, 0x1
    li r0, 0x0
    stb r3, 0xc8(r31)
    stb r0, 0xc9(r31)
    BombItem_Tick_L_800FC8C0:
    lbz r0, 0xc9(r31)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_Tick_L_800FC900
    bge BombItem_Tick_L_800FC8E0
    cmpwi r0, 0x0
    bge BombItem_Tick_L_800FC8EC
    b BombItem_Tick_L_800FCC48
    BombItem_Tick_L_800FC8E0:
    cmpwi r0, 0x3
    bge BombItem_Tick_L_800FCC48
    b BombItem_Tick_L_800FC9A4
    BombItem_Tick_L_800FC8EC:
    lfs f0, lbl_806D6348(r2)
    stfs f0, 0x2c(r31)
    lbz r3, 0xc9(r31)
    addi r0, r3, 0x1
    stb r0, 0xc9(r31)
    BombItem_Tick_L_800FC900:
    lfs f1, lbl_806D637C(r2)
    mr r3, r31
    lfs f2, lbl_806D63B0(r2)
    li r4, 0x1
    lfs f3, lbl_806D63B4(r2)
    bl GabyouItem_BuildLocalTransformFromHandJoint
    lwz r3, 0x184(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq BombItem_Tick_L_800FC934
    li r0, 0x0
    stb r0, 0x28(r31)
    b BombItem_Tick_L_800FC93C
    BombItem_Tick_L_800FC934:
    li r0, 0x1
    stb r0, 0x28(r31)
    BombItem_Tick_L_800FC93C:
    lbz r0, 0x18c(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BombItem_Tick_L_800FC988
    bge BombItem_Tick_L_800FCC48
    cmpwi r0, 0x1
    bge BombItem_Tick_L_800FC95C
    b BombItem_Tick_L_800FCC48
    BombItem_Tick_L_800FC95C:
    li r0, 0x1
    li r4, 0x0
    stb r0, 0x28(r31)
    lfs f0, lbl_806D6360(r2)
    stb r4, 0x18c(r31)
    stfs f0, 0x2c(r31)
    lbz r3, 0xc9(r31)
    addi r0, r3, 0x1
    stb r0, 0xc9(r31)
    stb r4, 0xca(r31)
    b BombItem_Tick_L_800FCC48
    BombItem_Tick_L_800FC988:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x18c(r31)
    stb r3, 0x28(r31)
    stb r0, 0xc8(r31)
    stb r3, 0xc9(r31)
    b BombItem_Tick_L_800FCC48
    BombItem_Tick_L_800FC9A4:
    lbz r0, 0xca(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BombItem_Tick_L_800FCAA0
    bge BombItem_Tick_L_800FC9C8
    cmpwi r0, 0x0
    beq BombItem_Tick_L_800FC9D4
    bge BombItem_Tick_L_800FCA30
    b BombItem_Tick_L_800FCB48
    BombItem_Tick_L_800FC9C8:
    cmpwi r0, 0x4
    bge BombItem_Tick_L_800FCB48
    b BombItem_Tick_L_800FCB14
    BombItem_Tick_L_800FC9D4:
    lfs f0, lbl_806D6348(r2)
    stfs f0, 0x100(r31)
    lbz r0, 0x1dc(r31)
    extsb. r0, r0
    beq BombItem_Tick_L_800FC9F4
    li r0, 0x384
    stw r0, 0xf0(r31)
    b BombItem_Tick_L_800FC9FC
    BombItem_Tick_L_800FC9F4:
    li r0, 0x258
    stw r0, 0xf0(r31)
    BombItem_Tick_L_800FC9FC:
    lwz r6, 0xa0(r31)
    addi r4, r1, 0x8
    lwz r0, 0xa4(r31)
    li r3, 0x83
    li r5, 0x0
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r31)
    stw r0, 0x10(r1)
    bl SoundMgr_PlaySE_Positional
    lbz r3, 0xca(r31)
    addi r0, r3, 0x1
    stb r0, 0xca(r31)
    BombItem_Tick_L_800FCA30:
    lfs f2, 0x100(r31)
    lfs f0, lbl_806D63A8(r2)
    lfs f1, lbl_806D6360(r2)
    fadds f0, f2, f0
    stfs f0, 0x100(r31)
    lfs f0, 0x100(r31)
    fcmpo cr0, f1, f0
    bge BombItem_Tick_L_800FCB48
    lis r3, BombExplosion_InitOrDestroy@ha
    stfs f1, 0x100(r31)
    addi r3, r3, BombExplosion_InitOrDestroy@l
    bl ItemObject_AllocFromPool
    stw r3, 0x148(r31)
    lwz r3, 0x148(r31)
    cmplwi r3, 0x0
    beq BombItem_Tick_L_800FCA90
    lbz r0, 0x1dc(r31)
    stb r0, 0x1dc(r3)
    lwz r0, 0x184(r31)
    lwz r3, 0x148(r31)
    stw r0, 0x184(r3)
    lwz r0, 0x180(r31)
    lwz r3, 0x148(r31)
    stw r0, 0x180(r3)
    BombItem_Tick_L_800FCA90:
    lbz r3, 0xca(r31)
    addi r0, r3, 0x1
    stb r0, 0xca(r31)
    b BombItem_Tick_L_800FCB48
    BombItem_Tick_L_800FCAA0:
    lwz r5, 0x184(r31)
    lis r3, 0x400
    li r4, 0x0
    lwz r5, 0x304(r5)
    lwz r0, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r0, r4
    and r3, r5, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne BombItem_Tick_L_800FCAD4
    stw r4, 0xf0(r31)
    BombItem_Tick_L_800FCAD4:
    lwz r0, 0xf0(r31)
    cmplwi r0, 0x0
    bne BombItem_Tick_L_800FCB48
    lwz r3, 0x148(r31)
    cmplwi r3, 0x0
    beq BombItem_Tick_L_800FCB04
    li r0, 0x1
    stb r0, 0x18c(r3)
    lwz r3, 0x148(r31)
    bl BombExplosion_InitOrDestroy
    li r0, 0x0
    stw r0, 0x148(r31)
    BombItem_Tick_L_800FCB04:
    lbz r3, 0xca(r31)
    addi r0, r3, 0x1
    stb r0, 0xca(r31)
    b BombItem_Tick_L_800FCB48
    BombItem_Tick_L_800FCB14:
    lfs f2, 0x2c(r31)
    lfs f1, lbl_806D63A8(r2)
    lfs f0, lbl_806D6348(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r31)
    lfs f1, 0x2c(r31)
    fcmpo cr0, f1, f0
    bge BombItem_Tick_L_800FCB48
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r31)
    stb r0, 0xc8(r31)
    stb r3, 0xc9(r31)
    BombItem_Tick_L_800FCB48:
    lwz r3, 0x184(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq BombItem_Tick_L_800FCB64
    li r0, 0x0
    stb r0, 0x28(r31)
    b BombItem_Tick_L_800FCB6C
    BombItem_Tick_L_800FCB64:
    li r0, 0x1
    stb r0, 0x28(r31)
    BombItem_Tick_L_800FCB6C:
    lwz r3, 0x184(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x84
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x44
    bl Matrix4_Identity
    addi r3, r1, 0x44
    lfs f1, lbl_806D63B8(r2)
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    addi r3, r1, 0x44
    lfs f1, lbl_806D6348(r2)
    lfs f2, lbl_806D6370(r2)
    mr r4, r3
    lfs f3, lbl_806D6350(r2)
    bl Matrix4_PreMultiplyTranslation
    addi r3, r1, 0xc4
    addi r4, r1, 0x44
    addi r5, r1, 0x84
    bl Matrix4_Multiply
    addi r3, r1, 0x44
    bl Matrix4_Identity
    addi r3, r1, 0x44
    lfs f1, lbl_806D6354(r2)
    mr r4, r3
    bl Mtx44_Scale_Uniform
    addi r3, r1, 0xc4
    addi r4, r1, 0x44
    mr r5, r3
    bl Matrix4_Multiply
    addi r3, r1, 0x14
    addi r4, r1, 0xc4
    bl DbgScene_CopyMatrix3x4Transpose
    addi r3, r31, 0x48
    lfs f1, 0x100(r31)
    mr r5, r3
    addi r4, r1, 0x14
    bl Mtx_Lerp
    addi r3, r31, 0xa0
    addi r4, r31, 0x48
    bl Mtx44_GetTranslation_RowMajor
    lwz r3, 0x184(r31)
    bl KartFxParam_GetConst1p5
    lfs f0, lbl_806D6354(r2)
    addi r4, r31, 0x48
    fmuls f0, f0, f1
    stfs f0, 0xc4(r31)
    lwz r3, 0x148(r31)
    bl BombExplosion_UpdateShockwaveVfx
    b BombItem_Tick_L_800FCC48
    BombItem_Tick_L_800FCC38:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r31
    bl SpriteSlot_Container_Free
    b BombItem_Tick_L_800FCC98
    BombItem_Tick_L_800FCC48:
    lwz r3, 0xf0(r31)
    cmplwi r3, 0x0
    beq BombItem_Tick_L_800FCC5C
    subi r0, r3, 0x1
    stw r0, 0xf0(r31)
    BombItem_Tick_L_800FCC5C:
    lwz r3, 0xf4(r31)
    cmplwi r3, 0x0
    beq BombItem_Tick_L_800FCC70
    subi r0, r3, 0x1
    stw r0, 0xf4(r31)
    BombItem_Tick_L_800FCC70:
    lwz r3, 0xf8(r31)
    cmplwi r3, 0x0
    beq BombItem_Tick_L_800FCC84
    subi r0, r3, 0x1
    stw r0, 0xf8(r31)
    BombItem_Tick_L_800FCC84:
    lwz r3, 0xfc(r31)
    cmplwi r3, 0x0
    beq BombItem_Tick_L_800FCC98
    subi r0, r3, 0x1
    stw r0, 0xfc(r31)
    BombItem_Tick_L_800FCC98:
    lwz r0, 0x114(r1)
    lwz r31, 0x10c(r1)
    mtlr r0
    addi r1, r1, 0x110
    blr
}

