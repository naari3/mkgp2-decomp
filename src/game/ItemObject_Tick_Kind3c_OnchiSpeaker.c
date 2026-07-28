/* === extracted from auto_ItemObject_Tick_Kind_text_9 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_KartImpactRing_AdvanceByVfxDelta();
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void Item_OrbitAnchorKart();
extern void OnchiSpeaker_State1_Held();
extern void OnchiSpeaker_State2_Active();
extern void OnchiSpeaker_State2_Flight();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();
extern void SpriteSlot_SetTransform();
extern void SpriteSlot_TickAnim();
extern void Vec3_Add_DestFirst();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5F18;
extern unsigned int lbl_806D5F1C;
extern unsigned int lbl_806D5F20;
extern unsigned int lbl_806D5F24;
extern unsigned int lbl_806D5F28;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_80421660[];

/* --- function index (1 fns, .text 0x800EEF34..0x800EF2DC) ---
 * [  0] 0x800EEF34 size:0x3A8   global ItemObject_Tick_Kind3c_OnchiSpeaker
 */

/* --- forward decls --- */
asm void ItemObject_Tick_Kind3c_OnchiSpeaker(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemObject_Tick_Kind3c_OnchiSpeaker[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemObject_Tick_Kind3c_OnchiSpeaker = {
    (void *)&ItemObject_Tick_Kind3c_OnchiSpeaker, 0x000003A8, (void *)extab_ItemObject_Tick_Kind3c_OnchiSpeaker
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemObject_Tick_Kind3c_OnchiSpeaker(void) { /* 0x800EEF34 size:0x3A8 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEFC0
    bge ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEF74
    cmpwi r0, 0x0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEF80
    bge ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEFB0
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEF74:
    cmpwi r0, 0x4
    bge ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1A0
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEF80:
    addi r3, r30, 0x14
    li r4, 0x40
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
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEFB0:
    mr r3, r30
    mr r4, r31
    bl OnchiSpeaker_State1_Held
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EEFC0:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    lis r4, jumptable_80421660@ha
    slwi r0, r0, 2
    addi r4, r4, jumptable_80421660@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    mr r4, r31
    bl OnchiSpeaker_State2_Active
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    mr r4, r31
    bl OnchiSpeaker_State2_Flight
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF074
    bge ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF074
    cmpwi r0, 0x0
    bge ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF020
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF074
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF020:
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f1, lbl_806D5F18(r2)
    stb r0, 0x3c(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5F1C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    lfs f0, lbl_806D5F18(r2)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF074:
    lfs f2, lbl_806D5F28(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    mr r4, r31
    bl OnchiSpeaker_State2_Flight
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF138
    bge ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF138
    cmpwi r0, 0x0
    bge ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF0D8
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF138
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF0D8:
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f1, lbl_806D5F18(r2)
    stb r0, 0x3c(r30)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5F1C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    lwz r5, 0x9c(r30)
    addi r3, r31, 0x34
    addi r4, r30, 0xa0
    addi r5, r5, 0xa0
    bl Vec3_Subtract_DestFirst
    li r0, 0x1e
    stw r0, 0x4(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF138:
    lfs f1, lbl_806D5F20(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lfs f1, lbl_806D5F24(r2)
    mr r3, r30
    lwz r5, 0x4(r31)
    addi r4, r31, 0x34
    fmr f2, f1
    bl Item_OrbitAnchorKart
    cmpwi r3, 0x0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    mr r4, r31
    bl OnchiSpeaker_State2_Flight
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    mr r4, r31
    bl OnchiSpeaker_State2_Flight
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    mr r4, r31
    bl OnchiSpeaker_State2_Flight
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1A0:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF2C4
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF1B0:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r6, 0xac(r30)
    addi r3, r30, 0x14
    lwz r0, 0xb0(r30)
    addi r4, r1, 0x2c
    addi r5, r1, 0x20
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xb4(r30)
    stw r0, 0x28(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x2c(r1)
    stw r0, 0x30(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x34(r1)
    lfs f1, 0xc4(r30)
    bl SpriteSlot_SetTransform
    addi r3, r30, 0x14
    bl SpriteSlot_TickAnim
    lbz r0, 0x28(r30)
    extsb. r0, r0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF248
    lwz r3, 0xa0(r30)
    addi r4, r1, 0x14
    lwz r0, 0xa4(r30)
    stw r3, 0x14(r1)
    stw r0, 0x18(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x1c(r1)
    lwz r3, 0x4c(r31)
    lfs f1, 0xc4(r30)
    lfs f2, 0x2c(r30)
    bl DrawEffect_KartImpactRing_AdvanceByVfxDelta
    b ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF274
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF248:
    lwz r3, 0xa0(r30)
    addi r4, r1, 0x8
    lwz r0, 0xa4(r30)
    lfs f2, lbl_806D5F18(r2)
    stw r3, 0x8(r1)
    stw r0, 0xc(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x10(r1)
    lwz r3, 0x4c(r31)
    lfs f1, 0xc4(r30)
    bl DrawEffect_KartImpactRing_AdvanceByVfxDelta
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF274:
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF288
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF288:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF29C
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF29C:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF2B0
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF2B0:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF2C4
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    ItemObject_Tick_Kind3c_OnchiSpeaker_L_800EF2C4:
    lwz r0, 0x44(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

