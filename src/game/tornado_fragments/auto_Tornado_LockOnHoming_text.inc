/* === extracted from auto_Tornado_LockOnHoming_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_ItemHitFx_Spawn();
extern void DrawEffect_ItemHitOriented_Spawn();
extern void GetSpawnPosition();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHit_Dispatch();
extern void ItemObject_AllocFromPool();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceFallingDrop();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D6260;
extern unsigned int lbl_806D6264;
extern unsigned int lbl_806D6274;
extern unsigned int lbl_806D627C;
extern unsigned int lbl_806D6280;
extern unsigned int lbl_806D6284;
extern unsigned int lbl_806D6288;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern void Tornado_HomingChildTick();

/* --- function index (1 fns, .text 0x800F9148..0x800F9618) ---
 * [  0] 0x800F9148 size:0x4D0   global Tornado_LockOnHomingTick
 */

/* --- forward decls --- */
asm void Tornado_LockOnHomingTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tornado_LockOnHomingTick[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tornado_LockOnHomingTick = {
    (void *)&Tornado_LockOnHomingTick, 0x000004D0, (void *)extab_Tornado_LockOnHomingTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Tornado_LockOnHomingTick(void) { /* 0x800F9148 size:0x4D0 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stw r31, 0x5c(r1)
    mr r31, r4
    stw r30, 0x58(r1)
    mr r30, r3
    stw r29, 0x54(r1)
    lbz r3, 0xc9(r3)
    extsb r0, r3
    cmpwi r0, 0x1
    beq Tornado_LockOnHomingTick_L_800F9198
    bge Tornado_LockOnHomingTick_L_800F95FC
    cmpwi r0, 0x0
    bge Tornado_LockOnHomingTick_L_800F9188
    b Tornado_LockOnHomingTick_L_800F95FC
    Tornado_LockOnHomingTick_L_800F9188:
    addi r3, r3, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    Tornado_LockOnHomingTick_L_800F9198:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Tornado_LockOnHomingTick_L_800F9210
    bge Tornado_LockOnHomingTick_L_800F91B8
    cmpwi r0, 0x0
    bge Tornado_LockOnHomingTick_L_800F91C4
    b Tornado_LockOnHomingTick_L_800F926C
    Tornado_LockOnHomingTick_L_800F91B8:
    cmpwi r0, 0x3
    bge Tornado_LockOnHomingTick_L_800F926C
    b Tornado_LockOnHomingTick_L_800F9224
    Tornado_LockOnHomingTick_L_800F91C4:
    mr r3, r30
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    li r3, 0x12c
    stb r0, 0x8d(r30)
    li r0, 0x0
    lfs f1, lbl_806D6264(r2)
    stw r3, 0x4(r31)
    lfs f0, lbl_806D627C(r2)
    stw r0, 0x8(r31)
    stw r0, 0xc(r31)
    stfs f1, 0x2c(r30)
    stfs f0, 0xc4(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    Tornado_LockOnHomingTick_L_800F9210:
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D6274(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    b Tornado_LockOnHomingTick_L_800F926C
    Tornado_LockOnHomingTick_L_800F9224:
    lfs f1, lbl_806D6260(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne Tornado_LockOnHomingTick_L_800F9244
    lfs f2, lbl_806D6260(r2)
    b Tornado_LockOnHomingTick_L_800F9248
    Tornado_LockOnHomingTick_L_800F9244:
    lfs f2, lbl_806D6280(r2)
    Tornado_LockOnHomingTick_L_800F9248:
    cmpwi r0, 0x0
    mr r3, r30
    bne Tornado_LockOnHomingTick_L_800F925C
    lfs f1, lbl_806D6284(r2)
    b Tornado_LockOnHomingTick_L_800F9260
    Tornado_LockOnHomingTick_L_800F925C:
    lfs f1, lbl_806D6288(r2)
    Tornado_LockOnHomingTick_L_800F9260:
    bl Item_AccelClampVelocity
    addi r3, r30, 0xa0
    bl fn_801B129C
    Tornado_LockOnHomingTick_L_800F926C:
    lfs f2, 0x2c(r30)
    lfs f0, lbl_806D627C(r2)
    lfs f1, lbl_806D6260(r2)
    fadds f0, f2, f0
    stfs f0, 0x2c(r30)
    lfs f0, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge Tornado_LockOnHomingTick_L_800F9290
    stfs f1, 0x2c(r30)
    Tornado_LockOnHomingTick_L_800F9290:
    mr r3, r30
    bl ItemCollision_Check
    cmpwi r3, 0x3
    beq Tornado_LockOnHomingTick_L_800F9334
    bge Tornado_LockOnHomingTick_L_800F92B4
    cmpwi r3, 0x1
    beq Tornado_LockOnHomingTick_L_800F92C4
    bge Tornado_LockOnHomingTick_L_800F93F4
    b Tornado_LockOnHomingTick_L_800F9414
    Tornado_LockOnHomingTick_L_800F92B4:
    cmpwi r3, 0x5
    beq Tornado_LockOnHomingTick_L_800F9408
    bge Tornado_LockOnHomingTick_L_800F9414
    b Tornado_LockOnHomingTick_L_800F93AC
    Tornado_LockOnHomingTick_L_800F92C4:
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
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    lis r3, Tornado_HomingChildTick@ha
    addi r3, r3, Tornado_HomingChildTick@l
    bl ItemObject_AllocFromPool
    mr. r29, r3
    beq Tornado_LockOnHomingTick_L_800F9324
    stw r30, 0x148(r29)
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x184(r29)
    Tornado_LockOnHomingTick_L_800F9324:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    b Tornado_LockOnHomingTick_L_800F9414
    Tornado_LockOnHomingTick_L_800F9334:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    lwz r4, 0xb8(r30)
    mr r3, r30
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
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0xc(r31)
    b Tornado_LockOnHomingTick_L_800F9414
    Tornado_LockOnHomingTick_L_800F93AC:
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
    b Tornado_LockOnHomingTick_L_800F95FC
    Tornado_LockOnHomingTick_L_800F93F4:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    Tornado_LockOnHomingTick_L_800F9408:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    Tornado_LockOnHomingTick_L_800F9414:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne Tornado_LockOnHomingTick_L_800F942C
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    Tornado_LockOnHomingTick_L_800F942C:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne Tornado_LockOnHomingTick_L_800F9460
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x4
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b Tornado_LockOnHomingTick_L_800F95FC
    Tornado_LockOnHomingTick_L_800F9460:
    mr r3, r30
    li r4, 0x0
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq Tornado_LockOnHomingTick_L_800F94B8
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6264(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x7
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b Tornado_LockOnHomingTick_L_800F95FC
    Tornado_LockOnHomingTick_L_800F94B8:
    lfs f1, lbl_806D6264(r2)
    mr r3, r30
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq Tornado_LockOnHomingTick_L_800F958C
    lwz r0, 0xc(r1)
    cmpwi r0, 0x0
    bne Tornado_LockOnHomingTick_L_800F94EC
    lbz r0, 0xca(r30)
    cmpwi r0, 0x2
    bne Tornado_LockOnHomingTick_L_800F95CC
    Tornado_LockOnHomingTick_L_800F94EC:
    lfs f1, 0x8(r1)
    lfs f0, lbl_806D6264(r2)
    stfs f1, 0xa4(r30)
    stfs f0, 0xbc(r30)
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne Tornado_LockOnHomingTick_L_800F9574
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x28
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x1c
    li r5, 0x3
    stw r6, 0x1c(r1)
    stw r0, 0x20(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x24(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x28(r1)
    stw r0, 0x2c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x30(r1)
    bl DrawEffect_ItemHitOriented_Spawn
    lwz r5, 0xa0(r30)
    mr r4, r30
    lwz r0, 0xa4(r30)
    addi r3, r1, 0x10
    stw r5, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x18(r1)
    bl DrawEffect_ItemHitFx_Spawn
    li r0, 0x3
    stw r0, 0x8(r31)
    Tornado_LockOnHomingTick_L_800F9574:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x1
    bne Tornado_LockOnHomingTick_L_800F95CC
    li r0, 0x2
    stb r0, 0xca(r30)
    b Tornado_LockOnHomingTick_L_800F95CC
    Tornado_LockOnHomingTick_L_800F958C:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    lfs f1, lbl_806D6264(r2)
    li r0, 0x0
    stb r0, 0x8d(r30)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x9
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b Tornado_LockOnHomingTick_L_800F95FC
    Tornado_LockOnHomingTick_L_800F95CC:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne Tornado_LockOnHomingTick_L_800F95FC
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r30)
    li r0, 0x5
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    Tornado_LockOnHomingTick_L_800F95FC:
    lwz r0, 0x64(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    lwz r29, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

