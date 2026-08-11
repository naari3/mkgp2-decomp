/* === extracted from auto_KartDriver_BuildJoin_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DbgScene_CopyMatrix3x4Transpose();
extern void KartDriver_GetJointMatrix4x3();
extern void KartFxParam_GetConst1p5();
extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Matrix4_PreMultiplyRotX();
extern void Matrix4_PreMultiplyRotY();
extern void Matrix4_PreMultiplyRotZ();
extern void Mtx44_Translate();
extern void PSMTXConcat();
extern void PSMTXScale();
extern void Vec3_Scale();

/* --- function index (1 fns, .text 0x800D68D4..0x800D6A00) ---
 * [  0] 0x800D68D4 size:0x12C   global KartDriver_BuildJoint12EulerTransform
 */

/* --- forward decls --- */
asm void KartDriver_BuildJoint12EulerTransform(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_BuildJoint12EulerTransform[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_BuildJoint12EulerTransform = {
    (void *)&KartDriver_BuildJoint12EulerTransform, 0x0000012C, (void *)extab_KartDriver_BuildJoint12EulerTransform
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_BuildJoint12EulerTransform(void) { /* 0x800D68D4 size:0x12C */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stw r31, 0xac(r1)
    stw r30, 0xa8(r1)
    stw r29, 0xa4(r1)
    stw r28, 0xa0(r1)
    fmr f31, f1
    mr r29, r4
    mr r28, r3
    mr r30, r5
    mr r31, r6
    mr r3, r29
    bl KartFxParam_GetConst1p5
    fdivs f31, f31, f1
    mr r3, r29
    addi r5, r1, 0x60
    li r4, 0xc
    bl KartDriver_GetJointMatrix4x3
    addi r3, r1, 0x20
    bl Matrix4_Identity
    addi r3, r1, 0x20
    lfs f1, 0x4(r31)
    mr r4, r3
    bl Matrix4_PreMultiplyRotY
    addi r3, r1, 0x20
    lfs f1, 0x8(r31)
    mr r4, r3
    bl Matrix4_PreMultiplyRotZ
    addi r3, r1, 0x20
    lfs f1, 0x0(r31)
    mr r4, r3
    bl Matrix4_PreMultiplyRotX
    fmr f1, f31
    mr r4, r30
    addi r3, r1, 0x14
    bl Vec3_Scale
    lwz r7, 0x14(r1)
    addi r3, r1, 0x20
    lwz r6, 0x18(r1)
    mr r4, r3
    lwz r0, 0x1c(r1)
    addi r5, r1, 0x8
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_Translate
    addi r3, r1, 0x60
    addi r4, r1, 0x20
    mr r5, r3
    bl Matrix4_Multiply
    addi r3, r28, 0x34
    addi r4, r1, 0x60
    bl DbgScene_CopyMatrix3x4Transpose
    fmr f1, f31
    addi r3, r1, 0x20
    fmr f2, f31
    fmr f3, f31
    bl PSMTXScale
    addi r3, r28, 0x34
    addi r4, r1, 0x20
    mr r5, r3
    bl PSMTXConcat
    psq_l f31, 0xb8(r1), 0, 0
    lwz r0, 0xc4(r1)
    lfd f31, 0xb0(r1)
    lwz r31, 0xac(r1)
    lwz r30, 0xa8(r1)
    lwz r29, 0xa4(r1)
    lwz r28, 0xa0(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

