/* === extracted from auto_BananaTriple_StuckOn_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void ItemHit_Dispatch();
extern void Item_DecayVelocityScalar();
extern void Item_PrepareHitRebound();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();
extern void Vec3_AddNormalizedXZ();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5D90;
extern unsigned int lbl_806D5D94;
extern unsigned int lbl_806D5D98;
extern unsigned int lbl_806D5DA0;
extern unsigned int lbl_806D5DA4;
extern unsigned int lbl_806D5DA8;
extern unsigned int lbl_806D5DAC;
extern unsigned int lbl_806D5DB0;
extern unsigned int lbl_806D5DB4;

/* --- function index (1 fns, .text 0x800E8818..0x800E8ACC) ---
 * [  0] 0x800E8818 size:0x2B4   global BananaTriple_StuckOnDriverTick_32to36
 */

/* --- forward decls --- */
asm void BananaTriple_StuckOnDriverTick_32to36(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BananaTriple_StuckOnDriverTick_32to36[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BananaTriple_StuckOnDriverTick_32to36 = {
    (void *)&BananaTriple_StuckOnDriverTick_32to36, 0x000002B4, (void *)extab_BananaTriple_StuckOnDriverTick_32to36
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BananaTriple_StuckOnDriverTick_32to36(void) { /* 0x800E8818 size:0x2B4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stw r31, 0x2c(r1)
    mr r31, r4
    stw r30, 0x28(r1)
    mr r30, r3
    lwz r3, 0x9c(r4)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x14
    bl Mtx44_GetTranslation_RowMajor
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BananaTriple_StuckOnDriverTick_32to36_L_800E88EC
    bge BananaTriple_StuckOnDriverTick_32to36_L_800E8868
    cmpwi r0, 0x0
    bge BananaTriple_StuckOnDriverTick_32to36_L_800E8874
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8A58
    BananaTriple_StuckOnDriverTick_32to36_L_800E8868:
    cmpwi r0, 0x3
    bge BananaTriple_StuckOnDriverTick_32to36_L_800E8A58
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8934
    BananaTriple_StuckOnDriverTick_32to36_L_800E8874:
    lbz r0, 0x1(r31)
    cmplwi r0, 0x0
    beq BananaTriple_StuckOnDriverTick_32to36_L_800E88A8
    mr r3, r30
    addi r4, r31, 0x40
    addi r5, r31, 0x34
    addi r6, r31, 0x4
    bl Item_PrepareHitRebound
    li r3, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8A58
    BananaTriple_StuckOnDriverTick_32to36_L_800E88A8:
    addi r3, r31, 0x34
    addi r4, r30, 0xb8
    bl Vec3_Copy
    lfs f1, lbl_806D5D90(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    addi r3, r31, 0x40
    addi r4, r30, 0xa0
    addi r5, r1, 0x14
    bl Vec3_Subtract_DestFirst
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8A58
    BananaTriple_StuckOnDriverTick_32to36_L_800E88EC:
    lwz r6, 0x34(r31)
    mr r3, r30
    lwz r0, 0x38(r31)
    addi r4, r31, 0x40
    addi r5, r1, 0x8
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0x3c(r31)
    stw r0, 0x10(r1)
    bl Vec3_AddNormalizedXZ
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne BananaTriple_StuckOnDriverTick_32to36_L_800E8A58
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8A58
    BananaTriple_StuckOnDriverTick_32to36_L_800E8934:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BananaTriple_StuckOnDriverTick_32to36_L_800E89E0
    bge BananaTriple_StuckOnDriverTick_32to36_L_800E89E0
    cmpwi r0, 0x0
    bge BananaTriple_StuckOnDriverTick_32to36_L_800E8954
    b BananaTriple_StuckOnDriverTick_32to36_L_800E89E0
    BananaTriple_StuckOnDriverTick_32to36_L_800E8954:
    lbz r0, 0x2(r31)
    cmplwi r0, 0x0
    beq BananaTriple_StuckOnDriverTick_32to36_L_800E8974
    lwz r6, 0x9c(r31)
    mr r3, r30
    addi r5, r30, 0xa0
    li r4, 0x0
    bl ItemHit_Dispatch
    BananaTriple_StuckOnDriverTick_32to36_L_800E8974:
    lfs f0, lbl_806D5DA4(r2)
    li r0, 0xa
    lfs f1, lbl_806D5DA8(r2)
    stfs f0, 0x38(r31)
    lfs f0, 0x34(r31)
    fmuls f0, f0, f1
    stfs f0, 0x34(r31)
    lfs f0, 0x3c(r31)
    fmuls f0, f0, f1
    stfs f0, 0x3c(r31)
    stw r0, 0x4(r31)
    lbz r3, 0xcb(r30)
    extsb. r0, r3
    beq BananaTriple_StuckOnDriverTick_32to36_L_800E89B8
    extsb r0, r3
    cmpwi r0, 0x4
    bne BananaTriple_StuckOnDriverTick_32to36_L_800E89D4
    BananaTriple_StuckOnDriverTick_32to36_L_800E89B8:
    lfs f1, lbl_806D5D90(r2)
    addi r3, r30, 0x14
    li r4, 0x6
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_StuckOnDriverTick_32to36_L_800E89D4:
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    BananaTriple_StuckOnDriverTick_32to36_L_800E89E0:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne BananaTriple_StuckOnDriverTick_32to36_L_800E8A24
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5DB0(r2)
    lfs f0, lbl_806D5D90(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge BananaTriple_StuckOnDriverTick_32to36_L_800E8A24
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8AB4
    BananaTriple_StuckOnDriverTick_32to36_L_800E8A24:
    lfs f1, 0x38(r31)
    addi r3, r31, 0x40
    lfs f0, lbl_806D5DB4(r2)
    mr r4, r3
    addi r5, r31, 0x34
    fadds f0, f1, f0
    stfs f0, 0x38(r31)
    bl Vec3_Add_DestFirst
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D5DA0(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    BananaTriple_StuckOnDriverTick_32to36_L_800E8A58:
    addi r3, r30, 0xa0
    addi r4, r1, 0x14
    addi r5, r31, 0x40
    bl Vec3_Add_DestFirst
    lwz r0, 0x8(r30)
    cmpwi r0, 0x34
    beq BananaTriple_StuckOnDriverTick_32to36_L_800E8A84
    lfs f1, lbl_806D5D94(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8A90
    BananaTriple_StuckOnDriverTick_32to36_L_800E8A84:
    lfs f1, lbl_806D5D98(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    BananaTriple_StuckOnDriverTick_32to36_L_800E8A90:
    lwz r3, 0x9c(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq BananaTriple_StuckOnDriverTick_32to36_L_800E8AAC
    li r0, 0x0
    stb r0, 0x28(r30)
    b BananaTriple_StuckOnDriverTick_32to36_L_800E8AB4
    BananaTriple_StuckOnDriverTick_32to36_L_800E8AAC:
    li r0, 0x1
    stb r0, 0x28(r30)
    BananaTriple_StuckOnDriverTick_32to36_L_800E8AB4:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

