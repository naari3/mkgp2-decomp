/* === extracted from auto_SpriteSlot_SetTransf_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void JObj_SetRotationQuat();
extern void Object_SetJObjPositionXYZ();
extern void Object_SetJObjScaleXYZ();

/* --- function index (1 fns, .text 0x800D6C20..0x800D6CEC) ---
 * [  0] 0x800D6C20 size:0xCC    global SpriteSlot_SetTransform
 */

/* --- forward decls --- */
asm void SpriteSlot_SetTransform(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_SetTransform[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_SetTransform = {
    (void *)&SpriteSlot_SetTransform, 0x000000CC, (void *)extab_SpriteSlot_SetTransform
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_SetTransform(void) { /* 0x800D6C20 size:0xCC */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    mr r30, r3
    lwz r6, 0x4(r4)
    lwz r0, 0x8(r4)
    fmr f31, f1
    lwz r3, 0x4(r3)
    mr r31, r5
    stw r6, 0x18(r1)
    lwz r4, 0x0(r4)
    cmplwi r3, 0x0
    stw r0, 0x1c(r1)
    lfs f2, 0x18(r1)
    stw r4, 0x14(r1)
    lfs f3, 0x1c(r1)
    beq SpriteSlot_SetTransform_L_800D6C7C
    lfs f1, 0x14(r1)
    bl Object_SetJObjPositionXYZ
    SpriteSlot_SetTransform_L_800D6C7C:
    lwz r4, 0x4(r31)
    lwz r0, 0x8(r31)
    lwz r3, 0x4(r30)
    stw r4, 0xc(r1)
    lwz r4, 0x0(r31)
    cmplwi r3, 0x0
    stw r0, 0x10(r1)
    lfs f2, 0xc(r1)
    stw r4, 0x8(r1)
    lfs f3, 0x10(r1)
    beq SpriteSlot_SetTransform_L_800D6CB0
    lfs f1, 0x8(r1)
    bl JObj_SetRotationQuat
    SpriteSlot_SetTransform_L_800D6CB0:
    lwz r3, 0x4(r30)
    cmplwi r3, 0x0
    beq SpriteSlot_SetTransform_L_800D6CCC
    fmr f1, f31
    fmr f2, f31
    fmr f3, f31
    bl Object_SetJObjScaleXYZ
    SpriteSlot_SetTransform_L_800D6CCC:
    psq_l f31, 0x38(r1), 0, 0
    lwz r0, 0x44(r1)
    lfd f31, 0x30(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

