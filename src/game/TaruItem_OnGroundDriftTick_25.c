/* === extracted from auto_TaruItem_OnGroundDri_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void FAbs_FloatAsDouble();
extern void Item_AccelClampVelocity();
extern void Item_AdvanceFallingDrop();
extern void Item_BounceOffWall();
extern void Item_CheckWallCollision();
extern void Item_DecayVelocityScalar();
extern void Item_ProbeLateralGroundPitch();
extern void Vec2_RotateY();
extern void Vec3_ToYaw();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int lbl_806D5DE0;
extern unsigned int lbl_806D5DE8;
extern unsigned int lbl_806D5DEC;
extern unsigned int lbl_806D5DF0;
extern unsigned int lbl_806D5DF4;
extern unsigned int lbl_806D5DF8;
extern unsigned int lbl_806D5DFC;
extern unsigned int lbl_806D5E00;
extern unsigned int lbl_806D5E04;
extern unsigned int lbl_806D5E08;
extern unsigned int lbl_806D5E0C;
extern unsigned int lbl_806D5E10;
extern unsigned int lbl_806D5E14;

/* --- function index (1 fns, .text 0x800E9E94..0x800EA0E8) ---
 * [  0] 0x800E9E94 size:0x254   global TaruItem_OnGroundDriftTick_25
 */

