/* === extracted from auto_OnchiSpeaker_State2_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void GetSpawnPosition();
extern void ItemObject_GetGroundTypeAt();
extern void Item_DecayVelocityScalar();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_GetTranslation_RowMajor();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Subtract_DestFirst();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5F18;
extern unsigned int lbl_806D5F1C;
extern unsigned int lbl_806D5F20;
extern unsigned int lbl_806D5F2C;
extern unsigned int lbl_806D5F40;
extern unsigned int lbl_806D5F44;
extern unsigned int lbl_806D5F48;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_80421638[];

/* --- function index (1 fns, .text 0x800EE620..0x800EE8D8) ---
 * [  0] 0x800EE620 size:0x2B8   global OnchiSpeaker_State2_Flight
 */

/* --- forward decls --- */
asm void OnchiSpeaker_State2_Flight(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_OnchiSpeaker_State2_Flight[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_OnchiSpeaker_State2_Flight = {
    (void *)&OnchiSpeaker_State2_Flight, 0x000002B8, (void *)extab_OnchiSpeaker_State2_Flight
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void OnchiSpeaker_State2_Flight(void) { /* 0x800EE620 size:0x2B8 */
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
    beq OnchiSpeaker_State2_Flight_L_800EE72C
    bge OnchiSpeaker_State2_Flight_L_800EE72C
    cmpwi r0, 0x0
    bge OnchiSpeaker_State2_Flight_L_800EE65C
    b OnchiSpeaker_State2_Flight_L_800EE72C
    OnchiSpeaker_State2_Flight_L_800EE65C:
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5F1C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
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
    beq OnchiSpeaker_State2_Flight_L_800EE6B8
    li r0, 0xa
    stw r0, 0x4(r31)
    b OnchiSpeaker_State2_Flight_L_800EE6C0
    OnchiSpeaker_State2_Flight_L_800EE6B8:
    li r0, 0x0
    stw r0, 0x4(r31)
    OnchiSpeaker_State2_Flight_L_800EE6C0:
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    bne OnchiSpeaker_State2_Flight_L_800EE6D4
    lfs f0, lbl_806D5F18(r2)
    stfs f0, 0xbc(r30)
    OnchiSpeaker_State2_Flight_L_800EE6D4:
    lwz r3, 0x9c(r31)
    cmplwi r3, 0x0
    beq OnchiSpeaker_State2_Flight_L_800EE720
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
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    OnchiSpeaker_State2_Flight_L_800EE720:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    OnchiSpeaker_State2_Flight_L_800EE72C:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne OnchiSpeaker_State2_Flight_L_800EE770
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5F2C(r2)
    lfs f0, lbl_806D5F18(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge OnchiSpeaker_State2_Flight_L_800EE770
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b OnchiSpeaker_State2_Flight_L_800EE8C0
    OnchiSpeaker_State2_Flight_L_800EE770:
    lfs f1, lbl_806D5F20(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmplwi r0, 0x9
    bgt OnchiSpeaker_State2_Flight_L_800EE800
    lis r3, jumptable_80421638@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_80421638@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D5F40(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b OnchiSpeaker_State2_Flight_L_800EE800
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D5F40(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b OnchiSpeaker_State2_Flight_L_800EE800
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D5F40(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b OnchiSpeaker_State2_Flight_L_800EE800
    lfs f1, lbl_806D5F48(r2)
    lfs f0, 0xac(r30)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    OnchiSpeaker_State2_Flight_L_800EE800:
    lwz r0, 0x9c(r31)
    cmplwi r0, 0x0
    bne OnchiSpeaker_State2_Flight_L_800EE87C
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq OnchiSpeaker_State2_Flight_L_800EE828
    lfs f1, 0xbc(r30)
    lfs f0, lbl_806D5F44(r2)
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    OnchiSpeaker_State2_Flight_L_800EE828:
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
    beq OnchiSpeaker_State2_Flight_L_800EE8C0
    lfs f1, 0x8(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stfs f0, 0x14(r31)
    b OnchiSpeaker_State2_Flight_L_800EE8C0
    OnchiSpeaker_State2_Flight_L_800EE87C:
    lfs f1, 0x44(r31)
    addi r3, r31, 0x34
    lfs f0, lbl_806D5F44(r2)
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
    OnchiSpeaker_State2_Flight_L_800EE8C0:
    lwz r0, 0x54(r1)
    lwz r31, 0x4c(r1)
    lwz r30, 0x48(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

