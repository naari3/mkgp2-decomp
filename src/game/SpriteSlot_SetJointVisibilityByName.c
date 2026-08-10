/* === extracted from auto_SpriteSlot_SetJointV_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void JObj_Hide();
extern void JObj_Show();
extern void ResolveJointByName();

/* --- function index (1 fns, .text 0x800D6BA8..0x800D6C20) ---
 * [  0] 0x800D6BA8 size:0x78    global SpriteSlot_SetJointVisibilityByName
 */

/* --- forward decls --- */
asm void SpriteSlot_SetJointVisibilityByName(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_SetJointVisibilityByName[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_SetJointVisibilityByName = {
    (void *)&SpriteSlot_SetJointVisibilityByName, 0x00000078, (void *)extab_SpriteSlot_SetJointVisibilityByName
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_SetJointVisibilityByName(void) { /* 0x800D6BA8 size:0x78 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r5
    stw r29, 0x14(r1)
    mr. r29, r3
    beq SpriteSlot_SetJointVisibilityByName_L_800D6C04
    lwz r3, 0x4(r29)
    bl ResolveJointByName
    mr. r4, r3
    beq SpriteSlot_SetJointVisibilityByName_L_800D6C04
    extsb. r0, r31
    beq SpriteSlot_SetJointVisibilityByName_L_800D6BF8
    lwz r3, 0x4(r29)
    mr r5, r30
    bl JObj_Hide
    b SpriteSlot_SetJointVisibilityByName_L_800D6C04
    SpriteSlot_SetJointVisibilityByName_L_800D6BF8:
    lwz r3, 0x4(r29)
    mr r5, r30
    bl JObj_Show
    SpriteSlot_SetJointVisibilityByName_L_800D6C04:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

