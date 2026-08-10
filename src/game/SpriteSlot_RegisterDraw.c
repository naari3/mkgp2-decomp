/* === extracted from auto_SpriteSlot_RegisterD_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void JObjTree_TranslateAndMul();
extern void Object_GetJObjPositionVec();
extern void Object_SetColorRGBA();
extern void clDrawMan_AddSorted_DepthRange();
extern void clDrawMan_AddSorted_NoDepthBias();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D5960;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int SpriteSlot_Render[];

/* --- function index (1 fns, .text 0x800D6E2C..0x800D6F40) ---
 * [  0] 0x800D6E2C size:0x114   global SpriteSlot_RegisterDraw
 */

/* --- forward decls --- */
asm void SpriteSlot_RegisterDraw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_RegisterDraw[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_RegisterDraw = {
    (void *)&SpriteSlot_RegisterDraw, 0x00000114, (void *)extab_SpriteSlot_RegisterDraw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_RegisterDraw(void) { /* 0x800D6E2C size:0x114 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq SpriteSlot_RegisterDraw_L_800D6F28
    lbz r0, 0x14(r30)
    extsb. r0, r0
    beq SpriteSlot_RegisterDraw_L_800D6F28
    lbz r0, 0x0(r30)
    rlwinm. r0, r0, 0, 30, 30
    beq SpriteSlot_RegisterDraw_L_800D6E6C
    b SpriteSlot_RegisterDraw_L_800D6F28
    SpriteSlot_RegisterDraw_L_800D6E6C:
    lfs f4, 0x18(r30)
    lfs f0, lbl_806D5960(r2)
    fcmpo cr0, f4, f0
    cror eq, lt, eq
    beq SpriteSlot_RegisterDraw_L_800D6F28
    lfs f1, 0x1c(r30)
    li r4, 0x0
    lfs f2, 0x20(r30)
    lfs f3, 0x24(r30)
    bl Object_SetColorRGBA
    lwz r3, 0x4(r30)
    li r4, 0x0
    lfs f1, 0x2c(r30)
    lfs f2, 0x30(r30)
    bl JObjTree_TranslateAndMul
    lwz r31, 0x4(r30)
    addi r4, r1, 0x8
    mr r3, r31
    bl Object_GetJObjPositionVec
    lbz r0, 0x0(r30)
    clrlwi. r0, r0, 31
    bne SpriteSlot_RegisterDraw_L_800D6EF8
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne SpriteSlot_RegisterDraw_L_800D6ED4
    li r3, 0x0
    SpriteSlot_RegisterDraw_L_800D6ED4:
    lis r4, SpriteSlot_Render@ha
    lfs f1, 0x8(r1)
    lfs f2, 0xc(r1)
    addi r4, r4, SpriteSlot_Render@l
    lfs f3, 0x10(r1)
    mr r5, r31
    lfs f4, lbl_806D5960(r2)
    bl clDrawMan_AddSorted_DepthRange
    b SpriteSlot_RegisterDraw_L_800D6F28
    SpriteSlot_RegisterDraw_L_800D6EF8:
    lwz r3, lbl_806D10AC(r13)
    cmplwi r3, 0x0
    bne SpriteSlot_RegisterDraw_L_800D6F08
    li r3, 0x0
    SpriteSlot_RegisterDraw_L_800D6F08:
    lis r4, SpriteSlot_Render@ha
    lfs f1, 0x8(r1)
    lfs f2, 0xc(r1)
    addi r4, r4, SpriteSlot_Render@l
    lfs f3, 0x10(r1)
    mr r5, r31
    lfs f4, lbl_806D5960(r2)
    bl clDrawMan_AddSorted_NoDepthBias
    SpriteSlot_RegisterDraw_L_800D6F28:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

