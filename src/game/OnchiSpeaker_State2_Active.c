/* === extracted from auto_OnchiSpeaker_State2_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void BuildOrientationFromYaw();
extern void DrawEffect_Free();
extern void DrawEffect_SpawnDirect();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition();
extern void Item_DecayVelocityScalar();
extern void JointByName_GetWorldPosition();
extern void KartDriver_GetKartRootMtx();
extern void KartFxParam_GetConst1p5();
extern void Mtx44_GetTranslation_ColMajor();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_TransformVec3();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetScale();
extern void Vec2_RotateY();
extern void Vec3_Add_DestFirst();
extern void Vec3_HorizontalYawTo();
extern void Vec3_Lerp();
extern void Vec3_Subtract_DestFirst();
extern void fn_8027E9E8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5F18;
extern unsigned int lbl_806D5F1C;
extern unsigned int lbl_806D5F2C;
extern unsigned int lbl_806D5F30;
extern unsigned int lbl_806D5F34;
extern unsigned int lbl_806D5F38;
extern unsigned int lbl_806D5F3C;
extern unsigned int lbl_806D5F40;
extern unsigned int lbl_806D5F44;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int DrawEffect_Cb_KartWheelSmokeOrbital_Tick[];
extern unsigned int DrawEffect_Cb_UVScroll_Tick[];
extern unsigned int lbl_8032F4F8[];
extern unsigned int lbl_8032F504[];

/* --- function index (1 fns, .text 0x800EE120..0x800EE620) ---
 * [  0] 0x800EE120 size:0x500   global OnchiSpeaker_State2_Active
 */

