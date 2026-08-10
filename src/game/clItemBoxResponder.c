/* === extracted from auto_clItemBoxResponder_C_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (1 fns, .text 0x8005FFBC..0x8005FFF0) ---
 * [  0] 0x8005FFBC size:0x34    global clItemBoxResponder_CmdGetWorldPos
 */

/* --- forward decls --- */
asm void clItemBoxResponder_CmdGetWorldPos(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clItemBoxResponder_CmdGetWorldPos[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clItemBoxResponder_CmdGetWorldPos = {
    (void *)&clItemBoxResponder_CmdGetWorldPos, 0x00000034, (void *)extab_clItemBoxResponder_CmdGetWorldPos
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_CmdGetWorldPos(void) { /* 0x8005FFBC size:0x34 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    li r0, 0x3c
    stw r0, 0x8(r3)
    lwz r12, 0x0(r3)
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


