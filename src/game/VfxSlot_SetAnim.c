/* === extracted from auto_03_800AFF6C_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (2 fns, .text 0x800AFF6C..0x800AFF9C) ---
 * [  0] 0x800AFF6C size:0x14    global VfxSlot_SetAnimSpeed
 * [  1] 0x800AFF80 size:0x1C    global VfxSlot_SetAnimFrame
 */

/* --- forward decls --- */
asm void VfxSlot_SetAnimSpeed(void);
asm void VfxSlot_SetAnimFrame(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void VfxSlot_SetAnimSpeed(void) { /* 0x800AFF6C size:0x14 */
    nofralloc
    lwz r0, 0x4(r3)
    cmplwi r0, 0x0
    beqlr
    stfs f1, 0x10(r3)
    blr
}

asm void VfxSlot_SetAnimFrame(void) { /* 0x800AFF80 size:0x1C */
    nofralloc
    lwz r0, 0x4(r3)
    cmplwi r0, 0x0
    beqlr
    li r0, 0x0
    stb r0, 0xa(r3)
    stfs f1, 0xc(r3)
    blr
}
