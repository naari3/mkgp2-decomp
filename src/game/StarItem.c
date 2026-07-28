/* === extracted from auto_StarItem_BoundToVict_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void FAbs_FloatAsDouble();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void Item_DecayVelocityScalar();
extern void Item_SpawnHitBurstParticles();
extern void JointByName_GetMatrix4x4Transposed();
extern void KartDriver_GetJointByIdx();
extern void KartDriver_GetKartRootMtx();
extern void KartFxParam_GetConst1p5();
extern void Mtx44_GetPitchOfPosZ();
extern void Mtx44_GetTranslation_ColMajor();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_GetYawOfPosZ();
extern void Mtx44_Inverse_GaussJordan();
extern void Mtx44_TransformVec3();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();
extern void Vec2_RotateY();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Lerp();
extern void Vec3_Subtract_DestFirst();
extern void Vec3_ToYaw();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D63F8;
extern unsigned int lbl_806D63FC;
extern unsigned int lbl_806D6430;
extern unsigned int lbl_806D6440;
extern unsigned int lbl_806D6444;
extern unsigned int lbl_806D6448;
extern unsigned int lbl_806D644C;
extern unsigned int lbl_806D6450;
extern unsigned int lbl_806D6454;
extern unsigned int lbl_806D6458;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80330374[];
extern unsigned int lbl_80330380[];

/* --- function index (1 fns, .text 0x800FD948..0x800FDF24) ---
 * [  0] 0x800FD948 size:0x5DC   global StarItem_BoundToVictimTick
 */

