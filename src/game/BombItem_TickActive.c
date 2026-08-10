/* === extracted from auto_BombItem_TickActive_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_ItemHitBurst_Spawn();
extern void DrawEffect_SpawnDirect();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHitRegistry_AddEntry();
extern void ItemHitRegistry_RemoveEntry();
extern void ItemHit_Dispatch();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AdvanceFallingDrop();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern void Item_RenderHandheldByCharacter();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void Vec3_ToYaw();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D61D0;
extern unsigned int lbl_806D61D4;
extern unsigned int lbl_806D61E4;
extern unsigned int lbl_806D61E8;
extern unsigned int lbl_806D61EC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int Effect_TwoChild_Res8F_Update[];
extern unsigned int lbl_8032FA48[];
extern unsigned int lbl_8032FA54[];

/* --- function index (1 fns, .text 0x800F6F54..0x800F7584) ---
 * [  0] 0x800F6F54 size:0x630   global BombItem_TickActive
 */

/* --- forward decls --- */
asm void BombItem_TickActive(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BombItem_TickActive[8] = {
    0x20, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BombItem_TickActive = {
    (void *)&BombItem_TickActive, 0x00000630, (void *)extab_BombItem_TickActive
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BombItem_TickActive(void) { /* 0x800F6F54 size:0x630 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stw r31, 0x7c(r1)
    mr r31, r4
    stw r30, 0x78(r1)
    mr r30, r3
    stw r29, 0x74(r1)
    stw r28, 0x70(r1)
    lbz r4, 0xc9(r3)
    extsb r0, r4
    cmpwi r0, 0x1
    beq BombItem_TickActive_L_800F6FB4
    bge BombItem_TickActive_L_800F6F98
    cmpwi r0, 0x0
    bge BombItem_TickActive_L_800F6FA4
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F6F98:
    cmpwi r0, 0x3
    bge BombItem_TickActive_L_800F7564
    b BombItem_TickActive_L_800F7108
    BombItem_TickActive_L_800F6FA4:
    addi r3, r4, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    BombItem_TickActive_L_800F6FB4:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_TickActive_L_800F700C
    bge BombItem_TickActive_L_800F7564
    cmpwi r0, 0x0
    bge BombItem_TickActive_L_800F6FD4
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F6FD4:
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D61D0(r2)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    li r0, 0x1
    lfs f0, lbl_806D61D0(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    BombItem_TickActive_L_800F700C:
    lis r4, lbl_8032FA54@ha
    lwzu r12, lbl_8032FA54@l(r4)
    lis r3, lbl_8032FA48@ha
    lfs f1, lbl_806D61E8(r2)
    addi r9, r3, lbl_8032FA48@l
    lwz r11, 0x4(r4)
    lwz r10, 0x8(r4)
    mr r3, r30
    lwz r8, 0x0(r9)
    addi r4, r1, 0x58
    lwz r7, 0x4(r9)
    addi r5, r1, 0x4c
    lwz r0, 0x8(r9)
    li r6, 0x1
    stw r12, 0x4c(r1)
    stw r11, 0x50(r1)
    stw r10, 0x54(r1)
    stw r8, 0x58(r1)
    stw r7, 0x5c(r1)
    stw r0, 0x60(r1)
    bl Item_RenderHandheldByCharacter
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq BombItem_TickActive_L_800F707C
    li r0, 0x0
    stb r0, 0x28(r30)
    b BombItem_TickActive_L_800F7084
    BombItem_TickActive_L_800F707C:
    li r0, 0x1
    stb r0, 0x28(r30)
    BombItem_TickActive_L_800F7084:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BombItem_TickActive_L_800F70EC
    bge BombItem_TickActive_L_800F7564
    cmpwi r0, 0x1
    bge BombItem_TickActive_L_800F70A4
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F70A4:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    stb r0, 0xa0(r31)
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D61E8(r2)
    mr r3, r30
    lfs f2, lbl_806D61D0(r2)
    li r4, 0x0
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F70EC:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F7108:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_TickActive_L_800F718C
    bge BombItem_TickActive_L_800F71AC
    cmpwi r0, 0x0
    bge BombItem_TickActive_L_800F712C
    b BombItem_TickActive_L_800F71AC
    b BombItem_TickActive_L_800F71AC
    BombItem_TickActive_L_800F712C:
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    lfs f1, lbl_806D61D0(r2)
    stb r0, 0x8d(r30)
    addi r3, r30, 0x14
    li r4, 0x1
    stb r0, 0x3c(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lis r3, Effect_TwoChild_Res8F_Update@ha
    addi r3, r3, Effect_TwoChild_Res8F_Update@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r31)
    li r4, 0x384
    li r0, 0x0
    mr r3, r30
    stw r4, 0x4(r31)
    stw r0, 0x8(r31)
    lbz r4, 0xca(r30)
    addi r0, r4, 0x1
    stb r0, 0xca(r30)
    bl ItemHitRegistry_AddEntry
    BombItem_TickActive_L_800F718C:
    lfs f1, 0xbc(r30)
    mr r3, r30
    lfs f0, lbl_806D61E4(r2)
    addi r4, r30, 0xb0
    li r5, 0x1
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    bl Item_HomingScanAndSteer
    BombItem_TickActive_L_800F71AC:
    lfs f1, lbl_806D61D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq BombItem_TickActive_L_800F7234
    bge BombItem_TickActive_L_800F71E0
    cmpwi r28, 0x1
    beq BombItem_TickActive_L_800F71F0
    bge BombItem_TickActive_L_800F7218
    b BombItem_TickActive_L_800F7370
    BombItem_TickActive_L_800F71E0:
    cmpwi r28, 0x5
    beq BombItem_TickActive_L_800F7364
    bge BombItem_TickActive_L_800F7370
    b BombItem_TickActive_L_800F731C
    BombItem_TickActive_L_800F71F0:
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
    BombItem_TickActive_L_800F7218:
    cmpwi r28, 0x2
    bne BombItem_TickActive_L_800F7234
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    BombItem_TickActive_L_800F7234:
    cmpwi r28, 0x3
    bne BombItem_TickActive_L_800F7250
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    BombItem_TickActive_L_800F7250:
    cmpwi r28, 0x3
    bne BombItem_TickActive_L_800F72DC
    lbz r0, 0xca(r30)
    cmpwi r0, 0x1
    bne BombItem_TickActive_L_800F72DC
    li r0, 0x0
    mr r3, r30
    stw r0, 0x7c(r31)
    lwz r4, 0xb8(r30)
    lwz r0, 0xbc(r30)
    stw r4, 0x34(r1)
    stw r0, 0x38(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x3c(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0x40(r1)
    stw r0, 0x44(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x48(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0x40
    addi r6, r1, 0x34
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0x8(r31)
    b BombItem_TickActive_L_800F7370
    BombItem_TickActive_L_800F72DC:
    cmpwi r28, 0x1
    bne BombItem_TickActive_L_800F72F8
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    BombItem_TickActive_L_800F72F8:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r3, 0x0
    li r0, 0x2
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r3, 0xcb(r30)
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F731C:
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
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F7364:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    BombItem_TickActive_L_800F7370:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne BombItem_TickActive_L_800F7388
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    BombItem_TickActive_L_800F7388:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne BombItem_TickActive_L_800F73E0
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    stb r4, 0x8d(r30)
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne BombItem_TickActive_L_800F73C8
    li r3, 0x2
    li r0, 0x4
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F73C8:
    li r3, 0x2
    li r0, 0x6
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F73E0:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x1
    bne BombItem_TickActive_L_800F7510
    mr r3, r30
    addi r4, r1, 0x64
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq BombItem_TickActive_L_800F7444
    lwz r6, 0x64(r1)
    mr r3, r30
    lwz r7, 0x68(r1)
    addi r4, r1, 0x28
    lwz r0, 0x6c(r1)
    li r5, 0xcb
    stw r6, 0x28(r1)
    li r6, 0x2
    lfs f1, lbl_806D61EC(r2)
    stw r7, 0x2c(r1)
    lfs f2, lbl_806D61D0(r2)
    stw r0, 0x30(r1)
    bl Item_BounceOffWall
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    BombItem_TickActive_L_800F7444:
    lfs f1, lbl_806D61D0(r2)
    mr r3, r30
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq BombItem_TickActive_L_800F74E8
    lwz r0, 0xc(r1)
    cmpwi r0, 0x0
    beq BombItem_TickActive_L_800F7510
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x1c
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x10
    li r5, 0x2
    stw r6, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x18(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x1c(r1)
    stw r0, 0x20(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x24(r1)
    bl DrawEffect_ItemHitBurst_Spawn
    lfs f1, lbl_806D61D0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lfs f1, lbl_806D61D0(r2)
    addi r3, r30, 0x14
    li r4, 0x2
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lbz r0, 0xca(r30)
    cmpwi r0, 0x1
    bne BombItem_TickActive_L_800F7510
    li r0, 0x2
    stb r0, 0xca(r30)
    b BombItem_TickActive_L_800F7510
    BombItem_TickActive_L_800F74E8:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x9
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b BombItem_TickActive_L_800F7564
    BombItem_TickActive_L_800F7510:
    lwz r4, 0x4(r31)
    mr r3, r30
    li r5, 0x0
    bl ItemHitRegistry_RemoveEntry
    clrlwi. r0, r3, 24
    beq BombItem_TickActive_L_800F7564
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq BombItem_TickActive_L_800F754C
    li r0, 0x1
    stb r0, 0xc9(r3)
    BombItem_TickActive_L_800F754C:
    li r0, 0x0
    mr r3, r30
    stw r0, 0x4c(r31)
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    BombItem_TickActive_L_800F7564:
    lwz r0, 0x84(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    lwz r29, 0x74(r1)
    lwz r28, 0x70(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}
