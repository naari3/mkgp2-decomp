/* === extracted from auto_EggItem_OnGroundDrif_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void FAbs_FloatAsDouble();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceFallingDrop();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_DecayVelocityScalar();
extern void Item_ProbeLateralGroundPitch();
extern void Vec2_RotateY();
extern void Vec3_ToYaw();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D5E28;
extern unsigned int lbl_806D5E30;
extern unsigned int lbl_806D5E34;
extern unsigned int lbl_806D5E38;
extern unsigned int lbl_806D5E3C;
extern unsigned int lbl_806D5E40;
extern unsigned int lbl_806D5E44;
extern unsigned int lbl_806D5E48;
extern unsigned int lbl_806D5E4C;
extern unsigned int lbl_806D5E50;
extern unsigned int lbl_806D5E54;
extern unsigned int lbl_806D5E58;
extern unsigned int lbl_806D5E5C;
extern unsigned int lbl_806D5E60;

/* --- function index (1 fns, .text 0x800EADB4..0x800EB01C) ---
 * [  0] 0x800EADB4 size:0x268   global EggItem_OnGroundDriftTick_3B3C
 */

/* --- forward decls --- */
asm void EggItem_OnGroundDriftTick_3B3C(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EggItem_OnGroundDriftTick_3B3C[8] = {
    0x08, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EggItem_OnGroundDriftTick_3B3C = {
    (void *)&EggItem_OnGroundDriftTick_3B3C, 0x00000268, (void *)extab_EggItem_OnGroundDriftTick_3B3C
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void EggItem_OnGroundDriftTick_3B3C(void) { /* 0x800EADB4 size:0x268 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    mr r31, r3
    lbz r0, 0xc9(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq EggItem_OnGroundDriftTick_3B3C_L_800EAE1C
    bge EggItem_OnGroundDriftTick_3B3C_L_800EAE1C
    cmpwi r0, 0x0
    bge EggItem_OnGroundDriftTick_3B3C_L_800EADF0
    b EggItem_OnGroundDriftTick_3B3C_L_800EAE1C
    EggItem_OnGroundDriftTick_3B3C_L_800EADF0:
    lbz r0, 0xcb(r31)
    cmpwi r0, 0x5
    beq EggItem_OnGroundDriftTick_3B3C_L_800EAE08
    li r0, 0xa
    stw r0, 0x4(r4)
    b EggItem_OnGroundDriftTick_3B3C_L_800EAE10
    EggItem_OnGroundDriftTick_3B3C_L_800EAE08:
    li r0, 0x0
    stw r0, 0x4(r4)
    EggItem_OnGroundDriftTick_3B3C_L_800EAE10:
    lbz r3, 0xc9(r31)
    addi r0, r3, 0x1
    stb r0, 0xc9(r31)
    EggItem_OnGroundDriftTick_3B3C_L_800EAE1C:
    lwz r0, 0x4(r4)
    cmplwi r0, 0x0
    bne EggItem_OnGroundDriftTick_3B3C_L_800EAE60
    lfs f2, 0x2c(r31)
    lfs f1, lbl_806D5E38(r2)
    lfs f0, lbl_806D5E28(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r31)
    lfs f1, 0x2c(r31)
    fcmpo cr0, f1, f0
    bge EggItem_OnGroundDriftTick_3B3C_L_800EAE60
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r31)
    stb r0, 0xc8(r31)
    stb r3, 0xc9(r31)
    b EggItem_OnGroundDriftTick_3B3C_L_800EB000
    EggItem_OnGroundDriftTick_3B3C_L_800EAE60:
    lfs f1, 0xbc(r31)
    lfs f0, lbl_806D5E3C(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r31)
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne EggItem_OnGroundDriftTick_3B3C_L_800EAE84
    lfs f2, lbl_806D5E40(r2)
    b EggItem_OnGroundDriftTick_3B3C_L_800EAE88
    EggItem_OnGroundDriftTick_3B3C_L_800EAE84:
    lfs f2, lbl_806D5E44(r2)
    EggItem_OnGroundDriftTick_3B3C_L_800EAE88:
    cmpwi r0, 0x0
    mr r3, r31
    bne EggItem_OnGroundDriftTick_3B3C_L_800EAE9C
    lfs f1, lbl_806D5E48(r2)
    b EggItem_OnGroundDriftTick_3B3C_L_800EAEA0
    EggItem_OnGroundDriftTick_3B3C_L_800EAE9C:
    lfs f1, lbl_806D5E4C(r2)
    EggItem_OnGroundDriftTick_3B3C_L_800EAEA0:
    bl Item_AccelClampVelocity
    lfs f1, lbl_806D5E34(r2)
    lfs f0, 0xac(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r31)
    addi r3, r31, 0xb8
    bl Vec3_ToYaw
    fmr f2, f1
    lfs f1, 0xb0(r31)
    lfs f3, lbl_806D5E50(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xb0(r31)
    mr r3, r31
    lfs f1, lbl_806D5E30(r2)
    bl Item_DecayVelocityScalar
    mr r3, r31
    addi r4, r1, 0x28
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq EggItem_OnGroundDriftTick_3B3C_L_800EAF2C
    lwz r6, 0x28(r1)
    mr r3, r31
    lwz r7, 0x2c(r1)
    addi r4, r1, 0x1c
    lwz r0, 0x30(r1)
    li r5, 0x0
    stw r6, 0x1c(r1)
    li r6, 0x0
    lfs f1, lbl_806D5E54(r2)
    stw r7, 0x20(r1)
    lfs f2, lbl_806D5E28(r2)
    stw r0, 0x24(r1)
    bl Item_BounceOffWall
    EggItem_OnGroundDriftTick_3B3C_L_800EAF2C:
    lfs f1, 0xac(r31)
    bl BuildOrientationFromYaw
    bl FAbs_FloatAsDouble
    lfs f1, lbl_806D5E30(r2)
    mr r3, r31
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq EggItem_OnGroundDriftTick_3B3C_L_800EB000
    lwz r0, 0xc(r1)
    cmpwi r0, 0x0
    beq EggItem_OnGroundDriftTick_3B3C_L_800EB000
    lfs f1, 0xbc(r31)
    addi r3, r1, 0x10
    lfs f0, lbl_806D5E58(r2)
    lfs f2, lbl_806D5E5C(r2)
    fmuls f0, f1, f0
    stfs f0, 0xbc(r31)
    lwz r4, 0xa0(r31)
    lwz r0, 0xa4(r31)
    lfs f0, 0x8(r1)
    stw r4, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xa8(r31)
    stw r0, 0x18(r1)
    lfs f3, 0xa4(r31)
    lfs f1, 0xb0(r31)
    fsubs f3, f3, f0
    bl Item_ProbeLateralGroundPitch
    fmr f31, f1
    bl FAbs_FloatAsDouble
    lfs f2, lbl_806D5E34(r2)
    fcmpo cr0, f2, f1
    bge EggItem_OnGroundDriftTick_3B3C_L_800EB000
    lfs f0, lbl_806D5E28(r2)
    fcmpo cr0, f0, f31
    bge EggItem_OnGroundDriftTick_3B3C_L_800EAFE4
    fsubs f0, f31, f2
    addi r3, r31, 0xb8
    lfs f1, lbl_806D5E60(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    b EggItem_OnGroundDriftTick_3B3C_L_800EB000
    EggItem_OnGroundDriftTick_3B3C_L_800EAFE4:
    fadds f0, f2, f31
    addi r3, r31, 0xb8
    lfs f1, lbl_806D5E60(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    EggItem_OnGroundDriftTick_3B3C_L_800EB000:
    psq_l f31, 0x48(r1), 0, 0
    lwz r0, 0x54(r1)
    lfd f31, 0x40(r1)
    lwz r31, 0x3c(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}



/* === extracted from auto_EggItem_Tick_HeldAnd_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void DrawEffect_ItemHitOriented_Spawn();
extern void FAbs_FloatAsDouble();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceFallingDrop();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void Item_InitLaunchFromKart();
extern void Item_ProbeLateralGroundPitch();
extern void KartDriver_GetJointByIdx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_CountActiveSEInstances();
extern void SoundMgr_PlaySE_Positional();
extern void SoundMgr_PlaySE_WithChannel();
extern void SoundMgr_StopSE_OrSpecial();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void Vec2_RotateY();
extern void Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D5E28;
extern unsigned int lbl_806D5E30;
extern unsigned int lbl_806D5E34;
extern unsigned int lbl_806D5E3C;
extern unsigned int lbl_806D5E40;
extern unsigned int lbl_806D5E44;
extern unsigned int lbl_806D5E48;
extern unsigned int lbl_806D5E4C;
extern unsigned int lbl_806D5E50;
extern unsigned int lbl_806D5E54;
extern unsigned int lbl_806D5E58;
extern unsigned int lbl_806D5E5C;
extern unsigned int lbl_806D5E60;
extern unsigned int lbl_806D5E64;
extern unsigned int lbl_806D5E68;
extern unsigned int lbl_806D5E6C;
extern unsigned int lbl_806D5E70;
extern unsigned int lbl_806D5E74;

/* --- function index (1 fns, .text 0x800EB01C..0x800EB870) ---
 * [  0] 0x800EB01C size:0x854   global EggItem_Tick_HeldAndHoming_3B3C
 */

/* --- forward decls --- */
asm void EggItem_Tick_HeldAndHoming_3B3C(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EggItem_Tick_HeldAndHoming_3B3C[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EggItem_Tick_HeldAndHoming_3B3C = {
    (void *)&EggItem_Tick_HeldAndHoming_3B3C, 0x00000854, (void *)extab_EggItem_Tick_HeldAndHoming_3B3C
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void EggItem_Tick_HeldAndHoming_3B3C(void) { /* 0x800EB01C size:0x854 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stw r31, 0x8c(r1)
    stw r30, 0x88(r1)
    stw r29, 0x84(r1)
    stw r28, 0x80(r1)
    mr r30, r3
    mr r31, r4
    lbz r4, 0xc9(r3)
    extsb r0, r4
    cmpwi r0, 0x1
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB084
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB068
    cmpwi r0, 0x0
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB074
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB068:
    cmpwi r0, 0x3
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB1A8
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB074:
    addi r3, r4, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB084:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB0CC
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    cmpwi r0, 0x0
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB0A4
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB0A4:
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r0, 0x1
    lfs f0, lbl_806D5E28(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB0CC:
    lfs f1, lbl_806D5E30(r2)
    mr r3, r30
    lfs f2, lbl_806D5E28(r2)
    li r4, 0x1
    lfs f3, lbl_806D5E64(r2)
    bl GabyouItem_BuildLocalTransformFromHandJoint
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB100
    li r0, 0x0
    stb r0, 0x28(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB108
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB100:
    li r0, 0x1
    stb r0, 0x28(r30)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB108:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB170
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB18C
    cmpwi r0, 0x1
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB128
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB18C
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB128:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0xa0(r31)
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D5E5C(r2)
    mr r3, r30
    lfs f2, lbl_806D5E68(r2)
    addi r4, r31, 0x34
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB170:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB18C:
    lwz r3, 0x98(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB1A8:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB214
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB214
    cmpwi r0, 0x0
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB1C8
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB214
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB1C8:
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r6, 0x1
    li r5, 0x258
    stb r6, 0x8d(r30)
    li r4, 0x0
    li r3, 0x8
    li r0, -0x1
    stb r6, 0x3c(r30)
    stw r5, 0x4(r31)
    stw r4, 0xc(r31)
    stw r4, 0x8(r31)
    stb r3, 0x0(r31)
    stw r0, 0x30(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB214:
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5E3C(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB238
    lfs f2, lbl_806D5E40(r2)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB23C
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB238:
    lfs f2, lbl_806D5E44(r2)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB23C:
    cmpwi r0, 0x0
    mr r3, r30
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB250
    lfs f1, lbl_806D5E48(r2)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB254
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB250:
    lfs f1, lbl_806D5E4C(r2)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB254:
    bl Item_AccelClampVelocity
    addi r3, r30, 0xa0
    bl fn_801B129C
    lfs f1, lbl_806D5E34(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    fmr f2, f1
    lfs f1, 0xb0(r30)
    lfs f3, lbl_806D5E50(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xb0(r30)
    mr r3, r30
    lfs f1, lbl_806D5E30(r2)
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB384
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB2C4
    cmpwi r28, 0x1
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB2D4
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB2FC
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB47C
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB2C4:
    cmpwi r28, 0x5
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB470
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB47C
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB408
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB2D4:
    lwz r3, 0x8(r30)
    bl ItemAlias_HitRemapLookup
    extsh r29, r3
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    mr r5, r29
    li r6, 0x0
    bl fn_801B1D5C
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB2FC:
    cmpwi r28, 0x2
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB318
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB318:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB350
    li r3, 0xc8
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB350:
    cmpwi r28, 0x1
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB364
    li r0, 0x1
    stb r0, 0x0(r31)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB36C
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB364:
    li r0, 0x0
    stb r0, 0x0(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB36C:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc8(r30)
    stb r0, 0xc9(r30)
    stb r0, 0xcb(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB384:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    lwz r4, 0xb8(r30)
    mr r3, r30
    lwz r0, 0xbc(r30)
    stw r4, 0x58(r1)
    stw r0, 0x5c(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x60(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x64(r1)
    stw r0, 0x68(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x6c(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0x64
    addi r6, r1, 0x58
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0xc(r31)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB47C
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB408:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B14B8
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB454
    li r3, 0xc8
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB454:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x3
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB470:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB47C:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB494
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB494:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB4FC
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D5E28(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB4E0
    li r3, 0xc8
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB4E0:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x4
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB4FC:
    mr r3, r30
    addi r4, r1, 0x70
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB5C8
    lbz r3, 0x0(r31)
    cmplwi r3, 0x0
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB528
    subi r0, r3, 0x1
    stb r0, 0x0(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB528:
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB56C
    lwz r6, 0x70(r1)
    mr r3, r30
    lwz r7, 0x74(r1)
    addi r4, r1, 0x4c
    lwz r0, 0x78(r1)
    li r5, 0xcb
    stw r6, 0x4c(r1)
    li r6, 0x3
    lfs f1, lbl_806D5E54(r2)
    stw r7, 0x50(r1)
    lfs f2, lbl_806D5E28(r2)
    stw r0, 0x54(r1)
    bl Item_BounceOffWall
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB5C8
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB56C:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D5E28(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB5AC
    li r3, 0xc8
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB5AC:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x7
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB5C8:
    lfs f1, 0xac(r30)
    bl BuildOrientationFromYaw
    bl FAbs_FloatAsDouble
    lfs f0, lbl_806D5E6C(r2)
    mr r3, r30
    lfs f3, lbl_806D5E74(r2)
    fdivs f0, f1, f0
    fcmpo cr0, f0, f3
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB5F4
    lfs f1, lbl_806D5E30(r2)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB608
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB5F4:
    fsubs f1, f0, f3
    lfs f2, lbl_806D5E70(r2)
    lfs f0, lbl_806D5E30(r2)
    fdivs f1, f1, f3
    fmadds f1, f2, f1, f0
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB608:
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB7B0
    lwz r0, 0xc(r1)
    cmpwi r0, 0x0
    beq EggItem_Tick_HeldAndHoming_3B3C_L_800EB790
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB67C
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x40
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x34
    li r5, 0x3
    stw r6, 0x34(r1)
    stw r0, 0x38(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x3c(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x40(r1)
    stw r0, 0x44(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x48(r1)
    bl DrawEffect_ItemHitOriented_Spawn
    li r0, 0x3
    stw r0, 0x8(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB67C:
    lfs f1, 0xbc(r30)
    addi r3, r1, 0x28
    lfs f0, lbl_806D5E58(r2)
    lfs f2, lbl_806D5E5C(r2)
    fmuls f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stw r4, 0x28(r1)
    stw r0, 0x2c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x30(r1)
    lfs f3, 0xa4(r30)
    lfs f1, 0xb0(r30)
    fsubs f3, f3, f0
    bl Item_ProbeLateralGroundPitch
    fmr f31, f1
    bl FAbs_FloatAsDouble
    lfs f2, lbl_806D5E34(r2)
    fcmpo cr0, f2, f1
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB71C
    lfs f0, lbl_806D5E28(r2)
    fcmpo cr0, f0, f31
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB700
    fsubs f0, f31, f2
    addi r3, r30, 0xb8
    lfs f1, lbl_806D5E60(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB71C
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB700:
    fadds f0, f2, f31
    addi r3, r30, 0xb8
    lfs f1, lbl_806D5E60(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB71C:
    lwz r5, 0x30(r31)
    cmpwi r5, 0x0
    bge EggItem_Tick_HeldAndHoming_3B3C_L_800EB768
    li r3, 0xc8
    bl SoundMgr_CountActiveSEInstances
    stw r3, 0x30(r31)
    lwz r5, 0x30(r31)
    cmpwi r5, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB7F8
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x1c
    lwz r0, 0xa4(r30)
    li r3, 0xc8
    stw r6, 0x1c(r1)
    stw r0, 0x20(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x24(r1)
    bl SoundMgr_PlaySE_Positional
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB7F8
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB768:
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x10
    lwz r0, 0xa4(r30)
    li r3, 0xc8
    stw r6, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x18(r1)
    bl SoundMgr_PlaySE_WithChannel
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB7F8
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB790:
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB7F8
    li r3, 0xc8
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB7F8
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB7B0:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB7DC
    li r3, 0xc8
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB7DC:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x9
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB7F8:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne EggItem_Tick_HeldAndHoming_3B3C_L_800EB848
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt EggItem_Tick_HeldAndHoming_3B3C_L_800EB830
    li r3, 0xc8
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB830:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x5
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    EggItem_Tick_HeldAndHoming_3B3C_L_800EB848:
    psq_l f31, 0x98(r1), 0, 0
    lwz r0, 0xa4(r1)
    lfd f31, 0x90(r1)
    lwz r31, 0x8c(r1)
    lwz r30, 0x88(r1)
    lwz r29, 0x84(r1)
    lwz r28, 0x80(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}



/* === extracted from auto_EggItem_Dispatch_3B3_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void EggItem_OnGroundDriftTick_3B3C();
extern void EggItem_Tick_HeldAndHoming_3B3C();
extern void GetSpawnPosition();
extern void ItemHit_Dispatch();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_PrepareHitRebound();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void ShellPile_Spawn();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetTransform();
extern void Vec3_AddNormalizedXZ();
extern void Vec3_Add_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5E28;
extern unsigned int lbl_806D5E2C;
extern unsigned int lbl_806D5E30;
extern unsigned int lbl_806D5E34;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_804215C0[];
extern unsigned int lbl_8032F480[];
extern unsigned int lbl_8032F494[];

/* --- function index (1 fns, .text 0x800EB870..0x800EBC00) ---
 * [  0] 0x800EB870 size:0x390   global EggItem_Dispatch_3B3C
 */

/* --- forward decls --- */
asm void EggItem_Dispatch_3B3C(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EggItem_Dispatch_3B3C[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EggItem_Dispatch_3B3C = {
    (void *)&EggItem_Dispatch_3B3C, 0x00000390, (void *)extab_EggItem_Dispatch_3B3C
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void EggItem_Dispatch_3B3C(void) { /* 0x800EB870 size:0x390 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq EggItem_Dispatch_3B3C_L_800EB924
    bge EggItem_Dispatch_3B3C_L_800EB8B0
    cmpwi r0, 0x0
    beq EggItem_Dispatch_3B3C_L_800EB8BC
    bge EggItem_Dispatch_3B3C_L_800EB914
    b EggItem_Dispatch_3B3C_L_800EBB44
    EggItem_Dispatch_3B3C_L_800EB8B0:
    cmpwi r0, 0x4
    bge EggItem_Dispatch_3B3C_L_800EBB44
    b EggItem_Dispatch_3B3C_L_800EBB34
    EggItem_Dispatch_3B3C_L_800EB8BC:
    addi r3, r30, 0x14
    li r4, 0x3c
    bl SpriteSlot_InitNonLoop
    lis r4, lbl_8032F480@ha
    addi r3, r30, 0x14
    addi r4, r4, lbl_8032F480@l
    li r5, 0x10
    li r6, 0x0
    bl SpriteSlot_SetJointVisibilityByName
    lis r4, lbl_8032F494@ha
    addi r3, r30, 0x14
    addi r4, r4, lbl_8032F494@l
    li r5, 0x10
    li r6, 0x1
    bl SpriteSlot_SetJointVisibilityByName
    li r0, 0x4
    li r3, 0x0
    stb r0, 0x8c(r30)
    li r0, 0x1
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    EggItem_Dispatch_3B3C_L_800EB914:
    mr r3, r30
    mr r4, r31
    bl EggItem_Tick_HeldAndHoming_3B3C
    b EggItem_Dispatch_3B3C_L_800EBB44
    EggItem_Dispatch_3B3C_L_800EB924:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt EggItem_Dispatch_3B3C_L_800EBB44
    lis r4, jumptable_804215C0@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_804215C0@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    lwz r3, 0x9c(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x8
    bl Mtx44_GetTranslation_RowMajor
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq EggItem_Dispatch_3B3C_L_800EB9A0
    bge EggItem_Dispatch_3B3C_L_800EB9A0
    cmpwi r0, 0x0
    bge EggItem_Dispatch_3B3C_L_800EB980
    b EggItem_Dispatch_3B3C_L_800EB9A0
    EggItem_Dispatch_3B3C_L_800EB980:
    mr r3, r30
    addi r4, r31, 0x40
    addi r5, r31, 0x34
    addi r6, r31, 0x4
    bl Item_PrepareHitRebound
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    EggItem_Dispatch_3B3C_L_800EB9A0:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne EggItem_Dispatch_3B3C_L_800EB9F0
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq EggItem_Dispatch_3B3C_L_800EB9CC
    lwz r6, 0x9c(r31)
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    bl ItemHit_Dispatch
    EggItem_Dispatch_3B3C_L_800EB9CC:
    mr r3, r30
    mr r4, r31
    bl ShellPile_Spawn
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b EggItem_Dispatch_3B3C_L_800EBB44
    EggItem_Dispatch_3B3C_L_800EB9F0:
    lwz r6, 0x34(r31)
    mr r3, r30
    lwz r0, 0x38(r31)
    addi r4, r31, 0x40
    addi r5, r1, 0x14
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0x3c(r31)
    stw r0, 0x1c(r1)
    bl Vec3_AddNormalizedXZ
    addi r3, r30, 0xa0
    addi r4, r1, 0x8
    addi r5, r31, 0x40
    bl Vec3_Add_DestFirst
    lfs f1, lbl_806D5E30(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, lbl_806D5E34(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b EggItem_Dispatch_3B3C_L_800EBB44
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq EggItem_Dispatch_3B3C_L_800EBAA4
    bge EggItem_Dispatch_3B3C_L_800EBAA4
    cmpwi r0, 0x0
    bge EggItem_Dispatch_3B3C_L_800EBA6C
    b EggItem_Dispatch_3B3C_L_800EBAA4
    EggItem_Dispatch_3B3C_L_800EBA6C:
    lfs f1, lbl_806D5E28(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D5E28(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    EggItem_Dispatch_3B3C_L_800EBAA4:
    lfs f2, lbl_806D5E2C(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq EggItem_Dispatch_3B3C_L_800EBB44
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b EggItem_Dispatch_3B3C_L_800EBB44
    mr r4, r31
    bl ShellPile_Spawn
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b EggItem_Dispatch_3B3C_L_800EBB44
    mr r4, r31
    bl ShellPile_Spawn
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b EggItem_Dispatch_3B3C_L_800EBB44
    mr r4, r31
    bl EggItem_OnGroundDriftTick_3B3C
    b EggItem_Dispatch_3B3C_L_800EBB44
    mr r4, r31
    bl EggItem_OnGroundDriftTick_3B3C
    b EggItem_Dispatch_3B3C_L_800EBB44
    EggItem_Dispatch_3B3C_L_800EBB34:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b EggItem_Dispatch_3B3C_L_800EBBE8
    EggItem_Dispatch_3B3C_L_800EBB44:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r6, 0xac(r30)
    addi r3, r30, 0x14
    lwz r0, 0xb0(r30)
    addi r4, r1, 0x2c
    addi r5, r1, 0x20
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xb4(r30)
    stw r0, 0x28(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x34(r1)
    lfs f1, 0xc4(r30)
    bl SpriteSlot_SetTransform
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq EggItem_Dispatch_3B3C_L_800EBBAC
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    EggItem_Dispatch_3B3C_L_800EBBAC:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq EggItem_Dispatch_3B3C_L_800EBBC0
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    EggItem_Dispatch_3B3C_L_800EBBC0:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq EggItem_Dispatch_3B3C_L_800EBBD4
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    EggItem_Dispatch_3B3C_L_800EBBD4:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq EggItem_Dispatch_3B3C_L_800EBBE8
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    EggItem_Dispatch_3B3C_L_800EBBE8:
    lwz r0, 0x44(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}



