/* === extracted from auto_CarrotItemEffect_Upd_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DbgScene_CopyMatrix3x4Transpose();
extern void FinalLapCoinJump_CheckActiveForObject();
extern void ItemEffectBus_ClearMask();
extern void KartCharacterParam_GetIdentityIndex();
extern void KartDriver_GetJointByIdx();
extern void Matrix4_Identity();
extern void Matrix4_Multiply();
extern void Mtx44_GetTranslation_RowMajor();
extern void Mtx44_Scale_Uniform();
extern void Mtx44_Translate();
extern void Mtx_TransposeToMtx44();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetAnimFrameAndApplyScale();
extern void SpriteSlot_SetJointVisibilityByName();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5034;
extern unsigned int lbl_806D5040;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803298F0[];
extern unsigned int lbl_8041A000[];

/* --- function index (1 fns, .text 0x800B2164..0x800B23CC) ---
 * [  0] 0x800B2164 size:0x268   global CarrotItemEffect_Update
 */

/* --- forward decls --- */
asm void CarrotItemEffect_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CarrotItemEffect_Update[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CarrotItemEffect_Update = {
    (void *)&CarrotItemEffect_Update, 0x00000268, (void *)extab_CarrotItemEffect_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CarrotItemEffect_Update(void) { /* 0x800B2164 size:0x268 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stw r31, 0x9c(r1)
    mr r31, r3
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x1
    beq CarrotItemEffect_Update_L_800B21FC
    bge CarrotItemEffect_Update_L_800B21FC
    cmpwi r0, 0x0
    bge CarrotItemEffect_Update_L_800B2198
    b CarrotItemEffect_Update_L_800B21FC
    CarrotItemEffect_Update_L_800B2198:
    addi r3, r31, 0x14
    li r4, 0x8e
    bl SpriteSlot_InitNonLoop
    lfs f1, lbl_806D5034(r2)
    addi r3, r31, 0x14
    li r4, 0x1
    bl SpriteSlot_SetAnimFrameAndApplyScale
    lis r4, lbl_803298F0@ha
    addi r3, r31, 0x14
    addi r4, r4, lbl_803298F0@l
    li r5, 0x10
    li r6, 0x1
    bl SpriteSlot_SetJointVisibilityByName
    addi r3, r31, 0x14
    li r4, 0x1
    bl SpriteSlot_SetMatrixSourceEnabled_WithReseed
    li r0, 0x258
    li r3, 0x3
    stw r0, 0xf0(r31)
    li r0, 0x3c
    stw r3, 0xf4(r31)
    stw r0, 0xf8(r31)
    lbz r3, 0xc8(r31)
    addi r0, r3, 0x1
    stb r0, 0xc8(r31)
    CarrotItemEffect_Update_L_800B21FC:
    lwz r0, 0xf4(r31)
    cmplwi r0, 0x0
    bne CarrotItemEffect_Update_L_800B2248
    lwz r3, 0x188(r31)
    lis r4, 0x1
    li r5, 0x0
    lwz r3, 0x304(r3)
    lwz r0, 0x10(r3)
    lwz r6, 0x14(r3)
    and r0, r0, r5
    and r4, r6, r4
    xor r4, r4, r5
    xor r0, r0, r5
    or. r0, r4, r0
    beq CarrotItemEffect_Update_L_800B2248
    stw r5, 0xf0(r31)
    li r6, 0x0
    lis r5, 0x2
    bl ItemEffectBus_ClearMask
    CarrotItemEffect_Update_L_800B2248:
    lwz r0, 0xf8(r31)
    cmplwi r0, 0x0
    bne CarrotItemEffect_Update_L_800B2288
    lwz r3, 0x188(r31)
    li r4, 0x0
    lis r0, 0x2
    lwz r5, 0x304(r3)
    lwz r3, 0x10(r5)
    lwz r5, 0x14(r5)
    and r0, r3, r0
    and r3, r5, r4
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne CarrotItemEffect_Update_L_800B2288
    stw r4, 0xf0(r31)
    CarrotItemEffect_Update_L_800B2288:
    lwz r3, 0x188(r31)
    bl FinalLapCoinJump_CheckActiveForObject
    clrlwi. r0, r3, 24
    beq CarrotItemEffect_Update_L_800B22A4
    li r0, 0x0
    stb r0, 0x28(r31)
    b CarrotItemEffect_Update_L_800B22AC
    CarrotItemEffect_Update_L_800B22A4:
    li r0, 0x1
    stb r0, 0x28(r31)
    CarrotItemEffect_Update_L_800B22AC:
    lwz r0, 0xf0(r31)
    cmplwi r0, 0x0
    bne CarrotItemEffect_Update_L_800B22C4
    mr r3, r31
    bl SpriteSlot_Container_Free
    b CarrotItemEffect_Update_L_800B23B8
    CarrotItemEffect_Update_L_800B22C4:
    lbz r0, 0x28(r31)
    extsb. r0, r0
    beq CarrotItemEffect_Update_L_800B2368
    lwz r3, 0x188(r31)
    li r4, 0xf
    bl KartDriver_GetJointByIdx
    mr r4, r3
    addi r3, r1, 0x54
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x14
    bl Matrix4_Identity
    addi r3, r1, 0x14
    lfs f1, lbl_806D5040(r2)
    mr r4, r3
    bl Mtx44_Scale_Uniform
    lwz r3, 0x188(r31)
    bl KartCharacterParam_GetIdentityIndex
    mulli r5, r3, 0xc
    lis r4, lbl_8041A000@ha
    addi r3, r1, 0x14
    addi r0, r4, lbl_8041A000@l
    add r8, r0, r5
    mr r4, r3
    lwz r7, 0x0(r8)
    addi r5, r1, 0x8
    lwz r6, 0x4(r8)
    lwz r0, 0x8(r8)
    stw r7, 0x8(r1)
    stw r6, 0xc(r1)
    stw r0, 0x10(r1)
    bl Mtx44_Translate
    addi r3, r1, 0x14
    addi r5, r1, 0x54
    mr r4, r3
    bl Matrix4_Multiply
    addi r3, r31, 0x48
    addi r4, r1, 0x14
    bl DbgScene_CopyMatrix3x4Transpose
    addi r3, r31, 0xa0
    addi r4, r31, 0x48
    bl Mtx44_GetTranslation_RowMajor
    CarrotItemEffect_Update_L_800B2368:
    lwz r3, 0xf0(r31)
    cmplwi r3, 0x0
    beq CarrotItemEffect_Update_L_800B237C
    subi r0, r3, 0x1
    stw r0, 0xf0(r31)
    CarrotItemEffect_Update_L_800B237C:
    lwz r3, 0xf4(r31)
    cmplwi r3, 0x0
    beq CarrotItemEffect_Update_L_800B2390
    subi r0, r3, 0x1
    stw r0, 0xf4(r31)
    CarrotItemEffect_Update_L_800B2390:
    lwz r3, 0xf8(r31)
    cmplwi r3, 0x0
    beq CarrotItemEffect_Update_L_800B23A4
    subi r0, r3, 0x1
    stw r0, 0xf8(r31)
    CarrotItemEffect_Update_L_800B23A4:
    lwz r3, 0xfc(r31)
    cmplwi r3, 0x0
    beq CarrotItemEffect_Update_L_800B23B8
    subi r0, r3, 0x1
    stw r0, 0xfc(r31)
    CarrotItemEffect_Update_L_800B23B8:
    lwz r0, 0xa4(r1)
    lwz r31, 0x9c(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}
