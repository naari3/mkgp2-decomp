/* === extracted from auto_BananaTriple_Dispatc_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BananaTriple_OnImpactTick_32to36();
extern void BananaTriple_StuckOnDriverTick_32to36();
extern void BananaTriple_Tick_HeldAndHoming_32to36();
extern void DbgScene_CopyMatrix3x4Transpose();
extern void DrawEffect_SpawnDirect();
extern void Effect_SparkSpray_PlaceChildren();
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_OrbitAnchorKart();
extern void JointByName_GetWorldPosition();
extern void Matrix4_Identity();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotY();
extern void Matrix4_PreMultiplyRotZ();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_Translate();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_TickAnim();
extern void Vec3_Add_DestFirst();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5D90;
extern unsigned int lbl_806D5D94;
extern unsigned int lbl_806D5D98;
extern unsigned int lbl_806D5D9C;
extern unsigned int lbl_806D5DA0;
extern unsigned int lbl_806D5DDC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int Effect_SparkSprayCompound_Update[];
extern unsigned int jumptable_80421570[];
extern unsigned int lbl_8032F41C[];
extern unsigned int lbl_804211B0[];

/* --- function index (1 fns, .text 0x800E9934..0x800E9E94) ---
 * [  0] 0x800E9934 size:0x560   global BananaTriple_Dispatch_32to36
 */

