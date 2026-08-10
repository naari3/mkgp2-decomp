/* === extracted from auto_JumpDistanceMode_Pre_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CarObject_GetKartMovementPtr();
extern void CarObject_GetRenderObj();
extern void KartDriver_GetKartRootMtx();
extern void KartMovement_PhysicsStep();
extern void Terrain_RaycastWall();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void memcpy();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806DAD70;
extern unsigned int lbl_806DAD74;
extern unsigned int lbl_806DAD78;
extern unsigned int lbl_806DAD7C;
extern unsigned int lbl_806DAD80;
extern unsigned int lbl_806DAD84;
extern unsigned int lbl_806DAD88;
extern unsigned int lbl_806DAD8C;

/* --- function index (1 fns, .text 0x80210A50..0x80210CD4) ---
 * [  0] 0x80210A50 size:0x284   global JumpDistanceMode_PredictLanding
 */

/* --- forward decls --- */
asm void JumpDistanceMode_PredictLanding(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_JumpDistanceMode_PredictLanding[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_JumpDistanceMode_PredictLanding = {
    (void *)&JumpDistanceMode_PredictLanding, 0x00000284, (void *)extab_JumpDistanceMode_PredictLanding
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void JumpDistanceMode_PredictLanding(void) { /* 0x80210A50 size:0x284 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stw r31, 0x5c(r1)
    stw r30, 0x58(r1)
    stw r29, 0x54(r1)
    stw r28, 0x50(r1)
    mr r28, r3
    lwz r3, 0x8(r3)
    bl CarObject_GetKartMovementPtr
    mr r4, r3
    lwz r3, 0x70(r28)
    li r5, 0x324
    bl memcpy
    lis r3, 0x1
    lfs f31, lbl_806DAD70(r2)
    subi r31, r3, 0x1
    li r30, 0x0
    li r29, 0x0
    b JumpDistanceMode_PredictLanding_L_80210B18
    JumpDistanceMode_PredictLanding_L_80210AA8:
    lfs f1, 0x74(r28)
    fcmpo cr0, f1, f31
    bge JumpDistanceMode_PredictLanding_L_80210ADC
    lfs f0, lbl_806DAD74(r2)
    fadds f0, f1, f0
    stfs f0, 0x74(r28)
    lfs f0, 0x74(r28)
    fcmpo cr0, f0, f31
    cror eq, gt, eq
    bne JumpDistanceMode_PredictLanding_L_80210ADC
    lfs f0, lbl_806DAD78(r2)
    lwz r3, 0x70(r28)
    stfs f0, 0x2d4(r3)
    JumpDistanceMode_PredictLanding_L_80210ADC:
    lfs f1, lbl_806DAD7C(r2)
    li r4, 0x1
    lwz r3, 0x70(r28)
    fmr f2, f1
    fmr f3, f1
    bl KartMovement_PhysicsStep
    lwz r3, 0x70(r28)
    lbz r0, 0x244(r3)
    cmplwi r0, 0x1
    bne JumpDistanceMode_PredictLanding_L_80210B08
    li r30, 0x1
    JumpDistanceMode_PredictLanding_L_80210B08:
    lbz r0, 0x2bd(r3)
    cmplwi r0, 0x0
    beq JumpDistanceMode_PredictLanding_L_80210B20
    addi r29, r29, 0x1
    JumpDistanceMode_PredictLanding_L_80210B18:
    cmpw r29, r31
    blt JumpDistanceMode_PredictLanding_L_80210AA8
    JumpDistanceMode_PredictLanding_L_80210B20:
    lwz r3, 0x70(r28)
    lfs f0, 0x40(r3)
    stfs f0, 0x44(r1)
    lfs f0, 0x44(r3)
    stfs f0, 0x48(r1)
    lfs f0, 0x48(r3)
    stfs f0, 0x4c(r1)
    lwz r3, 0x8(r28)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r3)
    addi r4, r1, 0x38
    addi r5, r1, 0x2c
    stfs f0, 0x38(r1)
    lfs f0, 0x1c(r3)
    stfs f0, 0x3c(r1)
    lfs f0, 0x2c(r3)
    addi r3, r1, 0x44
    stfs f0, 0x40(r1)
    bl Vec3_Subtract
    lfs f0, lbl_806DAD7C(r2)
    addi r3, r1, 0x2c
    mr r4, r3
    stfs f0, 0x30(r1)
    bl Vec3_Normalize
    lfs f4, lbl_806DAD80(r2)
    clrlwi r0, r30, 24
    lfs f1, 0x34(r1)
    cmplwi r0, 0x1
    lfs f0, 0x44(r1)
    lfs f5, 0x2c(r1)
    lfs f6, 0x4c(r1)
    fmadds f3, f4, f1, f0
    lfs f1, lbl_806DAD84(r2)
    lfs f0, 0x48(r1)
    fmadds f2, f4, f5, f6
    stfs f3, 0x20(r1)
    fadds f0, f1, f0
    stfs f2, 0x28(r1)
    stfs f0, 0x24(r1)
    bne JumpDistanceMode_PredictLanding_L_80210BD0
    fneg f0, f5
    fmadds f0, f4, f0, f6
    stfs f0, 0x28(r1)
    JumpDistanceMode_PredictLanding_L_80210BD0:
    addi r3, r1, 0x38
    addi r4, r1, 0x20
    addi r5, r1, 0x14
    addi r6, r1, 0x8
    bl Terrain_RaycastWall
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    beq JumpDistanceMode_PredictLanding_L_80210C10
    addi r3, r1, 0x44
    addi r4, r1, 0x20
    addi r5, r1, 0x14
    addi r6, r1, 0x8
    bl Terrain_RaycastWall
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_PredictLanding_L_80210C28
    JumpDistanceMode_PredictLanding_L_80210C10:
    lfs f0, 0x34(r1)
    lfs f2, lbl_806DAD80(r2)
    fneg f1, f0
    lfs f0, 0x44(r1)
    fmadds f0, f2, f1, f0
    stfs f0, 0x20(r1)
    JumpDistanceMode_PredictLanding_L_80210C28:
    clrlwi. r0, r30, 24
    bne JumpDistanceMode_PredictLanding_L_80210C5C
    lfs f3, 0x44(r1)
    lfs f2, 0x20(r1)
    lfs f1, 0x4c(r1)
    lfs f0, 0x28(r1)
    fsubs f2, f3, f2
    lfs f3, lbl_806DAD88(r2)
    fsubs f0, f1, f0
    lfs f4, lbl_806DAD8C(r2)
    fmuls f1, f3, f2
    fmuls f2, f3, f0
    b JumpDistanceMode_PredictLanding_L_80210C84
    JumpDistanceMode_PredictLanding_L_80210C5C:
    lfs f3, 0x44(r1)
    lfs f2, 0x20(r1)
    lfs f1, 0x4c(r1)
    lfs f0, 0x28(r1)
    fsubs f2, f3, f2
    lfs f3, lbl_806DAD88(r2)
    fsubs f0, f1, f0
    lfs f4, lbl_806DAD8C(r2)
    fmuls f1, f3, f2
    fmuls f2, f3, f0
    JumpDistanceMode_PredictLanding_L_80210C84:
    lwz r3, 0x40(r28)
    lfs f0, 0x20(r1)
    stfs f0, 0x8(r3)
    lfs f0, 0x24(r1)
    stfs f0, 0xc(r3)
    lfs f0, 0x28(r1)
    stfs f0, 0x10(r3)
    stfs f1, 0x14(r3)
    stfs f4, 0x18(r3)
    stfs f2, 0x1c(r3)
    psq_l f31, 0x68(r1), 0, 0
    lwz r0, 0x74(r1)
    lfd f31, 0x60(r1)
    lwz r31, 0x5c(r1)
    lwz r30, 0x58(r1)
    lwz r29, 0x54(r1)
    lwz r28, 0x50(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}



