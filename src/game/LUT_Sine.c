/* LUT_Sine (0x80065928, size 0x68).
 *
 * 16-bit sine LUT lookup. Radians → 65536-step binary angle via scale
 * lbl_806D2C60 (= 10430.378 = 65536 / (2*PI)), plus ±half-LSB rounding bias
 * (lbl_806D2C54 / lbl_806D2C58 = ±1/131072) per sign of angle, fctiwz to
 * int, masked to low 16 bits (lbl_806CEF18 = 0xFFFF), mirror at 0x7FFF for
 * the upper half of the period, then table lookup in lbl_802EE580[].
 *
 * Has extab/extabindex entry (large-frame flag from the stack-allocated
 * fctiwz scratch slot), so wrap with #pragma exceptions on to let CW
 * auto-emit the singleton extab + extabindex entries.
 *
 * Critical idioms for byte-identical match (sibling LUT_Cosine in
 * LUT_Cosine.c hit a register-allocator hard-block and retreated to
 * asm_fn): (1) `float scale = lbl_806D2C60;` local forces CW to eagerly
 * hoist the scale load before the conditional branch (else CW schedules it
 * after L_continue, adding a fadds + 4-byte size overflow); (2) compound
 * `idx &= lbl_806CEF18;` triggers in-place AND on the lwz destination
 * register (else CW splits AND src/dst, adding an extra register and
 * different reg allocation).
 */

extern const float lbl_806D2C54;
extern const float lbl_806D2C58;
extern const float lbl_806D2C5C;
extern const float lbl_806D2C60;
extern unsigned short lbl_806CEF18;
extern const float lbl_802EE580[];

#pragma exceptions on
float LUT_Sine(float angle) {
    float scale = lbl_806D2C60;
    float bias = (angle > lbl_806D2C5C) ? lbl_806D2C54 : lbl_806D2C58;
    unsigned int idx = (int)(scale * angle + bias);
    idx &= lbl_806CEF18;
    if ((unsigned short)idx > 0x7FFF) {
        idx = (0x10000 - idx) & 0xFFFF;
    }
    return lbl_802EE580[(unsigned short)idx];
}
#pragma exceptions reset
