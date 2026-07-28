/* === extracted from auto_OnchiSpeaker_State1_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHit_Dispatch();
extern void ItemObject_GetGroundTypeAt();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceProjectileSimple();
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
extern void Vec3_Add_DestFirst();
extern void Vec3_ToYaw();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D5F18;
extern unsigned int lbl_806D5F1C;
extern unsigned int lbl_806D5F20;
extern unsigned int lbl_806D5F3C;
extern unsigned int lbl_806D5F4C;
extern unsigned int lbl_806D5F50;
extern unsigned int lbl_806D5F54;
extern unsigned int lbl_806D5F58;
extern unsigned int lbl_806D5F5C;
extern unsigned int lbl_806D5F60;
extern unsigned int lbl_806D5F64;
extern unsigned int lbl_806D5F68;

/* --- function index (1 fns, .text 0x800EE8D8..0x800EEF34) ---
 * [  0] 0x800EE8D8 size:0x65C   global OnchiSpeaker_State1_Held
 */

/* --- forward decls --- */
asm void OnchiSpeaker_State1_Held(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_OnchiSpeaker_State1_Held[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_OnchiSpeaker_State1_Held = {
    (void *)&OnchiSpeaker_State1_Held, 0x0000065C, (void *)extab_OnchiSpeaker_State1_Held
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void OnchiSpeaker_State1_Held(void) { /* 0x800EE8D8 size:0x65C */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    mr r31, r4
    stw r30, 0x58(r1)
    mr r30, r3
    stw r29, 0x54(r1)
    lbz r4, 0xc9(r3)
    extsb r0, r4
    cmpwi r0, 0x1
    beq OnchiSpeaker_State1_Held_L_800EE934
    bge OnchiSpeaker_State1_Held_L_800EE918
    cmpwi r0, 0x0
    bge OnchiSpeaker_State1_Held_L_800EE924
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EE918:
    cmpwi r0, 0x3
    bge OnchiSpeaker_State1_Held_L_800EEF18
    b OnchiSpeaker_State1_Held_L_800EEA74
    OnchiSpeaker_State1_Held_L_800EE924:
    addi r3, r4, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    OnchiSpeaker_State1_Held_L_800EE934:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq OnchiSpeaker_State1_Held_L_800EE998
    bge OnchiSpeaker_State1_Held_L_800EEF18
    cmpwi r0, 0x0
    bge OnchiSpeaker_State1_Held_L_800EE954
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EE954:
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5F1C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    li r0, 0x1
    lfs f0, lbl_806D5F18(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    OnchiSpeaker_State1_Held_L_800EE998:
    lfs f1, lbl_806D5F20(r2)
    mr r3, r30
    lfs f2, lbl_806D5F4C(r2)
    li r4, 0x1
    lfs f3, lbl_806D5F50(r2)
    bl GabyouItem_BuildLocalTransformFromHandJoint
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq OnchiSpeaker_State1_Held_L_800EE9CC
    li r0, 0x0
    stb r0, 0x28(r30)
    b OnchiSpeaker_State1_Held_L_800EE9D4
    OnchiSpeaker_State1_Held_L_800EE9CC:
    li r0, 0x1
    stb r0, 0x28(r30)
    OnchiSpeaker_State1_Held_L_800EE9D4:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq OnchiSpeaker_State1_Held_L_800EEA3C
    bge OnchiSpeaker_State1_Held_L_800EEA58
    cmpwi r0, 0x1
    bge OnchiSpeaker_State1_Held_L_800EE9F4
    b OnchiSpeaker_State1_Held_L_800EEA58
    OnchiSpeaker_State1_Held_L_800EE9F4:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0xa0(r31)
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D5F54(r2)
    mr r3, r30
    lfs f2, lbl_806D5F18(r2)
    addi r4, r31, 0x34
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEA3C:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEA58:
    lwz r3, 0x98(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEA74:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq OnchiSpeaker_State1_Held_L_800EEB20
    bge OnchiSpeaker_State1_Held_L_800EEB20
    cmpwi r0, 0x0
    bge OnchiSpeaker_State1_Held_L_800EEA94
    b OnchiSpeaker_State1_Held_L_800EEB20
    OnchiSpeaker_State1_Held_L_800EEA94:
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    lfs f1, lbl_806D5F18(r2)
    stb r0, 0x8d(r30)
    addi r3, r30, 0x14
    li r4, 0x1
    stb r0, 0x3c(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5F1C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x38
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x38(r1)
    stw r0, 0x3c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x40(r1)
    bl ItemObject_GetGroundTypeAt
    lfs f1, 0xa4(r30)
    li r3, 0x12c
    lfs f0, 0x14(r31)
    li r0, 0x0
    fsubs f0, f1, f0
    stfs f0, 0x14(r31)
    stw r3, 0x4(r31)
    stw r0, 0x8(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    OnchiSpeaker_State1_Held_L_800EEB20:
    mr r3, r30
    addi r4, r30, 0xb0
    li r5, 0x0
    bl Item_HomingScanAndSteer
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne OnchiSpeaker_State1_Held_L_800EEB44
    lfs f2, lbl_806D5F1C(r2)
    b OnchiSpeaker_State1_Held_L_800EEB48
    OnchiSpeaker_State1_Held_L_800EEB44:
    lfs f2, lbl_806D5F3C(r2)
    OnchiSpeaker_State1_Held_L_800EEB48:
    cmpwi r0, 0x0
    mr r3, r30
    bne OnchiSpeaker_State1_Held_L_800EEB5C
    lfs f1, lbl_806D5F58(r2)
    b OnchiSpeaker_State1_Held_L_800EEB60
    OnchiSpeaker_State1_Held_L_800EEB5C:
    lfs f1, lbl_806D5F5C(r2)
    OnchiSpeaker_State1_Held_L_800EEB60:
    bl Item_AccelClampVelocity
    lfs f1, lbl_806D5F20(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    cmpwi r3, 0x3
    beq OnchiSpeaker_State1_Held_L_800EEC7C
    bge OnchiSpeaker_State1_Held_L_800EEB94
    cmpwi r3, 0x1
    beq OnchiSpeaker_State1_Held_L_800EEBA4
    bge OnchiSpeaker_State1_Held_L_800EEC10
    b OnchiSpeaker_State1_Held_L_800EED5C
    OnchiSpeaker_State1_Held_L_800EEB94:
    cmpwi r3, 0x5
    beq OnchiSpeaker_State1_Held_L_800EED50
    bge OnchiSpeaker_State1_Held_L_800EED5C
    b OnchiSpeaker_State1_Held_L_800EED08
    OnchiSpeaker_State1_Held_L_800EEBA4:
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
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r3, 0x0
    li r0, 0x2
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r3, 0xcb(r30)
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEC10:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    lfs f0, lbl_806D5F3C(r2)
    stb r4, 0x8d(r30)
    li r3, 0x2
    lfs f1, lbl_806D5F60(r2)
    li r0, 0x1
    stfs f0, 0xbc(r30)
    lfs f0, 0xb8(r30)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r30)
    lfs f0, 0xc0(r30)
    fmuls f0, f0, f1
    stfs f0, 0xc0(r30)
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEC7C:
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
    stw r4, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x28(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x34(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0x2c
    addi r6, r1, 0x20
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0x8(r31)
    b OnchiSpeaker_State1_Held_L_800EED5C
    OnchiSpeaker_State1_Held_L_800EED08:
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
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EED50:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    OnchiSpeaker_State1_Held_L_800EED5C:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne OnchiSpeaker_State1_Held_L_800EED74
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    OnchiSpeaker_State1_Held_L_800EED74:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne OnchiSpeaker_State1_Held_L_800EEE2C
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    stb r4, 0x8d(r30)
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne OnchiSpeaker_State1_Held_L_800EEE14
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x14
    lwz r0, 0xa4(r30)
    li r3, 0xcb
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
    lfs f0, lbl_806D5F3C(r2)
    li r4, 0x2
    lfs f1, lbl_806D5F64(r2)
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
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEE14:
    li r3, 0x2
    li r0, 0x6
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEE2C:
    mr r3, r30
    addi r4, r1, 0x44
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq OnchiSpeaker_State1_Held_L_800EEEA4
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    lfs f1, lbl_806D5F64(r2)
    stb r0, 0x8d(r30)
    mr r3, r30
    lfs f2, lbl_806D5F3C(r2)
    addi r4, r1, 0x8
    lwz r8, 0x44(r1)
    li r5, 0xcb
    lwz r7, 0x48(r1)
    li r6, 0x2
    lwz r0, 0x4c(r1)
    stw r8, 0x8(r1)
    stw r7, 0xc(r1)
    stw r0, 0x10(r1)
    bl Item_BounceOffWall
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x7
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEEA4:
    lfs f1, lbl_806D5F68(r2)
    mr r3, r30
    addi r4, r31, 0x14
    fmr f2, f1
    bl Item_AdvanceProjectileSimple
    cmpwi r3, 0x0
    bne OnchiSpeaker_State1_Held_L_800EEEE8
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x9
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b OnchiSpeaker_State1_Held_L_800EEF18
    OnchiSpeaker_State1_Held_L_800EEEE8:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne OnchiSpeaker_State1_Held_L_800EEF18
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x5
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    OnchiSpeaker_State1_Held_L_800EEF18:
    lwz r0, 0x64(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    lwz r29, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

