/*
 * PowItem @ 0x800F5B7C..0x800F6F54 (unit-claim #63).
 *
 * POW-family item unit: PowItem_TickHitResolve / PowItem_TickActive /
 * PowItem_Update. ItemObject_Partial layout is accessed by raw offsets
 * (no committed struct header yet); see Ghidra bmp_output plate comments.
 */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

/* --- extern decls: callees referenced from C bodies --- */
extern signed char ItemObject_GetGroundTypeAt(float *pos, float *outGroundY, int flag);
extern float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(float *out, float *mtx);
extern void Vec3_Subtract_DestFirst(float *dst, float *a, float *b);
extern void Vec3_Add_DestFirst(float *dst, float *a, float *b);
extern void Vec3_Copy(float *dst, float *src);
extern void GetSpawnPosition(float x, float y, float z, float *out);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(void *item, float scalar);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern int Item_AdvanceTetherToJoint13(float anchor, float k2, float k3, void *self, float *state);
extern int Item_OrbitAnchorKart(float k1, float k2, void *self, float *offset, int timer);
extern void ItemObject_DecrementCategoryBudget(void *self);
extern void SpriteSlot_Container_Free(void *self);
extern void Matrix4_Identity(float *mtx);
extern void Mtx44_Scale_Uniform(float scale, float *mtx, float *dst);
extern void Matrix4_PreMultiplyRotZ(float angle, float *mtx, float *dst);
extern void Matrix4_PreMultiplyRotX(float angle, float *mtx, float *dst);
extern void Matrix4_PreMultiplyRotY(float angle, float *mtx, float *dst);
extern void Mtx44_Translate(float *mtx, float *dst, float *pos);
extern void DbgScene_CopyMatrix3x4Transpose(float *dst, float *src);

/* --- extern decls: callees referenced only from the asm_fn body --- */
extern void AngleStepForward_OrSnap();
extern void DrawEffect_Free();
extern void DrawEffect_ItemHitOriented_Spawn();
extern void DrawEffect_SpawnDirect();
extern void FAbs_FloatAsDouble();
extern void GabyouItem_BuildLocalTransformFromHandJoint();
extern void ItemAlias_HitRemapLookup();
extern void ItemCollision_Check();
extern void ItemHitRegistry_AddEntry();
extern void ItemHitRegistry_RemoveEntry();
extern void ItemHit_Dispatch();
extern void ItemTracker_AcquireLock();
extern void ItemTracker_GetTargetKart();
extern void ItemTracker_ReleaseLock();
extern void ItemTracker_SetTrackPhase();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern void Item_ProbeForwardGroundPitch();
extern void Rand_RangeFloat();
extern void SoundMgr_PlaySE_Positional();
extern void Vec2_RotateX();
extern void Vec2_RotateY();
extern void Vec3_Magnitude_Wrapper();
extern void Vec3_Scale();
extern void Vec3_ScaleXZ();
extern void Vec3_ToYaw();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sdata2 float tuning bank --- */
extern const float lbl_806D6178;
extern const float lbl_806D617C;
extern const float lbl_806D6180;
extern const float lbl_806D6184;
extern const float lbl_806D6188;
extern const float lbl_806D618C;
extern const float lbl_806D6190;
extern const float lbl_806D6194;
extern const float lbl_806D6198;
extern const float lbl_806D619C;
extern const float lbl_806D61A0;
extern const float lbl_806D61A4;
extern const float lbl_806D61A8;
extern const float lbl_806D61AC;
extern const float lbl_806D61B0;
extern const float lbl_806D61B4;
extern const float lbl_806D61B8;
extern const float lbl_806D61BC;
extern const float lbl_806D61C0;
extern const float lbl_806D61C4;
extern const float lbl_806D61C8;
extern const float lbl_806D61CC;

/* --- extern decls: large-data refs (@ha/@l pairs, asm_fn body only) --- */
extern unsigned int EffectVfx4E_TextSplash_Tick[];
extern unsigned int Effect_HitFlash_Update[];