/* --- forward decls --- */
asm void StarItem_BoundToVictimTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_StarItem_BoundToVictimTick[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_StarItem_BoundToVictimTick = {
    (void *)&StarItem_BoundToVictimTick, 0x000005DC, (void *)extab_StarItem_BoundToVictimTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void StarItem_BoundToVictimTick(void) { /* 0x800FD948 size:0x5DC */
    nofralloc
    stwu r1, -0x180(r1)
    mflr r0
    stw r0, 0x184(r1)
    stfd f31, 0x170(r1)
    psq_st f31, 0x178(r1), 0, 0
    stw r31, 0x16c(r1)
    stw r30, 0x168(r1)
    mr r30, r3
    mr r31, r4
    lbz r0, 0xc9(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_BoundToVictimTick_L_800FD9B0
    bge StarItem_BoundToVictimTick_L_800FD98C
    cmpwi r0, 0x0
    bge StarItem_BoundToVictimTick_L_800FD998
    b StarItem_BoundToVictimTick_L_800FDEE0
    StarItem_BoundToVictimTick_L_800FD98C:
    cmpwi r0, 0x3
    bge StarItem_BoundToVictimTick_L_800FDEE0
    b StarItem_BoundToVictimTick_L_800FDE50
    StarItem_BoundToVictimTick_L_800FD998:
    li r4, 0x0
    stb r4, 0x3c(r30)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    stb r4, 0xca(r30)
    StarItem_BoundToVictimTick_L_800FD9B0:
    lwz r3, 0x9c(r31)
    li r4, 0xf
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r1, 0x11c
    bl Mtx_TransposeToMtx44
    lis r3, lbl_80330374@ha
    addi r5, r3, lbl_80330374@l
    lwz r4, 0x0(r5)
    lwz r3, 0x4(r5)
    lwz r0, 0x8(r5)
    stw r4, 0x50(r1)
    stw r3, 0x54(r1)
    stw r0, 0x58(r1)
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq StarItem_BoundToVictimTick_L_800FDBE0
    bge StarItem_BoundToVictimTick_L_800FDA0C
    cmpwi r0, 0x0
    beq StarItem_BoundToVictimTick_L_800FDA1C
    bge StarItem_BoundToVictimTick_L_800FDAF4
    b StarItem_BoundToVictimTick_L_800FDC9C
    StarItem_BoundToVictimTick_L_800FDA0C:
    cmpwi r0, 0x4
    beq StarItem_BoundToVictimTick_L_800FDC58
    bge StarItem_BoundToVictimTick_L_800FDC9C
    b StarItem_BoundToVictimTick_L_800FDC18
    StarItem_BoundToVictimTick_L_800FDA1C:
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    addi r3, r1, 0xdc
    addi r4, r1, 0x11c
    bl Mtx44_Inverse_GaussJordan
    lwz r6, 0xa0(r30)
    addi r3, r31, 0x34
    lwz r0, 0xa4(r30)
    addi r4, r1, 0xdc
    addi r5, r1, 0x2c
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x34(r1)
    bl Mtx44_TransformVec3
    addi r3, r31, 0x40
    addi r4, r31, 0x34
    bl Vec3_Copy
    lfs f0, lbl_806D63F8(r2)
    addi r3, r31, 0x34
    stfs f0, 0x14(r31)
    bl Vec3_ToYaw
    bl FAbs_FloatAsDouble
    lfs f2, lbl_806D6440(r2)
    lfs f0, lbl_806D6430(r2)
    fdivs f2, f1, f2
    lfs f1, lbl_806D6444(r2)
    fdivs f0, f0, f2
    stfs f0, 0x18(r31)
    lfs f0, 0x18(r31)
    fcmpo cr0, f1, f0
    bge StarItem_BoundToVictimTick_L_800FDAAC
    stfs f1, 0x18(r31)
    StarItem_BoundToVictimTick_L_800FDAAC:
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0x14
    li r4, 0x3
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6430(r2)
    addi r3, r30, 0x14
    lfs f0, 0x18(r31)
    lfs f2, lbl_806D6448(r2)
    fdivs f0, f1, f0
    fdivs f1, f2, f0
    bl SpriteSlot_SetScale
    li r3, 0x0
    li r0, 0xa
    stw r3, 0x8(r31)
    stw r0, 0xc(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    StarItem_BoundToVictimTick_L_800FDAF4:
    addi r3, r31, 0x34
    bl Vec3_ToYaw
    fmr f31, f1
    addi r3, r31, 0x34
    mr r4, r3
    fneg f1, f31
    bl Vec2_RotateY
    lwz r6, 0x34(r31)
    addi r3, r31, 0x34
    lwz r0, 0x38(r31)
    addi r4, r1, 0x20
    lwz r7, 0x50(r1)
    addi r5, r1, 0x14
    stw r6, 0x14(r1)
    lwz r6, 0x54(r1)
    stw r0, 0x18(r1)
    lwz r0, 0x58(r1)
    lwz r8, 0x3c(r31)
    stw r8, 0x1c(r1)
    stw r7, 0x20(r1)
    stw r6, 0x24(r1)
    stw r0, 0x28(r1)
    lfs f1, 0x14(r31)
    bl Vec3_Lerp
    lfs f2, 0x14(r31)
    addi r3, r31, 0x34
    lfs f1, lbl_806D6430(r2)
    mr r4, r3
    lfs f0, lbl_806D63F8(r2)
    fsubs f1, f1, f2
    fmuls f0, f0, f2
    fmadds f1, f31, f1, f0
    bl Vec2_RotateY
    lfs f2, 0x14(r31)
    lfs f0, 0x18(r31)
    lfs f1, lbl_806D6430(r2)
    fadds f0, f2, f0
    stfs f0, 0x14(r31)
    lfs f0, 0x14(r31)
    fcmpo cr0, f1, f0
    bge StarItem_BoundToVictimTick_L_800FDC9C
    addi r3, r31, 0x34
    addi r4, r1, 0x50
    bl Vec3_Copy
    addi r3, r31, 0x34
    lfs f1, lbl_806D63F8(r2)
    mr r4, r3
    bl Vec2_RotateY
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0x14
    li r4, 0x4
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6430(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b StarItem_BoundToVictimTick_L_800FDC9C
    StarItem_BoundToVictimTick_L_800FDBE0:
    lbz r0, 0x1e(r30)
    cmpwi r0, 0x1
    bne StarItem_BoundToVictimTick_L_800FDC9C
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0x14
    li r4, 0x5
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6430(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b StarItem_BoundToVictimTick_L_800FDC9C
    StarItem_BoundToVictimTick_L_800FDC18:
    lbz r0, 0x1e(r30)
    cmpwi r0, 0x1
    bne StarItem_BoundToVictimTick_L_800FDC9C
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0x14
    li r4, 0x6
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6430(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    li r0, 0x14
    stw r0, 0x4(r31)
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    b StarItem_BoundToVictimTick_L_800FDC9C
    StarItem_BoundToVictimTick_L_800FDC58:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne StarItem_BoundToVictimTick_L_800FDC9C
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D644C(r2)
    lfs f0, lbl_806D63F8(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge StarItem_BoundToVictimTick_L_800FDC9C
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_BoundToVictimTick_L_800FDF04
    StarItem_BoundToVictimTick_L_800FDC9C:
    lwz r6, 0x34(r31)
    addi r3, r30, 0xa0
    lwz r0, 0x38(r31)
    addi r4, r1, 0x11c
    addi r5, r1, 0x8
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0x3c(r31)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    lwz r3, 0x9c(r31)
    li r4, 0xf
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r1, 0x9c
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x9c
    bl Mtx44_GetPitchOfPosZ
    stfs f1, 0xac(r30)
    addi r3, r1, 0x9c
    bl Mtx44_GetYawOfPosZ
    lfs f2, lbl_806D6450(r2)
    lfs f0, lbl_806D63F8(r2)
    fadds f1, f2, f1
    fadds f1, f0, f1
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r30)
    lwz r3, 0x9c(r31)
    bl KartFxParam_GetConst1p5
    lfs f0, lbl_806D63FC(r2)
    mr r3, r30
    fmuls f1, f0, f1
    bl Item_DecayVelocityScalar
    lbz r0, 0xca(r30)
    cmpwi r0, 0x3
    bne StarItem_BoundToVictimTick_L_800FDD54
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne StarItem_BoundToVictimTick_L_800FDD54
    lfs f1, lbl_806D63F8(r2)
    mr r3, r30
    mr r4, r31
    li r5, 0x3
    bl Item_SpawnHitBurstParticles
    li r0, 0xa
    stw r0, 0x8(r31)
    StarItem_BoundToVictimTick_L_800FDD54:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne StarItem_BoundToVictimTick_L_800FDEE0
    lwz r3, 0x9c(r31)
    lis r4, 0x1
    li r5, 0x0
    lwz r6, 0x304(r3)
    lwz r0, 0x10(r6)
    lwz r6, 0x14(r6)
    and r0, r0, r5
    and r4, r6, r4
    xor r4, r4, r5
    xor r0, r0, r5
    or. r0, r4, r0
    beq StarItem_BoundToVictimTick_L_800FDEE0
    cmplwi r3, 0x0
    beq StarItem_BoundToVictimTick_L_800FDDA8
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r31, 0x34
    bl Mtx44_GetTranslation_RowMajor
    StarItem_BoundToVictimTick_L_800FDDA8:
    lis r4, lbl_80330380@ha
    addi r3, r1, 0x5c
    addi r5, r4, lbl_80330380@l
    addi r4, r30, 0x14
    bl JointByName_GetMatrix4x4Transposed
    addi r3, r30, 0xa0
    addi r4, r1, 0x5c
    bl Mtx44_GetTranslation_ColMajor
    addi r3, r1, 0x5c
    bl Mtx44_GetPitchOfPosZ
    stfs f1, 0xac(r30)
    addi r3, r1, 0x5c
    bl Mtx44_GetYawOfPosZ
    lfs f0, lbl_806D63F8(r2)
    addi r3, r30, 0x14
    stfs f1, 0xb0(r30)
    li r4, 0x0
    fmr f1, f0
    stfs f0, 0xb4(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    lwz r3, 0x9c(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x44
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r31, 0x34
    addi r4, r30, 0xa0
    addi r5, r1, 0x44
    bl Vec3_Subtract_DestFirst
    lfs f1, lbl_806D63F8(r2)
    addi r3, r31, 0x40
    lfs f2, lbl_806D6454(r2)
    fmr f3, f1
    bl GetSpawnPosition
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b StarItem_BoundToVictimTick_L_800FDF04
    StarItem_BoundToVictimTick_L_800FDE50:
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D644C(r2)
    lfs f0, lbl_806D63F8(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge StarItem_BoundToVictimTick_L_800FDE88
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_BoundToVictimTick_L_800FDF04
    StarItem_BoundToVictimTick_L_800FDE88:
    lfs f1, 0x44(r31)
    addi r3, r31, 0x34
    lfs f0, lbl_806D6458(r2)
    mr r4, r3
    addi r5, r31, 0x40
    fadds f0, f1, f0
    stfs f0, 0x44(r31)
    bl Vec3_Add_DestFirst
    lwz r3, 0x9c(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x38
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r30, 0xa0
    addi r4, r1, 0x38
    addi r5, r31, 0x34
    bl Vec3_Add_DestFirst
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6440(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    StarItem_BoundToVictimTick_L_800FDEE0:
    lwz r3, 0x9c(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq StarItem_BoundToVictimTick_L_800FDEFC
    li r0, 0x0
    stb r0, 0x28(r30)
    b StarItem_BoundToVictimTick_L_800FDF04
    StarItem_BoundToVictimTick_L_800FDEFC:
    li r0, 0x1
    stb r0, 0x28(r30)
    StarItem_BoundToVictimTick_L_800FDF04:
    psq_l f31, 0x178(r1), 0, 0
    lwz r0, 0x184(r1)
    lfd f31, 0x170(r1)
    lwz r31, 0x16c(r1)
    lwz r30, 0x168(r1)
    mtlr r0
    addi r1, r1, 0x180
    blr
}

/* === extracted from auto_StarItem_FallRecover_text === */
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
extern void Vec3_ToPitch();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D63F8;
extern unsigned int lbl_806D6430;
extern unsigned int lbl_806D6440;
extern unsigned int lbl_806D644C;
extern unsigned int lbl_806D6458;

/* --- function index (1 fns, .text 0x800FDF24..0x800FE1EC) ---
 * [  0] 0x800FDF24 size:0x2C8   global StarItem_FallRecoveryTick
 */

/* --- forward decls --- */
asm void StarItem_FallRecoveryTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_StarItem_FallRecoveryTick[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_StarItem_FallRecoveryTick = {
    (void *)&StarItem_FallRecoveryTick, 0x000002C8, (void *)extab_StarItem_FallRecoveryTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void StarItem_FallRecoveryTick(void) { /* 0x800FDF24 size:0x2C8 */
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
    beq StarItem_FallRecoveryTick_L_800FE014
    bge StarItem_FallRecoveryTick_L_800FE014
    cmpwi r0, 0x0
    bge StarItem_FallRecoveryTick_L_800FDF60
    b StarItem_FallRecoveryTick_L_800FE014
    StarItem_FallRecoveryTick_L_800FDF60:
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
    beq StarItem_FallRecoveryTick_L_800FDFA0
    li r0, 0xa
    stw r0, 0x4(r31)
    b StarItem_FallRecoveryTick_L_800FDFA8
    StarItem_FallRecoveryTick_L_800FDFA0:
    li r0, 0x0
    stw r0, 0x4(r31)
    StarItem_FallRecoveryTick_L_800FDFA8:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    bne StarItem_FallRecoveryTick_L_800FDFBC
    lfs f0, lbl_806D63F8(r2)
    stfs f0, 0xbc(r30)
    StarItem_FallRecoveryTick_L_800FDFBC:
    lwz r3, 0x9c(r31)
    cmplwi r3, 0x0
    beq StarItem_FallRecoveryTick_L_800FE008
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
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    StarItem_FallRecoveryTick_L_800FE008:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    StarItem_FallRecoveryTick_L_800FE014:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne StarItem_FallRecoveryTick_L_800FE058
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D644C(r2)
    lfs f0, lbl_806D63F8(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge StarItem_FallRecoveryTick_L_800FE058
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_FallRecoveryTick_L_800FE1D4
    StarItem_FallRecoveryTick_L_800FE058:
    lwz r0, 0x9c(r31)
    cmplwi r0, 0x0
    bne StarItem_FallRecoveryTick_L_800FE0D4
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq StarItem_FallRecoveryTick_L_800FE080
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D6458(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    StarItem_FallRecoveryTick_L_800FE080:
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
    beq StarItem_FallRecoveryTick_L_800FE118
    lfs f1, 0x8(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stfs f0, 0x14(r31)
    b StarItem_FallRecoveryTick_L_800FE118
    StarItem_FallRecoveryTick_L_800FE0D4:
    lfs f1, 0x44(r31)
    addi r3, r31, 0x34
    lfs f0, lbl_806D6458(r2)
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
    StarItem_FallRecoveryTick_L_800FE118:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmpwi r0, 0x5
    beq StarItem_FallRecoveryTick_L_800FE198
    bge StarItem_FallRecoveryTick_L_800FE144
    cmpwi r0, 0x1
    beq StarItem_FallRecoveryTick_L_800FE150
    blt StarItem_FallRecoveryTick_L_800FE1A4
    cmpwi r0, 0x4
    bge StarItem_FallRecoveryTick_L_800FE168
    b StarItem_FallRecoveryTick_L_800FE1A4
    StarItem_FallRecoveryTick_L_800FE144:
    cmpwi r0, 0x9
    beq StarItem_FallRecoveryTick_L_800FE180
    b StarItem_FallRecoveryTick_L_800FE1A4
    StarItem_FallRecoveryTick_L_800FE150:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6440(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b StarItem_FallRecoveryTick_L_800FE1A4
    StarItem_FallRecoveryTick_L_800FE168:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6440(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b StarItem_FallRecoveryTick_L_800FE1A4
    StarItem_FallRecoveryTick_L_800FE180:
    lfs f1, lbl_806D6440(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b StarItem_FallRecoveryTick_L_800FE1A4
    StarItem_FallRecoveryTick_L_800FE198:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    stfs f1, 0xac(r30)
    StarItem_FallRecoveryTick_L_800FE1A4:
    lfs f1, lbl_806D6430(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lwz r3, 0x9c(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq StarItem_FallRecoveryTick_L_800FE1CC
    li r0, 0x0
    stb r0, 0x28(r30)
    b StarItem_FallRecoveryTick_L_800FE1D4
    StarItem_FallRecoveryTick_L_800FE1CC:
    li r0, 0x1
    stb r0, 0x28(r30)
    StarItem_FallRecoveryTick_L_800FE1D4:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

/* === extracted from auto_StarItem_FlightAndLo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_SpawnDirect();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
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
extern void Item_CheckWallCollision();
extern void Item_ComputeYawRelativeApproach();
extern void Item_DecayVelocityScalar();
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart();
extern void Item_RenderCharacterScaledFromJoint12();
extern void Item_SpawnHitBurstParticles();
extern void JointByName_GetWorldPosition();
extern void KartDriver_GetJointByIdx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_SetScale();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_HorizontalMagnitude();
extern void Vec3_Scale();
extern void Vec3_Subtract_DestFirst();
extern void Vec3_ToPitch();
extern void Vec3_ToYaw();
extern void fn_801B129C();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D63F8;
extern unsigned int lbl_806D6424;
extern unsigned int lbl_806D6430;
extern unsigned int lbl_806D6450;
extern unsigned int lbl_806D6454;
extern unsigned int lbl_806D645C;
extern unsigned int lbl_806D6460;
extern unsigned int lbl_806D6464;
extern unsigned int lbl_806D6468;
extern unsigned int lbl_806D646C;
extern unsigned int lbl_806D6470;
extern unsigned int lbl_806D6474;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int EffectVfx82_FieldItemDropPuff_Tick[];
extern unsigned int lbl_8032FF60[];

/* --- function index (1 fns, .text 0x800FE1EC..0x800FEA94) ---
 * [  0] 0x800FE1EC size:0x8A8   global StarItem_FlightAndLockOnTick
 */

/* --- forward decls --- */
asm void StarItem_FlightAndLockOnTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_StarItem_FlightAndLockOnTick[8] = {
    0x18, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_StarItem_FlightAndLockOnTick = {
    (void *)&StarItem_FlightAndLockOnTick, 0x000008A8, (void *)extab_StarItem_FlightAndLockOnTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void StarItem_FlightAndLockOnTick(void) { /* 0x800FE1EC size:0x8A8 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    stw r29, 0x94(r1)
    mr r29, r3
    lis r6, lbl_8032FF60@ha
    lbz r5, 0xc9(r3)
    mr r30, r4
    addi r31, r6, lbl_8032FF60@l
    extsb r0, r5
    cmpwi r0, 0x1
    beq StarItem_FlightAndLockOnTick_L_800FE258
    bge StarItem_FlightAndLockOnTick_L_800FE23C
    cmpwi r0, 0x0
    bge StarItem_FlightAndLockOnTick_L_800FE248
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE23C:
    cmpwi r0, 0x3
    bge StarItem_FlightAndLockOnTick_L_800FEA70
    b StarItem_FlightAndLockOnTick_L_800FE3D0
    StarItem_FlightAndLockOnTick_L_800FE248:
    addi r3, r5, 0x1
    li r0, 0x0
    stb r3, 0xc9(r29)
    stb r0, 0xca(r29)
    StarItem_FlightAndLockOnTick_L_800FE258:
    lbz r0, 0xca(r29)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_FlightAndLockOnTick_L_800FE2C4
    bge StarItem_FlightAndLockOnTick_L_800FEA70
    cmpwi r0, 0x0
    bge StarItem_FlightAndLockOnTick_L_800FE278
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE278:
    addi r3, r29, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6454(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    li r0, 0x1
    lfs f1, lbl_806D63F8(r2)
    stb r0, 0x28(r29)
    lfs f0, lbl_806D645C(r2)
    stfs f1, 0x2c(r29)
    stfs f0, 0xc4(r29)
    lbz r3, 0xca(r29)
    addi r0, r3, 0x1
    stb r0, 0xca(r29)
    StarItem_FlightAndLockOnTick_L_800FE2C4:
    lwz r11, 0x408(r31)
    mr r3, r29
    lwz r10, 0x40c(r31)
    addi r4, r1, 0x50
    lwz r9, 0x410(r31)
    addi r5, r1, 0x44
    lwz r8, 0x3fc(r31)
    li r6, 0x1
    lwz r7, 0x400(r31)
    lwz r0, 0x404(r31)
    stw r11, 0x44(r1)
    lfs f1, lbl_806D6430(r2)
    stw r10, 0x48(r1)
    stw r9, 0x4c(r1)
    stw r8, 0x50(r1)
    stw r7, 0x54(r1)
    stw r0, 0x58(r1)
    bl Item_RenderCharacterScaledFromJoint12
    lwz r3, 0x98(r30)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq StarItem_FlightAndLockOnTick_L_800FE328
    li r0, 0x0
    stb r0, 0x28(r29)
    b StarItem_FlightAndLockOnTick_L_800FE330
    StarItem_FlightAndLockOnTick_L_800FE328:
    li r0, 0x1
    stb r0, 0x28(r29)
    StarItem_FlightAndLockOnTick_L_800FE330:
    lbz r0, 0xa0(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq StarItem_FlightAndLockOnTick_L_800FE398
    bge StarItem_FlightAndLockOnTick_L_800FE3B4
    cmpwi r0, 0x1
    bge StarItem_FlightAndLockOnTick_L_800FE350
    b StarItem_FlightAndLockOnTick_L_800FE3B4
    StarItem_FlightAndLockOnTick_L_800FE350:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x28(r29)
    addi r3, r29, 0x14
    li r4, 0x0
    stb r0, 0xa0(r30)
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f1, lbl_806D6460(r2)
    mr r3, r29
    lfs f2, lbl_806D63F8(r2)
    addi r4, r30, 0x34
    bl Item_InitLaunchFromKart
    lbz r3, 0xc9(r29)
    li r0, 0x0
    addi r3, r3, 0x1
    stb r3, 0xc9(r29)
    stb r0, 0xca(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE398:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r30)
    stb r3, 0x28(r29)
    stb r0, 0xc8(r29)
    stb r3, 0xc9(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE3B4:
    lwz r3, 0x98(r30)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r30, 0x34
    bl Mtx44_GetTranslation_RowMajor
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE3D0:
    lbz r0, 0xca(r29)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_FlightAndLockOnTick_L_800FE488
    bge StarItem_FlightAndLockOnTick_L_800FE3F0
    cmpwi r0, 0x0
    bge StarItem_FlightAndLockOnTick_L_800FE3FC
    b StarItem_FlightAndLockOnTick_L_800FE4FC
    StarItem_FlightAndLockOnTick_L_800FE3F0:
    cmpwi r0, 0x3
    bge StarItem_FlightAndLockOnTick_L_800FE4FC
    b StarItem_FlightAndLockOnTick_L_800FE4C0
    StarItem_FlightAndLockOnTick_L_800FE3FC:
    bl ItemTracker_AcquireLock
    mr r3, r29
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    li r0, 0x1
    addi r3, r1, 0x38
    stb r0, 0x8d(r29)
    addi r4, r30, 0x14
    li r5, 0x0
    stb r0, 0x3c(r29)
    lwz r6, 0xa0(r29)
    lwz r0, 0xa4(r29)
    stw r6, 0x38(r1)
    stw r0, 0x3c(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x40(r1)
    bl ItemObject_GetGroundTypeAt
    lfs f2, 0xa4(r29)
    addi r3, r29, 0x14
    lfs f0, 0x14(r30)
    li r4, 0x1
    lfs f1, lbl_806D63F8(r2)
    fsubs f0, f2, f0
    stfs f0, 0x14(r30)
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6454(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    li r3, 0x12c
    li r0, 0x0
    stw r3, 0x4(r30)
    stw r0, 0x8(r30)
    lbz r3, 0xca(r29)
    addi r0, r3, 0x1
    stb r0, 0xca(r29)
    StarItem_FlightAndLockOnTick_L_800FE488:
    lbz r0, 0x1e(r29)
    cmpwi r0, 0x1
    bne StarItem_FlightAndLockOnTick_L_800FE4FC
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    li r4, 0x2
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D6454(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    lbz r3, 0xca(r29)
    addi r0, r3, 0x1
    stb r0, 0xca(r29)
    b StarItem_FlightAndLockOnTick_L_800FE4FC
    StarItem_FlightAndLockOnTick_L_800FE4C0:
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne StarItem_FlightAndLockOnTick_L_800FE4D4
    lfs f2, lbl_806D6430(r2)
    b StarItem_FlightAndLockOnTick_L_800FE4D8
    StarItem_FlightAndLockOnTick_L_800FE4D4:
    lfs f2, lbl_806D6454(r2)
    StarItem_FlightAndLockOnTick_L_800FE4D8:
    cmpwi r0, 0x0
    mr r3, r29
    bne StarItem_FlightAndLockOnTick_L_800FE4EC
    lfs f1, lbl_806D6464(r2)
    b StarItem_FlightAndLockOnTick_L_800FE4F0
    StarItem_FlightAndLockOnTick_L_800FE4EC:
    lfs f1, lbl_806D6468(r2)
    StarItem_FlightAndLockOnTick_L_800FE4F0:
    bl Item_AccelClampVelocity
    addi r3, r29, 0xa0
    bl fn_801B129C
    StarItem_FlightAndLockOnTick_L_800FE4FC:
    addi r3, r1, 0x80
    addi r4, r29, 0x14
    addi r5, r31, 0x420
    bl JointByName_GetWorldPosition
    mr r3, r29
    addi r4, r29, 0xb0
    li r5, 0x0
    bl Item_HomingScanAndSteer
    addi r3, r29, 0xb8
    bl Vec3_ToPitch
    stfs f1, 0xac(r29)
    mr r3, r29
    lfs f1, lbl_806D6430(r2)
    bl Item_DecayVelocityScalar
    mr r3, r29
    bl ItemCollision_Check
    cmpwi r3, 0x3
    beq StarItem_FlightAndLockOnTick_L_800FE694
    bge StarItem_FlightAndLockOnTick_L_800FE558
    cmpwi r3, 0x1
    beq StarItem_FlightAndLockOnTick_L_800FE568
    bge StarItem_FlightAndLockOnTick_L_800FE5D4
    b StarItem_FlightAndLockOnTick_L_800FE7A0
    StarItem_FlightAndLockOnTick_L_800FE558:
    cmpwi r3, 0x5
    beq StarItem_FlightAndLockOnTick_L_800FE794
    bge StarItem_FlightAndLockOnTick_L_800FE7A0
    b StarItem_FlightAndLockOnTick_L_800FE720
    StarItem_FlightAndLockOnTick_L_800FE568:
    lwz r3, 0x8(r29)
    bl ItemAlias_HitRemapLookup
    extsh r31, r3
    mr r3, r29
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r30)
    mr r5, r31
    li r6, 0x0
    bl fn_801B1D5C
    mr r3, r29
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r30)
    mr r3, r29
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl ItemHit_Dispatch
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r3, 0x0
    li r0, 0x2
    stb r3, 0x8d(r29)
    stb r0, 0xc8(r29)
    stb r3, 0xc9(r29)
    stb r3, 0xcb(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE5D4:
    mr r3, r29
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r30)
    bl fn_801B1660
    mr r3, r29
    bl ItemTracker_GetTargetKart
    stw r3, 0x9c(r30)
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    lfs f0, lbl_806D6454(r2)
    stb r0, 0x8d(r29)
    addi r3, r29, 0xa0
    lfs f1, lbl_806D6424(r2)
    addi r4, r1, 0x80
    stfs f0, 0xbc(r29)
    lfs f0, 0xb8(r29)
    fmuls f0, f0, f1
    stfs f0, 0xb8(r29)
    lfs f0, 0xc0(r29)
    fmuls f0, f0, f1
    stfs f0, 0xc0(r29)
    bl Vec3_Copy
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    lwz r6, 0xa0(r29)
    addi r4, r1, 0x2c
    lwz r0, 0xa4(r29)
    li r3, 0x84
    li r5, 0x0
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x34(r1)
    bl SoundMgr_PlaySE_Positional
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x1
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE694:
    mr r3, r29
    bl ItemTracker_GetTargetKart
    mr r4, r3
    lwz r3, 0x98(r30)
    bl fn_801B158C
    li r0, 0x0
    mr r3, r29
    stw r0, 0x7c(r30)
    lwz r4, 0xb8(r29)
    lwz r0, 0xbc(r29)
    stw r4, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xc0(r29)
    stw r0, 0x1c(r1)
    lwz r4, 0xa0(r29)
    lwz r0, 0xa4(r29)
    stw r4, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x28(r1)
    bl ItemTracker_GetTargetKart
    mr r4, r3
    addi r3, r29, 0xb8
    addi r5, r1, 0x20
    addi r6, r1, 0x14
    bl Item_ComputeYawRelativeApproach
    addi r3, r29, 0xb8
    bl Vec3_ToYaw
    stfs f1, 0xb0(r29)
    mr r3, r29
    li r4, 0x0
    bl ItemTracker_SetTrackPhase
    li r0, 0x5
    stw r0, 0x8(r30)
    b StarItem_FlightAndLockOnTick_L_800FE7A0
    StarItem_FlightAndLockOnTick_L_800FE720:
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
    addi r3, r29, 0xa0
    stb r0, 0x8d(r29)
    addi r4, r1, 0x80
    bl Vec3_Copy
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x3
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE794:
    mr r3, r29
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    StarItem_FlightAndLockOnTick_L_800FE7A0:
    lwz r0, 0x8(r30)
    cmplwi r0, 0x0
    bne StarItem_FlightAndLockOnTick_L_800FE7B8
    mr r3, r29
    li r4, 0x1
    bl ItemTracker_SetTrackPhase
    StarItem_FlightAndLockOnTick_L_800FE7B8:
    lbz r0, 0x8d(r29)
    cmpwi r0, 0x2
    bne StarItem_FlightAndLockOnTick_L_800FE8C4
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    addi r3, r29, 0xa0
    stb r0, 0x8d(r29)
    addi r4, r1, 0x80
    bl Vec3_Copy
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    lbz r0, 0x8e(r29)
    cmpwi r0, 0x1
    bne StarItem_FlightAndLockOnTick_L_800FE894
    addi r3, r29, 0xb8
    addi r5, r29, 0x90
    mr r4, r3
    bl Vec3_Add_DestFirst
    lfs f0, lbl_806D6454(r2)
    mr r3, r29
    lfs f2, lbl_806D646C(r2)
    mr r4, r30
    stfs f0, 0xbc(r29)
    li r5, 0x0
    lfs f1, lbl_806D63F8(r2)
    lfs f0, 0xb8(r29)
    fmuls f0, f0, f2
    stfs f0, 0xb8(r29)
    lfs f0, 0xc0(r29)
    fmuls f0, f0, f2
    stfs f0, 0xc0(r29)
    bl Item_SpawnHitBurstParticles
    lwz r6, 0xa0(r29)
    addi r4, r1, 0x8
    lwz r0, 0xa4(r29)
    li r3, 0x84
    li r5, 0x0
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x10(r1)
    bl SoundMgr_PlaySE_Positional
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x4
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE894:
    lfs f1, lbl_806D63F8(r2)
    mr r3, r29
    mr r4, r30
    li r5, 0x2
    bl Item_SpawnHitBurstParticles
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x6
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE8C4:
    mr r3, r29
    addi r4, r1, 0x74
    addi r5, r1, 0x68
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq StarItem_FlightAndLockOnTick_L_800FE9E4
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r0, 0x0
    addi r3, r1, 0x5c
    stb r0, 0x8d(r29)
    addi r4, r1, 0x68
    addi r5, r29, 0xa0
    bl Vec3_Subtract_DestFirst
    addi r3, r1, 0x5c
    bl Vec3_HorizontalMagnitude
    lfs f0, lbl_806D6470(r2)
    addi r3, r29, 0xb8
    fsubs f31, f1, f0
    bl Vec3_HorizontalMagnitude
    lfs f0, lbl_806D6430(r2)
    addi r3, r1, 0x5c
    addi r4, r29, 0xb8
    fdivs f0, f0, f1
    fmuls f1, f0, f31
    bl Vec3_Scale
    addi r3, r29, 0xa0
    addi r4, r1, 0x80
    addi r5, r1, 0x5c
    bl Vec3_Add_DestFirst
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D63F8(r2)
    addi r3, r29, 0x14
    bl SpriteSlot_SetScale
    addi r3, r1, 0x74
    bl Vec3_ToYaw
    stfs f1, 0x14(r30)
    mr r3, r29
    mr r4, r30
    li r5, 0x1
    lfs f1, 0x14(r30)
    bl Item_SpawnHitBurstParticles
    lis r3, EffectVfx82_FieldItemDropPuff_Tick@ha
    addi r3, r3, EffectVfx82_FieldItemDropPuff_Tick@l
    bl DrawEffect_SpawnDirect
    mr. r31, r3
    beq StarItem_FlightAndLockOnTick_L_800FE9C8
    addi r3, r31, 0x8c
    addi r4, r29, 0xa0
    bl Vec3_Copy
    lfs f1, lbl_806D63F8(r2)
    addi r3, r31, 0x98
    lfs f2, lbl_806D6450(r2)
    lfs f0, 0x14(r30)
    fmr f3, f1
    fadds f2, f2, f0
    bl GetSpawnPosition
    StarItem_FlightAndLockOnTick_L_800FE9C8:
    li r0, 0x2
    li r3, 0x0
    stb r0, 0xc8(r29)
    li r0, 0x7
    stb r3, 0xc9(r29)
    stb r0, 0xcb(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FE9E4:
    lfs f1, lbl_806D6474(r2)
    mr r3, r29
    addi r4, r30, 0x14
    fmr f2, f1
    bl Item_AdvanceProjectileSimple
    cmpwi r3, 0x0
    bne StarItem_FlightAndLockOnTick_L_800FEA34
    lbz r0, 0xca(r29)
    cmpwi r0, 0x2
    bne StarItem_FlightAndLockOnTick_L_800FEA34
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r29)
    li r0, 0x9
    stb r3, 0xc8(r29)
    stb r4, 0xc9(r29)
    stb r0, 0xcb(r29)
    b StarItem_FlightAndLockOnTick_L_800FEA70
    StarItem_FlightAndLockOnTick_L_800FEA34:
    lwz r0, 0x4(r30)
    cmplwi r0, 0x0
    bne StarItem_FlightAndLockOnTick_L_800FEA70
    lbz r0, 0xca(r29)
    cmpwi r0, 0x2
    bne StarItem_FlightAndLockOnTick_L_800FEA70
    mr r3, r29
    bl ItemTracker_ReleaseLock
    li r4, 0x0
    li r3, 0x2
    stb r4, 0x8d(r29)
    li r0, 0x5
    stb r3, 0xc8(r29)
    stb r4, 0xc9(r29)
    stb r0, 0xcb(r29)
    StarItem_FlightAndLockOnTick_L_800FEA70:
    psq_l f31, 0xa8(r1), 0, 0
    lwz r0, 0xb4(r1)
    lfd f31, 0xa0(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    lwz r29, 0x94(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

/* === extracted from auto_StarItem_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_OrbitAnchorKart();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform();
extern void StarItem_BoundToVictimTick();
extern void StarItem_FallRecoveryTick();
extern void StarItem_FlightAndLockOnTick();
extern void Vec3_Add_DestFirst();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D63F8;
extern unsigned int lbl_806D6420;
extern unsigned int lbl_806D6424;
extern unsigned int lbl_806D6428;
extern unsigned int lbl_806D642C;
extern unsigned int lbl_806D6430;
extern unsigned int lbl_806D6434;
extern unsigned int lbl_806D6438;
extern unsigned int lbl_806D643C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_80421840[];

/* --- function index (1 fns, .text 0x800FEA94..0x800FEE8C) ---
 * [  0] 0x800FEA94 size:0x3F8   global StarItem_Tick
 */

/* --- forward decls --- */
asm void StarItem_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_StarItem_Tick[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_StarItem_Tick = {
    (void *)&StarItem_Tick, 0x000003F8, (void *)extab_StarItem_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void StarItem_Tick(void) { /* 0x800FEA94 size:0x3F8 */
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
    beq StarItem_Tick_L_800FEB18
    bge StarItem_Tick_L_800FEAD4
    cmpwi r0, 0x0
    beq StarItem_Tick_L_800FEAE0
    bge StarItem_Tick_L_800FEB08
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FEAD4:
    cmpwi r0, 0x4
    bge StarItem_Tick_L_800FEDD0
    b StarItem_Tick_L_800FEDC0
    StarItem_Tick_L_800FEAE0:
    addi r3, r30, 0x14
    li r4, 0x54
    bl SpriteSlot_InitNonLoop
    li r0, 0x2
    li r3, 0x0
    stb r0, 0x8c(r30)
    li r0, 0x1
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    StarItem_Tick_L_800FEB08:
    mr r3, r30
    mr r4, r31
    bl StarItem_FlightAndLockOnTick
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FEB18:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt StarItem_Tick_L_800FEDD0
    lis r4, jumptable_80421840@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_80421840@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    mr r4, r31
    bl StarItem_BoundToVictimTick
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_Tick_L_800FEBB0
    bge StarItem_Tick_L_800FEBB0
    cmpwi r0, 0x0
    bge StarItem_Tick_L_800FEB78
    b StarItem_Tick_L_800FEBB0
    StarItem_Tick_L_800FEB78:
    lfs f1, lbl_806D63F8(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D63F8(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    StarItem_Tick_L_800FEBB0:
    lfs f2, lbl_806D643C(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq StarItem_Tick_L_800FEDD0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_Tick_L_800FEC58
    bge StarItem_Tick_L_800FEC58
    cmpwi r0, 0x0
    bge StarItem_Tick_L_800FEC14
    b StarItem_Tick_L_800FEC58
    StarItem_Tick_L_800FEC14:
    lfs f1, lbl_806D63F8(r2)
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
    StarItem_Tick_L_800FEC58:
    lfs f1, lbl_806D6430(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lwz r5, 0x4(r31)
    mr r3, r30
    lfs f1, lbl_806D6434(r2)
    addi r4, r31, 0x34
    lfs f2, lbl_806D6438(r2)
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq StarItem_Tick_L_800FEDD0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_Tick_L_800FEDD0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq StarItem_Tick_L_800FECE4
    bge StarItem_Tick_L_800FECBC
    cmpwi r0, 0x0
    bge StarItem_Tick_L_800FECC8
    b StarItem_Tick_L_800FED5C
    StarItem_Tick_L_800FECBC:
    cmpwi r0, 0x3
    bge StarItem_Tick_L_800FED5C
    b StarItem_Tick_L_800FED08
    StarItem_Tick_L_800FECC8:
    li r0, 0xa
    lfs f0, lbl_806D63F8(r2)
    stw r0, 0x4(r31)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    StarItem_Tick_L_800FECE4:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne StarItem_Tick_L_800FED5C
    li r0, 0x14
    stw r0, 0x4(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    b StarItem_Tick_L_800FED5C
    StarItem_Tick_L_800FED08:
    lfs f1, 0x18(r31)
    lfs f0, lbl_806D6420(r2)
    fsubs f0, f1, f0
    stfs f0, 0x18(r31)
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne StarItem_Tick_L_800FED5C
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D6424(r2)
    lfs f0, lbl_806D63F8(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge StarItem_Tick_L_800FED5C
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FED5C:
    lfs f1, 0xb0(r30)
    lfs f2, 0x14(r31)
    lfs f3, lbl_806D6428(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xb0(r30)
    lfs f1, 0xac(r30)
    lfs f0, 0x18(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lfs f0, lbl_806D642C(r2)
    lfs f1, 0xac(r30)
    fcmpo cr0, f1, f0
    bge StarItem_Tick_L_800FED98
    stfs f0, 0xac(r30)
    StarItem_Tick_L_800FED98:
    lfs f1, lbl_806D6430(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    mr r4, r31
    bl StarItem_FallRecoveryTick
    b StarItem_Tick_L_800FEDD0
    StarItem_Tick_L_800FEDC0:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b StarItem_Tick_L_800FEE74
    StarItem_Tick_L_800FEDD0:
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
    beq StarItem_Tick_L_800FEE38
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    StarItem_Tick_L_800FEE38:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq StarItem_Tick_L_800FEE4C
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    StarItem_Tick_L_800FEE4C:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq StarItem_Tick_L_800FEE60
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    StarItem_Tick_L_800FEE60:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq StarItem_Tick_L_800FEE74
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    StarItem_Tick_L_800FEE74:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

