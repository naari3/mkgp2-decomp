/* === extracted from auto_SpriteSlot_SetRotati_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void JObj_SetRotationQuat();

/* --- function index (1 fns, .text 0x800D6D4C..0x800D6D84) ---
 * [  0] 0x800D6D4C size:0x38    global SpriteSlot_SetRotationQuatFromVec
 */

/* --- forward decls --- */
asm void SpriteSlot_SetRotationQuatFromVec(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_SetRotationQuatFromVec[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_SetRotationQuatFromVec = {
    (void *)&SpriteSlot_SetRotationQuatFromVec, 0x00000038, (void *)extab_SpriteSlot_SetRotationQuatFromVec
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_SetRotationQuatFromVec(void) { /* 0x800D6D4C size:0x38 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f3, 0x8(r4)
    stw r0, 0x14(r1)
    lfs f2, 0x4(r4)
    lwz r3, 0x4(r3)
    lfs f1, 0x0(r4)
    cmplwi r3, 0x0
    beq SpriteSlot_SetRotationQuatFromVec_L_800D6D74
    bl JObj_SetRotationQuat
    SpriteSlot_SetRotationQuatFromVec_L_800D6D74:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


