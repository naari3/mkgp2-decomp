/* LUT_Cosine (0x800658B4, size 0x74).
 *
 * 16-bit cosine LUT lookup. Radians → 65536-step binary angle via scale
 * lbl_806D2C60 (= 10430.378 = 65536 / (2*PI)), plus ±half-LSB rounding bias
 * (lbl_806D2C54 / lbl_806D2C58 = ±1/131072) per sign of angle, fctiwz to
 * int, masked to low 16 bits (lbl_806CEF18 = 0xFFFF), -0x4000 (= -π/2)
 * phase shift (cos(x) = sin(x + π/2)), then mirror at 0x7FFF for the
 * upper half of the period, then table lookup in lbl_802EE580[].
 *
 * Retreated to asm_fn after ~12 cycles: every C variant produced the
 * symmetric register-name swap (mask=r3 / int_val=r4 instead of target's
 * mask=r4 / int_val=r3), a classic CW register-allocator hard-block per
 * per_fn_matching_strategy.md §14.3. The sibling LUT_Sine matches as
 * plain C in src/game/LUT_Sine.c.
 *
 * Manual extab/extabindex emit via .extab_user / .extabindex_user; the
 * postprocess_extab_user.py rename hook (configured by extab_padding) maps
 * extab_LUT_Cosine → @etb_800080A0 and extabindex_LUT_Cosine →
 * @eti_80020F6C.
 */

extern unsigned int lbl_806CEF18;
extern unsigned int lbl_806D2C54;
extern unsigned int lbl_806D2C58;
extern unsigned int lbl_806D2C5C;
extern unsigned int lbl_806D2C60;
extern unsigned int lbl_802EE580[];

asm void LUT_Cosine(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_LUT_Cosine[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_LUT_Cosine = {
    (void *)&LUT_Cosine, 0x00000074, (void *)extab_LUT_Cosine
};

asm void LUT_Cosine(void) {
    nofralloc
    lfs f0, lbl_806D2C5C(r2)
    stwu r1, -0x10(r1)
    fcmpo cr0, f1, f0
    lfs f2, lbl_806D2C60(r2)
    ble LUT_Cosine_L_800658D0
    lfs f0, lbl_806D2C54(r2)
    b LUT_Cosine_L_800658D4
LUT_Cosine_L_800658D0:
    lfs f0, lbl_806D2C58(r2)
LUT_Cosine_L_800658D4:
    fmadds f0, f2, f1, f0
    lhz r4, lbl_806CEF18(r13)
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r3, 0xc(r1)
    and r3, r3, r4
    subi r0, r3, 0x4000
    clrlwi r0, r0, 16
    and r4, r0, r4
    clrlwi r0, r4, 16
    cmplwi r0, 0x7fff
    ble LUT_Cosine_L_80065910
    lis r0, 0x1
    subf r0, r4, r0
    clrlwi r4, r0, 16
LUT_Cosine_L_80065910:
    lis r3, lbl_802EE580@ha
    clrlslwi r0, r4, 16, 2
    addi r3, r3, lbl_802EE580@l
    lfsx f1, r3, r0
    addi r1, r1, 0x10
    blr
}
