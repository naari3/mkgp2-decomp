/* === extracted from auto_SpriteSlot_SetJointS_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void JObj_SetScale();
extern void ResolveJointByName();

/* --- function index (1 fns, .text 0x800D6B34..0x800D6BA8) ---
 * [  0] 0x800D6B34 size:0x74    global SpriteSlot_SetJointScaleByName
 */

/* --- forward decls --- */
asm void SpriteSlot_SetJointScaleByName(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_SetJointScaleByName[8] = {
    0x08, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_SetJointScaleByName = {
    (void *)&SpriteSlot_SetJointScaleByName, 0x00000074, (void *)extab_SpriteSlot_SetJointScaleByName
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_SetJointScaleByName(void) { /* 0x800D6B34 size:0x74 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x28(r1)
    fmr f31, f3
    stfd f30, 0x20(r1)
    fmr f30, f2
    stfd f29, 0x18(r1)
    fmr f29, f1
    stw r31, 0x14(r1)
    mr. r31, r3
    beq SpriteSlot_SetJointScaleByName_L_800D6B88
    lwz r3, 0x4(r31)
    bl ResolveJointByName
    mr. r4, r3
    beq SpriteSlot_SetJointScaleByName_L_800D6B88
    fmr f1, f29
    lwz r3, 0x4(r31)
    fmr f2, f30
    fmr f3, f31
    bl JObj_SetScale
    SpriteSlot_SetJointScaleByName_L_800D6B88:
    lwz r0, 0x34(r1)
    lfd f31, 0x28(r1)
    lfd f30, 0x20(r1)
    lfd f29, 0x18(r1)
    lwz r31, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

