/* === extracted from KartBody === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (1 fns, .text 0x8005771C..0x80057738) ---
 * [  0] 0x8005771C size:0x1C    global KartBody_SetWarpTransitFlag
 */

/* --- forward decls --- */
asm void KartBody_SetWarpTransitFlag(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartBody_SetWarpTransitFlag(void) { /* 0x8005771C size:0x1C */
    nofralloc
    stb r4, 0xd2(r3)
    lbz r0, 0xd2(r3)
    cmplwi r0, 0x1
    bnelr
    li r0, -0x1
    stw r0, 0x13c(r3)
    blr
}

