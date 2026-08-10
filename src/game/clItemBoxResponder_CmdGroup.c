/* === extracted from auto_03_8005FFF0_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (3 fns, .text 0x8005FFF0..0x80060024) ---
 * [  0] 0x8005FFF0 size:0x14    global clItemBoxResponder_IsCmdSlotFree
 * [  1] 0x80060004 size:0x18    global clItemBoxResponder_CmdSlotCountdown
 * [  2] 0x8006001C size:0x8     global clItemBoxResponder_GetBoundPosVec3
 */

/* --- forward decls --- */
asm void clItemBoxResponder_IsCmdSlotFree(void);
asm void clItemBoxResponder_CmdSlotCountdown(void);
asm void clItemBoxResponder_GetBoundPosVec3(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBoxResponder_IsCmdSlotFree(void) { /* 0x8005FFF0 size:0x14 */
    nofralloc
    lwz r0, 0x8(r3)
    li r3, 0x1
    cntlzw r0, r0
    rlwnm r3, r3, r0, 31, 31
    blr
}

asm void clItemBoxResponder_CmdSlotCountdown(void) { /* 0x80060004 size:0x18 */
    nofralloc
    lwz r4, 0x8(r3)
    cmpwi r4, 0x0
    blelr
    subi r0, r4, 0x1
    stw r0, 0x8(r3)
    blr
}

asm void clItemBoxResponder_GetBoundPosVec3(void) { /* 0x8006001C size:0x8 */
    nofralloc
    lwz r3, 0x4(r3)
    blr
}


