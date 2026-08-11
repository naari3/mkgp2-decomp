/* === extracted from auto_GabyouItem_BuildLoca_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DbgScene_CopyMatrix3x4Transpose();
extern void KartDriver_GetJointByIdx();
extern void KartDriver_GetKartRootMtx();
extern void Matrix4_Copy();
extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Matrix4_PreMultiplyRotY();
extern void Matrix4_PreMultiplyTranslation();
extern void Mtx44_GetTranslation_ColMajor();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_Translate();
extern void Mtx_TransposeToMtx44();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5AB8;
extern unsigned int lbl_806D5AC8;
extern unsigned int lbl_806D5ACC;
extern unsigned int lbl_806D5AEC;
extern unsigned int lbl_806D5AFC;
extern unsigned int lbl_806D5B1C;
extern unsigned int lbl_806D5B20;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_8041E980[];
extern unsigned int jumptable_8041E9B4[];

/* --- function index (1 fns, .text 0x800DABBC..0x800DAE88) ---
 * [  0] 0x800DABBC size:0x2CC   global GabyouItem_BuildLocalTransformFromHandJoint
 */

/* --- forward decls --- */
asm void GabyouItem_BuildLocalTransformFromHandJoint(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GabyouItem_BuildLocalTransformFromHandJoint[8] = {
    0x08, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GabyouItem_BuildLocalTransformFromHandJoint = {
    (void *)&GabyouItem_BuildLocalTransformFromHandJoint, 0x000002CC, (void *)extab_GabyouItem_BuildLocalTransformFromHandJoint
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GabyouItem_BuildLocalTransformFromHandJoint(void) { /* 0x800DABBC size:0x2CC */
    nofralloc
    stwu r1, -0x120(r1)
    mflr r0
    stw r0, 0x124(r1)
    stfd f31, 0x110(r1)
    psq_st f31, 0x118(r1), 0, 0
    stfd f30, 0x100(r1)
    psq_st f30, 0x108(r1), 0, 0
    stw r31, 0xfc(r1)
    mr. r31, r3
    fmr f30, f1
    fmr f31, f2
    beq GabyouItem_BuildLocalTransformFromHandJoint_L_800DAE64
    cmpwi r4, 0x1
    beq GabyouItem_BuildLocalTransformFromHandJoint_L_800DABFC
    bge GabyouItem_BuildLocalTransformFromHandJoint_L_800DAC20
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DAC20
    GabyouItem_BuildLocalTransformFromHandJoint_L_800DABFC:
    lfs f2, 0x2c(r31)
    lfs f0, lbl_806D5AFC(r2)
    lfs f1, lbl_806D5AB8(r2)
    fadds f0, f2, f0
    stfs f0, 0x2c(r31)
    lfs f0, 0x2c(r31)
    fcmpo cr0, f1, f0
    bge GabyouItem_BuildLocalTransformFromHandJoint_L_800DAC20
    stfs f1, 0x2c(r31)
    GabyouItem_BuildLocalTransformFromHandJoint_L_800DAC20:
    lwz r3, 0x184(r31)
    lwz r0, 0x1f8(r3)
    cmplwi r0, 0xc
    bgt GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB0
    lis r3, jumptable_8041E9B4@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8041E9B4@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AEC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    lfs f0, lbl_806D5AB8(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4
    GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB0:
    lfs f0, lbl_806D5AC8(r2)
    GabyouItem_BuildLocalTransformFromHandJoint_L_800DACB4:
    fmuls f0, f3, f0
    stfs f0, 0xc4(r31)
    lwz r3, 0x184(r31)
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0xac
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x20
    addi r4, r1, 0xac
    bl Mtx44_GetTranslation_ColMajor
    lwz r3, 0x184(r31)
    li r4, 0xc
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r1, 0x14
    bl Mtx44_GetTranslation_RowMajor
    addi r3, r1, 0x6c
    addi r4, r1, 0xac
    bl Matrix4_Copy
    lfs f1, 0x20(r1)
    addi r3, r1, 0x6c
    lfs f2, 0x24(r1)
    mr r4, r3
    lfs f0, 0x28(r1)
    fneg f1, f1
    fneg f2, f2
    fneg f3, f0
    bl Matrix4_PreMultiplyTranslation
    lwz r7, 0x14(r1)
    addi r3, r1, 0x6c
    lwz r6, 0x18(r1)
    mr r4, r3
    lwz r0, 0x1c(r1)
    addi r5, r1, 0x8
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_Translate
    addi r3, r1, 0x2c
    bl Matrix4_Identity
    lwz r3, 0x184(r31)
    lwz r0, 0x1f8(r3)
    cmplwi r0, 0xc
    bgt GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE4
    lis r3, jumptable_8041E980@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8041E980@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5B1C(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5B1C(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5B1C(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5B20(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    lfs f2, lbl_806D5ACC(r2)
    b GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8
    GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE4:
    lfs f2, lbl_806D5AC8(r2)
    GabyouItem_BuildLocalTransformFromHandJoint_L_800DADE8:
    lfs f1, lbl_806D5AC8(r2)
    addi r3, r1, 0x2c
    lfs f0, 0xc4(r31)
    mr r4, r3
    fmr f3, f1
    fmadds f2, f30, f0, f2
    bl Matrix4_PreMultiplyTranslation
    fmr f1, f31
    addi r3, r1, 0x2c
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    addi r3, r1, 0x6c
    addi r4, r1, 0x2c
    mr r5, r3
    bl Matrix4_Multiply
    addi r3, r1, 0x2c
    bl Matrix4_Identity
    addi r3, r1, 0x2c
    lfs f1, 0xc4(r31)
    mr r4, r3
    bl Mtx44_Scale_Uniform
    addi r3, r1, 0x6c
    addi r4, r1, 0x2c
    mr r5, r3
    bl Matrix4_Multiply
    addi r3, r31, 0x48
    addi r4, r1, 0x6c
    bl DbgScene_CopyMatrix3x4Transpose
    addi r3, r31, 0xa0
    addi r4, r31, 0x48
    bl Mtx44_GetTranslation_RowMajor
    GabyouItem_BuildLocalTransformFromHandJoint_L_800DAE64:
    psq_l f31, 0x118(r1), 0, 0
    lfd f31, 0x110(r1)
    psq_l f30, 0x108(r1), 0, 0
    lfd f30, 0x100(r1)
    lwz r0, 0x124(r1)
    lwz r31, 0xfc(r1)
    mtlr r0
    addi r1, r1, 0x120
    blr
}