/* --- forward decls --- */
asm void TaruItem_OnGroundDriftTick_25(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TaruItem_OnGroundDriftTick_25[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TaruItem_OnGroundDriftTick_25 = {
    (void *)&TaruItem_OnGroundDriftTick_25, 0x00000254, (void *)extab_TaruItem_OnGroundDriftTick_25
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TaruItem_OnGroundDriftTick_25(void) { /* 0x800E9E94 size:0x254 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stw r31, 0x3c(r1)
    mr r31, r3
    lbz r0, 0xc9(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TaruItem_OnGroundDriftTick_25_L_800E9EF4
    bge TaruItem_OnGroundDriftTick_25_L_800E9EF4
    cmpwi r0, 0x0
    bge TaruItem_OnGroundDriftTick_25_L_800E9EC8
    b TaruItem_OnGroundDriftTick_25_L_800E9EF4
    TaruItem_OnGroundDriftTick_25_L_800E9EC8:
    lbz r0, 0xcb(r31)
    cmpwi r0, 0x5
    beq TaruItem_OnGroundDriftTick_25_L_800E9EE0
    li r0, 0xa
    stw r0, 0x4(r4)
    b TaruItem_OnGroundDriftTick_25_L_800E9EE8
    TaruItem_OnGroundDriftTick_25_L_800E9EE0:
    li r0, 0x0
    stw r0, 0x4(r4)
    TaruItem_OnGroundDriftTick_25_L_800E9EE8:
    lbz r3, 0xc9(r31)
    addi r0, r3, 0x1
    stb r0, 0xc9(r31)
    TaruItem_OnGroundDriftTick_25_L_800E9EF4:
    lwz r0, 0x4(r4)
    cmplwi r0, 0x0
    bne TaruItem_OnGroundDriftTick_25_L_800E9F38
    lfs f2, 0x2c(r31)
    lfs f1, lbl_806D5DF0(r2)
    lfs f0, lbl_806D5DE0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r31)
    lfs f1, 0x2c(r31)
    fcmpo cr0, f1, f0
    bge TaruItem_OnGroundDriftTick_25_L_800E9F38
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r31)
    stb r0, 0xc8(r31)
    stb r3, 0xc9(r31)
    b TaruItem_OnGroundDriftTick_25_L_800EA0D4
    TaruItem_OnGroundDriftTick_25_L_800E9F38:
    lfs f1, 0xbc(r31)
    lfs f0, lbl_806D5DF4(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r31)
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x0
    bne TaruItem_OnGroundDriftTick_25_L_800E9F5C
    lfs f2, lbl_806D5DF8(r2)
    b TaruItem_OnGroundDriftTick_25_L_800E9F60
    TaruItem_OnGroundDriftTick_25_L_800E9F5C:
    lfs f2, lbl_806D5DFC(r2)
    TaruItem_OnGroundDriftTick_25_L_800E9F60:
    cmpwi r0, 0x0
    mr r3, r31
    bne TaruItem_OnGroundDriftTick_25_L_800E9F74
    lfs f1, lbl_806D5E00(r2)
    b TaruItem_OnGroundDriftTick_25_L_800E9F78
    TaruItem_OnGroundDriftTick_25_L_800E9F74:
    lfs f1, lbl_806D5E04(r2)
    TaruItem_OnGroundDriftTick_25_L_800E9F78:
    bl Item_AccelClampVelocity
    lfs f1, lbl_806D5DEC(r2)
    lfs f0, 0xac(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r31)
    addi r3, r31, 0xb8
    bl Vec3_ToYaw
    fmr f2, f1
    lfs f1, 0xb0(r31)
    lfs f3, lbl_806D5E08(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xb0(r31)
    mr r3, r31
    lfs f1, lbl_806D5DE8(r2)
    bl Item_DecayVelocityScalar
    mr r3, r31
    addi r4, r1, 0x28
    li r5, 0x0
    bl Item_CheckWallCollision
    cmpwi r3, 0x0
    beq TaruItem_OnGroundDriftTick_25_L_800EA004
    lwz r6, 0x28(r1)
    mr r3, r31
    lwz r7, 0x2c(r1)
    addi r4, r1, 0x1c
    lwz r0, 0x30(r1)
    li r5, 0x0
    stw r6, 0x1c(r1)
    li r6, 0x0
    lfs f1, lbl_806D5E0C(r2)
    stw r7, 0x20(r1)
    lfs f2, lbl_806D5DE0(r2)
    stw r0, 0x24(r1)
    bl Item_BounceOffWall
    TaruItem_OnGroundDriftTick_25_L_800EA004:
    lfs f1, lbl_806D5E10(r2)
    mr r3, r31
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq TaruItem_OnGroundDriftTick_25_L_800EA0D4
    lwz r0, 0xc(r1)
    cmpwi r0, 0x0
    beq TaruItem_OnGroundDriftTick_25_L_800EA0D4
    lfs f1, 0xbc(r31)
    addi r3, r1, 0x10
    lfs f0, lbl_806D5DF4(r2)
    lfs f2, lbl_806D5DE8(r2)
    fmuls f0, f1, f0
    stfs f0, 0xbc(r31)
    lwz r4, 0xa0(r31)
    lwz r0, 0xa4(r31)
    lfs f0, 0x8(r1)
    stw r4, 0x10(r1)
    stw r0, 0x14(r1)
    lwz r0, 0xa8(r31)
    stw r0, 0x18(r1)
    lfs f3, 0xa4(r31)
    lfs f1, 0xb0(r31)
    fsubs f3, f3, f0
    bl Item_ProbeLateralGroundPitch
    stfs f1, 0xb4(r31)
    lfs f1, 0xb4(r31)
    bl FAbs_FloatAsDouble
    lfs f2, lbl_806D5DEC(r2)
    fcmpo cr0, f2, f1
    bge TaruItem_OnGroundDriftTick_25_L_800EA0D4
    lfs f0, lbl_806D5DE0(r2)
    lfs f1, 0xb4(r31)
    fcmpo cr0, f0, f1
    bge TaruItem_OnGroundDriftTick_25_L_800EA0B8
    fsubs f0, f1, f2
    addi r3, r31, 0xb8
    lfs f1, lbl_806D5E14(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    b TaruItem_OnGroundDriftTick_25_L_800EA0D4
    TaruItem_OnGroundDriftTick_25_L_800EA0B8:
    fadds f0, f2, f1
    addi r3, r31, 0xb8
    lfs f1, lbl_806D5E14(r2)
    mr r4, r3
    fneg f0, f0
    fmuls f1, f1, f0
    bl Vec2_RotateY
    TaruItem_OnGroundDriftTick_25_L_800EA0D4:
    lwz r0, 0x44(r1)
    lwz r31, 0x3c(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

