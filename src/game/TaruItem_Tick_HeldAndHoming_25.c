/* === extracted from auto_TaruItem_Tick_HeldAn_text === */
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
extern void Item_RenderCharacterScaledFromJoint12();
extern void KartDriver_GetJointByIdx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_CountActiveSEInstances();
extern void SoundMgr_PlaySE_Positional();
extern void SoundMgr_PlaySE_WithChannel();
extern void SoundMgr_StopSE_OrSpecial();
extern void Vec2_RotateY();
extern void Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D5DE0;
extern unsigned int lbl_806D5DE8;
extern unsigned int lbl_806D5DEC;
extern unsigned int lbl_806D5DF4;
extern unsigned int lbl_806D5DF8;
extern unsigned int lbl_806D5DFC;
extern unsigned int lbl_806D5E00;
extern unsigned int lbl_806D5E04;
extern unsigned int lbl_806D5E08;
extern unsigned int lbl_806D5E0C;
extern unsigned int lbl_806D5E10;
extern unsigned int lbl_806D5E14;
extern unsigned int lbl_806D5E18;
extern unsigned int lbl_806D5E1C;
extern unsigned int lbl_806D5E20;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8032F440[];
extern unsigned int lbl_8032F44C[];

/* --- function index (1 fns, .text 0x800EA0E8..0x800EA958) ---
 * [  0] 0x800EA0E8 size:0x870   global TaruItem_Tick_HeldAndHoming_25
 */

