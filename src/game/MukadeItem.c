/* === extracted from auto_MukadeItem_Tick_Held_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void DrawEffect_SpawnDirect();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemHit_Dispatch();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void KartCharacterParam_GetIdentityIndex();
extern void KartDriver_GetJointByIdx();
extern void KartDriver_GetKartRootMtx();
extern void KartFxParam_GetConst1p5();
extern void KartItem_ApplyEffectToTarget();
extern void KartItem_QueryEffectStateFromIse();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_PlaySE_Positional();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Lerp();
extern void Vec3_Subtract_DestFirst();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5E78;
extern unsigned int lbl_806D5E7C;
extern unsigned int lbl_806D5E80;
extern unsigned int lbl_806D5E84;
extern unsigned int lbl_806D5E88;
extern unsigned int lbl_806D5E8C;
extern unsigned int lbl_806D5E90;
extern unsigned int lbl_806D5E94;
extern unsigned int lbl_806D5E98;
extern unsigned int lbl_806D5E9C;
extern unsigned int lbl_806D5EA0;
extern unsigned int lbl_806D5EA4;
extern unsigned int lbl_806D5EA8;
extern unsigned int lbl_806D5EAC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int Effect_KartJoint15_Res7B_Update[];
extern unsigned int lbl_8032F4C8[];

/* --- function index (1 fns, .text 0x800EBC00..0x800EC268) ---
 * [  0] 0x800EBC00 size:0x668   global MukadeItem_Tick_HeldAndHoming_3839
 */

