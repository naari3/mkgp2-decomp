/* === extracted from KartBody === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (1 fns, .text 0x8005771C..0x80057738) ---
 * [  0] 0x8005771C size:0x1C    global KartBody_SetWarpTransitFlag
 */

/* --- forward decls --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x8005771C size:0x1C */
void KartBody_SetWarpTransitFlag(void *e, unsigned char on) {
    TE_U8(e, 0xD2) = on;
    if (TE_U8(e, 0xD2) == 1) {
        TE_S32(e, 0x13C) = -1;
    }
}