/* --- forward decls --- */
asm void TaruItem_Tick_HeldAndHoming_25(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TaruItem_Tick_HeldAndHoming_25[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TaruItem_Tick_HeldAndHoming_25 = {
    (void *)&TaruItem_Tick_HeldAndHoming_25, 0x00000870, (void *)extab_TaruItem_Tick_HeldAndHoming_25
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TaruItem_Tick_HeldAndHoming_25(void) { /* 0x800EA0E8 size:0x870 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stw r31, 0xac(r1)
    mr r31, r4
    stw r30, 0xa8(r1)
    mr r30, r3
    stw r29, 0xa4(r1)
    stw r28, 0xa0(r1)
    lbz r4, 0xc9(r3)
    extsb r0, r4
    cmpwi r0, 0x1
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA148
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA12C
    cmpwi r0, 0x0
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA138
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA12C:
    cmpwi r0, 0x3
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA938
    b TaruItem_Tick_HeldAndHoming_25_L_800EA29C
    TaruItem_Tick_HeldAndHoming_25_L_800EA138:
    addi r3, r4, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    TaruItem_Tick_HeldAndHoming_25_L_800EA148:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA18C
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA938
    cmpwi r0, 0x0
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA168
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA168:
    li r3, 0x0
    li r0, 0x1
    stb r3, 0x0(r31)
    lfs f0, lbl_806D5DE0(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    TaruItem_Tick_HeldAndHoming_25_L_800EA18C:
    lis r4, lbl_8032F44C@ha
    lwzu r12, lbl_8032F44C@l(r4)
    lis r3, lbl_8032F440@ha
    lfs f1, lbl_806D5E18(r2)
    addi r9, r3, lbl_8032F440@l
    lwz r11, 0x4(r4)
    lwz r10, 0x8(r4)
    mr r3, r30
    lwz r8, 0x0(r9)
    addi r4, r1, 0x7c
    lwz r7, 0x4(r9)
    addi r5, r1, 0x70
    lwz r0, 0x8(r9)
    li r6, 0x1
    stw r12, 0x70(r1)
    stw r11, 0x74(r1)
    stw r10, 0x78(r1)
    stw r8, 0x7c(r1)
    stw r7, 0x80(r1)
    stw r0, 0x84(r1)
    bl Item_RenderCharacterScaledFromJoint12
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA1FC
    li r0, 0x0
    stb r0, 0x28(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA204
    TaruItem_Tick_HeldAndHoming_25_L_800EA1FC:
    li r0, 0x1
    stb r0, 0x28(r30)
    TaruItem_Tick_HeldAndHoming_25_L_800EA204:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA264
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA280
    cmpwi r0, 0x1
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA224
    b TaruItem_Tick_HeldAndHoming_25_L_800EA280
    TaruItem_Tick_HeldAndHoming_25_L_800EA224:
    li r5, 0x1
    li r0, 0x0
    stb r5, 0x28(r30)
    mr r3, r30
    lfs f1, lbl_806D5DE8(r2)
    addi r4, r31, 0x34
    stb r0, 0xa0(r31)
    lfs f2, lbl_806D5E1C(r2)
    stb r5, 0x0(r31)
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA264:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA280:
    lwz r3, 0x98(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA29C:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA30C
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA30C
    cmpwi r0, 0x0
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA2BC
    b TaruItem_Tick_HeldAndHoming_25_L_800EA30C
    TaruItem_Tick_HeldAndHoming_25_L_800EA2BC:
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
    stb r4, 0x1(r31)
    stb r3, 0x2(r31)
    stw r0, 0x30(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    TaruItem_Tick_HeldAndHoming_25_L_800EA30C:
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5DF4(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA330
    lfs f2, lbl_806D5DF8(r2)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA334
    TaruItem_Tick_HeldAndHoming_25_L_800EA330:
    lfs f2, lbl_806D5DFC(r2)
    TaruItem_Tick_HeldAndHoming_25_L_800EA334:
    cmpwi r0, 0x0
    mr r3, r30
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA348
    lfs f1, lbl_806D5E00(r2)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA34C
    TaruItem_Tick_HeldAndHoming_25_L_800EA348:
    lfs f1, lbl_806D5E04(r2)
    TaruItem_Tick_HeldAndHoming_25_L_800EA34C:
    bl Item_AccelClampVelocity
    addi r3, r30, 0xa0
    bl fn_801B129C
    lfs f1, lbl_806D5DEC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    fmr f2, f1
    lfs f1, 0xb0(r30)
    lfs f3, lbl_806D5E08(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xb0(r30)
    mr r3, r30
    lfs f1, lbl_806D5DE8(r2)
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA47C
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA3BC
    cmpwi r28, 0x1
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA3CC
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA3F4
    b TaruItem_Tick_HeldAndHoming_25_L_800EA574
    TaruItem_Tick_HeldAndHoming_25_L_800EA3BC:
    cmpwi r28, 0x5
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA568
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA574
    b TaruItem_Tick_HeldAndHoming_25_L_800EA500
    TaruItem_Tick_HeldAndHoming_25_L_800EA3CC:
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
    TaruItem_Tick_HeldAndHoming_25_L_800EA3F4:
    cmpwi r28, 0x2
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA410
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    TaruItem_Tick_HeldAndHoming_25_L_800EA410:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA448
    li r3, 0xbd
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA448:
    cmpwi r28, 0x1
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA45C
    li r0, 0x1
    stb r0, 0x1(r31)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA464
    TaruItem_Tick_HeldAndHoming_25_L_800EA45C:
    li r0, 0x0
    stb r0, 0x1(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA464:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc8(r30)
    stb r0, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA47C:
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
    b TaruItem_Tick_HeldAndHoming_25_L_800EA574
    TaruItem_Tick_HeldAndHoming_25_L_800EA500:
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
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA54C
    li r3, 0xbd
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA54C:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x3
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA568:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    TaruItem_Tick_HeldAndHoming_25_L_800EA574:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA58C
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    TaruItem_Tick_HeldAndHoming_25_L_800EA58C:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA5F4
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D5DE0(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA5D8
    li r3, 0xbd
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA5D8:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x4
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA5F4:
    mr r3, r30
    addi r4, r1, 0x88
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA6C0
    lbz r3, 0x2(r31)
    cmplwi r3, 0x0
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA620
    subi r0, r3, 0x1
    stb r0, 0x2(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA620:
    lbz r0, 0x2(r31)
    cmplwi r0, 0x0
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA664
    lwz r6, 0x88(r1)
    mr r3, r30
    lwz r7, 0x8c(r1)
    addi r4, r1, 0x4c
    lwz r0, 0x90(r1)
    li r5, 0x0
    stw r6, 0x4c(r1)
    li r6, 0x3
    lfs f1, lbl_806D5E0C(r2)
    stw r7, 0x50(r1)
    lfs f2, lbl_806D5DE0(r2)
    stw r0, 0x54(r1)
    bl Item_BounceOffWall
    b TaruItem_Tick_HeldAndHoming_25_L_800EA6C0
    TaruItem_Tick_HeldAndHoming_25_L_800EA664:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D5DE0(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA6A4
    li r3, 0xbd
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA6A4:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x7
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA6C0:
    lfs f1, lbl_806D5E10(r2)
    mr r3, r30
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA8A0
    lwz r0, 0xc(r1)
    cmpwi r0, 0x0
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA880
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA73C
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
    TaruItem_Tick_HeldAndHoming_25_L_800EA73C:
    lbz r0, 0x1(r31)
    cmplwi r0, 0x0
    beq TaruItem_Tick_HeldAndHoming_25_L_800EA75C
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5DF4(r2)
    fmuls f0, f1, f0
    stfs f0, 0xbc(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA76C
    TaruItem_Tick_HeldAndHoming_25_L_800EA75C:
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5E20(r2)
    fmuls f0, f1, f0
    stfs f0, 0xbc(r30)
    TaruItem_Tick_HeldAndHoming_25_L_800EA76C:
    li r0, 0x1
    lfs f2, lbl_806D5DE8(r2)
    stb r0, 0x1(r31)
    addi r3, r1, 0x28
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
    stfs f1, 0xb4(r30)
    lfs f1, 0xb4(r30)
    bl FAbs_FloatAsDouble
    lfs f2, lbl_806D5DEC(r2)
    fcmpo cr0, f2, f1
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA80C
    lfs f0, lbl_806D5DE0(r2)
    lfs f1, 0xb4(r30)
    fcmpo cr0, f0, f1
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA7F0
    fsubs f0, f1, f2
    addi r3, r30, 0xb8
    lfs f1, lbl_806D5E14(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    b TaruItem_Tick_HeldAndHoming_25_L_800EA80C
    TaruItem_Tick_HeldAndHoming_25_L_800EA7F0:
    fadds f0, f2, f1
    addi r3, r30, 0xb8
    lfs f1, lbl_806D5E14(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    TaruItem_Tick_HeldAndHoming_25_L_800EA80C:
    lwz r5, 0x30(r31)
    cmpwi r5, 0x0
    bge TaruItem_Tick_HeldAndHoming_25_L_800EA858
    li r3, 0xbd
    bl SoundMgr_CountActiveSEInstances
    stw r3, 0x30(r31)
    lwz r5, 0x30(r31)
    cmpwi r5, 0x0
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA8E8
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x1c
    lwz r0, 0xa4(r30)
    li r3, 0xbd
    stw r6, 0x1c(r1)
    stw r0, 0x20(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x24(r1)
    bl SoundMgr_PlaySE_Positional
    b TaruItem_Tick_HeldAndHoming_25_L_800EA8E8
    TaruItem_Tick_HeldAndHoming_25_L_800EA858:
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x10
    lwz r0, 0xa4(r30)
    li r3, 0xbd
    stw r6, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x18(r1)
    bl SoundMgr_PlaySE_WithChannel
    b TaruItem_Tick_HeldAndHoming_25_L_800EA8E8
    TaruItem_Tick_HeldAndHoming_25_L_800EA880:
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA8E8
    li r3, 0xbd
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA8E8
    TaruItem_Tick_HeldAndHoming_25_L_800EA8A0:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA8CC
    li r3, 0xbd
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA8CC:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x9
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TaruItem_Tick_HeldAndHoming_25_L_800EA938
    TaruItem_Tick_HeldAndHoming_25_L_800EA8E8:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TaruItem_Tick_HeldAndHoming_25_L_800EA938
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r4, 0x30(r31)
    cmpwi r4, 0x0
    blt TaruItem_Tick_HeldAndHoming_25_L_800EA920
    li r3, 0xbd
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r31)
    TaruItem_Tick_HeldAndHoming_25_L_800EA920:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x5
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    TaruItem_Tick_HeldAndHoming_25_L_800EA938:
    lwz r0, 0xb4(r1)
    lwz r31, 0xac(r1)
    lwz r30, 0xa8(r1)
    lwz r29, 0xa4(r1)
    lwz r28, 0xa0(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

