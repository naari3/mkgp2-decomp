/* === extracted from auto_TaruItem_Dispatch_25_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void GetSpawnPosition();
extern void ItemHit_Dispatch();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_PrepareHitRebound();
extern void KartDriver_GetKartRootMtx();
extern void Matrix4_Identity();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotY();
extern void Matrix4_PreMultiplyRotZ();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_Translate();
extern void ShellPile_Spawn();
extern void SoundMgr_PlaySE_Positional();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void TaruItem_OnGroundDriftTick_25();
extern void TaruItem_Tick_HeldAndHoming_25();
extern void Vec3_AddNormalizedXZ();
extern void Vec3_Add_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5DE0;
extern unsigned int lbl_806D5DE4;
extern unsigned int lbl_806D5DE8;
extern unsigned int lbl_806D5DEC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_80421598[];
extern unsigned int lbl_8032F458[];
extern unsigned int lbl_8032F468[];

/* --- function index (1 fns, .text 0x800EA958..0x800EADB4) ---
 * [  0] 0x800EA958 size:0x45C   global TaruItem_Dispatch_25
 */

/* --- forward decls --- */
asm void TaruItem_Dispatch_25(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TaruItem_Dispatch_25[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TaruItem_Dispatch_25 = {
    (void *)&TaruItem_Dispatch_25, 0x0000045C, (void *)extab_TaruItem_Dispatch_25
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TaruItem_Dispatch_25(void) { /* 0x800EA958 size:0x45C */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq TaruItem_Dispatch_25_L_800EAA1C
    bge TaruItem_Dispatch_25_L_800EA998
    cmpwi r0, 0x0
    beq TaruItem_Dispatch_25_L_800EA9A4
    bge TaruItem_Dispatch_25_L_800EAA0C
    b TaruItem_Dispatch_25_L_800EACB4
    TaruItem_Dispatch_25_L_800EA998:
    cmpwi r0, 0x4
    bge TaruItem_Dispatch_25_L_800EACB4
    b TaruItem_Dispatch_25_L_800EACA4
    TaruItem_Dispatch_25_L_800EA9A4:
    addi r3, r30, 0x14
    li r4, 0x3b
    bl SpriteSlot_InitNonLoop
    lis r4, lbl_8032F458@ha
    addi r3, r30, 0x14
    addi r4, r4, lbl_8032F458@l
    li r5, 0x10
    li r6, 0x0
    bl SpriteSlot_SetJointVisibilityByName
    lis r4, lbl_8032F468@ha
    addi r3, r30, 0x14
    addi r4, r4, lbl_8032F468@l
    li r5, 0x10
    li r6, 0x1
    bl SpriteSlot_SetJointVisibilityByName
    addi r3, r30, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r4, 0x1
    li r3, 0x4
    stb r4, 0x0(r31)
    li r0, 0x0
    stb r3, 0x8c(r30)
    stb r0, 0x8d(r30)
    stb r4, 0xc8(r30)
    stb r0, 0xc9(r30)
    TaruItem_Dispatch_25_L_800EAA0C:
    mr r3, r30
    mr r4, r31
    bl TaruItem_Tick_HeldAndHoming_25
    b TaruItem_Dispatch_25_L_800EACB4
    TaruItem_Dispatch_25_L_800EAA1C:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt TaruItem_Dispatch_25_L_800EACB4
    lis r4, jumptable_80421598@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_80421598@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    lwz r3, 0x9c(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x2c
    bl Mtx44_GetTranslation_RowMajor
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TaruItem_Dispatch_25_L_800EAA98
    bge TaruItem_Dispatch_25_L_800EAA98
    cmpwi r0, 0x0
    bge TaruItem_Dispatch_25_L_800EAA78
    b TaruItem_Dispatch_25_L_800EAA98
    TaruItem_Dispatch_25_L_800EAA78:
    mr r3, r30
    addi r4, r31, 0x40
    addi r5, r31, 0x34
    addi r6, r31, 0x4
    bl Item_PrepareHitRebound
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    TaruItem_Dispatch_25_L_800EAA98:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TaruItem_Dispatch_25_L_800EAB10
    lbz r0, 0x1(r31)
    cmplwi r0, 0x0
    beq TaruItem_Dispatch_25_L_800EAAC4
    lwz r6, 0x9c(r31)
    mr r3, r30
    li r4, 0x0
    li r5, 0x0
    bl ItemHit_Dispatch
    TaruItem_Dispatch_25_L_800EAAC4:
    mr r3, r30
    mr r4, r31
    bl ShellPile_Spawn
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x20
    lwz r0, 0xa4(r30)
    li r3, 0xbe
    li r5, 0x0
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x28(r1)
    bl SoundMgr_PlaySE_Positional
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TaruItem_Dispatch_25_L_800EACB4
    TaruItem_Dispatch_25_L_800EAB10:
    lwz r6, 0x34(r31)
    mr r3, r30
    lwz r0, 0x38(r31)
    addi r4, r31, 0x40
    addi r5, r1, 0x38
    stw r6, 0x38(r1)
    stw r0, 0x3c(r1)
    lwz r0, 0x3c(r31)
    stw r0, 0x40(r1)
    bl Vec3_AddNormalizedXZ
    addi r3, r30, 0xa0
    addi r4, r1, 0x2c
    addi r5, r31, 0x40
    bl Vec3_Add_DestFirst
    lfs f1, lbl_806D5DE8(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, lbl_806D5DEC(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TaruItem_Dispatch_25_L_800EACB4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TaruItem_Dispatch_25_L_800EABC4
    bge TaruItem_Dispatch_25_L_800EABC4
    cmpwi r0, 0x0
    bge TaruItem_Dispatch_25_L_800EAB8C
    b TaruItem_Dispatch_25_L_800EABC4
    TaruItem_Dispatch_25_L_800EAB8C:
    lfs f1, lbl_806D5DE0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D5DE0(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    TaruItem_Dispatch_25_L_800EABC4:
    lfs f2, lbl_806D5DE4(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq TaruItem_Dispatch_25_L_800EACB4
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TaruItem_Dispatch_25_L_800EACB4
    mr r4, r31
    bl ShellPile_Spawn
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x14
    lwz r0, 0xa4(r30)
    li r3, 0xbe
    li r5, 0x0
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    bl SoundMgr_PlaySE_Positional
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TaruItem_Dispatch_25_L_800EACB4
    mr r4, r31
    bl ShellPile_Spawn
    lwz r6, 0xa0(r30)
    addi r4, r1, 0x8
    lwz r0, 0xa4(r30)
    li r3, 0xbe
    li r5, 0x0
    stw r6, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x10(r1)
    bl SoundMgr_PlaySE_Positional
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TaruItem_Dispatch_25_L_800EACB4
    mr r4, r31
    bl TaruItem_OnGroundDriftTick_25
    b TaruItem_Dispatch_25_L_800EACB4
    mr r4, r31
    bl TaruItem_OnGroundDriftTick_25
    b TaruItem_Dispatch_25_L_800EACB4
    TaruItem_Dispatch_25_L_800EACA4:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b TaruItem_Dispatch_25_L_800EAD9C
    TaruItem_Dispatch_25_L_800EACB4:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq TaruItem_Dispatch_25_L_800EAD4C
    addi r3, r1, 0x50
    bl Matrix4_Identity
    addi r3, r1, 0x50
    lfs f1, 0xc4(r30)
    mr r4, r3
    bl Mtx44_Scale_Uniform
    addi r3, r1, 0x50
    lfs f1, 0xac(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    addi r3, r1, 0x50
    lfs f1, 0xb4(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotZ
    addi r3, r1, 0x50
    lfs f1, 0xb0(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x50
    lwz r0, 0xa4(r30)
    mr r4, r3
    addi r5, r1, 0x44
    stw r6, 0x44(r1)
    stw r0, 0x48(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x4c(r1)
    bl Mtx44_Translate
    addi r3, r30, 0x48
    addi r4, r1, 0x50
    bl DbgScene_CopyMatrix3x4Transpose
    TaruItem_Dispatch_25_L_800EAD4C:
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq TaruItem_Dispatch_25_L_800EAD60
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    TaruItem_Dispatch_25_L_800EAD60:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq TaruItem_Dispatch_25_L_800EAD74
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    TaruItem_Dispatch_25_L_800EAD74:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq TaruItem_Dispatch_25_L_800EAD88
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    TaruItem_Dispatch_25_L_800EAD88:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq TaruItem_Dispatch_25_L_800EAD9C
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    TaruItem_Dispatch_25_L_800EAD9C:
    lwz r0, 0xa4(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

