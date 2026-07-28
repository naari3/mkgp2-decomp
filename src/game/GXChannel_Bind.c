/* === extracted from auto_GXChannel_Bind_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void GX_ClearVtxDesc();
extern void GX_SetArray();
extern void GX_SetCullMode();
extern void GX_SetVtxAttrFmt();
extern void GX_SetVtxDesc();
extern void fn_802BCF94();
extern void fn_802C22D8();
extern void fn_802C35DC();
extern void fn_802C8510();
extern void fn_802D0F50();

/* --- function index (1 fns, .text 0x8007D834..0x8007D9C4) ---
 * [  0] 0x8007D834 size:0x190   global GXChannel_Bind
 */

/* --- forward decls --- */
asm void GXChannel_Bind(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GXChannel_Bind[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GXChannel_Bind = {
    (void *)&GXChannel_Bind, 0x00000190, (void *)extab_GXChannel_Bind
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GXChannel_Bind(void) { /* 0x8007D834 size:0x190 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    lbz r0, 0xc(r3)
    cmplwi r0, 0x1
    bne GXChannel_Bind_L_8007D860
    li r3, 0x0
    b GXChannel_Bind_L_8007D9AC
    GXChannel_Bind_L_8007D860:
    bl fn_802C8510
    addi r0, r3, 0x54
    stw r0, 0x10(r31)
    lwz r3, 0x0(r31)
    bl fn_802D0F50
    lwz r3, 0x4(r31)
    bl fn_802BCF94
    lwz r3, 0x4(r31)
    lwz r3, 0x8(r3)
    bl fn_802C22D8
    lwz r3, 0x4(r31)
    lwz r4, 0x8(r31)
    lwz r3, 0x8(r3)
    bl fn_802C35DC
    lwz r3, 0x4(r31)
    lwz r3, 0xc(r3)
    lwz r30, 0x8(r3)
    b GXChannel_Bind_L_8007D8CC
    GXChannel_Bind_L_8007D8A8:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x1
    beq GXChannel_Bind_L_8007D8C8
    lhz r0, 0x12(r30)
    lwz r3, 0x0(r30)
    lwz r4, 0x14(r30)
    clrlwi r5, r0, 24
    bl GX_SetArray
    GXChannel_Bind_L_8007D8C8:
    addi r30, r30, 0x18
    GXChannel_Bind_L_8007D8CC:
    lwz r0, 0x0(r30)
    cmpwi r0, 0xff
    bne GXChannel_Bind_L_8007D8A8
    lwz r3, 0x4(r31)
    lwz r30, 0xc(r3)
    bl GX_ClearVtxDesc
    lwz r30, 0x8(r30)
    b GXChannel_Bind_L_8007D928
    GXChannel_Bind_L_8007D8EC:
    lwz r3, 0x0(r30)
    lwz r4, 0x4(r30)
    bl GX_SetVtxDesc
    lwz r0, 0x0(r30)
    cmpwi r0, 0x9
    bge GXChannel_Bind_L_8007D90C
    cmpwi r0, 0x0
    bge GXChannel_Bind_L_8007D924
    GXChannel_Bind_L_8007D90C:
    lwz r4, 0x0(r30)
    li r3, 0x0
    lwz r5, 0x8(r30)
    lwz r6, 0xc(r30)
    lbz r7, 0x10(r30)
    bl GX_SetVtxAttrFmt
    GXChannel_Bind_L_8007D924:
    addi r30, r30, 0x18
    GXChannel_Bind_L_8007D928:
    lwz r0, 0x0(r30)
    cmpwi r0, 0xff
    bne GXChannel_Bind_L_8007D8EC
    lwz r4, 0x4(r31)
    lis r3, 0x1
    addi r0, r3, -0x8000
    lwz r4, 0xc(r4)
    lhz r4, 0xc(r4)
    rlwinm r4, r4, 0, 16, 17
    cmpw r4, r0
    beq GXChannel_Bind_L_8007D998
    bge GXChannel_Bind_L_8007D970
    cmpwi r4, 0x4000
    beq GXChannel_Bind_L_8007D98C
    bge GXChannel_Bind_L_8007D9A0
    cmpwi r4, 0x0
    beq GXChannel_Bind_L_8007D980
    b GXChannel_Bind_L_8007D9A0
    GXChannel_Bind_L_8007D970:
    subi r0, r3, 0x4000
    cmpw r4, r0
    beq GXChannel_Bind_L_8007D9A0
    b GXChannel_Bind_L_8007D9A0
    GXChannel_Bind_L_8007D980:
    li r3, 0x0
    bl GX_SetCullMode
    b GXChannel_Bind_L_8007D9A0
    GXChannel_Bind_L_8007D98C:
    li r3, 0x1
    bl GX_SetCullMode
    b GXChannel_Bind_L_8007D9A0
    GXChannel_Bind_L_8007D998:
    li r3, 0x2
    bl GX_SetCullMode
    GXChannel_Bind_L_8007D9A0:
    li r0, 0x1
    li r3, 0x1
    stb r0, 0xc(r31)
    GXChannel_Bind_L_8007D9AC:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

