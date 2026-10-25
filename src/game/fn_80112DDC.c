extern void DrawEffect_SpawnDirect();
extern void Effect_SparkSpray_PlaceChildren();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void Item_RenderHandheldByCharacter();
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_Inverse_GaussJordan();
extern void Mtx44_TransformVec3();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern void SpriteSlot_SetTransform();
extern void Vec3_Add_DestFirst();
extern void fn_80112BE4();
extern unsigned int lbl_806CF3E8;
extern unsigned int lbl_806CF3EC;
extern unsigned int lbl_806CF3F0;
extern unsigned int lbl_806D69A8;
extern unsigned int lbl_806D69BC;
extern unsigned int Effect_SparkSprayCompound_Update[];
extern unsigned int lbl_80421DA0[];
asm void fn_80112DDC(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80112DDC[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80112DDC = {
    (void *)&fn_80112DDC, 0x00000338, (void *)extab_fn_80112DDC
};



asm void fn_80112DDC(void) { /* 0x80112DDC size:0x338 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    lis r4, lbl_80421DA0@ha
    stw r0, 0xc4(r1)
    stw r31, 0xbc(r1)
    addi r31, r4, lbl_80421DA0@l
    stw r30, 0xb8(r1)
    stw r29, 0xb4(r1)
    mr r29, r3
    addi r30, r29, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq fn_80112DDC_L_80112F78
    bge fn_80112DDC_L_80112E28
    cmpwi r0, 0x0
    beq fn_80112DDC_L_80112E34
    bge fn_80112DDC_L_80112E78
    b fn_80112DDC_L_80112FAC
    fn_80112DDC_L_80112E28:
    cmpwi r0, 0x4
    bge fn_80112DDC_L_80112FAC
    b fn_80112DDC_L_80112F84
    fn_80112DDC_L_80112E34:
    lwz r0, lbl_806CF3E8(r13)
    addi r3, r29, 0x14
    clrlwi r4, r0, 24
    bl SpriteSlot_InitNonLoop
    lfs f0, lbl_806D69A8(r2)
    lis r3, Effect_SparkSprayCompound_Update@ha
    addi r3, r3, Effect_SparkSprayCompound_Update@l
    stfs f0, 0x2c(r29)
    bl DrawEffect_SpawnDirect
    stw r3, 0x4c(r30)
    addi r3, r29, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r3, 0x1
    li r0, 0x0
    stb r3, 0xc8(r29)
    stb r0, 0xc9(r29)
    fn_80112DDC_L_80112E78:
    lwz r11, 0xc(r31)
    mr r3, r29
    lwz r10, 0x10(r31)
    addi r4, r1, 0x8
    lwz r9, 0x14(r31)
    addi r5, r1, 0x14
    lwz r8, 0x0(r31)
    li r6, 0x1
    lwz r7, 0x4(r31)
    lwz r0, 0x8(r31)
    stw r11, 0x14(r1)
    lfs f1, lbl_806CF3EC(r13)
    stw r10, 0x18(r1)
    stw r9, 0x1c(r1)
    stw r8, 0x8(r1)
    stw r7, 0xc(r1)
    stw r0, 0x10(r1)
    bl Item_RenderHandheldByCharacter
    lbz r0, 0xa0(r30)
    extsb r0, r0
    cmpwi r0, 0x2
    beq fn_80112DDC_L_80112F60
    bge fn_80112DDC_L_80112FAC
    cmpwi r0, 0x1
    bge fn_80112DDC_L_80112EE0
    b fn_80112DDC_L_80112FAC
    fn_80112DDC_L_80112EE0:
    li r0, 0x0
    addi r3, r29, 0x14
    stb r0, 0xa0(r30)
    li r4, 0x0
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    lfs f0, lbl_806D69BC(r2)
    stfs f0, 0x2c(r29)
    lwz r3, 0x98(r30)
    cmplwi r3, 0x0
    beq fn_80112DDC_L_80112F4C
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x68
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x68
    mr r4, r3
    bl Mtx44_Inverse_GaussJordan
    lwz r6, 0xa0(r29)
    addi r3, r30, 0x34
    lwz r0, 0xa4(r29)
    addi r4, r1, 0x68
    addi r5, r1, 0x20
    stw r6, 0x20(r1)
    stw r0, 0x24(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x28(r1)
    bl Mtx44_TransformVec3
    fn_80112DDC_L_80112F4C:
    li r3, 0x2
    li r0, 0x0
    stb r3, 0xc8(r29)
    stb r0, 0xc9(r29)
    b fn_80112DDC_L_80112FAC
    fn_80112DDC_L_80112F60:
    li r3, 0x0
    li r0, 0x3
    stb r3, 0xa0(r30)
    stb r0, 0xc8(r29)
    stb r3, 0xc9(r29)
    b fn_80112DDC_L_80112FAC
    fn_80112DDC_L_80112F78:
    mr r4, r30
    bl fn_80112BE4
    b fn_80112DDC_L_80112FAC
    fn_80112DDC_L_80112F84:
    lwz r3, 0x4c(r30)
    cmplwi r3, 0x0
    beq fn_80112DDC_L_80112F98
    li r0, 0x1
    stb r0, 0xc9(r3)
    fn_80112DDC_L_80112F98:
    li r0, 0x0
    mr r3, r29
    stw r0, 0x4c(r30)
    bl SpriteSlot_Container_Free
    b fn_80112DDC_L_801130F8
    fn_80112DDC_L_80112FAC:
    lwz r3, 0x98(r30)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq fn_80112DDC_L_80112FC8
    li r0, 0x0
    stb r0, 0x28(r29)
    b fn_80112DDC_L_80112FD0
    fn_80112DDC_L_80112FC8:
    li r0, 0x1
    stb r0, 0x28(r29)
    fn_80112DDC_L_80112FD0:
    lwz r6, 0xac(r29)
    addi r3, r29, 0x14
    lwz r0, 0xb0(r29)
    addi r4, r1, 0x50
    addi r5, r1, 0x44
    stw r6, 0x44(r1)
    stw r0, 0x48(r1)
    lwz r0, 0xb4(r29)
    stw r0, 0x4c(r1)
    lwz r6, 0xa0(r29)
    lwz r0, 0xa4(r29)
    stw r6, 0x50(r1)
    stw r0, 0x54(r1)
    lwz r0, 0xa8(r29)
    stw r0, 0x58(r1)
    lfs f1, 0xc4(r29)
    bl SpriteSlot_SetTransform
    lwz r0, 0x4c(r30)
    cmplwi r0, 0x0
    beq fn_80112DDC_L_801130A8
    addi r3, r1, 0x5c
    addi r4, r29, 0xa0
    addi r5, r31, 0x18
    bl Vec3_Add_DestFirst
    lbz r0, 0x28(r29)
    extsb. r0, r0
    beq fn_80112DDC_L_80113074
    lwz r5, 0x5c(r1)
    addi r4, r1, 0x38
    lwz r3, 0x60(r1)
    lwz r0, 0x64(r1)
    stw r5, 0x38(r1)
    lfs f0, lbl_806CF3F0(r13)
    stw r3, 0x3c(r1)
    stw r0, 0x40(r1)
    lfs f1, 0xc4(r29)
    lwz r3, 0x4c(r30)
    fmuls f1, f1, f0
    lfs f2, 0x2c(r29)
    bl Effect_SparkSpray_PlaceChildren
    b fn_80112DDC_L_801130A8
    fn_80112DDC_L_80113074:
    lwz r5, 0x5c(r1)
    addi r4, r1, 0x2c
    lwz r3, 0x60(r1)
    lwz r0, 0x64(r1)
    stw r5, 0x2c(r1)
    lfs f0, lbl_806CF3F0(r13)
    stw r3, 0x30(r1)
    lfs f2, lbl_806D69A8(r2)
    stw r0, 0x34(r1)
    lfs f1, 0xc4(r29)
    lwz r3, 0x4c(r30)
    fmuls f1, f1, f0
    bl Effect_SparkSpray_PlaceChildren
    fn_80112DDC_L_801130A8:
    lwz r3, 0x4(r30)
    cmplwi r3, 0x0
    beq fn_80112DDC_L_801130BC
    subi r0, r3, 0x1
    stw r0, 0x4(r30)
    fn_80112DDC_L_801130BC:
    lwz r3, 0x8(r30)
    cmplwi r3, 0x0
    beq fn_80112DDC_L_801130D0
    subi r0, r3, 0x1
    stw r0, 0x8(r30)
    fn_80112DDC_L_801130D0:
    lwz r3, 0xc(r30)
    cmplwi r3, 0x0
    beq fn_80112DDC_L_801130E4
    subi r0, r3, 0x1
    stw r0, 0xc(r30)
    fn_80112DDC_L_801130E4:
    lwz r3, 0x10(r30)
    cmplwi r3, 0x0
    beq fn_80112DDC_L_801130F8
    subi r0, r3, 0x1
    stw r0, 0x10(r30)
    fn_80112DDC_L_801130F8:
    lwz r0, 0xc4(r1)
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    lwz r29, 0xb4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}