void PowItem_TickHitResolve(char *self, char *sub)
{
    float groundY;
    Vec3 kartTrans;
    Vec3 anchorTrans;
    Vec3 posCopy;
    Vec3 probePos;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        posCopy = *(Vec3 *)(self + 0xa0);
        ItemObject_GetGroundTypeAt((float *)&posCopy, (float *)(sub + 0x14), 0);
        if ((int)*(unsigned char *)(self + 0xcb) != 5) {
            *(int *)(sub + 4) = 10;
        } else {
            *(int *)(sub + 4) = 0;
        }
        if (*(void **)(sub + 0x9c) != 0) {
            Mtx44_GetTranslation_RowMajor((float *)&kartTrans,
                                          KartDriver_GetKartRootMtx(*(void **)(sub + 0x9c)));
            Vec3_Subtract_DestFirst((float *)(sub + 0x34), (float *)(self + 0xa0), (float *)&kartTrans);
            Vec3_Copy((float *)(sub + 0x40), (float *)(self + 0xb8));
            GetSpawnPosition(lbl_806D6178, lbl_806D6178, lbl_806D6178, (float *)(self + 0xb8));
        }
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        break;
    case 1:
        break;
    }
    if (*(unsigned int *)(sub + 4) == 0) {
        *(float *)(self + 0x2c) = *(float *)(self + 0x2c) - lbl_806D61A4;
        if (*(float *)(self + 0x2c) < lbl_806D6178) {
            self[0x28] = 0;
            self[0xc8] = 3;
            self[0xc9] = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(self, lbl_806D6198);
    switch (*(signed char *)(self + 0xcb)) {
    case 5:
        break;
    case 4:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(*(float *)(self + 0xac) - lbl_806D61A0);
        break;
    case 9:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D61A0 + *(float *)(self + 0xac));
        break;
    case 0:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(*(float *)(self + 0xac) - lbl_806D61A0);
        break;
    }
    if (*(void **)(sub + 0x9c) == 0) {
        if ((int)*(unsigned char *)(self + 0xcb) != 5) {
            *(float *)(self + 0xbc) = *(float *)(self + 0xbc) + lbl_806D61A8;
        }
        probePos = *(Vec3 *)(self + 0xa0);
        if (ItemObject_GetGroundTypeAt((float *)&probePos, &groundY, 0) != 0) {
            *(float *)(self + 0xa4) = *(float *)(self + 0xa4) + (groundY - *(float *)(sub + 0x14));
            *(float *)(sub + 0x14) = groundY;
        }
    } else {
        *(float *)(sub + 0x44) = *(float *)(sub + 0x44) + lbl_806D61A8;
        Vec3_Add_DestFirst((float *)(sub + 0x34), (float *)(sub + 0x34), (float *)(sub + 0x40));
        Mtx44_GetTranslation_RowMajor((float *)&anchorTrans,
                                      KartDriver_GetKartRootMtx(*(void **)(sub + 0x9c)));
        Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)&anchorTrans, (float *)(sub + 0x34));
    }
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x9c)) != 0) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}

