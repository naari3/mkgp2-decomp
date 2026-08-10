/* === extracted from auto_SpriteSlot_SetMatrix_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_BindMatrixSource();
extern void Object_ClearAnimBinding();
extern void Object_SetField14_IfValid();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D5960;
extern unsigned int lbl_806D5964;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8041AC24[];

/* --- function index (1 fns, .text 0x800D6A00..0x800D6B20) ---
 * [  0] 0x800D6A00 size:0x120   global SpriteSlot_SetMatrixSourceEnabled_WithReseed
 */

/* --- forward decls --- */
asm void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_SetMatrixSourceEnabled_WithReseed[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_SetMatrixSourceEnabled_WithReseed = {
    (void *)&SpriteSlot_SetMatrixSourceEnabled_WithReseed, 0x00000120, (void *)extab_SpriteSlot_SetMatrixSourceEnabled_WithReseed
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void) { /* 0x800D6A00 size:0x120 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    extsb. r0, r4
    stw r31, 0xc(r1)
    mr r31, r3
    beq SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6A30
    lwz r3, 0x4(r31)
    addi r4, r31, 0x34
    li r5, 0x0
    bl Object_BindMatrixSource
    b SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6A38
    SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6A30:
    lwz r3, 0x4(r31)
    bl Object_ClearAnimBinding
    SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6A38:
    lwz r0, 0x4(r31)
    lfs f1, 0xc(r31)
    cmplwi r0, 0x0
    lbz r0, 0x9(r31)
    beq SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6B0C
    stb r0, 0x9(r31)
    lis r3, lbl_8041AC24@ha
    addi r4, r3, lbl_8041AC24@l
    lbz r3, 0x8(r31)
    addi r7, r4, 0x4
    lbz r0, 0x9(r31)
    mulli r3, r3, 0x14
    extsb r0, r0
    mulli r0, r0, 0xc
    lwzx r3, r7, r3
    add r3, r3, r0
    lfs f0, 0x4(r3)
    lfs f2, 0x8(r3)
    fadds f1, f1, f0
    fcmpo cr0, f2, f1
    bge SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6A90
    fmr f1, f2
    SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6A90:
    li r0, 0x0
    lfs f3, lbl_806D5960(r2)
    stb r0, 0xa(r31)
    li r4, 0x0
    fmr f4, f3
    lfs f2, lbl_806D5964(r2)
    lbz r3, 0x8(r31)
    lbz r0, 0x9(r31)
    mulli r3, r3, 0x14
    extsb r0, r0
    mulli r0, r0, 0xc
    lwzx r3, r7, r3
    add r3, r3, r0
    lfs f0, 0x4(r3)
    fsubs f0, f1, f0
    stfs f0, 0xc(r31)
    lbz r3, 0x8(r31)
    lbz r0, 0x9(r31)
    mulli r6, r3, 0x14
    lfs f0, 0xc(r31)
    extsb r0, r0
    lwz r3, 0x4(r31)
    mulli r5, r0, 0xc
    lwzx r6, r7, r6
    addi r0, r5, 0x4
    lfsx f1, r6, r0
    fadds f1, f1, f0
    bl clNormal3D_SetScale
    lwz r3, 0x4(r31)
    lfs f1, lbl_806D5960(r2)
    bl Object_SetField14_IfValid
    SpriteSlot_SetMatrixSourceEnabled_WithReseed_L_800D6B0C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
