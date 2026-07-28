/* === extracted from auto_TornadoItem_TickActi_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void DrawEffect_ItemHitBurst_Spawn();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHit_Dispatch();
extern void ItemObject_RaycastWallStub();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceFallingDrop();
extern void Item_BendVelocityByGroundProbe();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern void KartDriver_GetJointByIdx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_SetScale();
extern void Vec2_RotateY();
extern void Vec3_Add_DestFirst();
extern void Vec3_HorizontalYawTo();
extern void Vec3_Lerp();
extern void Vec3_Magnitude_Wrapper();
extern void Vec3_ToPitch();
extern void Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D61F0;
extern unsigned int lbl_806D61F4;
extern unsigned int lbl_806D61FC;
extern unsigned int lbl_806D6204;
extern unsigned int lbl_806D6208;
extern unsigned int lbl_806D620C;
extern unsigned int lbl_806D6210;
extern unsigned int lbl_806D6214;
extern unsigned int lbl_806D6218;
extern unsigned int lbl_806D621C;
extern unsigned int lbl_806D6220;
extern unsigned int lbl_806D6224;
extern unsigned int lbl_806D6228;
extern unsigned int lbl_806D622C;
extern unsigned int lbl_806D6230;
extern unsigned int lbl_806D6234;
extern unsigned int lbl_806D6238;
extern unsigned int lbl_806D623C;
extern unsigned int lbl_806D6240;
extern unsigned int lbl_806D6244;
extern unsigned int lbl_806D6248;
extern unsigned int lbl_806D624C;
extern unsigned int lbl_806D6250;
extern unsigned int lbl_806D6254;
extern unsigned int lbl_806D6258;

/* --- function index (1 fns, .text 0x800F7AFC..0x800F869C) ---
 * [  0] 0x800F7AFC size:0xBA0   global TornadoItem_TickActive
 */