/* --- forward decls --- */
asm void PowItem_TickActive(char *self, char *sub);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_PowItem_TickActive[8] = {
    0x30, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_PowItem_TickActive = {
    (void *)&PowItem_TickActive, 0x00000DF8, (void *)extab_PowItem_TickActive
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void PowItem_TickActive(char *self, char *sub) { /* 0x800F5E20 size:0xDF8 */
    nofralloc
    stwu r1, -0x110(r1)
    mflr r0
    stw r0, 0x114(r1)
    stfd f31, 0x100(r1)
    psq_st f31, 0x108(r1), 0, 0
    stmw r26, 0xe8(r1)
    mr r30, r3
    mr r31, r4
    lbz r4, 0xc9(r3)
    extsb r0, r4
    cmpwi r0, 0x1
    beq PowItem_TickActive_L_800F5E7C
    bge PowItem_TickActive_L_800F5E60
    cmpwi r0, 0x0
    bge PowItem_TickActive_L_800F5E6C
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F5E60:
    cmpwi r0, 0x3
    bge PowItem_TickActive_L_800F6BFC
    b PowItem_TickActive_L_800F5F78
    PowItem_TickActive_L_800F5E6C:
    addi r3, r4, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    PowItem_TickActive_L_800F5E7C:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq PowItem_TickActive_L_800F5EC0
    bge PowItem_TickActive_L_800F6BFC
    cmpwi r0, 0x0
    bge PowItem_TickActive_L_800F5E9C
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F5E9C:
    li r3, 0x0
    li r0, 0x1
    stb r3, 0x0(r31)
    lfs f0, lbl_806D6178(r2)
    stb r0, 0x28(r30)
    stfs f0, 0x2c(r30)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    PowItem_TickActive_L_800F5EC0:
    lfs f1, lbl_806D61AC(r2)
    mr r3, r30
    lfs f2, lbl_806D61B0(r2)
    li r4, 0x1
    lfs f3, lbl_806D61B4(r2)
    bl GabyouItem_BuildLocalTransformFromHandJoint
    lwz r3, 0x98(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq PowItem_TickActive_L_800F5EF4
    li r0, 0x0
    stb r0, 0x28(r30)
    b PowItem_TickActive_L_800F5EFC
    PowItem_TickActive_L_800F5EF4:
    li r0, 0x1
    stb r0, 0x28(r30)
    PowItem_TickActive_L_800F5EFC:
    lbz r0, 0xa0(r31)
    extsb r0, r0
    cmpwi r0, 0x2
    beq PowItem_TickActive_L_800F5F5C
    bge PowItem_TickActive_L_800F6BFC
    cmpwi r0, 0x1
    bge PowItem_TickActive_L_800F5F1C
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F5F1C:
    li r5, 0x1
    li r0, 0x0
    stb r5, 0x28(r30)
    mr r3, r30
    lfs f1, lbl_806D617C(r2)
    li r4, 0x0
    stb r0, 0xa0(r31)
    lfs f2, lbl_806D6178(r2)
    stb r5, 0x0(r31)
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r30)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F5F5C:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r31)
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F5F78:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq PowItem_TickActive_L_800F5FE0
    bge PowItem_TickActive_L_800F6014
    cmpwi r0, 0x0
    bge PowItem_TickActive_L_800F5F9C
    b PowItem_TickActive_L_800F6014
    b PowItem_TickActive_L_800F6014
    PowItem_TickActive_L_800F5F9C:
    bl ItemTracker_AcquireLock
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r5, 0x1
    li r4, 0x384
    stb r5, 0x8d(r30)
    li r0, 0x0
    mr r3, r30
    stb r5, 0x3c(r30)
    stw r4, 0x4(r31)
    stw r0, 0x8(r31)
    stw r0, 0xc(r31)
    lbz r4, 0xca(r30)
    addi r0, r4, 0x1
    stb r0, 0xca(r30)
    bl ItemHitRegistry_AddEntry
    PowItem_TickActive_L_800F5FE0:
    lfs f2, 0xbc(r30)
    lfs f0, lbl_806D61A8(r2)
    lfs f1, lbl_806D61B8(r2)
    fadds f0, f2, f0
    stfs f0, 0xbc(r30)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    mr r3, r30
    addi r4, r30, 0xb0
    li r5, 0x1
    bl Item_HomingScanAndSteer
    PowItem_TickActive_L_800F6014:
    lfs f1, lbl_806D6198(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    mr r3, r30
    bl ItemCollision_Check
    mr r29, r3
    cmpwi r29, 0x3
    beq PowItem_TickActive_L_800F609C
    bge PowItem_TickActive_L_800F6048
    cmpwi r29, 0x1
    beq PowItem_TickActive_L_800F6058
    bge PowItem_TickActive_L_800F6080
    b PowItem_TickActive_L_800F6358
    PowItem_TickActive_L_800F6048:
    cmpwi r29, 0x5
    beq PowItem_TickActive_L_800F634C
    bge PowItem_TickActive_L_800F6358
    b PowItem_TickActive_L_800F62D0
    PowItem_TickActive_L_800F6058:
    lwz r3, 0x8(r30)
    bl ItemAlias_HitRemapLookup
    extsh r28, r3
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    mr r5, r28
    li r6, 0x0
    bl fn_801B1D5C
    PowItem_TickActive_L_800F6080:
    cmpwi r29, 0x2
    bne PowItem_TickActive_L_800F609C
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    PowItem_TickActive_L_800F609C:
    cmpwi r29, 0x3
    bne PowItem_TickActive_L_800F60B8
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    PowItem_TickActive_L_800F60B8:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x4
    beq PowItem_TickActive_L_800F6144
    cmpwi r29, 0x3
    bne PowItem_TickActive_L_800F6144
    li r0, 0x0
    mr r3, r30
    stw r0, 0x7c(r31)
    lwz r4, 0xb8(r30)
    lwz r0, 0xbc(r30)
    stw r4, 0xb4(r1)
    stw r0, 0xb8(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0xbc(r1)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0xc0(r1)
    stw r0, 0xc4(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0xc8(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r30, 0xb8
    addi r5, r1, 0xc0
    addi r6, r1, 0xb4
    bl Item_ComputeYawRelativeApproach
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    mr r3, r30
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0xc(r31)
    b PowItem_TickActive_L_800F6358
    PowItem_TickActive_L_800F6144:
    cmpwi r29, 0x1
    bne PowItem_TickActive_L_800F6160
    mr r3, r30
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    PowItem_TickActive_L_800F6160:
    mr r3, r30
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r31)
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    lfs f0, lbl_806D61B4(r2)
    stb r0, 0x8d(r30)
    addi r4, r1, 0xa8
    lfs f1, lbl_806D61BC(r2)
    li r3, 0x8e
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
    stw r6, 0xa8(r1)
    stw r0, 0xac(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0xb0(r1)
    bl SoundMgr_PlaySE_Positional
    lwz r26, 0x9c(r31)
    lis r3, Effect_HitFlash_Update@ha
    lwz r4, 0xa0(r30)
    addi r29, r3, Effect_HitFlash_Update@l
    lwz r0, 0xa4(r30)
    li r27, 0x0
    stw r4, 0x9c(r1)
    stw r0, 0xa0(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0xa4(r1)
    PowItem_TickActive_L_800F61F0:
    mr r3, r29
    bl DrawEffect_SpawnDirect
    mr. r28, r3
    beq PowItem_TickActive_L_800F627C
    addi r3, r28, 0x8c
    addi r4, r1, 0x9c
    bl Vec3_Copy
    lfs f1, lbl_806D617C(r2)
    lfs f2, lbl_806D6180(r2)
    bl Rand_RangeFloat
    fmr f3, f1
    lfs f1, lbl_806D6178(r2)
    addi r3, r28, 0xa4
    fmr f2, f1
    bl GetSpawnPosition
    lfs f1, lbl_806D6188(r2)
    lfs f2, lbl_806D618C(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D6184(r2)
    addi r3, r28, 0xa4
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateX
    lfs f1, lbl_806D6190(r2)
    lfs f2, lbl_806D6194(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D6184(r2)
    addi r3, r28, 0xa4
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateY
    li r0, 0x0
    stw r0, 0x10(r28)
    stw r26, 0x11c(r28)
    stw r0, 0xcc(r28)
    PowItem_TickActive_L_800F627C:
    addi r27, r27, 0x1
    cmpwi r27, 0x8
    blt PowItem_TickActive_L_800F61F0
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F629C
    li r0, 0x1
    stb r0, 0xc9(r3)
    PowItem_TickActive_L_800F629C:
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r3, 0x5c(r31)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r31)
    bl SpriteSlot_Container_Free
    li r3, 0x0
    li r0, 0x2
    stw r3, 0x5c(r31)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    stb r3, 0xcb(r30)
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F62D0:
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
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F6314
    li r0, 0x1
    stb r0, 0xc9(r3)
    PowItem_TickActive_L_800F6314:
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r3, 0x5c(r31)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r31)
    bl SpriteSlot_Container_Free
    li r4, 0x0
    li r3, 0x2
    stw r4, 0x5c(r31)
    li r0, 0x3
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F634C:
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    PowItem_TickActive_L_800F6358:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne PowItem_TickActive_L_800F6370
    mr r3, r30
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    PowItem_TickActive_L_800F6370:
    lwz r3, 0x5c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F6478
    bl ItemCollision_Check
    mr r28, r3
    cmpwi r28, 0x3
    beq PowItem_TickActive_L_800F63F4
    bge PowItem_TickActive_L_800F63A0
    cmpwi r28, 0x1
    beq PowItem_TickActive_L_800F63B0
    bge PowItem_TickActive_L_800F63D8
    b PowItem_TickActive_L_800F6460
    PowItem_TickActive_L_800F63A0:
    cmpwi r28, 0x5
    beq PowItem_TickActive_L_800F642C
    bge PowItem_TickActive_L_800F6460
    b PowItem_TickActive_L_800F6410
    PowItem_TickActive_L_800F63B0:
    lwz r3, 0x8(r30)
    bl ItemAlias_HitRemapLookup
    extsh r29, r3
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    mr r5, r29
    li r6, 0x1
    bl fn_801B1D5C
    PowItem_TickActive_L_800F63D8:
    cmpwi r28, 0x2
    bne PowItem_TickActive_L_800F63F4
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B1660
    PowItem_TickActive_L_800F63F4:
    cmpwi r28, 0x3
    bne PowItem_TickActive_L_800F6410
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B158C
    PowItem_TickActive_L_800F6410:
    cmpwi r28, 0x4
    bne PowItem_TickActive_L_800F642C
    mr r3, r30
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r31)
    bl fn_801B14B8
    PowItem_TickActive_L_800F642C:
    cmpwi r28, 0x1
    bne PowItem_TickActive_L_800F6448
    lwz r3, 0x5c(r31)
    addi r5, r30, 0xa0
    li r4, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    PowItem_TickActive_L_800F6448:
    lwz r3, 0x5c(r31)
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    lwz r3, 0x5c(r31)
    li r0, 0x5
    stw r0, 0xf0(r3)
    PowItem_TickActive_L_800F6460:
    lwz r3, 0x5c(r31)
    lwz r0, 0xf0(r3)
    cmplwi r0, 0x0
    bne PowItem_TickActive_L_800F6478
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    PowItem_TickActive_L_800F6478:
    lbz r0, 0x8d(r30)
    cmpwi r0, 0x2
    bne PowItem_TickActive_L_800F66E8
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F64A8
    li r0, 0x1
    stb r0, 0xc9(r3)
    PowItem_TickActive_L_800F64A8:
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r3, 0x5c(r31)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r31)
    bl SpriteSlot_Container_Free
    li r26, 0x0
    stw r26, 0x5c(r31)
    lbz r0, 0x8e(r30)
    cmpwi r0, 0x1
    bne PowItem_TickActive_L_800F6608
    addi r3, r30, 0xb8
    addi r5, r30, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D61B4(r2)
    addi r4, r1, 0x90
    lfs f1, lbl_806D61C0(r2)
    li r3, 0x8e
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
    stw r6, 0x90(r1)
    stw r0, 0x94(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x98(r1)
    bl SoundMgr_PlaySE_Positional
    lwz r4, 0xa0(r30)
    lis r3, Effect_HitFlash_Update@ha
    lwz r0, 0xa4(r30)
    addi r31, r3, Effect_HitFlash_Update@l
    li r26, 0x0
    stw r4, 0x84(r1)
    stw r0, 0x88(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x8c(r1)
    PowItem_TickActive_L_800F6554:
    mr r3, r31
    bl DrawEffect_SpawnDirect
    mr. r29, r3
    beq PowItem_TickActive_L_800F65E0
    addi r3, r29, 0x8c
    addi r4, r1, 0x84
    bl Vec3_Copy
    lfs f1, lbl_806D617C(r2)
    lfs f2, lbl_806D6180(r2)
    bl Rand_RangeFloat
    fmr f3, f1
    lfs f1, lbl_806D6178(r2)
    addi r3, r29, 0xa4
    fmr f2, f1
    bl GetSpawnPosition
    lfs f1, lbl_806D6188(r2)
    lfs f2, lbl_806D618C(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D6184(r2)
    addi r3, r29, 0xa4
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateX
    lfs f1, lbl_806D6190(r2)
    lfs f2, lbl_806D6194(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D6184(r2)
    addi r3, r29, 0xa4
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateY
    li r0, 0x0
    stw r0, 0x10(r29)
    stw r0, 0x11c(r29)
    stw r0, 0xcc(r29)
    PowItem_TickActive_L_800F65E0:
    addi r26, r26, 0x1
    cmpwi r26, 0x8
    blt PowItem_TickActive_L_800F6554
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x4
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F6608:
    lwz r27, 0x9c(r30)
    lis r3, Effect_HitFlash_Update@ha
    lwz r4, 0xa0(r30)
    addi r29, r3, Effect_HitFlash_Update@l
    lwz r0, 0xa4(r30)
    stw r4, 0x78(r1)
    stw r0, 0x7c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x80(r1)
    PowItem_TickActive_L_800F662C:
    mr r3, r29
    bl DrawEffect_SpawnDirect
    mr. r31, r3
    beq PowItem_TickActive_L_800F66C0
    addi r3, r31, 0x8c
    addi r4, r1, 0x78
    bl Vec3_Copy
    cmplwi r27, 0x0
    bne PowItem_TickActive_L_800F66B0
    lfs f1, lbl_806D617C(r2)
    lfs f2, lbl_806D6180(r2)
    bl Rand_RangeFloat
    fmr f3, f1
    lfs f1, lbl_806D6178(r2)
    addi r3, r31, 0xa4
    fmr f2, f1
    bl GetSpawnPosition
    lfs f1, lbl_806D6188(r2)
    lfs f2, lbl_806D618C(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D6184(r2)
    addi r3, r31, 0xa4
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateX
    lfs f1, lbl_806D6190(r2)
    lfs f2, lbl_806D6194(r2)
    bl Rand_RangeFloat
    lfs f0, lbl_806D6184(r2)
    addi r3, r31, 0xa4
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateY
    PowItem_TickActive_L_800F66B0:
    li r0, 0x0
    stw r0, 0x10(r31)
    stw r0, 0x11c(r31)
    stw r27, 0xcc(r31)
    PowItem_TickActive_L_800F66C0:
    addi r26, r26, 0x1
    cmpwi r26, 0x8
    blt PowItem_TickActive_L_800F662C
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r30)
    li r0, 0x6
    stb r3, 0xc9(r30)
    stb r0, 0xcb(r30)
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F66E8:
    lbz r0, 0xca(r30)
    cmpwi r0, 0x4
    beq PowItem_TickActive_L_800F674C
    mr r3, r30
    addi r4, r1, 0xd8
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq PowItem_TickActive_L_800F674C
    lwz r6, 0xd8(r1)
    mr r3, r30
    lwz r7, 0xdc(r1)
    addi r4, r1, 0x6c
    lwz r0, 0xe0(r1)
    li r5, 0x8e
    stw r6, 0x6c(r1)
    li r6, 0x2
    lfs f1, lbl_806D61C0(r2)
    stw r7, 0x70(r1)
    lfs f2, lbl_806D6178(r2)
    stw r0, 0x74(r1)
    bl Item_BounceOffWall
    addi r3, r30, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r30)
    PowItem_TickActive_L_800F674C:
    addi r3, r1, 0xcc
    addi r4, r30, 0xa0
    addi r5, r30, 0xb8
    bl Vec3_Add_DestFirst
    lwz r7, 0xcc(r1)
    addi r3, r1, 0x60
    lwz r6, 0xd0(r1)
    addi r4, r1, 0x8
    lwz r0, 0xd4(r1)
    li r5, 0x0
    stw r7, 0x60(r1)
    stw r6, 0x64(r1)
    stw r0, 0x68(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq PowItem_TickActive_L_800F6AEC
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq PowItem_TickActive_L_800F68CC
    bge PowItem_TickActive_L_800F67AC
    cmpwi r0, 0x1
    bge PowItem_TickActive_L_800F67B8
    b PowItem_TickActive_L_800F6B48
    PowItem_TickActive_L_800F67AC:
    cmpwi r0, 0x4
    bge PowItem_TickActive_L_800F6B48
    b PowItem_TickActive_L_800F69D0
    PowItem_TickActive_L_800F67B8:
    lfs f2, lbl_806D61AC(r2)
    lfs f1, 0xc4(r30)
    lfs f0, 0x8(r1)
    lfs f3, 0xd0(r1)
    fmadds f0, f2, f1, f0
    fcmpo cr0, f3, f0
    bge PowItem_TickActive_L_800F6B48
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x54
    lwz r0, 0xa4(r30)
    li r3, 0x8e
    li r5, 0x0
    stw r6, 0x54(r1)
    stw r0, 0x58(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x5c(r1)
    bl SoundMgr_PlaySE_Positional
    lfs f3, lbl_806D61AC(r2)
    addi r3, r30, 0xb8
    lfs f2, 0xc4(r30)
    mr r4, r3
    lfs f0, 0x8(r1)
    lfs f1, lbl_806D61BC(r2)
    fmadds f0, f3, f2, f0
    stfs f0, 0xa4(r30)
    bl Vec3_ScaleXZ
    lfs f0, lbl_806D6178(r2)
    lis r3, EffectVfx4E_TextSplash_Tick@ha
    addi r3, r3, EffectVfx4E_TextSplash_Tick@l
    stfs f0, 0xbc(r30)
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r31)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F6850
    addi r3, r3, 0x8c
    addi r4, r30, 0xa0
    bl Vec3_Copy
    PowItem_TickActive_L_800F6850:
    lwz r6, 0x5c(r31)
    cmplwi r6, 0x0
    beq PowItem_TickActive_L_800F68C0
    lbz r3, 0xf0(r31)
    li r5, 0x4b
    li r4, 0x9b
    li r0, 0x1
    stb r3, 0x1dc(r6)
    lwz r3, 0x5c(r31)
    stw r5, 0x8(r3)
    lwz r3, 0x5c(r31)
    stb r4, 0x1c(r3)
    lwz r3, 0x5c(r31)
    stb r0, 0x17c(r3)
    lwz r0, 0x94(r31)
    lwz r3, 0x5c(r31)
    stw r0, 0x180(r3)
    lwz r0, 0x98(r31)
    lwz r3, 0x5c(r31)
    stw r0, 0x184(r3)
    lwz r3, 0x5c(r31)
    bl ItemTracker_AcquireLock
    lwz r3, 0x5c(r31)
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    lfs f0, lbl_806D61C4(r2)
    lwz r3, 0x5c(r31)
    stfs f0, 0xc4(r3)
    PowItem_TickActive_L_800F68C0:
    li r0, 0x2
    stb r0, 0xca(r30)
    b PowItem_TickActive_L_800F6B48
    PowItem_TickActive_L_800F68CC:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne PowItem_TickActive_L_800F6920
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x48
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x3c
    li r5, 0x2
    stw r6, 0x3c(r1)
    stw r0, 0x40(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x44(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x48(r1)
    stw r0, 0x4c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x50(r1)
    bl DrawEffect_ItemHitOriented_Spawn
    li r0, 0x3
    stw r0, 0x8(r31)
    PowItem_TickActive_L_800F6920:
    lfs f2, lbl_806D61AC(r2)
    lfs f1, 0xc4(r30)
    lfs f0, 0x8(r1)
    fmadds f0, f2, f1, f0
    stfs f0, 0xa4(r30)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F694C
    addi r3, r3, 0x8c
    addi r4, r30, 0xa0
    bl Vec3_Copy
    PowItem_TickActive_L_800F694C:
    lwz r4, 0xa0(r30)
    addi r3, r1, 0x30
    lwz r0, 0xa4(r30)
    lfs f3, lbl_806D61AC(r2)
    stw r4, 0x30(r1)
    lfs f2, lbl_806D61B4(r2)
    stw r0, 0x34(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x38(r1)
    lfs f0, 0xc4(r30)
    lfs f1, 0xb0(r30)
    fmuls f3, f3, f0
    bl Item_ProbeForwardGroundPitch
    lfs f0, lbl_806D61C8(r2)
    fadds f1, f0, f1
    bl BuildOrientationFromYaw
    fmr f0, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61B8(r2)
    fmr f31, f0
    fmr f2, f31
    bl AngleStepForward_OrSnap
    stfs f1, 0xac(r30)
    lfs f0, 0xac(r30)
    fsubs f1, f0, f31
    bl BuildOrientationFromYaw
    bl FAbs_FloatAsDouble
    lfs f0, lbl_806D6184(r2)
    fcmpo cr0, f1, f0
    bge PowItem_TickActive_L_800F6B48
    li r0, 0x3
    stb r0, 0xca(r30)
    b PowItem_TickActive_L_800F6B48
    PowItem_TickActive_L_800F69D0:
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne PowItem_TickActive_L_800F6A24
    lwz r6, 0xb8(r30)
    addi r3, r1, 0x24
    lwz r0, 0xbc(r30)
    addi r4, r1, 0x18
    li r5, 0x2
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    lwz r0, 0xc0(r30)
    stw r0, 0x20(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x2c(r1)
    bl DrawEffect_ItemHitOriented_Spawn
    li r0, 0x3
    stw r0, 0x8(r31)
    PowItem_TickActive_L_800F6A24:
    lfs f3, lbl_806D61AC(r2)
    addi r3, r1, 0xc
    lfs f1, 0xc4(r30)
    lfs f0, 0x8(r1)
    lfs f2, lbl_806D61B4(r2)
    fmadds f0, f3, f1, f0
    stfs f0, 0xa4(r30)
    lwz r4, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r4, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x14(r1)
    lfs f0, 0xc4(r30)
    lfs f1, 0xb0(r30)
    fmuls f3, f3, f0
    bl Item_ProbeForwardGroundPitch
    lfs f0, lbl_806D61C8(r2)
    fadds f1, f0, f1
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F6A90
    addi r3, r3, 0x8c
    addi r4, r30, 0xa0
    bl Vec3_Copy
    PowItem_TickActive_L_800F6A90:
    addi r3, r30, 0xb8
    bl Vec3_Magnitude_Wrapper
    lfs f0, lbl_806D61CC(r2)
    lfs f2, lbl_806D6178(r2)
    fsubs f31, f1, f0
    fcmpo cr0, f2, f31
    bge PowItem_TickActive_L_800F6AD0
    addi r3, r30, 0xb8
    bl Vec3_Magnitude_Wrapper
    lfs f0, lbl_806D617C(r2)
    addi r3, r30, 0xb8
    mr r4, r3
    fdivs f0, f0, f1
    fmuls f1, f31, f0
    bl Vec3_Scale
    b PowItem_TickActive_L_800F6B48
    PowItem_TickActive_L_800F6AD0:
    fmr f1, f2
    addi r3, r30, 0xb8
    fmr f3, f2
    bl GetSpawnPosition
    li r0, 0x4
    stb r0, 0xca(r30)
    b PowItem_TickActive_L_800F6B48
    PowItem_TickActive_L_800F6AEC:
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F6B10
    li r0, 0x1
    stb r0, 0xc9(r3)
    PowItem_TickActive_L_800F6B10:
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r3, 0x5c(r31)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r31)
    bl SpriteSlot_Container_Free
    li r4, 0x0
    li r3, 0x2
    stw r4, 0x5c(r31)
    li r0, 0x9
    stb r3, 0xc8(r30)
    stb r4, 0xc9(r30)
    stb r0, 0xcb(r30)
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F6B48:
    lwz r4, 0x4(r31)
    mr r3, r30
    li r5, 0x0
    bl ItemHitRegistry_RemoveEntry
    clrlwi. r0, r3, 24
    beq PowItem_TickActive_L_800F6BB4
    mr r3, r30
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    stb r0, 0x8d(r30)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F6B80
    bl DrawEffect_Free
    PowItem_TickActive_L_800F6B80:
    li r0, 0x0
    stw r0, 0x4c(r31)
    lwz r3, 0x5c(r31)
    bl ItemTracker_ReleaseLock
    lwz r3, 0x5c(r31)
    bl SpriteSlot_Container_Free
    li r0, 0x0
    mr r3, r30
    stw r0, 0x5c(r31)
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b PowItem_TickActive_L_800F6BFC
    PowItem_TickActive_L_800F6BB4:
    lwz r4, 0x5c(r31)
    cmplwi r4, 0x0
    beq PowItem_TickActive_L_800F6BFC
    lwz r3, 0xf0(r4)
    cmplwi r3, 0x0
    beq PowItem_TickActive_L_800F6BD4
    subi r0, r3, 0x1
    stw r0, 0xf0(r4)
    PowItem_TickActive_L_800F6BD4:
    lwz r3, 0x5c(r31)
    addi r4, r30, 0xa0
    addi r3, r3, 0xa0
    bl Vec3_Copy
    lwz r3, 0x5c(r31)
    lfs f2, lbl_806D61AC(r2)
    lfs f1, 0xc4(r30)
    lfs f0, 0xa4(r3)
    fnmsubs f0, f2, f1, f0
    stfs f0, 0xa4(r3)
    PowItem_TickActive_L_800F6BFC:
    psq_l f31, 0x108(r1), 0, 0
    lfd f31, 0x100(r1)
    lmw r26, 0xe8(r1)
    lwz r0, 0x114(r1)
    mtlr r0
    addi r1, r1, 0x110
    blr
}


void PowItem_Update(char *self)
{
    Vec3 posCopy;
    float mtx[16];
    char *sub = self + 0xec;
    int code;

    switch (*(signed char *)(self + 0xc8)) {
    case 0:
        sub[0x90] = 1;
        SpriteSlot_InitNonLoop(self + 0x14, 0x4c);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        sub[0] = 1;
        self[0x8c] = 3;
        self[0x8d] = 0;
        self[0xc8] = 1;
        self[0xc9] = 0;
        /* fallthrough */
    case 1:
        PowItem_TickActive(self, sub);
        break;
    case 2:
        switch (*(signed char *)(self + 0xcb)) {
        case 0:
            PowItem_TickHitResolve(self, sub);
            break;
        case 3:
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                GetSpawnPosition(lbl_806D6178, lbl_806D6178, lbl_806D6178, (float *)(self + 0xb8));
                self[0x3c] = 0;
                *(float *)(sub + 0x14) = lbl_806D6178;
                *(float *)(sub + 0x18) = *(float *)(self + 0xc4);
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                break;
            case 1:
                break;
            }
            code = Item_AdvanceTetherToJoint13(*(float *)(sub + 0x18), lbl_806D61A0, lbl_806D61A0,
                                               self, (float *)(sub + 0x14));
            if (code != 0) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            }
            break;
        case 4:
            PowItem_TickHitResolve(self, sub);
            break;
        case 6:
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                GetSpawnPosition(lbl_806D6178, lbl_806D6178, lbl_806D6178, (float *)(self + 0xb8));
                self[0x3c] = 0;
                Vec3_Subtract_DestFirst((float *)(sub + 0x34), (float *)(self + 0xa0),
                                        (float *)(*(int *)(self + 0x9c) + 0xa0));
                *(int *)(sub + 4) = 0x1e;
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                break;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, lbl_806D6198);
            code = Item_OrbitAnchorKart(lbl_806D619C, lbl_806D619C, self, (float *)(sub + 0x34),
                                        *(int *)(sub + 4));
            if (code != 0) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            }
            break;
        case 9:
            PowItem_TickHitResolve(self, sub);
            break;
        case 5:
            PowItem_TickHitResolve(self, sub);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)(self + 0xa0), (float *)(self + 0xb8));
    if (*(unsigned char *)sub != 0) {
        Matrix4_Identity(mtx);
        Mtx44_Scale_Uniform(*(float *)(self + 0xc4), mtx, mtx);
        Matrix4_PreMultiplyRotZ(*(float *)(self + 0xb4), mtx, mtx);
        Matrix4_PreMultiplyRotX(*(float *)(self + 0xac), mtx, mtx);
        Matrix4_PreMultiplyRotY(*(float *)(self + 0xb0), mtx, mtx);
        posCopy = *(Vec3 *)(self + 0xa0);
        Mtx44_Translate(mtx, mtx, (float *)&posCopy);
        DbgScene_CopyMatrix3x4Transpose((float *)(self + 0x48), mtx);
    }
    if (*(unsigned int *)(sub + 4) != 0) {
        *(unsigned int *)(sub + 4) = *(unsigned int *)(sub + 4) - 1;
    }
    if (*(unsigned int *)(sub + 8) != 0) {
        *(unsigned int *)(sub + 8) = *(unsigned int *)(sub + 8) - 1;
    }
    if (*(unsigned int *)(sub + 0xc) != 0) {
        *(unsigned int *)(sub + 0xc) = *(unsigned int *)(sub + 0xc) - 1;
    }
    if (*(unsigned int *)(sub + 0x10) != 0) {
        *(unsigned int *)(sub + 0x10) = *(unsigned int *)(sub + 0x10) - 1;
    }
}
