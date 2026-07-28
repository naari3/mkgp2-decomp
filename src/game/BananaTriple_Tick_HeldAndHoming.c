/* === extracted from auto_BananaTriple_Tick_He_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void DrawEffect_ItemHitBurst_Spawn();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHitRegistry_AddEntry();
extern void ItemHitRegistry_RemoveEntry();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemObject_GetGroundTypeAt();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceFallingDrop();
extern void Item_AdvanceProjectileSimple();
extern void Item_BendVelocityByGroundProbe();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern void Item_ProbeForwardGroundPitch();
extern void Item_ProbeLateralGroundPitch();
extern void Item_RenderCharacterScaledFromJoint12();
extern void Item_SpawnGroundExplosionAndFX();
extern void KartDriver_TransformWorldToLocalY0();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetScale();
extern void Vec3_Add_DestFirst();
extern void Vec3_ToPitch();
extern void Vec3_ToYaw();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D5D90;
extern unsigned int lbl_806D5D94;
extern unsigned int lbl_806D5D98;
extern unsigned int lbl_806D5DA0;
extern unsigned int lbl_806D5DA4;
extern unsigned int lbl_806D5DAC;
extern unsigned int lbl_806D5DB4;
extern unsigned int lbl_806D5DB8;
extern unsigned int lbl_806D5DBC;
extern unsigned int lbl_806D5DC0;
extern unsigned int lbl_806D5DC4;
extern unsigned int lbl_806D5DC8;
extern unsigned int lbl_806D5DCC;
extern unsigned int lbl_806D5DD0;
extern unsigned int lbl_806D5DD4;
extern unsigned int lbl_806D5DD8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8032EFF0[];
extern unsigned int lbl_804211B0[];

/* --- function index (1 fns, .text 0x800E8CAC..0x800E9934) ---
 * [  0] 0x800E8CAC size:0xC88   global BananaTriple_Tick_HeldAndHoming_32to36
 */

