/* === extracted from auto_03_800579D8_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28CC;
extern unsigned int lbl_806D28D0;
extern unsigned int lbl_806D28F8;

/* --- function index (5 fns, .text 0x800579D8..0x80057A8C) ---
 * [  0] 0x800579D8 size:0x28    global TornadoEffect_SetColorY
 * [  1] 0x80057A00 size:0x8     global TornadoEffect_GetField114
 * [  2] 0x80057A08 size:0x10    global TornadoEffect_SetField114
 * [  3] 0x80057A18 size:0x34    global TornadoEffect_TriggerWheelScaleAnim
 * [  4] 0x80057A4C size:0x40    global TornadoEffect_SetColorRGBLerp
 */

/* --- forward decls --- */
asm void TornadoEffect_SetColorY(void);
asm void TornadoEffect_GetField114(void);
asm void TornadoEffect_SetField114(void);
asm void TornadoEffect_TriggerWheelScaleAnim(void);
asm void TornadoEffect_SetColorRGBLerp(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_SetColorY(void) { /* 0x800579D8 size:0x28 */
    nofralloc
    li r0, 0x1
    lfs f0, lbl_806D28CC(r2)
    stw r0, 0xd4(r3)
    stfs f0, 0xe0(r3)
    stfs f1, 0xe4(r3)
    stfs f0, 0xe8(r3)
    stfs f0, 0xec(r3)
    stfs f1, 0xf0(r3)
    stfs f0, 0xf4(r3)
    blr
}

asm void TornadoEffect_GetField114(void) { /* 0x80057A00 size:0x8 */
    nofralloc
    lfs f1, 0x114(r3)
    blr
}

asm void TornadoEffect_SetField114(void) { /* 0x80057A08 size:0x10 */
    nofralloc
    lfs f0, 0x114(r3)
    stfs f0, 0x118(r3)
    stfs f1, 0x114(r3)
    blr
}

asm void TornadoEffect_TriggerWheelScaleAnim(void) { /* 0x80057A18 size:0x34 */
    nofralloc
    li r0, 0x1
    stw r0, 0x104(r3)
    stfs f1, 0x108(r3)
    lfs f1, 0x108(r3)
    lfs f0, 0x10c(r3)
    fcmpo cr0, f1, f0
    ble TornadoEffect_TriggerWheelScaleAnim_L_80057A40
    lfs f0, lbl_806D28D0(r2)
    stfs f0, 0x110(r3)
    blr
    TornadoEffect_TriggerWheelScaleAnim_L_80057A40:
    lfs f0, lbl_806D28F8(r2)
    stfs f0, 0x110(r3)
    blr
}

asm void TornadoEffect_SetColorRGBLerp(void) { /* 0x80057A4C size:0x40 */
    nofralloc
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    bne TornadoEffect_SetColorRGBLerp_L_80057A74
    stfs f1, 0xec(r3)
    stfs f2, 0xf0(r3)
    stfs f3, 0xf4(r3)
    stfs f1, 0xe0(r3)
    stfs f2, 0xe4(r3)
    stfs f3, 0xe8(r3)
    blr
    TornadoEffect_SetColorRGBLerp_L_80057A74:
    li r0, 0x3
    stw r0, 0xd4(r3)
    stfs f1, 0xe0(r3)
    stfs f2, 0xe4(r3)
    stfs f3, 0xe8(r3)
    blr
}

