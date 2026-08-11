/* === extracted from auto_KartDriver_Transform_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartDriver_GetKartRootMtx();
extern void Mtx44_Inverse_GaussJordan();
extern void Mtx44_TransformVec3();
extern void Mtx_TransposeToMtx44();
extern void Vec3_Copy();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5AC8;

/* --- function index (1 fns, .text 0x800DC6D0..0x800DC784) ---
 * [  0] 0x800DC6D0 size:0xB4    global KartDriver_TransformWorldToLocalY0
 */

/* --- forward decls --- */
asm void KartDriver_TransformWorldToLocalY0(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartDriver_TransformWorldToLocalY0[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_TransformWorldToLocalY0 = {
    (void *)&KartDriver_TransformWorldToLocalY0, 0x000000B4, (void *)extab_KartDriver_TransformWorldToLocalY0
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_TransformWorldToLocalY0(void) { /* 0x800DC6D0 size:0xB4 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stw r31, 0xbc(r1)
    mr r31, r5
    stw r30, 0xb8(r1)
    mr r30, r3
    addi r3, r1, 0x20
    bl Vec3_Copy
    mr r3, r31
    bl KartDriver_GetKartRootMtx
    mr r4, r3
    addi r3, r1, 0x6c
    bl Mtx_TransposeToMtx44
    addi r3, r1, 0x2c
    addi r4, r1, 0x6c
    bl Mtx44_Inverse_GaussJordan
    lwz r7, 0x20(r1)
    addi r3, r1, 0x20
    lwz r6, 0x24(r1)
    addi r4, r1, 0x2c
    lwz r0, 0x28(r1)
    addi r5, r1, 0x14
    stw r7, 0x14(r1)
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    bl Mtx44_TransformVec3
    lfs f0, lbl_806D5AC8(r2)
    mr r3, r30
    lwz r6, 0x24(r1)
    addi r4, r1, 0x6c
    stfs f0, 0x20(r1)
    addi r5, r1, 0x8
    lwz r0, 0x28(r1)
    lwz r7, 0x20(r1)
    stw r6, 0xc(r1)
    stw r7, 0x8(r1)
    stw r0, 0x10(r1)
    bl Mtx44_TransformVec3
    lwz r0, 0xc4(r1)
    lwz r31, 0xbc(r1)
    lwz r30, 0xb8(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

