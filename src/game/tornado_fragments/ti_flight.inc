/* === extracted from auto_Tornado_FlightTick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void GetSpawnPosition();
extern void ItemObject_AllocFromPool();
extern void Item_AdvanceFallingDrop();
extern void Item_AdvanceTetherToJoint13();
extern void SoundMgr_CountActiveSEInstances();
extern void SoundMgr_PlaySE_Positional();
extern void SoundMgr_PlaySE_WithChannel();
extern void SoundMgr_StopSE_OrSpecial();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetPositionFromVec();
extern void SpriteSlot_SetRotationQuatFromVec();
extern void SpriteSlot_SetScaleXYZ();
extern void SpriteSlot_SetTranslateDxDy();
extern void Tornado_LockOnHomingTick();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Scale();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D6260;
extern unsigned int lbl_806D6264;
extern unsigned int lbl_806D6268;
extern unsigned int lbl_806D626C;
extern unsigned int lbl_806D6270;
extern unsigned int lbl_806D6274;
extern unsigned int lbl_806D6278;
extern unsigned int lbl_806D628C;
extern unsigned int lbl_806D6290;
extern unsigned int lbl_806D6294;
extern unsigned int lbl_806D6298;
extern unsigned int lbl_806D629C;
extern unsigned int lbl_806D62A0;
extern unsigned int lbl_806D62A4;
extern unsigned int lbl_806D62A8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int fn_800D748C[];
extern unsigned int jumptable_804217F8[];
extern unsigned int lbl_8032FE74[];
extern unsigned int lbl_8032FE8C[];

/* --- function index (1 fns, .text 0x800F9618..0x800F9FD4) ---
 * [  0] 0x800F9618 size:0x9BC   global Tornado_FlightTick
 */