/* --- forward decls --- */
asm void BananaTriple_Dispatch_32to36(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BananaTriple_Dispatch_32to36[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BananaTriple_Dispatch_32to36 = {
    (void *)&BananaTriple_Dispatch_32to36, 0x00000560, (void *)extab_BananaTriple_Dispatch_32to36
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BananaTriple_Dispatch_32to36(void) { /* 0x800E9934 size:0x560 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stw r31, 0x7c(r1)
    stw r30, 0x78(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BananaTriple_Dispatch_32to36_L_800E9AF8
    bge BananaTriple_Dispatch_32to36_L_800E9974
    cmpwi r0, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9980
    bge BananaTriple_Dispatch_32to36_L_800E9AE8
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    BananaTriple_Dispatch_32to36_L_800E9974:
    cmpwi r0, 0x4
    bge BananaTriple_Dispatch_32to36_L_800E9CF4
    b BananaTriple_Dispatch_32to36_L_800E9CA4
    BananaTriple_Dispatch_32to36_L_800E9980:
    li r3, 0x1
    stb r3, 0x90(r31)
    lwz r0, 0x8(r30)
    cmpwi r0, 0x34
    beq BananaTriple_Dispatch_32to36_L_800E99CC
    bge BananaTriple_Dispatch_32to36_L_800E99A8
    cmpwi r0, 0x32
    beq BananaTriple_Dispatch_32to36_L_800E99B8
    bge BananaTriple_Dispatch_32to36_L_800E99C4
    b BananaTriple_Dispatch_32to36_L_800E99EC
    BananaTriple_Dispatch_32to36_L_800E99A8:
    cmpwi r0, 0x36
    beq BananaTriple_Dispatch_32to36_L_800E99E4
    bge BananaTriple_Dispatch_32to36_L_800E99EC
    b BananaTriple_Dispatch_32to36_L_800E99D8
    BananaTriple_Dispatch_32to36_L_800E99B8:
    li r0, 0x0
    stb r0, 0x3(r31)
    b BananaTriple_Dispatch_32to36_L_800E99EC
    BananaTriple_Dispatch_32to36_L_800E99C4:
    stb r3, 0x3(r31)
    b BananaTriple_Dispatch_32to36_L_800E99EC
    BananaTriple_Dispatch_32to36_L_800E99CC:
    li r0, 0x2
    stb r0, 0x3(r31)
    b BananaTriple_Dispatch_32to36_L_800E99EC
    BananaTriple_Dispatch_32to36_L_800E99D8:
    li r0, 0x3
    stb r0, 0x3(r31)
    b BananaTriple_Dispatch_32to36_L_800E99EC
    BananaTriple_Dispatch_32to36_L_800E99E4:
    li r0, 0x4
    stb r0, 0x3(r31)
    BananaTriple_Dispatch_32to36_L_800E99EC:
    lbz r0, 0x3(r31)
    addi r4, r13, -0x7960  /* lbl_806CF3C0 */
    addi r3, r30, 0x14
    lbzx r4, r4, r0
    bl SpriteSlot_InitNonLoop
    li r0, 0x4
    addi r3, r30, 0x14
    stb r0, 0x14(r30)
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r0, 0x1
    lis r3, lbl_804211B0@ha
    stb r0, 0x0(r31)
    addi r0, r3, lbl_804211B0@l
    addi r3, r30, 0x14
    li r5, 0x10
    lbz r4, 0x3(r31)
    li r6, 0x1
    mulli r4, r4, 0xc0
    add r4, r0, r4
    bl SpriteSlot_SetJointVisibilityByName
    lbz r4, 0x3(r31)
    lis r3, lbl_804211B0@ha
    addi r0, r3, lbl_804211B0@l
    addi r3, r30, 0x14
    mulli r4, r4, 0xc0
    li r5, 0x10
    li r6, 0x0
    add r4, r0, r4
    addi r4, r4, 0x40
    bl SpriteSlot_SetJointVisibilityByName
    lwz r0, 0x8(r30)
    cmpwi r0, 0x35
    beq BananaTriple_Dispatch_32to36_L_800E9A98
    bge BananaTriple_Dispatch_32to36_L_800E9A8C
    cmpwi r0, 0x34
    bge BananaTriple_Dispatch_32to36_L_800E9AAC
    cmpwi r0, 0x32
    bge BananaTriple_Dispatch_32to36_L_800E9A98
    b BananaTriple_Dispatch_32to36_L_800E9ABC
    BananaTriple_Dispatch_32to36_L_800E9A8C:
    cmpwi r0, 0x37
    bge BananaTriple_Dispatch_32to36_L_800E9ABC
    b BananaTriple_Dispatch_32to36_L_800E9AAC
    BananaTriple_Dispatch_32to36_L_800E9A98:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0x8c(r30)
    stb r0, 0x8d(r30)
    b BananaTriple_Dispatch_32to36_L_800E9ABC
    BananaTriple_Dispatch_32to36_L_800E9AAC:
    li r3, 0x3
    li r0, 0x0
    stb r3, 0x8c(r30)
    stb r0, 0x8d(r30)
    BananaTriple_Dispatch_32to36_L_800E9ABC:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x33
    bne BananaTriple_Dispatch_32to36_L_800E9AD8
    lis r3, Effect_SparkSprayCompound_Update@ha
    addi r3, r3, Effect_SparkSprayCompound_Update@l
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r31)
    BananaTriple_Dispatch_32to36_L_800E9AD8:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0xc8(r30)
    stb r0, 0xc9(r30)
    BananaTriple_Dispatch_32to36_L_800E9AE8:
    mr r3, r30
    mr r4, r31
    bl BananaTriple_Tick_HeldAndHoming_32to36
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    BananaTriple_Dispatch_32to36_L_800E9AF8:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt BananaTriple_Dispatch_32to36_L_800E9CF4
    lis r4, jumptable_80421570@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_80421570@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    mr r4, r31
    bl BananaTriple_StuckOnDriverTick_32to36
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BananaTriple_Dispatch_32to36_L_800E9B84
    bge BananaTriple_Dispatch_32to36_L_800E9B84
    cmpwi r0, 0x0
    bge BananaTriple_Dispatch_32to36_L_800E9B4C
    b BananaTriple_Dispatch_32to36_L_800E9B84
    BananaTriple_Dispatch_32to36_L_800E9B4C:
    lfs f1, lbl_806D5D90(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D5D90(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    BananaTriple_Dispatch_32to36_L_800E9B84:
    lfs f2, lbl_806D5DA0(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9CF4
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    mr r4, r31
    bl BananaTriple_OnImpactTick_32to36
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BananaTriple_Dispatch_32to36_L_800E9C2C
    bge BananaTriple_Dispatch_32to36_L_800E9C2C
    cmpwi r0, 0x0
    bge BananaTriple_Dispatch_32to36_L_800E9BE8
    b BananaTriple_Dispatch_32to36_L_800E9C2C
    BananaTriple_Dispatch_32to36_L_800E9BE8:
    lfs f1, lbl_806D5D90(r2)
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
    BananaTriple_Dispatch_32to36_L_800E9C2C:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x34
    beq BananaTriple_Dispatch_32to36_L_800E9C48
    lfs f1, lbl_806D5D94(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b BananaTriple_Dispatch_32to36_L_800E9C54
    BananaTriple_Dispatch_32to36_L_800E9C48:
    lfs f1, lbl_806D5D98(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    BananaTriple_Dispatch_32to36_L_800E9C54:
    lfs f1, lbl_806D5D9C(r2)
    mr r3, r30
    lwz r5, 0x4(r31)
    addi r4, r31, 0x34
    fmr f2, f1
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9CF4
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    mr r4, r31
    bl BananaTriple_OnImpactTick_32to36
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    mr r4, r31
    bl BananaTriple_OnImpactTick_32to36
    b BananaTriple_Dispatch_32to36_L_800E9CF4
    BananaTriple_Dispatch_32to36_L_800E9CA4:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x33
    bne BananaTriple_Dispatch_32to36_L_800E9CCC
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9CC4
    li r0, 0x1
    stb r0, 0xc9(r3)
    BananaTriple_Dispatch_32to36_L_800E9CC4:
    li r0, 0x0
    stw r0, 0x4c(r31)
    BananaTriple_Dispatch_32to36_L_800E9CCC:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x35
    beq BananaTriple_Dispatch_32to36_L_800E9CE8
    cmpwi r0, 0x36
    beq BananaTriple_Dispatch_32to36_L_800E9CE8
    mr r3, r30
    bl ItemObject_DecrementCategoryBudget
    BananaTriple_Dispatch_32to36_L_800E9CE8:
    mr r3, r30
    bl SpriteSlot_Container_Free
    b BananaTriple_Dispatch_32to36_L_800E9E7C
    BananaTriple_Dispatch_32to36_L_800E9CF4:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lbz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9D8C
    addi r3, r1, 0x38
    bl Matrix4_Identity
    addi r3, r1, 0x38
    lfs f1, 0xc4(r30)
    mr r4, r3
    bl Mtx44_Scale_Uniform
    addi r3, r1, 0x38
    lfs f1, 0xb4(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotZ
    addi r3, r1, 0x38
    lfs f1, 0xac(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    addi r3, r1, 0x38
    lfs f1, 0xb0(r30)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x38
    lwz r0, 0xa4(r30)
    mr r4, r3
    addi r5, r1, 0x20
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x28(r1)
    bl Mtx44_Translate
    addi r3, r30, 0x48
    addi r4, r1, 0x38
    bl DbgScene_CopyMatrix3x4Transpose
    BananaTriple_Dispatch_32to36_L_800E9D8C:
    addi r3, r30, 0x14
    bl SpriteSlot_TickAnim
    lwz r0, 0x8(r30)
    cmpwi r0, 0x33
    bne BananaTriple_Dispatch_32to36_L_800E9E2C
    lis r4, lbl_8032F41C@ha
    addi r3, r1, 0x2c
    addi r5, r4, lbl_8032F41C@l
    addi r4, r30, 0x14
    bl JointByName_GetWorldPosition
    lbz r0, 0x28(r30)
    extsb. r0, r0
    beq BananaTriple_Dispatch_32to36_L_800E9DF8
    lwz r5, 0x2c(r1)
    addi r4, r1, 0x14
    lwz r3, 0x30(r1)
    lwz r0, 0x34(r1)
    stw r5, 0x14(r1)
    lfs f1, lbl_806D5DDC(r2)
    stw r3, 0x18(r1)
    stw r0, 0x1c(r1)
    lfs f0, 0xc4(r30)
    lwz r3, 0x4c(r31)
    fmuls f1, f1, f0
    lfs f2, 0x2c(r30)
    bl Effect_SparkSpray_PlaceChildren
    b BananaTriple_Dispatch_32to36_L_800E9E2C
    BananaTriple_Dispatch_32to36_L_800E9DF8:
    lwz r5, 0x2c(r1)
    addi r4, r1, 0x8
    lwz r3, 0x30(r1)
    lwz r0, 0x34(r1)
    stw r5, 0x8(r1)
    lfs f1, lbl_806D5DDC(r2)
    stw r3, 0xc(r1)
    lfs f2, lbl_806D5D90(r2)
    stw r0, 0x10(r1)
    lfs f0, 0xc4(r30)
    lwz r3, 0x4c(r31)
    fmuls f1, f1, f0
    bl Effect_SparkSpray_PlaceChildren
    BananaTriple_Dispatch_32to36_L_800E9E2C:
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9E40
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    BananaTriple_Dispatch_32to36_L_800E9E40:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9E54
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    BananaTriple_Dispatch_32to36_L_800E9E54:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9E68
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    BananaTriple_Dispatch_32to36_L_800E9E68:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq BananaTriple_Dispatch_32to36_L_800E9E7C
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    BananaTriple_Dispatch_32to36_L_800E9E7C:
    lwz r0, 0x84(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