/* --- forward decls --- */
asm void MukadeItem_Tick_HeldAndHoming_3839(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_MukadeItem_Tick_HeldAndHoming_3839[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MukadeItem_Tick_HeldAndHoming_3839 = {
    (void *)&MukadeItem_Tick_HeldAndHoming_3839, 0x00000668, (void *)extab_MukadeItem_Tick_HeldAndHoming_3839
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void MukadeItem_Tick_HeldAndHoming_3839(void) { /* 0x800EBC00 size:0x668 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stmw r27, 0x8c(r1)
    mr r30, r3
    mr r31, r4
    lwz r3, 0x9c(r4)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x44
    bl Mtx44_GetTranslation_RowMajor
    lwz r3, 0x9c(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EBC48
    li r0, 0x0
    stb r0, 0x28(r30)
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EBC50
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBC48:
    li r0, 0x1
    stb r0, 0x28(r30)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBC50:
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC0C8
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBC74
    cmpwi r0, 0x0
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EBC80
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBCC8
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBC74:
    cmpwi r0, 0x4
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC1C8
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBC80:
    lfs f1, lbl_806D5E78(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lwz r0, 0x8(r30)
    cmpwi r0, 0x39
    bne MukadeItem_Tick_HeldAndHoming_3839_L_800EBCAC
    li r0, 0x1
    stb r0, 0x0(r31)
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EBCB4
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBCAC:
    li r0, 0x3
    stb r0, 0x0(r31)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBCB4:
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBCC8:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EBD20
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBCE8
    cmpwi r0, 0x0
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBCF4
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EBDA0
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBCE8:
    cmpwi r0, 0x3
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBDA0
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EBD7C
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBCF4:
    li r0, 0x14
    lfs f1, lbl_806D5E78(r2)
    stw r0, 0x4(r31)
    lfs f0, lbl_806D5E84(r2)
    stfs f1, 0x14(r31)
    stfs f0, 0x18(r31)
    stfs f1, 0x1c(r31)
    stfs f1, 0x20(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBD20:
    lfs f1, lbl_806D5E88(r2)
    lfs f0, 0xb0(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r30)
    lfs f1, lbl_806D5E8C(r2)
    lfs f0, 0x20(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x20(r31)
    lfs f1, 0x20(r31)
    bl fn_8027E9E8
    frsp f1, f1
    lfs f0, lbl_806D5E80(r2)
    fmuls f0, f0, f1
    stfs f0, 0xac(r30)
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne MukadeItem_Tick_HeldAndHoming_3839_L_800EBDA0
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EBDA0
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBD7C:
    lfs f1, 0xac(r30)
    lfs f2, lbl_806D5E78(r2)
    lfs f3, lbl_806D5E90(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    lfs f0, lbl_806D5E94(r2)
    lfs f1, 0x1c(r31)
    fadds f0, f1, f0
    stfs f0, 0x1c(r31)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBDA0:
    lfs f2, 0x18(r31)
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D5E78(r2)
    fadds f1, f2, f1
    stfs f1, 0x18(r31)
    lfs f1, 0x18(r31)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne MukadeItem_Tick_HeldAndHoming_3839_L_800EBDC8
    stfs f0, 0x18(r31)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBDC8:
    lis r4, lbl_8032F4C8@ha
    lwz r3, 0x9c(r31)
    addi r27, r4, lbl_8032F4C8@l
    li r4, 0xf
    lwz r28, 0x0(r27)
    lwz r29, 0x4(r27)
    lwz r12, 0x8(r27)
    lwz r11, 0xc(r27)
    lwz r10, 0x10(r27)
    lwz r9, 0x14(r27)
    lwz r8, 0x18(r27)
    lwz r7, 0x1c(r27)
    lwz r6, 0x20(r27)
    lwz r5, 0x24(r27)
    lwz r0, 0x28(r27)
    stw r28, 0x50(r1)
    stw r29, 0x54(r1)
    stw r12, 0x58(r1)
    stw r11, 0x5c(r1)
    stw r10, 0x60(r1)
    stw r9, 0x64(r1)
    stw r8, 0x68(r1)
    stw r7, 0x6c(r1)
    stw r6, 0x70(r1)
    stw r5, 0x74(r1)
    stw r0, 0x78(r1)
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r1, 0x38
    bl Mtx44_GetTranslation_RowMajor
    lwz r3, 0x9c(r31)
    bl KartCharacterParam_GetIdentityIndex
    slwi r0, r3, 2
    addi r3, r1, 0x50
    lfsx f1, r3, r0
    lfs f0, 0x18(r31)
    lfs f2, 0x3c(r1)
    fadds f3, f0, f1
    lfs f0, lbl_806D5E98(r2)
    lfs f1, lbl_806D5E9C(r2)
    fadds f2, f2, f3
    stfs f2, 0x3c(r1)
    lfs f2, 0x14(r31)
    fadds f0, f2, f0
    stfs f0, 0x14(r31)
    lfs f0, 0x14(r31)
    fcmpo cr0, f1, f0
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBE8C
    stfs f1, 0x14(r31)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBE8C:
    lwz r6, 0xa0(r30)
    addi r3, r30, 0xa0
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x2c
    lwz r7, 0x38(r1)
    addi r5, r1, 0x20
    stw r6, 0x20(r1)
    lwz r6, 0x3c(r1)
    stw r0, 0x24(r1)
    lwz r0, 0x40(r1)
    lwz r8, 0xa8(r30)
    stw r8, 0x28(r1)
    stw r7, 0x2c(r1)
    stw r6, 0x30(r1)
    stw r0, 0x34(r1)
    lfs f1, 0x14(r31)
    bl Vec3_Lerp
    lfs f1, 0x18(r31)
    lfs f0, lbl_806D5E78(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne MukadeItem_Tick_HeldAndHoming_3839_L_800EC0AC
    lwz r3, 0x9c(r31)
    bl KartItem_QueryEffectStateFromIse
    mr r27, r3
    lwz r4, 0x9c(r31)
    mr r3, r30
    mr r5, r27
    bl KartItem_ApplyEffectToTarget
    cmpwi r27, 0x3
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EBFC4
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBF1C
    cmpwi r27, 0x1
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EBF2C
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EBFB8
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC058
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBF1C:
    cmpwi r27, 0x5
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC024
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EC058
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC004
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBF2C:
    lwz r3, 0x8(r30)
    bl ItemAlias_HitRemapLookup
    extsh r5, r3
    lwz r3, 0x98(r31)
    lwz r4, 0x9c(r31)
    li r6, 0x0
    bl fn_801B1D5C
    lwz r6, 0x9c(r31)
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    bl ItemHit_Dispatch
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x14
    lwz r0, 0xa4(r30)
    li r3, 0x85
    li r5, 0x0
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    bl SoundMgr_PlaySE_Positional
    lis r3, Effect_KartJoint15_Res7B_Update@ha
    addi r3, r3, Effect_KartJoint15_Res7B_Update@l
    bl DrawEffect_SpawnDirect
    mr. r29, r3
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC058
    addi r3, r29, 0x8c
    addi r4, r30, 0xa0
    bl Vec3_Copy
    lfs f0, 0xc4(r30)
    stfs f0, 0xb0(r29)
    lwz r0, 0x9c(r31)
    stw r0, 0x11c(r29)
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC058
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBFB8:
    lwz r3, 0x98(r31)
    lwz r4, 0x9c(r31)
    bl fn_801B1660
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBFC4:
    cmpwi r27, 0x3
    bne MukadeItem_Tick_HeldAndHoming_3839_L_800EBFD8
    lwz r3, 0x98(r31)
    lwz r4, 0x9c(r31)
    bl fn_801B158C
    MukadeItem_Tick_HeldAndHoming_3839_L_800EBFD8:
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x8
    lwz r0, 0xa4(r30)
    li r3, 0x85
    li r5, 0x0
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x10(r1)
    bl SoundMgr_PlaySE_Positional
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC058
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC004:
    lwz r3, 0x98(r31)
    lwz r4, 0x9c(r31)
    bl fn_801B14B8
    li r3, 0x3
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC024:
    li r0, 0x2
    li r5, 0x0
    stb r0, 0xc9(r30)
    li r0, 0x1
    addi r3, r31, 0x34
    addi r4, r30, 0xa0
    stb r5, 0xca(r30)
    addi r5, r1, 0x44
    stb r0, 0x0(r31)
    lfs f0, 0x1c(r31)
    stfs f0, 0x14(r31)
    bl Vec3_Subtract_DestFirst
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC058:
    lbz r3, 0x0(r31)
    cmplwi r3, 0x0
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC06C
    subi r0, r3, 0x1
    stb r0, 0x0(r31)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC06C:
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC084
    li r0, 0x0
    stb r0, 0xca(r30)
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC0AC
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC084:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc9(r30)
    addi r3, r31, 0x34
    addi r4, r30, 0xa0
    addi r5, r1, 0x44
    stb r0, 0xca(r30)
    stb r0, 0x0(r31)
    bl Vec3_Subtract_DestFirst
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC0AC:
    lwz r3, 0x9c(r31)
    bl KartFxParam_GetConst1p5
    lfs f0, lbl_806D5E7C(r2)
    mr r3, r30
    fmuls f1, f0, f1
    bl Item_DecayVelocityScalar
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC0C8:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC124
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EC124
    cmpwi r0, 0x0
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EC0E8
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC124
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC0E8:
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    bne MukadeItem_Tick_HeldAndHoming_3839_L_800EC0FC
    lfs f0, lbl_806D5EA0(r2)
    stfs f0, 0x14(r31)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC0FC:
    lfs f1, lbl_806D5EA4(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    li r0, 0xa
    stw r0, 0x4(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC124:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne MukadeItem_Tick_HeldAndHoming_3839_L_800EC168
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5EA8(r2)
    lfs f0, lbl_806D5E78(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EC168
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC168:
    lfs f1, 0x14(r31)
    addi r3, r30, 0xa0
    lfs f0, lbl_806D5E94(r2)
    addi r4, r1, 0x44
    addi r5, r31, 0x34
    fadds f0, f1, f0
    stfs f0, 0x14(r31)
    lfs f1, 0x38(r31)
    lfs f0, 0x14(r31)
    fadds f0, f1, f0
    stfs f0, 0x38(r31)
    bl Vec3_Add_DestFirst
    lfs f1, lbl_806D5EAC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lwz r3, 0x9c(r31)
    bl KartFxParam_GetConst1p5
    lfs f0, lbl_806D5E7C(r2)
    mr r3, r30
    fmuls f1, f0, f1
    bl Item_DecayVelocityScalar
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC1C8:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC220
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EC220
    cmpwi r0, 0x0
    bge MukadeItem_Tick_HeldAndHoming_3839_L_800EC1E8
    b MukadeItem_Tick_HeldAndHoming_3839_L_800EC220
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC1E8:
    lfs f1, lbl_806D5E78(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D5E78(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC220:
    lfs f2, lbl_806D5E90(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq MukadeItem_Tick_HeldAndHoming_3839_L_800EC254
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    MukadeItem_Tick_HeldAndHoming_3839_L_800EC254:
    lmw r27, 0x8c(r1)
    lwz r0, 0xa4(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

/* === extracted from auto_MukadeItem_TickHeldO_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void FindNearestDriverWithinConeAndRadius();
extern void ItemObject_GetGroundTypeAt();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceProjectileSimple();
extern void Item_BendVelocityByGroundProbe();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_DecayVelocityScalar();
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern void Item_RenderCharacterScaledFromJoint12();
extern void KartCharacterParam_GetVfxBindHeightOffset();
extern void KartDriver_GetJointByIdx();
extern void KartDriver_TransformWorldToLocalY0();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void Vec3_Add_DestFirst();
extern void Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D5E78;
extern unsigned int lbl_806D5E7C;
extern unsigned int lbl_806D5E80;
extern unsigned int lbl_806D5E88;
extern unsigned int lbl_806D5E8C;
extern unsigned int lbl_806D5E98;
extern unsigned int lbl_806D5E9C;
extern unsigned int lbl_806D5EA0;
extern unsigned int lbl_806D5EA4;
extern unsigned int lbl_806D5EB0;
extern unsigned int lbl_806D5EB4;
extern unsigned int lbl_806D5EB8;
extern unsigned int lbl_806D5EBC;
extern unsigned int lbl_806D5EC0;
extern unsigned int lbl_806D5EC4;
extern unsigned int lbl_806D5EC8;
extern unsigned int lbl_806D5ECC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8032F4B0[];
extern unsigned int lbl_8032F4BC[];

/* --- function index (1 fns, .text 0x800EC268..0x800EC828) ---
 * [  0] 0x800EC268 size:0x5C0   global MukadeItem_TickHeldOrSnake_3839
 */

/* --- forward decls --- */
asm void MukadeItem_TickHeldOrSnake_3839(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_MukadeItem_TickHeldOrSnake_3839[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MukadeItem_TickHeldOrSnake_3839 = {
    (void *)&MukadeItem_TickHeldOrSnake_3839, 0x000005C0, (void *)extab_MukadeItem_TickHeldOrSnake_3839
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void MukadeItem_TickHeldOrSnake_3839(void) { /* 0x800EC268 size:0x5C0 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stw r31, 0x8c(r1)
    mr r31, r4
    stw r30, 0x88(r1)
    mr r30, r3
    lbz r3, 0xc9(r3)
    extsb r0, r3
    cmpwi r0, 0x1
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC364
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC2A4
    cmpwi r0, 0x0
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC2B0
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC2A4:
    cmpwi r0, 0x3
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC810
    b MukadeItem_TickHeldOrSnake_3839_L_800EC4F4
    MukadeItem_TickHeldOrSnake_3839_L_800EC2B0:
    lwz r0, 0x10(r30)
    cmpwi r0, 0x0
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC354
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne MukadeItem_TickHeldOrSnake_3839_L_800EC2D0
    lfs f2, lbl_806D5EB0(r2)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC2D4
    MukadeItem_TickHeldOrSnake_3839_L_800EC2D0:
    lfs f2, lbl_806D5EB4(r2)
    MukadeItem_TickHeldOrSnake_3839_L_800EC2D4:
    lwz r5, 0xa0(r30)
    addi r3, r30, 0xb8
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x5c
    lfs f3, lbl_806D5E78(r2)
    stw r5, 0x5c(r1)
    stw r0, 0x60(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x64(r1)
    lfs f1, 0xb0(r30)
    bl Item_BendVelocityByGroundProbe
    lwz r5, 0xa0(r30)
    addi r3, r30, 0xa0
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x50
    stw r5, 0x50(r1)
    stw r0, 0x54(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x58(r1)
    lwz r5, 0x98(r31)
    bl KartDriver_TransformWorldToLocalY0
    lfs f1, lbl_806D5E7C(r2)
    li r4, 0x1
    lfs f0, lbl_806D5E9C(r2)
    li r3, 0x2
    stfs f1, 0xc4(r30)
    li r0, 0x0
    stfs f0, 0x2c(r30)
    stb r4, 0x28(r30)
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC354:
    addi r3, r3, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    MukadeItem_TickHeldOrSnake_3839_L_800EC364:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC3AC
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC810
    cmpwi r0, 0x0
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC384
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC384:
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r0, 0x1
    lfs f0, lbl_806D5E78(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    MukadeItem_TickHeldOrSnake_3839_L_800EC3AC:
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC3C8
    li r0, 0x0
    stb r0, 0x28(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC3D0
    MukadeItem_TickHeldOrSnake_3839_L_800EC3C8:
    li r0, 0x1
    stb r0, 0x28(r30)
    MukadeItem_TickHeldOrSnake_3839_L_800EC3D0:
    lis r4, lbl_8032F4B0@ha
    lwz r3, 0x98(r31)
    addi r6, r4, lbl_8032F4B0@l
    lwz r5, 0x0(r6)
    lwz r4, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x74(r1)
    stw r4, 0x78(r1)
    stw r0, 0x7c(r1)
    bl KartCharacterParam_GetVfxBindHeightOffset
    lfs f0, lbl_806D5EB8(r2)
    lis r3, lbl_8032F4BC@ha
    addi r4, r3, lbl_8032F4BC@l
    lwz r7, 0x78(r1)
    fadds f0, f0, f1
    lwz r11, 0x0(r4)
    lwz r10, 0x4(r4)
    mr r3, r30
    lwz r9, 0x8(r4)
    addi r4, r1, 0x44
    stfs f0, 0x74(r1)
    addi r5, r1, 0x38
    lwz r0, 0x7c(r1)
    li r6, 0x1
    lwz r8, 0x74(r1)
    stw r11, 0x38(r1)
    lfs f1, lbl_806D5E7C(r2)
    stw r10, 0x3c(r1)
    stw r9, 0x40(r1)
    stw r8, 0x44(r1)
    stw r7, 0x48(r1)
    stw r0, 0x4c(r1)
    bl Item_RenderCharacterScaledFromJoint12
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC4BC
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC4D8
    cmpwi r0, 0x1
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC474
    b MukadeItem_TickHeldOrSnake_3839_L_800EC4D8
    MukadeItem_TickHeldOrSnake_3839_L_800EC474:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0xa0(r31)
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D5EBC(r2)
    mr r3, r30
    lfs f2, lbl_806D5E78(r2)
    addi r4, r31, 0x34
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC4BC:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC4D8:
    lwz r3, 0x98(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC4F4:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC57C
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC57C
    cmpwi r0, 0x0
    bge MukadeItem_TickHeldOrSnake_3839_L_800EC514
    b MukadeItem_TickHeldOrSnake_3839_L_800EC57C
    MukadeItem_TickHeldOrSnake_3839_L_800EC514:
    li r0, 0x1
    addi r3, r1, 0x2c
    stb r0, 0x8d(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stb r0, 0x3c(r30)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x34(r1)
    bl ItemObject_GetGroundTypeAt
    lfs f2, 0xa4(r30)
    li r3, 0x12c
    lfs f1, 0x14(r31)
    li r0, 0x0
    lfs f0, lbl_806D5E78(r2)
    fsubs f1, f2, f1
    stfs f1, 0x14(r31)
    stw r3, 0x4(r31)
    stfs f0, 0x18(r31)
    lbz r3, 0xca(r30)
    addi r3, r3, 0x1
    stb r3, 0xca(r30)
    stb r0, 0xcb(r30)
    MukadeItem_TickHeldOrSnake_3839_L_800EC57C:
    mr r3, r30
    li r4, 0x0
    li r5, 0x0
    bl Item_HomingScanAndSteer
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne MukadeItem_TickHeldOrSnake_3839_L_800EC5A0
    lfs f2, lbl_806D5E9C(r2)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC5A4
    MukadeItem_TickHeldOrSnake_3839_L_800EC5A0:
    lfs f2, lbl_806D5EA0(r2)
    MukadeItem_TickHeldOrSnake_3839_L_800EC5A4:
    cmpwi r0, 0x0
    mr r3, r30
    bne MukadeItem_TickHeldOrSnake_3839_L_800EC5B8
    lfs f1, lbl_806D5EB0(r2)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC5BC
    MukadeItem_TickHeldOrSnake_3839_L_800EC5B8:
    lfs f1, lbl_806D5EB4(r2)
    MukadeItem_TickHeldOrSnake_3839_L_800EC5BC:
    bl Item_AccelClampVelocity
    addi r3, r30, 0xa0
    bl fn_801B129C
    lfs f1, lbl_806D5E88(r2)
    lfs f0, 0xb0(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r30)
    lfs f1, lbl_806D5E8C(r2)
    lfs f0, 0x18(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x18(r31)
    lfs f1, 0x18(r31)
    bl fn_8027E9E8
    frsp f2, f1
    lfs f0, lbl_806D5E80(r2)
    lfs f1, lbl_806D5E7C(r2)
    mr r3, r30
    fmuls f0, f0, f2
    stfs f0, 0xac(r30)
    bl Item_DecayVelocityScalar
    lwz r4, 0xa0(r30)
    addi r3, r30, 0xb8
    lwz r0, 0xa4(r30)
    stw r4, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x28(r1)
    bl Vec3_ToYaw
    lwz r4, 0x98(r31)
    addi r3, r1, 0x20
    lfs f2, lbl_806D5EC0(r2)
    li r5, 0x0
    lfs f3, lbl_806D5EC4(r2)
    bl FindNearestDriverWithinConeAndRadius
    stw r3, 0x9c(r31)
    lwz r0, 0x9c(r31)
    cmplwi r0, 0x0
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC678
    li r3, 0x0
    li r0, 0x2
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r3, 0xcb(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC678:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne MukadeItem_TickHeldOrSnake_3839_L_800EC728
    li r4, 0x0
    stb r4, 0x8d(r30)
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne MukadeItem_TickHeldOrSnake_3839_L_800EC710
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x14
    lwz r0, 0xa4(r30)
    li r3, 0x86
    li r5, 0x0
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    bl SoundMgr_PlaySE_Positional
    addi r3, r30, 0xb8
    addi r5, r30, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D5EA0(r2)
    li r4, 0x2
    lfs f1, lbl_806D5EC8(r2)
    li r3, 0x0
    stfs f0, 0xbc(r30)
    li r0, 0x4
    lfs f0, 0xb8(r30)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r30)
    lfs f0, 0xc0(r30)
    fmuls f0, f0, f1
    stfs f0, 0xc0(r30)
    stb r4, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC710:
    li r3, 0x2
    li r0, 0x6
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC728:
    mr r3, r30
    addi r4, r1, 0x68
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq MukadeItem_TickHeldOrSnake_3839_L_800EC7AC
    li r0, 0x0
    lfs f1, lbl_806D5E98(r2)
    stb r0, 0x8d(r30)
    mr r3, r30
    lfs f2, lbl_806D5EA0(r2)
    addi r4, r1, 0x8
    lwz r8, 0x68(r1)
    li r5, 0x86
    lwz r7, 0x6c(r1)
    li r6, 0x2
    lwz r0, 0x70(r1)
    stw r8, 0x8(r1)
    stw r7, 0xc(r1)
    stw r0, 0x10(r1)
    bl Item_BounceOffWall
    lfs f1, lbl_806D5EA4(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    li r4, 0x2
    li r3, 0x0
    li r0, 0x7
    stb r4, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC7AC:
    lfs f1, lbl_806D5ECC(r2)
    mr r3, r30
    addi r4, r31, 0x14
    fmr f2, f1
    bl Item_AdvanceProjectileSimple
    cmpwi r3, 0x0
    bne MukadeItem_TickHeldOrSnake_3839_L_800EC7E8
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x9
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b MukadeItem_TickHeldOrSnake_3839_L_800EC810
    MukadeItem_TickHeldOrSnake_3839_L_800EC7E8:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne MukadeItem_TickHeldOrSnake_3839_L_800EC810
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x5
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    MukadeItem_TickHeldOrSnake_3839_L_800EC810:
    lwz r0, 0x94(r1)
    lwz r31, 0x8c(r1)
    lwz r30, 0x88(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

/* === extracted from auto_MukadeItem_Dispatch_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemObject_GetGroundTypeAt();
extern void Item_DecayVelocityScalar();
extern void Item_OrbitAnchorKart();
extern void MukadeItem_TickHeldOrSnake_3839();
extern void MukadeItem_Tick_HeldAndHoming_3839();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform();
extern void Vec3_Add_DestFirst();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5E78;
extern unsigned int lbl_806D5E7C;
extern unsigned int lbl_806D5E80;
extern unsigned int lbl_806D5E94;
extern unsigned int lbl_806D5EA8;
extern unsigned int lbl_806D5EAC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_804215E8[];

/* --- function index (1 fns, .text 0x800EC828..0x800ED010) ---
 * [  0] 0x800EC828 size:0x7E8   global MukadeItem_Dispatch_3839
 */

/* --- forward decls --- */
asm void MukadeItem_Dispatch_3839(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_MukadeItem_Dispatch_3839[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MukadeItem_Dispatch_3839 = {
    (void *)&MukadeItem_Dispatch_3839, 0x000007E8, (void *)extab_MukadeItem_Dispatch_3839
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void MukadeItem_Dispatch_3839(void) { /* 0x800EC828 size:0x7E8 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq MukadeItem_Dispatch_3839_L_800EC8C8
    bge MukadeItem_Dispatch_3839_L_800EC868
    cmpwi r0, 0x0
    beq MukadeItem_Dispatch_3839_L_800EC874
    bge MukadeItem_Dispatch_3839_L_800EC8B8
    b MukadeItem_Dispatch_3839_L_800ECF54
    MukadeItem_Dispatch_3839_L_800EC868:
    cmpwi r0, 0x4
    bge MukadeItem_Dispatch_3839_L_800ECF54
    b MukadeItem_Dispatch_3839_L_800ECF44
    MukadeItem_Dispatch_3839_L_800EC874:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x39
    bne MukadeItem_Dispatch_3839_L_800EC890
    addi r3, r30, 0x14
    li r4, 0x3d
    bl SpriteSlot_InitNonLoop
    b MukadeItem_Dispatch_3839_L_800EC89C
    MukadeItem_Dispatch_3839_L_800EC890:
    addi r3, r30, 0x14
    li r4, 0x3e
    bl SpriteSlot_InitNonLoop
    MukadeItem_Dispatch_3839_L_800EC89C:
    li r0, 0x3
    li r3, 0x0
    stb r0, 0x8c(r30)
    li r0, 0x1
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    MukadeItem_Dispatch_3839_L_800EC8B8:
    mr r3, r30
    mr r4, r31
    bl MukadeItem_TickHeldOrSnake_3839
    b MukadeItem_Dispatch_3839_L_800ECF54
    MukadeItem_Dispatch_3839_L_800EC8C8:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt MukadeItem_Dispatch_3839_L_800ECF54
    lis r4, jumptable_804215E8@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_804215E8@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    mr r4, r31
    bl MukadeItem_Tick_HeldAndHoming_3839
    b MukadeItem_Dispatch_3839_L_800ECF54
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Dispatch_3839_L_800EC984
    bge MukadeItem_Dispatch_3839_L_800EC984
    cmpwi r0, 0x0
    bge MukadeItem_Dispatch_3839_L_800EC91C
    b MukadeItem_Dispatch_3839_L_800EC984
    MukadeItem_Dispatch_3839_L_800EC91C:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x60
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x60(r1)
    stw r0, 0x64(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x68(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800EC95C
    li r0, 0xa
    stw r0, 0x4(r31)
    b MukadeItem_Dispatch_3839_L_800EC964
    MukadeItem_Dispatch_3839_L_800EC95C:
    li r0, 0x0
    stw r0, 0x4(r31)
    MukadeItem_Dispatch_3839_L_800EC964:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    bne MukadeItem_Dispatch_3839_L_800EC978
    lfs f0, lbl_806D5E78(r2)
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800EC978:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    MukadeItem_Dispatch_3839_L_800EC984:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne MukadeItem_Dispatch_3839_L_800EC9C8
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5EA8(r2)
    lfs f0, lbl_806D5E78(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge MukadeItem_Dispatch_3839_L_800EC9C8
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b MukadeItem_Dispatch_3839_L_800ECF54
    MukadeItem_Dispatch_3839_L_800EC9C8:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800EC9E4
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5E94(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800EC9E4:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x6c
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x14
    li r5, 0x0
    stw r6, 0x6c(r1)
    stw r0, 0x70(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x74(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq MukadeItem_Dispatch_3839_L_800ECA34
    lfs f1, 0x14(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x14(r1)
    stfs f0, 0x14(r31)
    MukadeItem_Dispatch_3839_L_800ECA34:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECA54
    lfs f1, lbl_806D5EAC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    MukadeItem_Dispatch_3839_L_800ECA54:
    lfs f1, lbl_806D5E7C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b MukadeItem_Dispatch_3839_L_800ECF54
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Dispatch_3839_L_800ECAC8
    bge MukadeItem_Dispatch_3839_L_800ECAC8
    cmpwi r0, 0x0
    bge MukadeItem_Dispatch_3839_L_800ECA84
    b MukadeItem_Dispatch_3839_L_800ECAC8
    MukadeItem_Dispatch_3839_L_800ECA84:
    lfs f1, lbl_806D5E78(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    addi r3, r31, 0x34
    stb r0, 0x3c(r30)
    addi r4, r30, 0xa0
    lwz r5, 0x9c(r30)
    addi r5, r5, 0xa0
    bl Vec3_Subtract_DestFirst
    li r0, 0x1e
    stw r0, 0x4(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    MukadeItem_Dispatch_3839_L_800ECAC8:
    lfs f1, lbl_806D5E7C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, lbl_806D5E80(r2)
    mr r3, r30
    lwz r5, 0x4(r31)
    addi r4, r31, 0x34
    fmr f2, f1
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq MukadeItem_Dispatch_3839_L_800ECF54
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b MukadeItem_Dispatch_3839_L_800ECF54
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Dispatch_3839_L_800ECB94
    bge MukadeItem_Dispatch_3839_L_800ECB94
    cmpwi r0, 0x0
    bge MukadeItem_Dispatch_3839_L_800ECB2C
    b MukadeItem_Dispatch_3839_L_800ECB94
    MukadeItem_Dispatch_3839_L_800ECB2C:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x48
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x48(r1)
    stw r0, 0x4c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x50(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECB6C
    li r0, 0xa
    stw r0, 0x4(r31)
    b MukadeItem_Dispatch_3839_L_800ECB74
    MukadeItem_Dispatch_3839_L_800ECB6C:
    li r0, 0x0
    stw r0, 0x4(r31)
    MukadeItem_Dispatch_3839_L_800ECB74:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    bne MukadeItem_Dispatch_3839_L_800ECB88
    lfs f0, lbl_806D5E78(r2)
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800ECB88:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    MukadeItem_Dispatch_3839_L_800ECB94:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne MukadeItem_Dispatch_3839_L_800ECBD8
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5EA8(r2)
    lfs f0, lbl_806D5E78(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge MukadeItem_Dispatch_3839_L_800ECBD8
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b MukadeItem_Dispatch_3839_L_800ECF54
    MukadeItem_Dispatch_3839_L_800ECBD8:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECBF4
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5E94(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800ECBF4:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x54
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x10
    li r5, 0x0
    stw r6, 0x54(r1)
    stw r0, 0x58(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x5c(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq MukadeItem_Dispatch_3839_L_800ECC44
    lfs f1, 0x10(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x10(r1)
    stfs f0, 0x14(r31)
    MukadeItem_Dispatch_3839_L_800ECC44:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECC64
    lfs f1, lbl_806D5EAC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    MukadeItem_Dispatch_3839_L_800ECC64:
    lfs f1, lbl_806D5E7C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b MukadeItem_Dispatch_3839_L_800ECF54
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Dispatch_3839_L_800ECCFC
    bge MukadeItem_Dispatch_3839_L_800ECCFC
    cmpwi r0, 0x0
    bge MukadeItem_Dispatch_3839_L_800ECC94
    b MukadeItem_Dispatch_3839_L_800ECCFC
    MukadeItem_Dispatch_3839_L_800ECC94:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x30
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x30(r1)
    stw r0, 0x34(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x38(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECCD4
    li r0, 0xa
    stw r0, 0x4(r31)
    b MukadeItem_Dispatch_3839_L_800ECCDC
    MukadeItem_Dispatch_3839_L_800ECCD4:
    li r0, 0x0
    stw r0, 0x4(r31)
    MukadeItem_Dispatch_3839_L_800ECCDC:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    bne MukadeItem_Dispatch_3839_L_800ECCF0
    lfs f0, lbl_806D5E78(r2)
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800ECCF0:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    MukadeItem_Dispatch_3839_L_800ECCFC:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne MukadeItem_Dispatch_3839_L_800ECD40
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5EA8(r2)
    lfs f0, lbl_806D5E78(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge MukadeItem_Dispatch_3839_L_800ECD40
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b MukadeItem_Dispatch_3839_L_800ECF54
    MukadeItem_Dispatch_3839_L_800ECD40:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECD5C
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5E94(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800ECD5C:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x3c
    lwz r0, 0xa4(r30)
    addi r4, r1, 0xc
    li r5, 0x0
    stw r6, 0x3c(r1)
    stw r0, 0x40(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x44(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq MukadeItem_Dispatch_3839_L_800ECDAC
    lfs f1, 0xc(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0xc(r1)
    stfs f0, 0x14(r31)
    MukadeItem_Dispatch_3839_L_800ECDAC:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECDCC
    lfs f1, lbl_806D5EAC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    MukadeItem_Dispatch_3839_L_800ECDCC:
    lfs f1, lbl_806D5E7C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b MukadeItem_Dispatch_3839_L_800ECF54
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq MukadeItem_Dispatch_3839_L_800ECE64
    bge MukadeItem_Dispatch_3839_L_800ECE64
    cmpwi r0, 0x0
    bge MukadeItem_Dispatch_3839_L_800ECDFC
    b MukadeItem_Dispatch_3839_L_800ECE64
    MukadeItem_Dispatch_3839_L_800ECDFC:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x18
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x20(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECE3C
    li r0, 0xa
    stw r0, 0x4(r31)
    b MukadeItem_Dispatch_3839_L_800ECE44
    MukadeItem_Dispatch_3839_L_800ECE3C:
    li r0, 0x0
    stw r0, 0x4(r31)
    MukadeItem_Dispatch_3839_L_800ECE44:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    bne MukadeItem_Dispatch_3839_L_800ECE58
    lfs f0, lbl_806D5E78(r2)
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800ECE58:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    MukadeItem_Dispatch_3839_L_800ECE64:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne MukadeItem_Dispatch_3839_L_800ECEA8
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5EA8(r2)
    lfs f0, lbl_806D5E78(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge MukadeItem_Dispatch_3839_L_800ECEA8
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b MukadeItem_Dispatch_3839_L_800ECF54
    MukadeItem_Dispatch_3839_L_800ECEA8:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECEC4
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5E94(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    MukadeItem_Dispatch_3839_L_800ECEC4:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x24
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x8
    li r5, 0x0
    stw r6, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x2c(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq MukadeItem_Dispatch_3839_L_800ECF14
    lfs f1, 0x8(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stfs f0, 0x14(r31)
    MukadeItem_Dispatch_3839_L_800ECF14:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq MukadeItem_Dispatch_3839_L_800ECF34
    lfs f1, lbl_806D5EAC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    MukadeItem_Dispatch_3839_L_800ECF34:
    lfs f1, lbl_806D5E7C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b MukadeItem_Dispatch_3839_L_800ECF54
    MukadeItem_Dispatch_3839_L_800ECF44:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b MukadeItem_Dispatch_3839_L_800ECFF8
    MukadeItem_Dispatch_3839_L_800ECF54:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r6, 0xac(r30)
    addi r3, r30, 0x14
    lwz r0, 0xb0(r30)
    addi r4, r1, 0x84
    addi r5, r1, 0x78
    stw r6, 0x78(r1)
    stw r0, 0x7c(r1)
    lwz r0, 0xb4(r30)
    stw r0, 0x80(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x84(r1)
    stw r0, 0x88(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x8c(r1)
    lfs f1, 0xc4(r30)
    bl SpriteSlot_SetTransform
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq MukadeItem_Dispatch_3839_L_800ECFBC
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    MukadeItem_Dispatch_3839_L_800ECFBC:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq MukadeItem_Dispatch_3839_L_800ECFD0
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    MukadeItem_Dispatch_3839_L_800ECFD0:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq MukadeItem_Dispatch_3839_L_800ECFE4
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    MukadeItem_Dispatch_3839_L_800ECFE4:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq MukadeItem_Dispatch_3839_L_800ECFF8
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    MukadeItem_Dispatch_3839_L_800ECFF8:
    lwz r0, 0xa4(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

