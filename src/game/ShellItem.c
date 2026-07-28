/*
 * ShellItem unit: exact target asm_fn bodies and extab data.
 * Generated from the four reversed-extab singleton groups with
 * tools/extract_fn_asm.py; promote individual members to C later.
 */

/* === extracted from auto_ShellItem_TickReboun_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void ItemHit_Dispatch();
extern void Item_DecayVelocityScalar();
extern void Item_PrepareHitRebound();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_PlaySE_Positional();
extern void Vec3_AddNormalizedXZ();
extern void Vec3_Add_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D6128;
extern unsigned int lbl_806D612C;
extern unsigned int lbl_806D6138;
extern unsigned int lbl_806D613C;
extern unsigned int lbl_806D6140;
extern unsigned int lbl_806D6144;

/* --- function index (1 fns, .text 0x800F4C28..0x800F4E5C) ---
 * [  0] 0x800F4C28 size:0x234   global ShellItem_TickReboundOrCarry
 */

/* --- forward decls --- */
asm void ShellItem_TickReboundOrCarry(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ShellItem_TickReboundOrCarry[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ShellItem_TickReboundOrCarry = {
    (void *)&ShellItem_TickReboundOrCarry, 0x00000234, (void *)extab_ShellItem_TickReboundOrCarry
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ShellItem_TickReboundOrCarry(void) { /* 0x800F4C28 size:0x234 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stw r31, 0x3c(r1)
    mr r31, r4
    stw r30, 0x38(r1)
    mr r30, r3
    lwz r3, 0x9c(r4)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x20
    bl Mtx44_GetTranslation_RowMajor
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ShellItem_TickReboundOrCarry_L_800F4CA4
    bge ShellItem_TickReboundOrCarry_L_800F4C78
    cmpwi r0, 0x0
    bge ShellItem_TickReboundOrCarry_L_800F4C84
    b ShellItem_TickReboundOrCarry_L_800F4DF0
    ShellItem_TickReboundOrCarry_L_800F4C78:
    cmpwi r0, 0x3
    bge ShellItem_TickReboundOrCarry_L_800F4DF0
    b ShellItem_TickReboundOrCarry_L_800F4CEC
    ShellItem_TickReboundOrCarry_L_800F4C84:
    mr r3, r30
    addi r4, r31, 0x40
    addi r5, r31, 0x34
    addi r6, r31, 0x4
    bl Item_PrepareHitRebound
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    ShellItem_TickReboundOrCarry_L_800F4CA4:
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
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne ShellItem_TickReboundOrCarry_L_800F4DF0
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b ShellItem_TickReboundOrCarry_L_800F4DF0
    ShellItem_TickReboundOrCarry_L_800F4CEC:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ShellItem_TickReboundOrCarry_L_800F4D8C
    bge ShellItem_TickReboundOrCarry_L_800F4D8C
    cmpwi r0, 0x0
    bge ShellItem_TickReboundOrCarry_L_800F4D0C
    b ShellItem_TickReboundOrCarry_L_800F4D8C
    ShellItem_TickReboundOrCarry_L_800F4D0C:
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq ShellItem_TickReboundOrCarry_L_800F4D2C
    lwz r6, 0x9c(r31)
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    bl ItemHit_Dispatch
    ShellItem_TickReboundOrCarry_L_800F4D2C:
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x8
    lwz r0, 0xa4(r30)
    li r3, 0xcb
    li r5, 0x0
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x10(r1)
    bl SoundMgr_PlaySE_Positional
    lfs f0, lbl_806D612C(r2)
    li r0, 0xa
    lfs f1, lbl_806D6138(r2)
    stfs f0, 0x38(r31)
    lfs f0, 0x34(r31)
    fmuls f0, f0, f1
    stfs f0, 0x34(r31)
    lfs f0, 0x3c(r31)
    fmuls f0, f0, f1
    stfs f0, 0x3c(r31)
    stw r0, 0x4(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    ShellItem_TickReboundOrCarry_L_800F4D8C:
    lfs f1, 0x38(r31)
    addi r3, r31, 0x40
    lfs f0, lbl_806D613C(r2)
    mr r4, r3
    addi r5, r31, 0x34
    fadds f0, f1, f0
    stfs f0, 0x38(r31)
    bl Vec3_Add_DestFirst
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne ShellItem_TickReboundOrCarry_L_800F4DF0
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D6140(r2)
    lfs f0, lbl_806D6128(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge ShellItem_TickReboundOrCarry_L_800F4DF0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b ShellItem_TickReboundOrCarry_L_800F4E44
    ShellItem_TickReboundOrCarry_L_800F4DF0:
    addi r3, r30, 0xa0
    addi r4, r1, 0x20
    addi r5, r31, 0x40
    bl Vec3_Add_DestFirst
    lfs f1, lbl_806D6144(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    mr r3, r30
    lfs f1, lbl_806D612C(r2)
    bl Item_DecayVelocityScalar
    lwz r3, 0x9c(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq ShellItem_TickReboundOrCarry_L_800F4E3C
    li r0, 0x0
    stb r0, 0x28(r30)
    b ShellItem_TickReboundOrCarry_L_800F4E44
    ShellItem_TickReboundOrCarry_L_800F4E3C:
    li r0, 0x1
    stb r0, 0x28(r30)
    ShellItem_TickReboundOrCarry_L_800F4E44:
    lwz r0, 0x44(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

/* === extracted from auto_ShellItem_TickHitRes_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void ItemObject_GetGroundTypeAt();
extern void Item_DecayVelocityScalar();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D6128;
extern unsigned int lbl_806D612C;
extern unsigned int lbl_806D613C;
extern unsigned int lbl_806D6140;
extern unsigned int lbl_806D6148;
extern unsigned int lbl_806D614C;

/* --- function index (1 fns, .text 0x800F4E5C..0x800F5068) ---
 * [  0] 0x800F4E5C size:0x20C   global ShellItem_TickHitResolve
 */

/* --- forward decls --- */
asm void ShellItem_TickHitResolve(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ShellItem_TickHitResolve[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ShellItem_TickHitResolve = {
    (void *)&ShellItem_TickHitResolve, 0x0000020C, (void *)extab_ShellItem_TickHitResolve
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ShellItem_TickHitResolve(void) { /* 0x800F4E5C size:0x20C */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r4
    stw r30, 0x28(r1)
    mr r30, r3
    lbz r0, 0xc9(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ShellItem_TickHitResolve_L_800F4F00
    bge ShellItem_TickHitResolve_L_800F4F00
    cmpwi r0, 0x0
    bge ShellItem_TickHitResolve_L_800F4E98
    b ShellItem_TickHitResolve_L_800F4F00
    ShellItem_TickHitResolve_L_800F4E98:
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
    beq ShellItem_TickHitResolve_L_800F4ED8
    li r0, 0xa
    stw r0, 0x4(r31)
    b ShellItem_TickHitResolve_L_800F4EE0
    ShellItem_TickHitResolve_L_800F4ED8:
    li r0, 0x0
    stw r0, 0x4(r31)
    ShellItem_TickHitResolve_L_800F4EE0:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    bne ShellItem_TickHitResolve_L_800F4EF4
    lfs f0, lbl_806D6128(r2)
    stfs f0, 0xbc(r30)
    ShellItem_TickHitResolve_L_800F4EF4:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    ShellItem_TickHitResolve_L_800F4F00:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne ShellItem_TickHitResolve_L_800F4F44
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D6140(r2)
    lfs f0, lbl_806D6128(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge ShellItem_TickHitResolve_L_800F4F44
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b ShellItem_TickHitResolve_L_800F5050
    ShellItem_TickHitResolve_L_800F4F44:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq ShellItem_TickHitResolve_L_800F4F60
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D613C(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    ShellItem_TickHitResolve_L_800F4F60:
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
    beq ShellItem_TickHitResolve_L_800F4FB0
    lfs f1, 0x8(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stfs f0, 0x14(r31)
    ShellItem_TickHitResolve_L_800F4FB0:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmpwi r0, 0x7
    beq ShellItem_TickHitResolve_L_800F5000
    bge ShellItem_TickHitResolve_L_800F4FDC
    cmpwi r0, 0x5
    beq ShellItem_TickHitResolve_L_800F5030
    bge ShellItem_TickHitResolve_L_800F5044
    cmpwi r0, 0x4
    bge ShellItem_TickHitResolve_L_800F4FE8
    b ShellItem_TickHitResolve_L_800F5044
    ShellItem_TickHitResolve_L_800F4FDC:
    cmpwi r0, 0x9
    beq ShellItem_TickHitResolve_L_800F5018
    b ShellItem_TickHitResolve_L_800F5044
    ShellItem_TickHitResolve_L_800F4FE8:
    lfs f1, lbl_806D6148(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b ShellItem_TickHitResolve_L_800F5044
    ShellItem_TickHitResolve_L_800F5000:
    lfs f1, lbl_806D6148(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b ShellItem_TickHitResolve_L_800F5044
    ShellItem_TickHitResolve_L_800F5018:
    lfs f1, lbl_806D614C(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b ShellItem_TickHitResolve_L_800F5044
    ShellItem_TickHitResolve_L_800F5030:
    lfs f1, lbl_806D614C(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    ShellItem_TickHitResolve_L_800F5044:
    lfs f1, lbl_806D612C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    ShellItem_TickHitResolve_L_800F5050:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

/* === extracted from auto_ShellItem_TickActive_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemObject_AllocGabyou();
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
extern void Item_RenderFlyingFromKart();
extern void Item_SpawnGroundExplosionAndFX();
extern void KartDriver_GetJointByIdx();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void Vec3_Add_DestFirst();
extern void Vec3_HorizontalMagnitude();
extern void Vec3_ScaleXZ();
extern void Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D6128;
extern unsigned int lbl_806D612C;
extern unsigned int lbl_806D6138;
extern unsigned int lbl_806D614C;
extern unsigned int lbl_806D6150;
extern unsigned int lbl_806D6154;
extern unsigned int lbl_806D6158;
extern unsigned int lbl_806D615C;
extern unsigned int lbl_806D6160;
extern unsigned int lbl_806D6164;
extern unsigned int lbl_806D6168;
extern unsigned int lbl_806D616C;
extern unsigned int lbl_806D6170;
extern unsigned int lbl_806D6174;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8032FA38[];

/* --- function index (1 fns, .text 0x800F5068..0x800F583C) ---
 * [  0] 0x800F5068 size:0x7D4   global ShellItem_TickActive
 */

/* --- forward decls --- */
asm void ShellItem_TickActive(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ShellItem_TickActive[8] = {
    0x20, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ShellItem_TickActive = {
    (void *)&ShellItem_TickActive, 0x000007D4, (void *)extab_ShellItem_TickActive
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ShellItem_TickActive(void) { /* 0x800F5068 size:0x7D4 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stfd f30, 0x80(r1)
    psq_st f30, 0x88(r1), 0, 0
    stw r31, 0x7c(r1)
    stw r30, 0x78(r1)
    stw r29, 0x74(r1)
    stw r28, 0x70(r1)
    mr r30, r3
    mr r31, r4
    lbz r4, 0xc9(r3)
    extsb r0, r4
    cmpwi r0, 0x1
    beq ShellItem_TickActive_L_800F5110
    bge ShellItem_TickActive_L_800F50BC
    cmpwi r0, 0x0
    bge ShellItem_TickActive_L_800F50C8
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F50BC:
    cmpwi r0, 0x3
    bge ShellItem_TickActive_L_800F580C
    b ShellItem_TickActive_L_800F5260
    ShellItem_TickActive_L_800F50C8:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x49
    bne ShellItem_TickActive_L_800F5100
    bl Item_SpawnGroundExplosionAndFX
    lfs f1, lbl_806D612C(r2)
    li r3, 0x0
    lfs f0, lbl_806D6150(r2)
    li r0, 0x2
    stfs f1, 0xc4(r30)
    stfs f0, 0x2c(r30)
    stb r3, 0x28(r30)
    stb r0, 0xc9(r30)
    stb r3, 0xca(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5100:
    addi r3, r4, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    ShellItem_TickActive_L_800F5110:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ShellItem_TickActive_L_800F5160
    bge ShellItem_TickActive_L_800F580C
    cmpwi r0, 0x0
    bge ShellItem_TickActive_L_800F5130
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5130:
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    bl ItemObject_AllocGabyou
    stw r3, 0x5c(r31)
    li r0, 0x1
    lfs f0, lbl_806D6128(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    ShellItem_TickActive_L_800F5160:
    lwz r4, 0x5c(r31)
    mr r3, r30
    lfs f1, lbl_806D6154(r2)
    li r5, 0x1
    lfs f2, lbl_806D6158(r2)
    lfs f3, lbl_806D6150(r2)
    bl Item_RenderFlyingFromKart
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq ShellItem_TickActive_L_800F5198
    li r0, 0x0
    stb r0, 0x28(r30)
    b ShellItem_TickActive_L_800F51A0
    ShellItem_TickActive_L_800F5198:
    li r0, 0x1
    stb r0, 0x28(r30)
    ShellItem_TickActive_L_800F51A0:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq ShellItem_TickActive_L_800F5218
    bge ShellItem_TickActive_L_800F5244
    cmpwi r0, 0x1
    bge ShellItem_TickActive_L_800F51C0
    b ShellItem_TickActive_L_800F5244
    ShellItem_TickActive_L_800F51C0:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0xa0(r31)
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lwz r3, 0x5c(r31)
    bl SpriteSlot_Container_Free
    li r0, 0x0
    lfs f1, lbl_806D615C(r2)
    stw r0, 0x5c(r31)
    mr r3, r30
    lfs f2, lbl_806D6128(r2)
    addi r4, r31, 0x34
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5218:
    li r0, 0x0
    stb r0, 0xa0(r31)
    lwz r3, 0x5c(r31)
    bl SpriteSlot_Container_Free
    li r3, 0x0
    li r0, 0x3
    stw r3, 0x5c(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5244:
    lwz r3, 0x98(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5260:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ShellItem_TickActive_L_800F52F4
    bge ShellItem_TickActive_L_800F52F4
    cmpwi r0, 0x0
    bge ShellItem_TickActive_L_800F5280
    b ShellItem_TickActive_L_800F52F4
    ShellItem_TickActive_L_800F5280:
    li r0, 0x1
    stb r0, 0x28(r30)
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    addi r3, r1, 0x38
    stb r0, 0x8d(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stb r0, 0x3c(r30)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x38(r1)
    stw r0, 0x3c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x40(r1)
    bl ItemObject_GetGroundTypeAt
    lfs f1, 0xa4(r30)
    li r4, 0x12c
    lfs f0, 0x14(r31)
    li r3, 0x0
    li r0, 0x1
    fsubs f0, f1, f0
    stfs f0, 0x14(r31)
    stw r4, 0x4(r31)
    stw r3, 0x8(r31)
    stb r0, 0xca(r30)
    ShellItem_TickActive_L_800F52F4:
    lfs f1, lbl_806D614C(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lwz r0, 0x8(r30)
    cmpwi r0, 0x48
    beq ShellItem_TickActive_L_800F5370
    bge ShellItem_TickActive_L_800F5324
    cmpwi r0, 0x47
    bge ShellItem_TickActive_L_800F5330
    b ShellItem_TickActive_L_800F548C
    ShellItem_TickActive_L_800F5324:
    cmpwi r0, 0x4a
    bge ShellItem_TickActive_L_800F548C
    b ShellItem_TickActive_L_800F53B8
    ShellItem_TickActive_L_800F5330:
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne ShellItem_TickActive_L_800F5344
    lfs f2, lbl_806D6150(r2)
    b ShellItem_TickActive_L_800F5348
    ShellItem_TickActive_L_800F5344:
    lfs f2, lbl_806D612C(r2)
    ShellItem_TickActive_L_800F5348:
    cmpwi r0, 0x0
    mr r3, r30
    bne ShellItem_TickActive_L_800F535C
    lfs f1, lbl_806D6160(r2)
    b ShellItem_TickActive_L_800F5360
    ShellItem_TickActive_L_800F535C:
    lfs f1, lbl_806D6164(r2)
    ShellItem_TickActive_L_800F5360:
    bl Item_AccelClampVelocity
    addi r3, r30, 0xa0
    bl fn_801B129C
    b ShellItem_TickActive_L_800F548C
    ShellItem_TickActive_L_800F5370:
    mr r3, r30
    addi r4, r30, 0xb0
    li r5, 0x1
    bl Item_HomingScanAndSteer
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne ShellItem_TickActive_L_800F5394
    lfs f2, lbl_806D6150(r2)
    b ShellItem_TickActive_L_800F5398
    ShellItem_TickActive_L_800F5394:
    lfs f2, lbl_806D612C(r2)
    ShellItem_TickActive_L_800F5398:
    cmpwi r0, 0x0
    mr r3, r30
    bne ShellItem_TickActive_L_800F53AC
    lfs f1, lbl_806D6168(r2)
    b ShellItem_TickActive_L_800F53B0
    ShellItem_TickActive_L_800F53AC:
    lfs f1, lbl_806D6160(r2)
    ShellItem_TickActive_L_800F53B0:
    bl Item_AccelClampVelocity
    b ShellItem_TickActive_L_800F548C
    ShellItem_TickActive_L_800F53B8:
    mr r3, r30
    addi r4, r30, 0xb0
    li r5, 0x1
    bl Item_HomingScanAndSteer
    addi r3, r30, 0xb8
    bl Vec3_HorizontalMagnitude
    lfs f0, lbl_806D6150(r2)
    lwz r0, g_ccClass(r13)
    fdivs f31, f0, f1
    cmpwi r0, 0x0
    bne ShellItem_TickActive_L_800F53EC
    lfs f0, lbl_806D616C(r2)
    b ShellItem_TickActive_L_800F53F0
    ShellItem_TickActive_L_800F53EC:
    lfs f0, lbl_806D6170(r2)
    ShellItem_TickActive_L_800F53F0:
    lwz r3, 0x7c(r31)
    fmuls f30, f31, f0
    cmplwi r3, 0x0
    beq ShellItem_TickActive_L_800F547C
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x5c
    bl Mtx44_GetTranslation_RowMajor
    lis r3, lbl_8032FA38@ha
    lfs f2, 0x5c(r1)
    addi r6, r3, lbl_8032FA38@l
    lfs f1, 0x64(r1)
    lwz r5, 0x0(r6)
    addi r3, r1, 0x50
    lwz r4, 0x4(r6)
    lwz r0, 0x8(r6)
    stw r5, 0x50(r1)
    stw r4, 0x54(r1)
    stw r0, 0x58(r1)
    lfs f0, 0xa0(r30)
    fsubs f0, f2, f0
    stfs f0, 0x50(r1)
    lfs f0, 0xa8(r30)
    fsubs f0, f1, f0
    stfs f0, 0x58(r1)
    bl Vec3_HorizontalMagnitude
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne ShellItem_TickActive_L_800F546C
    lfs f0, lbl_806D616C(r2)
    b ShellItem_TickActive_L_800F5470
    ShellItem_TickActive_L_800F546C:
    lfs f0, lbl_806D6170(r2)
    ShellItem_TickActive_L_800F5470:
    fcmpo cr0, f1, f0
    bge ShellItem_TickActive_L_800F547C
    fmuls f30, f31, f1
    ShellItem_TickActive_L_800F547C:
    fmr f1, f30
    addi r3, r30, 0xb8
    mr r4, r3
    bl Vec3_ScaleXZ
    ShellItem_TickActive_L_800F548C:
    lfs f1, lbl_806D612C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq ShellItem_TickActive_L_800F5560
    bge ShellItem_TickActive_L_800F54C0
    cmpwi r28, 0x1
    beq ShellItem_TickActive_L_800F54D0
    bge ShellItem_TickActive_L_800F54F8
    b ShellItem_TickActive_L_800F5640
    ShellItem_TickActive_L_800F54C0:
    cmpwi r28, 0x5
    beq ShellItem_TickActive_L_800F5634
    bge ShellItem_TickActive_L_800F5640
    b ShellItem_TickActive_L_800F55EC
    ShellItem_TickActive_L_800F54D0:
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
    ShellItem_TickActive_L_800F54F8:
    cmpwi r28, 0x2
    bne ShellItem_TickActive_L_800F5514
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    ShellItem_TickActive_L_800F5514:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    cmpwi r28, 0x1
    stb r0, 0x8d(r30)
    bne ShellItem_TickActive_L_800F5544
    li r0, 0x1
    stb r0, 0x0(r31)
    b ShellItem_TickActive_L_800F5548
    ShellItem_TickActive_L_800F5544:
    stb r0, 0x0(r31)
    ShellItem_TickActive_L_800F5548:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc8(r30)
    stb r0, 0xc9(r30)
    stb r0, 0xcb(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5560:
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
    b ShellItem_TickActive_L_800F5640
    ShellItem_TickActive_L_800F55EC:
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
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5634:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    ShellItem_TickActive_L_800F5640:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne ShellItem_TickActive_L_800F5658
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    ShellItem_TickActive_L_800F5658:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne ShellItem_TickActive_L_800F5710
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    stb r4, 0x8d(r30)
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne ShellItem_TickActive_L_800F56F8
    addi r3, r30, 0xb8
    addi r5, r30, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D612C(r2)
    addi r4, r1, 0x14
    lfs f1, lbl_806D6138(r2)
    li r3, 0xcb
    stfs f0, 0xbc(r30)
    li r5, 0x0
    lfs f0, 0xb8(r30)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r30)
    lfs f0, 0xc0(r30)
    fmuls f0, f0, f1
    stfs f0, 0xc0(r30)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    bl SoundMgr_PlaySE_Positional
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x4
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F56F8:
    li r3, 0x2
    li r0, 0x6
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5710:
    mr r3, r30
    addi r4, r1, 0x44
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq ShellItem_TickActive_L_800F5794
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    lfs f1, lbl_806D6138(r2)
    stb r0, 0x8d(r30)
    mr r3, r30
    lfs f2, lbl_806D612C(r2)
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
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    li r4, 0x2
    li r3, 0x0
    li r0, 0x7
    stb r4, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F5794:
    lfs f1, lbl_806D6174(r2)
    mr r3, r30
    lfs f2, lbl_806D6150(r2)
    addi r4, r31, 0x14
    bl Item_AdvanceProjectileSimple
    cmpwi r3, 0x0
    bne ShellItem_TickActive_L_800F57DC
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x9
    stb r4, 0x3c(r30)
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b ShellItem_TickActive_L_800F580C
    ShellItem_TickActive_L_800F57DC:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne ShellItem_TickActive_L_800F580C
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x5
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    ShellItem_TickActive_L_800F580C:
    psq_l f31, 0x98(r1), 0, 0
    lfd f31, 0x90(r1)
    psq_l f30, 0x88(r1), 0, 0
    lfd f30, 0x80(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    lwz r29, 0x74(r1)
    lwz r0, 0xa4(r1)
    lwz r28, 0x70(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

/* === extracted from auto_ShellItem_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_OrbitAnchorKart();
extern void ShellItem_TickActive();
extern void ShellItem_TickHitResolve();
extern void ShellItem_TickReboundOrCarry();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform();
extern void Vec3_Add_DestFirst();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D6128;
extern unsigned int lbl_806D612C;
extern unsigned int lbl_806D6130;
extern unsigned int lbl_806D6134;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_80421760[];

/* --- function index (1 fns, .text 0x800F583C..0x800F5B7C) ---
 * [  0] 0x800F583C size:0x340   global ShellItem_Update
 */

/* --- forward decls --- */
asm void ShellItem_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ShellItem_Update[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ShellItem_Update = {
    (void *)&ShellItem_Update, 0x00000340, (void *)extab_ShellItem_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ShellItem_Update(void) { /* 0x800F583C size:0x340 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq ShellItem_Update_L_800F5908
    bge ShellItem_Update_L_800F587C
    cmpwi r0, 0x0
    beq ShellItem_Update_L_800F5888
    bge ShellItem_Update_L_800F58F8
    b ShellItem_Update_L_800F5AC0
    ShellItem_Update_L_800F587C:
    cmpwi r0, 0x4
    bge ShellItem_Update_L_800F5AC0
    b ShellItem_Update_L_800F5AA4
    ShellItem_Update_L_800F5888:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x48
    beq ShellItem_Update_L_800F58C0
    bge ShellItem_Update_L_800F58A4
    cmpwi r0, 0x47
    bge ShellItem_Update_L_800F58B0
    b ShellItem_Update_L_800F58DC
    ShellItem_Update_L_800F58A4:
    cmpwi r0, 0x4a
    bge ShellItem_Update_L_800F58DC
    b ShellItem_Update_L_800F58D0
    ShellItem_Update_L_800F58B0:
    addi r3, r30, 0x14
    li r4, 0x4a
    bl SpriteSlot_InitNonLoop
    b ShellItem_Update_L_800F58DC
    ShellItem_Update_L_800F58C0:
    addi r3, r30, 0x14
    li r4, 0x4b
    bl SpriteSlot_InitNonLoop
    b ShellItem_Update_L_800F58DC
    ShellItem_Update_L_800F58D0:
    addi r3, r30, 0x14
    li r4, 0x17
    bl SpriteSlot_InitNonLoop
    ShellItem_Update_L_800F58DC:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0x8c(r30)
    li r0, 0x1
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    ShellItem_Update_L_800F58F8:
    mr r3, r30
    mr r4, r31
    bl ShellItem_TickActive
    b ShellItem_Update_L_800F5AC0
    ShellItem_Update_L_800F5908:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt ShellItem_Update_L_800F5AC0
    lis r4, jumptable_80421760@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_80421760@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    mr r4, r31
    bl ShellItem_TickReboundOrCarry
    b ShellItem_Update_L_800F5AC0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ShellItem_Update_L_800F5994
    bge ShellItem_Update_L_800F5994
    cmpwi r0, 0x0
    bge ShellItem_Update_L_800F595C
    b ShellItem_Update_L_800F5994
    ShellItem_Update_L_800F595C:
    lfs f1, lbl_806D6128(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D6128(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    ShellItem_Update_L_800F5994:
    lfs f2, lbl_806D6134(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq ShellItem_Update_L_800F5AC0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b ShellItem_Update_L_800F5AC0
    mr r4, r31
    bl ShellItem_TickHitResolve
    b ShellItem_Update_L_800F5AC0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ShellItem_Update_L_800F5A3C
    bge ShellItem_Update_L_800F5A3C
    cmpwi r0, 0x0
    bge ShellItem_Update_L_800F59F8
    b ShellItem_Update_L_800F5A3C
    ShellItem_Update_L_800F59F8:
    lfs f1, lbl_806D6128(r2)
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
    ShellItem_Update_L_800F5A3C:
    lfs f1, lbl_806D612C(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, lbl_806D6130(r2)
    mr r3, r30
    lwz r5, 0x4(r31)
    addi r4, r31, 0x34
    fmr f2, f1
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq ShellItem_Update_L_800F5AC0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b ShellItem_Update_L_800F5AC0
    mr r4, r31
    bl ShellItem_TickHitResolve
    b ShellItem_Update_L_800F5AC0
    mr r4, r31
    bl ShellItem_TickHitResolve
    b ShellItem_Update_L_800F5AC0
    mr r4, r31
    bl ShellItem_TickHitResolve
    b ShellItem_Update_L_800F5AC0
    ShellItem_Update_L_800F5AA4:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x49
    beq ShellItem_Update_L_800F5AB4
    bl ItemObject_DecrementCategoryBudget
    ShellItem_Update_L_800F5AB4:
    mr r3, r30
    bl SpriteSlot_Container_Free
    b ShellItem_Update_L_800F5B64
    ShellItem_Update_L_800F5AC0:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r6, 0xac(r30)
    addi r3, r30, 0x14
    lwz r0, 0xb0(r30)
    addi r4, r1, 0x14
    addi r5, r1, 0x8
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xb4(r30)
    stw r0, 0x10(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    lfs f1, 0xc4(r30)
    bl SpriteSlot_SetTransform
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq ShellItem_Update_L_800F5B28
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    ShellItem_Update_L_800F5B28:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq ShellItem_Update_L_800F5B3C
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    ShellItem_Update_L_800F5B3C:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq ShellItem_Update_L_800F5B50
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    ShellItem_Update_L_800F5B50:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq ShellItem_Update_L_800F5B64
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    ShellItem_Update_L_800F5B64:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
