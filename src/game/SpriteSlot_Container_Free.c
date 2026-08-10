/* === extracted from auto_SpriteSlot_Container_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void SpriteSlot_Destroy();

/* --- function index (1 fns, .text 0x800D7F30..0x800D7F70) ---
 * [  0] 0x800D7F30 size:0x40    global SpriteSlot_Container_Free
 */

/* --- forward decls --- */
asm void SpriteSlot_Container_Free(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SpriteSlot_Container_Free[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteSlot_Container_Free = {
    (void *)&SpriteSlot_Container_Free, 0x00000040, (void *)extab_SpriteSlot_Container_Free
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SpriteSlot_Container_Free(void) { /* 0x800D7F30 size:0x40 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq SpriteSlot_Container_Free_L_800D7F5C
    beq SpriteSlot_Container_Free_L_800D7F5C
    addi r3, r31, 0x14
    bl SpriteSlot_Destroy
    li r0, 0x0
    stb r0, 0x0(r31)
    SpriteSlot_Container_Free_L_800D7F5C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


