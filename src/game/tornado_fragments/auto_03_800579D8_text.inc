/* === extracted from auto_03_800579D8_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D28CC;
extern const float lbl_806D28D0;
extern const float lbl_806D28F8;

/* --- function index (5 fns, .text 0x800579D8..0x80057A8C) ---
 * [  0] 0x800579D8 size:0x28    global TornadoEffect_SetColorY
 * [  1] 0x80057A00 size:0x8     global TornadoEffect_GetField114
 * [  2] 0x80057A08 size:0x10    global TornadoEffect_SetField114
 * [  3] 0x80057A18 size:0x34    global TornadoEffect_TriggerWheelScaleAnim
 * [  4] 0x80057A4C size:0x40    global TornadoEffect_SetColorRGBLerp
 */

/* --- forward decls --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x800579D8 size:0x28 */
void TornadoEffect_SetColorY(void *e, float y) {
    TE_S32(e, 0xD4) = 1;
    TE_F(e, 0xE0) = lbl_806D28CC;
    TE_F(e, 0xE4) = y;
    TE_F(e, 0xE8) = lbl_806D28CC;
    TE_F(e, 0xEC) = lbl_806D28CC;
    TE_F(e, 0xF0) = y;
    TE_F(e, 0xF4) = lbl_806D28CC;
}

/* 0x80057A00 size:0x8 */
float TornadoEffect_GetField114(void *e) {
    return TE_F(e, 0x114);
}

/* 0x80057A08 size:0x10 */
void TornadoEffect_SetField114(void *e, float v) {
    TE_F(e, 0x118) = TE_F(e, 0x114);
    TE_F(e, 0x114) = v;
}

/* 0x80057A18 size:0x34 */
void TornadoEffect_TriggerWheelScaleAnim(void *e, float v) {
    TE_S32(e, 0x104) = 1;
    TE_F(e, 0x108) = v;
    if (TE_F(e, 0x108) > TE_F(e, 0x10C)) {
        TE_F(e, 0x110) = lbl_806D28D0;
    } else {
        TE_F(e, 0x110) = lbl_806D28F8;
    }
}

/* 0x80057A4C size:0x40 */
void TornadoEffect_SetColorRGBLerp(void *e, float r, float g, float b, unsigned char now) {
    if (now == 1) {
        TE_F(e, 0xEC) = r;
        TE_F(e, 0xF0) = g;
        TE_F(e, 0xF4) = b;
        TE_F(e, 0xE0) = r;
        TE_F(e, 0xE4) = g;
        TE_F(e, 0xE8) = b;
    } else {
        TE_S32(e, 0xD4) = 3;
        TE_F(e, 0xE0) = r;
        TE_F(e, 0xE4) = g;
        TE_F(e, 0xE8) = b;
    }
}

