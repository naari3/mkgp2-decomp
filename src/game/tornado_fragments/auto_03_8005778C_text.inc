/* === extracted from auto_03_8005778C_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28C8;

/* --- function index (3 fns, .text 0x8005778C..0x800577C8) ---
 * [  0] 0x8005778C size:0x1C    global TornadoEffect_ClearFlagC0AndSetC4
 * [  1] 0x800577A8 size:0x8     global TornadoEffect_SetField11c
 * [  2] 0x800577B0 size:0x18    global TornadoEffect_SetFlagB4
 */

/* --- forward decls --- */
asm void TornadoEffect_ClearFlagC0AndSetC4(void);
asm void TornadoEffect_SetField11c(void);
asm void TornadoEffect_SetFlagB4(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_ClearFlagC0AndSetC4(void) { /* 0x8005778C size:0x1C */
    nofralloc
    lbz r0, 0xc0(r3)
    cmplwi r0, 0x1
    bne TornadoEffect_ClearFlagC0AndSetC4_L_8005779C
    stfs f1, 0xc4(r3)
    TornadoEffect_ClearFlagC0AndSetC4_L_8005779C:
    li r0, 0x0
    stb r0, 0xc0(r3)
    blr
}

asm void TornadoEffect_SetField11c(void) { /* 0x800577A8 size:0x8 */
    nofralloc
    stfs f1, 0x11c(r3)
    blr
}

asm void TornadoEffect_SetFlagB4(void) { /* 0x800577B0 size:0x18 */
    nofralloc
    clrlwi. r0, r4, 24
    stb r4, 0xb4(r3)
    bnelr
    lfs f0, lbl_806D28C8(r2)
    stfs f0, 0x11c(r3)
    blr
}

