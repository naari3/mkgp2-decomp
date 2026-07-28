/* === extracted from auto_GXChannel_Init_text === */
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

/* --- function index (1 fns, .text 0x8007DA5C..0x8007DC08) ---
 * [  0] 0x8007DA5C size:0x1AC   global GXChannel_Init
 */

/* --- forward decls --- */
asm void GXChannel_Init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_GXChannel_Init[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_GXChannel_Init = {
    (void *)&GXChannel_Init, 0x000001AC, (void *)extab_GXChannel_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void GXChannel_Init(void) { /* 0x8007DA5C size:0x1AC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    clrlwi r0, r7, 24
    cmplwi r0, 0x1
    stw r31, 0xc(r1)
    mr r31, r3
    stw r30, 0x8(r1)
    stw r4, 0x0(r3)
    li r3, 0x0
    stw r5, 0x4(r31)
    stw r6, 0x8(r31)
    stb r3, 0xc(r31)
    stw r3, 0x10(r31)
    bne GXChannel_Init_L_8007DBEC
    lbz r0, 0xc(r31)
    cmplwi r0, 0x1
    beq GXChannel_Init_L_8007DBEC
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
    b GXChannel_Init_L_8007DB10
    GXChannel_Init_L_8007DAEC:
    lwz r0, 0x4(r30)
    cmpwi r0, 0x1
    beq GXChannel_Init_L_8007DB0C
    lhz r0, 0x12(r30)
    lwz r3, 0x0(r30)
    lwz r4, 0x14(r30)
    clrlwi r5, r0, 24
    bl GX_SetArray
    GXChannel_Init_L_8007DB0C:
    addi r30, r30, 0x18
    GXChannel_Init_L_8007DB10:
    lwz r0, 0x0(r30)
    cmpwi r0, 0xff
    bne GXChannel_Init_L_8007DAEC
    lwz r3, 0x4(r31)
    lwz r30, 0xc(r3)
    bl GX_ClearVtxDesc
    lwz r30, 0x8(r30)
    b GXChannel_Init_L_8007DB6C
    GXChannel_Init_L_8007DB30:
    lwz r3, 0x0(r30)
    lwz r4, 0x4(r30)
    bl GX_SetVtxDesc
    lwz r0, 0x0(r30)
    cmpwi r0, 0x9
    bge GXChannel_Init_L_8007DB50
    cmpwi r0, 0x0
    bge GXChannel_Init_L_8007DB68
    GXChannel_Init_L_8007DB50:
    lwz r4, 0x0(r30)
    li r3, 0x0
    lwz r5, 0x8(r30)
    lwz r6, 0xc(r30)
    lbz r7, 0x10(r30)
    bl GX_SetVtxAttrFmt
    GXChannel_Init_L_8007DB68:
    addi r30, r30, 0x18
    GXChannel_Init_L_8007DB6C:
    lwz r0, 0x0(r30)
    cmpwi r0, 0xff
    bne GXChannel_Init_L_8007DB30
    lwz r4, 0x4(r31)
    lis r3, 0x1
    addi r0, r3, -0x8000
    lwz r4, 0xc(r4)
    lhz r4, 0xc(r4)
    rlwinm r4, r4, 0, 16, 17
    cmpw r4, r0
    beq GXChannel_Init_L_8007DBDC
    bge GXChannel_Init_L_8007DBB4
    cmpwi r4, 0x4000
    beq GXChannel_Init_L_8007DBD0
    bge GXChannel_Init_L_8007DBE4
    cmpwi r4, 0x0
    beq GXChannel_Init_L_8007DBC4
    b GXChannel_Init_L_8007DBE4
    GXChannel_Init_L_8007DBB4:
    subi r0, r3, 0x4000
    cmpw r4, r0
    beq GXChannel_Init_L_8007DBE4
    b GXChannel_Init_L_8007DBE4
    GXChannel_Init_L_8007DBC4:
    li r3, 0x0
    bl GX_SetCullMode
    b GXChannel_Init_L_8007DBE4
    GXChannel_Init_L_8007DBD0:
    li r3, 0x1
    bl GX_SetCullMode
    b GXChannel_Init_L_8007DBE4
    GXChannel_Init_L_8007DBDC:
    li r3, 0x2
    bl GX_SetCullMode
    GXChannel_Init_L_8007DBE4:
    li r0, 0x1
    stb r0, 0xc(r31)
    GXChannel_Init_L_8007DBEC:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

