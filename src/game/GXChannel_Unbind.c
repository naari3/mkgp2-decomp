/* === extracted from auto_GXChannel_Unbind_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_802BCF94();
extern void fn_802C14B8();
extern void fn_802C22D8();
extern void fn_802CAEA0();

/* --- function index (1 fns, .text 0x8007D7BC..0x8007D834) ---
 * [  0] 0x8007D7BC size:0x78    global GXChannel_Unbind
 */

/* --- forward decls --- */
asm void GXChannel_Unbind(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GXChannel_Unbind[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GXChannel_Unbind = {
    (void *)&GXChannel_Unbind, 0x00000078, (void *)extab_GXChannel_Unbind
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GXChannel_Unbind(void) { /* 0x8007D7BC size:0x78 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lbz r0, 0xc(r3)
    cmplwi r0, 0x1
    bne GXChannel_Unbind_L_8007D81C
    lwz r3, 0x4(r31)
    lwz r4, 0x8(r31)
    lwz r3, 0x8(r3)
    lwz r5, 0x0(r3)
    lwz r12, 0x50(r5)
    mtctr r12
    bctrl
    li r3, 0x0
    bl fn_802C22D8
    li r3, 0x0
    bl fn_802BCF94
    bl fn_802CAEA0
    li r3, -0x1
    bl fn_802C14B8
    li r0, 0x0
    stb r0, 0xc(r31)
    GXChannel_Unbind_L_8007D81C:
    lwz r0, 0x14(r1)
    li r3, 0x1
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

