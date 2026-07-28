/* === extracted from auto_03_80058510_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (1 fns, .text 0x80058510..0x80058534) ---
 * [  0] 0x80058510 size:0x24    global TornadoEffect_SetField128AndMaybeClear134
 */

/* --- forward decls --- */
asm void TornadoEffect_SetField128AndMaybeClear134(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_SetField128AndMaybeClear134(void) { /* 0x80058510 size:0x24 */
    nofralloc
    cmpwi r4, 0x0
    beqlr
    clrlwi r0, r5, 24
    cmplwi r0, 0x1
    bne TornadoEffect_SetField128AndMaybeClear134_L_8005852C
    li r0, 0x0
    stw r0, 0x134(r3)
    TornadoEffect_SetField128AndMaybeClear134_L_8005852C:
    stw r4, 0x128(r3)
    blr
}

