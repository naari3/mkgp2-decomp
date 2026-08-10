/* === extracted from auto_SpriteSlot_Destroy_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_DtorWithGXSync();

/* --- function index (1 fns, .text 0x800D6DE8..0x800D6E2C) ---
 * [  0] 0x800D6DE8 size:0x44    global SpriteSlot_Destroy
 */

/* --- forward decls --- */
asm void SpriteSlot_Destroy(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_Destroy[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_Destroy = {
    (void *)&SpriteSlot_Destroy, 0x00000044, (void *)extab_SpriteSlot_Destroy
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_Destroy(void) { /* 0x800D6DE8 size:0x44 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    beq SpriteSlot_Destroy_L_800D6E18
    li r4, 0x1
    bl Object_DtorWithGXSync
    li r0, 0x0
    stw r0, 0x4(r31)
    SpriteSlot_Destroy_L_800D6E18:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