/* --- forward decls --- */
asm void BananaTriple_Tick_HeldAndHoming_32to36(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BananaTriple_Tick_HeldAndHoming_32to36[8] = {
    0x28, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BananaTriple_Tick_HeldAndHoming_32to36 = {
    (void *)&BananaTriple_Tick_HeldAndHoming_32to36, 0x00000C88, (void *)extab_BananaTriple_Tick_HeldAndHoming_32to36
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BananaTriple_Tick_HeldAndHoming_32to36(void) { /* 0x800E8CAC size:0xC88 */
    nofralloc
    stwu r1, -0x100(r1)
    mflr r0
    lis r6, lbl_8032EFF0@ha
    stw r0, 0x104(r1)
    stmw r27, 0xec(r1)
    mr r29, r3
    mr r30, r4
    addi r31, r6, lbl_8032EFF0@l
    lbz r5, 0xc9(r3)
    extsb r0, r5
    cmpwi r0, 0x1
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8DC4
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E8CEC
    cmpwi r0, 0x0
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E8CF8
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8CEC:
    cmpwi r0, 0x3
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F90
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8CF8:
    lwz r3, 0x8(r29)
    cmpwi r3, 0x35
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D18
    cmpwi r3, 0x36
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D18
    lwz r0, 0x10(r29)
    cmpwi r0, 0x0
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8DB4
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D18:
    cmpwi r3, 0x35
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D28
    cmpwi r3, 0x36
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D34
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D28:
    mr r3, r29
    bl Item_SpawnGroundExplosionAndFX
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D8C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D34:
    lwz r5, 0xa0(r29)
    addi r3, r29, 0xb8
    lwz r0, 0xa4(r29)
    addi r4, r1, 0xd0
    lfs f2, lbl_806D5DAC(r2)
    stw r5, 0xd0(r1)
    lfs f3, lbl_806D5D90(r2)
    stw r0, 0xd4(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0xd8(r1)
    lfs f1, 0xb0(r29)
    bl Item_BendVelocityByGroundProbe
    lwz r5, 0xa0(r29)
    addi r3, r29, 0xa0
    lwz r0, 0xa4(r29)
    addi r4, r1, 0xc4
    stw r5, 0xc4(r1)
    stw r0, 0xc8(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0xcc(r1)
    lwz r5, 0x98(r30)
    bl KartDriver_TransformWorldToLocalY0
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8D8C:
    lfs f1, lbl_806D5D94(r2)
    li r3, 0x0
    lfs f0, lbl_806D5DAC(r2)
    li r0, 0x2
    stfs f1, 0xc4(r29)
    stfs f0, 0x2c(r29)
    stb r3, 0x28(r29)
    stb r0, 0xc9(r29)
    stb r3, 0xca(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8DB4:
    addi r3, r5, 0x1
    li r0, 0x0
    stb r3, 0xc9(r29)
    stb r0, 0xca(r29)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8DC4:
    lbz r0, 0xca(r29)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8E50
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    cmpwi r0, 0x0
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E8DE4
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8DE4:
    li r0, 0x0
    stb r0, 0x0(r30)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x34
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8E18
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x5
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E8E34
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8E18:
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8E34:
    li r0, 0x1
    lfs f0, lbl_806D5D90(r2)
    stb r0, 0x28(r29)
    stfs f0, 0x2c(r29)
    lbz r3, 0xca(r29)
    addi r0, r3, 0x1
    stb r0, 0xca(r29)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8E50:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x34
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8EA8
    lwz r11, 0x408(r31)
    mr r3, r29
    lwz r10, 0x40c(r31)
    addi r4, r1, 0xb8
    lwz r9, 0x410(r31)
    addi r5, r1, 0xac
    lwz r8, 0x3fc(r31)
    li r6, 0x1
    lwz r7, 0x400(r31)
    lwz r0, 0x404(r31)
    stw r11, 0xac(r1)
    lfs f1, lbl_806D5DB8(r2)
    stw r10, 0xb0(r1)
    stw r9, 0xb4(r1)
    stw r8, 0xb8(r1)
    stw r7, 0xbc(r1)
    stw r0, 0xc0(r1)
    bl Item_RenderCharacterScaledFromJoint12
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E8EF0
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8EA8:
    lwz r11, 0x420(r31)
    mr r3, r29
    lwz r10, 0x424(r31)
    addi r4, r1, 0xa0
    lwz r9, 0x428(r31)
    addi r5, r1, 0x94
    lwz r8, 0x414(r31)
    li r6, 0x1
    lwz r7, 0x418(r31)
    lwz r0, 0x41c(r31)
    stw r11, 0x94(r1)
    lfs f1, lbl_806D5DBC(r2)
    stw r10, 0x98(r1)
    stw r9, 0x9c(r1)
    stw r8, 0xa0(r1)
    stw r7, 0xa4(r1)
    stw r0, 0xa8(r1)
    bl Item_RenderCharacterScaledFromJoint12
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8EF0:
    lwz r3, 0x98(r30)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F0C
    li r0, 0x0
    stb r0, 0x28(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F14
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F0C:
    li r0, 0x1
    stb r0, 0x28(r29)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F14:
    lbz r0, 0xa0(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F74
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    cmpwi r0, 0x1
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F34
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F34:
    li r5, 0x1
    li r0, 0x0
    stb r5, 0x28(r29)
    mr r3, r29
    lfs f1, lbl_806D5DAC(r2)
    li r4, 0x0
    stb r0, 0xa0(r30)
    lfs f2, lbl_806D5D90(r2)
    stb r5, 0x0(r30)
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r29)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r29)
    stb r0, 0xca(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F74:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r30)
    stb r3, 0x28(r29)
    stb r0, 0xc8(r29)
    stb r3, 0xc9(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8F90:
    lbz r0, 0xca(r29)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E914C
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E8FB4
    cmpwi r0, 0x0
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E8FC0
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E90F0
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8FB4:
    cmpwi r0, 0x4
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E918C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E8FC0:
    li r0, 0x1
    stb r0, 0x28(r29)
    bl ItemTracker_AcquireLock
    mr r3, r29
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r4, 0x1
    lis r3, lbl_804211B0@ha
    stb r4, 0x8d(r29)
    addi r0, r3, lbl_804211B0@l
    addi r3, r29, 0x14
    li r5, 0x10
    stb r4, 0x3c(r29)
    li r6, 0x0
    lbz r4, 0x3(r30)
    mulli r4, r4, 0xc0
    add r4, r0, r4
    bl SpriteSlot_SetJointVisibilityByName
    lbz r4, 0x3(r30)
    lis r3, lbl_804211B0@ha
    addi r0, r3, lbl_804211B0@l
    addi r3, r29, 0x14
    mulli r4, r4, 0xc0
    li r5, 0x10
    li r6, 0x1
    add r4, r0, r4
    addi r4, r4, 0x40
    bl SpriteSlot_SetJointVisibilityByName
    lwz r6, 0xa0(r29)
    addi r3, r1, 0x88
    lwz r0, 0xa4(r29)
    addi r4, r30, 0x18
    li r5, 0x0
    stw r6, 0x88(r1)
    stw r0, 0x8c(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x90(r1)
    bl ItemObject_GetGroundTypeAt
    lfs f1, 0xa4(r29)
    li r0, 0x0
    lfs f0, 0x18(r30)
    fsubs f0, f1, f0
    stfs f0, 0x18(r30)
    stw r0, 0xc(r30)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x35
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9084
    cmpwi r0, 0x36
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E90BC
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9084:
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x1
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    li r0, 0x12c
    li r3, 0x3c
    stw r0, 0x4(r30)
    li r0, 0x1
    stw r3, 0x8(r30)
    stb r0, 0xca(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E90BC:
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    li r3, 0x0
    li r0, 0x2
    stw r3, 0x4(r30)
    stw r3, 0x8(r30)
    stb r0, 0xca(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E90F0:
    addi r4, r29, 0xb0
    li r5, 0x0
    bl Item_HomingScanAndSteer
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9110
    lfs f2, lbl_806D5DAC(r2)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9114
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9110:
    lfs f2, lbl_806D5DA4(r2)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9114:
    cmpwi r0, 0x0
    mr r3, r29
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9128
    lfs f1, lbl_806D5DC0(r2)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E912C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9128:
    lfs f1, lbl_806D5DC4(r2)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E912C:
    bl Item_AccelClampVelocity
    lwz r0, 0x4(r30)
    cmplwi r0, 0x0
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    lbz r3, 0xca(r29)
    addi r0, r3, 0x1
    stb r0, 0xca(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E914C:
    lfs f1, 0xbc(r29)
    lfs f0, lbl_806D5DB4(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r29)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x32
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9178
    cmpwi r0, 0x33
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9178
    cmpwi r0, 0x34
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9178:
    mr r3, r29
    addi r4, r29, 0xb0
    li r5, 0x1
    bl Item_HomingScanAndSteer
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E918C:
    lfs f1, 0xbc(r29)
    lfs f0, lbl_806D5DB4(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r29)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E919C:
    lwz r0, 0x8(r30)
    cmplwi r0, 0x0
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E91D0
    lbz r0, 0x1d(r29)
    cmpwi r0, 0x4
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E91D0
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E91D0:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x34
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E91EC
    lfs f1, lbl_806D5D94(r2)
    mr r3, r29
    bl Item_DecayVelocityScalar
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E91F8
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E91EC:
    lfs f1, lbl_806D5D98(r2)
    mr r3, r29
    bl Item_DecayVelocityScalar
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E91F8:
    mr r3, r29
    bl ItemCollision_Check
    mr r31, r3
    cmpwi r31, 0x3
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9290
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E9220
    cmpwi r31, 0x1
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9230
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E9274
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9464
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9220:
    cmpwi r31, 0x5
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9458
    bge BananaTriple_Tick_HeldAndHoming_32to36_L_800E9464
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E93E4
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9230:
    lbz r0, 0xca(r29)
    lwz r3, 0x8(r29)
    extsb r0, r0
    subfic r0, r0, 0x3
    cntlzw r0, r0
    srwi r27, r0, 5
    bl ItemAlias_HitRemapLookup
    extsh r28, r3
    mr r3, r29
    bl ItemTracker_GetTargetKart
    neg r0, r27
    mr r4, r3
    or r0, r0, r27
    lwz r3, 0x98(r30)
    srwi r6, r0, 31
    mr r5, r28
    bl fn_801B1D5C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9274:
    cmpwi r31, 0x2
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9290
    mr r3, r29
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r30)
    bl fn_801B1660
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9290:
    cmpwi r31, 0x3
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E92AC
    mr r3, r29
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r30)
    bl fn_801B158C
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E92AC:
    mr r3, r29
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r30)
    bl fn_801B14B8
    lbz r0, 0xca(r29)
    cmpwi r0, 0x3
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E934C
    cmpwi r31, 0x3
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E934C
    li r0, 0x0
    mr r3, r29
    stw r0, 0x7c(r30)
    lwz r4, 0xb8(r29)
    lwz r0, 0xbc(r29)
    stw r4, 0x70(r1)
    stw r0, 0x74(r1)
    lwz r0, 0xc0(r29)
    stw r0, 0x78(r1)
    lwz r4, 0xa0(r29)
    lwz r0, 0xa4(r29)
    stw r4, 0x7c(r1)
    stw r0, 0x80(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x84(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r29, 0xb8
    addi r5, r1, 0x7c
    addi r6, r1, 0x70
    bl Item_ComputeYawRelativeApproach
    addi r3, r29, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r29)
    mr r3, r29
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0xc(r30)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9464
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E934C:
    mr r3, r29
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r30)
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r29)
    lbz r0, 0x1d(r29)
    cmpwi r0, 0x4
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9390
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9390:
    lbz r0, 0xca(r29)
    cmpwi r0, 0x1
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E93A8
    li r0, 0x1
    stb r0, 0x1(r30)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E93B0
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E93A8:
    li r0, 0x0
    stb r0, 0x1(r30)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E93B0:
    cmpwi r31, 0x1
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E93C4
    li r0, 0x1
    stb r0, 0x2(r30)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E93CC
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E93C4:
    li r0, 0x0
    stb r0, 0x2(r30)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E93CC:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc8(r29)
    stb r0, 0xc9(r29)
    stb r0, 0xcb(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E93E4:
    mr r3, r29
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r30)
    bl fn_801B14B8
    mr r3, r29
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r30)
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r29)
    lbz r0, 0x1d(r29)
    cmpwi r0, 0x4
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E943C
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E943C:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x3
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9458:
    mr r3, r29
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9464:
    lwz r0, 0xc(r30)
    cmplwi r0, 0x0
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E947C
    mr r3, r29
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E947C:
    lbz r0, 0x8d(r29)
    cmpwi r0, 0x2
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9538
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r29)
    lbz r0, 0x1d(r29)
    cmpwi r0, 0x4
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E94C0
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E94C0:
    lbz r0, 0x8e(r29)
    cmpwi r0, 0x1
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E951C
    addi r3, r29, 0xb8
    addi r5, r29, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D5DA4(r2)
    li r4, 0x2
    lfs f1, lbl_806D5DC8(r2)
    li r3, 0x0
    stfs f0, 0xbc(r29)
    li r0, 0x4
    lfs f0, 0xb8(r29)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r29)
    lfs f0, 0xc0(r29)
    fmuls f0, f0, f1
    stfs f0, 0xc0(r29)
    stb r4, 0xc8(r29)
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E951C:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x6
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9538:
    lbz r0, 0xca(r29)
    cmpwi r0, 0x3
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9610
    mr r3, r29
    addi r4, r1, 0xdc
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9610
    lwz r0, 0x8(r29)
    cmpwi r0, 0x34
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E95A0
    lwz r6, 0xdc(r1)
    mr r3, r29
    lwz r7, 0xe0(r1)
    addi r4, r1, 0x64
    lwz r0, 0xe4(r1)
    li r5, 0x0
    stw r6, 0x64(r1)
    li r6, 0x2
    lfs f1, lbl_806D5DC8(r2)
    stw r7, 0x68(r1)
    lfs f2, lbl_806D5D90(r2)
    stw r0, 0x6c(r1)
    bl Item_BounceOffWall
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E95D4
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E95A0:
    lwz r6, 0xdc(r1)
    mr r3, r29
    lwz r7, 0xe0(r1)
    addi r4, r1, 0x58
    lwz r0, 0xe4(r1)
    li r5, 0x0
    stw r6, 0x58(r1)
    li r6, 0x3
    lfs f1, lbl_806D5DC8(r2)
    stw r7, 0x5c(r1)
    lfs f2, lbl_806D5D90(r2)
    stw r0, 0x60(r1)
    bl Item_BounceOffWall
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E95D4:
    lbz r0, 0x1d(r29)
    cmpwi r0, 0x4
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E95FC
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E95FC:
    lbz r0, 0xca(r29)
    cmpwi r0, 0x1
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9610
    li r0, 0x0
    stw r0, 0x4(r30)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9610:
    lbz r3, 0xca(r29)
    extsb. r0, r3
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9628
    extsb r0, r3
    cmpwi r0, 0x1
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9680
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9628:
    lfs f1, lbl_806D5DCC(r2)
    mr r3, r29
    addi r4, r30, 0x18
    fmr f2, f1
    bl Item_AdvanceProjectileSimple
    lwz r0, 0x8(r29)
    mr r31, r3
    cmpwi r0, 0x35
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9654
    cmpwi r0, 0x36
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9670
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9654:
    addi r3, r29, 0xb8
    bl Vec3_ToPitch
    lfs f0, lbl_806D5DD0(r2)
    fadds f1, f0, f1
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9850
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9670:
    addi r3, r29, 0xb8
    bl Vec3_ToPitch
    stfs f1, 0xac(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9850
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9680:
    lwz r0, 0x8(r29)
    cmpwi r0, 0x34
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E96A4
    lfs f1, lbl_806D5DD4(r2)
    mr r3, r29
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E96B8
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E96A4:
    lfs f1, lbl_806D5DD4(r2)
    mr r3, r29
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E96B8:
    lwz r0, 0xc(r1)
    mr r31, r3
    cmpwi r0, 0x0
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E97B8
    lbz r0, 0xca(r29)
    cmpwi r0, 0x2
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E977C
    lwz r0, 0x8(r29)
    cmpwi r0, 0x34
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9724
    lwz r6, 0xb8(r29)
    addi r3, r1, 0x4c
    lwz r0, 0xbc(r29)
    addi r4, r1, 0x40
    li r5, 0x2
    stw r6, 0x40(r1)
    stw r0, 0x44(r1)
    lwz r0, 0xc0(r29)
    stw r0, 0x48(r1)
    lwz r6, 0xa0(r29)
    lwz r0, 0xa4(r29)
    stw r6, 0x4c(r1)
    stw r0, 0x50(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x54(r1)
    bl DrawEffect_ItemHitBurst_Spawn
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9764
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9724:
    lwz r6, 0xb8(r29)
    addi r3, r1, 0x34
    lwz r0, 0xbc(r29)
    addi r4, r1, 0x28
    li r5, 0x3
    stw r6, 0x28(r1)
    stw r0, 0x2c(r1)
    lwz r0, 0xc0(r29)
    stw r0, 0x30(r1)
    lwz r6, 0xa0(r29)
    lwz r0, 0xa4(r29)
    stw r6, 0x34(r1)
    stw r0, 0x38(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x3c(r1)
    bl DrawEffect_ItemHitBurst_Spawn
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9764:
    li r3, 0x384
    li r0, 0x3
    stw r3, 0x4(r30)
    mr r3, r29
    stb r0, 0xca(r29)
    bl ItemHitRegistry_AddEntry
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E977C:
    lbz r0, 0x1d(r29)
    cmpwi r0, 0x4
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E97A4
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E97A4:
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E97B8:
    lwz r4, 0xa0(r29)
    addi r3, r1, 0x1c
    lwz r0, 0xa4(r29)
    lfs f0, 0x8(r1)
    stw r4, 0x1c(r1)
    lfs f2, lbl_806D5DD8(r2)
    stw r0, 0x20(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x24(r1)
    lfs f3, 0xa4(r29)
    lfs f1, 0xb0(r29)
    fsubs f3, f3, f0
    bl Item_ProbeForwardGroundPitch
    fmr f0, f1
    lfs f1, 0xac(r29)
    lfs f3, lbl_806D5DA0(r2)
    fmr f2, f0
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r29)
    addi r3, r1, 0x10
    lfs f2, lbl_806D5DD8(r2)
    lwz r4, 0xa0(r29)
    lwz r0, 0xa4(r29)
    lfs f0, 0x8(r1)
    stw r4, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x18(r1)
    lfs f3, 0xa4(r29)
    lfs f1, 0xb0(r29)
    fsubs f3, f3, f0
    bl Item_ProbeLateralGroundPitch
    fmr f0, f1
    lfs f1, 0xb4(r29)
    lfs f3, lbl_806D5DA0(r2)
    fmr f2, f0
    bl AngleStepTowards_Shortest
    stfs f1, 0xb4(r29)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9850:
    cmpwi r31, 0x0
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E98AC
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r29)
    lbz r0, 0x1d(r29)
    cmpwi r0, 0x4
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9890
    lfs f1, lbl_806D5D90(r2)
    addi r3, r29, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9890:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x9
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E98AC:
    lbz r0, 0xca(r29)
    cmpwi r0, 0x3
    bne BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    lwz r4, 0x4(r30)
    mr r3, r29
    li r5, 0x0
    bl ItemHitRegistry_RemoveEntry
    clrlwi. r0, r3, 24
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r29)
    lwz r3, 0x4c(r30)
    cmplwi r3, 0x0
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E98F4
    li r0, 0x1
    stb r0, 0xc9(r3)
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E98F4:
    li r0, 0x0
    stw r0, 0x4c(r30)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x35
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9918
    cmpwi r0, 0x36
    beq BananaTriple_Tick_HeldAndHoming_32to36_L_800E9918
    mr r3, r29
    bl ItemObject_DecrementCategoryBudget
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9918:
    mr r3, r29
    bl SpriteSlot_Container_Free
    BananaTriple_Tick_HeldAndHoming_32to36_L_800E9920:
    lmw r27, 0xec(r1)
    lwz r0, 0x104(r1)
    mtlr r0
    addi r1, r1, 0x100
    blr
}

