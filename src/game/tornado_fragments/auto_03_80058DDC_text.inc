/* === extracted from auto_03_80058DDC_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (1 fns, .text 0x80058DDC..0x80058DE8) ---
 * [  0] 0x80058DDC size:0xC     global TornadoEffect_TriggerField140
 */

/* --- forward decls --- */
asm void TornadoEffect_TriggerField140(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_TriggerField140(void) { /* 0x80058DDC size:0xC */
    nofralloc
    li r0, 0x2
    stw r0, 0x140(r3)
    blr
}

