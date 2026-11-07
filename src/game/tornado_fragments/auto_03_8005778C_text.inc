/* === extracted from auto_03_8005778C_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D28C8;

/* --- function index (3 fns, .text 0x8005778C..0x800577C8) ---
 * [  0] 0x8005778C size:0x1C    global TornadoEffect_ClearFlagC0AndSetC4
 * [  1] 0x800577A8 size:0x8     global TornadoEffect_SetField11c
 * [  2] 0x800577B0 size:0x18    global TornadoEffect_SetFlagB4
 */

/* --- forward decls --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x8005778C size:0x1C */
void TornadoEffect_ClearFlagC0AndSetC4(void *e, float v) {
    if (TE_U8(e, 0xC0) == 1) {
        TE_F(e, 0xC4) = v;
    }
    TE_U8(e, 0xC0) = 0;
}

/* 0x800577A8 size:0x8 */
void TornadoEffect_SetField11c(void *e, float v) {
    TE_F(e, 0x11C) = v;
}

/* 0x800577B0 size:0x18 */
void TornadoEffect_SetFlagB4(void *e, unsigned char on) {
    TE_U8(e, 0xB4) = on;
    if (!on) {
        TE_F(e, 0x11C) = lbl_806D28C8;
    }
}