/* --- forward decls --- */
asm void OnchiSpeaker_State2_Active(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_OnchiSpeaker_State2_Active[8] = {
    0x18, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_OnchiSpeaker_State2_Active = {
    (void *)&OnchiSpeaker_State2_Active, 0x00000500, (void *)extab_OnchiSpeaker_State2_Active
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void OnchiSpeaker_State2_Active(void) { /* 0x800EE120 size:0x500 */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    stw r29, 0x94(r1)
    mr r30, r3
    mr r31, r4
    lbz r3, 0xc9(r3)
    extsb r0, r3
    cmpwi r0, 0x1
    beq OnchiSpeaker_State2_Active_L_800EE184
    bge OnchiSpeaker_State2_Active_L_800EE168
    cmpwi r0, 0x0
    bge OnchiSpeaker_State2_Active_L_800EE174
    b OnchiSpeaker_State2_Active_L_800EE5FC
    OnchiSpeaker_State2_Active_L_800EE168:
    cmpwi r0, 0x3
    bge OnchiSpeaker_State2_Active_L_800EE5FC
    b OnchiSpeaker_State2_Active_L_800EE4E8
    OnchiSpeaker_State2_Active_L_800EE174:
    addi r3, r3, 0x1
    li r0, 0x0
    stb r3, 0xc9(r30)
    stb r0, 0xca(r30)
    OnchiSpeaker_State2_Active_L_800EE184:
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq OnchiSpeaker_State2_Active_L_800EE234
    bge OnchiSpeaker_State2_Active_L_800EE234
    cmpwi r0, 0x0
    bge OnchiSpeaker_State2_Active_L_800EE1A4
    b OnchiSpeaker_State2_Active_L_800EE234
    OnchiSpeaker_State2_Active_L_800EE1A4:
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0x14
    li r4, 0x2
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5F1C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r5, 0x0
    lis r3, DrawEffect_Cb_UVScroll_Tick@ha
    stb r5, 0x3c(r30)
    li r4, 0x708
    lfs f0, lbl_806D5F18(r2)
    li r0, 0xa
    addi r3, r3, DrawEffect_Cb_UVScroll_Tick@l
    stfs f0, 0x14(r31)
    stfs f0, 0x18(r31)
    stw r4, 0x4(r31)
    stw r0, 0x8(r31)
    stw r5, 0xc(r31)
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r31)
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq OnchiSpeaker_State2_Active_L_800EE228
    lwz r0, 0x9c(r31)
    stw r0, 0x11c(r3)
    lwz r3, 0x4c(r31)
    stw r30, 0xcc(r3)
    OnchiSpeaker_State2_Active_L_800EE228:
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    OnchiSpeaker_State2_Active_L_800EE234:
    lwz r3, 0x9c(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq OnchiSpeaker_State2_Active_L_800EE250
    li r0, 0x0
    stb r0, 0x28(r30)
    b OnchiSpeaker_State2_Active_L_800EE258
    OnchiSpeaker_State2_Active_L_800EE250:
    li r0, 0x1
    stb r0, 0x28(r30)
    OnchiSpeaker_State2_Active_L_800EE258:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne OnchiSpeaker_State2_Active_L_800EE2AC
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5F2C(r2)
    lfs f0, lbl_806D5F18(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge OnchiSpeaker_State2_Active_L_800EE2F0
    li r0, 0x0
    stb r0, 0x28(r30)
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r3, 0x0
    li r0, 0x3
    stw r3, 0x4c(r31)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b OnchiSpeaker_State2_Active_L_800EE5FC
    OnchiSpeaker_State2_Active_L_800EE2AC:
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    bne OnchiSpeaker_State2_Active_L_800EE2F0
    lis r3, DrawEffect_Cb_KartWheelSmokeOrbital_Tick@ha
    addi r3, r3, DrawEffect_Cb_KartWheelSmokeOrbital_Tick@l
    bl DrawEffect_SpawnDirect
    mr. r29, r3
    beq OnchiSpeaker_State2_Active_L_800EE2E8
    lis r4, lbl_8032F504@ha
    addi r3, r29, 0x8c
    addi r5, r4, lbl_8032F504@l
    addi r4, r30, 0x14
    bl JointByName_GetWorldPosition
    lwz r0, 0x9c(r31)
    stw r0, 0x11c(r29)
    OnchiSpeaker_State2_Active_L_800EE2E8:
    li r0, 0xa
    stw r0, 0xc(r31)
    OnchiSpeaker_State2_Active_L_800EE2F0:
    lwz r3, 0x9c(r31)
    bl KartFxParam_GetConst1p5
    lfs f0, lbl_806D5F30(r2)
    mr r3, r30
    fmuls f1, f0, f1
    bl Item_DecayVelocityScalar
    lfs f2, 0x14(r31)
    lfs f0, lbl_806D5F2C(r2)
    lfs f1, lbl_806D5F1C(r2)
    fadds f0, f2, f0
    stfs f0, 0x14(r31)
    lfs f0, 0x14(r31)
    fcmpo cr0, f1, f0
    bge OnchiSpeaker_State2_Active_L_800EE32C
    stfs f1, 0x14(r31)
    OnchiSpeaker_State2_Active_L_800EE32C:
    lfs f1, lbl_806D5F34(r2)
    lfs f0, 0x18(r31)
    fadds f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0x18(r31)
    lwz r3, 0x9c(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x50
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x44
    addi r4, r1, 0x50
    bl Mtx44_GetTranslation_ColMajor
    lis r3, lbl_8032F4F8@ha
    addi r5, r3, lbl_8032F4F8@l
    lwz r4, 0x0(r5)
    lwz r3, 0x4(r5)
    lwz r0, 0x8(r5)
    stw r4, 0x38(r1)
    stw r3, 0x3c(r1)
    stw r0, 0x40(r1)
    lfs f1, 0x18(r31)
    bl fn_8027E9E8
    frsp f1, f1
    lfs f0, lbl_806D5F38(r2)
    addi r3, r1, 0x38
    mr r4, r3
    fmuls f1, f0, f1
    bl Vec2_RotateY
    lwz r7, 0x38(r1)
    addi r3, r1, 0x38
    lwz r6, 0x3c(r1)
    addi r4, r1, 0x50
    lwz r0, 0x40(r1)
    addi r5, r1, 0x20
    stw r7, 0x20(r1)
    stw r6, 0x24(r1)
    stw r0, 0x28(r1)
    bl Mtx44_TransformVec3
    addi r3, r30, 0xa0
    addi r4, r1, 0x44
    bl Vec3_HorizontalYawTo
    lwz r5, 0xa0(r30)
    fmr f31, f1
    lwz r0, 0xa4(r30)
    addi r3, r30, 0xa0
    lwz r7, 0x38(r1)
    addi r4, r1, 0x14
    stw r5, 0x8(r1)
    lwz r6, 0x3c(r1)
    addi r5, r1, 0x8
    stw r0, 0xc(r1)
    lwz r0, 0x40(r1)
    lwz r8, 0xa8(r30)
    stw r8, 0x10(r1)
    stw r7, 0x14(r1)
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    lfs f1, 0x14(r31)
    bl Vec3_Lerp
    lfs f3, 0x14(r31)
    lfs f0, lbl_806D5F1C(r2)
    lfs f1, 0xac(r30)
    fsubs f0, f0, f3
    lfs f2, lbl_806D5F18(r2)
    fmuls f0, f1, f0
    fmadds f1, f2, f3, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lfs f0, lbl_806D5F1C(r2)
    lfs f2, 0x14(r31)
    lfs f1, 0xb0(r30)
    fsubs f0, f0, f2
    fmuls f0, f1, f0
    fmadds f1, f31, f2, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xb0(r30)
    lwz r0, 0x8(r31)
    cmplwi r0, 0x0
    bne OnchiSpeaker_State2_Active_L_800EE5FC
    lwz r5, 0x9c(r31)
    lis r3, 0x200
    li r4, 0x0
    lwz r6, 0x304(r5)
    lwz r0, 0x10(r6)
    lwz r5, 0x14(r6)
    and r0, r0, r4
    and r3, r5, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne OnchiSpeaker_State2_Active_L_800EE4A0
    stw r4, 0x4(r31)
    OnchiSpeaker_State2_Active_L_800EE4A0:
    lwz r0, 0x10(r6)
    li r4, 0x0
    lwz r5, 0x14(r6)
    lis r3, 0x1
    and r0, r0, r4
    and r3, r5, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    beq OnchiSpeaker_State2_Active_L_800EE5FC
    lwz r3, 0x4c(r31)
    bl DrawEffect_Free
    li r3, 0x0
    li r0, 0x2
    stw r3, 0x4c(r31)
    stb r0, 0xc9(r30)
    stb r3, 0xca(r30)
    b OnchiSpeaker_State2_Active_L_800EE5FC
    OnchiSpeaker_State2_Active_L_800EE4E8:
    lwz r3, 0x9c(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x2c
    bl Mtx44_GetTranslation_RowMajor
    lbz r0, 0xca(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq OnchiSpeaker_State2_Active_L_800EE568
    bge OnchiSpeaker_State2_Active_L_800EE568
    cmpwi r0, 0x0
    bge OnchiSpeaker_State2_Active_L_800EE51C
    b OnchiSpeaker_State2_Active_L_800EE568
    OnchiSpeaker_State2_Active_L_800EE51C:
    lfs f1, lbl_806D5F18(r2)
    addi r3, r30, 0x14
    li r4, 0x0
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lfs f1, lbl_806D5F1C(r2)
    addi r3, r30, 0x14
    bl SpriteSlot_SetScale
    addi r3, r31, 0x34
    addi r4, r30, 0xa0
    addi r5, r1, 0x2c
    bl Vec3_Subtract_DestFirst
    lfs f1, lbl_806D5F18(r2)
    addi r3, r31, 0x40
    lfs f2, lbl_806D5F3C(r2)
    fmr f3, f1
    bl GetSpawnPosition
    lbz r3, 0xca(r30)
    addi r0, r3, 0x1
    stb r0, 0xca(r30)
    OnchiSpeaker_State2_Active_L_800EE568:
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D5F2C(r2)
    lfs f0, lbl_806D5F18(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge OnchiSpeaker_State2_Active_L_800EE5A0
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b OnchiSpeaker_State2_Active_L_800EE5FC
    OnchiSpeaker_State2_Active_L_800EE5A0:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D5F40(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    lwz r3, 0x9c(r31)
    bl KartFxParam_GetConst1p5
    lfs f0, lbl_806D5F30(r2)
    mr r3, r30
    fmuls f1, f0, f1
    bl Item_DecayVelocityScalar
    lfs f1, 0x44(r31)
    addi r3, r31, 0x34
    lfs f0, lbl_806D5F44(r2)
    mr r4, r3
    addi r5, r31, 0x40
    fadds f0, f1, f0
    stfs f0, 0x44(r31)
    bl Vec3_Add_DestFirst
    addi r3, r30, 0xa0
    addi r4, r1, 0x2c
    addi r5, r31, 0x34
    bl Vec3_Add_DestFirst
    OnchiSpeaker_State2_Active_L_800EE5FC:
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