/* --- forward decls --- */
asm void Tornado_FlightTick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tornado_FlightTick[8] = {
    0x28, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tornado_FlightTick = {
    (void *)&Tornado_FlightTick, 0x000009BC, (void *)extab_Tornado_FlightTick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Tornado_FlightTick(void) { /* 0x800F9618 size:0x9BC */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stmw r27, 0x3c(r1)
    mr r27, r3
    lbz r0, 0xc8(r3)
    addi r29, r27, 0xec
    extsb r0, r0
    cmpwi r0, 0x2
    beq Tornado_FlightTick_L_800F97A4
    bge Tornado_FlightTick_L_800F965C
    cmpwi r0, 0x0
    beq Tornado_FlightTick_L_800F9668
    bge Tornado_FlightTick_L_800F9794
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F965C:
    cmpwi r0, 0x4
    bge Tornado_FlightTick_L_800F9CFC
    b Tornado_FlightTick_L_800F9CAC
    Tornado_FlightTick_L_800F9668:
    li r0, 0x4f
    addi r3, r27, 0x14
    stw r0, 0x8(r27)
    li r4, 0x50
    bl SpriteSlot_InitNonLoop
    li r5, 0x0
    lis r3, fn_800D748C@ha
    stb r5, 0x28(r27)
    li r4, 0x5
    lfs f1, lbl_806D6264(r2)
    li r0, -0x1
    stb r4, 0x8c(r27)
    mr r30, r29
    lfs f0, lbl_806D6260(r2)
    addi r31, r3, fn_800D748C@l
    stb r5, 0x8d(r27)
    li r28, 0x0
    stfs f1, 0x1c(r29)
    stfs f0, 0x20(r29)
    stw r0, 0x30(r29)
    Tornado_FlightTick_L_800F96B8:
    mr r3, r31
    bl ItemObject_AllocFromPool
    stw r3, 0x5c(r30)
    lwz r3, 0x5c(r30)
    cmplwi r3, 0x0
    beq Tornado_FlightTick_L_800F9774
    addi r3, r3, 0x14
    li r4, 0x50
    bl SpriteSlot_InitNonLoop
    cmpwi r28, 0x0
    bne Tornado_FlightTick_L_800F96F8
    lwz r3, 0x5c(r30)
    lfs f1, lbl_806D628C(r2)
    lfs f2, lbl_806D6264(r2)
    addi r3, r3, 0x14
    bl SpriteSlot_SetTranslateDxDy
    Tornado_FlightTick_L_800F96F8:
    cmpwi r28, 0x0
    bne Tornado_FlightTick_L_800F973C
    lwz r6, 0x5c(r30)
    lis r3, lbl_8032FE74@ha
    addi r4, r3, lbl_8032FE74@l
    li r5, 0x10
    addi r3, r6, 0x14
    li r6, 0x0
    bl SpriteSlot_SetJointVisibilityByName
    lwz r6, 0x5c(r30)
    lis r3, lbl_8032FE8C@ha
    addi r4, r3, lbl_8032FE8C@l
    li r5, 0x10
    addi r3, r6, 0x14
    li r6, 0x1
    bl SpriteSlot_SetJointVisibilityByName
    b Tornado_FlightTick_L_800F9774
    Tornado_FlightTick_L_800F973C:
    lwz r6, 0x5c(r30)
    lis r3, lbl_8032FE74@ha
    addi r4, r3, lbl_8032FE74@l
    li r5, 0x10
    addi r3, r6, 0x14
    li r6, 0x1
    bl SpriteSlot_SetJointVisibilityByName
    lwz r6, 0x5c(r30)
    lis r3, lbl_8032FE8C@ha
    addi r4, r3, lbl_8032FE8C@l
    li r5, 0x10
    addi r3, r6, 0x14
    li r6, 0x0
    bl SpriteSlot_SetJointVisibilityByName
    Tornado_FlightTick_L_800F9774:
    addi r28, r28, 0x1
    addi r30, r30, 0x4
    cmpwi r28, 0x3
    blt Tornado_FlightTick_L_800F96B8
    li r3, 0x1
    li r0, 0x0
    stb r3, 0xc8(r27)
    stb r0, 0xc9(r27)
    Tornado_FlightTick_L_800F9794:
    mr r3, r27
    mr r4, r29
    bl Tornado_LockOnHomingTick
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F97A4:
    lbz r0, 0xcb(r27)
    extsb r3, r0
    subi r0, r3, 0x3
    cmplwi r0, 0x6
    bgt Tornado_FlightTick_L_800F9CFC
    lis r3, jumptable_804217F8@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_804217F8@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lbz r0, 0xc9(r27)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Tornado_FlightTick_L_800F982C
    bge Tornado_FlightTick_L_800F97F0
    cmpwi r0, 0x0
    bge Tornado_FlightTick_L_800F97FC
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F97F0:
    cmpwi r0, 0x3
    bge Tornado_FlightTick_L_800F9CFC
    b Tornado_FlightTick_L_800F986C
    Tornado_FlightTick_L_800F97FC:
    lfs f1, lbl_806D6264(r2)
    addi r3, r27, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    lfs f0, lbl_806D6264(r2)
    stfs f0, 0x14(r29)
    lfs f0, 0xc4(r27)
    stfs f0, 0x18(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    Tornado_FlightTick_L_800F982C:
    lfs f2, lbl_806D6264(r2)
    mr r3, r27
    lfs f1, 0x18(r29)
    addi r4, r29, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq Tornado_FlightTick_L_800F9CFC
    lfs f0, lbl_806D6264(r2)
    li r0, 0x78
    stfs f0, 0x2c(r27)
    stw r0, 0x4(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F986C:
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    bne Tornado_FlightTick_L_800F9CFC
    li r3, 0x3
    li r0, 0x0
    stb r3, 0xc8(r27)
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    lbz r0, 0xc9(r27)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Tornado_FlightTick_L_800F98CC
    bge Tornado_FlightTick_L_800F98AC
    cmpwi r0, 0x0
    bge Tornado_FlightTick_L_800F98B8
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F98AC:
    cmpwi r0, 0x3
    bge Tornado_FlightTick_L_800F9CFC
    b Tornado_FlightTick_L_800F9974
    Tornado_FlightTick_L_800F98B8:
    lfs f0, lbl_806D6268(r2)
    stfs f0, 0x18(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    Tornado_FlightTick_L_800F98CC:
    lfs f2, 0x2c(r27)
    lfs f1, lbl_806D626C(r2)
    lfs f0, lbl_806D6264(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r27)
    lfs f1, 0x2c(r27)
    fcmpo cr0, f1, f0
    bge Tornado_FlightTick_L_800F9908
    stfs f0, 0x2c(r27)
    li r0, 0x78
    stw r0, 0x4(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9908:
    addi r3, r27, 0xb8
    lfs f1, lbl_806D6270(r2)
    mr r4, r3
    bl Vec3_Scale
    lfs f1, lbl_806D6264(r2)
    mr r3, r27
    li r4, 0x0
    li r5, 0x0
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq Tornado_FlightTick_L_800F9948
    lfs f1, 0xbc(r27)
    lfs f0, lbl_806D6274(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r27)
    b Tornado_FlightTick_L_800F9950
    Tornado_FlightTick_L_800F9948:
    lfs f0, lbl_806D6264(r2)
    stfs f0, 0xbc(r27)
    Tornado_FlightTick_L_800F9950:
    lfs f1, 0x18(r29)
    lfs f0, lbl_806D6278(r2)
    fmuls f0, f1, f0
    stfs f0, 0x18(r29)
    lfs f1, 0x20(r29)
    lfs f0, 0x18(r29)
    fadds f0, f1, f0
    stfs f0, 0x20(r29)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9974:
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    bne Tornado_FlightTick_L_800F9CFC
    li r3, 0x3
    li r0, 0x0
    stb r3, 0xc8(r27)
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    lbz r0, 0xc9(r27)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Tornado_FlightTick_L_800F99D4
    bge Tornado_FlightTick_L_800F99B4
    cmpwi r0, 0x0
    bge Tornado_FlightTick_L_800F99C0
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F99B4:
    cmpwi r0, 0x3
    bge Tornado_FlightTick_L_800F9CFC
    b Tornado_FlightTick_L_800F9A7C
    Tornado_FlightTick_L_800F99C0:
    lfs f0, lbl_806D6268(r2)
    stfs f0, 0x18(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    Tornado_FlightTick_L_800F99D4:
    lfs f2, 0x2c(r27)
    lfs f1, lbl_806D626C(r2)
    lfs f0, lbl_806D6264(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r27)
    lfs f1, 0x2c(r27)
    fcmpo cr0, f1, f0
    bge Tornado_FlightTick_L_800F9A10
    stfs f0, 0x2c(r27)
    li r0, 0x78
    stw r0, 0x4(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9A10:
    addi r3, r27, 0xb8
    lfs f1, lbl_806D6270(r2)
    mr r4, r3
    bl Vec3_Scale
    lfs f1, lbl_806D6264(r2)
    mr r3, r27
    li r4, 0x0
    li r5, 0x0
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq Tornado_FlightTick_L_800F9A50
    lfs f1, 0xbc(r27)
    lfs f0, lbl_806D6274(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r27)
    b Tornado_FlightTick_L_800F9A58
    Tornado_FlightTick_L_800F9A50:
    lfs f0, lbl_806D6264(r2)
    stfs f0, 0xbc(r27)
    Tornado_FlightTick_L_800F9A58:
    lfs f1, 0x18(r29)
    lfs f0, lbl_806D6278(r2)
    fmuls f0, f1, f0
    stfs f0, 0x18(r29)
    lfs f1, 0x20(r29)
    lfs f0, 0x18(r29)
    fadds f0, f1, f0
    stfs f0, 0x20(r29)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9A7C:
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    bne Tornado_FlightTick_L_800F9CFC
    li r3, 0x3
    li r0, 0x0
    stb r3, 0xc8(r27)
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    lbz r0, 0xc9(r27)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Tornado_FlightTick_L_800F9ADC
    bge Tornado_FlightTick_L_800F9ABC
    cmpwi r0, 0x0
    bge Tornado_FlightTick_L_800F9AC8
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9ABC:
    cmpwi r0, 0x3
    bge Tornado_FlightTick_L_800F9CFC
    b Tornado_FlightTick_L_800F9B84
    Tornado_FlightTick_L_800F9AC8:
    lfs f0, lbl_806D6268(r2)
    stfs f0, 0x18(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    Tornado_FlightTick_L_800F9ADC:
    lfs f2, 0x2c(r27)
    lfs f1, lbl_806D626C(r2)
    lfs f0, lbl_806D6264(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r27)
    lfs f1, 0x2c(r27)
    fcmpo cr0, f1, f0
    bge Tornado_FlightTick_L_800F9B18
    stfs f0, 0x2c(r27)
    li r0, 0x78
    stw r0, 0x4(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9B18:
    addi r3, r27, 0xb8
    lfs f1, lbl_806D6270(r2)
    mr r4, r3
    bl Vec3_Scale
    lfs f1, lbl_806D6264(r2)
    mr r3, r27
    li r4, 0x0
    li r5, 0x0
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq Tornado_FlightTick_L_800F9B58
    lfs f1, 0xbc(r27)
    lfs f0, lbl_806D6274(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r27)
    b Tornado_FlightTick_L_800F9B60
    Tornado_FlightTick_L_800F9B58:
    lfs f0, lbl_806D6264(r2)
    stfs f0, 0xbc(r27)
    Tornado_FlightTick_L_800F9B60:
    lfs f1, 0x18(r29)
    lfs f0, lbl_806D6278(r2)
    fmuls f0, f1, f0
    stfs f0, 0x18(r29)
    lfs f1, 0x20(r29)
    lfs f0, 0x18(r29)
    fadds f0, f1, f0
    stfs f0, 0x20(r29)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9B84:
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    bne Tornado_FlightTick_L_800F9CFC
    li r3, 0x3
    li r0, 0x0
    stb r3, 0xc8(r27)
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    lbz r0, 0xc9(r27)
    extsb r0, r0
    cmpwi r0, 0x1
    beq Tornado_FlightTick_L_800F9BE4
    bge Tornado_FlightTick_L_800F9BC4
    cmpwi r0, 0x0
    bge Tornado_FlightTick_L_800F9BD0
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9BC4:
    cmpwi r0, 0x3
    bge Tornado_FlightTick_L_800F9CFC
    b Tornado_FlightTick_L_800F9C8C
    Tornado_FlightTick_L_800F9BD0:
    lfs f0, lbl_806D6268(r2)
    stfs f0, 0x18(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    Tornado_FlightTick_L_800F9BE4:
    lfs f2, 0x2c(r27)
    lfs f1, lbl_806D626C(r2)
    lfs f0, lbl_806D6264(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r27)
    lfs f1, 0x2c(r27)
    fcmpo cr0, f1, f0
    bge Tornado_FlightTick_L_800F9C20
    stfs f0, 0x2c(r27)
    li r0, 0x78
    stw r0, 0x4(r29)
    lbz r3, 0xc9(r27)
    addi r0, r3, 0x1
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9C20:
    addi r3, r27, 0xb8
    lfs f1, lbl_806D6270(r2)
    mr r4, r3
    bl Vec3_Scale
    lfs f1, lbl_806D6264(r2)
    mr r3, r27
    li r4, 0x0
    li r5, 0x0
    bl Item_AdvanceFallingDrop
    cmpwi r3, 0x0
    beq Tornado_FlightTick_L_800F9C60
    lfs f1, 0xbc(r27)
    lfs f0, lbl_806D6274(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r27)
    b Tornado_FlightTick_L_800F9C68
    Tornado_FlightTick_L_800F9C60:
    lfs f0, lbl_806D6264(r2)
    stfs f0, 0xbc(r27)
    Tornado_FlightTick_L_800F9C68:
    lfs f1, 0x18(r29)
    lfs f0, lbl_806D6278(r2)
    fmuls f0, f1, f0
    stfs f0, 0x18(r29)
    lfs f1, 0x20(r29)
    lfs f0, 0x18(r29)
    fadds f0, f1, f0
    stfs f0, 0x20(r29)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9C8C:
    lwz r0, 0x4(r29)
    cmplwi r0, 0x0
    bne Tornado_FlightTick_L_800F9CFC
    li r3, 0x3
    li r0, 0x0
    stb r3, 0xc8(r27)
    stb r0, 0xc9(r27)
    b Tornado_FlightTick_L_800F9CFC
    Tornado_FlightTick_L_800F9CAC:
    li r31, 0x0
    mr r30, r29
    mr r28, r31
    Tornado_FlightTick_L_800F9CB8:
    lwz r3, 0x5c(r30)
    bl SpriteSlot_Container_Free
    addi r31, r31, 0x1
    stw r28, 0x5c(r30)
    cmpwi r31, 0x3
    addi r30, r30, 0x4
    blt Tornado_FlightTick_L_800F9CB8
    lwz r4, 0x30(r29)
    cmpwi r4, 0x0
    blt Tornado_FlightTick_L_800F9CF0
    li r3, 0x82
    bl SoundMgr_StopSE_OrSpecial
    li r0, -0x1
    stw r0, 0x30(r29)
    Tornado_FlightTick_L_800F9CF0:
    mr r3, r27
    bl SpriteSlot_Container_Free
    b Tornado_FlightTick_L_800F9FB8
    Tornado_FlightTick_L_800F9CFC:
    addi r3, r27, 0xa0
    addi r5, r27, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r5, 0x30(r29)
    cmpwi r5, 0x0
    bge Tornado_FlightTick_L_800F9D58
    li r3, 0x82
    bl SoundMgr_CountActiveSEInstances
    stw r3, 0x30(r29)
    lwz r5, 0x30(r29)
    cmpwi r5, 0x0
    blt Tornado_FlightTick_L_800F9D7C
    lwz r6, 0xa0(r27)
    addi r4, r1, 0x2c
    lwz r0, 0xa4(r27)
    li r3, 0x82
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r27)
    stw r0, 0x34(r1)
    bl SoundMgr_PlaySE_Positional
    b Tornado_FlightTick_L_800F9D7C
    Tornado_FlightTick_L_800F9D58:
    lwz r6, 0xa0(r27)
    addi r4, r1, 0x20
    lwz r0, 0xa4(r27)
    li r3, 0x82
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r27)
    stw r0, 0x28(r1)
    bl SoundMgr_PlaySE_WithChannel
    Tornado_FlightTick_L_800F9D7C:
    lfs f2, 0x1c(r29)
    lfs f0, lbl_806D6290(r2)
    lfs f1, lbl_806D6260(r2)
    fadds f0, f2, f0
    stfs f0, 0x1c(r29)
    lfs f0, 0x1c(r29)
    fcmpo cr0, f1, f0
    bge Tornado_FlightTick_L_800F9DA4
    fsubs f0, f0, f1
    stfs f0, 0x1c(r29)
    Tornado_FlightTick_L_800F9DA4:
    li r31, 0x0
    mr r30, r29
    Tornado_FlightTick_L_800F9DAC:
    lwz r3, 0x5c(r30)
    cmplwi r3, 0x0
    beq Tornado_FlightTick_L_800F9F58
    addi r3, r3, 0xa0
    addi r4, r27, 0xa0
    bl Vec3_Copy
    lwz r6, 0x5c(r30)
    addi r4, r1, 0x14
    lwz r5, 0xa0(r6)
    addi r3, r6, 0x14
    lwz r0, 0xa4(r6)
    stw r5, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r6)
    stw r0, 0x1c(r1)
    bl SpriteSlot_SetPositionFromVec
    cmpwi r31, 0x2
    lfs f31, 0x1c(r29)
    bne Tornado_FlightTick_L_800F9E10
    lfs f1, lbl_806D6294(r2)
    lfs f0, lbl_806D6260(r2)
    fadds f31, f31, f1
    fcmpo cr0, f0, f31
    bge Tornado_FlightTick_L_800F9E10
    fsubs f31, f31, f0
    Tornado_FlightTick_L_800F9E10:
    lwz r3, 0x5c(r30)
    addi r4, r27, 0xac
    addi r3, r3, 0xac
    bl Vec3_Copy
    cmpwi r31, 0x1
    beq Tornado_FlightTick_L_800F9E64
    bge Tornado_FlightTick_L_800F9E38
    cmpwi r31, 0x0
    bge Tornado_FlightTick_L_800F9E44
    b Tornado_FlightTick_L_800F9EA0
    Tornado_FlightTick_L_800F9E38:
    cmpwi r31, 0x3
    bge Tornado_FlightTick_L_800F9EA0
    b Tornado_FlightTick_L_800F9E84
    Tornado_FlightTick_L_800F9E44:
    lwz r3, 0x5c(r30)
    lfs f1, lbl_806D6298(r2)
    lfs f0, 0xb0(r3)
    fmadds f1, f1, f31, f0
    bl BuildOrientationFromYaw
    lwz r3, 0x5c(r30)
    stfs f1, 0xb0(r3)
    b Tornado_FlightTick_L_800F9EA0
    Tornado_FlightTick_L_800F9E64:
    lwz r3, 0x5c(r30)
    lfs f1, lbl_806D629C(r2)
    lfs f0, 0xb0(r3)
    fmadds f1, f1, f31, f0
    bl BuildOrientationFromYaw
    lwz r3, 0x5c(r30)
    stfs f1, 0xb0(r3)
    b Tornado_FlightTick_L_800F9EA0
    Tornado_FlightTick_L_800F9E84:
    lwz r3, 0x5c(r30)
    lfs f1, lbl_806D629C(r2)
    lfs f0, 0xb0(r3)
    fmadds f1, f1, f31, f0
    bl BuildOrientationFromYaw
    lwz r3, 0x5c(r30)
    stfs f1, 0xb0(r3)
    Tornado_FlightTick_L_800F9EA0:
    lwz r6, 0x5c(r30)
    addi r4, r1, 0x8
    lwz r5, 0xac(r6)
    addi r3, r6, 0x14
    lwz r0, 0xb0(r6)
    stw r5, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xb4(r6)
    stw r0, 0x10(r1)
    bl SpriteSlot_SetRotationQuatFromVec
    lfs f0, 0xc4(r27)
    cmpwi r31, 0x0
    lwz r3, 0x5c(r30)
    stfs f0, 0xc4(r3)
    lwz r3, 0x5c(r30)
    lfs f0, 0x20(r29)
    lfs f2, 0xc4(r3)
    fmuls f3, f2, f0
    beq Tornado_FlightTick_L_800F9EFC
    lfs f1, lbl_806D6278(r2)
    lfs f0, lbl_806D6268(r2)
    fmadds f0, f1, f31, f0
    fmuls f2, f2, f0
    Tornado_FlightTick_L_800F9EFC:
    fmr f1, f3
    addi r3, r3, 0x14
    bl SpriteSlot_SetScaleXYZ
    lfs f0, 0x2c(r27)
    cmpwi r31, 0x0
    lwz r3, 0x5c(r30)
    stfs f0, 0x2c(r3)
    beq Tornado_FlightTick_L_800F9F58
    lfs f1, lbl_806D62A8(r2)
    lfs f0, lbl_806D62A4(r2)
    lfs f2, lbl_806D62A0(r2)
    fmadds f0, f1, f31, f0
    fmuls f1, f2, f0
    bl fn_8027E9E8
    frsp f2, f1
    lfs f1, lbl_806D6260(r2)
    lwz r3, 0x5c(r30)
    lfs f0, lbl_806D6294(r2)
    fadds f1, f1, f2
    lfs f2, 0x2c(r3)
    fmuls f0, f1, f0
    fmuls f0, f2, f0
    stfs f0, 0x2c(r3)
    Tornado_FlightTick_L_800F9F58:
    addi r31, r31, 0x1
    addi r30, r30, 0x4
    cmpwi r31, 0x3
    blt Tornado_FlightTick_L_800F9DAC
    lwz r3, 0x4(r29)
    cmplwi r3, 0x0
    beq Tornado_FlightTick_L_800F9F7C
    subi r0, r3, 0x1
    stw r0, 0x4(r29)
    Tornado_FlightTick_L_800F9F7C:
    lwz r3, 0x8(r29)
    cmplwi r3, 0x0
    beq Tornado_FlightTick_L_800F9F90
    subi r0, r3, 0x1
    stw r0, 0x8(r29)
    Tornado_FlightTick_L_800F9F90:
    lwz r3, 0xc(r29)
    cmplwi r3, 0x0
    beq Tornado_FlightTick_L_800F9FA4
    subi r0, r3, 0x1
    stw r0, 0xc(r29)
    Tornado_FlightTick_L_800F9FA4:
    lwz r3, 0x10(r29)
    cmplwi r3, 0x0
    beq Tornado_FlightTick_L_800F9FB8
    subi r0, r3, 0x1
    stw r0, 0x10(r29)
    Tornado_FlightTick_L_800F9FB8:
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    lmw r27, 0x3c(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

