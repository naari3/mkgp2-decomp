/* === extracted from auto_Jyugemu_Flag_Render_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Object_RenderJObjTree();

/* --- function index (1 fns, .text 0x800806F4..0x80080748) ---
 * [  0] 0x800806F4 size:0x54    global Jyugemu_Flag_Render
 */

/* --- forward decls --- */
asm void Jyugemu_Flag_Render(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Jyugemu_Flag_Render[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Jyugemu_Flag_Render = {
    (void *)&Jyugemu_Flag_Render, 0x00000054, (void *)extab_Jyugemu_Flag_Render
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Jyugemu_Flag_Render(void) { /* 0x800806F4 size:0x54 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r4, 0x0(r3)
    cmplwi r4, 0x0
    bne Jyugemu_Flag_Render_L_80080714
    li r3, 0x0
    b Jyugemu_Flag_Render_L_80080738
    Jyugemu_Flag_Render_L_80080714:
    lwz r0, 0x8(r3)
    cmplwi r0, 0x0
    bne Jyugemu_Flag_Render_L_80080728
    li r3, 0x0
    b Jyugemu_Flag_Render_L_80080738
    Jyugemu_Flag_Render_L_80080728:
    mr r3, r4
    li r4, 0x7
    bl Object_RenderJObjTree
    li r3, 0x1
    Jyugemu_Flag_Render_L_80080738:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

