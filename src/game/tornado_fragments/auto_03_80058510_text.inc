/* === extracted from auto_03_80058510_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (1 fns, .text 0x80058510..0x80058534) ---
 * [  0] 0x80058510 size:0x24    global TornadoEffect_SetField128AndMaybeClear134
 */

/* --- forward decls --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x80058510 size:0x24 */
void TornadoEffect_SetField128AndMaybeClear134(void *e, int v, unsigned char reset) {
    if (v == 0) {
        return;
    }
    if (reset == 1) {
        TE_S32(e, 0x134) = 0;
    }
    TE_S32(e, 0x128) = v;
}

