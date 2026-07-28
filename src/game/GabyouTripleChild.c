/* GabyouTripleChild inline-assembly bundle: 0x800F3B20..0x800F4914. */

/* === extracted from auto_GabyouTripleChild_Ti_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void ItemObject_GetGroundTypeAt();
extern void Item_DecayVelocityScalar();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D60D0;
extern unsigned int lbl_806D60D4;
extern unsigned int lbl_806D60DC;
extern unsigned int lbl_806D60E0;
extern unsigned int lbl_806D60E4;

/* --- function index (1 fns, .text 0x800F3B20..0x800F3DC4) ---
 * [  0] 0x800F3B20 size:0x2A4   global GabyouTripleChild_TickHitResolve
 */

/* --- forward decls --- */
asm void GabyouTripleChild_TickHitResolve(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GabyouTripleChild_TickHitResolve[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GabyouTripleChild_TickHitResolve = {
    (void *)&GabyouTripleChild_TickHitResolve, 0x000002A4, (void *)extab_GabyouTripleChild_TickHitResolve
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GabyouTripleChild_TickHitResolve(void) { /* 0x800F3B20 size:0x2A4 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    mr r31, r4
    stw r30, 0x48(r1)
    mr r30, r3
    lbz r0, 0xc9(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq GabyouTripleChild_TickHitResolve_L_800F3BFC
    bge GabyouTripleChild_TickHitResolve_L_800F3BFC
    cmpwi r0, 0x0
    bge GabyouTripleChild_TickHitResolve_L_800F3B5C
    b GabyouTripleChild_TickHitResolve_L_800F3BFC
    GabyouTripleChild_TickHitResolve_L_800F3B5C:
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
    beq GabyouTripleChild_TickHitResolve_L_800F3B9C
    li r0, 0xa
    stw r0, 0x4(r31)
    b GabyouTripleChild_TickHitResolve_L_800F3BA4
    GabyouTripleChild_TickHitResolve_L_800F3B9C:
    li r0, 0x0
    stw r0, 0x4(r31)
    GabyouTripleChild_TickHitResolve_L_800F3BA4:
    lwz r3, 0x9c(r31)
    cmplwi r3, 0x0
    beq GabyouTripleChild_TickHitResolve_L_800F3BF0
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x30
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r31, 0x34
    addi r4, r30, 0xa0
    addi r5, r1, 0x30
    bl Vec3_Subtract_DestFirst
    addi r3, r31, 0x40
    addi r4, r30, 0xb8
    bl Vec3_Copy
    lfs f1, lbl_806D60D0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    GabyouTripleChild_TickHitResolve_L_800F3BF0:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    GabyouTripleChild_TickHitResolve_L_800F3BFC:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne GabyouTripleChild_TickHitResolve_L_800F3C40
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D60E0(r2)
    lfs f0, lbl_806D60D0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge GabyouTripleChild_TickHitResolve_L_800F3C40
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b GabyouTripleChild_TickHitResolve_L_800F3DAC
    GabyouTripleChild_TickHitResolve_L_800F3C40:
    lfs f1, lbl_806D60D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmpwi r0, 0x5
    beq GabyouTripleChild_TickHitResolve_L_800F3CC8
    bge GabyouTripleChild_TickHitResolve_L_800F3C78
    cmpwi r0, 0x0
    beq GabyouTripleChild_TickHitResolve_L_800F3C84
    blt GabyouTripleChild_TickHitResolve_L_800F3CC8
    cmpwi r0, 0x4
    bge GabyouTripleChild_TickHitResolve_L_800F3C9C
    b GabyouTripleChild_TickHitResolve_L_800F3CC8
    GabyouTripleChild_TickHitResolve_L_800F3C78:
    cmpwi r0, 0x9
    beq GabyouTripleChild_TickHitResolve_L_800F3CB4
    b GabyouTripleChild_TickHitResolve_L_800F3CC8
    GabyouTripleChild_TickHitResolve_L_800F3C84:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D60DC(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b GabyouTripleChild_TickHitResolve_L_800F3CC8
    GabyouTripleChild_TickHitResolve_L_800F3C9C:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D60DC(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b GabyouTripleChild_TickHitResolve_L_800F3CC8
    GabyouTripleChild_TickHitResolve_L_800F3CB4:
    lfs f1, lbl_806D60DC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    GabyouTripleChild_TickHitResolve_L_800F3CC8:
    lwz r3, 0x9c(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq GabyouTripleChild_TickHitResolve_L_800F3CE4
    li r0, 0x0
    stb r0, 0x28(r30)
    b GabyouTripleChild_TickHitResolve_L_800F3CEC
    GabyouTripleChild_TickHitResolve_L_800F3CE4:
    li r0, 0x1
    stb r0, 0x28(r30)
    GabyouTripleChild_TickHitResolve_L_800F3CEC:
    lwz r0, 0x9c(r31)
    cmplwi r0, 0x0
    bne GabyouTripleChild_TickHitResolve_L_800F3D68
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq GabyouTripleChild_TickHitResolve_L_800F3D14
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D60E4(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    GabyouTripleChild_TickHitResolve_L_800F3D14:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0xc
    lwz r0, 0xa4(r30)
    addi r4, r1, 0x8
    li r5, 0x0
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x14(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq GabyouTripleChild_TickHitResolve_L_800F3DAC
    lfs f1, 0x8(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stfs f0, 0x14(r31)
    b GabyouTripleChild_TickHitResolve_L_800F3DAC
    GabyouTripleChild_TickHitResolve_L_800F3D68:
    lfs f1, 0x44(r31)
    addi r3, r31, 0x34
    lfs f0, lbl_806D60E4(r2)
    mr r4, r3
    addi r5, r31, 0x40
    fadds f0, f1, f0
    stfs f0, 0x44(r31)
    bl Vec3_Add_DestFirst
    lwz r3, 0x9c(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x24
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r30, 0xa0
    addi r4, r1, 0x24
    addi r5, r31, 0x34
    bl Vec3_Add_DestFirst
    GabyouTripleChild_TickHitResolve_L_800F3DAC:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

/* === extracted from auto_GabyouTripleChild_Ti_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepForward_OrSnap();
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void DrawEffect_Free();
extern void DrawEffect_ItemHitOriented_Spawn();
extern void DrawEffect_SpawnDirect();
extern void FAbs_FloatAsDouble();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHitRegistry_AddEntry();
extern void ItemHitRegistry_RemoveEntry();
extern void ItemHit_Dispatch();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemObject_GetGroundTypeAt();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void Item_HomingScanAndSteer();
extern void Item_ProbeForwardGroundPitch();
extern void Item_ProbeLateralGroundPitch();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();
extern void Vec3_Add_DestFirst();
extern void Vec3_Scale();
extern void Vec3_ToYaw();
extern void fn_801B1D5C();
extern void fn_8027E240();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D60D0;
extern unsigned int lbl_806D60D4;
extern unsigned int lbl_806D60DC;
extern unsigned int lbl_806D60E4;
extern unsigned int lbl_806D60E8;
extern unsigned int lbl_806D60EC;
extern unsigned int lbl_806D60F0;
extern unsigned int lbl_806D60F4;
extern unsigned int lbl_806D60F8;
extern unsigned int lbl_806D60FC;
extern unsigned int lbl_806D6100;
extern unsigned int lbl_806D6104;
extern unsigned int lbl_806D6108;
extern unsigned int lbl_806D610C;
extern unsigned int lbl_806D6110;
extern unsigned int lbl_806D6114;
extern unsigned int lbl_806D6118;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int EffectVfx7F_PulseFan_Tick[];

/* --- function index (1 fns, .text 0x800F3DC4..0x800F4540) ---
 * [  0] 0x800F3DC4 size:0x77C   global GabyouTripleChild_TickActive
 */

/* --- forward decls --- */
asm void GabyouTripleChild_TickActive(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GabyouTripleChild_TickActive[8] = {
    0x28, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GabyouTripleChild_TickActive = {
    (void *)&GabyouTripleChild_TickActive, 0x0000077C, (void *)extab_GabyouTripleChild_TickActive
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GabyouTripleChild_TickActive(void) { /* 0x800F3DC4 size:0x77C */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stmw r27, 0x9c(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xc9(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq GabyouTripleChild_TickActive_L_800F3E28
    bge GabyouTripleChild_TickActive_L_800F4524
    cmpwi r0, 0x0
    bge GabyouTripleChild_TickActive_L_800F3E04
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F3E04:
    li r0, 0x1
    lfs f0, lbl_806D60E8(r2)
    stb r0, 0x28(r30)
    li r0, 0x0
    stfs f0, 0x2c(r30)
    lbz r3, 0xc9(r30)
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    GabyouTripleChild_TickActive_L_800F3E28:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq GabyouTripleChild_TickActive_L_800F3EB0
    bge GabyouTripleChild_TickActive_L_800F3ED0
    cmpwi r0, 0x0
    bge GabyouTripleChild_TickActive_L_800F3E4C
    b GabyouTripleChild_TickActive_L_800F3ED0
    b GabyouTripleChild_TickActive_L_800F3ED0
    GabyouTripleChild_TickActive_L_800F3E4C:
    mr r3, r30
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    lfs f1, lbl_806D60D0(r2)
    stb r0, 0x8d(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0x3c(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D60E8(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    li r3, 0x384
    li r0, 0x0
    stw r3, 0x4(r31)
    mr r3, r30
    stw r0, 0x8(r31)
    stw r0, 0xc(r31)
    lbz r4, 0xca(r30)
    addi r0, r4, 0x1
    stb r0, 0xca(r30)
    bl ItemHitRegistry_AddEntry
    GabyouTripleChild_TickActive_L_800F3EB0:
    lfs f1, 0xbc(r30)
    mr r3, r30
    lfs f0, lbl_806D60E4(r2)
    addi r4, r30, 0xb0
    li r5, 0x1
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    bl Item_HomingScanAndSteer
    GabyouTripleChild_TickActive_L_800F3ED0:
    lfs f1, lbl_806D60D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x4
    beq GabyouTripleChild_TickActive_L_800F4044
    bge GabyouTripleChild_TickActive_L_800F3F04
    cmpwi r28, 0x1
    beq GabyouTripleChild_TickActive_L_800F3F10
    bge GabyouTripleChild_TickActive_L_800F3F54
    b GabyouTripleChild_TickActive_L_800F4094
    GabyouTripleChild_TickActive_L_800F3F04:
    cmpwi r28, 0x6
    bge GabyouTripleChild_TickActive_L_800F4094
    b GabyouTripleChild_TickActive_L_800F4088
    GabyouTripleChild_TickActive_L_800F3F10:
    lbz r0, 0xca(r30)
    lwz r3, 0x8(r30)
    extsb r0, r0
    subfic r0, r0, 0x3
    cntlzw r0, r0
    srwi r27, r0, 5
    bl ItemAlias_HitRemapLookup
    extsh r29, r3
    mr r3, r30
    bl ItemTracker_GetTargetKart
    neg r0, r27
    mr r4, r3
    or r0, r0, r27
    lwz r3, 0x98(r31)
    srwi r6, r0, 31
    mr r5, r29
    bl fn_801B1D5C
    GabyouTripleChild_TickActive_L_800F3F54:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x3
    beq GabyouTripleChild_TickActive_L_800F3FE0
    cmpwi r28, 0x3
    bne GabyouTripleChild_TickActive_L_800F3FE0
    li r0, 0x0
    mr r3, r30
    stw r0, 0x7c(r31)
    lwz r4, 0xb8(r30)
    lwz r0, 0xbc(r30)
    stw r4, 0x60(r1)
    stw r0, 0x64(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x68(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x6c(r1)
    stw r0, 0x70(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x74(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0x6c
    addi r6, r1, 0x60
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0xc(r31)
    b GabyouTripleChild_TickActive_L_800F4094
    GabyouTripleChild_TickActive_L_800F3FE0:
    cmpwi r28, 0x1
    bne GabyouTripleChild_TickActive_L_800F3FFC
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    GabyouTripleChild_TickActive_L_800F3FFC:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    lfs f0, lbl_806D60EC(r2)
    stb r0, 0x8d(r30)
    stfs f0, 0xbc(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r3, 0x0
    li r0, 0x2
    stw r3, 0x4c(r31)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r3, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F4044:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r4, 0x0
    li r3, 0x2
    stw r4, 0x4c(r31)
    li r0, 0x3
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F4088:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    GabyouTripleChild_TickActive_L_800F4094:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne GabyouTripleChild_TickActive_L_800F40AC
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    GabyouTripleChild_TickActive_L_800F40AC:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne GabyouTripleChild_TickActive_L_800F414C
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r4, 0x0
    stw r4, 0x4c(r31)
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne GabyouTripleChild_TickActive_L_800F4134
    addi r3, r30, 0xb8
    addi r5, r30, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D60EC(r2)
    li r4, 0x2
    lfs f1, lbl_806D60F0(r2)
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
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F4134:
    li r3, 0x2
    li r0, 0x6
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F414C:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x3
    beq GabyouTripleChild_TickActive_L_800F41B0
    mr r3, r30
    addi r4, r1, 0x84
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq GabyouTripleChild_TickActive_L_800F41B0
    lwz r6, 0x84(r1)
    mr r3, r30
    lwz r7, 0x88(r1)
    addi r4, r1, 0x54
    lwz r0, 0x8c(r1)
    li r5, 0x0
    stw r6, 0x54(r1)
    li r6, 0x1
    lfs f1, lbl_806D60F0(r2)
    stw r7, 0x58(r1)
    lfs f2, lbl_806D60D0(r2)
    stw r0, 0x5c(r1)
    bl Item_BounceOffWall
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    GabyouTripleChild_TickActive_L_800F41B0:
    addi r3, r1, 0x78
    addi r4, r30, 0xa0
    addi r5, r30, 0xb8
    bl Vec3_Add_DestFirst
    lwz r7, 0x78(r1)
    addi r3, r1, 0x48
    lwz r6, 0x7c(r1)
    addi r4, r1, 0x8
    lwz r0, 0x80(r1)
    li r5, 0x0
    stw r7, 0x48(r1)
    stw r6, 0x4c(r1)
    stw r0, 0x50(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq GabyouTripleChild_TickActive_L_800F4488
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq GabyouTripleChild_TickActive_L_800F426C
    bge GabyouTripleChild_TickActive_L_800F4210
    cmpwi r0, 0x1
    bge GabyouTripleChild_TickActive_L_800F421C
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F4210:
    cmpwi r0, 0x4
    bge GabyouTripleChild_TickActive_L_800F44C0
    b GabyouTripleChild_TickActive_L_800F43F4
    GabyouTripleChild_TickActive_L_800F421C:
    lfs f1, lbl_806D60F4(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lfs f0, 0x7c(r1)
    lfs f1, 0x8(r1)
    fcmpo cr0, f0, f1
    bge GabyouTripleChild_TickActive_L_800F44C0
    stfs f1, 0xa4(r30)
    addi r3, r30, 0xb8
    lfs f0, lbl_806D60D0(r2)
    mr r4, r3
    lfs f1, lbl_806D60F8(r2)
    stfs f0, 0xbc(r30)
    bl Vec3_Scale
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F426C:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne GabyouTripleChild_TickActive_L_800F42C0
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x3c
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x30
    li r5, 0x1
    stw r6, 0x30(r1)
    stw r0, 0x34(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x38(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x3c(r1)
    stw r0, 0x40(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x44(r1)
    bl DrawEffect_ItemHitOriented_Spawn
    li r0, 0x3
    stw r0, 0x8(r31)
    GabyouTripleChild_TickActive_L_800F42C0:
    lfs f1, lbl_806D60FC(r2)
    bl fn_8027E240
    frsp f1, f1
    bl fn_8027E9E8
    frsp f2, f1
    lfs f0, lbl_806D6100(r2)
    lfs f1, 0xac(r30)
    fmuls f31, f0, f2
    bl BuildOrientationFromYaw
    bl FAbs_FloatAsDouble
    lfs f2, lbl_806D6104(r2)
    fcmpo cr0, f1, f2
    bge GabyouTripleChild_TickActive_L_800F4304
    lfs f0, lbl_806D6100(r2)
    fmuls f0, f0, f1
    fdivs f3, f0, f2
    b GabyouTripleChild_TickActive_L_800F434C
    GabyouTripleChild_TickActive_L_800F4304:
    lfs f0, lbl_806D6108(r2)
    fcmpo cr0, f1, f0
    bge GabyouTripleChild_TickActive_L_800F4330
    lfs f3, lbl_806D6100(r2)
    fsubs f2, f1, f2
    lfs f0, lbl_806D610C(r2)
    fsubs f1, f31, f3
    fmuls f1, f2, f1
    fdivs f0, f1, f0
    fadds f3, f3, f0
    b GabyouTripleChild_TickActive_L_800F434C
    GabyouTripleChild_TickActive_L_800F4330:
    lfs f2, lbl_806D6110(r2)
    fsubs f3, f1, f0
    lfs f0, lbl_806D610C(r2)
    fsubs f1, f2, f31
    fmuls f1, f3, f1
    fdivs f0, f1, f0
    fadds f3, f31, f0
    GabyouTripleChild_TickActive_L_800F434C:
    lfs f1, 0xc4(r30)
    addi r3, r1, 0x24
    lfs f0, 0x8(r1)
    fmuls f3, f3, f1
    lfs f2, lbl_806D6110(r2)
    fadds f0, f0, f3
    stfs f0, 0xa4(r30)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x2c(r1)
    lfs f1, 0xb0(r30)
    bl Item_ProbeForwardGroundPitch
    fmr f0, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D6114(r2)
    fmr f31, f0
    fmr f2, f31
    bl AngleStepForward_OrSnap
    stfs f1, 0xac(r30)
    lfs f0, 0xac(r30)
    fsubs f1, f0, f31
    bl BuildOrientationFromYaw
    bl FAbs_FloatAsDouble
    lfs f0, lbl_806D6118(r2)
    fcmpo cr0, f1, f0
    bge GabyouTripleChild_TickActive_L_800F44C0
    lfs f1, lbl_806D60D0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lis r3, EffectVfx7F_PulseFan_Tick@ha
    addi r3, r3, EffectVfx7F_PulseFan_Tick@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F43F4:
    lfs f0, 0x8(r1)
    addi r3, r1, 0x18
    lfs f2, lbl_806D6110(r2)
    stfs f0, 0xa4(r30)
    lfs f3, lbl_806D60D0(r2)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x18(r1)
    stw r0, 0x1c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x20(r1)
    lfs f1, 0xb0(r30)
    bl Item_ProbeForwardGroundPitch
    fmr f0, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D60DC(r2)
    fmr f2, f0
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    addi r3, r1, 0xc
    lfs f2, lbl_806D6110(r2)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    lfs f3, lbl_806D60D0(r2)
    stw r4, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x14(r1)
    lfs f1, 0xb0(r30)
    bl Item_ProbeLateralGroundPitch
    fmr f0, f1
    lfs f1, 0xb4(r30)
    lfs f3, lbl_806D60DC(r2)
    fmr f2, f0
    bl AngleStepTowards_Shortest
    stfs f1, 0xb4(r30)
    b GabyouTripleChild_TickActive_L_800F44C0
    GabyouTripleChild_TickActive_L_800F4488:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r4, 0x0
    li r3, 0x2
    stw r4, 0x4c(r31)
    li r0, 0x9
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b GabyouTripleChild_TickActive_L_800F4524
    GabyouTripleChild_TickActive_L_800F44C0:
    lwz r4, 0x4(r31)
    mr r3, r30
    li r5, 0x0
    bl ItemHitRegistry_RemoveEntry
    clrlwi. r0, r3, 24
    beq GabyouTripleChild_TickActive_L_800F4524
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r0, 0x10(r30)
    cmpwi r0, 0x0
    bne GabyouTripleChild_TickActive_L_800F451C
    mr r3, r30
    bl ItemObject_DecrementCategoryBudget
    GabyouTripleChild_TickActive_L_800F451C:
    mr r3, r30
    bl SpriteSlot_Container_Free
    GabyouTripleChild_TickActive_L_800F4524:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    lmw r27, 0x9c(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

/* === extracted from auto_GabyouTripleChild_Up_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DbgScene_CopyMatrix3x4Transpose();
extern void DrawEffect_Free();
extern void GabyouTripleChild_TickActive();
extern void GabyouTripleChild_TickHitResolve();
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_OrbitAnchorKart();
extern void Matrix4_Identity();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotY();
extern void Matrix4_PreMultiplyRotZ();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_TransformVec3();
extern void Mtx44_Translate();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void Vec3_Add_DestFirst();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D60D0;
extern unsigned int lbl_806D60D4;
extern unsigned int lbl_806D60D8;
extern unsigned int lbl_806D60DC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_80421738[];
extern unsigned int lbl_8032FA28[];

/* --- function index (1 fns, .text 0x800F4540..0x800F4914) ---
 * [  0] 0x800F4540 size:0x3D4   global GabyouTripleChild_Update
 */

/* --- forward decls --- */
asm void GabyouTripleChild_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GabyouTripleChild_Update[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GabyouTripleChild_Update = {
    (void *)&GabyouTripleChild_Update, 0x000003D4, (void *)extab_GabyouTripleChild_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GabyouTripleChild_Update(void) { /* 0x800F4540 size:0x3D4 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stw r31, 0xbc(r1)
    stw r30, 0xb8(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq GabyouTripleChild_Update_L_800F45E4
    bge GabyouTripleChild_Update_L_800F4580
    cmpwi r0, 0x0
    beq GabyouTripleChild_Update_L_800F458C
    bge GabyouTripleChild_Update_L_800F45D4
    b GabyouTripleChild_Update_L_800F47A4
    GabyouTripleChild_Update_L_800F4580:
    cmpwi r0, 0x4
    bge GabyouTripleChild_Update_L_800F47A4
    b GabyouTripleChild_Update_L_800F4774
    GabyouTripleChild_Update_L_800F458C:
    li r3, 0x1
    li r0, 0x46
    stb r3, 0x90(r31)
    addi r3, r30, 0x14
    li r4, 0x49
    stw r0, 0x8(r30)
    bl SpriteSlot_InitNonLoop
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r4, 0x1
    li r3, 0x2
    stb r4, 0x0(r31)
    li r0, 0x0
    stb r3, 0x8c(r30)
    stb r0, 0x8d(r30)
    stb r4, 0xc8(r30)
    stb r0, 0xc9(r30)
    GabyouTripleChild_Update_L_800F45D4:
    mr r3, r30
    mr r4, r31
    bl GabyouTripleChild_TickActive
    b GabyouTripleChild_Update_L_800F47A4
    GabyouTripleChild_Update_L_800F45E4:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt GabyouTripleChild_Update_L_800F47A4
    lis r4, jumptable_80421738@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_80421738@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    mr r4, r31
    bl GabyouTripleChild_TickHitResolve
    b GabyouTripleChild_Update_L_800F47A4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq GabyouTripleChild_Update_L_800F4670
    bge GabyouTripleChild_Update_L_800F4670
    cmpwi r0, 0x0
    bge GabyouTripleChild_Update_L_800F4638
    b GabyouTripleChild_Update_L_800F4670
    GabyouTripleChild_Update_L_800F4638:
    lfs f1, lbl_806D60D0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D60D0(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    GabyouTripleChild_Update_L_800F4670:
    lfs f2, lbl_806D60DC(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq GabyouTripleChild_Update_L_800F47A4
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b GabyouTripleChild_Update_L_800F47A4
    mr r4, r31
    bl GabyouTripleChild_TickHitResolve
    b GabyouTripleChild_Update_L_800F47A4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq GabyouTripleChild_Update_L_800F4718
    bge GabyouTripleChild_Update_L_800F4718
    cmpwi r0, 0x0
    bge GabyouTripleChild_Update_L_800F46D4
    b GabyouTripleChild_Update_L_800F4718
    GabyouTripleChild_Update_L_800F46D4:
    lfs f1, lbl_806D60D0(r2)
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
    GabyouTripleChild_Update_L_800F4718:
    lfs f1, lbl_806D60D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, lbl_806D60D8(r2)
    mr r3, r30
    lwz r5, 0x4(r31)
    addi r4, r31, 0x34
    fmr f2, f1
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq GabyouTripleChild_Update_L_800F47A4
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b GabyouTripleChild_Update_L_800F47A4
    mr r4, r31
    bl GabyouTripleChild_TickHitResolve
    b GabyouTripleChild_Update_L_800F47A4
    mr r4, r31
    bl GabyouTripleChild_TickHitResolve
    b GabyouTripleChild_Update_L_800F47A4
    GabyouTripleChild_Update_L_800F4774:
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r0, 0x10(r30)
    cmpwi r0, 0x0
    bne GabyouTripleChild_Update_L_800F4798
    mr r3, r30
    bl ItemObject_DecrementCategoryBudget
    GabyouTripleChild_Update_L_800F4798:
    mr r3, r30
    bl SpriteSlot_Container_Free
    b GabyouTripleChild_Update_L_800F48FC
    GabyouTripleChild_Update_L_800F47A4:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq GabyouTripleChild_Update_L_800F483C
    addi r3, r1, 0x6c
    bl Matrix4_Identity
    addi r3, r1, 0x6c
    lfs f1, 0xc4(r30)
    mr r4, r3
    bl Mtx44_Scale_Uniform
    addi r3, r1, 0x6c
    lfs f1, 0xb4(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotZ
    addi r3, r1, 0x6c
    lfs f1, 0xac(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    addi r3, r1, 0x6c
    lfs f1, 0xb0(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x6c
    lwz r0, 0xa4(r30)
    mr r4, r3
    addi r5, r1, 0x14
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    bl Mtx44_Translate
    addi r3, r30, 0x48
    addi r4, r1, 0x6c
    bl DbgScene_CopyMatrix3x4Transpose
    GabyouTripleChild_Update_L_800F483C:
    lwz r0, 0x4c(r31)
    cmplwi r0, 0x0
    beq GabyouTripleChild_Update_L_800F48AC
    lis r4, lbl_8032FA28@ha
    addi r3, r1, 0x2c
    addi r7, r4, lbl_8032FA28@l
    addi r4, r30, 0x48
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r6, 0x20(r1)
    stw r5, 0x24(r1)
    stw r0, 0x28(r1)
    bl Mtx_TransposeToMtx44
    lwz r6, 0x20(r1)
    addi r4, r1, 0x2c
    lwz r3, 0x24(r1)
    addi r5, r1, 0x8
    lwz r0, 0x28(r1)
    stw r6, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r3, 0x4c(r31)
    addi r3, r3, 0x8c
    bl Mtx44_TransformVec3
    lfs f0, 0xc4(r30)
    lwz r3, 0x4c(r31)
    stfs f0, 0xb0(r3)
    GabyouTripleChild_Update_L_800F48AC:
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq GabyouTripleChild_Update_L_800F48C0
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    GabyouTripleChild_Update_L_800F48C0:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq GabyouTripleChild_Update_L_800F48D4
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    GabyouTripleChild_Update_L_800F48D4:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq GabyouTripleChild_Update_L_800F48E8
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    GabyouTripleChild_Update_L_800F48E8:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq GabyouTripleChild_Update_L_800F48FC
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    GabyouTripleChild_Update_L_800F48FC:
    lwz r0, 0xc4(r1)
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

