/* === extracted from auto_03_800578C4_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (3 fns, .text 0x800578C4..0x80057960) ---
 * [  0] 0x800578C4 size:0x10    global TornadoEffect_SetMatrixRow0_5c
 * [  1] 0x800578D4 size:0x8     global TornadoEffect_SetFieldAc
 * [  2] 0x800578DC size:0x84    global TornadoEffect_SetMatrix1c
 */

/* --- forward decls --- */
asm void TornadoEffect_SetMatrixRow0_5c(void);
asm void TornadoEffect_SetFieldAc(void);
asm void TornadoEffect_SetMatrix1c(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_SetMatrixRow0_5c(void) { /* 0x800578C4 size:0x10 */
    nofralloc
    stfs f1, 0x5c(r3)
    stfs f2, 0x60(r3)
    stfs f3, 0x64(r3)
    blr
}

asm void TornadoEffect_SetFieldAc(void) { /* 0x800578D4 size:0x8 */
    nofralloc
    stfs f1, 0xac(r3)
    blr
}

asm void TornadoEffect_SetMatrix1c(void) { /* 0x800578DC size:0x84 */
    nofralloc
    lfs f1, 0x0(r4)
    lfs f0, 0x4(r4)
    stfs f1, 0x1c(r3)
    lfs f1, 0x8(r4)
    stfs f0, 0x20(r3)
    lfs f0, 0xc(r4)
    stfs f1, 0x24(r3)
    lfs f1, 0x10(r4)
    stfs f0, 0x28(r3)
    lfs f0, 0x14(r4)
    stfs f1, 0x2c(r3)
    lfs f1, 0x18(r4)
    stfs f0, 0x30(r3)
    lfs f0, 0x1c(r4)
    stfs f1, 0x34(r3)
    lfs f1, 0x20(r4)
    stfs f0, 0x38(r3)
    lfs f0, 0x24(r4)
    stfs f1, 0x3c(r3)
    lfs f1, 0x28(r4)
    stfs f0, 0x40(r3)
    lfs f0, 0x2c(r4)
    stfs f1, 0x44(r3)
    lfs f1, 0x30(r4)
    stfs f0, 0x48(r3)
    lfs f0, 0x34(r4)
    stfs f1, 0x4c(r3)
    lfs f1, 0x38(r4)
    stfs f0, 0x50(r3)
    lfs f0, 0x3c(r4)
    stfs f1, 0x54(r3)
    stfs f0, 0x58(r3)
    blr
}

