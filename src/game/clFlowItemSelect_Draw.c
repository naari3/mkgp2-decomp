/* === extracted from auto_clFlowItemSelect_Dra_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemDisplay_GetOrCreate();
extern void fn_801A0004();
extern void fn_801F8A34();
extern void fn_801F8E58();
extern void fn_8020AC34();
extern void fn_8023CD54();

/* --- function index (1 fns, .text 0x801CBCAC..0x801CBD58) ---
 * [  0] 0x801CBCAC size:0xAC    global clFlowItemSelect_Draw
 */

/* --- forward decls --- */
asm void clFlowItemSelect_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowItemSelect_Draw[8] = {
    0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowItemSelect_Draw = {
    (void *)&clFlowItemSelect_Draw, 0x000000AC, (void *)extab_clFlowItemSelect_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowItemSelect_Draw(void) { /* 0x801CBCAC size:0xAC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    mr r26, r3
    li r30, 0x0
    mr r31, r26
    clFlowItemSelect_Draw_L_801CBCC8:
    lwz r3, 0x80(r31)
    cmplwi r3, 0x0
    beq clFlowItemSelect_Draw_L_801CBCDC
    lwz r3, 0x0(r3)
    bl fn_801A0004
    clFlowItemSelect_Draw_L_801CBCDC:
    addi r30, r30, 0x1
    addi r31, r31, 0x4
    cmpwi r30, 0x5
    blt clFlowItemSelect_Draw_L_801CBCC8
    bl fn_801F8E58
    mr r30, r26
    mr r29, r3
    li r28, 0x0
    clFlowItemSelect_Draw_L_801CBCFC:
    li r27, 0x0
    mr r31, r30
    clFlowItemSelect_Draw_L_801CBD04:
    lwz r4, 0x98(r31)
    mr r3, r29
    li r5, 0x5
    bl fn_801F8A34
    addi r27, r27, 0x1
    addi r31, r31, 0x4
    cmpwi r27, 0x4
    blt clFlowItemSelect_Draw_L_801CBD04
    addi r28, r28, 0x1
    addi r30, r30, 0x10
    cmpwi r28, 0x3
    blt clFlowItemSelect_Draw_L_801CBCFC
    lwz r3, 0xe8(r26)
    bl fn_8023CD54
    bl ItemDisplay_GetOrCreate
    bl fn_8020AC34
    lmw r26, 0x8(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

