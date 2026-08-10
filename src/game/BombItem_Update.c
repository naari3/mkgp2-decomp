/* === extracted from auto_BombItem_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BombItem_TickActive();
extern void BuildOrientationFromYaw();
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemObject_SpawnWithAlias();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_OrbitAnchorKart();
extern void JointByName_GetWorldPosition();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform();
extern void SpriteSlot_TickAnim();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Subtract_DestFirst();
extern void VfxEffect_UpdateTwoChildSpinAndSound_Helper();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D61D0;
extern unsigned int lbl_806D61D4;
extern unsigned int lbl_806D61D8;
extern unsigned int lbl_806D61DC;
extern unsigned int lbl_806D61E0;
extern unsigned int lbl_806D61E4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_804217B0[];
extern unsigned int lbl_8032FA60[];

/* --- function index (1 fns, .text 0x800F7584..0x800F7AFC) ---
 * [  0] 0x800F7584 size:0x578   global BombItem_Update
 */

/* --- forward decls --- */
asm void BombItem_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BombItem_Update[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BombItem_Update = {
    (void *)&BombItem_Update, 0x00000578, (void *)extab_BombItem_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BombItem_Update(void) { /* 0x800F7584 size:0x578 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stw r31, 0x4c(r1)
    stw r30, 0x48(r1)
    mr r30, r3
    addi r31, r30, 0xec
    stw r29, 0x44(r1)
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq BombItem_Update_L_800F761C
    bge BombItem_Update_L_800F75C8
    cmpwi r0, 0x0
    beq BombItem_Update_L_800F75D4
    bge BombItem_Update_L_800F760C
    b BombItem_Update_L_800F79F4
    BombItem_Update_L_800F75C8:
    cmpwi r0, 0x4
    bge BombItem_Update_L_800F79F4
    b BombItem_Update_L_800F79C4
    BombItem_Update_L_800F75D4:
    li r0, 0x1
    addi r3, r30, 0x14
    stb r0, 0x90(r31)
    li r4, 0x4d
    bl SpriteSlot_InitNonLoop
    li r0, 0x4
    li r4, 0x3
    stb r0, 0x14(r30)
    li r3, 0x0
    li r0, 0x1
    stb r4, 0x8c(r30)
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    BombItem_Update_L_800F760C:
    mr r3, r30
    mr r4, r31
    bl BombItem_TickActive
    b BombItem_Update_L_800F79F4
    BombItem_Update_L_800F761C:
    lbz r0, 0xcb(r30)
    extsb r4, r0
    cmplwi r4, 0x9
    bgt BombItem_Update_L_800F79F4
    lis r3, jumptable_804217B0@ha
    slwi r0, r4, 2
    addi r3, r3, jumptable_804217B0@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    li r3, 0x63
    li r4, 0xff
    bl ItemObject_SpawnWithAlias
    mr. r29, r3
    beq BombItem_Update_L_800F7684
    lbz r0, 0xf0(r31)
    addi r3, r29, 0xa0
    addi r4, r30, 0xa0
    stb r0, 0x1dc(r29)
    lwz r0, 0xf4(r31)
    stw r0, 0x1e0(r29)
    bl Vec3_Copy
    lwz r0, 0x94(r31)
    stw r0, 0x180(r29)
    lwz r0, 0x98(r31)
    stw r0, 0x184(r29)
    BombItem_Update_L_800F7684:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BombItem_Update_L_800F79F4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_Update_L_800F76F4
    bge BombItem_Update_L_800F76F4
    cmpwi r0, 0x0
    bge BombItem_Update_L_800F76BC
    b BombItem_Update_L_800F76F4
    BombItem_Update_L_800F76BC:
    lfs f1, lbl_806D61D0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D61D0(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    BombItem_Update_L_800F76F4:
    lfs f2, lbl_806D61DC(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq BombItem_Update_L_800F79F4
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BombItem_Update_L_800F79F4
    li r3, 0x63
    li r4, 0xff
    bl ItemObject_SpawnWithAlias
    mr. r29, r3
    beq BombItem_Update_L_800F776C
    lbz r0, 0xf0(r31)
    addi r3, r29, 0xa0
    addi r4, r30, 0xa0
    stb r0, 0x1dc(r29)
    lwz r0, 0xf4(r31)
    stw r0, 0x1e0(r29)
    bl Vec3_Copy
    lwz r0, 0x94(r31)
    stw r0, 0x180(r29)
    lwz r0, 0x98(r31)
    stw r0, 0x184(r29)
    BombItem_Update_L_800F776C:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BombItem_Update_L_800F79F4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_Update_L_800F77E8
    bge BombItem_Update_L_800F77E8
    cmpwi r0, 0x0
    bge BombItem_Update_L_800F77A4
    b BombItem_Update_L_800F77E8
    BombItem_Update_L_800F77A4:
    lfs f1, lbl_806D61D0(r2)
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
    BombItem_Update_L_800F77E8:
    lfs f1, lbl_806D61D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, lbl_806D61D8(r2)
    mr r3, r30
    lwz r5, 0x4(r31)
    addi r4, r31, 0x34
    fmr f2, f1
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq BombItem_Update_L_800F79F4
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BombItem_Update_L_800F79F4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_Update_L_800F7874
    bge BombItem_Update_L_800F7874
    cmpwi r0, 0x0
    bge BombItem_Update_L_800F784C
    b BombItem_Update_L_800F7874
    BombItem_Update_L_800F784C:
    cmpwi r4, 0x5
    beq BombItem_Update_L_800F7860
    li r0, 0xa
    stw r0, 0x4(r31)
    b BombItem_Update_L_800F7868
    BombItem_Update_L_800F7860:
    li r0, 0x0
    stw r0, 0x4(r31)
    BombItem_Update_L_800F7868:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    BombItem_Update_L_800F7874:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne BombItem_Update_L_800F78B8
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D61E0(r2)
    lfs f0, lbl_806D61D0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge BombItem_Update_L_800F78B8
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BombItem_Update_L_800F79F4
    BombItem_Update_L_800F78B8:
    lfs f1, lbl_806D61D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x9
    bne BombItem_Update_L_800F79F4
    lfs f2, 0xbc(r30)
    lfs f0, lbl_806D61E4(r2)
    lfs f1, lbl_806D61DC(r2)
    fadds f0, f2, f0
    stfs f0, 0xbc(r30)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b BombItem_Update_L_800F79F4
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq BombItem_Update_L_800F7940
    bge BombItem_Update_L_800F7940
    cmpwi r0, 0x0
    bge BombItem_Update_L_800F7918
    b BombItem_Update_L_800F7940
    BombItem_Update_L_800F7918:
    cmpwi r4, 0x5
    beq BombItem_Update_L_800F792C
    li r0, 0xa
    stw r0, 0x4(r31)
    b BombItem_Update_L_800F7934
    BombItem_Update_L_800F792C:
    li r0, 0x0
    stw r0, 0x4(r31)
    BombItem_Update_L_800F7934:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    BombItem_Update_L_800F7940:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne BombItem_Update_L_800F7984
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D61E0(r2)
    lfs f0, lbl_806D61D0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge BombItem_Update_L_800F7984
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BombItem_Update_L_800F79F4
    BombItem_Update_L_800F7984:
    lfs f1, lbl_806D61D4(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x9
    bne BombItem_Update_L_800F79F4
    lfs f2, 0xbc(r30)
    lfs f0, lbl_806D61E4(r2)
    lfs f1, lbl_806D61DC(r2)
    fadds f0, f2, f0
    stfs f0, 0xbc(r30)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b BombItem_Update_L_800F79F4
    BombItem_Update_L_800F79C4:
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq BombItem_Update_L_800F79D8
    li r0, 0x1
    stb r0, 0xc9(r3)
    BombItem_Update_L_800F79D8:
    li r0, 0x0
    mr r3, r30
    stw r0, 0x4c(r31)
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b BombItem_Update_L_800F7AE0
    BombItem_Update_L_800F79F4:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r6, 0xac(r30)
    addi r3, r30, 0x14
    lwz r0, 0xb0(r30)
    addi r4, r1, 0x20
    addi r5, r1, 0x14
    stw r6, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xb4(r30)
    stw r0, 0x1c(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x28(r1)
    lfs f1, 0xc4(r30)
    bl SpriteSlot_SetTransform
    addi r3, r30, 0x14
    bl SpriteSlot_TickAnim
    lis r4, lbl_8032FA60@ha
    addi r3, r1, 0x2c
    addi r5, r4, lbl_8032FA60@l
    addi r4, r30, 0x14
    bl JointByName_GetWorldPosition
    lwz r5, 0x2c(r1)
    addi r4, r1, 0x8
    lwz r3, 0x30(r1)
    lwz r0, 0x34(r1)
    stw r5, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    lwz r3, 0x4c(r31)
    lfs f1, 0xc4(r30)
    lfs f2, 0x2c(r30)
    bl VfxEffect_UpdateTwoChildSpinAndSound_Helper
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq BombItem_Update_L_800F7AA4
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    BombItem_Update_L_800F7AA4:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq BombItem_Update_L_800F7AB8
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    BombItem_Update_L_800F7AB8:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq BombItem_Update_L_800F7ACC
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    BombItem_Update_L_800F7ACC:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq BombItem_Update_L_800F7AE0
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    BombItem_Update_L_800F7AE0:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    lwz r29, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}