/* --- forward decls --- */
asm void TornadoItem_TickActive(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoItem_TickActive[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoItem_TickActive = {
    (void *)&TornadoItem_TickActive, 0x00000BA0, (void *)extab_TornadoItem_TickActive
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoItem_TickActive(void) { /* 0x800F7AFC size:0xBA0 */
    nofralloc
    stwu r1, -0x180(r1)
    mflr r0
    stw r0, 0x184(r1)
    stfd f31, 0x170(r1)
    psq_st f31, 0x178(r1), 0, 0
    stw r31, 0x16c(r1)
    stw r30, 0x168(r1)
    stw r29, 0x164(r1)
    stw r28, 0x160(r1)
    mr r30, r3
    mr r31, r4
    lbz r4, 0xc9(r3)
    extsb r0, r4
    cmpwi r0, 0x1
    beq TornadoItem_TickActive_L_800F7B64
    bge TornadoItem_TickActive_L_800F7B48
    cmpwi r0, 0x0
    bge TornadoItem_TickActive_L_800F7B54
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F7B48:
    cmpwi r0, 0x3
    bge TornadoItem_TickActive_L_800F8674
    b TornadoItem_TickActive_L_800F7CA4
    TornadoItem_TickActive_L_800F7B54:
    addi r3, r4, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    TornadoItem_TickActive_L_800F7B64:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TornadoItem_TickActive_L_800F7BC8
    bge TornadoItem_TickActive_L_800F8674
    cmpwi r0, 0x0
    bge TornadoItem_TickActive_L_800F7B84
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F7B84:
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D61F0(r2)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6208(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    li r0, 0x1
    lfs f0, lbl_806D61F0(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    TornadoItem_TickActive_L_800F7BC8:
    lfs f1, lbl_806D620C(r2)
    mr r3, r30
    lfs f2, lbl_806D6210(r2)
    li r4, 0x1
    lfs f3, lbl_806D6214(r2)
    bl GabyouItem_BuildLocalTransformFromHandJoint
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq TornadoItem_TickActive_L_800F7BFC
    li r0, 0x0
    stb r0, 0x28(r30)
    b TornadoItem_TickActive_L_800F7C04
    TornadoItem_TickActive_L_800F7BFC:
    li r0, 0x1
    stb r0, 0x28(r30)
    TornadoItem_TickActive_L_800F7C04:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq TornadoItem_TickActive_L_800F7C6C
    bge TornadoItem_TickActive_L_800F7C88
    cmpwi r0, 0x1
    bge TornadoItem_TickActive_L_800F7C24
    b TornadoItem_TickActive_L_800F7C88
    TornadoItem_TickActive_L_800F7C24:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0xa0(r31)
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D6218(r2)
    mr r3, r30
    lfs f2, lbl_806D61F0(r2)
    addi r4, r31, 0x34
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F7C6C:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F7C88:
    lwz r3, 0x98(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F7CA4:
    lbz r4, 0xca(r30)
    extsb r0, r4
    cmpwi r0, 0x2
    beq TornadoItem_TickActive_L_800F7D64
    bge TornadoItem_TickActive_L_800F7D78
    cmpwi r0, 0x0
    beq TornadoItem_TickActive_L_800F7CCC
    bge TornadoItem_TickActive_L_800F7D40
    b TornadoItem_TickActive_L_800F7D78
    b TornadoItem_TickActive_L_800F7D78
    TornadoItem_TickActive_L_800F7CCC:
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    lfs f1, lbl_806D61F0(r2)
    stb r0, 0x8d(r30)
    addi r3, r30, 0x14
    li r4, 0x1
    stb r0, 0x3c(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D621C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    li r0, 0x258
    li r4, 0x1e
    stw r0, 0x4(r31)
    li r0, 0x0
    addi r3, r30, 0xb8
    stw r4, 0x8(r31)
    stw r0, 0xc(r31)
    stw r0, 0x10(r31)
    bl Vec3_ToYaw
    stfs f1, 0x14(r31)
    lfs f0, lbl_806D61F0(r2)
    stfs f0, 0x18(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    TornadoItem_TickActive_L_800F7D40:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TornadoItem_TickActive_L_800F7D78
    li r0, 0xb4
    stw r0, 0x4(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b TornadoItem_TickActive_L_800F7D78
    TornadoItem_TickActive_L_800F7D64:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TornadoItem_TickActive_L_800F7D78
    addi r0, r4, 0x1
    stb r0, 0xca(r30)
    TornadoItem_TickActive_L_800F7D78:
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D61FC(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne TornadoItem_TickActive_L_800F7D9C
    lfs f2, lbl_806D6208(r2)
    b TornadoItem_TickActive_L_800F7DA0
    TornadoItem_TickActive_L_800F7D9C:
    lfs f2, lbl_806D6220(r2)
    TornadoItem_TickActive_L_800F7DA0:
    cmpwi r0, 0x0
    mr r3, r30
    bne TornadoItem_TickActive_L_800F7DB4
    lfs f1, lbl_806D6224(r2)
    b TornadoItem_TickActive_L_800F7DB8
    TornadoItem_TickActive_L_800F7DB4:
    lfs f1, lbl_806D6228(r2)
    TornadoItem_TickActive_L_800F7DB8:
    bl Item_AccelClampVelocity
    addi r3, r30, 0xa0
    bl fn_801B129C
    lfs f1, 0xb0(r30)
    lfs f2, 0x14(r31)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xb0(r30)
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    mr r3, r30
    lfs f1, lbl_806D6204(r2)
    bl Item_DecayVelocityScalar
    lbz r0, 0x1d(r30)
    cmpwi r0, 0x1
    bne TornadoItem_TickActive_L_800F7E34
    lbz r0, 0x1e(r30)
    cmpwi r0, 0x1
    bne TornadoItem_TickActive_L_800F7E34
    lfs f1, lbl_806D61F0(r2)
    addi r3, r30, 0x14
    li r4, 0x2
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6208(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    TornadoItem_TickActive_L_800F7E34:
    lwz r0, 0x10(r31)
    cmplwi r0, 0x0
    bne TornadoItem_TickActive_L_800F7E70
    lwz r6, 0xa0(r30)
    addi r4, r1, 0xe4
    lwz r0, 0xa4(r30)
    li r3, 0xac
    li r5, 0x0
    stw r6, 0xe4(r1)
    stw r0, 0xe8(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0xec(r1)
    bl SoundMgr_PlaySE_Positional
    li r0, 0x1e
    stw r0, 0x10(r31)
    TornadoItem_TickActive_L_800F7E70:
    lwz r0, 0x7c(r31)
    cmplwi r0, 0x0
    beq TornadoItem_TickActive_L_800F7E98
    mr r3, r30
    addi r4, r30, 0xb0
    li r5, 0x0
    bl Item_HomingScanAndSteer
    lfs f0, 0xb0(r30)
    stfs f0, 0x14(r31)
    b TornadoItem_TickActive_L_800F81A8
    TornadoItem_TickActive_L_800F7E98:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x1
    bne TornadoItem_TickActive_L_800F81A8
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne TornadoItem_TickActive_L_800F81A0
    li r29, 0x0
    addi r28, r1, 0x144
    TornadoItem_TickActive_L_800F7EB8:
    cmpwi r29, 0x0
    beq TornadoItem_TickActive_L_800F7ED8
    lfs f1, lbl_806D622C(r2)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    fmr f31, f1
    b TornadoItem_TickActive_L_800F7EEC
    TornadoItem_TickActive_L_800F7ED8:
    lfs f1, lbl_806D6230(r2)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    fmr f31, f1
    TornadoItem_TickActive_L_800F7EEC:
    lfs f1, lbl_806D61F0(r2)
    mr r3, r28
    lfs f3, lbl_806D6234(r2)
    fmr f2, f1
    bl GetSpawnPosition
    fmr f1, f31
    mr r3, r28
    mr r4, r28
    bl Vec2_RotateY
    mr r3, r28
    mr r4, r28
    addi r5, r30, 0xa0
    bl Vec3_Add_DestFirst
    lwz r6, 0x0(r28)
    addi r3, r1, 0xd8
    lwz r7, 0x4(r28)
    addi r4, r1, 0xcc
    lwz r0, 0x8(r28)
    addi r5, r1, 0x138
    stw r6, 0xcc(r1)
    addi r6, r1, 0x12c
    stw r7, 0xd0(r1)
    stw r0, 0xd4(r1)
    lwz r7, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r7, 0xd8(r1)
    stw r0, 0xdc(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0xe0(r1)
    bl ItemObject_RaycastWallStub
    clrlwi. r0, r3, 24
    beq TornadoItem_TickActive_L_800F7F7C
    lfs f1, 0x138(r1)
    lfs f0, 0x140(r1)
    stfs f1, 0x0(r28)
    stfs f0, 0x8(r28)
    TornadoItem_TickActive_L_800F7F7C:
    addi r29, r29, 0x1
    addi r28, r28, 0xc
    cmpwi r29, 0x2
    blt TornadoItem_TickActive_L_800F7EB8
    lwz r10, 0x150(r1)
    addi r3, r1, 0x120
    lwz r9, 0x154(r1)
    addi r4, r1, 0xc0
    lwz r8, 0x158(r1)
    addi r5, r1, 0xb4
    lwz r7, 0x144(r1)
    lwz r6, 0x148(r1)
    lwz r0, 0x14c(r1)
    stw r10, 0xb4(r1)
    lfs f1, lbl_806D621C(r2)
    stw r9, 0xb8(r1)
    stw r8, 0xbc(r1)
    stw r7, 0xc0(r1)
    stw r6, 0xc4(r1)
    stw r0, 0xc8(r1)
    bl Vec3_Lerp
    addi r3, r30, 0xa0
    addi r4, r1, 0x120
    bl Vec3_HorizontalYawTo
    stfs f1, 0x14(r31)
    addi r3, r1, 0x114
    lfs f1, lbl_806D61F0(r2)
    lfs f3, lbl_806D6234(r2)
    fmr f2, f1
    bl GetSpawnPosition
    addi r3, r1, 0x114
    lfs f1, 0x14(r31)
    mr r4, r3
    bl Vec2_RotateY
    addi r3, r1, 0x114
    addi r5, r30, 0xa0
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r4, 0x114(r1)
    addi r5, r1, 0x108
    lwz r7, 0x118(r1)
    mr r6, r5
    lwz r0, 0x11c(r1)
    addi r3, r1, 0xa8
    stw r4, 0x9c(r1)
    addi r4, r1, 0x9c
    stw r7, 0xa0(r1)
    stw r0, 0xa4(r1)
    lwz r7, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r7, 0xa8(r1)
    stw r0, 0xac(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0xb0(r1)
    bl ItemObject_RaycastWallStub
    clrlwi. r0, r3, 24
    beq TornadoItem_TickActive_L_800F8150
    li r28, 0x0
    TornadoItem_TickActive_L_800F8064:
    cmpwi r28, 0x0
    beq TornadoItem_TickActive_L_800F8084
    lfs f1, lbl_806D6238(r2)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    fmr f31, f1
    b TornadoItem_TickActive_L_800F8098
    TornadoItem_TickActive_L_800F8084:
    lfs f1, lbl_806D623C(r2)
    lfs f0, 0x14(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    fmr f31, f1
    TornadoItem_TickActive_L_800F8098:
    lfs f1, lbl_806D61F0(r2)
    addi r3, r1, 0xfc
    lfs f3, lbl_806D6234(r2)
    fmr f2, f1
    bl GetSpawnPosition
    fmr f1, f31
    addi r3, r1, 0xfc
    mr r4, r3
    bl Vec2_RotateY
    addi r3, r1, 0xfc
    addi r5, r30, 0xa0
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r4, 0xfc(r1)
    addi r5, r1, 0x108
    lwz r7, 0x100(r1)
    mr r6, r5
    lwz r0, 0x104(r1)
    addi r3, r1, 0x90
    stw r4, 0x84(r1)
    addi r4, r1, 0x84
    stw r7, 0x88(r1)
    stw r0, 0x8c(r1)
    lwz r7, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r7, 0x90(r1)
    stw r0, 0x94(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x98(r1)
    bl ItemObject_RaycastWallStub
    clrlwi. r0, r3, 24
    beq TornadoItem_TickActive_L_800F8144
    cmpwi r28, 0x0
    bne TornadoItem_TickActive_L_800F8134
    addi r3, r30, 0xb8
    lfs f1, lbl_806D6240(r2)
    mr r4, r3
    bl Vec2_RotateY
    b TornadoItem_TickActive_L_800F8144
    TornadoItem_TickActive_L_800F8134:
    addi r3, r30, 0xb8
    lfs f1, lbl_806D6244(r2)
    mr r4, r3
    bl Vec2_RotateY
    TornadoItem_TickActive_L_800F8144:
    addi r28, r28, 0x1
    cmpwi r28, 0x2
    blt TornadoItem_TickActive_L_800F8064
    TornadoItem_TickActive_L_800F8150:
    lfs f2, 0x18(r31)
    lfs f0, lbl_806D6248(r2)
    lfs f1, lbl_806D6208(r2)
    fadds f0, f2, f0
    stfs f0, 0x18(r31)
    lfs f0, 0x18(r31)
    fcmpo cr0, f1, f0
    bge TornadoItem_TickActive_L_800F8174
    stfs f1, 0x18(r31)
    TornadoItem_TickActive_L_800F8174:
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    lfs f0, 0x14(r31)
    fsubs f1, f0, f1
    bl BuildOrientationFromYaw
    lfs f0, 0x18(r31)
    addi r3, r30, 0xb8
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateY
    b TornadoItem_TickActive_L_800F81A8
    TornadoItem_TickActive_L_800F81A0:
    lfs f0, lbl_806D61F0(r2)
    stfs f0, 0x18(r31)
    TornadoItem_TickActive_L_800F81A8:
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq TornadoItem_TickActive_L_800F8274
    bge TornadoItem_TickActive_L_800F81D0
    cmpwi r28, 0x1
    beq TornadoItem_TickActive_L_800F81E0
    bge TornadoItem_TickActive_L_800F8208
    b TornadoItem_TickActive_L_800F8364
    TornadoItem_TickActive_L_800F81D0:
    cmpwi r28, 0x5
    beq TornadoItem_TickActive_L_800F8358
    bge TornadoItem_TickActive_L_800F8364
    b TornadoItem_TickActive_L_800F8310
    TornadoItem_TickActive_L_800F81E0:
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
    TornadoItem_TickActive_L_800F8208:
    cmpwi r28, 0x2
    bne TornadoItem_TickActive_L_800F8224
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    TornadoItem_TickActive_L_800F8224:
    cmpwi r28, 0x1
    bne TornadoItem_TickActive_L_800F8240
    mr r3, r30
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    TornadoItem_TickActive_L_800F8240:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    mr r3, r30
    bl ItemTracker_GetTargetKart
    lwz r0, 0x7c(r31)
    cmplw r0, r3
    bne TornadoItem_TickActive_L_800F8364
    li r3, 0x0
    li r0, 0x1e
    stw r3, 0x7c(r31)
    stw r0, 0x8(r31)
    b TornadoItem_TickActive_L_800F8364
    TornadoItem_TickActive_L_800F8274:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    li r0, 0x0
    mr r3, r30
    stw r0, 0x7c(r31)
    lwz r4, 0xb8(r30)
    lwz r0, 0xbc(r30)
    stw r4, 0x6c(r1)
    stw r0, 0x70(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x74(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x78(r1)
    stw r0, 0x7c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x80(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0x78
    addi r6, r1, 0x6c
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    li r0, 0x1e
    mr r3, r30
    li r4, 0x0
    lfs f0, 0xb0(r30)
    stfs f0, 0x14(r31)
    stw r0, 0x8(r31)
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0xc(r31)
    b TornadoItem_TickActive_L_800F8364
    TornadoItem_TickActive_L_800F8310:
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
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x3
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F8358:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    TornadoItem_TickActive_L_800F8364:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne TornadoItem_TickActive_L_800F837C
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    TornadoItem_TickActive_L_800F837C:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne TornadoItem_TickActive_L_800F8428
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    addi r4, r1, 0x60
    stb r0, 0x8d(r30)
    li r3, 0xcb
    li r5, 0x0
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x60(r1)
    stw r0, 0x64(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x68(r1)
    bl SoundMgr_PlaySE_Positional
    addi r3, r30, 0xb8
    addi r5, r30, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D6220(r2)
    addi r3, r30, 0xb8
    lfs f1, lbl_806D6214(r2)
    stfs f0, 0xbc(r30)
    lfs f0, 0xb8(r30)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r30)
    lfs f0, 0xc0(r30)
    fmuls f0, f0, f1
    stfs f0, 0xc0(r30)
    bl Vec3_ToYaw
    lfs f0, lbl_806D624C(r2)
    fadds f1, f0, f1
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r30)
    li r4, 0x2
    li r3, 0x0
    li r0, 0x4
    stb r4, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F8428:
    mr r3, r30
    addi r4, r1, 0xf0
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq TornadoItem_TickActive_L_800F84E8
    lwz r6, 0xf0(r1)
    mr r3, r30
    lwz r7, 0xf4(r1)
    addi r4, r1, 0x54
    lwz r0, 0xf8(r1)
    li r5, 0x0
    stw r6, 0x54(r1)
    li r6, 0x3
    lfs f1, lbl_806D621C(r2)
    stw r7, 0x58(r1)
    lfs f2, lbl_806D61F0(r2)
    stw r0, 0x5c(r1)
    bl Item_BounceOffWall
    lbz r0, 0xca(r30)
    cmpwi r0, 0x1
    bne TornadoItem_TickActive_L_800F84A0
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    li r0, 0x0
    lfs f0, 0xb0(r30)
    stfs f0, 0x14(r31)
    stw r0, 0x8(r31)
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F84A0:
    lfs f0, lbl_806D6220(r2)
    addi r3, r30, 0xb8
    stfs f0, 0xbc(r30)
    bl Vec3_ToYaw
    lfs f0, lbl_806D624C(r2)
    fadds f1, f0, f1
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x7
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F84E8:
    lfs f1, lbl_806D6250(r2)
    mr r3, r30
    addi r4, r1, 0x8
    li r5, 0x0
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq TornadoItem_TickActive_L_800F8650
    lwz r0, 0x8(r1)
    cmpwi r0, 0x0
    beq TornadoItem_TickActive_L_800F8674
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x48
    lwz r0, 0xa4(r30)
    li r3, 0xad
    li r5, 0x0
    stw r6, 0x48(r1)
    stw r0, 0x4c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x50(r1)
    bl SoundMgr_PlaySE_Positional
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x3c
    lwz r0, 0xa4(r30)
    li r3, 0xb5
    li r5, 0x0
    stw r6, 0x3c(r1)
    stw r0, 0x40(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x44(r1)
    bl SoundMgr_PlaySE_Positional
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x30
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x24
    li r5, 0x3
    stw r6, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x2c(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x30(r1)
    stw r0, 0x34(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x38(r1)
    bl DrawEffect_ItemHitBurst_Spawn
    lbz r0, 0xca(r30)
    cmpwi r0, 0x3
    beq TornadoItem_TickActive_L_800F85E8
    lwz r4, 0xa0(r30)
    addi r3, r30, 0xb8
    lwz r0, 0xa4(r30)
    stw r4, 0x18(r1)
    stw r0, 0x1c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x20(r1)
    bl Vec3_Magnitude_Wrapper
    fmr f2, f1
    lfs f1, 0x14(r31)
    lfs f3, lbl_806D6254(r2)
    addi r3, r30, 0xb8
    addi r4, r1, 0x18
    bl Item_BendVelocityByGroundProbe
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F85E8:
    lwz r4, 0xa0(r30)
    addi r3, r30, 0xb8
    lwz r0, 0xa4(r30)
    stw r4, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x14(r1)
    bl Vec3_Magnitude_Wrapper
    fmr f31, f1
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    fmr f2, f31
    lfs f3, lbl_806D6258(r2)
    addi r3, r30, 0xb8
    addi r4, r1, 0xc
    bl Item_BendVelocityByGroundProbe
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x5
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b TornadoItem_TickActive_L_800F8674
    TornadoItem_TickActive_L_800F8650:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x9
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    TornadoItem_TickActive_L_800F8674:
    psq_l f31, 0x178(r1), 0, 0
    lwz r0, 0x184(r1)
    lfd f31, 0x170(r1)
    lwz r31, 0x16c(r1)
    lwz r30, 0x168(r1)
    lwz r29, 0x164(r1)
    lwz r28, 0x160(r1)
    mtlr r0
    addi r1, r1, 0x180
    blr
}

