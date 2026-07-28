/* === extracted from auto_BananaTriple_OnImpac_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void ItemObject_GetGroundTypeAt();
extern void Item_DecayVelocityScalar();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5D90;
extern unsigned int lbl_806D5D94;
extern unsigned int lbl_806D5D98;
extern unsigned int lbl_806D5DA0;
extern unsigned int lbl_806D5DAC;
extern unsigned int lbl_806D5DB0;
extern unsigned int lbl_806D5DB4;

/* --- function index (1 fns, .text 0x800E8ACC..0x800E8CAC) ---
 * [  0] 0x800E8ACC size:0x1E0   global BananaTriple_OnImpactTick_32to36
 */

/* --- forward decls --- */
asm void BananaTriple_OnImpactTick_32to36(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_BananaTriple_OnImpactTick_32to36[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BananaTriple_OnImpactTick_32to36 = {
    (void *)&BananaTriple_OnImpactTick_32to36, 0x000001E0, (void *)extab_BananaTriple_OnImpactTick_32to36
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BananaTriple_OnImpactTick_32to36(void) { /* 0x800E8ACC size:0x1E0 */
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
    beq BananaTriple_OnImpactTick_32to36_L_800E8B84
    bge BananaTriple_OnImpactTick_32to36_L_800E8B84
    cmpwi r0, 0x0
    bge BananaTriple_OnImpactTick_32to36_L_800E8B08
    b BananaTriple_OnImpactTick_32to36_L_800E8B84
    BananaTriple_OnImpactTick_32to36_L_800E8B08:
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
    beq BananaTriple_OnImpactTick_32to36_L_800E8B48
    li r0, 0xa
    stw r0, 0x4(r31)
    b BananaTriple_OnImpactTick_32to36_L_800E8B50
    BananaTriple_OnImpactTick_32to36_L_800E8B48:
    li r0, 0x0
    stw r0, 0x4(r31)
    BananaTriple_OnImpactTick_32to36_L_800E8B50:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x4
    bne BananaTriple_OnImpactTick_32to36_L_800E8B78
    lfs f1, lbl_806D5D90(r2)
    addi r3, r30, 0x14
    li r4, 0x6
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5DAC(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    BananaTriple_OnImpactTick_32to36_L_800E8B78:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    BananaTriple_OnImpactTick_32to36_L_800E8B84:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne BananaTriple_OnImpactTick_32to36_L_800E8BC8
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5DB0(r2)
    lfs f0, lbl_806D5D90(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge BananaTriple_OnImpactTick_32to36_L_800E8BC8
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b BananaTriple_OnImpactTick_32to36_L_800E8C94
    BananaTriple_OnImpactTick_32to36_L_800E8BC8:
    lwz r0, 0x8(r30)
    cmpwi r0, 0x34
    beq BananaTriple_OnImpactTick_32to36_L_800E8BE4
    lfs f1, lbl_806D5D94(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b BananaTriple_OnImpactTick_32to36_L_800E8BF0
    BananaTriple_OnImpactTick_32to36_L_800E8BE4:
    lfs f1, lbl_806D5D98(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    BananaTriple_OnImpactTick_32to36_L_800E8BF0:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq BananaTriple_OnImpactTick_32to36_L_800E8C94
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
    beq BananaTriple_OnImpactTick_32to36_L_800E8C4C
    lfs f1, 0x8(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stfs f0, 0x14(r31)
    BananaTriple_OnImpactTick_32to36_L_800E8C4C:
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5DB4(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x4
    bne BananaTriple_OnImpactTick_32to36_L_800E8C80
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D5DA0(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b BananaTriple_OnImpactTick_32to36_L_800E8C94
    BananaTriple_OnImpactTick_32to36_L_800E8C80:
    lfs f1, lbl_806D5DA0(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    BananaTriple_OnImpactTick_32to36_L_800E8C94:
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

